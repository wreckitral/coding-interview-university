#include <stdexcept>
#include <iostream>

template <typename T> class VectorClass {
    // pointer to the array in memory
    T* arr;

    // the capacity of our vector
    int capacities;

    // the number of items that we currently have
    int current;

public:
    // constructor
    VectorClass() {
        arr = new T[1];
        capacities = 1;
        current = 0;
    }

    // destructor to deallocate memory allocated by dynamic allocation
    ~VectorClass() { delete[] arr; }

    // return the number element that we have
    int size() {
        return current;
    }

    // return how much can the vector holds
    int capacity() {
        return capacities;
    }

    // check do we got anything in the vector
    bool is_empty() {
        if (current == 0) return true;

        return false;
    }

    // get item at the index
    T at(int index) {
        if(index < current) {
            return arr[index];
        }

        throw std::out_of_range("index out of range");
    }


    void push(T item) {
        if(current == capacities) {
            resize(2 * capacities);
        }

        arr[current] = item;
        current++;
    }

    void insert(int index, T item) {
        if(index > current) throw std::out_of_range("index out of range");

        if(current == capacities) {
            resize(2 * capacities);
        }

        for(int i = current; i > index; i--) {
            arr[i] = arr[i - 1];
        }

        arr[index] = item;
        current++;
    }

    void prepend(T item) {
        insert(0, item);
    }

    T pop() {
        if(current / capacities == 2) {
            resize(capacities / 2);
        }

        current--;
        return arr[current + 1];
    }

    void del(int index) {
        if(index > current) throw std::out_of_range("index out of range");

        for(int i = index; i < current - 1; i++) {
            arr[i] = arr[i + 1];
        }

        current--;
    }

    void remove(T item) {
        for(int i = 0; i < current; i++) {
            if(item == arr[i]) {
                del(i);
                i--; // recheck same index because the items are shifted left
            }
        }
    }

    T find(T item) {
        for(int i = 0; i < current; i++) {
            if(item == arr[i]) {
                return i;
            }
        }

        return -1;
    }

private:

    void resize(int new_capacity) {
        T* temp = new T[2 * capacities];

        for(int i = 0; i < current; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        capacities = new_capacity;
    }
};


int main() {
    VectorClass<int> v;

    v.push(10);
    v.push(20);
    v.push(30);
    v.push(55);

    v.insert(1, 99);

    std::cout << "size: " << v.size() << std::endl;
    std::cout << "cap: " << v.capacity() << std::endl;
    std::cout << "at(1): " << v.at(1) << std::endl;

    return 0;
}
