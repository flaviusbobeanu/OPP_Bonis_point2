cmake_minimum_required(VERSION 3.20)
project(HAFFMAN)

set(CMAKE_CXX_STANDARD 20)

add_executable(HAFFMAN
        main.cpp
        node.cpp
        code.cpp
        huffman.cpp
        aux_functions.cpp
        writebit.cpp
        ReadBit.cpp
        Huffman_encoding.cpp
        Huffman_decoding.cpp
)
