//
// Created by eduard.parvu on 12/25/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_POINTER_MATH_H
#define SDL2_OPENGL_VULKAN_ENGINE_POINTER_MATH_H

#include <cstdalign>
#include "utils/types.h"

using namespace EngineTypes;

namespace PointerMath {
    bool        is_aligned(const void* address, u8 alignment);

    template<class T>
    bool        is_aligned(const T* address);

    void*       align_forward(void* address, u8 alignment);
    const void* align_forward(const void* address, u8 alignment);

    void*       align_backward(void* address, u8 alignment);
    const void* align_backward(const void* address, u8 alignment);

    u8          align_forward_adjustment(const void* address, u8 alignment);
    template<typename T>
    u8			align_forward_adjustment_with_header(const void* address, u8 alignment);

    u8          align_backward_adjustment(const void* address, u8 alignment);

    void*       add(void* p, size_t x);
    const void* add(const void* p, size_t x);

    void*       subtract(void* p, size_t x);
    const void* subtract(const void* p, size_t x);
}


// Inline definitions

namespace PointerMath {
    inline bool is_aligned(const void* address, u8 alignment) {
        return align_forward_adjustment(address, alignment) == 0;
    }

    template<class T>
    inline bool is_aligned(const T* address) {
        return align_forward_adjustment(address, alignof(T)) == 0;
    }

    inline void* align_forward(void* address, u8 alignment) {
        return (void*)((reinterpret_cast<uptr>(address) + static_cast<uptr>(alignment-1)) & static_cast<uptr>(~(alignment-1)));
    }

    inline const void* align_forward(const void* address, u8 alignment) {
        return (void*)((reinterpret_cast<uptr>(address) + static_cast<uptr>(alignment-1)) & static_cast<uptr>(~(alignment-1)));
    }

    inline void* align_backward(void* address, u8 alignment) {
        return (void*)(reinterpret_cast<uptr>(address) & static_cast<uptr>(~(alignment-1)));
    }

    inline const void* align_backward(const void* address, u8 alignment) {
        return (void*)(reinterpret_cast<uptr>(address) & static_cast<uptr>(~(alignment-1)));
    }

    inline u8 align_forward_adjustment(const void* address, u8 alignment) {
        u8 adjustment = alignment - (reinterpret_cast<uptr>(address) & static_cast<uptr>(alignment-1));

        if (adjustment == alignment) {
            return 0; // already aligned
        }

        return adjustment;
    }

    template<typename T>
    inline u8 align_forward_adjustment_with_header(const void* address, u8 alignment) {
        if(alignof(T) > alignment)
            alignment = alignof(T);

        u8 adjustment = sizeof(T) + align_forward_adjustment(add(address, sizeof(T)), alignment);

        return adjustment;
    }

    inline u8 align_backward_adjustment(const void* address, u8 alignment) {
        u8 adjustment = reinterpret_cast<uptr>(address)& static_cast<uptr>(alignment - 1);

        if(adjustment == alignment)
            return 0; //already aligned

        return adjustment;
    }

    inline void* add(void* p, size_t x) {
        return (void*)(reinterpret_cast<uptr>(p)+x);
    }

    inline const void* add(const void* p, size_t x) {
        return (const void*)(reinterpret_cast<uptr>(p)+x);
    }

    inline void* subtract(void* p, size_t x) {
        return (void*)(reinterpret_cast<uptr>(p)-x);
    }

    inline const void* subtract(const void* p, size_t x) {
        return (const void*)(reinterpret_cast<uptr>(p)-x);
    }
}

#endif //SDL2_OPENGL_VULKAN_ENGINE_POINTER_MATH_H
