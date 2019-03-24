#ifndef ARBRALS_H
#define ARBRALS_H

#define DIMVECTMAX 32767

using namespace std;
// STRUCTURI FOLOSITE SI FUNCTII AUXILIARE



// L.
// reprezentarea cu liste liniare a arborilor binari
template  < typename tip >
struct nodAB{
    tip info;
    nodAB *st, *dr;
};



// L.
// Arbore oarecare
template  < typename tip >
struct nodAO{
    tip info;
    short numarFii;
    nodAO* fii[DIMVECTMAX]={NULL};
};

// L.
// Arbore Oarecare Null
template  < typename tip >
nodAO< tip >* AONull()
{
    return NULL;
}

// A.
// Functie pentru verificare daca areborele oarecare este NULL
template < typename tip >
bool esteAONull(nodAO< tip >* root)
{
    return root == NULL;
}

// L.
// crearea unui nou nod AO
template < typename tip >
nodAO< tip >* makeNewNodAO(tip info,short numarFii = 0)
{
    nodAO< tip > *nod;
    nod = new nodAO< tip >;
    nod->info = info;
    nod->numarFii = numarFii;
    for(short i = 0;i<numarFii;i++)
        nod->fii[i] = NULL;
    return nod;
}


// A.
// functie de adaugare a unui nod intr-un arbore binar oarecare
template < typename tip >
void addToAO(nodAO< tip >*& tata, nodAO< tip >*& fiu, tip info, short numarDescendentiFiu = 0)
{
    if( !esteAONull(tata) ){
            short contor=0;
            while( tata->fii[contor] ) contor++;
            if( numarDescendentiFiu ){
                fiu=makeNewNodAO(info,numarDescendentiFiu);
                tata->fii[contor]=fiu;
            }
            else{
                  fiu=makeNewNodAO(info);
                  tata->fii[contor]=fiu;
                  tata->numarFii++;
                }
    }
}



// L.
// reprezentarea ca vector a arborilor binari
template  < typename tip >
struct vectorAB{
    // numar de la >0 pentru arbore existent
    // 0 pentru arbore vid
    short limitaVector;
    // elemente de la vect[0] la vect[limitaVector-1]
    tip *elemente;
    bool *exista;
};



// L.
// reprezentarea unui heap
template  < typename tip >
struct heapAB{
    // numar de la >0 pentru arbore existent
    // 0 pentru arbore vid
    short limitaHeap;
    // elemente de la vect[0] la vect[limitaVector-1]
    tip *elemente;
    bool (*prioritate)(tip stanga, tip dreapta);
};



// L.
// Coada
template  < typename tip >
struct coadaAB{
    short primulElement, ultimulElement;
    tip *elemente;
};

// L.
// Functie ce returneaza o coada null
template < typename tip >
coadaAB< tip > coadaABNull()
{
    coadaAB< tip > coada;
    coada.primulElement = 0;
    coada.ultimulElement = 0;
    coada.elemente = new tip[DIMVECTMAX];
    return coada;
}



// L.
// Functie ce interschimba doua variabile
template < typename tip >
void interschimba(tip &x, tip &y)
{
    tip aux = x;
    x = y;
    y = aux;
}

#endif // ARBRALS_H



