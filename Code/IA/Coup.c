/*

	Fichier regroupant toutes les fonctions concernant la structure Coup

*/


#include "Coup.h"

#include <stdio.h>




// initialise un coup
void initialiserCoup( Coup* coup, SGameState gameState, unsigned char dices[4], Player maCouleur ) {
	
	coup -> nbMouvements = 0;
	
	coup -> gameState = gameState;
	
	coup -> maCouleur = maCouleur;

	// on copie la valeur des dés
	int i;
	for( i = 0; i < 4; i++ ) {
		coup -> dices[i] = dices[i];
	}

}


// ajoute un mouvement au coup, et met à jour l'état du jeu (on effectue le mouvement sur le plateau)
void ajouterMouvementAuCoup( Coup* coup, SMove mouvement, int numeroDeUtilise ) {

	// ajout du mouvement à la liste des mouvements du coup
	coup -> mouvements[ coup -> nbMouvements ] = mouvement;
	coup -> nbMouvements += 1;

	// mise à jour de l'état du jeu
	deplacerUnPion( &(coup -> gameState), coup -> maCouleur, mouvement );
	coup -> dices[ numeroDeUtilise ] = 0;	// indique que je viens d'utiliser le dé

}


// fonction permettant d'afficher les variables du coup
void afficherCoup( Coup* coup ) {
	SMove mouvement;

	printf(" nbCasesSecurisees : %i \n", coup -> nbCasesSecurisees);
	printf(" nbCases2Dames : %i \n", coup -> nbCases2Pions);
	printf(" probabilitePertePion : %lf \n", coup -> probabilitePertePion);
	printf(" nbMouvements : %i \n", coup -> nbMouvements);

	int i;
	for( i = 0; i < coup -> nbMouvements; i++ ) {
		mouvement = coup -> mouvements[i];
		printf(" mouvement %i : de %i a %i \n", i, mouvement.src_point, mouvement.dest_point );
	}

	printf("\n");
}


// calcul les différentes caractéristiques d'un coup (nombre de cases sécurisées...)
void calculerCaracteristiquesCoup( Coup* coup ) {

	coup -> nbCasesSecurisees = 0;
	coup -> nbCases2Pions = 0;
	coup -> probabilitePertePion = 0.0;

	Player maCouleur = coup -> maCouleur;
	SGameState* gameState = &(coup -> gameState);
	Square laCase;

	int i;
	for( i = 1; i < 25; i++ ) {

		laCase = getCaseReelle( gameState, maCouleur, i );

		if( caseEstAuJoueur(laCase,maCouleur) && caseEstSecurisee(laCase) ) coup -> nbCasesSecurisees += 1;
		if( caseEstAuJoueur(laCase,maCouleur) && laCase.nbDames == 2 ) coup -> nbCases2Pions += 1;
	}

	coup -> probabilitePertePion = getProbabilitePerdreUnPion( gameState, maCouleur );

}






/*
	fonctions de comparaison de coups

	ces fonctions renveront :
	- 1 	si c1 > c2
	- 0 	si c1 == c2
	- -1	si c1 < c2

*/


int comparerCoups_nbMouvements( Coup* c1, Coup* c2 ) {
	int nbMouvements_c1 = c1 -> nbMouvements;
	int nbMouvements_c2 = c2 -> nbMouvements;

	if( nbMouvements_c1 > nbMouvements_c2 ) return 1;
	else if( nbMouvements_c1 < nbMouvements_c2 ) return -1;
	else return 0;
}


// fonction qui compare deux coup en fonctions de leurs nombre de cases sécurisées
int comparerCoups_CasesSecurisees( Coup* c1, Coup* c2 ) {
	int nbCasesSecurisees_c1 = c1 -> nbCasesSecurisees;
	int nbCasesSecurisees_c2 = c2 -> nbCasesSecurisees;

	if( nbCasesSecurisees_c1 > nbCasesSecurisees_c2 ) return 1;
	else if( nbCasesSecurisees_c1 < nbCasesSecurisees_c2 ) return -1;
	else return 0;
}


// fonction qui compare deux coup en fonctions de leurs nombre de pions adverse sur la barre
int comparerCoups_PionsAdverseBarre( Coup* c1, Coup* c2 ) {
	int barreAdverse_c1 = c1 -> gameState.bar[ getCouleurAdverse( c1 -> maCouleur ) ];
	int barreAdverse_c2 = c2 -> gameState.bar[ getCouleurAdverse( c2 -> maCouleur ) ];

	if( barreAdverse_c1 > barreAdverse_c2 ) return 1;
	else if( barreAdverse_c1 < barreAdverse_c2 ) return -1;
	else return 0;
}


// fonction qui compare deux coup en fonctions de leurs nombre sortie du plateau
int comparerCoups_PionsSorties( Coup* c1, Coup* c2 ) {

	int nbPionsSorties_c1 = c1 -> gameState.out[ c1 -> maCouleur ];
	int nbPionsSorties_c2 = c2 -> gameState.out[ c2 -> maCouleur ];

	if( nbPionsSorties_c1 > nbPionsSorties_c2 ) return 1;
	else if( nbPionsSorties_c1 < nbPionsSorties_c2 ) return -1;
	else return 0;
}


// fonction qui compare deux coup en fonctions de leurs nombre de cases possèdant exactement 2 pions
int comparerCoup_Cases2Dames( Coup* c1, Coup* c2 ) {
	int nbCases2Dames_c1 = c1 -> nbCases2Pions;
	int nbCases2Dames_c2 = c2 -> nbCases2Pions;

	if( nbCases2Dames_c1 > nbCases2Dames_c2 ) return 1;
	else if( nbCases2Dames_c1 < nbCases2Dames_c2 ) return -1;
	else return 0;
}


// fonction qui compare deux coup en fonctions de la probabilité de perdre un pion au prochain tour
int comparerCoups_ProbabilitesPertePion( Coup* c1, Coup* c2 ) {
	double probabilitePertePion_c1 = c1 -> probabilitePertePion;
	double probabilitePertePion_c2 = c2 -> probabilitePertePion;

	if( probabilitePertePion_c1 < probabilitePertePion_c2 ) return 1;		// on cherche a avoir la probabilitée la plus proche de 0
	else if( probabilitePertePion_c1 > probabilitePertePion_c2 ) return -1;
	else return 0;
}




// fonction qui compare deux coups en fonctions de plusieurs critères, permettant de définir quel coup est le moins dangereux
int comparerCoups_Securitee( Coup* c1, Coup* c2 ) {

	int comparaison = comparerCoups_nbMouvements( c1, c2 );
	if( comparaison != 0 ) return comparaison;

	comparaison = comparerCoups_PionsSorties( c1, c2 );
	if( comparaison != 0 ) return comparaison;

	comparaison = comparerCoups_CasesSecurisees( c1, c2 );
	if( comparaison != 0 ) return comparaison;

	comparaison = comparerCoups_PionsAdverseBarre( c1, c2 );
	if( comparaison != 0 ) return comparaison;

	comparaison = comparerCoups_ProbabilitesPertePion( c1, c2 );
	if( comparaison != 0 ) return comparaison;

	comparaison = comparerCoup_Cases2Dames( c1, c2 );
	return comparaison;
}

















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

