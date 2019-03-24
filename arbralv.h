#ifndef ARBRALV_H
#define ARBRALV_H

#include "arbrals.h"

using namespace std;
// REPREZENTAREA CA VECTORI A ARBORILOR BINARI OARECARE

// L.
// Functie ce returneaza un arbore binar null
template < typename tip >
vectorAB< tip > vectorABNull()
{
    vectorAB< tip > arbore;
    arbore.limitaVector = 0;
    arbore.elemente = new tip[DIMVECTMAX];
    arbore.exista = new bool[DIMVECTMAX];
    arbore.exista[0] = false;
    return arbore;
}

// L.
// Functie ce distruge arborele in reprezentarea ca vectori
template < typename tip >
void destroyVectorAB(vectorAB< tip >& arbore)
{
    arbore.limitaVector = 0;
    delete[] arbore.elemente;
    delete[] arbore.exista;
}



// L.
// Functie ce verifica daca un vectorAB e null
template < typename tip >
bool esteVectorABNull(vectorAB< tip > arbore)
{
    return arbore.limitaVector == 0;
}

// L.
// Functie ce verifica daca un element este frunza
template < typename tip >
bool esteVectorABFrunza(vectorAB< tip > arbore,short pozitie)
{
    return !arbore.exista[pozitie*2+1] && !arbore.exista[pozitie*2+2];
}

// L.
// Functie ce vrifica pozitia de intrare a vectoruluiAB
template < typename tip >
bool pozitieVectorABCorecta(vectorAB< tip > arbore,short pozitie)
{
    return pozitie < arbore.limitaVector && arbore.exista[pozitie];
}



// A.
// Functie pentru a verifica daca un arbore binar este propriu
template < typename tip >
bool esteVectorABPropriu(vectorAB< tip > arbore, short pozitie)
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return false;

    if( esteVectorABFrunza(arbore,pozitie) ) return true;
    if( arbore.exista[2*pozitie+1] && arbore.exista[2*pozitie+2] ) return esteVectorABPropriu(arbore,2*pozitie+1) && esteVectorABPropriu(arbore,2*pozitie+2);
     else return false;
}

// L.
// functie ce verifica daca un arbore este complet
template < typename tip >
bool esteVectorABComplet(vectorAB< tip > arbore)
{
    if( esteVectorABNull(arbore) ) return false;

    short numarElemente = arbore.limitaVector + 1;
    while( numarElemente != 1 ){
        if ( numarElemente % 2 == 1 ) return false;
        numarElemente/=2;
    }
    for( short i=0; i<arbore.limitaVector; i++)
        if( !arbore.exista[i] ) return false;
    return true;
}

// A.
// functie ce verifica daca un arbore binar este aproape complet ( almost complete binary tree )
template < typename tip >
bool esteVectorABAproapeComplet(vectorAB< tip > arbore)
{
    if( esteVectorABNull(arbore) ) return false;

    for( short i=0; i<arbore.limitaVector; i++)
        if( !arbore.exista[i] ) return false;

    return true;

    /*short numarFrunze = numaraFrunzeVectorAB(arbore,0);
    short nrNoduriMaximUltimNivel = 1;
    while( arbore.limitaVector > nrNoduriMaximUltimNivel ){
        nrNoduriMaximUltimNivel= 2*nrNoduriMaximUltimNivel;
    }
    nrNoduriMaximUltimNivel/=2;

   //if( numarFrunze != arbore.limitaVector-nrNoduriMaximUltimNivel+1 ) return false;

    for(int i=nrNoduriMaximUltimNivel-1; i < arbore.limitaVector; ++i){
        if( !arbore.exista[i] ) return false;
    }*/


    /*short numarFrunze=0;
    coadaAB< tip > coada;
    coada=coadaABNull< tip >();

    coada.elemente[coada.primulElement]=0;
    while( coada.primulElement <= coada.ultimulElement ){
        tip pozitieCurenta=coada.elemente[coada.primulElement++];
        bool frateStang=false;
        if( arbore.exista[2*pozitieCurenta+1] ){
            if( !esteVectorABFrunza(arbore,2*pozitieCurenta+1) ) coada.elemente[++coada.ultimulElement]=2*pozitieCurenta+1;
             else{
                   if( inaltimeVectorAB(arbore)==adancimeNodVectorAB(arbore,2*pozitieCurenta+1) ){
                      if( numarFrunze%2==0 ){
                        numarFrunze++;
                        frateStang=true;
                      }
                      else return false;
                   }
                   else return false;
                 }
        }
     if( arbore.exista[2*pozitieCurenta+2] ){
        if( !esteVectorABFrunza(arbore,2*pozitieCurenta+2) ) coada.elemente[++coada.ultimulElement]=2*pozitieCurenta+2;
         else{
              if( inaltimeVectorAB(arbore)==adancimeNodVectorAB(arbore,2*pozitieCurenta+2) ){
                if( frateStang && numarFrunze%2!=0 ) numarFrunze++;
                 else return false;
              }
              else return false;
             }
     }
    }
    return true;*/
}

/*template < typename tip >
bool esteVectorABFull(vectorAB< tip > arbore, short pozitie)
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return false;

    if( esteVectorABFrunza(arbore,pozitie) ) return true;
    if( arbore.exista[2*pozitie+1] && arbore.exista[2*pozitie+2] ) return esteVectorABFull(arbore,2*pozitie+1) && esteVectorABFull(arbore,2*pozitie+2);
     else return false;
}*/

// A.
// functie care verifica daca un arbore binar este degenerat ( degenerate tree )
template < typename tip >
bool esteVectorABDegenerat(vectorAB< tip > arbore, short pozitie)
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return false;

    if( arbore.exista[2*pozitie+1] && !arbore.exista[2*pozitie+2] ) return true && esteVectorABDegenerat(arbore,2*pozitie+1);
     else if( !arbore.exista[2*pozitie+1] && arbore.exista[2*pozitie+2] ) return true && esteVectorABDegenerat(arbore,2*pozitie+2);
           else if( esteVectorABFrunza(arbore,pozitie) ) return true;
    return false;
}

// A.
// Functie pentru a verifica daca un arbore binar este echilibrat
// Echilibrat = inaltimile subarborilor fii difera cu cel mult o unitate
template < typename tip >
bool esteVectorABEchilibrat(vectorAB< tip > arbore, short pozitie)
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return true;
    if( esteVectorABFrunza(arbore,pozitie) ) return true;
    short lungimeStanga = 0, lungimeDreapta = 0;
    lungimeStanga=distantaDelaNodlaFrunzaVectorAB(arbore,2*pozitie+1);
    lungimeDreapta=distantaDelaNodlaFrunzaVectorAB(arbore,2*pozitie+2);
    if( lungimeStanga < lungimeDreapta ) interschimba(lungimeStanga,lungimeDreapta);
    return ( (lungimeStanga-lungimeDreapta) < 2) && esteVectorABEchilibrat(arbore,2*pozitie+1) && esteVectorABEchilibrat(arbore,2*pozitie+2);
}



// A.
// Functie de adaugare a unui nod
template < typename tip >
void addToVectorAB(vectorAB< tip >& arbore, short pozitie, tip info)
{
   if( !arbore.exista[pozitie] ){
        arbore.elemente[pozitie]=info;
        arbore.exista[pozitie]=true;
        if( pozitie+1 > arbore.limitaVector ) arbore.limitaVector=pozitie+1;
   }
}

// L.
// Functie pentru eliminarea unui nod
template < typename tip >
vectorAB< tip > deleteFromVectorAB(vectorAB< tip >& arbore,short pozitie)
{
    if( !pozitieVectorABCorecta(arbore,pozitie) ) return arbore;


    if( esteVectorABFrunza(arbore,pozitie) ){
        arbore.exista[pozitie] = false;
    }
    else{
        arbore.exista[arbore.limitaVector-1] = false;
        arbore.elemente[pozitie] = arbore.elemente[arbore.limitaVector-1];
    }
    while( !arbore.exista[arbore.limitaVector-1] )arbore.limitaVector--;

    /*if( arbore.exista[2*pozitie+1] && arbore.pozitie[2*pozitie+2] ) return arbore;
    if( esteVectorABFrunza(pozitie) ) arbore.exista[pozitie]=false;
     else{
          if()
         }*/

    return arbore;
}

// A.
// functie pentru eliminarea tuturor nodurilor cu aceeasi valoare care au un fiu sau niciunul
template < typename tip >
vectorAB< tip > deleteAllNodesWithSameValueVectorAB(vectorAB< tip >& arbore,short pozitie, tip info)
{
   if( esteVectorABNull(arbore) ) return arbore;
   if( !pozitieVectorABCorecta(arbore,pozitie) ) return arbore;

   if( arbore.exista[pozitie] ){
     if( arbore.elemente[pozitie] == info ) {
            deleteFromVectorAB(arbore,pozitie);
            deleteAllNodesWithSameValueVectorAB(arbore,pozitie,info);
     }
     else{
          if( arbore.exista[2*pozitie+1] ) deleteAllNodesWithSameValueVectorAB(arbore,2*pozitie+1,info);
          if( arbore.exista[2*pozitie+2] ) deleteAllNodesWithSameValueVectorAB(arbore,2*pozitie+2,info);
         }
   }
}



// Parcurgerile arborelui in RSD SRD SDR si BF
// Toate primesc si o functie de tip void viziteaza si cu parametru pentru nodul de vizitat
// care spune in ce mod sunt procesate informatiile

// A.
template < typename tip >
void parcurgeVectorABRSD(vectorAB< tip >& arbore,short pozitie,void (*viziteaza)(vectorAB< tip >& ,short ))
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return;

    (*viziteaza)(arbore,pozitie);
    parcurgeVectorABRSD(arbore,2*pozitie+1,viziteaza);
    parcurgeVectorABRSD(arbore,2*pozitie+2,viziteaza);
}

// L.
template  < typename tip >
void parcurgeVectorABSRD(vectorAB< tip >& arbore,short pozitie,void (*viziteaza)(vectorAB< tip >& ,short ))
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return;

    parcurgeVectorABSRD(arbore,pozitie*2+1,viziteaza);
    (*viziteaza)(arbore,pozitie);
    parcurgeVectorABSRD(arbore,pozitie*2+2,viziteaza);
}

// L.
template  < typename tip >
void parcurgeVectorABSDR(vectorAB< tip >& arbore,short pozitie,void (*viziteaza)(vectorAB< tip >& ,short ))
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return;

    parcurgeVectorABSDR(arbore,pozitie*2+1,viziteaza);
    parcurgeVectorABSDR(arbore,pozitie*2+2,viziteaza);
    (*viziteaza)(arbore,pozitie);
}

// A.
template < typename tip >
void parcurgeVectorABBF(vectorAB< tip >& arbore,short pozitie,void (*viziteaza)(vectorAB< tip >& ,short ))
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return;

    coadaAB < tip > coada;
    coada = coadaABNull< tip >();

    coada.elemente[coada.primulElement]=pozitie;
    while( coada.primulElement <= coada.ultimulElement ){
        tip pozitieCurenta=coada.elemente[coada.primulElement++];
        (*viziteaza)(arbore,pozitieCurenta);
        if(arbore.exista[2*pozitieCurenta+1]) coada.elemente[++coada.ultimulElement]=2*pozitieCurenta+1;
        if(arbore.exista[2*pozitieCurenta+2]) coada.elemente[++coada.ultimulElement]=2*pozitieCurenta+2;
    }
}



// A.
// Functie ce returneaza numarul de noduri dintr-un arbore binar
template  < typename tip >
short numaraNoduriVectorAB( vectorAB< tip > arbore, short pozitie )
{
    if( !arbore.exista[pozitie] ) return 0;
    if( esteVectorABFrunza(arbore,pozitie) ) return 1;
    return 1 + numaraNoduriVectorAB(arbore,2*pozitie+1) + numaraNoduriVectorAB(arbore,2*pozitie+2);
}

// A.
// Functie ce returneaza numarul de frunze dintr-un arbore binar
template  < typename tip >
short numaraFrunzeVectorAB( vectorAB< tip > arbore, short pozitie )
{
    if( !arbore.exista[pozitie] ) return 0;
    if( esteVectorABFrunza(arbore,pozitie) ) return 1;
    return numaraFrunzeVectorAB(arbore,2*pozitie+1) + numaraFrunzeVectorAB(arbore,2*pozitie+2);
}

// A.
// Functie ce returneaza numarul de noduri interne dintr-un arbore binar
template  < typename tip >
short numaraNoduriInterneVectorAB( vectorAB< tip > arbore, short pozitie )
{
   if( !arbore.exista[pozitie] || esteVectorABFrunza(arbore,pozitie) ) return 0;
   return 1 + numaraNoduriInterneVectorAB(arbore,2*pozitie+1) + numaraNoduriInterneVectorAB(arbore,2*pozitie+2);
}

// L.
// functie pentru obtinerea inaltimii unui arbore binar
// presupunem ca inaltimea arborelui null este negativa
template  < typename tip >
short inaltimeVectorAB(vectorAB< tip > arbore)
{
    if( esteVectorABNull(arbore) ) return -1;
    if( esteVectorABFrunza(arbore,0) ) return 0;
    short putere = 1, exponent = 0;
    while( arbore.limitaVector > putere ){
        putere = 2*putere;
        exponent++;
    }
    return exponent-1;
}

// A.
// functie pentru obtinerea adancimii unui nod intr-un arbore
// presupunem ca adancimea in arborele null este negativa si
// ca adancimea unui nod null este negativa si ca adancimea unui nod
// intr-un arbore in care acesta nu se afla este negativa
template  < typename tip >
short adancimeNodVectorAB(vectorAB< tip > arbore,short pozitie)
{
    short adancime = 0, putere = 2;

    if( arbore.exista[pozitie] ){
        while( putere-1 <= pozitie ){
            adancime++;
            putere = 2*putere;
        }
        return adancime;
    }
    else return -1;
}

// A.
// functie care calculeaza distanta de la un nod la cea mai indepartat fiu al sau
template < typename tip >
short distantaDelaNodlaFrunzaVectorAB(vectorAB< tip > arbore, short pozitie)
{
    if( esteVectorABNull(arbore) || !pozitieVectorABCorecta(arbore,pozitie) ) return -1;
    if( esteVectorABFrunza(arbore,pozitie) ) return 0;
    short distantaStanga = 0, distantaDreapta = 0;
    if( arbore.exista[2*pozitie+1] ) distantaStanga=1+distantaDelaNodlaFrunzaVectorAB(arbore,2*pozitie+1);
    if( arbore.exista[2*pozitie+2] ) distantaDreapta=1+distantaDelaNodlaFrunzaVectorAB(arbore,2*pozitie+2);
    if( distantaStanga > distantaDreapta ) return distantaStanga;
     else return distantaDreapta;
}



// L.
// Functie pentru echilibrat arbore
template  < typename tip >
vectorAB< tip > echilibreazaVectorAB(vectorAB< tip >& arbore)
{
    vectorAB< tip > arboreEchi = vectorABNull< tip >();
    for(short i=0; i<arbore.limitaVector; i++)
        if( arbore.exista[i] ){
            arboreEchi.exista[arboreEchi.limitaVector] = true;
            arboreEchi.elemente[arboreEchi.limitaVector++]=arbore.elemente[i];
        }
    destroyVectorAB(arbore);
    arbore = arboreEchi;
    return arboreEchi;
}



// A.
// AO -> AB
// st = fiu dr = frate
template  < typename tip >
vectorAB< tip > transformaAOinVectorAB(nodAO< tip >* rootAO)
{
    vectorAB< tip > arbore = vectorABNull< tip >();

    if( rootAO == NULL ) return arbore;

    short pozitie[DIMVECTMAX]={0};

    coadaAB< nodAO< tip >* > coada;
    coada = coadaABNull< nodAO< tip >* >();

    coada.elemente[coada.primulElement]=rootAO;
    arbore.elemente[0]=rootAO->info;
    arbore.exista[0]=true;
    arbore.limitaVector=1;
    pozitie[0]=0;

    while( coada.primulElement <= coada.ultimulElement ){

        nodAO< tip >* nodCurent=coada.elemente[coada.primulElement];
        short pozitieNodCurent=pozitie[coada.primulElement++];

        if( nodCurent->numarFii>0 && nodCurent->fii[0]!=NULL ){
            coada.elemente[++coada.ultimulElement]=nodCurent->fii[0];
            arbore.elemente[2*pozitieNodCurent+1]=nodCurent->fii[0]->info;
            arbore.exista[2*pozitieNodCurent+1]=true;
            if( 2*pozitieNodCurent+2 > arbore.limitaVector ) arbore.limitaVector=2*pozitieNodCurent+2;
            pozitie[coada.ultimulElement]=2*pozitieNodCurent+1;
        }

        pozitieNodCurent=2*pozitieNodCurent+1;
        for( int i=1; i<=nodCurent->numarFii; ++i ){
            if( nodCurent->fii[i]!=NULL ){
                coada.elemente[++coada.ultimulElement]=nodCurent->fii[i];
                arbore.elemente[2*pozitieNodCurent+2]=nodCurent->fii[i]->info;
                arbore.exista[2*pozitieNodCurent+2]=true;
                if( 2*pozitieNodCurent+3 > arbore.limitaVector ) arbore.limitaVector=2*pozitieNodCurent+3;
                pozitie[coada.ultimulElement]=2*pozitieNodCurent+2;
                pozitieNodCurent=2*pozitieNodCurent+2;
            }
        }
    }
   return arbore;
}

#endif // ARBRALV_H



