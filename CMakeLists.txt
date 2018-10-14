cmake_minimum_required(VERSION 3.12)
project(buddy_mm_pp)

set(CMAKE_CXX_STANDARD 17)

add_executable(buddy_mm_pp main.cpp buddy_mm/buddy_mm.h properties/errors.h properties/commands.h properties/messages.h properties/settings.h parser/parser.h parser/parser.cpp)