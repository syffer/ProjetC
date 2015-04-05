
/*

	Bot qui calcul touts les coups possibles, et en choisis un selon certain critère
	
	
	CE QUIL MANQUE :
		- gestion du videau (doubler la mise, accepter la mise)
		- faire une meilleur fonction de comparaison des coups


*/


#include <stdio.h>
#include <string.h>

#include "../Commun/backgammon.h"
#include "fonctionsBot.h"
#include "ListeChainee.h"


static Bot bot;


/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary( char name[50] ) {
	
	strcpy( bot.nom, "LynxBot" );
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
	bot.scoreCible = target_score;
}


/**
 * Initialiser l'IA pour une manche (d'un match)
 */
void StartGame(Player p) {
	bot.maCouleur = p;
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
	// on a enlever les 'const' de 'gameState' pour pouvoir le manipuler

	*nbMove = 0;

	Player maCouleur = bot.maCouleur;

	// on recalcul les dés, il y en a 4 au maximum
	unsigned char lesDes[4];
	getDices( dices, lesDes );

	// on calcul tout les coups possibles
	ListeChainee* coups = creerListeChainee();
	calculerCoupsPossibles( gameState, maCouleur, lesDes, coups );

	// on en choisi un parmit tout les coups possible, selon un certain critère
	Coup meilleurCoup;
	getCoupMaximum( coups, comparerDeuxCoups, &meilleurCoup );


	// on plase les mouvements du coup dans le tableaux envoyé à l'arbitre
	*nbMove = meilleurCoup.nbMouvements;

	int i;
	for( i = 0; i < *nbMove; i++ ) {
		moves[i] = meilleurCoup.mouvements[i];
	}

	afficherCoups(coups);
	
	detruireListeChainee(coups);
}








