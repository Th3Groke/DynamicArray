#ifndef _SORTING_H
#define _SORTING_H

template<typename T>
class Sorting {
    private:
        template<typename Iter>
        using ValueType = typename std::iterator_traits<Iter>::value_type;

        template<typename Iter>
        static void SwapValue(Iter a, Iter b);

        template<typename Iter>
        static void InsertionSort(Iter begin, Iter end);

        template<typename Iter>
        static void Heapify(Iter begin, int n, int i);

        template<typename Iter>
        static void HeapSort(Iter begin, Iter end);

        template<typename Iter>
        static Iter MedianOf3(Iter low, Iter high);

        template<typename Iter>
        static Iter Partition(Iter low, Iter high);

        template<typename Iter>
        static void IntroSortUtil(Iter begin, Iter end, int depthLimit);

    public:
        template<typename Iter>
        static void IntroSort(Iter begin, Iter end);
};

#include "../src/Sorting.tpp"
#endif //_SORTING_H
