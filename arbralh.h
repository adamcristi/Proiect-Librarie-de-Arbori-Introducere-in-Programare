#ifndef ARBRALH_H
#define ARBRALH_H

#include "arbrals.h"

using namespace std;

//IMPLEMENTAREA HEAPULUI CU ARBORI BINARI

// L.
// Functie ce returneaza un heap null
template < typename tip >
heapAB< tip > heapABNull(bool (*prioritate)(tip stanga, tip dreapta))
{
    heapAB< tip > heap;
    heap.limitaHeap = 0;
    heap.elemente = new tip[DIMVECTMAX];
    heap.prioritate = prioritate;
    return heap;
}

//L.
// functie pentru distrugerea unui heapAB
template < typename tip >
void destroyHeap(heapAB< tip >& heap)
{
    heap.limitaHeap = 0;
    delete[] heap.elemente;
    heap.prioritate = NULL;
}

// L.
// Functie ce verifica daca un heap este null
template < typename tip >
bool esteHeapNull(heapAB< tip > heap)
{
    return heap.limitaHeap == 0;
}

// L.
// Functie ce adauga un nou element in heap
template < typename tip >
heapAB< tip > pushHeapAB(heapAB< tip >& heap, tip info)
{
    heap.elemente[heap.limitaHeap++] = info;
    short i = heap.limitaHeap-1;
    bool esteHeap = false;
    while( i && !esteHeap ){
        short tata = (i-1)/2;
        if( !(*heap.prioritate)(heap.elemente[tata],heap.elemente[i]) ){
            interschimba(heap.elemente[tata],heap.elemente[i]);
            i=tata;
        }
        else esteHeap = true;
    }
    return heap;
}

// L.
// Functie ce returneaza varful heapului
template < typename tip >
tip topHeapAB(heapAB< tip > heap)
{
    return heap.elemente[0];
}

// L.
// Functie ce elimina un element din heap
template < typename tip >
tip popHeapAB(heapAB< tip >& heap)
{
    tip top = topHeapAB(heap);
    heap.elemente[0] = heap.elemente[--heap.limitaHeap];
    short i=0,fiu;
    bool esteHeap = false;
    fiu = 2*i + 1;
    while ( fiu < heap.limitaHeap && !esteHeap)
    {
        if( fiu< heap.limitaHeap-1 && !(*heap.prioritate)(heap.elemente[fiu],heap.elemente[fiu + 1]) )
            fiu++;
        if( !(*heap.prioritate)(heap.elemente[i],heap.elemente[fiu]) ){
            interschimba(heap.elemente[i],heap.elemente[fiu]);
            i = fiu;
            fiu = 2*i + 1;
        }
        else esteHeap = true;
    }
    return top;
}
#endif // ARBRALH
