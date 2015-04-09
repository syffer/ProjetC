/*
	Bot fusion de AntiJeu & Lynx
*/

#include <stdio.h>
#include <string.h>

#include "../Commun/backgammon.h"
#include "ListeChainee.h"
#include "fonctionsBot.h"


static Bot bot;



/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary( char name[50] ) {

	printf("InitLibrary\n");

	strcpy( bot.nom, "PerfectBot" );
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
	printf("EndGame\n");
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
void PlayTurn( SGameState * gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	printf("PlayTurn\n");
	Player maCouleur = bot.maCouleur;
	printf("(%s) je suis %i \n", bot.nom, maCouleur );

	// on récupère les dés
	unsigned char lesDes[4];
	getDices( dices, lesDes );

	// on regarde les coups possibles
	ListeChainee* coups = creerListeChainee();
	calculerCoupsPossibles( gameState, maCouleur, lesDes, coups );

	// on cherche le meilleur coup
	Coup meilleurCoup;
	if( getDonneeMax( coups, comparerCoups_BotParfait, &meilleurCoup ) ) {		// si une erreur apparait, la liste est vide, et donc pas de coup possible
		*nbMove = 0;
		return;
	}

	*nbMove = meilleurCoup.nbMouvements;
	int i;

	for( i = 0; i < *nbMove; i++ ) {
		moves[i] = meilleurCoup.mouvements[i];
	}

	printf( "(%s) je joue le coup suivant : \n", bot.nom );
	afficherCoup(&meilleurCoup);
	detruireListeChainee(coups);
}