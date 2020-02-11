// ConsoleApplication7.cpp: archivo de proyecto principal.

#include "pch.h"
// final.cpp: archivo de proyecto principal.
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "map.h"

#define DERECHA 77
#define IZQUIERDA 75
#define ABAJO 80
#define ARRIBA 72
#define ESPACIO 32

//Orientaciones para los proyectiles
#define Norte 0
#define Sur 1
#define Este 2
#define Oeste 3

using namespace System;
using namespace std;




int main()
{
	createMap();
	bool CambioVida = true;
	bool Disparo = false;
	int malos = 0;
	int mainJx, mainJy; //coordenadas el jugador
	mainJx = 40; mainJy = 1;
	char tecla;

	Bala* BalasActuales;

	BalasActuales = new Bala[10];

	Jugador* main = new Jugador(226, 178, 47, 92, 186, 6, mainJx, mainJy);
	while (1)
	{
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
				//main->Patas = 188;
				main->DibujaJugador();
				//cout << "x: " << main->Jx << "y: " << main->Jy <<" 1: "<< mapa[main->Jy + 3][main->Jx]<<" 2: " << mapa[main->Jy - 2][main->Jx + 1] <<" 3: " << mapa[main->Jy - 2][main->Jx - 1];
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
				if (orientacion == Norte) {
					main->Bizquierdo = 32;
					main->Bderecho = 32;
					main->DibujaBrazos();
					_sleep(100);
					main->Bizquierdo = 196;
					main->Bderecho = 196;
					main->DibujaBrazos();
				}
				else if (orientacion == Este) {
					main->Bizquierdo = 32;
					main->Bderecho = 32;
					main->DibujaBrazos();
					_sleep(100);
					main->Bizquierdo = 32;
					main->Bderecho = 185;
					main->DibujaBrazos();
				}
				else if (orientacion == Oeste) {
					main->Bizquierdo = 32;
					main->Bderecho = 32;
					main->DibujaBrazos();
					_sleep(100);
					main->Bizquierdo = 204;
					main->Bderecho = 32;
					main->DibujaBrazos();

					Disparo = true;
					//Disparo(&Disparo, orientacion);
				}
				else if (orientacion == Sur) {
					main->Bizquierdo = 32;
					main->Bderecho = 32;
					main->DibujaBrazos();
					_sleep(100);
					main->Bizquierdo = 179;
					main->Bderecho = 179;
					main->DibujaBrazos();
				}
			}

		}
		if (CambioVida) {
			main->Pintar();
			Console::SetCursorPosition(1, 2);
			for (int i = 0; i < main->vida; i++) {
				cout << " ";
			}
			Console::SetCursorPosition(1, 2);
			for (int i = 0; i < main->vida; i++) {
				Console::ForegroundColor = ConsoleColor::Red;
				cout << (char)220;
			}
			//cout << main->vida;
			for (int i = 0; i < 6 - main->vida; i++) {
				cout << " ";

			}
			CambioVida = false;
		}
		if (Disparo) {
			if (orientacion == Oeste) {
				Bala* b1 = new Bala();
				b1->x = 2;
				BalasActuales[10].push_back

				cout << BalasActuales[0]->x;
			}

			main->Pintar();
			Console::SetCursorPosition(main->Jx - varx, main->Jy + 1);
			cout << " ";
			varx++;
			Console::SetCursorPosition(main->Jx - varx, main->Jy + 1);
			cout << (char)245;
			_sleep(20);
			if (main->Jx - varx == 0) {
				main->Pintar();
				Console::SetCursorPosition(main->Jx - varx, main->Jy + 1);
				cout << " ";
				Disparo = false;
				varx = 2;
			}

		}
	}

	system("pause");
	return 0;
}