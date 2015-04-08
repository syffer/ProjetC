
/*

	Cas où un joueur joue et non un bot

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h> 	// abs()

#include "../Commun/backgammon.h"
#include "../GUI/graphique.h"
#include "fonctionsBot.h"

static Bot bot;

/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary( char name[50] ) {

	strcpy( bot.nom, "Joueur " );
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
	

	/*
		lancer une fenetre pour savoir si le joueur veut doubler la mise
	*/

	ouvrirFenetreDoublerMiseGraphique();

	return getChoixUtilisateurGraphique();
	
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

	ouvrirFenetreAccepterDoublerMise();

	return getChoixUtilisateurGraphique();
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

	
	*nbMove = 0;

	// on récupère les dés
	unsigned char lesDes[4];
	getDices( dices, lesDes );




	int selectionTerminee;

	int valeurDe;
	int positionDe;

	int positionCaseDepart;
	int positionCaseArrivee;

	Square caseDepart;

	SMove mouvement;


	while( peutEncoreJoueur( gameState, bot.maCouleur, lesDes ) ) {

		selectionTerminee = 0;
		while( ! selectionTerminee ) {

			// arrêter animation pions

			positionCaseDepart = selectionnerCaseGraphique();

			caseDepart = getCaseReelle( gameState, bot.maCouleur, positionCaseDepart );

			// la case de départ sélectionnée n'appartient pas au joueur
			if( ! caseEstAuJoueur( caseDepart, bot.maCouleur ) || ! casePossedeDesPions(caseDepart) ) continue;

			// animerPionGraphique(caseDepart);

			positionCaseArrivee = selectionnerCaseGraphique();


			if( positionCaseDepart == positionCaseArrivee ) continue;	// on annule le coup


			valeurDe = abs( positionCaseArrivee - positionCaseDepart );

			// le joueur ne peut pas déplacer ce pion
			if( ! peutDeplacerUnPion( gameState, bot.maCouleur, positionCaseDepart, valeurDe ) ) continue;	


			// le joueur n'a pas utilisé l'un de ses dés
			positionDe = rechercherPositionValeurDe( lesDes, valeurDe );
			if( positionDe == -1 ) continue;	


			// ajout du mouvement dans la liste des mouvements
			mouvement = moves[ *nbMove ];
			initialiserMouvement( &mouvement, bot.maCouleur, positionCaseDepart, valeurDe );
			moves[ *nbMove ] = mouvement;
			*nbMove += 1;

			// on modifie l'état du jeu
			deplacerUnPion( gameState, bot.maCouleur, mouvement );
			///////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////// MODIFIER LE GRAPHIQUE ICI AUSSI !!!!
			///////////////////////////////////////////////////////////

			lesDes[ positionDe ] = 0;		// on indique que le dé a été utilisé


			// on indique que la sélection est terminée
			selectionTerminee = 1;
		}



	}



}




