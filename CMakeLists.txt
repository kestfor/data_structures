cmake_minimum_required(VERSION 3.23)

project(data_structures)

set(CMAKE_C_STANDARD 17)

add_executable(hash_table hash_table/hash_table.c)
add_executable(fibonacci_heap--priority_queue fibonacci_heap--priority_queue/fibonacci_heap.c)
add_executable(vector vector/vector.c)
add_executable(avl_tree avl_tree/avl_tree.c)
add_executable(list list/list.c)