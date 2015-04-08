/*

	Fichier regroupant toutes les fonctions concernant la structure Coup

*/
#ifndef _Coup
	#define _Coup


#include "../Commun/backgammon.h"
#include "GameState.h"



/*
	Structure combinaison (de mouvements).
	Une combinaison représente une liste de mouvements que l'on aura effectué sur l'état du jeu
*/
struct Coup {
	
	// les mouvements effectués
	SMove mouvements[4];
	int nbMouvements;

	// l'état du jeu après avoir effectué les mouvements
	SGameState gameState;
	unsigned char dices[4];
	Player maCouleur;

	// caracteristiques d'un coup
	int ennemisAManger;
	int nbCasesSecurisees;				// le nombre de cases ayant plus de 2 pions (pour un joueur donné)
	int nbCases2Pions;					// le nombre de cases ayant exactement 2 pions (pour un joueur donné)
	double probabilitePertePion;		// probabilité de perdre un pion au prochain tour (pour un joueur donné)
	
};
typedef struct Coup Coup;




void initialiserCoup( Coup* coup, SGameState gameState, unsigned char dices[4], Player maCouleur );
void ajouterMouvementAuCoup( Coup* coup, SMove mouvement, int numeroDeUtilise );
void afficherCoup( Coup* coup );
void calculerCaracteristiquesCoup( Coup* coup );


int comparerEntier( int e1, int e2 );
int comparerDouble( double d1, double d2 );



/*
	fonctions de comparaison de coups

	ces fonctions renveront :
	- 1 	si c1 > c2
	- 0 	si c1 == c2
	- -1	si c1 < c2

*/
int comparerCoups_nbMouvements( Coup* c1, Coup* c2 );
int comparerCoups_CasesRepas( Coup* c1, Coup* c2 );
int comparerCoups_CasesSecurisees( Coup* c1, Coup* c2 );		// on compare les coups en fonctions de leurs nombre de cases sécurisées 
int comparerCoups_PionsAdverseBarre( Coup* c1, Coup* c2 );		// 								     				 de pions adverse sur la barre
int comparerCoups_PionsSorties( Coup* c1, Coup* c2 );			// 								     				 de pions sortie du plateau
int comparerCoup_Cases2Dames( Coup* c1, Coup* c2 );				// 									 				 de cases possèdant exactement 2 pions
int comparerCoups_ProbabilitesPertePion( Coup* c1, Coup* c2 );	//									 de la probabilité de perdre un pion au prochain tour
int comparerCoups_Securitee( Coup* c1, Coup* c2 );				// on compare les coups en fonctions de plusieurs critères, permettant de définir quel coup est le moins dangereux



//int comparerMeilleurCoup( Coup* c1, Coup* c2 );
int comparerAntiJeu( Coup* c1, Coup* c2 );
int comparerCoups_BotParfait( Coup* c1, Coup* c2 );

#endif