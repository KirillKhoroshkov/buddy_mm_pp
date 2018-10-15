#include "buddy_mm.h"

size_t Buddy_mm::calculate_power_of_two(size_t degree) {
    size_t rez = 1;
    for (int i = 0; i < degree; i++) {
        rez *= 2;
    }
    return rez;
}

size_t Buddy_mm::ceil_to_multiple(size_t size, size_t max_align) {
    if ((size % max_align) == 0) {
        return size;
    } else {
        size_t rez = size / max_align;
        rez += 1;
        return rez * max_align;
    }
}

size_t Buddy_mm::get_size_by_index(size_t index, size_t size) {
    while (index > 0) {
        size /= 2;
        index--;
    }
    return size;
}

void Buddy_mm::split_block(size_t from, size_t to) {
    size_t current_index = from;
    while (current_index < to) {
        void *current_place = (*this).avail_blocks[current_index];
        (*this).avail_blocks[current_index] = (*this).avail_blocks[current_index]->next_block;
        auto *right = (Block_header*) ((uintptr_t)current_place + get_size_by_index(current_index + 1, (*this).size_of_space));
        right->next_block = (*this).avail_blocks[current_index + 1];
        auto *left = (Block_header*) current_place;
        left->next_block = right;
        (*this).avail_blocks[current_index + 1] = left;
        current_index++;
    }
}

void *Buddy_mm::alloc_block(size_t index) {
    size_t current_index = index;
    while (this->avail_blocks[current_index] == nullptr) {
        if (current_index == 0) {
            return nullptr;
        } else {
            current_index--;
        }
    }
    Block_header *appropriate_block;
    if (current_index != index) {
        split_block(current_index, index);
    }
    appropriate_block = this->avail_blocks[index];
    this->avail_blocks[index] = this->avail_blocks[index]->next_block;
    return appropriate_block;
}

void *Buddy_mm::get_buddy_address(void *address, size_t size, void *start_address) {
    void *relative_address = (void *) ((uintptr_t)address - (uintptr_t)start_address);
    bool is_buddy_on_right = (bool) ((((size_t)relative_address + size) / size) % 2);
    if (is_buddy_on_right) {
        return (void*)((uintptr_t)address + size);
    } else {
        return (void*)((uintptr_t)address - size);
    }
}

void Buddy_mm::merge_first_with_buddy(size_t block_size) {
    if (block_size == 0) {
        return;
    }
    Block_header *first_block = this->avail_blocks[block_size];
    size_t size = get_size_by_index(block_size, this->size_of_space);
    void *buddy_address = get_buddy_address(first_block, size, this->space);
    Block_header *current_address = first_block->next_block;
    while (current_address != nullptr) {
        if (current_address == buddy_address) {
            Block_header *prev = current_address->previous_block;
            prev->next_block = current_address->next_block;
            Block_header *next = current_address->next_block;
            if (next != nullptr) {
                next->previous_block = prev;
            }
            this->avail_blocks[block_size] = first_block->next_block;
            if (this->avail_blocks[block_size] != nullptr) {
                this->avail_blocks[block_size]->previous_block = nullptr;
            }
            Block_header *new_block;
            if (first_block < current_address) {
                new_block = first_block;
            } else {
                new_block = current_address;
            }
            new_block->next_block = this->avail_blocks[block_size - 1];
            if (this->avail_blocks[block_size - 1] != nullptr) {
                this->avail_blocks[block_size - 1]->previous_block = new_block;
            }
            this->avail_blocks[block_size - 1] = new_block;
            merge_first_with_buddy(block_size - 1);
            return;
        } else {
            current_address = current_address->next_block;
        }
    }
}

Buddy_mm::Buddy_mm(size_t degree) {
    size_t size_of_space = calculate_power_of_two(degree);
    size_t max_align = alignof(max_align_t);
    size_t min_size_of_block = ceil_to_multiple(sizeof(Block_header), max_align);
    if (size_of_space < min_size_of_block) {
        throw 1;
    }
    void *space = malloc(size_of_space);
    if (space == nullptr) {
        throw 1;
    }
    Block_header **avail_blocks;
    size_t current_size = size_of_space;
    size_t number_of_lists_of_available = 0;
    while (current_size >= min_size_of_block) {
        number_of_lists_of_available += 1;
        current_size /= 2;
    }
    avail_blocks = (Block_header**) malloc(sizeof(Block_header*) * number_of_lists_of_available);
    if (avail_blocks == nullptr) {
        throw 1;
    }
    for (int i = 1; i < number_of_lists_of_available; i++) {
        avail_blocks[i] = nullptr;
    }
    auto *first_block = (Block_header *)(space);
    first_block->previous_block = nullptr;
    first_block->next_block = nullptr;
    first_block->size = 0;
    avail_blocks[0] = first_block;
    this->space = space;
    this->header_and_align_size = min_size_of_block;
    this->size_of_space = size_of_space;
    this->avail_blocks = avail_blocks;
}

Buddy_mm::~Buddy_mm() {
    free (this->space);
}

void *Buddy_mm::get_start_address() {
    return this->space;
}

void *Buddy_mm::buddy_malloc(size_t required_size) {
    size_t max_align = alignof(max_align_t);
    size_t align_size = ceil_to_multiple(required_size, max_align);
    size_t needed_size = ceil_to_multiple(sizeof(size_t), max_align) + align_size;
    size_t appropriate_size = this->size_of_space;
    if (needed_size > appropriate_size) {
        return nullptr;
    }
    size_t index = 0;
    while (true) {
        if (!((appropriate_size >= (this->header_and_align_size)) && (appropriate_size >= needed_size))) {
            index--;
            break;
        }
        index++;
        appropriate_size /= 2;
    }
    void *appropriate_place = alloc_block(index);
    if (appropriate_place == nullptr) {
        return nullptr;
    } else {
        *((size_t*) appropriate_place) = index;
        return (void*) ((uintptr_t) appropriate_place + ceil_to_multiple(sizeof(size_t), max_align));
    }
}

void Buddy_mm::buddy_free(void *ptr) {
    size_t max_align = alignof(max_align_t);
    size_t header_size = ceil_to_multiple(sizeof(size_t), max_align);
    void *start_of_block = (void*) ((uintptr_t) ptr - header_size);
    size_t block_size = *((size_t*) start_of_block);
    auto *header = (Block_header*) start_of_block;
    header->size = 0;
    header->previous_block = nullptr;
    header->next_block = this->avail_blocks[block_size];
    if (this->avail_blocks[block_size] != nullptr) {
        this->avail_blocks[block_size]->previous_block = header;
    }
    this->avail_blocks[block_size] = header;
    merge_first_with_buddy(block_size);
}
