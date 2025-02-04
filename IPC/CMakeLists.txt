cmake_minimum_required(VERSION 3.16)

add_executable(pipe ./src/pipe.c)
add_executable(fifo_parent ./src/fifo_parent.c)
add_executable(fifo_child ./src/fifo_child.c)

