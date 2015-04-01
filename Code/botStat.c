
/*

	Bot dont le comportement se base sur des statistiques

*/

#include <stdio.h>
#include <string.h>

#include "backgammon.h"
#include "ListeChainee.h"


char nom[] = "StatBot";
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


/* ================================ */
void calculerMouvements( SGameState gameState, ListeChainee* dices, SMove mouvements[4], int* nbMouvements ) {


	Square laCase;
	Cellule* leDe;
	Cellule* tmp;
	unsigned char valeurDe;


	// pour chaque case du plateau
	int i;
	for( i = 0; i < 25; i++ ) {

		if( i != 0 ) laCase = gameState.board[ i - 1 ]; 		// cas particulier : la barre est représentée par 0
		else {		
			laCase.owner = maCouleur;
			laCase.nbDames = gameState.bar[ maCouleur ];
		}


		if( gameState.bar[ maCouleur ] && i != 0 ) break;	// il y a des pions sur la barre, je n'ai pas le droit de deplacer autre chose

		if( laCase.owner != maCouleur || laCase.nbDames <= 0 ) continue;	// je n'ai pas de pions sur cette case


		// pour chaque dé de la liste
		leDe = getPremierElement(dices);
		while( leDe ) {

			valeurDe = getDonnee(leDe);

			if( 1 ) {	// si je ne peux pas déplacer un pion avec ce dé
				// j'essaie avec un autre dé

			}
			else {

				detruireCellule( dices, leDe );		// on retire le dé de la liste (car on l'a utilisé)


				// si j'ai encore des dés à jouer
				if( ! listeEstVide(dices) ) {	
					calculerMouvements( gameState, dices, mouvements, nbMouvements );
				
					// créée un couple entre le mouvement actuel et chaque mouvement venant d'être généré
				}


				leDe = ajouterElementDebut( dices, valeurDe ); 	// on remet le dé dans la liste

			}

			leDe = getCelluleSuivante(leDe);
		
		}

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
// !!!!!!!!!!!!!!!!!!! on a enlevé les const pour pouvoir modifier gameState
void PlayTurn( SGameState * gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	

	*nbMove = 0;
	
	/*****
	 * 
	 * 	*nbMove = 0;

	// on est obligé d'utiliser tout les dés SAUF lorsque ce n'est pas possible....
	ListeChainee* mesDes = getDices( dices ); 	// mes dés
	
	
	Cellule* dice;	// variable utilisée pour parcourir la liste des dés.


	// on est obligé de remettre en jeu TOUS nos pions
	if( possedeDesPionsSurLaBarre(gameState) ) {

		printf(" -> je dois rerentrer les pions sortis du plateau...\n");

		dice = getPremierElement(mesDes);
		while( gameState -> bar[maCouleur] ) {

			if( !dice ) break;

			if( peutDeplacerUnPion( gameState, 0, getDonnee(dice) ) ) {
				
				printf("on peut bouger un pion avec ce dé...\n");

				moves[ *nbMove ] = deplacerUnPion( gameState, 0, getDonnee(dice) );
				*nbMove++;
			

				dice = getCelluleSuivante(dice);
				detruireCellule( mesDes, getCellulePrecedente(dice) );
			}
			else dice = getCelluleSuivante(dice);
		}

	}



	
	regarder si, avec les dés, on peut :
	- prendre un pion adverse
	- prendre un point (au moins deux pions sur le même triangle)
	(- créer une ancre ?)
	


	// si j'ai utilisé tout mes dés, ou qu'il y a encore des pions sur la barre (alors que j'ai utilisé tout les dés)
	if( listeEstVide(mesDes) || possedeDesPionsSurLaBarre(gameState) ) return;


	// si je n'ai pas utilisé tout mes dés, et qu'il n'y a plus rien en dehors du plateau

	int i;
	int position;

	for( i = 1; i < 25; i++ ) {

		if( listeEstVide(mesDes) ) break;

		dice = getPremierElement(mesDes);
		while( dice ) {
		
			position = (maCouleur == BLACK) ? i : 24 - i;

			if( peutDeplacerUnPion(gameState, position, getDonnee(dice) ) ) {

				moves[ *nbMove ] = deplacerUnPion( gameState, position, getDonnee(dice) );
				*nbMove++;

				dice = getCelluleSuivante(dice);
				detruireCellule( mesDes, getCellulePrecedente(dice) );
			}
			else dice = getCelluleSuivante(dice);
		}


	}
	 * ****/


}