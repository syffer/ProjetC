
#include <stdio.h>
#include <string.h>

#include "backgammon.h"


//////////////////////////////////////////////////////////
// Dans la librairie
//

unsigned int score;
static Player maCouleur;


/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary( char name[50] ) {
	strcpy(name,"AlphaBot");
	score = 0;
	maCouleur = NOBODY;
}


/**
 * Initialiser l'IA pour un match
 * @param const unsigned int target_score
 *	score cible pour gagner un match
 */
void StartMatch( const unsigned int target_score ) {
	score = target_score;
}


/**
 * Initialiser l'IA pour une manche (d'un match)
 */
void StartGame(Player p) {
	maCouleur = p;
}


/**
 * Fin d'une manche (d'un match)
 */
void EndGame() {
}


/**
 * Fin d'un match
 */
void EndMatch() {

	///////////////////////////////////////////////
	// LIBERATION PROPRE DE TOUTES LES RESSOURCES
	//						TOUTES
	///////////////////////////////////////////////
}


/**
 * Doubler la mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on propose de doubler : faux sinon
 */
int DoubleStack( const SGameState * const gameState ) {
	// on ne double jamais la mise
	return(0);		
}


/**
 * Accepter ou refuser la nouvelle mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on accepte la nouvelle mise ; faux sinon
 */
int TakeDouble( const SGameState * const gameState ) {
	// on ne refuse jamais la nouvelle mise
	return(1);
}


















void getDeplacements( const unsigned char dices[2], unsigned char deplacements[4], int *nbDeplacements ) {

	// on a fait un double (exemple : 1-1 , 2-2 , ... 6-6 )
	if( dices[0] == dices[1] ) {
		*nbDeplacements = 4;
		int i;
		for( i = 0; i < 4; i++ ) deplacements[i] = dices[0];
	}
	else {
		*nbDeplacements = 2;
		deplacements[0] = dices[0];
		deplacements[1] = dices[1];
	}

}





/**
 * Prise de décision de la part de l'IA
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @param SMove moves[4]
 *	tableau des mouvements à effectuer par l'IA
 * @param unsigned int tries
 *	nombre d'essais restants (3 initialement).
 */
void PlayTurn( const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	
	//printf("PlayTurn\n");

	unsigned char deplacements[4];
	int nbDeplacements;
	
	getDeplacements( dices, deplacements, &nbDeplacements );


	// on est obligé d'utiliser tout les dés SAUF lorsque ce n'est pas possible....

}




