#include "pch.h"
#include "map.h"
using namespace System;
using namespace std;
int main()
{
    srand(time(NULL));
    createMap();
    bool camb = true; //Variable para la animacion del diparo
    bool CambioVida = true;
    bool Disparo = false;
    int malos, BalaVar, numBalas, temporizador,randomizador = 0;
    int mainJx, mainJy; //coordenadas el jugador
    mainJx = 20; mainJy = 1;
    char tecla;

    Bala* BalasActuales = new Bala[10000];
    int vida = 10;

    Jugador* main = new Jugador(226, 178, 47, 92, 186, vida, mainJx, mainJy);
    main->DibujaJugador();

    Jugador* Malo1 = new Jugador(225, 206, 47, 92, 202, 4, 100, 4);
    Malo1->DibujaJugador();

    Jugador* Malo2 = new Jugador(225, 206, 47, 92, 202, 4, 100, 43);
    Malo2->DibujaJugador();

    Jugador* MalosActuales = new Jugador[100];

    MalosActuales[0] = *Malo1;
    MalosActuales[1] = *Malo2;
    while (1)
    {
        randomizador = rand() % 30;

        if (_kbhit())
        {
            tecla = _getch();
            if (tecla == DERECHA && (mapa[main->Jy][main->Jx + 1] == 1 && mapa[main->Jy + 2][main->Jx + 1] == 1 && mapa[main->Jy + 1][main->Jx + 2] == 1) && main->Jx + 1 != 119)
            {
                main->vida--;
                CambioVida = true;
                //Declaro la direccion del personaje
                orientacion = Este;
                //borrar
                main->BorraJugador();
                //mover
                main->Jx++;
                //dibujar
                main->Bderecho = 92;
                main->Bizquierdo = 60;
                if (VarWalk == 1) {
                    main->Patas = 188;
                    VarWalk = 0;
                }
                else {
                    main->Patas = 186;
                    VarWalk = 1;
                }
                main->DibujaJugador();
            }
            else if (tecla == ARRIBA && (mapa[main->Jy - 1][main->Jx] == 1 && mapa[main->Jy][main->Jx + 1] == 1 && mapa[main->Jy][main->Jx - 1] == 1)) {
                //Declaro la direccion del personaje
                orientacion = Norte;
                //borrar
                main->BorraJugador();
                //mover
                main->Jy--;
                //dibujar
                main->Bderecho = 92;
                main->Bizquierdo = 47;
                main->Patas = 186;
                main->DibujaJugador();
            }
            else if (tecla == ABAJO && mapa[main->Jy + 3][main->Jx] == 1 && mapa[main->Jy + 2][main->Jx + 1] == 1 && mapa[main->Jy + 2][main->Jx - 1] == 1) {
                //Declaro la direccion del personaje
                orientacion = Sur;
                main->BorraJugador();
                //mover
                main->Jy++;
                //dibujar
                main->Bderecho = 92;
                main->Bizquierdo = 47;
                main->Patas = 186;
                main->DibujaJugador();
            }
            else if (tecla == IZQUIERDA && mapa[main->Jy][main->Jx - 1] == 1 && mapa[main->Jy + 2][main->Jx - 1] == 1 && mapa[main->Jy + 1][main->Jx - 2] == 1 && (main->Jx - 1 != 0)) {
                //Declaro la direccion del personaje
                orientacion = Oeste;
                //borrar
                main->BorraJugador();
                //mover
                main->Jx--;
                //dibujar
                main->Bizquierdo = 47;
                main->Bderecho = 62;
                if (VarWalk == 1) {
                    main->Patas = 200;
                    VarWalk = 0;
                }
                else {
                    main->Patas = 186;
                    VarWalk = 1;
                }
                main->DibujaJugador();
            }
            if (tecla == ESPACIO) {
                switch (orientacion) {
                case Norte: animacionDisparo(*main, 196, 196, 238, 238, &camb); break;
                case Este: animacionDisparo(*main, 32, 185, 32, 205, &camb); break;
                case Sur: animacionDisparo(*main, 179, 179, 124, 124, &camb); break;
                case Oeste: animacionDisparo(*main, 204, 32, 205, 32, &camb);
                }
                Disparo = true;
            }//Disparo

        }
        if (CambioVida) {
            Pintar(1);
            Console::SetCursorPosition(1, 2);
            for (int i = 0; i < main->vida; i++) {
                cout << " ";
            }
            Console::SetCursorPosition(1, 2);
            for (int i = 0; i < main->vida; i++) {
                Console::ForegroundColor = ConsoleColor::Red;
                cout << (char)220;
            }
            for (int i = 0; i < 6 - main->vida; i++) {
                cout << " ";

            }
            CambioVida = false;
        }

        if (Disparo) {
            if (orientacion == Oeste) {
                BalasActuales[BalaVar] = Bala(main->Jx - 2, main->Jy + 1, Oeste);
            }
            else if (orientacion == Este) {
                BalasActuales[BalaVar] = Bala(main->Jx + 2, main->Jy + 1, Este);
            }
            else if (orientacion == Norte) {
                BalasActuales[BalaVar] = Bala(main->Jx, main->Jy - 1, Norte);
            }
            else if (orientacion == Sur) {
                BalasActuales[BalaVar] = Bala(main->Jx, main->Jy + 3, Sur);
            }
            Disparo = false;
            BalaVar++;
            numBalas++;
        }
        for (int i = 0; i < numBalas; i++) {//For del recorrido de las balas
            BalasActuales[i].DibujaBala();

            //Revisar si la bala choca con algo
            for (int bala = 0; bala < 2; bala++) {
                if (BalasActuales[i].x == MalosActuales[bala].Jx && (BalasActuales[i].y == MalosActuales[bala].Jy || BalasActuales[i].y == (MalosActuales[bala].Jy + 1) || BalasActuales[i].y == (MalosActuales[bala].Jy + 2))) {
                    MalosActuales[bala].cabeza = 32;
                }
            }
        }
        if (temporizador == 2) {

            for (int m = 0; m < 2; m++) {
                MalosActuales[m].BorraJugador();

                if (mapa[MalosActuales[m].Jy - 1][MalosActuales[m].Jx] != 1) {
                    MalosActuales[m].dy *= -1;
                }

                if (mapa[MalosActuales[m].Jy + 3][MalosActuales[m].Jx] != 1) {
                    MalosActuales[m].dy *= -1;
                }

                MalosActuales[m].Jy += MalosActuales[m].dy;

                MalosActuales[m].DibujaJugador();
            }
            temporizador = 0;
        }
        if (randomizador == 22) {

            BalasActuales[BalaVar] = Bala(MalosActuales[0].Jx - 2, MalosActuales[0].Jy, Oeste);
            BalaVar++;
            numBalas++;
        }
        if (randomizador == 23) {

            BalasActuales[BalaVar] = Bala(MalosActuales[1].Jx - 2, MalosActuales[1].Jy, Oeste);
            BalaVar++;
            numBalas++;
        }

        temporizador++;
        _sleep(20);
    }

    system("pause");
    return 0;
}