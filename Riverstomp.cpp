#include "pch.h"
#include "map.h"
#include <Windows.h>
using namespace System;
using namespace std;
int main()
{
	srand(time(NULL));
	createMap();
	bool camb = true; //Variable para la animacion del diparo
	bool CambioVida = true;
	bool Disparo, Perder = false;
	int malos, BalaVar, numBalas, temporizador, randomizador = 0;

	char tecla;


	//Variables importantes del juego:
	int cantEnemigos = 2;
	int vida = 10;
	int mainJx, mainJy; //coordenadas el jugador
	mainJx = 20; mainJy = 1;
	int EnemigoPosX = 100;

	int *EnemigoPosY = new int[cantEnemigos];
	EnemigoPosY[0] = 4;
	EnemigoPosY[1] = 43;


	Bala* BalasActuales = new Bala[10000];
	

	Jugador* main = new Jugador(226, 178, 47, 92, 186, vida, mainJx, mainJy);//Creación del jugador principal
	main->DibujaJugador();

	Jugador* MalosActuales = new Jugador[100]; //Arreglo que me permitirá mover a los enemigos por el mapa con un for que lo recorra más adelante

	for (int m = 0; m < cantEnemigos; m++) {//For que llena los enemigos en su arreglo

		MalosActuales[m] = Jugador(225, 206, 47, 92, 202, 2, EnemigoPosX, EnemigoPosY[m]);

	}

	while (1)
	{
		randomizador = rand() % 30;

		//******************************************************************   Movimiento del jugador y disparo    **************************************************************
		if (_kbhit())
		{
			tecla = _getch();
			if (tecla == DERECHA && (mapa[main->Jy][main->Jx + 1] == 1 && mapa[main->Jy + 2][main->Jx + 1] == 1 && mapa[main->Jy + 1][main->Jx + 2] == 1) && main->Jx + 1 != 119)
			{
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

			//Disparos
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
		// ***********************************************************************************************************************************************************

		//******************************************************************   Cambios en la barra de vida    **************************************************************
		if (CambioVida) {
			if (main->vida == 0)Perder = true;
			Console::SetCursorPosition(30, 0);
			Pintar(3);
			Console::SetCursorPosition(1, 0);
			for (int i = 0; i < vida; i++) {
				cout << " ";
			}
			Console::SetCursorPosition(1, 0);
			for (int i = 0; i < main->vida; i++) {
				Console::ForegroundColor = ConsoleColor::Red;
				cout << (char)254;
			}

			CambioVida = false;
		}
		// ***********************************************************************************************************************************************************

		//******************************************************************   Creación de balas aliadas *************************************************************
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
		// ***********************************************************************************************************************************************************

		//// ******************************************************************   Movimiento de las balas    **********************************************************
		for (int i = 0; i < numBalas; i++) {//For del recorrido de las balas
			BalasActuales[i].DibujaBala();

			//Revisar si la bala choca con algo

			//Si choca con los enemigos
			for (int bala = 0; bala < cantEnemigos; bala++) {
				if (((BalasActuales[i].x == (MalosActuales[bala].Jx) && (BalasActuales[i].y == MalosActuales[bala].Jy || BalasActuales[i].y == (MalosActuales[bala].Jy + 1) || BalasActuales[i].y == (MalosActuales[bala].Jy + 2))) || (BalasActuales[i].x == (MalosActuales[bala].Jx + 2) && BalasActuales[i].y == MalosActuales[bala].Jy + 1)) && !MalosActuales[bala].muerto) {
					Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
					Pintar(1);
					MalosActuales[bala].DibujaJugador();
					(MalosActuales[bala].vida)--;
					BalasActuales[i].y = 0;
					BalasActuales[i].x = 20;
					BalasActuales[i].parada = true;
					if (MalosActuales[bala].vida == 0) {
						MalosActuales[bala].muerto = true;
						MalosActuales[bala].BorraJugador();
					}
				}

			}

			//Si choca con el main
			if ((BalasActuales[i].x == (main->Jx + 1) && (BalasActuales[i].y == main->Jy || BalasActuales[i].y == (main->Jy + 1) || BalasActuales[i].y == (main->Jy + 2))) || (BalasActuales[i].x == (main->Jx + 2) && BalasActuales[i].y == main->Jy + 1)) {
				(main->vida)--;
				CambioVida = true;
				Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
				Pintar(1);
				cout << " ";
				BalasActuales[i].y = 0;
				BalasActuales[i].x = 20;
				BalasActuales[i].parada = true;

			}
		}
		// ***********************************************************************************************************************************************************


		// ******************************************************************   Movimiento de los enemigos    **********************************************************
		if (temporizador == 40) {

			for (int m = 0; m < cantEnemigos; m++) {
				if(!(MalosActuales[m].muerto)){
					//Borra
					MalosActuales[m].BorraJugador();

					//Mueve
					bool derechaEnemigo = mapa[MalosActuales[m].Jy][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy + 1][MalosActuales[m].Jx + 2] == 1;
					bool izquierdaEnemigo = mapa[MalosActuales[m].Jy][MalosActuales[m].Jx - 1] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx - 1] == 1 && mapa[MalosActuales[m].Jy + 1][MalosActuales[m].Jx - 2] == 1;

					bool arribaEnemigo = mapa[MalosActuales[m].Jy - 1][MalosActuales[m].Jx] == 1 && mapa[MalosActuales[m].Jy][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy][MalosActuales[m].Jx -1] == 1;
					bool abajoEnemigo = mapa[MalosActuales[m].Jy + 3][MalosActuales[m].Jx] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx - 1] == 1;

					//Movimiento vertical
					if (main->Jy > MalosActuales[m].Jy && abajoEnemigo) MalosActuales[m].Jy += 1;
					else if (main->Jy < MalosActuales[m].Jy && arribaEnemigo)  MalosActuales[m].Jy += -1;

					//Movimiento horizontal
					else if (main->Jx > MalosActuales[m].Jx && derechaEnemigo) MalosActuales[m].Jx += 1;
					else if (main->Jx < MalosActuales[m].Jx && izquierdaEnemigo)  MalosActuales[m].Jx += -1;




					//Dibuja
					MalosActuales[m].DibujaJugador();
				}


			}
			temporizador = 0;
		}
		// ***********************************************************************************************************************************************************

		// ******************************************************************  Disparos de los enemigos    ***********************************************************
		if (randomizador == 22 && !(MalosActuales[0].muerto)) {
			BalasActuales[BalaVar] = Bala(MalosActuales[0].Jx - 2, MalosActuales[0].Jy, Oeste);
			BalaVar++;
			numBalas++;

		}
		if (randomizador == 23 && !(MalosActuales[1].muerto)) {

			BalasActuales[BalaVar] = Bala(MalosActuales[1].Jx - 2, MalosActuales[1].Jy, Oeste);
			BalaVar++;
			numBalas++;
		}
		// ***********************************************************************************************************************************************************


		temporizador++;
		_sleep(20);

		// ******************************************************************   Pantalla GAME OVER    ******************************************************************
		if (Perder) {
			system("cls");
			Console::SetCursorPosition(40, 14);
			cout << "GAME OVER";
			break;
		}
		// **************************************************************************************************************************************************************
	}
	system("pause>null");
	return 0;
}