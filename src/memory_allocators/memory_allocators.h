//
// Created by Valar on 12/10/2020.
//

/**
 * https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/
**/

#ifndef SDL2_OPENGL_VULKAN_ENGINE_MEMORY_ALLOCATORS_H
#define SDL2_OPENGL_VULKAN_ENGINE_MEMORY_ALLOCATORS_H

#include <cstdint>
#include <cassert>

bool is_power_of_two(uintptr_t x);

uintptr_t align_forward(uintptr_t ptr, size_t align);

struct Arena {
    unsigned char *buffer;
    size_t buffer_length;
    size_t previous_offset;
    size_t current_offset;
};

void arena_init(Arena *arena, void *backing_buffer, size_t backing_buffer_length);
void *arena_alloc_align(Arena *arena, size_t size, size_t align);
void *arena_resize_align(Arena *arena, void *old_memory, size_t old_size, size_t new_size, size_t align);
void arena_free(Arena *arena, void *ptr);
void arena_free_all(Arena *arena);
void example_use_case();

struct Temp_Arena_Memory {
    Arena *arena;
    size_t previous_offset;
    size_t current_offset;
};

Temp_Arena_Memory temp_arena_memory_begin(Arena *arena);
void temp_arena_memory_end(Temp_Arena_Memory temp);

#endif //SDL2_OPENGL_VULKAN_ENGINE_MEMORY_ALLOCATORS_H
