
#include "pch.h"
#include "map.h"
#include <iostream>

/*
TODO:

5- Efectos de sonido
8- Pantallas de inicio, final e instrucciones
*/

using namespace System;
using namespace std;
using namespace chrono;
int main()
{
	SetConsoleOutputCP(850);
	int vida = PantallaInicio();
	pantallaInstrucciones();
	srand(time(NULL));
	createMap();



	//Variables valor agregado
	bool purificadorAgua = false;
	bool armaComprada = false;
	int contaminacionPosX, contaminacionPosY, randomizadorContaminacion;
	bool todosMuertos;


	int posSalidaBalaX = 0, posSalidaBalaY = 0;
	int orientacionBalaEnemiga;

	bool avanzado = true;

	//********************************  Valoriables booleanas para entrar en apartados del while principal    *********************************

	bool CambioVida = true;
	bool Disparo = false;
	bool Perder = false;


	bool camb = true;// Variable para hacer que la animacion al disparar vaya variando.

	int BalaVar, numBalas, temporizador, randomizador, randomizador2;


	BalaVar = numBalas = temporizador = randomizador = randomizador2 = 0;

	char tecla;//para el getch

	//Herramientas para las bonificaciones
	int temporizadorBonificacion, bonificacionPosX, bonificacionPosY, DibujaBonProyectil;
	bool showBonificacion = true;
	temporizadorBonificacion = DibujaBonProyectil = 0;
	Bonificacion bon;//Se crea la única bonificación que irá moviéndose por el mapa para dar puntos extra.
	bool intemediarioBonProy = false;//Dos booleanos para hacer que no se borre cuando un proyectil lo atraviesa
	bool variabl2 = true;

	//Herramientas para las monedas
	int temporizadorMoneda, DibujaMonedaProyectil;
	bool showMoneda = true;
	temporizadorMoneda = DibujaMonedaProyectil = 0;
	Moneda coin;//Se crea la única bonificación que irá moviéndose por el mapa para dar puntos extra.
	bool intemediarioMonedaProy = false;//Dos booleanos para hacer que no se borre cuando un proyectil lo atraviesa
	bool variabl1 = true;


	//Variables de parametros del jugador

	int mainJx, mainJy; //coordenadas donde empezará el jugador
	mainJx = 20; mainJy = 1;
	int Puntos = 100; ActualizaPuntos(100, &Puntos);
	int Dinero = 0; ActualizaDinero(0, &Dinero);


	Bala* BalasActuales = new Bala[10000];

	//Creaci�n del jugador principal
	Personaje* main = new Personaje(226, 178, 47, 92, 186, vida, mainJx, mainJy, 0);
	main->DibujaJugador();
	short temporizadorInmunidad = 0;

	bool Inmunidad = false; //Variable para volverte inmune al daño



	int generacionMalo, enemigoInvisible, timerInvisiblidadAlfa;
	int EnemigoPosX, EnemigoPosY;
	int cantEnemigos = 0;
	bool generarAlfa = true;

	Personaje* MalosActuales = new Personaje[100]; //Arreglo que me permitirá mover a los enemigos por el mapa con un for que lo recorra más adelante

	//Variables y configuracion del timer
	short sec, min;
	time_point<system_clock> start;
	start = system_clock::now();

	//Variables para el timer de la invisibilidad
	short  timerInv, timerMessage;
	timerMessage = 0;
	bool count = false;
	bool count2 = true;


	short ronda = 0; //Variable para contorlar las rondas

	//Enemigos por ronda (van acumulando el anterior)
	int EnemigosRonda[4];
	EnemigosRonda[0] = 3;
	EnemigosRonda[1] = 8;
	EnemigosRonda[2] = 15;
	EnemigosRonda[3] = 24;

	int kills = 0; //Muertes que ha hecho el jugador
	int Contaminacion = 0;
	while (1)
	{
		//Compruebo si hay 4 en la matriz mapa (solo si ha llegado a la quinta ronda, sino porlas)
				//Compruebo si hay 4 en la matriz mapa (solo si ha llegado a la cuarta ronda, sino porlas)
		if (ronda == 4) {
			Contaminacion = 0;
			for (int f = 0; f < 51; f++)
			{
				for (int c = 0; c < 120; c++)
				{
					if (mapa[f][c] == 4) Contaminacion++;
				}
			}
		}
		 

		//Condiciones para ganar: que ronda sea 4 y que no haya mierda en el rio.
		if (ronda == 4 && Contaminacion == 0) {
			//NivelMapa++;
			GAMEOVER();
		}


		//Condiciones para ganar: que ronda sea 4 y que no haya mierda en el rio.
		

		//Generacion de enemigos
		Console::SetCursorPosition(21, 0);
		Pintar(3,0);
		Console::ForegroundColor = ConsoleColor::White;
		cout << "Ronda: " << ronda + 1 << "  Kills: " << kills;
		if (kills == EnemigosRonda[ronda]) {
			ronda++;
			generarAlfa = true;
		}

		generacionMalo = rand() % 150;

		//Si entra genera un enemigo (genera un alfa por ronda)
		if ((generacionMalo == 20 && cantEnemigos < EnemigosRonda[ronda]) && ronda < 4) {
			while (1) {//Genero posiciones aleatorias dentro de los lugares permitidos
				EnemigoPosY = rand() % 48 + 1;
				EnemigoPosX = rand() % 118 + 1;
				if (mapa[EnemigoPosY][EnemigoPosX] == 1)break;
			}
			if (generarAlfa) {
				MalosActuales[cantEnemigos] = Personaje(155, 206, 47, 92, 202, 5, EnemigoPosX, EnemigoPosY, 2);
				MalosActuales[cantEnemigos].DibujaJugador();
				generarAlfa = false;
				cantEnemigos++;
			}
			else {
				MalosActuales[cantEnemigos] = Personaje(225, 206, 47, 92, 202, 2, EnemigoPosX, EnemigoPosY, 1);
				MalosActuales[cantEnemigos].DibujaJugador();
				cantEnemigos++;
			}


			
		}

		//Si entra cambia el color de los enemigos de tipo beta
		if (generacionMalo == 3) {
			for (int a = 0; a < cantEnemigos; a++) {
				if (!MalosActuales[a].muerto && MalosActuales[a].tipo == 1) {
					int randomizador4 = rand() % 3 + 1;
					MalosActuales[a].color = randomizador4;
				}
			}
		}

		//Si entra vuelve al alfa invisible
		if (generacionMalo == 1) {
			for (int a = 0; a < cantEnemigos; a++) {
				if (!MalosActuales[a].muerto && MalosActuales[a].tipo == 2) {
					if(!MalosActuales[a].invisibilidad){
						enemigoInvisible = a;
						MalosActuales[a].invisibilidad = true;
						MalosActuales[a].BorraJugador();
						timerInvisiblidadAlfa = sec + 5;
					}
				}
			}
		}
		//Para quitarle la invisibilidad luego de 5 segundos
		if (timerInvisiblidadAlfa == sec) {
			MalosActuales[enemigoInvisible].invisibilidad = false;
			MalosActuales[enemigoInvisible].DibujaJugador();
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
		if (timerMessage == sec && timerMessage != 0) { //En caso el mensaje "Necesitas mas puntos para...." aparezca, que se vaya luego de 3 segundos
			timerMessage = 0;
			Console::SetCursorPosition(41, 0);
			cout << "                                                      ";
		}

		if (count) {
			Console::SetCursorPosition(67, 0);
			Console::BackgroundColor = ConsoleColor::Black;
			Console::ForegroundColor = ConsoleColor::White;
			cout << "  ";
			Console::SetCursorPosition(67, 0);
			Console::BackgroundColor = ConsoleColor::Black;
			Console::ForegroundColor = ConsoleColor::White;
			if (count2) {
				timerInv = sec + 10;
				count2 = false;
			}
			cout << (timerInv - sec);

			if (sec == timerInv) {
				Console::SetCursorPosition(41, 0);
				Pintar(3, 0);
				Console::ForegroundColor = ConsoleColor::White;
				cout << "                        ";
				Console::SetCursorPosition(67, 0);
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

		//****************************************  Movimiento del jugador, disparo, invisibilidad y arma limpiadora   **************************************************************
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
			else if (tecla == 99 && !armaComprada) {
				
				if (Dinero > 99) {
				ActualizaDinero(-100, &Dinero);
				armaComprada = true;
				}
			}
			//cout << tecla;

			//******************************************************************   Colisiones personaje principal    **************************************************************
			//Con las bonificaciones
			if (bonificacionPosX == main->Jx && bonificacionPosY == main->Jy || bonificacionPosX == main->Jx && bonificacionPosY == main->Jy + 2 || bonificacionPosX == main->Jx + 1 && bonificacionPosY == main->Jy + 1 || bonificacionPosX == main->Jx - 1 && bonificacionPosY == main->Jy + 1) {
				ActualizaPuntos(20, &Puntos);
				showBonificacion = true;
			}
			//Con las Monedas
			if (coin.x == main->Jx && coin.y == main->Jy || coin.x == main->Jx && coin.y == main->Jy + 2 || coin.x == main->Jx + 1 && coin.y == main->Jy + 1 || coin.x == main->Jx - 1 && coin.y == main->Jy + 1) {
				ActualizaDinero(20, &Dinero);
				showMoneda = true;
			}
			//Con los enemigos
			for (int m = 0; m < cantEnemigos; m++) {
				//											Su mano derecha en mi cabeza											Su mano derecha en mi mano izquieda															Su mano derecha en mis 
				bool derechaEnemigoCol = MalosActuales[m].Jy + 1 == main->Jy && MalosActuales[m].Jx + 1 == main->Jx || MalosActuales[m].Jy + 1 == main->Jy + 1 && MalosActuales[m].Jx + 1 == main->Jx - 1 || MalosActuales[m].Jy + 1 == main->Jy + 2 && MalosActuales[m].Jx + 1 == main->Jx;
				//											Su mano izquierda en mi cabeza											Su mano izquierda en mi mano derecha															Su mano izquierda en mis pies
				bool izquierdaEnemigoCol = MalosActuales[m].Jy + 1 == main->Jy && MalosActuales[m].Jx - 1 == main->Jx || MalosActuales[m].Jy + 1 == main->Jy + 1 && MalosActuales[m].Jx - 1 == main->Jx + 1 || MalosActuales[m].Jy + 1 == main->Jy + 2 && MalosActuales[m].Jx - 1 == main->Jx;
				//											Su cabeza en mis pies											
				bool arribaEnemigoCol = MalosActuales[m].Jy == main->Jy + 2 && MalosActuales[m].Jx == main->Jx;
				//											Sus pies en mi cabeza										
				bool abajoEnemigoCol = MalosActuales[m].Jy + 2 == main->Jy && MalosActuales[m].Jx == main->Jx;

				if ((derechaEnemigoCol || izquierdaEnemigoCol || arribaEnemigoCol || abajoEnemigoCol) && !(MalosActuales[m].muerto)) {
					CambioVida = true;
					temporizadorInmunidad = sec + 3; //3 Segundos de inmunidad cuando te chocas con un enemigo
					Inmunidad = true;
				}
			}


			//Disparos
			if (tecla == ESPACIO || tecla == 101) {
				switch (orientacion) {
				case Norte: animacionDisparo(*main, 196, 196, 238, 238, &camb); break;
				case Este: animacionDisparo(*main, 32, 185, 32, 205, &camb); break;
				case Sur: animacionDisparo(*main, 179, 179, 124, 124, &camb); break;
				case Oeste: animacionDisparo(*main, 204, 32, 205, 32, &camb);
				}
				if (tecla == ESPACIO)Disparo = true;
				else if (tecla == 101 && armaComprada) purificadorAgua = true;
			}//Disparo


		//******************************************************************   Invisibilidad    ******************************************************************   
			if (tecla == 105 && !(main->invisibilidad)) {
				if (Puntos >= 50) {
					ActualizaPuntos(-50, &Puntos);
					Console::SetCursorPosition(41, 0);
					Pintar(3,0);
					Console::ForegroundColor = ConsoleColor::White;
					cout << "                                                                    ";
					Console::SetCursorPosition(41, 0);
					Pintar(3,0);
					Console::ForegroundColor = ConsoleColor::White;
					cout << "*Invisibilidad activada*";
					ActualizaPuntos(0, &Puntos);
					main->BorraJugador();
					main->invisibilidad = true;
					count = true;//Temporizador de la invisibilidad


				}
				else {
					Console::SetCursorPosition(41, 0);
					Pintar(3,0);
					Console::ForegroundColor = ConsoleColor::White;
					cout << "Necesitas m" << (char)160 << "s puntos para activar la invisibilidad!";
					timerMessage = sec + 4;//Para borrar el mensaje de arriba luego de 4 segundos, cuando timver message y sec sean iguales es que han pasado.

				}
			}
		}
		// ***********************************************************************************************************************************************************

		//******************************************************************   Cambios en la barra de vida    **************************************************************
		if (temporizadorInmunidad == sec && temporizadorInmunidad != 0) {
			Inmunidad = false;
			temporizadorInmunidad = 0;
		}
		if (CambioVida && !Inmunidad) {
			main->vida--;
			if (main->vida == 0) {
				Perder = true;
			}
			Console::SetCursorPosition(1, 0);
			for (int i = 0; i < vida; i++) {
				Pintar(3,0);
				cout << " ";
			}
			Console::SetCursorPosition(1, 0);
			for (int i = 0; i < main->vida; i++) {
				Pintar(3,0);
				Console::ForegroundColor = ConsoleColor::Red;
				cout << (char)254;
			}

			CambioVida = false;
		}
		// ***********************************************************************************************************************************************************

		//******************************************************************   Creación de balas aliadas *************************************************************
		if (Disparo) {
			if (orientacion == Oeste) {
				BalasActuales[BalaVar] = Bala(main->Jx - 2, main->Jy + 1, Oeste, true, false);
			}
			else if (orientacion == Este) {
				BalasActuales[BalaVar] = Bala(main->Jx + 2, main->Jy + 1, Este, true, false);
			}
			else if (orientacion == Norte) {
				BalasActuales[BalaVar] = Bala(main->Jx, main->Jy - 1, Norte, true, false);
			}
			else if (orientacion == Sur) {
				BalasActuales[BalaVar] = Bala(main->Jx, main->Jy + 3, Sur, true, false);
			}
			Disparo = false;
			BalaVar++;
			numBalas++;
		}
		// ***********************************************************************************************************************************************************
		//******************************************************************   Creación de balas purificadoras *************************************************************
		if (purificadorAgua) {
			if (orientacion == Oeste) {
				BalasActuales[BalaVar] = Bala(main->Jx - 2, main->Jy + 1, Oeste, true, true);
			}
			else if (orientacion == Este) {
				BalasActuales[BalaVar] = Bala(main->Jx + 2, main->Jy + 1, Este, true, true);
			}
			else if (orientacion == Norte) {
				BalasActuales[BalaVar] = Bala(main->Jx, main->Jy - 1, Norte, true, true);
			}
			else if (orientacion == Sur) {
				BalasActuales[BalaVar] = Bala(main->Jx, main->Jy + 3, Sur, true, true);
			}
			purificadorAgua = false;
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
					if ((main->Jy > MalosActuales[m].Jy&& abajoEnemigo) && !(main->invisibilidad)) MalosActuales[m].Jy += 1;
					else if (main->Jy < MalosActuales[m].Jy && arribaEnemigo && !(main->invisibilidad))  MalosActuales[m].Jy += -1;

					//Movimiento horizontal
					else if (main->Jx > MalosActuales[m].Jx&& derechaEnemigo && !(main->invisibilidad)) MalosActuales[m].Jx += 1;
					else if (main->Jx < MalosActuales[m].Jx && izquierdaEnemigo && !(main->invisibilidad))  MalosActuales[m].Jx += -1;





					//Dibuja
					MalosActuales[m].DibujaJugador();


					//Colisiones con el jugador
					//											Su mano derecha en mi cabeza											Su mano derecha en mi mano izquieda															Su mano derecha en mis pies
					bool derechaEnemigoCol = MalosActuales[m].Jy + 1 == main->Jy && MalosActuales[m].Jx + 1 == main->Jx || MalosActuales[m].Jy + 1 == main->Jy + 1 && MalosActuales[m].Jx + 1 == main->Jx - 1 || MalosActuales[m].Jy + 1 == main->Jy + 2 && MalosActuales[m].Jx + 1 == main->Jx;
					//											Su mano izquierda en mi cabeza											Su mano izquierda en mi mano derecha															Su mano izquierda en mis pies
					bool izquierdaEnemigoCol = MalosActuales[m].Jy + 1 == main->Jy && MalosActuales[m].Jx - 1 == main->Jx || MalosActuales[m].Jy + 1 == main->Jy + 1 && MalosActuales[m].Jx - 1 == main->Jx + 1 || MalosActuales[m].Jy + 1 == main->Jy + 2 && MalosActuales[m].Jx - 1 == main->Jx;
					//											Su cabeza en mis pies											
					bool arribaEnemigoCol = MalosActuales[m].Jy == main->Jy + 2 && MalosActuales[m].Jx == main->Jx;
					//											Sus pies en mi cabeza										
					bool abajoEnemigoCol = MalosActuales[m].Jy + 2 == main->Jy && MalosActuales[m].Jx == main->Jx;

					if (derechaEnemigoCol || izquierdaEnemigoCol || arribaEnemigoCol || abajoEnemigoCol) {
						CambioVida = true;
					}



				}


			}
			temporizador = 0;
		}
		// ***********************************************************************************************************************************************************

		// ******************************************************************  Cracion de balas enemigas ***********************************************************
		randomizador = rand() % 40; //Para decidir si dispara o no
		if (randomizador == 11 && avanzado) {
			for (int dis = 0; dis < cantEnemigos; dis++) {
				randomizador2 = rand() % cantEnemigos;
				if (!(MalosActuales[randomizador2].muerto)) {

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
						BalasActuales[BalaVar] = Bala(MalosActuales[randomizador2].Jx + posSalidaBalaX, MalosActuales[randomizador2].Jy + posSalidaBalaY, orientacionBalaEnemiga, false, false);
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
				if (mapa[BalasActuales[i].y][BalasActuales[i].x] == 1) Pintar(1,0);
				else if (mapa[BalasActuales[i].y][BalasActuales[i].x] == 2) Pintar(2,0);
				else if (mapa[BalasActuales[i].y][BalasActuales[i].x] == 4) Pintar(4,0);
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
				//										Si le doy en la cabeza																								Si le doy en el brazo izquierdo												      	Si le doy en brazo derecho																						Si le doy en los pies				
				if (( (BalasActuales[i].x == MalosActuales[bala].Jx && BalasActuales[i].y == MalosActuales[bala].Jy) || (BalasActuales[i].x == MalosActuales[bala].Jx - 1 && BalasActuales[i].y == MalosActuales[bala].Jy + 1) || (BalasActuales[i].x == MalosActuales[bala].Jx + 1 && BalasActuales[i].y == MalosActuales[bala].Jy + 1) || (BalasActuales[i].x == MalosActuales[bala].Jx && BalasActuales[i].y == MalosActuales[bala].Jy + 2) ) && !MalosActuales[bala].muerto && BalasActuales[i].aliado) {
					Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
					Pintar(1,0);
					MalosActuales[bala].DibujaJugador();
					(MalosActuales[bala].vida)--;
					BalasActuales[i].y = 0;
					BalasActuales[i].x = 20;
					BalasActuales[i].parada = true;
					ActualizaPuntos(10, &Puntos);
					if (MalosActuales[bala].vida == 0) {
						kills++;
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
			bool ChoqueDerecha = (BalasActuales[i].x == (main->Jx + 1) && (BalasActuales[i].y == main->Jy + 1 || BalasActuales[i].x == (main->Jx) && BalasActuales[i].y == (main->Jy + 2))) || (BalasActuales[i].x == (main->Jx) && BalasActuales[i].y == main->Jy);
			bool ChoqueIzquierda = (BalasActuales[i].x == (main->Jx) && (BalasActuales[i].y == main->Jy || BalasActuales[i].x == (main->Jx) && BalasActuales[i].y == (main->Jy + 2))) || (BalasActuales[i].x == (main->Jx - 1) && BalasActuales[i].y == main->Jy + 1);
			bool ChoqueInferior = (BalasActuales[i].x == (main->Jx) && (BalasActuales[i].y == main->Jy + 2 || BalasActuales[i].x == (main->Jx + 1) && BalasActuales[i].y == (main->Jy + 1))) || (BalasActuales[i].x == (main->Jx - 1) && BalasActuales[i].y == main->Jy + 1);
			bool ChoqueSuperior = (BalasActuales[i].x == (main->Jx) && (BalasActuales[i].y == main->Jy || BalasActuales[i].x == (main->Jx + 1) && BalasActuales[i].y == (main->Jy + 1))) || (BalasActuales[i].x == (main->Jx - 1) && BalasActuales[i].y == main->Jy +1);
			if (ChoqueDerecha || ChoqueInferior || ChoqueSuperior || ChoqueIzquierda) {

				CambioVida = true;
				Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
				Pintar(1,0);
				cout << " ";
				BalasActuales[i].y = 0;
				BalasActuales[i].x = 20;
				BalasActuales[i].parada = true;
				main->DibujaJugador();

			}

			//Si choca con una bonificacion

			if (BalasActuales[i].x == bonificacionPosX && BalasActuales[i].y == bonificacionPosY) intemediarioBonProy = true;

			//Si choca con una Moneda

			if (BalasActuales[i].x == coin.x && BalasActuales[i].y ==coin.y) intemediarioMonedaProy = true;

			//Si la purificadora choca con la contaminacion

			if (BalasActuales[i].purificadora && (mapa[BalasActuales[i].y][BalasActuales[i].x] == 4)) {
				Console::SetCursorPosition(BalasActuales[i].x, BalasActuales[i].y);
				Console::BackgroundColor = ConsoleColor::Blue;
				cout << " ";
				mapa[BalasActuales[i].y][BalasActuales[i].x] = 2;
			}
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

				//// ******************************************************************   Monedas   **********************************************************
		//Aparicion
		if (showMoneda) {
			while (1) {

				coin.x = rand() % 120;
				coin.y = rand() % 51;
				if (mapa[coin.y][coin.x] == 1)break;

			}
			coin.dibujaMoneda();
			showMoneda = false;
		}

		//Que no se borre si le cae una bala
		if (intemediarioMonedaProy) DibujaMonedaProyectil++;
		if (DibujaMonedaProyectil == 2) {
			coin.dibujaMoneda();
			DibujaMonedaProyectil= 0;
		}
		// ***********************************************************************************************************************************************************
		// ******************************************************************   Contaminación del agua    ******************************************************************
		//Compruebo si hay enemigos vivos
		
		for (int malos = 0; malos < cantEnemigos; malos++) {
			if (malos == 0) todosMuertos = MalosActuales[malos].muerto;//Si el primero está muerto adqquiere 1, de lo contrario 0
			else {
				todosMuertos *= MalosActuales[malos].muerto; //Voy multiplicando el resultado del anterior con el estado del sigueinte, si todos están muertos da 1, si hay 1 solo vivo da 0
			}
		}
		
		randomizadorContaminacion = rand() % 100;
		if (!todosMuertos && randomizadorContaminacion == 23) {//Entra cuando hay al menos 1 vivo
			while (1) {

				contaminacionPosX = rand() % 118 + 1;
				contaminacionPosY = rand() % 51;
				if (mapa[contaminacionPosY][contaminacionPosX] == 2)break;

			}
			mapa[contaminacionPosY][contaminacionPosX] = 4;
			Console::SetCursorPosition(contaminacionPosX, contaminacionPosY);
			Console::BackgroundColor = ConsoleColor::DarkBlue;
			cout << " ";
		}

		// **************************************************************************************************************************************************************




		temporizador++;
		temporizadorBonificacion++;
		_sleep(20);

		// ******************************************************************   Pantalla GAME OVER    ******************************************************************
		if (Perder) {
			GAMEOVER();
			break;
		}
		// **************************************************************************************************************************************************************

	}
	system("pause>null");
	return 0;
}