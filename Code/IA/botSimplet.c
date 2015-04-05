
/*

	Bot ne faisant qu'avancer ses pions les plus éloignés.
	Bot non fini (manque la gestion du videau)
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
	
	strcpy( bot.nom, "SimpleBot" );
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
	// la couleur ne change pas apparemment
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
	// on a enlever les 'const' de 'gameState' pour pouvoir le manipuler
	
	*nbMove = 0;

	Player maCouleur = bot.maCouleur;

	// on est obligé d'utiliser tout les dés SAUF lorsque ce n'est pas possible....
	unsigned char mesDes[4];
	getDices( dices, mesDes );
	SMove mouvement;


	// si je n'ai pas utilisé tout mes dés, et qu'il n'y a plus rien en dehors du plateau

	int i, j;
	int position;

	for( i = 0; i < 25; i++ ) {

		if( joueurPossedeDesPionsSurLaBarre(gameState,maCouleur) && i != 0 ) break;

		if( maCouleur == WHITE || i == 0 ) position = i; 	// je suis le WHITE, ou je suis sur la barre
		else position = 24 - i;


		for( j = 0; j < 4; j++ ) {
		
			if( peutDeplacerUnPion(gameState, maCouleur, position, mesDes[j] ) ) {

				printf(" -> je bouge un pion de la case %i de %i cases \n", position, mesDes[j] );


				initialiserMouvement( &mouvement, maCouleur, position, mesDes[j] );

				moves[ *nbMove ] = mouvement;
				*nbMove += 1;

				deplacerUnPion( gameState, maCouleur, mouvement );
				
				mesDes[j] = 0;

			}

		}


	}



}




