#ifndef _Coup
	#define _Coup


#include "../Commun/backgammon.h"
#include "GameState.h"

// combinaison de mouvements
struct Coup {
	
	// les mouvements effectués
	SMove mouvements[4];
	int nbMouvements;
	Player maCouleur;

	// l'état du jeu après avoir effectué les mouvements
	SGameState gameState;
	unsigned char dices[4];

	// caracteristiques d'un coup
	int nbCasesSecurisees;
	int nbCases2Pions;
	int ennemisAManger;
	double probabilitePertePion;
	
};
typedef struct Coup Coup;




void initialiserCoup( Coup* coup, SGameState gameState, unsigned char dices[4], Player maCouleur );
void ajouterMouvementAuCoup( Coup* coup, SMove mouvement, int numeroDeUtilise );
void afficherCoup( Coup* coup );
void calculerCaracteristiquesCoup( Coup* coup );


// fonctions de comparaison de coup
int comparerCoups_CasesRepas( Coup* c1, Coup* c2 );
int comparerCoups_CasesSecurisees( Coup* c1, Coup* c2 );
int comparerCoups_PionsAdverseSorties( Coup* c1, Coup* c2 );
int comparerCoup_Cases2Dames( Coup* c1, Coup* c2 );
int comparerCoups_ProbabilitesPertePion( Coup* c1, Coup* c2 );
int comparerCoups_Securitee( Coup* c1, Coup* c2 );
int comparerCoups_BotParfait( Coup* c1, Coup* c2 );


//int comparerMeilleurCoup( Coup* c1, Coup* c2 );
int comparerAntiJeu( Coup* c1, Coup* c2 );


#endif