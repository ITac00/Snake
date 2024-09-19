#include <iostream>
#include "bib.h"
#include <exception>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

Game::Game(int x,int y):x(x),y(y){
    if(x<5||y<5)
        throw logic_error("Blad");
    s=new snake(x,y);
    p=new pilka(x,y,s);
    Mapa();
}
Game::~Game(){
        delete s;
        delete p;
    }

void Game::Mapa(){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {0,0};
    SetConsoleCursorPosition(hStdout,position);

    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            if(i==0||j==0||j==x-1||i==y-1)
                cout<<"*";
            else
                if(s->Sprawdz(i,j))
                    cout<<"O";
                else
                    if(j==p->getx()&&i==p->gety())
                        cout<<"#";
                    else
                        cout<<" ";
        }
        cout<<endl;
    }
    cout<<"\n\nPunkty: "<<s->getl()-2;
}
void Game::Start(){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible=false;
    SetConsoleCursorInfo(out,&cursorInfo);

    while(!s->Kolizja(x,y)){
        Mapa();
        this_thread::sleep_for(std::chrono::milliseconds(100)); //ZMIANA PREDKOSCI WYMAGA CZYSZCZENIA BUFORU Z SMIECI

        if(_kbhit()){
            char z = _getch();
            s->ZmianaKierunku(z);
        }
        czyZjedzone();

        if(s->getl()>=(x-2)*(y-2))
            break;
    }
    if(s->getl()>=(x-2)*(y-2))
        cout<<"\n\nVICTORY\n\n";
    else
        cout<<"\n\nGAME OVER\n\n";
    this_thread::sleep_for(std::chrono::milliseconds(1200));
}

Game::czyZjedzone(){
    if(s->Compare(p->getx(),p->gety(),0)){
        s->Wydluz(p->getx(),p->gety());
        p->Wyznacz(x,y);
    }
    else
        s->Porusz();
}
Game::snake::Wydluz(int x, int y){
    l++;
    block *tn=new block[l];
    tn[l-1].setwsp(tab[l-2].getx(),tab[l-2].gety());
    this->Porusz();
    for(int i=0;i<l-1;i++)
        tn[i].setwsp(tab[i].getx(),tab[i].gety());
    delete [] tab;
    this->tab=tn;
}

Game::pilka::pilka(int x, int y, snake *s){
    this->s=s;
    Wyznacz(x,y);
}
Game::pilka::Wyznacz(int x, int y){
    srand(time(0));
    do{
    this->x=rand()%(x-2)+1;
    this->y=rand()%(y-2)+1;
    }while(czyWaz());
}
bool Game::pilka::czyWaz(){
                    for(int i=0;i<s->getl();i++)
                        if(s->Compare(this->x, this->y, i))
                            return true;
                    return false;
                }

Game::snake::Kolizja(int x, int y){
                 if(tab[0].getx()==0||tab[0].getx()==x-1||tab[0].gety()==0||tab[0].gety()==y-1)
                    return true;
                 for(int i=1;i<l;i++)
                    if(tab[0].getx()==tab[i].getx()&&tab[0].gety()==tab[i].gety())
                        return true;
                 return false;
             }

Game::snake::ZmianaKierunku(char z){
    if(z=='w'||z=='s'||z=='d'||z=='a'){
            switch(kierunek){
                case 'w':
                case 's':
                    if(z=='a')
                        kierunek='a';
                    if(z=='d')
                        kierunek='d';
                    break;
                case 'a':
                case 'd':
                    if(z=='w')
                        kierunek='w';
                    if(z=='s')
                        kierunek='s';
                    break;
            }
    }
}

Game::snake::Porusz(){
                for(int i=l-1;i>0;i--)
                            tab[i].setwsp(tab[i-1].getx(),tab[i-1].gety());
                 switch(kierunek){
                    case 'w':
                        tab[0].setwsp(tab[0].getx(),tab[0].gety()-1);
                        break;
                    case 's':
                        tab[0].setwsp(tab[0].getx(),tab[0].gety()+1);
                        break;
                    case 'd':
                        tab[0].setwsp(tab[0].getx()+1,tab[0].gety());
                        break;
                    case 'a':
                        tab[0].setwsp(tab[0].getx()-1,tab[0].gety());
                 }
}

Game::snake::snake(int x, int y){
                kierunek='w';
                l=2;
                tab=new block[l];
                tab[0].setwsp(x/2,y/2);
                tab[1].setwsp(x/2,y/2-1);
            }
bool Game::snake::Sprawdz(int i, int j){
                for(int k=0;k<l;k++)
                    if(tab[k].getx()==j&&tab[k].gety()==i)
                        return true;
                return false;
            }
Game::snake::~snake(){
                delete [] tab;
            }
bool Game::snake::Compare(int x, int y, int i){
                if(tab[i].getx()==x&&tab[i].gety()==y)
                    return true;
                return false;
             }
