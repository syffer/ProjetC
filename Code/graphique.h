#ifndef _graphique
	#define _graphique


#ifdef _WIN32
	#include <SDL.h>
#else
	#include "SDL/SDL.h"
#endif

#include "backgammon.h"

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define TAILLE_CASE      80 // 80 px de large pour chaque case
    #define NB_CASES_LARGEUR 12 // 12 cases de largeur

#endif // DEF_CONSTANTES
int afficherJeu();
char* retournerPathDe(char dice);
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2);

typedef struct{

    SDL_Rect* posPion;
    SDL_Surface* imagePion;

}Pion;

void creerPion(Pion pions[30], int positionPion, int posX, int posY, char* image);
void positionnerPion(Pion *pion, SDL_Rect *pos);

#endif
