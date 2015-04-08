/*
	
	Fichier contenant la structure Bot, et les fonctions de calcul des différents coups possibles
	(utilise à la fois le fichier Coup.h et ListeChainee.h) 

*/
#ifndef _fonctionsBot
	#define _fonctionsBot



#include "../Commun/backgammon.h"

#include "GameState.h"
#include "Coup.h"
#include "ListeChainee.h"



/*
	Structure Bot.

	Cette structure stockera les différentes variables utilisées par un bot 
	(son nom, sa couleur)

*/
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