#ifndef ARBRALL_H
#define ARBRALL_H

#include "arbrals.h"

using namespace std;
// REPREZENTAREA CA LISTE A ARBORILOR BINARI OARECARE


// L.
// Functie ce returneaza un arbore binar null
template < typename tip >
nodAB< tip >* ABNull()
{
    return NULL;
}

// A.
template < typename tip >
void deleteNod(nodAB < tip >*& nod)
{
    delete[] nod;
    nod=NULL;
}

// A.
// Functie ce distruge arborele
template < typename tip >
void destroyAB(nodAB< tip >*& root)
{
    parcurgeABSDR(root,deleteNod);
    /*if(root->st!=NULL) destroyAB(root->st);
    if(root->dr!=NULL) destroyAB(root->dr);
    delete(root);
    root=NULL;*/
}



// L.
// Functie pentru verificare daca areborele este NULL
template < typename tip >
bool esteABNull(nodAB< tip >* root)
{
    return root == NULL;
}

// L.
// Functie pentru verificcarea daca un nod este frunza
template < typename tip >
bool esteABFrunza(nodAB< tip >* nodCurent)
{
    return esteABNull(nodCurent->st) &&  esteABNull(nodCurent->dr);
}



// L.
// Functie pentru a verifica daca un arbore binar este propriu
template < typename tip >
bool esteABPropriu(nodAB< tip >* radacina)
{
    if( esteABNull(radacina) ) return true;
    if( esteABFrunza(radacina) ) return true;
    if( !esteABNull(radacina->st) && !esteABNull(radacina->dr) )
        return esteABPropriu(radacina->st) && esteABPropriu(radacina->dr);
    return false;
}

// A.
// functie ce verifica daca un arbore este complet ( complete binary tree )
template < typename tip >
bool esteABComplet(nodAB< tip >* radacina, nodAB< tip >* nodCurent)
{
    if( !esteABNull(nodCurent) ){
        if( !esteABFrunza(nodCurent) ){
            if( !esteABNull(nodCurent->st) && !esteABNull(nodCurent->dr) ) return esteABComplet(radacina,nodCurent->st) && esteABComplet(radacina,nodCurent->dr);
             else return false;
        }
        else{
             if( inaltimeAB(radacina)==adancimeNodAB(radacina,nodCurent) ) return true;
              else return false;
            }
    }
    else return false;
}

// A.
// functie ce verifica daca un arbore binar este aproape complet ( almost complete binary tree )
template < typename tip >
bool esteABAproapeComplet(nodAB< tip >* radacina)
{
    short numarFrunze=0;

    if( !esteABNull(radacina) ){
        coadaAB< nodAB< tip >* > coada;
        coada = coadaABNull< nodAB< tip >* >();

        coada.elemente[coada.primulElement]=radacina;
        while( coada.primulElement <= coada.ultimulElement ){

            nodAB< tip >* nodCurent=coada.elemente[coada.primulElement++];
            bool frateStang=false;

            if( !esteABNull(nodCurent->st) ){
                if( !esteABFrunza(nodCurent->st) ) coada.elemente[++coada.ultimulElement]=nodCurent->st;
                 else{
                      if( inaltimeAB(radacina)==adancimeNodAB(radacina,nodCurent->st) ){
                          if( numarFrunze%2==0 ){
                                numarFrunze++;
                                frateStang=true;
                            }
                           else return false;
                       }
                       else return false;
                     }
            }

            if( !esteABNull(nodCurent->dr) ){
                if( !esteABFrunza(nodCurent->dr) ) coada.elemente[++coada.ultimulElement]=nodCurent->dr;
                 else{
                      if( inaltimeAB(radacina)==adancimeNodAB(radacina,nodCurent->dr) ){
                          if( frateStang && numarFrunze%2!=0 ) numarFrunze++;
                           else return false;
                       }
                       else return false;
                     }
            }
        }
      return true;
    }
    else return false;
}

// A.
// functie care verifica daca un arbore binar este full ( full binary tree )
/*template < typename tip >
bool esteABFull(nodAB< tip >* radacina)
{
    if( !esteABNull(radacina) ){
        if( !esteABNull(radacina->st) && !esteABNull(radacina->dr) ) return esteABFull(radacina->st) && esteABFull(radacina->dr);
         else if( esteABFrunza(radacina) ) return true;
               else return false;
    }
    else return false;
}*/

// A.
// functie care verifica daca un arbore binar este degenerat ( degenerate tree )
template < typename tip >
bool esteABDegenerat(nodAB< tip >* radacina)
{
    if( !esteABNull(radacina) ){
        if( !esteABNull(radacina->st) && esteABNull(radacina->dr) ) return true && esteABDegenerat(radacina->st);
         else if( esteABNull(radacina->st) && !esteABNull(radacina->dr) ) return true && esteABDegenerat(radacina->dr);
               else if( esteABFrunza(radacina) ) return true;
                      else return false;
    }
    else return false;
}

// L.
// Functie pentru a verifica daca un arbore binar este echilibrat
// Echilibrat = inaltimile subarborilor fii difera cu cel mult o unitate
template < typename tip >
bool esteABEchilibrat(nodAB< tip >* radacina)
{
    if( esteABNull(radacina) ) return true;
    if( esteABFrunza(radacina) ) return true;
    short hStanga, hDreapta;
    hStanga = inaltimeAB(radacina->st);
    hDreapta = inaltimeAB(radacina->dr);
    if ( hStanga < hDreapta )
        interschimba(hStanga,hDreapta);
    return ((hStanga - hDreapta) < 2) &&
        esteABEchilibrat(radacina->st) &&
        esteABEchilibrat(radacina->dr);
}



// L.
// functie pentru crearea unui nodAB cu o informatie data
// aceasta functie doar creaza un nodAB fara a-l lega de un arbore
template < typename tip >
nodAB< tip >* makeNewNodAB(tip info)
{
    nodAB< tip > *nod;
    nod = new nodAB< tip >;
    nod->info = info;
    nod->st = NULL;
    nod->dr = NULL;
    return nod;
}

// L.
// functie de adaugare a unui nod in
// reprezentarea cu liste liniare a arborilor binari
// Are nevoie de nodul tata, informatia ce trebuie adaugata si
// unde trebuie adaugata ( 0 - stanga, 1 - dreapta )
// Daca nu este specificat tipul fiului, acesta se ia ca fiind fiul stanga
// Daca pozitia este deja ocupata atunci adaugarea nu va avea loc
// Daca tata este null facem un nou arbore cu radacina in tata
template  < typename tip >
void addToAB( nodAB< tip >*& tata, tip info, bool laDreapta = false )
{
    if ( esteABNull(tata) ){
            tata = makeNewNodAB(info);
            return;
    }
    if( laDreapta ){
        if( esteABNull(tata->dr) ){
            tata->dr = makeNewNodAB(info);
        }
    }
    else{
        if( esteABNull(tata->st) ){
            tata->st = makeNewNodAB(info);
        }
    }

}

// A.
// functie pentru eliminarea unui nod care are un fiu sau niciunul
template < typename tip >
void deleteFromAB(nodAB< tip >*& radacina,nodAB< tip >*& tata, nodAB< tip >*& nodSters)
{
    if( tata==NULL && radacina==nodSters ){
        if( nodSters->st==NULL || nodSters->dr==NULL ){
            if( nodSters->st!=NULL ){
                 nodAB < tip >* nodaux=nodSters;
                 radacina=nodSters->st;
                 delete[] nodaux;
            }
            else if( nodSters->dr!=NULL ){
                     nodAB < tip >* nodaux=nodSters;
                     radacina=nodSters->dr;
                     delete[] nodaux;
                 }
                 else{
                      radacina=NULL;
                      delete[] nodSters;
                     }
        }
        else cout<<"Eliminarea nu se poate face.\n";
    }
    else if( nodSters->st==NULL || nodSters->dr==NULL ){
            if( nodSters->st!=NULL ){
                if( tata->dr==nodSters ){
                    nodAB < tip >* nodaux=nodSters;
                    tata->dr=nodSters->st;
                    delete[] nodaux;
                }
                else{
                     nodAB < tip >* nodaux=nodSters;
                     tata->st=nodSters->st;
                     delete[] nodaux;
                    }
            }
            else if( nodSters->dr!=NULL ){
                        if( tata->dr==nodSters ){
                            nodAB < tip >* nodaux=nodSters;
                            tata->dr=nodSters->dr;
                            delete[] nodaux;
                        }
                        else{
                             nodAB < tip >* nodaux=nodSters;
                             tata->st=nodSters->dr;
                             delete[] nodaux;
                            }
                 }
                else{
                    if( tata->dr==nodSters ){
                        tata->dr=NULL;
                        delete[] nodSters;
                    }
                    else{
                         tata->st=NULL;
                         delete[] nodSters;
                        }
                    }
        }
         else cout<<"Eliminarea nu se poate face.\n";
}

//A.
// functie pentru eliminarea tuturor nodurilor cu aceeasi valoare care au un fiu sau niciunul
template < typename tip >
void deleteAllNodesWithSameValueAB(nodAB< tip >*& radacina, nodAB< tip >*& tata, nodAB< tip >*& nodCurent, tip info)
{
    if( !esteABNull(nodCurent) ){
        if( nodCurent->st!=NULL ) deleteAllNodesWithSameValueAB(radacina,nodCurent,nodCurent->st,info);
        if( nodCurent->dr!=NULL ) deleteAllNodesWithSameValueAB(radacina,nodCurent,nodCurent->dr,info);
        if( nodCurent->info==info ){
            if( nodCurent->st==NULL || nodCurent->dr==NULL )
                    deleteFromAB(radacina,tata,nodCurent);
            }
            /*if(tata==NULL && radacina==nodactual){
                if( nodactual->st==NULL || nodactual->dr==NULL ){
                    if( nodactual->st!=NULL ){
                        nodAB< tip >* nodaux=nodactual;
                        radacina=nodactual->st;
                        delete[] nodaux;
                        //nodactual=NULL;
                        //nodactual=radacina;
                    }
                    else if( nodactual->dr!=NULL ){
                            nodAB< tip >* nodaux=nodactual;
                            radacina=nodactual->dr;
                            delete[] nodaux;
                            //nodactual=NULL;
                            //nodactual=radacina;
                        }
                        else{
                             radacina=NULL;
                             delete[] nodactual;
                             //nodactual=NULL;
                            }
                }
            }
            else if( nodactual->st==NULL || nodactual->dr==NULL ){
                    if( nodactual->st!=NULL ){
                        if( tata->dr==nodactual ){
                            nodAB< tip >* nodaux=nodactual;
                            tata->dr=nodactual->st;
                            delete[] nodaux;
                            //nodactual=NULL;
                            //nodactual=tata;
                        }
                        else{
                             nodAB< tip >* nodaux=nodactual;
                             tata->st=nodactual->st;
                             delete[] nodaux;
                            }
                    }
                    else if( nodactual->dr!=NULL ){
                            if( tata->dr==nodactual ){
                                nodAB< tip >* nodaux=nodactual;
                                tata->dr=nodactual->dr;
                                delete[] nodaux;
                            }
                            else{
                                 nodAB< tip >* nodaux=nodactual;
                                 tata->st=nodactual->dr;
                                 delete[] nodaux;
                                }
                        }
                        else{
                             if( tata->dr==nodactual ){
                                tata->dr=NULL;
                                delete[] nodactual;
                             }
                             else{
                                  tata->st=NULL;
                                  delete[] nodactual;
                                 }
                            }
                }
        }*/
    }
}



// Parcurgerile arborelui in RSD SRD SDR si BF
// Toate primesc si o functie de tip void viziteaza si cu parametru pentru nodul de vizitat
// care spune in ce mod sunt procesate informatiile

// L.
template  < typename tip >
void parcurgeABRSD(nodAB< tip >* &radacina,void (*viziteaza)(nodAB< tip >*&))
{
    if( !esteABNull(radacina) ){
        (*viziteaza)(radacina);
        parcurgeABRSD(radacina->st,viziteaza);
        parcurgeABRSD(radacina->dr,viziteaza);
    }
}

// A.
template  < typename tip >
void parcurgeABSRD(nodAB< tip >* &radacina,void (*viziteaza)(nodAB< tip >*&))
{
    if( !esteABNull(radacina)){
        if( !esteABNull(radacina->st) ) parcurgeABSRD(radacina->st,viziteaza);
        (*viziteaza)(radacina);
        if( !esteABNull(radacina->dr) ) parcurgeABSRD(radacina->dr,viziteaza);
    }
}

// A.
template  < typename tip >
void parcurgeABSDR(nodAB< tip >* &radacina,void (*viziteaza)(nodAB< tip >*&))
{
    if( !esteABNull(radacina) ){
        if( !esteABNull(radacina->st) ) parcurgeABSDR(radacina->st,viziteaza);
        if( !esteABNull(radacina->dr) ) parcurgeABSDR(radacina->dr,viziteaza);
        (*viziteaza)(radacina);
    }
}

// L.
template  < typename tip >
void parcurgeABBF(nodAB< tip >* &radacina,void (*viziteaza)(nodAB< tip >*&))
{
    if( esteABNull(radacina) ) return;

    coadaAB< nodAB< tip >* > coada;
    coada = coadaABNull< nodAB< tip >* >();
    coada.elemente[coada.primulElement] = radacina;
    while( coada.primulElement <= coada.ultimulElement ){
        nodAB< tip >* nodCurent = coada.elemente[coada.primulElement++];
        (*viziteaza)(nodCurent);

        if( !esteABNull(nodCurent->st) )
            coada.elemente[++coada.ultimulElement] = nodCurent->st;
        if( !esteABNull(nodCurent->dr) )
            coada.elemente[++coada.ultimulElement] = nodCurent->dr;
    }
}



// L.
// Functie ce returneaza numarul de noduri dintr-un arbore binar
template  < typename tip >
short numaraNoduriAB( nodAB< tip >* radacina )
{
    if( esteABNull(radacina) ) return 0;
    if( esteABFrunza(radacina) ) return 1;
    return 1 + numaraNoduriAB(radacina->st) + numaraNoduriAB(radacina->dr);
}

// L.
// Functie ce returneaza numarul de frunze dintr-un arbore binar
template  < typename tip >
short numaraFrunzeAB( nodAB< tip >* radacina )
{
    if( esteABNull(radacina) ) return 0;
    if( esteABFrunza(radacina) ) return 1;
    return numaraFrunzeAB(radacina->st) + numaraFrunzeAB(radacina->dr);
}

// L.
// Functie ce returneaza numarul de noduri interne dintr-un arbore binar
template  < typename tip >
short numaraNoduriInterneAB( nodAB< tip >* radacina )
{
    if( esteABNull(radacina) ) return 0;
    if( esteABFrunza(radacina) ) return 0;
    return 1 + numaraNoduriInterneAB(radacina->st) + numaraNoduriInterneAB(radacina->dr);
}

// L.
// functie pentru obtinerea inaltimii unui arbore binar
// presupunem ca inaltimea arborelui null este negativa
template  < typename tip >
short inaltimeAB(nodAB< tip >* radacina)
{
    if( esteABNull(radacina) ) return -1;
    if( esteABFrunza(radacina) ) return 0;
    short st, dr;
    st = inaltimeAB(radacina->st);
    dr = inaltimeAB(radacina->dr);
    return ( ( st > dr )? st : dr ) +1 ;
}

// L.
// functie pentru obtinerea adancimii unui nod intr-un arbore
// presupunem ca adancimea in arborele null este negativa si
// ca adancimea unui nod null este negativa si ca adancimea unui nod
// intr-un arbore in care acesta nu se afla este negativa
template  < typename tip >
short adancimeNodAB(nodAB< tip >* radacina,nodAB< tip >* nod)
{
    if( esteABNull(radacina) ) return -1;
    if( esteABNull(nod) ) return -1;

    if( radacina == nod ) return 0;
    short st = adancimeNodAB(radacina->st,nod);
    short dr = adancimeNodAB(radacina->dr,nod);
    if ( st < 0 && dr < 0 ) return -1;
    if ( st < 0 ) return dr + 1;
    if ( dr < 0 ) return st + 1;
}



// A.
// Functie pentru echilibrat arbore
template  < typename tip >
nodAB< tip >* echilibreazaAB(nodAB< tip >*& radacina)
{
    coadaAB< nodAB< tip >* > coada;
    coada = coadaABNull< nodAB< tip >* >();

    coada.elemente[coada.primulElement]=radacina;
    while( coada.primulElement <= coada.ultimulElement){
        nodAB< tip >* nodCurent=coada.elemente[coada.primulElement++];
        if( !esteABNull(nodCurent->st) ) coada.elemente[++coada.ultimulElement]=nodCurent->st;
        if( !esteABNull(nodCurent->dr) ) coada.elemente[++coada.ultimulElement]=nodCurent->dr;
    }


    nodAB< tip >* radacinaNoua=makeNewNodAB(radacina->info);
    nodAB< tip >* noduri[numaraNoduriAB(radacina)];

    noduri[0]=radacinaNoua;

    for( int i=0; i<=coada.ultimulElement/2; ++i ){
        if( 2*i+1 <= coada.ultimulElement){
            addToAB(noduri[i],coada.elemente[2*i+1]->info);
            noduri[2*i+1]=noduri[i]->st;
        }
        if( 2*i+2<=coada.ultimulElement ){
            addToAB(noduri[i],coada.elemente[2*i+2]->info,true);
            noduri[2*i+2]=noduri[i]->dr;
        }

    }
    destroyAB(radacina);
    radacina=radacinaNoua;
}



// L.
// AO -> AB
// st = fiu dr = frate
template  < typename tip >
nodAB< tip >* transformaAOinAB(nodAO< tip >* rootAO)
{
    if(rootAO == NULL) return NULL;
    nodAB< tip >* rootAB = makeNewNodAB(rootAO->info);

    if( rootAO->fii[0] != NULL && rootAO->numarFii > 0 )
        rootAB->st = transformaAOinAB(rootAO->fii[0]);

    nodAB< tip >* p = rootAB->st;
    for( short i=1; i<rootAO->numarFii; i++)
        if( rootAO->fii[i] != NULL ){
            p->dr = transformaAOinAB(rootAO->fii[i]);
            p=p->dr;
        }

    return rootAB;
}

#endif // ARBRALL_H



