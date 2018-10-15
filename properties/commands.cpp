#include "commands.h"

Get_command::Get_command(void *address, size_t index) {
    this->address = address;
    this->index = index;
}

Exit_command::Exit_command() = default;

Print_command::Print_command() = default;

Init_command::Init_command(size_t degree) {
    this->degree = degree;
}

Allocate_command::Allocate_command(size_t size) {
    this->size = size;
}

Reallocate_command::Reallocate_command(void *address, size_t new_size) {
    this->address = address;
    this->new_size = new_size;
}

Save_command::~Save_command() {
    file_path.clear();
}

Save_command::Save_command(string file_path, bool rewrite_it) {
    this->file_path = std::move(file_path);
    this->rewrite_it = rewrite_it;
}

Open_command::Open_command(string file_path) {
    this->file_path = std::move(file_path);
}

Open_command::~Open_command() {
    file_path.clear();
}

Help_command::Help_command() = default;

Read_command::Read_command(string file_path) {
    this->file_path = std::move(file_path);
}

Read_command::~Read_command() {
    file_path.clear();
}

Free_command::Free_command(void *address) {
    this->address = address;
}

Set_command::Set_command(void *address, size_t index, char new_value) {
    this->address = address;
    this->index = index;
    this->new_value = new_value;
}
