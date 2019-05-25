#include <iostream>
#include <cstdint>
#include <cmath>
#include <cassert>

using namespace std;
using idx_type = uint32_t;

uint64_t generate_increase(const idx_type idx, const idx_type size) {
    return idx;
}

template <typename T, typename gen_func>
T* generate_array(const idx_type len, gen_func func) {
   T* result = new T[len];
   for (idx_type idx = 0; idx < len; ++idx) {
        result[idx] = func(idx, len);
   }
   return result;
}

template<typename T>
void print_array(T* arr, idx_type size) {
    for (idx_type idx = 0; idx < size; ++idx) {
        std::cout << arr[idx] << "\t";

    }
}

template<typename T>
void destroy_array(T* arr) {
    delete [] arr;
}

inline idx_type get_parent_idx(idx_type idx) {
    return (idx-1)/2;
};

inline idx_type get_left_child_idx(idx_type idx) {
    return idx*2 + 1;
};

inline idx_type get_right_child_idx(idx_type idx) {
    return idx*2 + 2;
};

template<typename T>
void Swap(T* arr, idx_type left, idx_type right) {
    T tmp(arr[left]);
    arr[left] = arr[right];
    arr[right] = tmp;
}

template <typename T>
void Drown(T* arr, idx_type idx, idx_type size){
    idx_type left_idx = get_left_child_idx(idx);
    idx_type right_idx = get_right_child_idx(idx);
    idx_type largest = idx;

    if (left_idx < size) {
        if (arr[left_idx] > arr[idx])
            largest = left_idx;
    }
    if (right_idx < size) {
        if (arr[right_idx] > arr[largest])
            largest = right_idx;
    }
    if (largest != idx) {
        Swap(arr, idx, largest);
        Drown(arr, largest, size);
    }
};

template<typename T>
void Bubble(T* arr, idx_type idx, idx_type size) {
    assert(idx < size);
    idx_type parent_idx = get_parent_idx(idx);
    if (0 == idx)
        return;
    if (arr[idx] > arr[parent_idx]) {
        Swap(arr, idx, parent_idx);
        Bubble(arr,parent_idx, size);
    }

}

template<typename T>
void BuildHeap(T* arr, idx_type size){
    for (idx_type idx = floor(static_cast<float>(size-1) /2); idx > 0; --idx) {
        Drown(arr, idx, size);
        //print_array(arr, size);
        //std::cout <<std::endl;
    }
    Drown(arr, 0, size);
};

template<typename T>
void Remove(T* arr, idx_type idx, idx_type size) {
    assert(idx < size);
    Swap(arr, size-1, idx);

    idx_type parent_idx = get_parent_idx(idx);
    if (arr[idx] > arr[parent_idx])
        Bubble(arr, idx, size-1);
    else
        Drown(arr, idx, size-1);
}

template<typename T>
void Heapsort(T* arr, idx_type size) {
    BuildHeap(arr, size);
    for(idx_type idx = size - 1; idx > 0; --idx){
        Swap(arr, 0, idx);
        Drown(arr, 0, idx);
    }
}



int main()
{
    idx_type array_size = 20;
    uint64_t* increase_array  = generate_array<uint64_t>(array_size, generate_increase);
    std::cout << "Before: " << std::endl;
    print_array(increase_array, array_size);
    std::cout << std::endl;

    Heapsort(increase_array, array_size);

    std::cout << "After: " << std::endl;
    print_array(increase_array, array_size);
    std::cout << std::endl;

    destroy_array(increase_array);
    return 0;
}
