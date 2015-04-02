#ifndef _fonctionsBot
	#define _fonctionsBot


#include "backgammon.h"
#include "ListeChainee.h"


// signature des fonctions communes
struct Bot {
	
	char nom[50];
	Player maCouleur;
	unsigned int scoreCible;	// ??
	
	SGameState gameState;	   // ??
	
};
typedef struct Bot Bot;




// combinaison de mouvements
struct Coup {
	
	SMove mouvements[4];
	int nbMouvements;

};
typedef struct Coup Coup;



ListeChainee* getDices( const unsigned char dices[2] );





#endif