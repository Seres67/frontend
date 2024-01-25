#include "linked_list.h"
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>

linked_list_t *event_queue = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#pragma pack(push, 1)

typedef struct data_s
{
    char command;
    short arg1;
    short arg2;
} m_data_t;

#pragma pack(pop)

void parse()
{
    // 1 ADD PLAYER (X, Y)
    // 2 REMOVE PLAYER
    // 3 MOVE PLAYER (DELTAX, DELTAY)
    // 4 SET PLAYER POS (X, Y)
    // 5 ADD ENTITY (ID, X, Y)
    // 6 REMOVE ENTITY (ID)
    // 7 MOVE ENTITY (ID, DELTAX, DELTAY)
    // 8 SET ENTITY POS (ID, X, Y)
}

void *frontend_func(void *args)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        if (event_queue->next != NULL) {
            m_data_t *received = linked_list_pop(event_queue);
            printf("frontend received: %d %d %d\n", received->command,
                   received->arg1, received->arg2);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int setup_socket(int s, int port)
{
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    int opt = 1;
    int status = setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                            sizeof(opt));
    if (status) {
        perror("setsockopt");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    long b = bind(s, (struct sockaddr *)&address, sizeof(address));
    if (b < 0) {
        perror("bind failed");
        return -1;
    }
    int l = listen(s, 3);
    if (l < 0) {
        perror("cannot listen");
        return -1;
    }
    int new_socket = accept(s, (struct sockaddr *)&address, &addrlen);
    if (new_socket < 0) {
        perror("cannot accept");
        return -1;
    }
    return new_socket;
}

void *thread_func(void *args)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("couldnt create socket");
        return NULL;
    }
    int client_socket = setup_socket(server_socket, 12948);
    while (1) {
        char buffer[6] = {0};
        ssize_t r = read(client_socket, buffer, 6);
        if (r == 0)
            break;
        buffer[5] = 0;
        printf("=> buffer %d %d %d %d %d %d\n", buffer[0], buffer[1], buffer[2],
               buffer[3], buffer[4], buffer[5]);
        short arg1 = (buffer[1] << 8) + buffer[2];
        short arg2 = (buffer[3] << 8) + buffer[4];
        m_data_t received = {.command = buffer[0], .arg1 = arg1, .arg2 = arg2};
        pthread_mutex_lock(&mutex);
        linked_list_push(event_queue, &received);
        pthread_mutex_unlock(&mutex);
    }
    return (void *)1;
}

int main(int ac, char **av)
{
    event_queue = linked_list_new(NULL);
    pthread_t server_thread, frontend_thread;
    pthread_create(&server_thread, NULL, thread_func, NULL);
    pthread_create(&frontend_thread, NULL, frontend_func, NULL);
    pthread_join(server_thread, NULL);
    pthread_join(frontend_thread, NULL);
    return 0;
}
