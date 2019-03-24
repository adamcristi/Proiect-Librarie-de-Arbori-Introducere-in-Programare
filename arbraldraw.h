#ifndef ARBRALDRAW_H
#define ARBRALDRAW_H

#include "arbraltrans.h"

#include <cmath>
#include <cstring>
#include <graphics.h>
//#include <winbgim.h>
// Am comentat ultima biblioteca ca mie sa imi poata rula programul, altfel imi apareau erori

using namespace std;
// DESENAREA PE ECRAN A ARBORILOR BINARI

// desenare predefinita doar pentru tipurile de informatii: short, int, char, char*

// L.
//Structura ce reprezinta o casuta pe ecran
struct box{
    short top,bottom,left,right,height,width;
};



// L.
//Functii ce transforma informatia din tip-ul ei in string pentru reprezentarea grafica
char* InfoToString(int info){

    char* cInfo = new char[10];
    char lungimeNr = 0;
    if( info==0 ) cInfo[lungimeNr++] = '0';
     else{
          while(info){
            cInfo[lungimeNr++] = (char)(info%10+48);
            info/=10;
           }
         }
    cInfo[lungimeNr] = '\0';
    for(int i=0;i<lungimeNr/2;i++)
        interschimba(cInfo[i],cInfo[lungimeNr-i-1]);
    return cInfo;
}

// L.
char* InfoToString(short info){
    char* cInfo = new char[5];
    char lungimeNr = 0;
    if( info==0 ) cInfo[lungimeNr++] = '0';
     else{
          while(info){
            cInfo[lungimeNr++] = (char)(info%10+48);
            info/=10;
           }
         }
    cInfo[lungimeNr] = '\0';
    for(int i=0;i<lungimeNr/2;i++)
        interschimba(cInfo[i],cInfo[lungimeNr-i-1]);
    return cInfo;
}

// L.
char* InfoToString(char info){
    char* cInfo = new char;
    *cInfo = info;
    return cInfo;
}

// L.
char* InfoToString(char* info){
    return info;
}


// L.
//Functie ce uneste toate nodurile de pe nivelul curent si nivelul anterior
template < typename tip >
void drawLinesVectorAB(vectorAB< tip > arbore,short elementCurent,short nivel, short numarNoduri,short boxWidth,short boxHeight,short raza){
    if(nivel == 0) return;
    for(int i=0;i<numarNoduri/2;i++){
        if( arbore.exista[elementCurent-numarNoduri-numarNoduri/2+i] )
        {
            int xTata,yTata,xFiu,yFiu;
            xTata=i*boxWidth*2+boxWidth;
            yTata=(nivel-1)*boxHeight+boxHeight/2+raza;
            xFiu=(i*2)*boxWidth+boxWidth/2;
            yFiu=nivel*boxHeight+boxHeight/2-raza;
            if( arbore.exista[elementCurent-numarNoduri+2*i] ) line(xTata,yTata,xFiu,yFiu);
            xFiu=(i*2+1)*boxWidth+boxWidth/2;
            if( arbore.exista[elementCurent-numarNoduri+2*i+1] ) line(xTata,yTata,xFiu,yFiu);
        }
    }
}

// L.
//Functie ce deseneaza un nod
template < typename tip >
void drawInfoVectorAB(vectorAB< tip > arbore,short& elementCurent,box myBox,short raza,char* (*InfoToStringCustom)(tip) = 0){
    short midBoxX = (myBox.left+myBox.right)/2;
    short midBoxY = (myBox.bottom+myBox.top)/2;
    if(arbore.exista[elementCurent]){
        char* cInfo;
        if(InfoToStringCustom == 0 )cInfo = InfoToString(arbore.elemente[elementCurent]);
        else cInfo = InfoToStringCustom(arbore.elemente[elementCurent]);
        circle(midBoxX ,midBoxY, raza);
        if(textheight(cInfo)>=raza*2 || textwidth(cInfo)>=raza*2){
            cInfo[0]='B';cInfo[1]='I';cInfo[2]='G';cInfo[3]='\0';
        }
        outtextxy(midBoxX-textwidth(cInfo)/2,midBoxY-textheight(cInfo)/2,cInfo);
    }
    elementCurent++;
}

// L.
//Desenarea unui arbore pe ecran reprezentat prin vectori
//Se imparte ecranul in casute in funtie de inaltimea arborelui,
//fiecare casuta reprezand spatiul unui nod din arbore. Inaltime maxima = 5
template < typename tip >
void drawVectorAB(vectorAB< tip > arbore,char* (*InfoToStringCustom)(tip) = 0)
{
    if( esteVectorABNull(arbore) ) return;

    short WIDTH = 1520, HEIGHT = 800;
    initwindow(WIDTH,HEIGHT);

    short inaltime = 0;
    short noduriPeNivelMax = 1;

    if( !esteVectorABFrunza(arbore,0) ){
        while(arbore.limitaVector>noduriPeNivelMax){
            noduriPeNivelMax = 2*noduriPeNivelMax;
            inaltime++;
        }
        noduriPeNivelMax = noduriPeNivelMax / 2;
    }
    else inaltime++;

    if(inaltime > 6){
        char c[]={"Arborele este prea mare pentru a fi desenat."};
        outtextxy(WIDTH/2-textwidth(c)/2,HEIGHT/2-textheight(c)/2,c);
        getch();
        closegraph();
        return;
    }

    short raza = ((WIDTH/noduriPeNivelMax)/2<(HEIGHT/inaltime)/2)?(WIDTH/noduriPeNivelMax)/2:(HEIGHT/inaltime)/2;
    short noduriPeNivel = 0;
    short elementCurent=0;
    box myBox;

    myBox.height = HEIGHT / inaltime;
    myBox.width = 0;

    for(int i=0;i<inaltime;i++){
        if(noduriPeNivel == 0) noduriPeNivel = 1;
        else noduriPeNivel*=2;
        myBox.width = WIDTH /noduriPeNivel;
        myBox.top = i*myBox.height;
        myBox.bottom =(i+1)*myBox.height;
        for(int j=0;j<noduriPeNivel;j++){
            myBox.left = j*myBox.width;
            myBox.right =(j+1)*myBox.width;
            drawInfoVectorAB(arbore,elementCurent,myBox,raza,InfoToStringCustom);
        }
        drawLinesVectorAB(arbore,elementCurent,i,noduriPeNivel,myBox.width,myBox.height,raza);
    }
    getch();
    closegraph();
}



// A.
//Functie ce uneste print-o linie tatal si fiul
void drawLineAB(box myBoxTata, box myBoxFiu, short raza)
{
    int xTata=0, yTata=0, xFiu=0, yFiu=0;
    xTata=myBoxTata.left+(myBoxTata.right-myBoxTata.left)/2;
    yTata=myBoxTata.top+(myBoxTata.bottom-myBoxTata.top)/2+raza;
    xFiu=myBoxFiu.left+(myBoxFiu.right-myBoxFiu.left)/2;
    yFiu=myBoxFiu.top+(myBoxFiu.bottom-myBoxFiu.top)/2-raza;
    line(xTata,yTata,xFiu,yFiu);

}

// A.
// Functie ce deseneaza un nod
template < typename tip >
void drawInfoAB(nodAB< tip >* nodCurent, box myBox, short raza, char* (*InfoToStringCustom)(tip) = 0)
{
    short midBoxX = (myBox.left+myBox.right)/2;
    short midBoxY = (myBox.bottom+myBox.top)/2;

    if( !esteABNull(nodCurent) ){
        char* cInfo;
        if( InfoToStringCustom==0 ) cInfo=InfoToString(nodCurent->info);
         else cInfo=InfoToStringCustom(nodCurent->info);
        circle(midBoxX,midBoxY,raza);
        if( textheight(cInfo)>=raza*2 && textwidth(cInfo)>=raza*2 ){
            cInfo[0]='B';cInfo[1]='I';cInfo[2]='G';cInfo[3]='\0';
        }
        outtextxy(midBoxX-textwidth(cInfo)/2,midBoxY-textheight(cInfo)/2,cInfo);
    }
}

// A.
// Desenarea unui arbore pe ecran reprezentat prin structuri inlantuite
template < typename tip >
void drawAB(nodAB< tip >* radacina, char* (*InfoToStringCustom)(tip) = 0)
{
    if( esteABNull(radacina) ) return;

    short WIDTH = 1520, HEIGHT = 800;
    initwindow(WIDTH,HEIGHT);

    short inaltime=inaltimeAB(radacina)+1;

    if(inaltime > 6){
        char c[]={"Arborele este prea mare pentru a fi desenat."};
        outtextxy(WIDTH/2-textwidth(c)/2,HEIGHT/2-textheight(c)/2,c);
        getch();
        closegraph();
        return;
    }

    short numarNoduriPeNivelMax=1,contor=1;

    while(contor<inaltime){
        numarNoduriPeNivelMax=2*numarNoduriPeNivelMax;
        contor++;
    }

    short raza=0;
    if( WIDTH/numarNoduriPeNivelMax/2 < HEIGHT/inaltime/2 ) raza = WIDTH/numarNoduriPeNivelMax/2;
     else raza = HEIGHT/inaltime/2;

    coadaAB< nodAB< tip >* > coada;
    coada=coadaABNull< nodAB< tip >* >();
    box myBox[numaraNoduriAB(radacina)];
    short rowHeight = HEIGHT / inaltime;

    coada.elemente[0]=radacina;

    myBox[0].height = rowHeight;
    myBox[0].width = WIDTH;
    myBox[0].top = 0;
    myBox[0].bottom = rowHeight;
    myBox[0].left = 0;
    myBox[0].right = WIDTH;
    drawInfoAB(radacina,myBox[0],raza,InfoToStringCustom);

    while(coada.primulElement<=coada.ultimulElement){
        nodAB< tip >* nodCurent=coada.elemente[coada.primulElement];
        if( !esteABNull(nodCurent->st) ){
            coada.elemente[++coada.ultimulElement]=nodCurent->st;

            myBox[coada.ultimulElement].height = rowHeight;
            myBox[coada.ultimulElement].width = myBox[coada.primulElement].width/2;
            myBox[coada.ultimulElement].top = myBox[coada.primulElement].bottom;
            myBox[coada.ultimulElement].bottom = myBox[coada.primulElement].bottom + rowHeight;
            myBox[coada.ultimulElement].left = myBox[coada.primulElement].left;
            myBox[coada.ultimulElement].right = myBox[coada.primulElement].right - myBox[coada.primulElement].width/2;
            drawInfoAB(nodCurent->st,myBox[coada.ultimulElement],raza,InfoToStringCustom);
            drawLineAB(myBox[coada.primulElement],myBox[coada.ultimulElement],raza);
        }

        if( !esteABNull(nodCurent->dr) ){
            coada.elemente[++coada.ultimulElement]=nodCurent->dr;

            myBox[coada.ultimulElement].height = rowHeight;
            myBox[coada.ultimulElement].width = myBox[coada.primulElement].width/2;
            myBox[coada.ultimulElement].top = myBox[coada.primulElement].bottom;
            myBox[coada.ultimulElement].bottom = myBox[coada.primulElement].bottom + rowHeight;
            myBox[coada.ultimulElement].left = myBox[coada.primulElement].left + myBox[coada.primulElement].width/2;
            myBox[coada.ultimulElement].right = myBox[coada.primulElement].right;
            drawInfoAB(nodCurent->dr,myBox[coada.ultimulElement],raza,InfoToStringCustom);
            drawLineAB(myBox[coada.primulElement],myBox[coada.ultimulElement],raza);
        }

        coada.primulElement++;
    }

    getch();
    closegraph();
}

// A.
// Desenarea unui heap
template < typename tip >
void drawHeapAB(heapAB< tip > heap, char* (*InfoToStringCustom)(tip) = 0)
{
    vectorAB< tip > arbore =vectorABNull< tip >();
    arbore=transformaHeapInVectorAB(heap);
    drawVectorAB(arbore,InfoToStringCustom);
}

// A.
// Desenarea unui arbore binar de cautare
template < typename tip >
void drawArbBinCautare(nodAB< tip >* radacina, char* (*InfoToStringCustom)(tip) = 0)
{
    drawAB(radacina,InfoToStringCustom);
}

#endif // ARBRALDRAW
