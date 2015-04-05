#ifndef _fonctionsBot
	#define _fonctionsBot


#include "../Commun/backgammon.h"

#include "GameState.h"
#include "Coup.h"
#include "ListeChainee.h"



// signature des fonctions communes
struct Bot {
	
	char nom[50];
	Player maCouleur;
	unsigned int scoreCible;

};
typedef struct Bot Bot;



void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups );
void calculerCoupsPossiblesInitiaux( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups );
void calculerCoupsPossiblesSuivants( Player maCouleur, ListeChainee* listeCoups );





#endif