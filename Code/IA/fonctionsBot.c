/*
	
	Fichier contenant la structure Bot, et les fonctions de calcul des différents coups possibles
	(utilise à la fois le fichier Coup.h et ListeChainee.h) 

*/


#include "fonctionsBot.h"




// retourne tous les coups qu'un joueur peut faire, et les stock dans une liste chainée
// un coup a besoin de l'état du jeu, on doit donc passer en paramètres ces variables
void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups ) {

	calculerCoupsPossiblesInitiaux( gameState, maCouleur, dices, listeCoups );

	calculerCoupsPossiblesSuivants( maCouleur, listeCoups );

	calculerCaracteristiquesCoups( listeCoups );
}


// calcule les premiers coups, ces coups n'ont utilisé pour l'instant qu'un seul des dés
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



// calcul, pour une liste de coup initiaux, tout les coups possibles jusqu'a ce qu'il ne reste plus de dé à jouer pour chaque coup
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
	while( cellule ) {		// tant qu'on arrive pas à la fin de la liste (tant que l'on a pas traité tout les éléments de la liste)


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

					ajouterElementFin( listeCoups, nouveauCoup );	// on ajout ece coup en fin de liste pour qu'on le prenne en compte dans le traitements des éléments de la liste

					ancienCoupObsolete = 1;		// on indique que le coup actuel est à supprimer, puisque ce coup a été utilisé pour générer un autre coup.
				}


			}


		}

		cellule = getCelluleSuivante(cellule);

		// on supprime de la liste le coup que l'on vient d'utilisé pour générer des nouveaux coups 
		if( ancienCoupObsolete ) {

			celluleAsupprimer = getCellulePrecedente(cellule);
			detruireCellule( listeCoups, celluleAsupprimer );

			ancienCoupObsolete = 0;
		}

	}

}


// calcul les caractéristiques de chaque coup d'une liste de coup (on applique une fonction au éléments de la liste)
void calculerCaracteristiquesCoups( ListeChainee* listeCoups ) {

	appliquerFonctionSurElement( listeCoups, calculerCaracteristiquesCoup );
}




// affiche chaque coup présent dans une liste de coups (on applique une fonction au éléments de la liste)
void afficherCoups( ListeChainee* listeCoups ) {

	appliquerFonctionSurElement( listeCoups, afficherCoup );
}


