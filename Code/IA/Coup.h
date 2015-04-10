/*
	Fichier regroupant toutes les fonctions concernant la structure Coup
*/

#ifndef _Coup
	#define _Coup

#include "../Commun/backgammon.h"
#include "GameState.h"

/** Structure représentant les mouvements effectués
 * @attribut mouvement : les mouvements effectués
 * @attribut nbMouvements : le nombre de mouvements effectués
 * @attribut gameState : le plateau
 * @attribut dices : les dés
 * @attribut maCouleur : la couleur du joueur
 * @attribut ennemisAManger : les pions adverses (un seul pion sur une case)
 * @attribut nbCasesSecurisees : le nombre de cases ayant plus de 2 pions (pour un joueur donné)
 * @attribut nbCases2Pions : le nombre de cases ayant exactement 2 pions (pour un joueur donné)
 * @attribut probabilitePertePion : probabilité de perdre un pion au prochain tour (pour un joueur donné)
 * */
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
	int nbCasesSecurisees;
	int nbCases2Pions;
	double probabilitePertePion;
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

	ces fonctions renverront :
	- 1 	si c1 > c2
	- 0 	si c1 == c2
	- -1	si c1 < c2

*/
int comparerCoups_nbMouvements( Coup* c1, Coup* c2 );
int comparerCoups_CasesRepas( Coup* c1, Coup* c2 );
int comparerCoups_CasesSecurisees( Coup* c1, Coup* c2 );		// on compare les coups en fonction de leur nombre de cases sécurisées 
int comparerCoups_PionsAdverseBarre( Coup* c1, Coup* c2 );		// 								     				 de pions adverses sur la barre
int comparerCoups_PionsSorties( Coup* c1, Coup* c2 );			// 								     				 de pions sortis du plateau
int comparerCoup_Cases2Dames( Coup* c1, Coup* c2 );				// 									 				 de cases possèdant exactement 2 pions
int comparerCoups_ProbabilitesPertePion( Coup* c1, Coup* c2 );	//									 de la probabilité de perdre un pion au prochain tour
int comparerCoups_Securitee( Coup* c1, Coup* c2 );				// on compare les coups en fonction de plusieurs critères, permettant de définir quel coup est le moins dangereux

int comparerAntiJeu( Coup* c1, Coup* c2 );
int comparerCoups_BotFusion( Coup* c1, Coup* c2 );

#endif