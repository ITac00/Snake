#ifndef biblioteka
#define biblioteka
class Game{

    int x,y;

    class snake{
        int l;
        char kierunek;
        class block{
                int x,y;
            public:
                block(int x, int y):x(x),y(y){};
                block():x(0),y(0){};
                void setwsp(int n, int m){x=n;y=m;}
                int getx(){return x;}
                int gety(){return y;}
        };
        block *tab;
        public:
             snake(int x, int y);
             bool Sprawdz(int i, int j);
             ~snake();
             Kolizja(int x, int y);
             Porusz();
             ZmianaKierunku(char z);
             int getl(){return l;}
             bool Compare(int x, int y, int i);
             Wydluz(int x, int y);
    };
    class pilka{
                int x,y;
                snake *s;
            public:
                pilka(int x, int y, snake *s);
                int getx(){return x;}
                int gety(){return y;}
                Wyznacz(int x, int y);
                bool czyWaz();
        };

    pilka *p;
    snake *s;

    public:
    czyZjedzone();
    Game(int x, int y);
    void Start();
    void Mapa();
    ~Game();
};
#endif
