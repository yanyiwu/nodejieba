#ifndef LIMONP_LOCAL_VECTOR_HPP
#define LIMONP_LOCAL_VECTOR_HPP

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

namespace Limonp
{
    using namespace std;
    /*
     * LocalVector<T> : T must be primitive type (char , int, size_t), if T is struct or class, LocalVector<T> may be dangerous..
     * LocalVector<T> is simple and not well-tested. 
     */
    const size_t LOCAL_VECTOR_BUFFER_SIZE = 16;
    template <class T>
        class LocalVector
        {
            public:
                typedef const T* const_iterator ;
                typedef T value_type;
                typedef size_t size_type;
            private:
                T _buffer[LOCAL_VECTOR_BUFFER_SIZE];
                T * _ptr;
                size_t _size;
                size_t _capacity;
            public:
                LocalVector()
                {
                    _init();
                };
                LocalVector(const LocalVector<T>& vec)
                {
                    _init();
                    *this = vec;
                }
                LocalVector(const_iterator  begin, const_iterator end) // TODO: make it faster
                {
                    _init();
                    while(begin != end)
                    {
                        push_back(*begin++);
                    }
                }
                LocalVector(size_t size, const T& t) // TODO: make it faster
                {
                    _init();
                    while(size--)
                    {
                        push_back(t);
                    }
                }
                ~LocalVector()
                {
                    if(_ptr != _buffer)
                    {
                        free(_ptr);
                    }
                };
            public:
                LocalVector<T>& operator = (const LocalVector<T>& vec)
                {
                    clear();
                    _size = vec.size();
                    _capacity = vec.capacity();
                    if(vec._buffer == vec._ptr)
                    {
                        memcpy(_buffer, vec._buffer, sizeof(T) * _size);
                        _ptr = _buffer;
                    }
                    else
                    {
                        _ptr = (T*) malloc(vec.capacity() * sizeof(T));
                        assert(_ptr);
                        memcpy(_ptr, vec._ptr, vec.size() * sizeof(T));
                    }
                    return *this;
                }
            private:
                void _init()
                {
                    _ptr = _buffer;
                    _size = 0;
                    _capacity = LOCAL_VECTOR_BUFFER_SIZE;
                }
            public:
                T& operator [] (size_t i) 
                {
                    return _ptr[i];
                }
                const T& operator [] (size_t i) const
                {
                    return _ptr[i];
                }
                void push_back(const T& t)
                {
                    if(_size == _capacity)
                    {
                        assert(_capacity);
                        reserve(_capacity * 2);
                    }
                    _ptr[_size ++ ] = t;
                }
                void reserve(size_t size) 
                {
                    if(size <= _capacity)
                    {
                        return;
                    }
                    T * next =  (T*)malloc(sizeof(T) * size);
                    assert(next);
                    T * old = _ptr;
                    _ptr = next;
                    memcpy(_ptr, old, sizeof(T) * _capacity);
                    _capacity = size;
                    if(old != _buffer)
                    {
                        free(old);
                    }
                }
                bool empty() const
                {
                    return 0 == size();
                }
                size_t size() const
                {
                    return _size;
                }
                size_t capacity() const
                {
                    return _capacity;
                }
                const_iterator begin() const
                {
                    return _ptr;
                }
                const_iterator end() const
                {
                    return _ptr + _size;
                }
                void clear()
                {
                    if(_ptr != _buffer)
                    {
                        free(_ptr);
                    }
                    _init();
                }
        };

    template <class T>
        ostream & operator << (ostream& os, const LocalVector<T>& vec)
        {
            if(vec.empty())
            {
                return os << "[]";
            }
            os<<"[\""<<vec[0];
            for(size_t i = 1; i < vec.size(); i++)
            {
                os<<"\", \""<<vec[i];
            }
            os<<"\"]";
            return os;
        }

}

#endif
