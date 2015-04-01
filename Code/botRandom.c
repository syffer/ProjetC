
/*

	Bot jouant aléatoirement 

*/

#include <stdio.h>
#include <string.h>

#include "backgammon.h"
#include "ListeChainee.h"


char nom[] = "PerfectBot";
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
	


}