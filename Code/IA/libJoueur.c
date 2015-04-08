
/*

	Bot ne faisant qu'avancer ses pions les plus éloignés.
	Bot non fini (manque la gestion du videau)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>		// abs()


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

	strcpy( bot.nom, "BotJoueur" );
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
	printf("Doubler la mise ? (y or n) : ");

	scanf("%c",&choix);
    while(choix != 'y' || choix != 'n'){
        printf("\nchoix ? : ");
        scanf("%c",&choix);
    }

    if(choix == 'y'){
        return 1;
    }else{
        return 2;
    }
	//appeler la fonction graphique qui demande au joueur s'il veux doubler ou non
	return(choix);
}


/**
 * Accepter ou refuser la nouvelle mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on accepte la nouvelle mise ; faux sinon
 */
int TakeDouble( const SGameState * const gameState ) {
	printf("Doubler la mise ? (y or n) : ");

	scanf("%c",&choix);
    while(choix != 'y' || choix != 'n'){
        printf("\nchoix ? : ");
        scanf("%c",&choix);
    }

    if(choix == 'y'){
        return 1;
    }else{
        return 2;
    }
	//appeler la fonction graphique qui demande au joueur s'il veux accepter ou non
	return(choix);
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
    int i;
    SMove move;
    for(i=0;i<nbMove;i++){
        printf("mouvement 1\nsrc ? : ");
        scanf("%d",&(move.src_point));
        printf("dest ? : ");
        scanf("%d",&(move.dest_point));
        moves[i] = move;
    }
    //appeler la fonction graphique !!!
}
