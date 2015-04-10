/*
	Bot ayant pour but de gagner le match au premier tour en trichant.
	
	Ce bot va essayer de modifier les valeurs de la variable GameState, 
	mais ne donne pas de mouvements à l'arbitre.
	
*/

#include <stdio.h>
#include <string.h>

#include "../Commun/backgammon.h"
#include "fonctionsBot.h"

static Bot bot;

/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary( char name[50] ) {
	printf("InitLibrary\n");
	strcpy( bot.nom, "TricheurBot" );
	bot.maCouleur = NOBODY;
	bot.scoreCible = 0;	
	strcpy( name, bot.nom );
}

/**
 * Initialiser l'IA pour un match
 * @param const unsigned int target_score
 *	score cible pour gagner un match
 */
void StartMatch( const unsigned int target_score ) {
	printf("StartMatch\n");
	bot.scoreCible = target_score;
}

/**
 * Initialiser l'IA pour une manche (d'un match)
 */
void StartGame(Player p) {
	printf("StartGame\n");
	bot.maCouleur = p;
}

/**
 * Fin d'une manche (d'un match)
 */
void EndGame() {
	printf("EndGame\n");
}


/**
 * Fin d'un match
 */
void EndMatch() {
	printf("EndMatch\n");
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
	printf("TakeDouble\n");
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
void PlayTurn( SGameState * gameState, unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	printf("PlayTurn\n");

	Player maCouleur = bot.maCouleur;
	Player couleurAdverse = (maCouleur == BLACK) ? WHITE : BLACK;

	// on met tous nos pions sur la sortie
	gameState -> out[ maCouleur ] = 15;
	gameState -> out[ couleurAdverse ] = 0;

	// on met tous les pions de l'adversaire sur la barre
	gameState -> bar[ maCouleur ] = 0;
	gameState -> bar[ couleurAdverse ] = 15;

	// on efface les pions du plateau
	int i;
	Square* laCase;
	for( i = 0; i < 24; i++ ) {
		laCase = &(gameState -> board[i]);
		laCase -> owner = NOBODY;
		laCase -> nbDames = 30;
	}

	// on modifie le score des joueurs
	if( maCouleur == BLACK ) {
		gameState -> blackScore += bot.scoreCible;
		gameState -> whiteScore = 0;
	}
	else {
		gameState -> whiteScore += bot.scoreCible;
		gameState -> blackScore = 0;
	}

	// on essaie de rejouer juste après
	gameState -> turn = couleurAdverse;

	*nbMove = 0;
}