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

/*
* Démarrer la SDL, charger l'écran et le plateau
*/
int afficherJeu(SDL_Surface *tabafree[]);


char* retournerPathDe(char dice);
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2);


typedef struct{

    SDL_Rect* posPion;
    SDL_Surface* imagePion;

}Pion;

void creerPion(Pion pions[30], int positionPion, int posX, int posY, char* image);
void positionnerPion(Pion *pion, SDL_Rect *pos);

//A implémenter
void remplirCaseX(Square* laCase, Player couleurJoueur, int nbDames); //remplir la case de N pions de couleur donnée en param
void afficherTitre(); //affiche un titre sur le plateau annonçant le tour du joueur ou le début de la partie
void actualiserDes(unsigned char dices[2]);
void afficherDeplacementX(SMove move);



#endif
