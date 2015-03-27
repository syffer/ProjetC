#ifndef _joueur
    #define _joueur

// windows de merde qui n'est pas foutu d'avoir <dlfcn.h>
#ifdef _WIN32
	#include <windows.h>

	#define Librairie HMODULE
	#define chargerLibrairie(nomLib) LoadLibrary(nomLib)
	#define TypeFonction FARPROC
	#define extraireLibrairie(libType, nomFonction) GetProcAddress(libType, nomFonction)
	#define fermerLibrairie(libType) FreeLibrary(libType)

	char* getError();

#else
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


Joueur* chargerJoueur( char nomLibrairie[] );
int dlerrorDetectee();
void libererJoueur( Joueur* joueur );




#endif
