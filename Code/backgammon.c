
#include "verifications.h"
#include "joueur.h"
#include "arbitre.h"
#include "graphique.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>		// a virer apres

int main( int argc, char* argv[] ) {

	/*
	*	vérification des paramètres entrés par l'utilisateur
	*/

	unsigned char dices[2];
	SGameState gameState = initialiserEtatJeux();
	initialiserPlateau( gameState.board );

	initialiserFenetre();

    afficherJeu();
	// lancerLesDes( dices );

	pause();



	fermerFenetre();

	return 0;

}

