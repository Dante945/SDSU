// STUDENT ORGANIC WAGYU CODE
// Author: Dante Viscuso
// San Diego State University
// CS210/CS496: Data Structures
//
// File: CircularArray.h
// Defines the CircularArray collection class.

#define VERSION_CIRARRAY 0.1

// STUDENT CODE
#ifndef PROG1_CIRCULARARRAY_H
#define PROG1_CIRCULARARRAY_H

#include "Queue.h"
#include "List.h"
#include <cmath>  

namespace sdsu {
    template<typename T>
    class CircularArray : public sdsu::Queue<T>, public sdsu::List<T> {

    private:
        int curSize;
        int curCapacity;
        int head = -1;
        int tail = -1;
        T* storage;

        bool isFull() {
            return curSize == curCapacity;
        }

        void doubleSize() {
            T* temp;
            temp = new T[curCapacity * 2];
            int i = 0;
            int j = head;

            do {
                temp[i++] = storage[j];
                j = (j + 1) % curCapacity;
            } while (j != head);

            head = 0;
            tail = curCapacity - 1;
            delete[] storage;
            storage = temp;
            curCapacity = curCapacity * 2;
        }
       
        void checkCapacity() {
            if (curSize < (curCapacity * 0.25)) {
                shrink();
            }
       }

        void shrink() {
            T* temp;
            temp = new T[curCapacity * 0.5];
            int i = 0;
            int j = head;
            int t = tail;

            do {
                temp[i++] = storage[j];
                j = (j + 1) % curCapacity;
            } while (j != t);

            head = 0;
            tail = curSize - 1;
            delete[] storage;
            storage = temp;
            curCapacity = curCapacity * 0.5;
        }

    public:
        
        CircularArray() : curSize(0) {
            //initialize a default capacity storage array on the heap
            storage = new T[10];
            curCapacity = 10;
        }

        CircularArray(const CircularArray<T>& other) : CircularArray() {}
        ~CircularArray() override {
            delete[] storage;
        }

        void clear() override {
            delete[] storage;
            storage = new T[curCapacity];
            curSize = 0;
            curCapacity = 10;
            head = -1;
            tail = -1; 
        }

        T dequeue() override {
            return removeFirst();
        }

        bool enqueue(T t) override {
            return addLast(t);
        }

        bool isEmpty() const override {
            return size() == 0;
        }

        T& peek() override {
            return storage[head];
        }

        bool addFirst(T t) override {
            return insert(0, t);
        }

        bool addLast(T t) override {
            return insert((curSize), t);
        }

        T& get(int idx) override {
            if (isEmpty()) 
                throw std::out_of_range("CircularArray<T>::get(idx) : index out of range.");        
            if (idx >= curSize) 
                throw std::out_of_range("CircularArray<T>::get(idx) : index out of range.");
            if (idx < 0) 
                throw std::out_of_range("CircularArray<T>::get(idx) : index out of range.");
            return storage[((idx + head) % curCapacity)];
        }

        // Inserts data at the index of the list
        // Shifts minimum amount of data as needed to make room
        bool insert(int idx, T t) override {
            if (isFull()) 
                doubleSize();
   
            else if (isEmpty()) {
                head = tail = 0;
                storage[tail] = t;
                curSize++;
                return true;
            }

            if (idx == (curSize)) {
                int newTail = (tail + 1) % curCapacity;
                storage[newTail] = t;
                tail = newTail;
                curSize++;
                return true;
            }

             if (idx == 0) {
                int newHead = head - 1;
                if (head == 0) {
                    newHead = curCapacity - 1;
                }
                storage[newHead] = t;
                head = newHead;
                curSize++;
                return true;
            }

            int modifiedIdx = ((idx + head) % curCapacity);
            int distanceFromTail = (abs(curSize - 1 - idx));
            int distanceFromHead = (abs(0 - idx));

            if (distanceFromTail < distanceFromHead) {
                int newTail = (tail + 1) % curCapacity;

                    if (tail == 0) {
                        for (int i = 0; i <= distanceFromTail; i++) {
                            storage[((curCapacity - 1) + 2 - i) % curCapacity] = storage[((curCapacity - 1) + 1 - i) % curCapacity];
                        }
                    }
                    else {
                        for (int i = 0; i <= distanceFromTail; i++) {
                            storage[newTail - i] = storage[tail - i];
                        }
                    }
                    storage[modifiedIdx] = t;
                    curSize++;
                    return true;
            }
            else {
                int newHead = head - 1;
                if (head == 0) {
                    newHead = curCapacity = 1;
                }

                    for (int i = 0; i <= distanceFromHead; i++) {
                        storage[(newHead + i) % curCapacity] = storage[(head + i) % curCapacity];
                    }
                    storage[modifiedIdx] = t;
                    head = newHead;
                    curSize++;
                    return true;
            }
            return false;
        }

        // Removes and returns data at the index of the list
        // Shifts minimum amount of data as needed to make room
        T remove(int idx) override {
            if (isEmpty()) 
                throw std::out_of_range("Queue Empty, nothing to return");

            //Uses head as a way to refrence idx for the case of the list not starting at array[0]
            int modifiedIdx = ((idx + head) % curCapacity);
            int temp = storage[modifiedIdx];
            
            if (head == tail) {
                head = tail = -1;
                curSize--;
                return temp;
            }

            if (idx == 0) {
                int newHead = (head + 1) % curCapacity;
                head = newHead;
                    curSize--;
                    return temp;
            }

            if (idx == curSize) {
                int newTail = tail - 1;
                if (tail == 0) {
                    newTail = curCapacity = 1;
                }
                    tail = newTail;
                    curSize--;
                    checkCapacity();
                    return temp;
            }
            
            int distanceFromTail = (abs(curSize - 1 - idx));
            int distanceFromHead = (abs(0 - idx));

            if (distanceFromTail < distanceFromHead) {
                int newTail = tail - 1;
                if (tail == 0) {
                    newTail = curCapacity - 1;
                }
                    for (int i = 0; i <= distanceFromTail; i++) {
                        storage[(newTail + i) % curCapacity] = storage[(newTail + i) % curCapacity];
                    }
                    tail = newTail;
                    curSize--;
                    checkCapacity();
                    return temp; 
            }
            else {
                int newHead = (head + 1) % curCapacity;
                    for (int i = 0; i <= distanceFromHead; i++) {
                        storage[newHead - i] = storage[head - i];
                    }
                    head = newHead;
                    curSize--;
                    checkCapacity();
                    return temp; 
            }
            return temp;
        }

        T removeFirst() override {
            return remove(0);
        }

        T removeLast() override {
            return remove(curSize);
        }

        void set(int idx, T value) override {
            throw std::out_of_range("CircularArray<T>::set(idx,value) : index out of range.");
            storage[((idx + head) % curCapacity)] = value;
        }

        int size() const override {
            return curSize;
        }
    };
}
#endif //PROG1_CIRCULARARRAY_H