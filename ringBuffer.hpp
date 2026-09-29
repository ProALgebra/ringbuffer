#pragma once
#include <cstddef>
#include <array>
#include <stdexcept>
#include <utility>
/*
    Задача сделать ring Buffer
    У него должен быть 
    size возвращает текущее количество элементов
    head указывает на первый элемент
    tail указывает куда мы хотим вставить
    front это head
    push(T) выдаёт ошибку если буфер полный 
    pop() удаляет элемент удаляет
*/

template<class T, std::size_t N> requires (N > 0)
class RingBuffer{
    public:
        RingBuffer() = default;
        void push(T value){
            if(_size == N){
                throw std::overflow_error("buffer is full");
            }
            buffer[tail] = std::move(value);
            plusTail();
            _size++;
        }
        
        bool empty() const{
            return _size == 0;
        }

        bool full() const{
            return _size == N;
        }

        T& front() {
            if(_size == 0){
                throw std::logic_error("buffer is empty");
            }
            return buffer[head];
        }

        const T& front() const{
            if(_size == 0){
                throw std::logic_error("buffer is empty");
            }
            return buffer[head];
        }

        void pop(){
            if(_size == 0){
                throw std::logic_error("buffer is empty");
            }
            _size--;
            plusHead();
        }

        std::size_t size() const {
            return _size;
        }

    private:

        void plusTail(){
            tail = tail + 1;
            tail %= N;
        }

        void plusHead(){
            head++;
            head %= N;
        }
        std::array<T,N> buffer;
        std::size_t head = 0;
        std::size_t tail = 0;
        std::size_t _size = 0;
};


