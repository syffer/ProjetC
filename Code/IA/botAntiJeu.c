
/*

	Bot dont le but est de gagner en bloquant au maximum le coup de ses adversaires
	Bot non fini

*/


#include <stdio.h>
#include <string.h>

#include "../Commun/backgammon.h"
#include "ListeChainee.h"
#include "fonctionsBot.h"

static Bot bot;

char nom[] = "AntiJeuBot";
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
// !!!!!!!!!!!!!!!!!!! on a enlevé les const pour pouvoir modifier gameState
void PlayTurn( SGameState * gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	

	Player maCouleur = bot.maCouleur;
	printf("(%s) je suis %i \n", bot.nom, maCouleur );

	unsigned char lesDes[4];
	getDices( dices, lesDes );

	
	ListeChainee* coups = creerListeChainee();
	calculerCoupsPossibles( gameState, maCouleur, lesDes, coups );


	Coup meilleurCoup;
	if( getDonneeMax( coups, comparerAntiJeu, &meilleurCoup ) ) {		// si une erreur apparait, la liste est vide, et donc pas de coup possible
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