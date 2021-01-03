//
// Created by Valar on 12/29/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_ALLOCATOR_H
#define SDL2_OPENGL_VULKAN_ENGINE_ALLOCATOR_H

#include <utils/types.h>
#include <cstdalign>
#include <new>
#include <functional>
#include <cassert>

using namespace EngineTypes;

class Allocator {
public:
    static constexpr u8 DEFAULT_ALIGNMENT = 4;

    explicit Allocator(size_t size);
    virtual ~Allocator();

    virtual void* allocate(size_t size, u8 alignment = DEFAULT_ALIGNMENT) = 0;
    virtual void deallocate(void* p) = 0;

    [[nodiscard]] size_t get_size() const;
    [[nodiscard]] size_t get_used_memory() const;
    [[nodiscard]] size_t get_number_of_allocations() const;

protected:
    size_t m_size;
    size_t m_used_memory;
    size_t m_number_of_allocations;
};

namespace allocator {
    template<class T, class... Args>
    T* allocate_new(Allocator& allocator, Args&&... args);

    template<class T>
    void deallocate_delete(Allocator& allocator, T* object);

    template<class T>
    T* allocate_array(Allocator& allocator, size_t length);

    template<class T>
    T* allocate_array_no_construct(Allocator& allocator, size_t length);

    template<class T>
    void deallocate_array(Allocator& allocator, T* array);

    template<class T>
    void deallocate_array_no_destruct(Allocator& allocator, T* array);
}

#include "Allocator.inl"

#endif //SDL2_OPENGL_VULKAN_ENGINE_ALLOCATOR_H
