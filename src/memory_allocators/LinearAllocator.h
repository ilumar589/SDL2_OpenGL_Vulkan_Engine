//
// Created by Valar on 12/29/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_LINEARALLOCATOR_H
#define SDL2_OPENGL_VULKAN_ENGINE_LINEARALLOCATOR_H


#include "Allocator.h"
#include <utils/types.h>
#include <utils/pointer_math.h>

class LinearAllocator : Allocator {
public:
    LinearAllocator(size_t size, void *start);
    LinearAllocator(const LinearAllocator&) = delete;
    LinearAllocator& operator=(const LinearAllocator&) = delete;
    ~LinearAllocator() override;

    void* allocate(size_t size, u8 alignment) final;
    void deallocate(void *p) final;
    void clear();

    [[nodiscard]] void* get_start() const;
    [[nodiscard]] void* get_mark() const;

private:

    void* m_start;
    void* m_current_position;
};


#endif //SDL2_OPENGL_VULKAN_ENGINE_LINEARALLOCATOR_H
