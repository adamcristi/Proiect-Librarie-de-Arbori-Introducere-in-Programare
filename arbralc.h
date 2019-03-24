#ifndef ARBRALC_H
#define ARBRALC_H

#include "arbrals.h"
#include "arbrall.h"

using namespace std;

//IMPLEMENTAREA ARBORELUI DE CAUTARE CU ARBORI BINARI

// A.
// Functie ce returneaza un arbore binar null
template < typename tip >
nodAB< tip >* ArbBinCautareNULL()
{
    return NULL;
}

// A.
template < typename tip >
void deleteElement(nodAB < tip >*& nod)
{
    delete[] nod;
    nod=NULL;
}

// A.
// Functie ce distruge arborele
template < typename tip >
void destroyArbBinCautare(nodAB< tip >*& radacina)
{
    parcurgeABSDR(radacina,deleteElement);
}



// A.
// Functie pentru verificare daca areborele este NULL
template < typename tip >
bool esteArbBinCautareNull(nodAB< tip >* radacina)
{
    return radacina == NULL;
}


// A.
// Functie care verifica daca un arbore binar reprezentat prin structuri inlantuite este arbore binar de cautare
template < typename tip >
bool esteABArbBinCautare(nodAB< tip >* radacina, tip minim, tip maxim)
{
    if( esteArbBinCautareNull(radacina) ) return true;
    if( radacina->info < minim || radacina->info > maxim ) return false;
     else return esteABArbBinCautare(radacina->st,minim,radacina->info) && esteABArbBinCautare(radacina->dr,radacina->info,maxim);
}



// A.
// functie de adaugare a unui nod in arborele binar de cautare
template < typename tip >
void inserareElementArbBinCautare(nodAB< tip >*& radacina, tip info)
{
    if( esteArbBinCautareNull(radacina) ) radacina=makeNewNodAB(info);

    if( info < radacina->info ){
        if( !esteArbBinCautareNull(radacina->st) ) inserareElementArbBinCautare(radacina->st,info);
         else{
              nodAB< tip >* nodElement=makeNewNodAB(info);
              radacina->st=nodElement;
             }
    }
    if( info > radacina->info ){
        if( !esteArbBinCautareNull(radacina->dr) ) inserareElementArbBinCautare(radacina->dr,info);
         else{
              nodAB< tip >* nodElement=makeNewNodAB(info);
              radacina->dr=nodElement;
             }
    }
}

// A.
// Functie pentru eliminarea unui nod cu  anumita valoare
template < typename tip >
void stergereElementArbBinCautare(nodAB< tip >* tata, nodAB< tip >* nodCurent, tip info, bool laDreapta = false)
{
    if( nodCurent->info==info ){
        if( !esteArbBinCautareNull(nodCurent->st) && !esteArbBinCautareNull(nodCurent->dr) ){
            nodAB< tip >* nod=nodCurent->st;
            if( nod->dr!=NULL ){
                while( nod->dr->dr!=NULL ) nod=nod->dr;
                interschimba(nodCurent->info,nod->dr->info);
                nod->dr=NULL;
                deleteElement(nod->dr);
            }
            else{
                 if(nod->st!=NULL){
                     interschimba(nodCurent->info,nod->info);
                     nodCurent->st=nod->st;
                     deleteElement(nod);
                  }
                  else{
                       interschimba(nodCurent->info,nod->info);
                       nodCurent->st=NULL;
                       deleteElement(nod);
                      }
                }
        }
         else if( !esteArbBinCautareNull(nodCurent->st) ){
                  if( !laDreapta ) tata->st=nodCurent->st;
                   else tata->dr=nodCurent->st;
                  deleteElement(nodCurent);
              }
              else if( !esteArbBinCautareNull(nodCurent->dr) ){
                        if( !laDreapta ) tata->st=nodCurent->dr;
                         else tata->dr=nodCurent->dr;
                        deleteElement(nodCurent);
                    }
                    else{
                          if( !laDreapta ) tata->st=NULL;
                           else tata->dr=NULL;
                          deleteElement(nodCurent);
                        }
    }
    else{
         if( info < nodCurent->info ) stergereElementArbBinCautare(nodCurent,nodCurent->st,info);
          else stergereElementArbBinCautare(nodCurent,nodCurent->dr,info,true);
        }
}



// A.
// Functie de cautare a unei valori in arbore
template < typename tip >
nodAB< tip >* cautareElementArbBinCautare(nodAB< tip >* radacina, tip info)
{
    while( radacina!=NULL && radacina->info!=info ){
        if( info < radacina->info ) radacina=radacina->st;
         else radacina=radacina->dr;
    }
    return radacina;
}

// A.
// Functie de cautare a predecesorului unei valori in arbore
template < typename tip >
nodAB< tip >* determinarePredecesorElementArbBinCautare(nodAB< tip >* radacina, tip info, nodAB< tip >*& nodPredecesor)
{

    if( !esteArbBinCautareNull(radacina) ){
        if( !esteArbBinCautareNull(radacina->st) ) determinarePredecesorElementArbBinCautare(radacina->st,info,nodPredecesor);
        if( radacina->info <= info ) nodPredecesor = radacina;
        if( !esteArbBinCautareNull(radacina->dr) ) determinarePredecesorElementArbBinCautare(radacina->dr,info,nodPredecesor);
    }
}

// A.
// Functie de cautare a succesorului unei valori in arbore
template < typename tip >
nodAB< tip >* determinareSuccesorElementArbBinCautare(nodAB< tip >* radacina, tip info, nodAB< tip >*& nodSuccesor)
{
    if( !esteArbBinCautareNull(radacina) ){
        if( !esteArbBinCautareNull(radacina->dr) ) determinareSuccesorElementArbBinCautare(radacina->dr,info,nodSuccesor);
        if( info <= radacina->info ) nodSuccesor=radacina;
        if( !esteArbBinCautareNull(radacina->st) ) determinareSuccesorElementArbBinCautare(radacina->st,info,nodSuccesor);
    }
}


#endif // ARBRALC_H
