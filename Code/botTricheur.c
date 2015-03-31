
/*

	Bot ayant pour but de gagner le match au premier tour en trichant.

*/

#include <stdio.h>
#include <string.h>

#include "backgammon.h"



char nom[] = "TricheurBot";
unsigned int score;
static Player maCouleur;


/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary( char name[50] ) {
	strcpy( name, nom );
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
	maCouleur = NOBODY;
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


/**
 * Prise de décision de la part de l'IA
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @param SMove moves[4]
 *	tableau des mouvements à effectuer par l'IA
 * @param unsigned int tries
 *	nombre d'essais restants (3 initialement).
 */
void PlayTurn( SGameState * gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	
	Player couleurAdverse = (maCouleur == BLACK) ? WHITE : BLACK;

	gameState -> out[ maCouleur ] = 15;
	gameState -> out[ couleurAdverse ] = 0;

	gameState -> bar[ maCouleur ] = 0;
	gameState -> bar[ couleurAdverse ] = 15;

	int i;
	Square laCase;
	for( i = 0; i < 24; i++ ) {
		laCase = gameState -> board[i];
		laCase.owner = NOBODY;
		laCase.nbDames = 30;
	}

	if( maCouleur == BLACK ) {
		gameState -> blackScore += 100;
		gameState -> whiteScore = 0;
	}
	else {
		gameState -> whiteScore += 100;
		gameState -> blackScore = 0;
	}

	gameState -> turn = couleurAdverse;

	*nbMove = 0;

}




