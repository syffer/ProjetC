/*
	Bot ne faisant qu'avancer ses pions les plus éloignés.
	
	Ce bot avance les pions les plus éloignés si possibles, 
	il ne double jamais la mise, et accepte toujours une nouvelle mise.
	
	Auteurs :
	- Pauline HOULGATTE
	- Maxime PINEAU	

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

	// on récupère la valeur des dés
	unsigned char mesDes[4];
	getDices( dices, mesDes );

	*nbMove = 0;
	SMove mouvement;

	// variable permettant de calculer la véritable position de la case en fonction de la variable de boucle i
	int position;
	int a_retirer = (maCouleur == WHITE) ? 0 : 25;
	int i, j;

	for( i = 0; i < 25; i++ ) {		// pour chaque case

		// on ne peut pas jouer d'autres pions s'il y a des pions sur la barre
		if( joueurPossedeDesPionsSurLaBarre(gameState,maCouleur) && i != 0 ) break;		

		if( i == 0 ) position = 0;		// la barre est toujours représentée par 0, pas besoin de recalculer la position
		else position = abs( a_retirer - i );

		for( j = 0; j < 4; j++ ) {		// pour chaque dé
		
			if( peutDeplacerUnPion(gameState, maCouleur, position, mesDes[j] ) ) {
				printf("(%s) je bouge un pion de la case %i de %i case(s) \n", bot.nom, position, mesDes[j] );
				initialiserMouvement( &mouvement, maCouleur, position, mesDes[j] );

				moves[ *nbMove ] = mouvement;
				*nbMove += 1;

				// on met à jour notre gameState pour ne pas avoir de valeurs incohérentes dans l'état du jeu
				deplacerUnPion( gameState, maCouleur, mouvement );
				
				// on indique que l'on a utilisé le dé en lui donnant la valeur 0
				mesDes[j] = 0;
			}
		}
	}
}