/**
 * Fichier contenant toutes les fonctions utiles pour les différents bots
 * Evite la redondance de code !
 * */




#include "fonctionsBot.h"








// retourne tous les coups qu'un joueur peut faire, et les stoque dans une liste chainée
void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups ) {

	calculerCoupsPossiblesInitiaux( gameState, maCouleur, dices, listeCoups );

	calculerCoupsPossiblesSuivants( maCouleur, listeCoups );

	calculerCaracteristiquesCoups( listeCoups );
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

				initialiserCoup( &coup, *gameState, dices, maCouleur );

				ajouterMouvementAuCoup( &coup, mouvement, j );

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
					nouveauCoup = coup;		// on copie le coup d'origine, pour lui rajouté un mouvement

					ajouterMouvementAuCoup( &nouveauCoup, mouvement, j );

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


void calculerCaracteristiquesCoups( ListeChainee* listeCoups ) {

	appliquerFonctionSurElement( listeCoups, calculerCaracteristiquesCoup );
}





void afficherCoups( ListeChainee* listeCoups ) {

	appliquerFonctionSurElement( listeCoups, afficherCoup );
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



