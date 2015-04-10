/*
	Fichier contenant toutes les fonctions concernant le chargement des libraires.
	Les fonctions d'une librairie chargée seront stockées dans une structure Joueur, 
	celle-ci ne contient que des pionteurs de fonctions.
	
	Auteurs :
	- Pauline HOULGATTE
	- Maxime PINEAU	

*/

#ifndef _joueur
    #define _joueur

// les fonctions chargeant les librairies dépendent de l'OS utilisé
#ifdef _WIN32
	#include <windows.h>

	#define Librairie HMODULE
	#define chargerLibrairie(nomLib) LoadLibrary(nomLib)
	#define TypeFonction FARPROC
	#define extraireLibrairie(libType, nomFonction) GetProcAddress(libType, nomFonction)
	#define fermerLibrairie(libType) FreeLibrary(libType)

	char* getError();

#endif

#ifdef linux
	#include <dlfcn.h>

	#define Librairie void*
	#define chargerLibrairie(nomLib) dlopen( nomLib, RTLD_LOCAL || RTLD_LAZY ) 		// http://stackoverflow.com/questions/3433522/loading-two-instances-of-a-shared-library
	#define TypeFonction void
	#define extraireLibrairie(libType, nomFonction) dlsym(libType, nomFonction)
	#define fermerLibrairie(libType) dlclose(libType)
	#define getError() dlerror()
#endif


#include "backgammon.h"



struct Joueur {

	int estUnBot;

	Librairie librairie;

	pfInitLibrary InitLibrary;
	pfStartMatch StartMatch;
	pfStartGame StartGame;
	pfEndGame EndGame;
	pfEndMatch EndMatch;
	pfDoubleStack DoubleStack;
	pfTakeDouble TakeDouble;
	pfPlayTurn PlayTurn;
};
typedef struct Joueur Joueur;


Joueur chargerJoueur( char nomLibrairie[] );
Joueur chargerJoueurReel();
int dlerrorDetectee();
void libererJoueur( Joueur joueur );




#endif