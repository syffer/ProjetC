/*
	Bot qui calcule tous les coups possibles, et en choisit un selon certain critère
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

	printf("InitLibrary\n");

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
int DoubleStack( SGameState * gameState ) {
	printf("DoubleStack\n");

	int monScore;

	// on récupère les scores
	if( bot.maCouleur == WHITE ) {
		monScore = gameState -> whiteScore;
	}	
	else {
		monScore = gameState -> blackScore;
	}

	// on regarde les points manquants pour atteindre l'objectif
	int scoreRestant = bot.scoreCible - monScore;
	
	// pas la peine de doubler mise si le nombre de points est déjà supérieur au score qu'il nous reste à atteindre
	if ( gameState -> stake >= scoreRestant) return 0;

	// on récupère le placement de nos pions par rapport à la sortie
	int coefficientEloignementOut = getEloignementOut( gameState, bot.maCouleur );
	int coefficientEloignementOut_adverse = getEloignementOut( gameState, getCouleurAdverse(bot.maCouleur) );

	// si nos pions sont près de la sortie et que ce n'est pas le cas de l'adversaire ou si peu de nos pions sont éloignés
	if (coefficientEloignementOut_adverse>0 && coefficientEloignementOut==0) return 1;
	else if (coefficientEloignementOut_adverse>7 && coefficientEloignementOut<3) return 1;
	else return 0;	// dans les autres cas on ne double pas la mise
}

/**
 * Accepter ou refuser la nouvelle mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on accepte la nouvelle mise ; faux sinon
 */
int TakeDouble( SGameState * gameState ) {
	printf("TakeDouble\n");

	int scoreAdverse;

	// on récupère les scores
	if( bot.maCouleur == WHITE ) {
		scoreAdverse = gameState -> blackScore;
	}	
	else {
		scoreAdverse = gameState -> whiteScore;
	}

	// on récupère les points qu'ils manquent
	int scoreRestant_adverse = bot.scoreCible - scoreAdverse;

	if( gameState -> stake >= scoreRestant_adverse ) return 1;	// on n'abandonne pas une partie qui nous fait perdre le match

	// on récupère le placement de nos pions par rapport à la sortie
	int coefficientEloignementOut = getEloignementOut( gameState, bot.maCouleur );
	int coefficientEloignementOut_adverse = getEloignementOut( gameState, getCouleurAdverse(bot.maCouleur) );

	if( coefficientEloignementOut>0 && coefficientEloignementOut_adverse==0 ) return 0; // l'adversaire est avantagé
	else if (coefficientEloignementOut==0 && coefficientEloignementOut_adverse==0){ // cas où la partie est équibilibrée
		if( gameState -> stake*2 >= scoreRestant_adverse ) return 0; // si cela peut permettre de faire gagner l'adversaire alors abandonner
		else return 1; // sinon accepter
	}
	else if (coefficientEloignementOut==0) return 1; // on a l'avantage
	else if (coefficientEloignementOut<coefficientEloignementOut_adverse && coefficientEloignementOut<4) return 1; // si il nous reste moins de pions à ramener que l'adversaire et qu'ils sont peu nombreux
	else return 0; // sinon on refuse
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

	// on recalcule les dés, il y en a 4 au maximum
	unsigned char lesDes[4];
	getDices( dices, lesDes );

	// on calcule tous les coups possibles
	ListeChainee* coups = creerListeChainee();
	calculerCoupsPossibles( gameState, maCouleur, lesDes, coups );

	// on en choisit un parmi tous les coups possible, selon un certain critère
	Coup coupChoisi;
	if( getDonneeMax( coups, comparerCoups_Securitee, &coupChoisi ) ) {		// si une erreur apparait, la liste est vide, et donc pas de coup possible
		*nbMove = 0;
		return;
	}

	// on place les mouvements du coup dans le tableau envoyé à l'arbitre
	*nbMove = coupChoisi.nbMouvements;

	int i;
	for( i = 0; i < *nbMove; i++ ) {
		moves[i] = coupChoisi.mouvements[i];
	}

	printf( "(%s) je joue le coup suivant : \n", bot.nom );
	afficherCoup(&coupChoisi);

	detruireListeChainee(coups);
}