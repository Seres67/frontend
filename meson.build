project('frontend', 'c', default_options: ['warning_level=3'])
include = include_directories('include')
src = ['src/main.c', 'src/linked_list.c']
allegro = dependency('allegro-5', required: true)
allegro_font = dependency('allegro_font-5', required: true)
executable('frontend', src, include_directories: include, dependencies: [allegro, allegro_font])
