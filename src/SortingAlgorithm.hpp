#pragma once

#include <iostream>
#include <vector>

namespace SortLibrary {

template<typename T>
concept Sortable = requires(T& t) {
    {t < t} -> std::convertible_to<bool>;
};

// BUBBLESORT 
template<Sortable T>
void BubbleSort(std::vector<T>& v)
{
    const unsigned int n = v.size();

    for(unsigned int i = 0; i < n; i++)
    {
        for(unsigned int j = 1; j < n - i; j++)
        {
            if(v[j] < v[j-1])
            {
                // swap 
                T tmp = v[j];
                v[j] = v[j-1];
                v[j-1] = tmp;
            }
        }
    }
}


// TOHEAP - funzione ausiliaria che trasforma un albero in heap 
template<Sortable T>
void ToHeap(std::vector<T>& v, const unsigned int n, unsigned int i)
{
    unsigned int largest = i;
    unsigned int left = 2 * i + 1;
    unsigned int right = 2 * i + 2;

    if(left < n && v[left] > v[largest])
        largest = left;

    if(right < n && v[right] > v[largest])
        largest = right;

    if(largest != i)
    {
        // swap 
        T tmp = v[i];
        v[i] = v[largest];
        v[largest] = tmp;

        ToHeap(v, n, largest); //lo rifaccio per il nuovo sottoalbero
    }
}

// HEAPSORT principale
template<Sortable T>
void HeapSort(std::vector<T>& v)
{
    const unsigned int n = v.size();

    // Costruisco un heap (parto da n/2 -1 perchè gli elementi dopo non hanno figli) 
    for(int i = n / 2 - 1; i >= 0; i--)
        ToHeap(v, n, i);

    // Estraggo gli elementi uno alla volta
    for(int i = n - 1; i > 0; i--)
    {
        // sposto la radice (max) alla fine
        T tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;

        // ricostruisco l'heap sul vettore ridotto
        ToHeap(v, i, 0);
    }
}

}

