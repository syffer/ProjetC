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
void remplirCaseX(/*LA STRUCTURE MAGIQUE*/);

typedef struct{

    SDL_Rect* posPion;
    SDL_Surface* imagePion;

}Pion;

typedef struct{

    int posX;
    int posY;
    Pion tabPions[15];
    int nbPions;
}Case;

typedef struct{

    Case tabCases[24];
    int bar[2];
    int out[2];
    int hauteur;
    int largeur;

}Plateau;

Pion creerPion(int posX, int posY, char* image);
void positionnerPion(Pion *pion, Plateau *plateau, Case case_pos, int numCase);
void initCases(Plateau *plateau);
void initPions(Plateau *plateau, SGameState gameState);
void creerPlateau(Plateau *plateau);

#endif
