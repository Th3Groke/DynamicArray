#include <algorithm>
#include <cmath>
#ifndef SORTING_TPP
#define SORTING_TPP

#include "../inc/Sorting.h"


static const int INSERTION_SORT_THRESHOLD = 16;

template<typename T>
template<typename Iter>
void Sorting<T>::SwapValue(Iter a, Iter b) {
    if (a==b) return;

    T temp = std::move(*a);
    *a = std::move(*b);
    *b = std::move(temp);
}

template<typename T>
template<typename Iter>
void Sorting<T>::InsertionSort(Iter begin, Iter end) {
    if(begin == end) return;
    if(begin + 1 == end)return;

    for (Iter i = begin + 1; i != end; ++i) {
        auto key = std::move(*i);
        Iter j = i;

        while (j !=begin && *(j-1) > key) {
            *(j) = std::move(*(j-1));
            --j;
        }
        *j = std::move(key);
    }
}

template<typename T>
template<typename Iter>
void Sorting<T>::Heapify(Iter begin, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && begin[left] > begin[largest]) {
        largest = left;
    }
    if (right < n && begin[right] > begin[largest]) {
        largest = right;
    }
    if (largest != i) {
        SwapValue(&begin[i], &begin[largest]);
        Heapify(begin, n, largest);
    }
}

template<typename T>
template<typename Iter>
void Sorting<T>::HeapSort(Iter begin, Iter end) {
    int n = end - begin;
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(begin, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        SwapValue(&begin[i], &begin[0]);
        Heapify(begin, i, 0);
    }
}


template<typename T>
template<typename Iter>
Iter Sorting<T>::MedianOf3(Iter low, Iter high) {
    Iter mid = low + (high - low) / 2;

    if (*mid < *low) {
        SwapValue(mid, low);
    }
    if (*high < *low) {
        SwapValue(high, low);
    }
    if (*high < *mid) {
        SwapValue(high, mid);
    }
    return mid;
}

template<typename T>
template<typename Iter>
Iter Sorting<T>::Partition(Iter low, Iter high) {
    Iter pivotPos = MedianOf3(low, high);

    SwapValue(pivotPos, high);

    auto pivot = *high;

    Iter i = low;

    for (Iter j = low; j != high; ++j) {
        if (*j < pivot) {
            SwapValue(i, j);
            i++;
        }
    }
    SwapValue(i, high);
    return i;
}

template<typename T>
template<typename Iter>
void Sorting<T>::IntroSortUtil(Iter begin, Iter end, int depthLimit) {
    long size = end - begin;
    if (size < INSERTION_SORT_THRESHOLD) {
        InsertionSort(begin, end);
        return;
    }

    if (depthLimit == 0) {
        HeapSort(begin, end);
        return;
    }

    Iter pivot = Partition(begin, end - 1);
    IntroSortUtil(begin, pivot, depthLimit - 1);
    IntroSortUtil(pivot + 1, end, depthLimit - 1);
}

template<typename T>
template<typename Iter>
void Sorting<T>::IntroSort(Iter begin, Iter end) {
    long size = end - begin;
    if (size < 2) {
        return;
    }
    int depthLimit = 2 * std::log2(size);

    IntroSortUtil(begin, end, depthLimit);
};

#endif // SORTING_TPP
