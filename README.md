# Frontend

This will be a TCP server receiving information to display on screen, so I can experiment with Vale as a backend.

## Prerequisites

- a C compiler
- meson
- ninja

## How to build

`meson setup build && cd build && ninja`

## How to run

`cd build && ./frontend`

## How to use

`frontend` is a TCP server waiting for data to parse and display. 
Here's the protocol:

| Action Name           | First Byte | Second Byte       | Third Byte         | Fourth Byte       | Fifth Byte         |
| add player/camera     | 0x01       | X first byte      | X second byte      | Y first byte      | Y second byte      |
| remove player/camera  | 0x02       |                   |                    |                   |                    |
| move player/camera    | 0x03       | DeltaX first byte | DeltaX second byte | DeltaY first byte | DeltaY second byte |
| set pos player/camera | 0x04       | X first byte      | X second byte      | Y first byte      | Y second byte      |
