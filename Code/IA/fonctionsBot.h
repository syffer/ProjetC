#ifndef _fonctionsBot
	#define _fonctionsBot


#include "../Commun/backgammon.h"
#include "ListeChainee.h"




// signature des fonctions communes
struct Bot {
	
	char nom[50];
	Player maCouleur;
	unsigned int scoreCible;
	
	SGameState gameState;	  // ?? va t'on l'utiliser ?
	
};
typedef struct Bot Bot;



void getDices( const unsigned char dices[2], unsigned char newDices[4] );

Square getCaseReelle( SGameState* gameState, Player maCouleur, int i );
int possedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur );
int peutDeplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases );
void deplacerUnPion( SGameState* gameState, Player maCouleur, SMove mouvement );

void afficherGameState( SGameState gameState );



void initialiserMouvement( SMove* mouvement, Player maCouleur, int depart, int nbCases );


void initialiserCoup( Coup* coup, SGameState gameState, unsigned char dices[4] );
void ajouterMouvementAuCoup( Coup* coup, SMove mouvement );
void afficherCoup( Coup coup );


void calculerCoupsPossiblesSuivants( Player maCouleur, ListeChainee* listeCoups );
void calculerCoupsPossiblesInitiaux( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups );
void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups );
void afficherCoup( Coup coup );
void afficherCoups( ListeChainee* listeCoups );


int random_bot(int min,int max);
int calculerCout( SGameState* gameState ); 		//  <----------------------------- que fait elle ??? ou plutot, quelle est la raison de son existance ?
int getNbPointsPrit( SGameState* gameState );

/*
	retourne :
		- 1 si le c1 > c2
		- 0 si c1 == c2
		- -1 si c1 < c2
*/
typedef int (fonctionComparaisonCoups)(Coup c1, Coup c2);
int comparerAntiJeu( Coup c1, Coup c2 );
int comparerMeilleurCoup( Coup c1, Coup c2 );
int comparerDeuxCoups( Coup c1, Coup c2 );

int calculerMeilleurCoup( SGameState* gameState );



int getCoupMaximum( ListeChainee* listeCoups, fonctionComparaisonCoups f_compraison, Coup* coupMaximum );





#endif