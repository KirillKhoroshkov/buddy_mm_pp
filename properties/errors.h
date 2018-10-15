#include <utility>

#ifndef BUDDY_MM_ERRORS_H
#define BUDDY_MM_ERRORS_H

#define unknown_command_error 2
#define invalid_args_error 3
#define not_configured_error 4
#define not_enough_space_error 5
#define invalid_configuration_error 6
#define out_of_memory_error 7
#define out_of_allocated_memory_error 8
#define invalid_file_path_error 9
#define invalid_file_error 10
#define file_already_consist_error 11
#define reading_while_reading_error 12

#include <malloc.h>
#include <memory.h>
#include "messages.h"
#include <iostream>
#include "settings.h"

using namespace::std;

class Error: public Info {
public:
    int code;
    string message;
    Error(int code, string message);
    ~Error();
};

class Unknown_command_error: public Error {
public:
    Unknown_command_error();
};

class Invalid_args_error: public Error {
public:
    Invalid_args_error();
};

class Not_configured_error: public Error {
public:
    Not_configured_error();
};

class Not_enough_space_error: public Error {
public:
    Not_enough_space_error();
};

class Invalid_configuration_error: public Error {
public:
    Invalid_configuration_error();
};

class Out_of_memory_error: public Error {
public:
    Out_of_memory_error();
};

class Out_of_allocated_memory_error: public Error {
public:
    Out_of_allocated_memory_error();
};

class Invalid_file_path_error: public Error {
public:
    Invalid_file_path_error();
};

class Invalid_file_error: public Error {
public:
    Invalid_file_error();
};

class File_already_consist_error: public Error {
public:
    File_already_consist_error();
};

class Reading_while_reading_error: public Error {
public:
    Reading_while_reading_error();
};

#endif //BUDDY_MM_ERRORS_H