#ifndef _Coup
	#define _Coup


#include "../Commun/backgammon.h"
#include "GameState.h"

// combinaison de mouvements
struct Coup {
	
	SMove mouvements[4];
	int nbMouvements;

	SGameState gameState;
	unsigned char dices[4];
	
};
typedef struct Coup Coup;




void initialiserCoup( Coup* coup, SGameState gameState, unsigned char dices[4] );
void ajouterMouvementAuCoup( Coup* coup, SMove mouvement );
void afficherCoup( Coup coup );



/////// fonctions de comparaison de coup
int comparerMeilleurCoup( Coup* c1, Coup* c2 );
int comparerAntiJeu( Coup* c1, Coup* c2 );
int comparerDeuxCoups( Coup* c1, Coup* c2 );


#endif