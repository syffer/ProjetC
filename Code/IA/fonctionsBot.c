/**
 * Fichier contenant toutes les fonctions utiles pour les différents bots
 * Evite la redondance de code !
 * */


/* 


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
*/



#include "fonctionsBot.h"


// retourne tous les coups qu'un joueur peut faire, et les stoque dans une liste chainée
void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups ) {

	calculerCoupsPossiblesInitiaux( gameState, maCouleur, dices, listeCoups );

	calculerCoupsPossiblesSuivants( maCouleur, listeCoups );
}



void calculerCoupsPossiblesInitiaux( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups ) {

	Square laCase;
	Coup coup;
	SMove mouvement;
	
	int i, j;
	for( i = 0; i < 25; i++ ) {		// pour chaque case 

		if( joueurPossedeDesPionsSurLaBarre( gameState, maCouleur ) && i != 0 ) break;	// il y a des pions sur la barre, je n'ai pas le droit de deplacer autre chose
		

		laCase = getCaseReelle( gameState, maCouleur, i );
		if( !caseEstAuJoueur(laCase, maCouleur) || !casePossedeDesPions(laCase) ) continue;	// je n'ai pas de pions sur cette case

		
		for( j = 0; j < 4; j++ ) {	// pour chaque dé


			if( peutDeplacerUnPion( gameState, maCouleur, i, dices[j] ) ) {


				initialiserMouvement( &mouvement, maCouleur, i, dices[j] );

				initialiserCoup( &coup, *gameState, dices );

				ajouterMouvementAuCoup( &coup, mouvement );

				deplacerUnPion( &(coup.gameState), maCouleur, mouvement );		
				coup.dices[j] = 0;	// indique que je viens d'utiliser le dé

				ajouterElementFin( listeCoups, coup );
			}

		}

	}

}




void calculerCoupsPossiblesSuivants( Player maCouleur, ListeChainee* listeCoups ) {

	Square laCase;
	
	Coup coup;
	Coup nouveauCoup;
	SGameState* gameState;
	SMove mouvement;

	int ancienCoupObsolete = 0;

	int i, j;	// pour parcourir les cases et les dés

	Cellule* celluleAsupprimer;
	Cellule* cellule = getPremierElement(listeCoups);
	while( cellule ) {


		coup = getDonnee(cellule);
		gameState = &(coup.gameState);

		for( i = 0; i < 25; i++ ) {		// pour chaque case


			if( joueurPossedeDesPionsSurLaBarre( gameState, maCouleur ) && i != 0 ) break;	// il y a des pions sur la barre, je n'ai pas le droit de deplacer autre chose

			laCase = getCaseReelle( gameState, maCouleur, i );
			if( !caseEstAuJoueur(laCase, maCouleur) || !casePossedeDesPions(laCase) ) continue;	// je n'ai pas de pions sur cette case


			for( j = 0; j < 4; j++ ) {		// pour chaque dé

				if( peutDeplacerUnPion( gameState, maCouleur, i, coup.dices[j] ) ) {

					initialiserMouvement( &mouvement, maCouleur, i, coup.dices[j] );
					nouveauCoup = coup;

					ajouterMouvementAuCoup( &nouveauCoup, mouvement );
					deplacerUnPion( &(nouveauCoup.gameState), maCouleur, mouvement );
					nouveauCoup.dices[j] = 0;

					ajouterElementFin( listeCoups, nouveauCoup );

					ancienCoupObsolete = 1;
				}


			}


		}

		cellule = getCelluleSuivante(cellule);


		if( ancienCoupObsolete ) {

			celluleAsupprimer = getCellulePrecedente(cellule);
			detruireCellule( listeCoups, celluleAsupprimer );

			ancienCoupObsolete = 0;
		}

	}

}










/*
void afficherPeutDeplacer( SGameState* gameState ) {

	printf(" je suis WHITE\n" );
	int i, j;
	for( i = 0; i < 25; i++ ) {

		printf(" case %i : ", i );
		for( j = 1; j <= 6; j++ ) {

			if( peutDeplacerUnPion(gameState, WHITE, i, j) ) printf( " %i", j );
			else printf( "  " );

		}
		printf("\n");
		
	}


	printf("\n je suis BLACK\n" );
	for( i = 0; i < 25; i++ ) {

		printf(" case %i : ", i );
		for( j = 1; j <= 6; j++ ) {

			if( peutDeplacerUnPion(gameState, BLACK, i, j) ) printf( " %i", j );
			else printf( "  " );

		}
		printf("\n");
		
	}

}
*/




























/*
int getCoupMaximum( ListeChainee* listeCoups, fonctionComparaisonCoups f_compraison, Coup* coupMaximum ) {

	int nbCoups = getNbElements(listeCoups);
	if( nbCoups == 0 ) {
		printf("la liste est vide, pas de maximum \n");
		return -1;
	}

	Cellule* cellule = getPremierElement(listeCoups);
	Coup coupMax = getDonnee(cellule);
	Coup coup;


	int i;
	for( i = 1; i < nbCoups; i++ ) {

		cellule = getCelluleSuivante(cellule);
		coup = getDonnee(cellule);

		if( f_compraison(coup, coupMax) ) coupMax = coup; 

	}

	*coupMaximum = coupMax;

	return 0;
}
*/


