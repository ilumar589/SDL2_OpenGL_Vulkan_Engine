//
// Created by Valar on 12/29/2020.
//

#include "LinearAllocator.h"

using namespace EngineTypes;

LinearAllocator::LinearAllocator(size_t size, void *start) : Allocator(size), m_start(start), m_current_position(start) {

}

LinearAllocator::~LinearAllocator() {
    m_current_position = nullptr;
}

void *LinearAllocator::allocate(size_t size, u8 alignment) {
    assert(size != 0 && alignment != 0);

    u8 adjustment = PointerMath::align_forward_adjustment(m_current_position, alignment);

    if(m_used_memory + adjustment + size > m_size)
        return nullptr;

    uptr aligned_address = (uptr)m_current_position + adjustment;

    m_current_position = (void*)(aligned_address + size);

    m_used_memory = (uptr)m_current_position - (uptr)m_start;

    m_number_of_allocations++;

    return (void*)aligned_address;
}

void LinearAllocator::deallocate(void *p) {
    assert(false && "Use clear() instead");
}

void *LinearAllocator::get_start() const {
    return m_start;
}

void *LinearAllocator::get_mark() const {
    return m_current_position;
}

void LinearAllocator::clear() {
    m_number_of_allocations = 0;
    m_used_memory = 0;
    m_current_position = m_start;
}

