
/*

	Bot ne faisant qu'avancer ses pions les plus éloignés.

*/

#include <stdio.h>
#include <string.h>

#include "backgammon.h"
#include "ListeChainee.h"
#include "fonctionsBot.h"


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
	
	printf("debut\n");

	*nbMove = 0;

	Player maCouleur = bot.maCouleur;

	// // on est obligé d'utiliser tout les dés SAUF lorsque ce n'est pas possible....
	// ListeChainee* mesDes = getDices( dices ); 	// mes dés
	
	// printf("INCICICIC\n");
	
	// Cellule* dice;	// variable utilisée pour parcourir la liste des dés.
	// Cellule* tmp;
	// SMove mouv;

	// // on est obligé de remettre en jeu TOUS nos pions
	// if( possedeDesPionsSurLaBarre(gameState,maCouleur) ) {

	// 	printf(" -> je dois rerentrer les pions sortis du plateau...\n");

	// 	dice = getPremierElement(mesDes);
	// 	while( gameState -> bar[maCouleur] ) {

	// 		if( !dice ) break;

	// 		if( peutDeplacerUnPion( gameState, maCouleur, 0, getDonnee(dice) ) ) {
				
	// 			moves[ *nbMove ] = creerMouvementJoueur( maCouleur, 0, getDonnee(dice) );
	// 			deplacerUnPion( *gameState, maCouleur, moves[*nbMove], gameState );
	// 			*nbMove++;

	// 			dice = getCelluleSuivante(dice);
	// 			detruireCellule( mesDes, getCellulePrecedente(dice) );
	// 		}
	// 		else dice = getCelluleSuivante(dice);
	// 	}

	// }



	
	// regarder si, avec les dés, on peut :
	// - prendre un pion adverse
	// - prendre un point (au moins deux pions sur le même triangle)
	// (- créer une ancre ?)
	


	// // si j'ai utilisé tout mes dés, ou qu'il y a encore des pions sur la barre (alors que j'ai utilisé tout les dés)
	// if( listeEstVide(mesDes) || possedeDesPionsSurLaBarre(gameState,maCouleur) ) return;


	// // si je n'ai pas utilisé tout mes dés, et qu'il n'y a plus rien en dehors du plateau

	// int i;
	// int position;

	// for( i = 1; i < 25; i++ ) {

	// 	if( listeEstVide(mesDes) ) break;

	// 	dice = getPremierElement(mesDes);
	// 	while( dice ) {
		
	// 		position = (maCouleur == WHITE) ? i : 25 - i;

	// 		if( peutDeplacerUnPion(gameState, maCouleur, position, getDonnee(dice) ) ) {

	// 			printf(" -> je bouge un pion de la case %i de %i cases \n", position, getDonnee(dice) );

	// 			moves[ *nbMove ] = creerMouvementJoueur( maCouleur, 0, getDonnee(dice) );
	// 			deplacerUnPion( *gameState, maCouleur, moves[*nbMove], gameState );
	// 			*nbMove++;

	// 			tmp = dice;
	// 			dice = getCelluleSuivante(dice);
	// 			detruireCellule( mesDes, tmp );

	// 		}
	// 		else dice = getCelluleSuivante(dice);
	// 	}


	// }



}




