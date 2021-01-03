namespace allocator {
    template<class T, class... Args>
    T* allocate_new(Allocator& allocator, Args&&... args) {
        return new (allocator.allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
    }

    template<class T>
    void deallocate_delete(Allocator& allocator, T* object) {
        object->~T();
        allocator.deallocate(object);
    }

    template<class T>
    T* allocate_array(Allocator& allocator, size_t length) {
        assert(length != 0);

        u8 header_size = sizeof(size_t) / sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        //Allocate extra space to store array length in the bytes before the array
        T* p = ((T*)allocator.allocate(sizeof(T)*(length + header_size), alignof(T))) + header_size;

        *(((size_t*)p) - 1) = length;

        for(size_t i = 0; i < length; i++)
            new (&p[i]) T;

        return p;
    }

    template<class T>
    T* allocate_array_no_construct(Allocator& allocator, size_t length) {
        assert(length != 0);

        u8 header_size = sizeof(size_t) / sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        //Allocate extra space to store array length in the bytes before the array
        T* p = ((T*)allocator.allocate(sizeof(T)*(length + header_size), alignof(T))) + header_size;

        *(((size_t*)p) - 1) = length;

        return p;
    }

    template<class T>
    void deallocate_array(Allocator& allocator, T* array) {
        assert(array != nullptr);

        size_t length = *(((size_t*)array) - 1);

        //should be reverse order
        for(size_t i = 0; i < length; i++)
            array[i].~T();

        //Calculate how much extra memory was allocated to store the length before the array
        u8 header_size = sizeof(size_t) / sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        allocator.deallocate(array - header_size);
    }

    template<class T>
    void deallocate_array_no_destruct(Allocator& allocator, T* array) {
        assert(array != nullptr);

        size_t length = *(((size_t*)array) - 1);

        //Calculate how much extra memory was allocated to store the length before the array
        u8 header_size = sizeof(size_t) / sizeof(T);

        if(sizeof(size_t) % sizeof(T) > 0)
            header_size += 1;

        allocator.deallocate(array - header_size);
    }
}