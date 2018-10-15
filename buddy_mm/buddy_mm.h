#ifndef BUDDY_MM_BUDDY_MM_H

#define BUDDY_MM_BUDDY_MM_H

#include <cstdint>
#include <stdbool.h>
#include <malloc.h>
#include <memory.h>

class Block_header {
public:
    size_t size;
    Block_header *previous_block;
    Block_header *next_block;
};

class Buddy_mm {
private:
    Block_header **avail_blocks;
    void *space; // for uninit
    size_t size_of_space;
    size_t header_and_align_size;

    size_t calculate_power_of_two(size_t degree);

    size_t ceil_to_multiple(size_t size, size_t max_align);

    size_t get_size_by_index(size_t index, size_t size);

    void split_block(size_t from, size_t to);

    void *alloc_block(size_t index);

    void *get_buddy_address(void *address, size_t size, void *start_address);

    void merge_first_with_buddy(size_t block_size);

public:
    explicit Buddy_mm(size_t degree);

    ~Buddy_mm();

    void *get_start_address();

    void *buddy_malloc(size_t required_size);

    void buddy_free(void *ptr);
};

#endif //BUDDY_MM_BUDDY_MM_H