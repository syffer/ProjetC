#ifndef _graphique
	#define _graphique
	#include "../Commun/backgammon.h"


//#include "SDL/SDL.h"

/*
int afficherPlateau();
char* retournerPathDe(char dice);
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2);
*/

void remplirCaseX( int laCase, int couleur, int nbDames );
void afficherDeplacementX(SMove move);


#endif
