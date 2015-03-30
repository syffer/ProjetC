#ifndef _graphique
	#define _graphique


#ifdef _WIN32
	#include <SDL.h>
#else
	#include "SDL/SDL.h"
#endif


int afficherJeu();
char* retournerPathDe(char dice);
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2);
void remplirCaseX(/*LA STRUCTURE MAGIQUE*/);



#endif
