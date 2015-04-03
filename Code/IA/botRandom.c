
/*

	Bot jouant aléatoirement 
	Bot non fini

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
	// on a enlever les 'const' de 'dameState' pour pouvoir le manipuler

	*nbMove = 0;
	
	Player maCouleur = bot.maCouleur;
	printf(" je suis %i \n", maCouleur );

	unsigned char lesDes[4];
	getDices( dices, lesDes );

	ListeChainee* coups = creerListeChainee();
	Cellule* cellule = getPremierElement(coups);
	Coup coup_aleatoire;

	calculerCoupsPossibles( gameState, maCouleur, lesDes, coups );
	
	int aleatoire = random_bot(0,getNbElements(coups));
	
	printf("YOLO %i // %i\n",aleatoire,getNbElements(coups));
	
	while( aleatoire>0) 
	{
		cellule = getCelluleSuivante(cellule);
		aleatoire--;
	}
	coup_aleatoire = getDonnee(cellule);
	
	*nbMove = coup_aleatoire.nbMouvements;

	int i;
	for( i = 0; i < *nbMove; i++ ) {
		moves[i] = coup_aleatoire.mouvements[i];
	}

	afficherCoup(coup_aleatoire);
	
	printf("___fin___\n");
}