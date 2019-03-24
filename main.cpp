#include <iostream>
#include <fstream>
#include "arbral.h"

using namespace std;
ifstream fin("date.in");

nodAB<int> *vect[101],*rad;

//nodAO<int> *vect[101],*rad;

//vectorAB<char> tablou;

//heapAB<char> tablouHeap;

void afisareAB(nodAB<int> *&p)
    {
     cout<<p->info<<" ";
    }

void afisareVectorAB(vectorAB<int>& vect, short poz)
    {
     cout<<vect.elemente[poz]<<" ";
    }

bool prioritateHeap(int a,int b)
{
    /*if(a>b) return true;
     else return false;*/
     return a > b ?  true : false ;
}

bool prioritateHeapForChar(char a,char b)
{
    /*if(a>b) return true;
     else return false;*/
     return (int) a > (int) b ?  true : false ;
}

char* InfoToStringForChar(char caracter)
{
    char* cInfo = new char[2];
    cInfo[0] = caracter;
    cInfo[1] = '\0';
    return cInfo;
}

int main()
{
    //Arbori binari reprezentati prin liste

    int n=0,fs=0,fd=0;
    int val[101]={0};
    fin>>n;
    for(int i=1;i<=n;++i) fin>>val[i];
    rad=makeNewNodAB(val[1]);
    vect[1]=rad;
    int pred=1;
    while(fin>>fs>>fd)
        {
         if(fs)
            {
             addToAB(vect[pred],val[fs]);
             vect[fs]=vect[pred]->st;
            }
         if(fd)
            {
             addToAB(vect[pred],val[fd],true);
             vect[fd]=vect[pred]->dr;
            }
         pred++;
        }
    drawAB(rad);

    /*destroyAB(rad);
    cout<<esteABNull(rad);*/

    //cout<<esteABNull(rad)<<" "<<esteABFrunza(vect[12])<<"\n";

    /*cout<<esteABPropriu(rad)<<"\n";
    cout<<esteABComplet(rad,rad)<<"\n";
    cout<<esteABAproapeComplet(rad)<<"\n";
    cout<<esteABDegenerat(rad)<<"\n";
    cout<<esteABEchilibrat(rad)<<"\n";*/

    /*deleteFromAB(rad,vect[1],vect[2]);
    deleteFromAB(rad,vect[2],vect[4]);
    deleteFromAB(rad,vect[5],vect[9]);
    deleteFromAB(rad,vect[6],vect[10]);
    deleteFromAB(rad,vect[7],vect[11]);
    if( !esteABNull(rad)) parcurgeABBF(rad,afisareAB);
     else cout<<"Arbore null";*/

    /*deleteAllNodesWithSameValueAB(rad,vect[0],vect[1],20);
    if( !esteABNull(rad)) parcurgeABBF(rad,afisareAB);
     else cout<<"Arbore null";*/

    /*parcurgeABRSD(rad,afisareAB);
    cout<<"\n"<<"\n";
    parcurgeABSRD(rad,afisareAB);
    cout<<"\n"<<"\n";
    parcurgeABSDR(rad,afisareAB);
    cout<<"\n"<<"\n";
    parcurgeABBF(rad,afisareAB);
    cout<<"\n"<<"\n";*/

    /*cout<<numaraNoduriAB(rad)<<" "<<numaraNoduriInterneAB(rad)<<" "<<numaraFrunzeAB(rad)<<"\n";
    cout<<inaltimeAB(rad)<<" "<<adancimeNodAB(rad,vect[12])<<"\n";*/

    /*if( !esteABEchilibrat(rad) ){
        cout<<"Arborele nu este echilibrat."<<"\n";
        echilibreazaAB(rad);
        parcurgeABSRD(rad,afisareAB);
    }
    else cout<<"Arbore echilibrat.";*/

    /*vectorAB< int > tablou=vectorABNull< int >();
    tablou=transformaABInVectorAB(rad);
    //parcurgeVectorABBF(tablou,0,afisareVectorAB);
    for(int i=0; i<tablou.limitaVector; ++i) //cout<<tablou.elemente[i]<<" ";
        if(tablou.exista[i]) cout<<tablou.elemente[i]<<" ";
         else cout<<-1<<" ";
    cout<<"\n";
    vectorAB< short > tata=vectorABNull< short >();
    tata=obtineVectorTatiAB(rad);
    for(int i=0;i<tata.limitaVector;++i) cout<<tata.elemente[i]<<" ";*/



    /*parcurgeABSRD(rad,afisareAB);
    cout<<"\n"<<"\n";
    echilibreazaAB(rad);
    parcurgeABSRD(rad,afisareAB);*/


    /*ex:
     5
     6 2 3 7 10
     2 3
     0 4
     5 0

     4
     6 2 7 10
     2 0
     3 4

     6
     6 2 3 20 7 10
     2 3
     4 5
     6 0

     7
     6 2 3 20 7 10 3
     2 3
     4 5
     6 0
     0 0
     0 0
     0 7

     8
     6 2 3 20 7 10 9 20
     2 3
     4 5
     6 0
     0 7
     0 0
     0 8

     6
     6 2 6 7 9 6
     2 0
     3 4
     0 5
     6 0

     10
     6 2 3 20 7 10 15 9 20 20
     2 3
     4 5
     6 7
     0 8
     0 0
     0 9

     14
     6 2 3 20 7 10 15 9 20 20 20 11 17 4
     2 3
     4 5
     6 7
     0 8
     0 9
     0 10
     11 0
     0 0
     0 12
     13 0
     14 0

     7
     6 2 3 20 7 10 15
     2 3
     4 5
     6 7

     14
     6 2 3 20 7 10 15 9 20 20 17 4 11 25
     2 3
     4 5
     6 7
     8 9
     10 11
     12 13
     14 0

     7
     6 2 3 20 7 17 4
     2 3
     4 5
     0 0
     0 0
     6 7

     7
     6 2 3 20 7 17 4
     2 0
     4 0
     5 0
     6 0
     7 0
    */

    // Arbori oarecare

    /*int n=0,val[101]={0},nrf[101]={0};
    fin>>n;
    for(int i=1;i<=n;++i) fin>>val[i];
    for(int i=1;i<=n;++i) fin>>nrf[i];
    rad=makeNewNodAO(val[1],nrf[1]);
    vect[1]=rad;
    for(int i=1;i<=n;++i)
        {
         if(nrf[i])
            {
             int f=0;
             for(int j=1;j<=nrf[i];++j)
                {
                 fin>>f;
                 addToAO(vect[i],vect[f],val[f],nrf[f]);
                }
            }
        }*/

    /*nodAB<int> *radAB=transformaAOinAB(rad);
    //parcurgeABBF(radAB,afisareAB);
    parcurgeABSRD(radAB,afisareAB);*/

    /*vectorAB< int > tablou=transformaAOinVectorAB(rad);
    //parcurgeVectorABBF(tablou,0,afisareVectorAB);
    parcurgeVectorABSRD(tablou,0,afisareVectorAB);*/

    /*ex:
    11
    15 10 14 12 8 11 22 1 2 4 6
    4 2 3 4 5
    2 6 7
    0
    3 8 9 10
    1 11
    0
    0
    0
    0
    0
    0
    */

    //Arbori binari reprezentati prin tablouri

    /*tablou=vectorABNull< char >();
    char val[101]={'\0'};
    int n,fs=0,fd=0;
    fin>>n;
    for( int i=1;i<=n;++i) fin>>val[i];
    addToVectorAB(tablou,0,val[1]);
    int poz=0;
    while(fin>>fs>>fd)
        {
         if(fs) addToVectorAB(tablou,2*poz+1,val[fs]);
         if(fd) addToVectorAB(tablou,2*poz+2,val[fd]);
         poz++;
        }*/
   //drawVectorAB(tablou,InfoToStringForChar);

    /*destroyVectorAB(tablou);
    cout<<esteVectorABNull(tablou);*/

    //cout<<esteVectorABNull(tablou)<<" "<<esteVectorABFrunza(tablou,22)<<" "<<pozitieVectorABCorecta(tablou,12);

    /*cout<<esteVectorABPropriu(tablou,0)<<"\n";
    cout<<esteVectorABComplet(tablou)<<"\n";
    cout<<esteVectorABAproapeComplet(tablou)<<"\n";
    cout<<esteVectorABDegenerat(tablou,0)<<"\n";
    cout<<esteVectorABEchilibrat(tablou,0)<<"\n";*/

    /*deleteFromVectorAB(tablou,3);
    parcurgeVectorABBF(tablou,0,afisareVectorAB);*/

    /*deleteAllNodesWithSameValueVectorAB(tablou,0,20);
    parcurgeVectorABBF(tablou,0,afisareVectorAB);*/

    /*parcurgeVectorABRSD(tablou,0,afisareVectorAB);
    cout<<"\n"<<"\n";
    parcurgeVectorABSRD(tablou,0,afisareVectorAB);
    cout<<"\n"<<"\n";
    parcurgeVectorABSDR(tablou,0,afisareVectorAB);
    cout<<"\n"<<"\n";
    parcurgeVectorABBF(tablou,0,afisareVectorAB);
    cout<<"\n"<<"\n";*/

    /*cout<<numaraNoduriVectorAB(tablou,0)<<" "<<numaraNoduriInterneVectorAB(tablou,0)<<" "<<numaraFrunzeVectorAB(tablou,0)<<"\n";
    cout<<inaltimeVectorAB(tablou)<<" "<<adancimeNodVectorAB(tablou,2)<<" "<<distantaDelaNodlaFrunzaVectorAB(tablou,2);*/

    /*tablou=echilibreazaVectorAB(tablou);
    parcurgeVectorABSRD(tablou,0,afisareVectorAB);*/

    /*nodAB< int >* rad=transformaVectorABInAB(tablou);
    parcurgeABSRD(rad,afisareAB);
    cout<<"\n";
    vectorAB< short > tata=vectorABNull< short >();
    tata=obtineVectorTatiVectorAB(tablou);
    for(int i=0;i<tata.limitaVector;++i) cout<<tata.elemente[i]<<" ";*/

    /* ex:
     14
     6 2 3 20 7 10 15 9 20 20 20 11 17 4
     2 3
     4 5
     6 7
     0 8
     0 9
     0 10
     11 0
     0 0
     0 0
     0 0
     0 12
     0 0
     13 0
     14 0

     7
     6 2 3 20 7 17 4
     2 3
     4 5
     0 0
     0 0
     6 7

     6
     6 2 3 20 7 17
     2 3
     4 0
     5 6

     8
     6 2 3 20 7 9 20 20
     2 3
     4 5
     0 0
     6 7
     8 0

     10
     6 2 3 20 7 10 15 9 20 20
     2 3
     4 5
     6 7
     8 9
     10 0

     4
     6 2 3 20
     2 0
     0 3
     0 0
     0 0
     4 0

     5
     6 2 3 20 7
     2 3
     4 5
    */

    // Heap-uri

    /*tablouHeap = heapABNull(prioritateHeapForChar);
    int n=0;
    char x;
    fin>>n;
    for(int i=1;i<=n;++i)
        {
         fin>>x;
         tablouHeap=pushHeapAB(tablouHeap,x);
        }*/
    //drawHeapAB(tablouHeap,InfoToStringForChar);

    //for(int i=0;i<tablouHeap.limitaHeap;++i) cout<<tablouHeap.elemente[i]<<" ";

    /*destroyHeap(tablouHeap);
    cout<<esteHeapNull(tablouHeap);*/

    //cout<<topHeapAB(tablouHeap);

    /*popHeapAB(tablouHeap);
    for(int i=0;i<tablouHeap.limitaHeap;++i) cout<<tablouHeap.elemente[i]<<" ";*/

    /*vectorAB< int > tablou=transformaHeapInVectorAB(tablouHeap);
    parcurgeVectorABSRD(tablou,0,afisareVectorAB);*/

    /*nodAB< int >* rad=transformaHeapInAB(tablouHeap);
    parcurgeABSRD(rad,afisareAB);*/

    /* ex:
    11
    15 10 14 12 8 11 22 1 2 4 6
    */

    // Arbori Binari de Cautare

    /*nodAB<int>* rad=ArbBinCautareNULL< int >(), *elementNull=ArbBinCautareNULL< int >();
    int n=0;
    fin>>n;
    int x=0;
    for(int i=1;i<=n;i++)
        {
         fin>>x;
         inserareElementArbBinCautare(rad,x);
        }*/

    //drawArbBinCautare(rad);

    /*destroyArbBinCautare(rad);
    cout<<esteArbBinCautareNull(rad);*/

    //cout<<esteABArbBinCautare(rad,0,10001);

     /*stergereElementArbBinCautare(elementNull,rad,35);
     parcurgeABSRD(rad,afisareAB);
     drawArbBinCautare(rad);*/

     /*nodAB< int >* nod = cautareElementArbBinCautare(rad,37);
     if( nod!=NULL ) cout<<nod->info;
      else cout<<-1;*/

     /*nodAB< int >* nod = ArbBinCautareNULL< int >();
     determinarePredecesorElementArbBinCautare(rad,18,nod);
      if( nod!=NULL ) cout<<nod->info;
      else cout<<"Nu exista predecesor.";*/

    /*nodAB< int >* nod = ArbBinCautareNULL< int >();
    determinareSuccesorElementArbBinCautare(rad,51,nod);
    if( nod!=NULL ) cout<<nod->info;
      else cout<<"Nu exista succesor.";*/

     /* ex:
     11
     15 10 14 12 8 11 22 1 2 4 6

     8
     20 0 40 15 30 50 25 35

     10
     20 0 40 15 30 50 25 35 33 37
     */
    return 0;
}
