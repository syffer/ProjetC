
#include "arbitre.h"


#include "joueur.h"
#include "graphique.h"
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













SGameState initialiserEtatJeux() { 
	SGameState etatJeux; // pions sur la barre centrales (ceux pas encore en jeu) 
	etatJeux.bar[ BLACK ] = 0; etatJeux.bar[ WHITE ] = 0; // pions déjà sorties 
	etatJeux.out[ BLACK ] = 0; etatJeux.out[ WHITE ] = 0; // score des joueurs 
	etatJeux.whiteScore = 0; 
	etatJeux.blackScore = 0; 
	etatJeux.turn = WHITE; //mise courante (du videau) 
	etatJeux.stake = 1; // on initialise tout le plateau à "rien/personne/NOBODY" 

	int i; for( i = 0; i < 24; i++ ) { 
		remplirCase( etatJeux.board, i, NOBODY, 0 ); 
	} 

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


int remplirCase( Square board[], int laCase, int couleurJoueur, int nbDames ) { 

	if( laCase < 0 || laCase > 23 ){ 
		perror("laCase pointe vers rien du tout !"); 
		exit(EXIT_FAILURE); 
	} 

	board[laCase].owner = couleurJoueur; 
	board[laCase].nbDames = nbDames; 

	/*
	if(nbDames != 0){ 
		remplirCaseX(laCase, couleurJoueur, nbDames);//mettre le nombre de pions qu'il faut dans chaque case !
	} 
	*/
	
	return 0; 
}



