
#include "pch.h"
#include "map.h"

/*
TODO:

3- Aparición de enemigos de manera progresiva
5- Efectos de sonido
6- Niveles de dificultad
8- Pantallas de inicio y final
*/

using namespace System;
using namespace std;
using namespace chrono;
int main()
{
	srand(time(NULL));
	createMap();
	int posSalidaBalaX = 0, posSalidaBalaY = 0;
	int orientacionBalaEnemiga;
	bool camb = true; //Variable para la animacion del disparo
	bool CambioVida = true;
	bool Disparo = false;
	bool Perder = false;
	int malos, BalaVar, numBalas, temporizador, randomizador, randomizador2;
	int DibujaBonProyectil = 0;

	malos = BalaVar = numBalas = temporizador = randomizador = randomizador2 = 0;

	char tecla;

	//Herramientas para las bonificaciones
	int temporizadorBonificacion, bonificacionPosX, bonificacionPosY;
	bool showBonificacion = true;
	temporizadorBonificacion = 0;
	Bonificacion bon;//Se crea la �nica bonificaci�n que ir� movi�ndose por el mapa para dar puntos extra.

	int cantEnemigos = 0;
	int vida = 10;
	int mainJx, mainJy; //coordenadas el jugador
	mainJx = 20; mainJy = 1;
	int Puntos = 100; ActualizaPuntos(0, &Puntos);
	int EnemigoPosX, EnemigoPosY;

	bool intemediarioBonProy = false;
	bool variabl2 = true;
	int generacionMalo = 0;
	Bala* BalasActuales = new Bala[10000];

	Jugador* main = new Jugador(226, 178, 47, 92, 186, vida, mainJx, mainJy);//Creaci�n del jugador principal
	main->DibujaJugador();
	Jugador* MalosActuales = new Jugador[100]; //Arreglo que me permitir� mover a los enemigos por el mapa con un for que lo recorra m�s adelante
	short mal = 0;
	short sec, min, timerInv;
	time_point<system_clock> start;
	start = system_clock::now();
	bool count = false;
	bool count2 = true;


	while (1)
	{
		//Generacion de enemigos
		generacionMalo = rand() % 40;
		if (generacionMalo == 20) {
			while (1) {//Genero posiciones aleatorias dentro de los lugares permitidos
				EnemigoPosY = rand() % 48 + 1;
				EnemigoPosX = rand() % 118 + 1;
				if (mapa[EnemigoPosY][EnemigoPosX] == 1)break;
			}

			MalosActuales[mal] = Jugador(225, 206, 47, 92, 202, 2, EnemigoPosX, EnemigoPosY);
			MalosActuales[mal].DibujaJugador();

			mal++;
			cantEnemigos++;
			generacionMalo = 0;
		}


		//Timer
		sec = duration_cast<seconds>(system_clock::now() - start).count();
		min = duration_cast<minutes>(system_clock::now() - start).count();
		Console::SetCursorPosition(13, 0);
		Console::BackgroundColor = ConsoleColor::Black;
		Console::ForegroundColor = ConsoleColor::White;
		if (sec % 60 < 10)
			cout << 0 << min << ":" << 0 << sec % 60;
		else
			cout << 0 << min << ":" << sec % 60;

		//******************************************************************  Temporizador invisibilidad   **************************************************************
		if (count) { 
			Console::SetCursorPosition(55, 0);
			Console::BackgroundColor = ConsoleColor::Black;
			Console::ForegroundColor = ConsoleColor::White;
			cout << "  ";
			Console::SetCursorPosition(55, 0);
			Console::BackgroundColor = ConsoleColor::Black;
			Console::ForegroundColor = ConsoleColor::White;
			if (count2) {
				timerInv = sec + 10;
				count2 = false;
			}
			cout << (timerInv - sec);

			if (sec == timerInv) {
				Console::SetCursorPosition(30, 0);
				Pintar(3);
				Console::ForegroundColor = ConsoleColor::White;
				cout << "                        ";
				Console::SetCursorPosition(55, 0);
				Console::BackgroundColor = ConsoleColor::Black;
				Console::ForegroundColor = ConsoleColor::White;
				cout << " ";
				main->invisibilidad = false;
				main->DibujaJugador();
				count = false;
				count2 = true;
			}

		}
		// ***********************************************************************************************************************************************************

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

			//******************************************************************   Colisiones personaje principal    **************************************************************
			//Con las bonificaciones
			if (bonificacionPosX == main->Jx && bonificacionPosY == main->Jy || bonificacionPosX == main->Jx && bonificacionPosY == main->Jy + 2 || bonificacionPosX == main->Jx + 1 && bonificacionPosY == main->Jy + 1 || bonificacionPosX == main->Jx - 1 && bonificacionPosY == main->Jy + 1) {
				ActualizaPuntos(20, &Puntos);
				showBonificacion = true;
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


			 //******************************************************************   Invisibilidad    ******************************************************************   
			if (tecla == 105) {
				if (Puntos >= 50) {
					ActualizaPuntos(-50, &Puntos);
					Console::SetCursorPosition(30, 0);
					Pintar(3);
					Console::ForegroundColor = ConsoleColor::White;
					cout << "                                                                    ";
					Console::SetCursorPosition(30, 0);
					Pintar(3);
					Console::ForegroundColor = ConsoleColor::White;
					cout << "*Invisibilidad activada*";
					main->BorraJugador();
					main->invisibilidad = true;
					count = true;//Temporizador de la invisibilidad


				}
				else {
					Console::SetCursorPosition(30, 0);
					Pintar(3);
					Console::ForegroundColor = ConsoleColor::White;
					cout << "Necesitas m" << (char)160 << "s puntos para activar la invisibilidad!";

				}
			}
		}
		// ***********************************************************************************************************************************************************

		//******************************************************************   Cambios en la barra de vida    **************************************************************
		if (CambioVida) {
			main->vida--;
			if (main->vida == 0) {
				Perder = true;
			}
			Console::SetCursorPosition(1, 0);
			for (int i = 0; i < vida; i++) {
				Pintar(3);
				cout << " ";
			}
			Console::SetCursorPosition(1, 0);
			for (int i = 0; i < main->vida; i++) {
				Pintar(3);
				Console::ForegroundColor = ConsoleColor::Red;
				cout << (char)254;
			}

			CambioVida = false;
		}
		// ***********************************************************************************************************************************************************

		//******************************************************************   Creaci�n de balas aliadas *************************************************************
		if (Disparo) {
			if (orientacion == Oeste) {
				BalasActuales[BalaVar] = Bala(main->Jx - 2, main->Jy + 1, Oeste, true);
			}
			else if (orientacion == Este) {
				BalasActuales[BalaVar] = Bala(main->Jx + 2, main->Jy + 1, Este, true);
			}
			else if (orientacion == Norte) {
				BalasActuales[BalaVar] = Bala(main->Jx, main->Jy - 1, Norte, true);
			}
			else if (orientacion == Sur) {
				BalasActuales[BalaVar] = Bala(main->Jx, main->Jy + 3, Sur, true);
			}
			Disparo = false;
			BalaVar++;
			numBalas++;
		}
		// ***********************************************************************************************************************************************************

		// ******************************************************************   Movimiento de los enemigos    **********************************************************
		if (temporizador == 40) {

			for (int m = 0; m < cantEnemigos; m++) {
				if (!(MalosActuales[m].muerto)) {
					//Borra
					MalosActuales[m].BorraJugador();


					//Mueve
					bool derechaEnemigo = mapa[MalosActuales[m].Jy][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy + 1][MalosActuales[m].Jx + 2] == 1;
					bool izquierdaEnemigo = mapa[MalosActuales[m].Jy][MalosActuales[m].Jx - 1] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx - 1] == 1 && mapa[MalosActuales[m].Jy + 1][MalosActuales[m].Jx - 2] == 1;

					bool arribaEnemigo = mapa[MalosActuales[m].Jy - 1][MalosActuales[m].Jx] == 1 && mapa[MalosActuales[m].Jy][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy][MalosActuales[m].Jx - 1] == 1;
					bool abajoEnemigo = mapa[MalosActuales[m].Jy + 3][MalosActuales[m].Jx] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx + 1] == 1 && mapa[MalosActuales[m].Jy + 2][MalosActuales[m].Jx - 1] == 1;

					//Movimiento vertical
					if ((main->Jy > MalosActuales[m].Jy && abajoEnemigo) && !(main->invisibilidad)) MalosActuales[m].Jy += 1;
					else if (main->Jy < MalosActuales[m].Jy && arribaEnemigo && !(main->invisibilidad))  MalosActuales[m].Jy += -1;

					//Movimiento horizontal
					else if (main->Jx > MalosActuales[m].Jx && derechaEnemigo && !(main->invisibilidad)) MalosActuales[m].Jx += 1;
					else if (main->Jx < MalosActuales[m].Jx && izquierdaEnemigo && !(main->invisibilidad))  MalosActuales[m].Jx += -1;
					




					//Dibuja
					MalosActuales[m].DibujaJugador();
				}


			}
			temporizador = 0;
		}
		// ***********************************************************************************************************************************************************

		// ******************************************************************  Disparos de los enemigos    ***********************************************************
		randomizador = rand() % 22; //Para decidir si dispara o no
		if (randomizador == 11) {
			for (int dis = 0; dis < cantEnemigos; dis++) {
				randomizador2 = rand() % cantEnemigos;
				if (!(MalosActuales[randomizador2].muerto )) {

					//Decisión enemiga de la dirección del disparo para darle al jugador
					if ((MalosActuales[randomizador2].Jy - main->Jy) < 0) {//Está debajo 1 está encima 0
						if ((MalosActuales[randomizador2].Jx - main->Jx) < 0) {//Está a la derecha 1 está a la izquierda 0
							//Jugador está Debajo y derecha 
							if ((-(MalosActuales[randomizador2].Jy - main->Jy)) > (-(MalosActuales[randomizador2].Jx - main->Jx))) orientacionBalaEnemiga = Sur;
							else orientacionBalaEnemiga = Este;
						}
						else {
							//Jugador está Debajo e izquierda
							if ((-(MalosActuales[randomizador2].Jy - main->Jy)) > (MalosActuales[randomizador2].Jx - main->Jx)) orientacionBalaEnemiga = Sur;
							else orientacionBalaEnemiga = Oeste;
						}
					}
					else {
						if ((MalosActuales[randomizador2].Jx - main->Jx) < 0) {//Está a la derecha 1 está a la izquierda 0
							//Jugador está Encima y derecha
							if (((MalosActuales[randomizador2].Jy - main->Jy)) > (-(MalosActuales[randomizador2].Jx - main->Jx))) orientacionBalaEnemiga = Norte;
							else orientacionBalaEnemiga = Este;
						}
						else {
							//Jugador está Encima e izquierda
							if (((MalosActuales[randomizador2].Jy - main->Jy)) > ((MalosActuales[randomizador2].Jx - main->Jx))) orientacionBalaEnemiga = Norte;
							else orientacionBalaEnemiga = Oeste;
						}
					}
					if (!(main->invisibilidad)) { //Inicializo variables para dar la posicion inicial de las balas en funcion a la orientacion
						switch (orientacionBalaEnemiga) {
						case Norte:  posSalidaBalaX = 0; posSalidaBalaY = -1; break;
						case Sur:  posSalidaBalaX = 0; posSalidaBalaY = 3; break;
						case Este:  posSalidaBalaX = 2; posSalidaBalaY = 1; break;
						case Oeste:  posSalidaBalaX = -2; posSalidaBalaY = 1; break;
					}
					BalasActuales[BalaVar] = Bala(MalosActuales[randomizador2].Jx + posSalidaBalaX, MalosActuales[randomizador2].Jy + posSalidaBalaY, orientacionBalaEnemiga, false);
					BalaVar++;
					numBalas++;
					}
				}
			}
		}
		// ***********************************************************************************************************************************************************

		//// ******************************************************************   Movimiento de las balas    **********************************************************

		for (int i = 0; i < BalaVar; i++) {//For del recorrido de las balas

			if (!(BalasActuales[i].parada)) {
				//Borra
				Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
				if (mapa[BalasActuales[i].y][BalasActuales[i].x] == 1) Pintar(1);
				else if (mapa[BalasActuales[i].y][BalasActuales[i].x] == 2) Pintar(2);
				cout << " ";

				//Mueve
				if (BalasActuales[i].x + 1 != 120 && BalasActuales[i].x - 1 != -1 && BalasActuales[i].y + 1 != 51 && BalasActuales[i].y - 1 != -1) {
					if (BalasActuales[i]. or == Norte)BalasActuales[i].y--;
					else if (BalasActuales[i]. or == Sur)BalasActuales[i].y++;
					else if (BalasActuales[i]. or == Este)BalasActuales[i].x++;
					else if (BalasActuales[i]. or == Oeste)BalasActuales[i].x--;
				}

				//Dibuja
				//Solo dibujo la bala si no ha sido parda
				BalasActuales[i].DibujaBala();
			}
			//Revisar si la bala choca con algo

			//Si choca con los enemigos
			for (int bala = 0; bala < cantEnemigos; bala++) {
				if (((BalasActuales[i].x == (MalosActuales[bala].Jx) && (BalasActuales[i].y == MalosActuales[bala].Jy || BalasActuales[i].y == (MalosActuales[bala].Jy + 1) || BalasActuales[i].y == (MalosActuales[bala].Jy + 2))) || (BalasActuales[i].x == (MalosActuales[bala].Jx + 2) && BalasActuales[i].y == MalosActuales[bala].Jy + 1)) && !MalosActuales[bala].muerto && BalasActuales[i].aliado) {
					Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
					Pintar(1);
					MalosActuales[bala].DibujaJugador();
					(MalosActuales[bala].vida)--;
					BalasActuales[i].y = 0;
					BalasActuales[i].x = 20;
					BalasActuales[i].parada = true;
					ActualizaPuntos(10, &Puntos);
					if (MalosActuales[bala].vida == 0) {
						MalosActuales[bala].muerto = true;
						MalosActuales[bala].BorraJugador();
					}
				}
				//TODO
				//else if (((BalasActuales[i].x == (MalosActuales[bala].Jx) && (BalasActuales[i].y == MalosActuales[bala].Jy || BalasActuales[i].y == (MalosActuales[bala].Jy + 1) || BalasActuales[i].y == (MalosActuales[bala].Jy + 2))) || (BalasActuales[i].x == (MalosActuales[bala].Jx + 2) && BalasActuales[i].y == MalosActuales[bala].Jy + 1)) && !MalosActuales[bala].muerto && !BalasActuales[i].aliado){

				//	MalosActuales[bala].DibujaJugador();
				//}

			}

			//Si choca con el main
			if ((BalasActuales[i].x == (main->Jx + 1) && (BalasActuales[i].y == main->Jy || BalasActuales[i].y == (main->Jy + 1) || BalasActuales[i].y == (main->Jy + 2))) || (BalasActuales[i].x == (main->Jx + 2) && BalasActuales[i].y == main->Jy + 1)) {
			
				CambioVida = true;
				Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
				Pintar(1);
				cout << " ";
				BalasActuales[i].y = 0;
				BalasActuales[i].x = 20;
				BalasActuales[i].parada = true;

			}

			//Si choca con una bonificacion

			if (BalasActuales[i].x == bonificacionPosX && BalasActuales[i].y == bonificacionPosY) intemediarioBonProy = true;
		}
		// ***********************************************************************************************************************************************************
		
		//// ******************************************************************   Bonificaciones   **********************************************************
		//Aparicion
		if (showBonificacion) {
			while (1) {

				bonificacionPosX = rand() % 120;
				bonificacionPosY = rand() % 51;
				if (mapa[bonificacionPosY][bonificacionPosX] == 1)break;

			}
			bon.a = bonificacionPosX;
			bon.b = bonificacionPosY;
			bon.dibujaBonificacion();
			showBonificacion = false;
		}

		//Que no se borre si le cae una bala
		if (intemediarioBonProy) DibujaBonProyectil++;
		if (DibujaBonProyectil == 2) {
			bon.dibujaBonificacion();
			DibujaBonProyectil = 0;
		}
		// ***********************************************************************************************************************************************************

		temporizador++;
		temporizadorBonificacion++;
		_sleep(20);

		// ******************************************************************   Pantalla GAME OVER    ******************************************************************
		if (Perder) {
			GAMEOVER();
			break;
		}
		// **************************************************************************************************************************************************************

		//Console::SetCursorPosition(16, 0);
		//cout << temporizador;

	}
	system("pause>null");
	return 0;
}