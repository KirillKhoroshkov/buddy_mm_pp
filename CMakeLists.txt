cmake_minimum_required(VERSION 3.12)
project(buddy_mm_pp)

set(CMAKE_CXX_STANDARD 17)

add_executable(buddy_mm_pp main.cpp buddy_mm/buddy_mm.h buddy_mm/buddy_mm.cpp properties/errors.h properties/errors.cpp properties/commands.h properties/commands.cpp properties/messages.h properties/settings.h properties/settings.cpp parser/parser.h parser/parser.cpp)