
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

	int monScore;
	int scoreAdverse;

	if( bot.maCouleur == WHITE ) {
		monScore = gameState -> whiteScore;
		scoreAdverse = gameState -> blackScore;
	}	
	else {
		monScore = gameState -> blackScore;
		scoreAdverse = gameState -> whiteScore;
	}

	int scoreRestant = bot.scoreCible - monScore;
	int scoreRestant_adverse = bot.scoreCible - scoreAdverse;


	if( gameState -> stake * 2 >= scoreAdverse ) return 0;

	



	int coefficientEloignementOut = getCoefficientEloignementOut( gameState, bot.maCouleur );
	int coefficientEloignementOut_adverse = getCoefficientEloignementOut( gameState, getCouleurAdverse(bot.maCouleur) );

	if( coefficientEloignementOut > 90 ) return 0;
	else return 1;	// on double la mise si il n'y a plus beaucoup de pions

}


/**
 * Accepter ou refuser la nouvelle mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on accepte la nouvelle mise ; faux sinon
 */
int TakeDouble( const SGameState * const gameState ) {

	int monScore;
	int scoreAdverse;

	if( bot.maCouleur == WHITE ) {
		monScore = gameState -> whiteScore;
		scoreAdverse = gameState -> blackScore;
	}	
	else {
		monScore = gameState -> blackScore;
		scoreAdverse = gameState -> whiteScore;
	}

	int scoreRestant = bot.scoreCible - monScore;
	int scoreRestant_adverse = bot.scoreCible - scoreAdverse;


	if( gameState -> stake >= scoreRestant_adverse ) return 1;	// on abandonne pas une partie qui nous fait perdre le match

	//if( monScore < scoreAdverse ) return 1;


	int coefficientEloignementOut = getCoefficientEloignementOut( gameState, bot.maCouleur );
	int coefficientEloignementOut_adverse = getCoefficientEloignementOut( gameState, getCouleurAdverse(bot.maCouleur) );

	if( coefficientEloignementOut > 90 ) {

		if( coefficientEloignementOut_adverse > 90 ) return 1;	// partie équilibrée
		else return 0;		// l'adversaire a l'avantage 
	}
	else {

		if( coefficientEloignementOut_adverse > 90 ) return 1;	// j'ai l'avantage
		else return 1;		// partie équilibrée
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
void PlayTurn( SGameState * gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	// on a enlever les 'const' de 'gameState' pour pouvoir le manipuler


	Player maCouleur = bot.maCouleur;

	// on recalcul les dés, il y en a 4 au maximum
	unsigned char lesDes[4];
	getDices( dices, lesDes );

	// on calcul tout les coups possibles
	ListeChainee* coups = creerListeChainee();
	calculerCoupsPossibles( gameState, maCouleur, lesDes, coups );


	// on en choisi un parmit tout les coups possible, selon un certain critère
	Coup coupChoisi;
	if( getDonneeMax( coups, comparerCoups_Securitee, &coupChoisi ) ) {		// si une erreur apparait, la liste est vide, et donc pas de coup possible
		*nbMove = 0;
		return;
	}


	// on plase les mouvements du coup dans le tableaux envoyé à l'arbitre
	*nbMove = coupChoisi.nbMouvements;

	int i;
	for( i = 0; i < *nbMove; i++ ) {
		moves[i] = coupChoisi.mouvements[i];
	}

	//afficherCoups(coups);

	afficherCoup(&coupChoisi);
	
	detruireListeChainee(coups);
}








