
/*

	Cas où un joueur joue et non un bot

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h> 	// abs()

#include "../Commun/backgammon.h"
#include "../GUI/graphique.h"


char nom[] = "Joueur ";
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
	

	/*
		lancer une fenetre pour savoir si le joueur veut doubler la mise
	*/

	return(0);		
}


/**
 * Accepter ou refuser la nouvelle mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on accepte la nouvelle mise ; faux sinonTitouan Psq
 */
int TakeDouble( const SGameState * const gameState ) {


	/*
		lancer une fenetre pour savoir si le joueur accepte la nouvelle mise
	*/	


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
	

	/*
		gestion des evenements SDL / horizon des évenements SDL


			- besoin du graphique.h et des variables de plateau ???
	*/


	/*
	
	sdl event

	swith event

	

	selectionner case depart (pion)

	animer le pion pour le voir


	selectionner case destination
		if( source == destination ) retour avant
		if( ! peutBougerPion ) retour avant

	bouger pion graphique


	*/


	/*

	for( j = 0; j < 4; j++ ) {		// pour chaque dé

				if( peutDeplacerUnPion( gameState, maCouleur, i, coup.dices[j] ) ) {

					initialiserMouvement( &mouvement, maCouleur, i, coup.dices[j] );
					nouveauCoup = coup;		// on copie le coup d'origine, pour lui rajouté un mouvement

					ajouterMouvementAuCoup( &nouveauCoup, mouvement, j );

					ajouterElementFin( listeCoups, nouveauCoup );	// on ajout ece coup en fin de liste pour qu'on le prenne en compte dans le traitements des éléments de la liste

					ancienCoupObsolete = 1;		// on indique que le coup actuel est à supprimer, puisque ce coup a été utilisé pour générer un autre coup.
								
				}*/


}




