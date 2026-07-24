#pragma once
#include <vector>
#include <algorithm>
#include <assert.h>
namespace bit
{
    template<class T>
    class vector
    {
    public:
        // Vector的迭代器是一个原生指针
        typedef T* iterator;
        typedef const T* const_iterator;
        iterator begin() { return _start; }
        iterator end() { return _finish; }
        const_iterator cbegin() { return (const_iterator)_start; }
        const_iterator cend() const { return (const_iterator)_finish; }
        // construct and destroy
        vector()
        {
            _start = nullptr;
            _finish = nullptr;
            _endOfStorage = nullptr;
        }
        vector(int n, const T& value = T())
        {
            size_t Oldstorage = _endOfStorage - _start;
            iterator tmp = new T[n];
            std::fill(tmp, tmp + n, value);
            delete[] _start;
            _start = tmp;
            _finish = tmp + n;
            _endOfStorage = _start + Oldstorage;
        }
        template<class InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            assert(last - first > 0);
            size_t Oldstorage = _endOfStorage - _start;
            iterator tmp = new T[last - first];
            for (int n=0;n<last-first;n++)
            {
                *(tmp + n) = *(first + n);
            }
            _start = tmp;
            _finish = tmp + n;
            _endOfStorage = _start + Oldstorage;
        }
        vector(const vector<T>& v)
        {
            vector<T> tmp(v.begin(), v.end());
            swap(*this, tmp);
            delete[] tmp;
        }
        vector<T>& operator= (vector<T> v);
        ~vector()
        {
            delete[] _start;
            _start = nullptr;
            _finish = nullptr;
            _endOfStorage = nullptr;
        }
            // capacity
        size_t size() const { return _finish - _start; }
        size_t capacity() const { return _endOfStorage - _start; }
        void reserve(size_t n)
        {
            if (n > _endOfStorage - _start) _endOfStorage = _start + n;
        }
        void resize(size_t n, const T& value = T());
            ///////////////access///////////////////////////////
        T& operator[](size_t pos) 
        {
            assert(pos < _finish - _start);
            return *(_start + pos); 
        }
        const T& operator[](size_t pos)const 
        {
            assert(pos < _finish - _start);
            return *(_start + pos); 
        }
            //////////////modify/////////////////////////////
        void push_back(const T& x);
        void pop_back()
        {
            assert(_finish - _start >= 0);
            _finish--;
        }
        void swap(vector<T>& v)
        {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_endOfStorage, v._endOfStorage);
        }
        iterator insert(iterator pos, const T& x)
        {
            if (_finish == _endOfStorage)
            {
                iterator tmp = new T[2 * (_finish - _start)];
                memcpy(tmp, _start, _finish - _start);
                size_t OldStorage = _finish - _start;
                _start = tmp;
                _finish = tmp + OldStorage;
                _endOfStorage= tmp + 2 * OldStorage
            }
            _finish++;
            for (tmp = _finish; tmp > pos; tmp--)
            {
                *tmp = *(tmp - 1);
            }
            *tmp = x;
        }
        iterator erase(iterator pos);
    private:
        iterator _start; // 指向数据块的开始
        iterator _finish; // 指向有效数据的尾
        iterator _endOfStorage; // 指向存储容量的尾
    };

}