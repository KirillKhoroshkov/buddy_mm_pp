#include "errors.h"

Error::Error(int code, string message) {
    this->code = code;
    this->message = std::move(message);
}

Error::~Error() {
    message.clear();
}

Unknown_command_error::Unknown_command_error() : Error(unknown_command_error, unknown_command_error_message) {};

Invalid_args_error::Invalid_args_error() : Error(invalid_args_error, invalid_args_error_message) {};

Not_configured_error::Not_configured_error() : Error(not_configured_error, not_configured_error_message) {};

Not_enough_space_error::Not_enough_space_error(): Error(not_enough_space_error, not_enough_space_error_message) {};

Invalid_configuration_error::Invalid_configuration_error(): Error(invalid_configuration_error, invalid_configuration_error_message) {};

Out_of_memory_error::Out_of_memory_error(): Error(out_of_memory_error, out_of_memory_error_message) {};

Out_of_allocated_memory_error::Out_of_allocated_memory_error(): Error(out_of_allocated_memory_error, out_of_allocated_memory_error_message) {};

Invalid_file_path_error::Invalid_file_path_error(): Error(invalid_file_path_error, invalid_file_path_error_message) {};

Invalid_file_error::Invalid_file_error(): Error(invalid_file_error, invalid_file_error_message) {};

File_already_consist_error::File_already_consist_error(): Error(file_already_consist_error, file_already_consist_error_message) {};

Reading_while_reading_error::Reading_while_reading_error(): Error(reading_while_reading_error, reading_while_reading_error_message) {};