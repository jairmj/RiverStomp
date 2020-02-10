// ConsoleApplication7.cpp: archivo de proyecto principal.

#include "pch.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "map.h"

#define DERECHA 77
#define IZQUIERDA 75
#define ABAJO 80
#define ARRIBA 72

using namespace System;
using namespace std;


int main()
{
	//Jugador *main = new Jugador(1, 1, 3);

	createMap();
	int mainJx, mainJy; //coordenadas el jugador
	mainJx = 40; mainJy = 1;
	char tecla;

	Jugador *main = new Jugador('O', 178, 47, 92, 186, 3, mainJx, mainJy);
	while (1)
	{
		if (_kbhit())
		{
			tecla = _getch();


			if (tecla == DERECHA && (mapa[main->Jy][main->Jx + 1] == 1 && mapa[main->Jy + 2][main->Jx + 1] == 1 && mapa[main->Jy+1][main->Jx + 2] == 1) && main->Jx + 1 != 119)
			{
				//borrar 
				main->BorraJugador();
				//mover
				main->Jx++;
				//dibujar
				main->DibujaJugador();
				//cout << "x: " << main->Jx << "y: " << main->Jy <<" 1: "<< mapa[main->Jy + 3][main->Jx]<<" 2: " << mapa[main->Jy - 2][main->Jx + 1] <<" 3: " << mapa[main->Jy - 2][main->Jx - 1];
			}
			else if (tecla == ARRIBA && (mapa[main->Jy - 1][main->Jx] == 1 && mapa[main->Jy][main->Jx+1] == 1 && mapa[main->Jy][main->Jx-1] == 1)) {
				//borrar 
				main->BorraJugador();
				//mover
				main->Jy--;
				//dibujar
				main->DibujaJugador();
			}
			else if (tecla == ABAJO && mapa[main->Jy + 3][main->Jx] == 1 && mapa[main->Jy + 2][main->Jx+1] == 1 && mapa[main->Jy + 2][main->Jx-1] == 1) {
				main->BorraJugador();
				//mover
				main->Jy++;
				//dibujar
				main->DibujaJugador();
				//cout << "x: "<<main->Jx << "y: " << main->Jy;
			}
			else if (tecla == IZQUIERDA && mapa[main->Jy][main->Jx - 1] == 1 && mapa[main->Jy + 2][main->Jx - 1] == 1 && mapa[main->Jy + 1][main->Jx - 2] == 1 && (main->Jx - 1 != 0)) {
				//borrar 
				main->BorraJugador();
				//mover
				main->Jx--;
				//dibujar
				main->DibujaJugador();
			}


		}

	}
	


	system("pause");
	return 0;
}