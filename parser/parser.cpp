#include "parser.h"

Info *parse(string &raw_text) {
    Info *response;
    istringstream string_stream(raw_text);
    string entered_command;
    if (!(string_stream >> entered_command)) { // if string is empty
        response = new Invalid_args_error;
    } else if (entered_command == get_command) {
        void *address;
        size_t index;
        if (string_stream >> address && string_stream >> index) {
            response = new Get_command(address, index);
        } else {
            response = new Invalid_args_error;
        }
    } else if (entered_command == set_command) {
        void *address;
        size_t index;
        char new_value;
        if (string_stream >> address && string_stream >> index && string_stream >> new_value) {
            response = new Set_command(address, index, new_value);
        } else {
            response = new Invalid_args_error();
        }
    } else if (entered_command == reallocate_command) {
        void *address;
        size_t new_size;
        if (string_stream >> address && string_stream >> new_size) {
            response = new Reallocate_command(address, new_size);
        } else {
            response = new Invalid_args_error();
        }
    } else if (entered_command == allocate_command) {
        size_t size;
        if (string_stream >> size) {
            response = new Allocate_command(size);
        } else {
            response = new Invalid_args_error();
        }
    } else if (entered_command == free_command) {
        void *address;
        if (string_stream >> address) {
            response = new Free_command(address);
        } else {
            response = new Invalid_args_error();
        }
    } else if (entered_command == print_command) {
        response = new Print_command();
    } else if (entered_command == save_command) {
        string file_path;
        if (string_stream >> file_path) {
            bool rewrite_it;
            string flag_pointer;
            string_stream >> flag_pointer;
            rewrite_it = flag_pointer == rewrite_flag;
            response = new Save_command(file_path, rewrite_it);
        } else {
            response = new Invalid_args_error();
        }
    } else if (entered_command == open_command) {
        string file_path;
        if (string_stream >> file_path) {
            response = new Open_command(file_path);
        } else {
            response = new Invalid_args_error();
        }
    } else if (entered_command == init_command) {
        size_t degree;
        if (!(string_stream >> degree)) {
            degree = default_space_size;
        }
        response = new Init_command(degree);
    } else if (entered_command == help_command) {
        response = new Help_command;
    } else if (entered_command == read_command) {
        string file_path;
        if (string_stream >> file_path) {
            response = new Read_command(file_path);
        } else {
            response = new Invalid_args_error();
        }
    } else if (entered_command == exit_command) {
        response = new Exit_command();
    } else {
        response = new Unknown_command_error();
    }
    entered_command.clear();
    return response;
}