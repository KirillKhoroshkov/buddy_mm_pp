#include <utility>

#ifndef BUDDY_MM_COMMANDS_H
#define BUDDY_MM_COMMANDS_H

#define exit_command "exit"
#define print_command "print"
#define init_command "start"
#define allocate_command "allocate"
#define reallocate_command "reallocate"
#define save_command "save"
#define rewrite_flag "-r"
#define open_command "open"
#define help_command "help"
#define read_command "read"
#define free_command "free"
#define get_command "get"
#define set_command "set"

#include <memory.h>
#include <stdbool.h>
#include <iostream>
#include "settings.h"

using namespace::std;

class Command: public Info {};

class Exit_command: public Command {
public:
    Exit_command();
};

class  Print_command: public Command {
public:
    Print_command();
};

class Init_command: public Command {
public:
    size_t degree;
    Init_command(size_t degree);
};

class  Allocate_command: public Command {
public:
    size_t size;
    Allocate_command(size_t size);
};

class  Reallocate_command: public Command {
public:
    void *address;
    size_t new_size;
    Reallocate_command(void *address, size_t new_size);
};

class Save_command: public Command {
public:
    string file_path;
    bool rewrite_it;
    Save_command(string file_path, bool rewrite_it);
    ~Save_command();
};

class  Open_command: public Command {
public:
    string file_path;
    Open_command(string file_path);
    ~Open_command();
};

class Help_command: public Command {
public:
    Help_command();
};

class Read_command: public Command {
public:
    string file_path;
    Read_command(string file_path);
    ~Read_command();
};

class Free_command: public Command {
public:
    void *address;
    Free_command(void *address);
};

class Get_command: public Command {
public:
    void *address;
    size_t index;
    Get_command(void *address, size_t index);
};

class Set_command: public Command {
public:
    void *address;
    size_t index;
    char new_value;
    Set_command(void *address, size_t index, char new_value);
};
#endif //BUDDY_MM_COMMANDS_H