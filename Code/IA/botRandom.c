/*
	Bot jouant aléatoirement 
	
	Ce bot calcule tous les coups possibles,
	et en tire un aléatoirement.
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
	strcpy( bot.nom, "RandomBot" );
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
void PlayTurn( SGameState * gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	printf("PlayTurn\n");

	Player maCouleur = bot.maCouleur;
	printf("(%s) C'est a mon tour de jouer, je suis %i \n", bot.nom, maCouleur );

	// on recalcule les dés (pour en avoir 4 et non deux)
	unsigned char lesDes[4];
	getDices( dices, lesDes );

	// on calcule tous les coups possibles
	ListeChainee* coups = creerListeChainee();
	calculerCoupsPossibles( gameState, maCouleur, lesDes, coups );

	if( ! getNbElements(coups) ) {	// pas de coup possible s'il n'y a rien dans la liste
		*nbMove = 0;
		return;
	}

	// on en tire un aléatoirement
	int aleatoire = randomINT( 0, getNbElements(coups) - 1 );
	
	Coup coupAleatoire;
	Cellule* cellule = getPremierElement(coups);
	while( cellule ) {
		if( aleatoire == 0 ) {
			coupAleatoire = getDonnee(cellule);
			break;
		}
		cellule = getCelluleSuivante(cellule);
		aleatoire--;
	}

	// il n'y a pas eu d'erreur lors de la récupération du coup aléatoirement
	if( cellule ) {		// != NULL
		*nbMove = coupAleatoire.nbMouvements;
		int i;
		for( i = 0; i < *nbMove; i++ ) {
			moves[i] = coupAleatoire.mouvements[i];
		}
		printf( "(%s) je veux jouer le coup : ", bot.nom );
		afficherCoup(&coupAleatoire);
	}
	else printf( "(%s) Erreur lors du tirage aleatoire du coup\n", bot.nom );

	// on détruit (libère) la liste qui n'est plus utilisée
	detruireListeChainee(coups);
	
	printf( "(%s) j'ai fini de jouer\n", bot.nom );
}