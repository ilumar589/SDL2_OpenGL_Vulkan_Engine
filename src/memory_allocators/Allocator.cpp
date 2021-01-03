//
// Created by Valar on 12/29/2020.
//

#include "Allocator.h"

Allocator::Allocator(size_t size) : m_size(size), m_used_memory(0), m_number_of_allocations(0) {
    assert(size > 0);
}

Allocator::~Allocator() {
    assert(m_number_of_allocations == 0 && m_used_memory == 0);
}

size_t Allocator::get_size() const {
    return m_size;
}

size_t Allocator::get_used_memory() const {
    return m_used_memory;
}

size_t Allocator::get_number_of_allocations() const {
    return m_number_of_allocations;
}
