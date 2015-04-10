/*
	Fichier contenant la structure Bot, et les fonctions de calculs des différents coups possibles
	(utilise à la fois le fichier Coup.h et ListeChainee.h) 
	
	Auteurs :
	- Pauline HOULGATTE
	- Maxime PINEAU	

*/

#include "fonctionsBot.h"

/** Retourne les coups possibles pour un joueur
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @param dices : le tirage des dés
 * @param listeCoups : les coups possibles
 * */
void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups ) {
	calculerCoupsPossiblesInitiaux( gameState, maCouleur, dices, listeCoups );
	calculerCoupsPossiblesSuivants( maCouleur, listeCoups );
	calculerCaracteristiquesCoups( listeCoups );
}

/** Calcule les coups possibles avec les deux dés
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @param dices : les dés
 * @param listeCoups : les coups possibles
 * */
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

/** Calcule les coups possibles après avoir joué un dé, jusqu'à ce qu'il n'y ait plus de dé à jouer
 * @param maCouleur : la couleur du joueur
 * @param listeCoups : les coups possibles
 * */
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
	while( cellule ) {		// tant qu'on arrive pas à la fin de la liste (tant que l'on a pas traité tous les éléments de la liste)
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
					ajouterElementFin( listeCoups, nouveauCoup );	// on ajoute ce coup en fin de liste pour qu'on le prenne en compte dans le traitement des éléments de la liste
					ancienCoupObsolete = 1;	// on indique que le coup actuel est à supprimer, puisque ce coup a été utilisé pour générer un autre coup.
				}
			}
		}

		cellule = getCelluleSuivante(cellule);

		// on supprime de la liste le coup que l'on vient d'utiliser pour générer des nouveaux coups 
		if( ancienCoupObsolete ) {
			celluleAsupprimer = getCellulePrecedente(cellule);
			detruireCellule( listeCoups, celluleAsupprimer );
			ancienCoupObsolete = 0;
		}
	}
}

/** Calcule les caractéristiques d'un coup
 * @param listeCoups : la liste contenant les coups
 * */
void calculerCaracteristiquesCoups( ListeChainee* listeCoups ) {
	appliquerFonctionSurElement( listeCoups, calculerCaracteristiquesCoup );
}

/** Affiche les coups contenus dans une liste
 * @param listeCoups : la liste des coups
 * */
void afficherCoups( ListeChainee* listeCoups ) {
	appliquerFonctionSurElement( listeCoups, afficherCoup );
}