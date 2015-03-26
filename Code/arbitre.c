
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






void jouerPartie( int nbParties, Joueur* joueur1, Joueur* joueur2 ) {



	//unsigned int nbMoves;
	unsigned char dices[2];

	char nomBot1[50];
	char nomBot2[50];
	joueur1 -> InitLibrary(nomBot1);
	joueur2 -> InitLibrary(nomBot2);

	printf(" %p \n %p \n ", joueur1 -> StartMatch, joueur2 -> StartMatch );
	
	// ........................................................................... 
	

	lancerLesDes( dices );
	afficherDes( dices );


	// ??? score cible pour gagner un match ???
	joueur1 -> StartMatch(-1);
	joueur2 -> StartMatch(-1);



	joueur1 -> StartGame( WHITE );
	joueur2 -> StartGame( BLACK );


	joueur1 -> EndGame();
	joueur2 -> EndGame();


	joueur1 -> EndMatch();
	joueur2 -> EndMatch();

}




