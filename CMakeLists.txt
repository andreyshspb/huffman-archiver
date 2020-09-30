cmake_minimum_required(VERSION 3.15)
project(hw_03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(include)

add_executable(hw_03 src/main.cpp include/Huffman.h src/Huffman.cpp
               include/BitStream.h src/BitStream.cpp include/HuffmanArchiver.h
               src/HuffmanArchiver.cpp include/CLI.h src/CLI.cpp)

add_executable(test_hw_03 test/TestMain.cpp test/TestCLI.cpp test/doctest.h
               include/CLI.h src/CLI.cpp test/TestHuffmanTree.cpp
               include/Huffman.h src/Huffman.cpp test/TestBitStream.cpp
               include/BitStream.h src/BitStream.cpp test/TestHuffmanArchiver.cpp
               include/HuffmanArchiver.h src/HuffmanArchiver.cpp)