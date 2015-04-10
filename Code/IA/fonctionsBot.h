/*
	Fichier contenant la structure Bot, et les fonctions de calcul des différents coups possibles
	(utilise à la fois le fichier Coup.h et ListeChainee.h) 

	Auteurs :
	- Pauline HOULGATTE
	- Maxime PINEAU	

*/

#ifndef _fonctionsBot
	#define _fonctionsBot

#include "../Commun/backgammon.h"
#include "GameState.h"
#include "Coup.h"
#include "ListeChainee.h"

/** Structure d'un bot
 * @attribut nom : le nom du bot
 * @attribut maCouleur : sa couleur
 * @attribut scoreCible : le score à atteindre
 * */
struct Bot {
	char nom[50];
	Player maCouleur;
	unsigned int scoreCible;

};
typedef struct Bot Bot;


void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups );
void calculerCoupsPossiblesInitiaux( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups );
void calculerCoupsPossiblesSuivants( Player maCouleur, ListeChainee* listeCoups );
void calculerCaracteristiquesCoups( ListeChainee* listeCoups );
void afficherCoups( ListeChainee* listeCoups );


#endif