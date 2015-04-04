/**
 * Fichier contenant toutes les fonctions utiles pour les différents bots
 * Evite la redondance de code !
 * */
 
#include "fonctionsBot.h"

#include <stdio.h>


#include <time.h>
#include <stdlib.h>


// duplique les dés si nécéssaire, si l'on a deux dés identiques au départ, on doit avoir 4 dés à l'arrivée
// on place la valeur 0 pour un dé qui n'existe pas
void getDices( const unsigned char dices[2], unsigned char newDices[4] ) {

	// on a fait un double (exemple : 1-1 , 2-2 , ... 6-6 )
	if( dices[0] == dices[1] ) {

		int i;
		for( i = 0; i < 4; i++ ) newDices[i] = dices[0];
	}
	else {
		newDices[0] = dices[0];
		newDices[1] = dices[1];
		newDices[2] = newDices[3] = 0;
	}

}




/* retourne la case à la position i
		convention :
		- 0 : la barre (gamestate -> bar[macouleur] )
		- 1 à 24 : le plateau 
		- 25 : la sortie (out)
*/
Square getCaseReelle( SGameState* gameState, Player maCouleur, int i ) {
	
	Square laCase;
	
	if( i == 0 ){								// 0 représente la barre
		laCase.owner = maCouleur;
		laCase.nbDames = gameState -> bar[ maCouleur ];
	} 	
	else if( i == 25 ) {						// 25 représente la sortie (out)
		laCase.owner = maCouleur;
		laCase.nbDames = gameState -> out[ maCouleur ];
	}
	else laCase = gameState -> board[ i - 1 ]; 	// sinon la case est sur le plateau 

	
	return laCase;
}







// retourne vrai si le joueur désigné par sa couleur possède des pions sur la barre (pions à remettre en jeu)
int possedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur ) {
	return gameState -> bar[ maCouleur ];
}



//	retourne vrai si un pion à la case depart peut etre déplacer de nbCases
int peutDeplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases ) {

	if( depart < 0 || depart > 24 ) return 0;		// deplacement impossible, depassement de borne
	if( nbCases <= 0 ) return 0;

	SMove mouvement;
	initialiserMouvement( &mouvement, maCouleur, depart, nbCases );
	int arrivee = mouvement.dest_point;

	Square caseDepart = getCaseReelle( gameState, maCouleur, depart );
	Square caseArrivee = getCaseReelle( gameState, maCouleur, arrivee );

	// verification de la case de départ
	if( caseDepart.nbDames <= 0 ) return 0;			// pas de pions à déplacer sur la case de départ
	if( caseDepart.owner != maCouleur ) return 0;	// les pions ne sont pas à moi


	// verification de la case d'arrivee
	if( caseArrivee.owner != maCouleur && caseArrivee.nbDames > 1 ) return 0;	// il y a plus d'un pion adverse sur la case d'arrivee
	
	if( arrivee == 25 ) {	// si on veut sortir nos pions

		if( gameState -> bar[maCouleur] ) return 0;		// il y a des pions sur la barre.

		int i;
		Square laCase;
		int i_depart = (maCouleur == WHITE) ? 0 : 6;
		for( i = i_depart; i < i_depart + 18; i++ ) {
			laCase = gameState -> board[i];
			if( laCase.owner == maCouleur && laCase.nbDames > 0 ) return 0;		// j'ai encore des pions hors du jar interieur adverse
		}

	}

	return 1;
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



/* déplace un pion sur le plateau du jeu
*
* Attention : ne vérifie pas si l'on peut déplacer le pion, il faut pour cela appeler une autre fonction AVANT celle ci
*
*/
void deplacerUnPion( SGameState* gameState, Player maCouleur, SMove mouvement ) {

	int depart = mouvement.src_point;
	int arrivee = mouvement.dest_point;

	if( depart == 0 ) {
		gameState -> bar[ maCouleur ]--;
	}
	else {

		gameState -> board[ depart - 1 ].nbDames--;
		if( ! gameState -> board[ depart - 1 ].nbDames ) { 	// == 0
			gameState -> board[ depart - 1 ].owner = NOBODY;
		}

	}



	if( arrivee == 25 ) {
		gameState -> out[maCouleur]++;
	}
	else {
		// on ne vérifie pas si il y a un adversaire ici	
		gameState -> board[ arrivee - 1 ].nbDames++;
		gameState -> board[ arrivee - 1 ].owner = maCouleur;
	}

}





void initialiserMouvement( SMove* mouvement, Player maCouleur, int depart, int nbCases ) {

	int arrivee;
	if( maCouleur == WHITE ) arrivee = depart + nbCases;
	else if( depart == 0 ) arrivee = 25 - nbCases;		// je suis le BLACK
	else arrivee = depart - nbCases;

	if( arrivee > 25 || arrivee <= 0 ) arrivee = 25;	

	mouvement -> src_point = depart;
	mouvement -> dest_point = arrivee;
}







void afficherGameState( SGameState gameState ) {
	printf("\n");
	char* nom;
	int i;
	for( i = 0; i < 24; i++ ) {

		if( gameState.board[i].owner == BLACK ) nom = "BLACK";
		else if( gameState.board[i].owner == WHITE  ) nom = "WHITE";
		else nom = "NOBODY";

		printf( "   case %i nbDames %i %s \n", i+1, gameState.board[i].nbDames, nom );
	}
	printf("\n");
}








void initialiserCoup( Coup* coup, SGameState gameState, unsigned char dices[4] ) {
	
	coup -> nbMouvements = 0;
	
	coup -> gameState = gameState;
	
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

void afficherCoups( ListeChainee* listeCoups ) {

	int i = 0;

	Coup coup;
	Cellule* cellule = getPremierElement(listeCoups);

	while( cellule ) {

		printf("-------- COUP %i \n", i);

		coup = getDonnee(cellule);

		afficherCoup(coup);

		cellule = getCelluleSuivante(cellule);
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


			if( possedeDesPionsSurLaBarre( gameState, maCouleur ) && i != 0 ) break;	// il y a des pions sur la barre, je n'ai pas le droit de deplacer autre chose

			laCase = getCaseReelle( gameState, maCouleur, i );
			if( laCase.owner != maCouleur || laCase.nbDames <= 0 ) continue;	// je n'ai pas de pions sur cette case


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




void calculerCoupsPossiblesInitiaux( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups ) {

	Square laCase;
	Coup coup;
	SMove mouvement;
	
	int i, j;
	for( i = 0; i < 25; i++ ) {		// pour chaque case 

		if( possedeDesPionsSurLaBarre( gameState, maCouleur ) && i != 0 ) break;	// il y a des pions sur la barre, je n'ai pas le droit de deplacer autre chose
		

		laCase = getCaseReelle( gameState, maCouleur, i );
		if( laCase.owner != maCouleur || laCase.nbDames <= 0 ) continue;	// je n'ai pas de pions sur cette case

		
		for( j = 0; j < 4; j++ ) {	// pour chaque dé


			if( peutDeplacerUnPion( gameState, maCouleur, i, dices[j] ) ) {


				initialiserMouvement( &mouvement, maCouleur, i, dices[j] );

				initialiserCoup( &coup, *gameState, dices );

				ajouterMouvementAuCoup( &coup, mouvement );


				deplacerUnPion( &(coup.gameState), maCouleur, mouvement );
				coup.dices[j] = 0;

				ajouterElementFin( listeCoups, coup );
			}

		}

	}

}


void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, unsigned char dices[4], ListeChainee* listeCoups ) {

	calculerCoupsPossiblesInitiaux( gameState, maCouleur, dices, listeCoups );

	calculerCoupsPossiblesSuivants( maCouleur, listeCoups );

}




int getNbPointsPrit( SGameState* gameState ) {

	Player maCouleur = gameState -> turn;

	int totalePoints = 0;

	int i;
	for( i = 0; i < 24; i++ ) {

		if( gameState -> board[i].owner == maCouleur && gameState -> board[i].nbDames > 1 ) totalePoints++;
	}

	return totalePoints;
}


/**
 * Fonction  
 * @param :
 * @return : 
 * */
int calculerCout( SGameState* gameState ) {

	Player maCouleur = gameState -> turn;

	int totalePoints = 0;

	int i;
	for( i = 0; i < 24; i++ ) {

		if( gameState -> board[i].owner != maCouleur && gameState -> board[i].nbDames == 1 ) totalePoints += 3;
		else if( gameState -> board[i].owner != maCouleur && gameState -> board[i].nbDames == 0 ) totalePoints += 2;
		else if( gameState -> board[i].owner == maCouleur && gameState -> board[i].nbDames == 1 ) totalePoints += 2;
		else if( gameState -> board[i].owner == maCouleur && gameState -> board[i].nbDames > 1 ) totalePoints++;
	}

	return totalePoints;
}

/**
 * Fonction  
 * @param :
 * @return : 
 * */
int calculerMeilleurCoup( SGameState* gameState ) {

	Player maCouleur = gameState -> turn;

	int totalePoints = 0;

	int i;
	for( i = 0; i < 24; i++ ) {

		if( gameState -> board[i].owner != maCouleur && gameState -> board[i].nbDames == 1 ) totalePoints += 3;
		else if( gameState -> board[i].owner != maCouleur && gameState -> board[i].nbDames == 0 ) totalePoints += 2;
		else if( gameState -> board[i].owner == maCouleur && gameState -> board[i].nbDames == 1 ) totalePoints += 3;
		else if( gameState -> board[i].owner == maCouleur && gameState -> board[i].nbDames > 1 ) totalePoints++;
		else totalePoints--;
	}

	return totalePoints;
}

/**
 * Fonction sélectionnant le meilleur coup entre deux
 * @param c1 : le premier coup
 * @param c2 : le deuxième coup
 * @return : un entier (booleen)
 * */
int comparerMeilleurCoup( Coup c1, Coup c2 ) {

	int nbPointsC1 = calculerMeilleurCoup( &c1.gameState );
	int nbPointsC2 = calculerMeilleurCoup( &c2.gameState );

	return nbPointsC1 > nbPointsC2;

}

/**
 * Fonction sélectionnant le meilleur coup entre deux
 * @param c1 : le premier coup
 * @param c2 : le deuxième coup
 * @return : un entier (booleen)
 * */
int comparerAntiJeu( Coup c1, Coup c2 ) {

	int nbPointsC1 = calculerCout( &c1.gameState );
	int nbPointsC2 = calculerCout( &c2.gameState );

	return nbPointsC1 > nbPointsC2;

}

/**
 * Fonction sélectionnant le meilleur coup entre deux
 * @param fonction : la fonction de calcul de points
 * @param c1 : le premier coup
 * @param c2 : le deuxième coup
 * @return : un entier (booleen)
 * */
int comparerDeuxCoups( Coup c1, Coup c2 ) {

	int nbPointsC1 = getNbPointsPrit( &c1.gameState );
	int nbPointsC2 = getNbPointsPrit( &c2.gameState );

	return nbPointsC1 > nbPointsC2;

}

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

/**
 * Fonction permettant de générer un nombre aléatoire compris dans les bornes
 * @param min : la valeur minimum de l'intervalle
 * @param max : la valeur maximale de l'intervalle
 * @return : l'entier généré
 * */
int random_bot(int min,int max)
{
	int valeur_generee;
	srand(time(NULL));
	valeur_generee= (rand()%(max-min))+min;
	return valeur_generee;
}
