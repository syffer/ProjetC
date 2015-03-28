
#include "arbitre.h"

#include "backgammon.h"
#include "joueur.h"

#include <time.h>		// time
#include <stdlib.h> 	// srand
#include <stdio.h>		// printf()


/*
* Affiche le contenu du tableau contenant la valeurs des dés.
*
*/
void afficherDes( unsigned char dices[2] ) {
	printf( " des : %i %i \n", dices[0], dices[1] );
}


/*
* Lance les dés
*
*/
void lancerLesDes( unsigned char dices[2] ) {
	dices[0] = (unsigned char) randomINT(1,6);
	dices[1] = (unsigned char) randomINT(1,6);
}



/*
* Retourne un nombre généré aléatoirement entre min et max compris.
*
*/
int randomINT( int min, int max ) {
	
	// on vérifie si le générateur aléatoire a été initialisé
	static int generateurInitialise = 0;
    if( ! generateurInitialise ) {		// si ce n'est pas le cas, on l'initialise
        generateurInitialise = 1;
        srand( time(NULL) );
    }
    
	return ( rand() % (max-min+1) ) + min;
}










int remplirCase( Square board[24], int numeroCase, Player couleurJoueur, int nbDames ) {
	if( numeroCase >= 24 || numeroCase < 0 ) return -1;

	board[ numeroCase ].owner = couleurJoueur;
	board[ numeroCase ].nbDames = nbDames;

	return 0;
}



SGameState initialiserEtatJeux() {

	SGameState etatJeux;

	// pions sur la barre centrales (ceux pas encore en jeu)
	etatJeux.bar[ BLACK ] = 0;
	etatJeux.bar[ WHITE ] = 0;

	// pions déjà sorties
	etatJeux.out[ BLACK ] = 0;
	etatJeux.out[ WHITE ] = 0;

	// score des joueurs
	etatJeux.whiteScore = 0;
	etatJeux.blackScore = 0;

	etatJeux.turn = WHITE;

	//mise courante (du videau)
	etatJeux.stake = 1;

	// on initialise tout le plateau à "rien/personne/NOBODY"
	int i;
	for( i = 0; i < 24; i++ ) {
		remplirCase( etatJeux.board, i, NOBODY, 0 );
	}

	// on remplit petit à petit le plateau
	/*
	remplirCase( etatJeux, 0, WHITE, 2 );
	remplirCase( etatJeux, 5, BLACK, 5 );
	remplirCase( etatJeux, 7, BLACK, 3 );
	remplirCase( etatJeux, 11, WHITE, 5 );
	remplirCase( etatJeux, 12, BLACK, 5 );
	remplirCase( etatJeux, 16, WHITE, 3 );
	remplirCase( etatJeux, 18, WHITE, 5 );
	remplirCase( etatJeux, 23, BLACK, 2 );
	*/

	return etatJeux;
}



void initialiserPlateau( Square board[24] ) {
	remplirCase( board, 0, WHITE, 2 );
	remplirCase( board, 5, BLACK, 5 );
	remplirCase( board, 7, BLACK, 3 );
	remplirCase( board, 11, WHITE, 5 );
	remplirCase( board, 12, BLACK, 5 );
	remplirCase( board, 16, WHITE, 3 );
	remplirCase( board, 18, WHITE, 5 );
	remplirCase( board, 23, BLACK, 2 );
}


const SGameState * const copierEtatJeux( SGameState etatJeux ) {
	return NULL;

}



void jouerPartie( int nbParties, Joueur joueur1, Joueur joueur2 ) {

	char nomBot1[50];
	char nomBot2[50];
	joueur1.InitLibrary(nomBot1);
	joueur2.InitLibrary(nomBot2);

	
	// variables de jeux 
	unsigned int nbMoves;
	SMove moves[4];
	unsigned char dices[2];
	int triesWhite = 2;
	int triesBlack = 2;

	SGameState etatJeux = initialiserEtatJeux(); 	// /!\ a initialiser (tableau de cases, nb points ....)

	Joueur joueur;		// le joueur qui va jouer

	int score = 5; 	// quel est le score à atteindre ??????


	joueur1.StartMatch(score);
	joueur2.StartMatch(score);

	int i;
	for( i = 0; i < nbParties; i++ ) {

		printf("-> partie %i \n", i+1 );

		initialiserPlateau( etatJeux.board );

		// on lance les dés jusqu'a ce que l'on obtienne deux nombre différents
		do
		{
			lancerLesDes(dices);
		} while( dices[0] == dices[1] ); 	


		// convention pour le début : le joueur 1 a jeté le dés à l'indice 0
		if( dices[0] > dices[1] ) {
			joueur1.StartGame( WHITE );
			joueur2.StartGame( BLACK );

			joueur = joueur1;
		}
		else {
			joueur1.StartGame( BLACK );
			joueur2.StartGame( WHITE );
		
			joueur = joueur2;
		}


		while( 1 ) {  	// tant que la partie n'est pas terminée

			/* 
				!!!! attention, pour le premier tour, le joueur blanc doit utiliser les premiers dés tirés
				(ceux utilisé pour déterminé qui est noir et qui est blanc)

			*/


			// si le joueur a le videau, alors le proposer à l'autre de le prendre
			// puis demander au 1er joueur si il accept ou non la nouvelle mise
			// 

			/*

			if (j1DoubleStack(&gameState))
				j2TakeDouble(&gameState);
			*/

			
			//joueur.PlayTurn( etatJeux, dices, moves, &nbMoves, triesWhite );
			

			if( etatJeux.turn == WHITE ) {
				etatJeux.turn = BLACK;

			}
			else {
				etatJeux.turn = WHITE;

			}



		}



		joueur1.EndGame();
		joueur2.EndGame();
		printf("-> fin de la partie %i \n", i+1 );
	}

	joueur1.EndMatch();
	joueur2.EndMatch();

		


	// model : 
	// j1StartMatch(5);
	// 	//*****// à faire pour chaque jeu
	// 	j1StartGame(BLACK);
	// 		//*****// pour chaque joueur, tant que ce n'est pas fini
	// 		if (j1DoubleStack(&gameState))
	// 			j2TakeDouble(&gameState);
	// 		j1PlayTurn(&gameState,dices,moves,&nbMoves,3);
	// 	j1EndGame();

	// j1EndMatch();

}




