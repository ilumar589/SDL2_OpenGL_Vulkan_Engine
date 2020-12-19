//
// Created by Valar on 12/10/2020.
//

#include <cstring>
#include <cstdio>
#include "memory_allocators.h"

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

bool is_power_of_two(uintptr_t x) {
    return (x & (x-1)) == 0;
}

uintptr_t align_forward(uintptr_t ptr, size_t align) {
    uintptr_t p, a, modulo;

    assert(is_power_of_two(align));

    p = ptr;
    a = (uintptr_t)align;
    // Same as (p % a) but faster as  'a' is a power of two
    modulo = p & (a -1);

    if (modulo != 0) {
        // If 'p' address is not aligned, push the address to the next value
        // which is aligned
        p += a - modulo;
    }

    return p;
}

void *arena_alloc_align(Arena *arena, size_t size, size_t align = DEFAULT_ALIGNMENT) {
    // Align 'current_offset' forward to the specified alignment
    uintptr_t current_ptr = (uintptr_t)arena->buffer + (uintptr_t)arena->current_offset;
    uintptr_t offset = align_forward(current_ptr, align);
    offset -= (uintptr_t)arena->buffer; // Change to relative offset

    // Check to see if the backing memory has space left
    if (offset + size <= arena->buffer_length) {
        void *ptr = &arena->buffer[offset];
        arena->previous_offset = offset;
        arena->current_offset = offset + size;

        // Zero new memory by default;
        memset(ptr, 0, size);
        return ptr;
    }

    return nullptr;
}

void arena_init(Arena *arena, void *backing_buffer, size_t backing_buffer_length) {
    arena->buffer = (unsigned char *) backing_buffer;
    arena->buffer_length = backing_buffer_length;
    arena->current_offset = 0;
    arena->previous_offset = 0;
}

void arena_free(Arena *arena, void *ptr) {
    // Do nothing
}


void *arena_resize_align(Arena *arena, void *old_memory, size_t old_size, size_t new_size, size_t align = DEFAULT_ALIGNMENT) {
    auto *old_mem = (unsigned char *)old_memory;

    assert(is_power_of_two(align));

    if (old_mem == nullptr || old_size == 0) {
        return arena_alloc_align(arena, new_size, align);
    } else if (arena->buffer <= old_mem && old_mem < arena->buffer + arena->buffer_length) {
        if (arena->buffer + arena->previous_offset == old_mem) {
            arena->current_offset = arena->previous_offset + new_size;
            if (new_size > old_size) {
                // Zero the new memory by default
                memset(&arena->buffer[arena->current_offset], 0, new_size-old_size);
            }
            return old_memory;
        } else {
            void *new_memory = arena_alloc_align(arena, new_size, align);
            size_t copy_size = old_size < new_size ? old_size : new_size;
            // Copy across old memory to the new memory
            memmove(new_memory, old_memory, copy_size);
            return new_memory;
        }

    } else {
        assert(0 && "Memory is out of bounds of the buffer in this arena");
        return nullptr;
    }
}

void arena_free_all(Arena *arena) {
    arena->current_offset = 0;
    arena->previous_offset = 0;
}

Temp_Arena_Memory temp_arena_memory_begin(Arena *arena) {
    Temp_Arena_Memory temp{};
    temp.arena = arena;
    temp.previous_offset = arena->previous_offset;
    temp.current_offset = arena->current_offset;

    return temp;
}

void temp_arena_memory_end(Temp_Arena_Memory temp) {
    temp.arena->previous_offset = temp.previous_offset;
    temp.arena->current_offset = temp.current_offset;
}


void example_use_case() {
    unsigned char backing_buffer[256];
    Arena arena{};
    arena_init(&arena, backing_buffer, 256);

    for (int i = 0; i < 10; ++i) {
        int *x;
        float *f;
        char *str;

        // reset all arena offsets for each loop
        arena_free_all(&arena);

        x = static_cast<int *>(arena_alloc_align(&arena, sizeof(int)));
        f = static_cast<float *>(arena_alloc_align(&arena, sizeof(float)));
        str = static_cast<char *>(arena_alloc_align(&arena, 10));

        *x = 123;
        *f = 987;
        memmove(str, "Hellope", 8);

        printf("%p: %d\n", x, *x);
        printf("%p: %f\n", f, *f);
        printf("%p: %s\n", str, str);

        str = static_cast<char *>(arena_resize_align(&arena, str, 10, 16));
        memmove(str+7, " world!", 8);
        printf("%p: %s\n", str, str);
    }

    arena_free_all(&arena);
}

