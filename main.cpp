#include <iostream>
#include <string>
#include <fstream>
#include "properties/settings.h"
#include "properties/messages.h"
#include "properties/errors.h"
#include "parser/parser.h"
#include "buddy_mm/buddy_mm.h"

using namespace::std;

int main( ) {
    cout << start_message << endl;
    string raw_text;
    ifstream file;
    bool is_reading_from_file = false;
    Info *parser_info = nullptr;
    string message;
    Buddy_mm *buddy_mm = nullptr;
    void *shift; // for the relative addresses
    while (true) {
        cout << program_name << "> ";
        if (is_reading_from_file) {
            getline(file, raw_text);
            if (file.eof()) {
                is_reading_from_file = false;
                getline(cin, raw_text);
            } else {
                cout << raw_text << endl;
            }
        } else {
            getline(cin, raw_text);
        }
        parser_info = parse(raw_text);
        if (auto *err = dynamic_cast<Error*>(parser_info)) {
            message = "";
            message += to_string(err->code);
            message += ", ";
            message += err->message;
        } else if (dynamic_cast<Exit_command*>(parser_info)) {
            break;
        } else if (dynamic_cast<Help_command*>(parser_info)) {
            message = "0, ";
            message += help_message;
        } else if (auto *init_c = dynamic_cast<Init_command*>(parser_info)) {
            size_t degree = init_c->degree;
            delete buddy_mm;
            try {
                buddy_mm = new Buddy_mm(degree);
                shift = buddy_mm->get_start_address();
                message = "0, ";
                std::stringstream ss;
                ss << hex <<(uintptr_t) shift;
                message += ss.str();
            } catch (int i) {
                Error *error = new Invalid_configuration_error();
                message = "";
                message += to_string(error->code);
                message += ", ";
                message += error->message;
                delete error;
            }
        } else if (auto alloc_c = dynamic_cast<Allocate_command*>(parser_info)) {
            size_t size = alloc_c->size;
            if (buddy_mm == nullptr) {
                Error *error = new Not_configured_error();
                message = "";
                message += to_string(error->code);
                message += ", ";
                message += error->message;
                delete error;
            } else {
                void *address = buddy_mm->buddy_malloc(size * sizeof(char));
                uintptr_t relative_address = ((uintptr_t) address - (uintptr_t) shift);
                message = "0, ";
                std::stringstream ss;
                ss << hex << relative_address;
                message += ss.str();
            }
        } else if (auto *read_c = dynamic_cast<Read_command*>(parser_info)) {
            string file_path = read_c->file_path;
            if (is_reading_from_file) {
                Error *error = new Reading_while_reading_error();
                message = "";
                message += to_string(error->code);
                message += ", ";
                message += error->message;
                delete error;
            } else {
                file = ifstream(file_path);
                if (file.good()) {
                    is_reading_from_file = true;
                    message = "0, ";
                    message += read_c->file_path;
                } else {
                    Error *error = new Invalid_file_path_error();
                    message = "";
                    message += to_string(error->code);
                    message += ", ";
                    message += error->message;
                    delete error;
                }
            }
        } else if (auto *free_c = dynamic_cast<Free_command*>(parser_info)) {
            void *relative_address = free_c->address;
            if (buddy_mm == nullptr) {
                Error *error = new Not_configured_error();
                message = "";
                message += to_string(error->code);
                message += ", ";
                message += error->message;
                delete error;
            } else {
                void *address = (void *) ((size_t) relative_address + (size_t) shift);
                buddy_mm->buddy_free(address);
                message = "0, ";
                std::stringstream ss;
                ss << hex << (uintptr_t) relative_address;
                message += ss.str();
            }
        } else if (auto *get_c = dynamic_cast<Get_command*> (parser_info)) {
            if (buddy_mm == nullptr) {
                Error *error = new Not_configured_error();
                message = "";
                message += to_string(error->code);
                message += ", ";
                message += error->message;
                delete error;
            } else {
                void *relative_address = get_c->address;
                size_t index = get_c->index;
                void *address = (void *) ((size_t) relative_address + (size_t) shift);
                char *ch = ((char *) address) + index;
                message = "0, ";
                message += *ch;
            }
        } else if (auto *set_c = dynamic_cast<Set_command*>(parser_info)) {
            if (buddy_mm == nullptr) {
                Error *error = new Not_configured_error();
                message = "";
                message += to_string(error->code);
                message += ", ";
                message += error->message;
                delete error;
            } else {
                void *relative_address = set_c->address;
                void *address = (void *) ((size_t) relative_address + (size_t) shift);
                size_t index = set_c->index;
                char new_value = set_c->new_value;
                char *ch = ((char *) address) + index;
                char old_value = *ch;
                *ch = new_value;
                message = "0, ";
                message += old_value;
            }
        }
        cout << message << endl;
        message.clear();
        raw_text.clear();
    }
    delete parser_info;
}