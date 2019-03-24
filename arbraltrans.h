#ifndef ARBRALTRANS_H
#define ARBRALTRANS_H

#include "arbrals.h"
#include "arbrall.h"
#include "arbralv.h"
#include "arbralh.h"
#include "arbralc.h"

using namespace std;

// TRECERI DE LA O REPREZENTARE LA ALTA

// L.
// Functie de trecere de la implementarea cu liste la cea cu vector
template  < typename tip >
vectorAB< tip > transformaABInVectorAB( nodAB< tip >* radacina )
{
    vectorAB< tip > arbore = vectorABNull< tip >();

    if( esteABNull(radacina) ) return arbore;
    short elementeNenule = 0;

    coadaAB< nodAB< tip >* > coada;
    coada = coadaABNull< nodAB< tip >* >();

    coada.elemente[coada.primulElement] = radacina;
    elementeNenule++;
    while( coada.primulElement <= coada.ultimulElement && elementeNenule > 0){
        nodAB< tip >* nodCurent = coada.elemente[coada.primulElement++];
        if( esteABNull(nodCurent) ) arbore.exista[arbore.limitaVector++] = false;
        else{
            elementeNenule--;
            arbore.exista[arbore.limitaVector] = true;
            arbore.elemente[arbore.limitaVector++] = nodCurent->info;
        }
        if(!esteABNull(nodCurent) ){
            elementeNenule = elementeNenule + (int)!esteABNull(nodCurent->st) +(int)!esteABNull(nodCurent->dr);
            coada.elemente[++coada.ultimulElement] = nodCurent->st;
            coada.elemente[++coada.ultimulElement] = nodCurent->dr;
        }
        else{
            coada.elemente[++coada.ultimulElement] = NULL;
            coada.elemente[++coada.ultimulElement] = NULL;
        }
    }
    while( !arbore.exista[arbore.limitaVector-1] )arbore.limitaVector--;
    return arbore;
}



// A.
// Functie de trecere de la vectori la implementarea cu liste
template  < typename tip >
nodAB< tip >* transformaVectorABInAB( vectorAB< tip > arbore )
{
    nodAB< tip > *radacina,*tata[arbore.limitaVector];

    if( esteVectorABNull(arbore) ) return radacina;

    coadaAB< short > pozitie=coadaABNull< short >();

    radacina=makeNewNodAB(arbore.elemente[0]);
    tata[0]=radacina;
    pozitie.elemente[0]=0;
    while( pozitie.primulElement <= pozitie.ultimulElement ){
          short pozitieNodCurent=pozitie.elemente[pozitie.primulElement++];
          if( arbore.exista[2*pozitieNodCurent+1] ){
            addToAB(tata[pozitieNodCurent],arbore.elemente[2*pozitieNodCurent+1]);
            tata[2*pozitieNodCurent+1]=tata[pozitieNodCurent]->st;
            pozitie.elemente[++pozitie.ultimulElement]=2*pozitieNodCurent+1;
          }
          if( arbore.exista[2*pozitieNodCurent+2] ){
            addToAB(tata[pozitieNodCurent],arbore.elemente[2*pozitieNodCurent+2],true);
            tata[2*pozitieNodCurent+2]=tata[pozitieNodCurent]->dr;
            pozitie.elemente[++pozitie.ultimulElement]=2*pozitieNodCurent+2;
          }
        }
    return radacina;
}



// A.
// functie pentru obtinerea vectorului de tati
template < typename tip >
vectorAB< short > obtineVectorTatiAB(nodAB< tip >* radacina)
{
    vectorAB< short > vectorTati = vectorABNull< short >();
    short nrElemente=0;

    if( esteABNull(radacina) ) return vectorTati;

    coadaAB< nodAB< tip >* > coada;
    coada = coadaABNull< nodAB< tip >* >();

    vectorTati.limitaVector=1;
    vectorTati.elemente[nrElemente++]=-1;
    coada.elemente[coada.primulElement]=radacina;
    while( coada.primulElement <= coada.ultimulElement){
        nodAB< tip >* nodCurent=coada.elemente[coada.primulElement++];
        if( !esteABNull(nodCurent->st) ){
            vectorTati.limitaVector+=1;
            vectorTati.elemente[nrElemente++]=coada.primulElement-1;
            coada.elemente[++coada.ultimulElement]=nodCurent->st;
        }
        if( !esteABNull(nodCurent->dr) ){
            vectorTati.limitaVector+=1;
            vectorTati.elemente[nrElemente++]=coada.primulElement-1;
            coada.elemente[++coada.ultimulElement]=nodCurent->dr;
        }
    }
    return vectorTati;
}

// L.
// functie pentru obtinerea vectorului de tati
template < typename tip >
vectorAB< short > obtineVectorTatiVectorAB(vectorAB< tip > arbore)
{
    vectorAB< short > vectorTati = vectorABNull< short >();

    if( esteVectorABNull(arbore) ) return vectorTati;

    short eticheta[arbore.limitaVector], nrElemente = 0;

    vectorTati.limitaVector = 1;
    vectorTati.elemente[0] = -1;
    eticheta[0] = nrElemente++;

    for( short i = 1; i < arbore.limitaVector; i++){
        if( arbore.exista[i] ){
            eticheta[i] = nrElemente++;
            vectorTati.elemente[vectorTati.limitaVector++] = eticheta[(i-1)/2];
        }
    }

    return vectorTati;
}


// L.
// Functie de trecere de la heapuri la vectori
template  < typename tip >
vectorAB< tip > transformaHeapInVectorAB( heapAB< tip > heap )
{
    if( esteHeapNull(heap) ) return vectorABNull< tip >();

    vectorAB< tip > arbore = vectorABNull< tip >();

    arbore.limitaVector = heap.limitaHeap;
    for(short i = 0; i< heap.limitaHeap;i++){
        arbore.elemente[i] = heap.elemente[i];
        arbore.exista[i] = true;
    }
    destroyHeap(heap);

    return arbore;
}

// A.
// Functie de trecere de la heapuri la implementarea cu liste
template  < typename tip >
nodAB< tip >* transformaHeapInAB( heapAB< tip > heap )
{
    if( esteHeapNull(heap) ) return NULL;

    nodAB< tip >* radacina=makeNewNodAB(heap.elemente[0]);
    nodAB< tip >*tata[heap.limitaHeap];

    tata[0]=radacina;
    for( short i=1; i<heap.limitaHeap; ++i ){
        if( i%2!=0 ){
            addToAB(tata[(i-1)/2],heap.elemente[i]);
            tata[i]=tata[(i-1)/2]->st;
        }
        else{
             addToAB(tata[(i-1)/2],heap.elemente[i],true);
             tata[i]=tata[(i-1)/2]->dr;
            }
    }
   destroyHeap(heap);

   return radacina;
}

#endif // ARBRALTRANS
