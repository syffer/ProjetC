

#include "Coup.h"

#include <stdio.h>





void initialiserCoup( Coup* coup, SGameState gameState, unsigned char dices[4] ) {
	
	coup -> nbMouvements = 0;
	
	coup -> gameState = gameState;
	
	// on copie la valeur des dés
	int i;
	for( i = 0; i < 4; i++ ) {
		coup -> dices[i] = dices[i];
	}

}


void ajouterMouvementAuCoup( Coup* coup, SMove mouvement ) {

	coup -> mouvements[ coup -> nbMouvements ] = mouvement;
	coup -> nbMouvements += 1;
}



void afficherCoup( Coup coup ) {
	SMove mouvement;
	int i;
	printf(" nbMouvements : %i \n", coup.nbMouvements);
	for( i = 0; i < coup.nbMouvements; i++ ) {
		mouvement = coup.mouvements[i];
		printf(" mouvement %i : de %i a %i \n", i, mouvement.src_point, mouvement.dest_point );
	}
}


/*
void afficherCoups( ListeChainee* listeCoups ) {

	int i = 0;

	Coup coup;
	Cellule* cellule = getPremierElement(listeCoups);

	while( cellule ) {

		printf("-------- COUP %i \n", i);

		coup = getDonnee(cellule);

		afficherCoup(coup);

		cellule = getCelluleSuivante(cellule);

		i++;
	}

}
*/

















/**
 * Fonction sélectionnant le meilleur coup entre deux
 * @param c1 : le premier coup
 * @param c2 : le deuxième coup
 * @return : un entier (booleen)
 * */
int comparerMeilleurCoup( Coup* c1, Coup* c2 ) {

	int nbPointsC1 = calculerMeilleurCoup( &(c1 -> gameState) );
	int nbPointsC2 = calculerMeilleurCoup( &(c2 -> gameState) );

	return nbPointsC1 > nbPointsC2;

}

/**
 * Fonction sélectionnant le meilleur coup entre deux
 * @param c1 : le premier coup
 * @param c2 : le deuxième coup
 * @return : un entier (booleen)
 * */
int comparerAntiJeu( Coup* c1, Coup* c2 ) {

	int nbPointsC1 = calculerCout( &(c1 -> gameState) );
	int nbPointsC2 = calculerCout( &(c2 -> gameState) );

	return nbPointsC1 > nbPointsC2;

}

/**
 * Fonction sélectionnant le meilleur coup entre deux
 * @param fonction : la fonction de calcul de points
 * @param c1 : le premier coup
 * @param c2 : le deuxième coup
 * @return : un entier (booleen)
 * */
int comparerDeuxCoups( Coup* c1, Coup* c2 ) {

	int nbPointsC1 = getNbCasesSecurisees( &(c1 -> gameState), c1 -> gameState.turn );
	int nbPointsC2 = getNbCasesSecurisees( &(c2 -> gameState), c1 -> gameState.turn );

	return nbPointsC1 > nbPointsC2;

}
