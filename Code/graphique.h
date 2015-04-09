#ifndef _graphique
	#define _graphique



#include <SDL/SDL_ttf.h>
#include "backgammon.h"

#ifdef _WIN32
    #include <SDL.h>

#else
    #include "SDL/SDL.h"
#endif



#define LARGEUR_CASE        84 // 84 px de large pour chaque case
#define HAUTEUR_CASE        260
#define NB_CASES_LARGEUR    12 // 12 cases de largeur



typedef struct{

    SDL_Rect posPion;
    SDL_Surface* imagePion;

} Pion;

typedef struct{

    int valeur;
    int posX;
    int posY;
    int largeur;
    int hauteur;

} OutGraphique;

typedef struct{

    int posX;
    int posY;
    Pion tabPions[15];
    int nbPions;
    int hauteur;
    int largeur;
    SDL_Surface* imageCase;
} Case;

typedef struct{

    Case tabCases[24];
    int bar[2];
    int out[2];
    int hauteur;
    int largeur;
    OutGraphique outGraphique[2];

} Plateau;

typedef struct{

    int source;
    int dest;
    Plateau plateau;

} Deplacement;




int initialiserFenetre();
void fermerFenetre();
void initialiserPlateauGraphique( SGameState* gameState );
void updateDesGraphique( unsigned char dices[2] );
void deplacerPionGraphique(SMove move, Player couleur);
void updateTourJoueurGraphique( Player joueur );
void updateScoreJoueurBlanc(int score);
void updateScoreJoueurNoir(int score);
void updateScoreCibleGraphique( int scoreCible );
void updateMiseCouranteGraphique( int nouvelleMise );


// pour libJoueur.h
int selectionnerCaseGraphique();
void ouvrirFenetreDoublerMiseGraphique();
void ouvrirFenetreAccepterDoublerMise();
int getChoixUtilisateurGraphique();



void pause();   // a virer plus tard



Pion creerPion(int posX, int posY, char* image);
SDL_Rect positionnerPion(Case *case_pos, int numCase);
void initCases(Plateau *plateau);
void initPions(Plateau *plateau, SGameState gameState);
void creerPlateau(Plateau *plateau);
void deplacerPionVers(Pion *pion);
void updateOutGraphic(int numJoueur);
int retournerNumCase(int sourisX, int sourisY, Plateau plateau);
void drawEmptyRect(SDL_Surface* surf,int posX, int posY, int width, int length, int R, int G, int B);

char* retournerPathDe(char dice);
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2);




#endif
