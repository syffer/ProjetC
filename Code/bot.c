
#include "backgammon.h"
#include <stdio.h>
#include <string.h>

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
	
	//printf("InitLibrary\n");
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
	//printf("StartMatch\n");
	score = target_score;
}


/**
 * Initialiser l'IA pour une manche (d'un match)
 */
void StartGame(Player p) {
	//printf("StartGame\n");
	maCouleur = p;
}


/**
 * Fin d'une manche (d'un match)
 */
void EndGame() {
	//printf("EndGame\n");
}


/**
 * Fin d'un match
 */
void EndMatch() {
	//printf("EndMatch\n");


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
	printf("DoubleStack\n");
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
	//printf("TakeDouble\n");
	return(1);
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
	printf("PlayTurn\n");


	if( dices[0] == dices[1] ) {
		printf("dedoublement des des/dices \n");
	}


}





