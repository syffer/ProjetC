/**
 * Fichier contenant toutes les fonctions utiles pour les différents bots
 * Evite la redondance de code !
 * */
 
#include "fonctionsBot.h"



// rend les dés sous forme d'une liste chainée
ListeChainee* getDices( const unsigned char dices[2] ) {

	ListeChainee* liste = creerListeChainee();

	// on a fait un double (exemple : 1-1 , 2-2 , ... 6-6 )
	if( dices[0] == dices[1] ) {
		int i;
		for( i = 0; i < 4; i++ ) ajouterElementFin( liste, dices[0] );
	}
	else {
		ajouterElementFin( liste, dices[0] );
		ajouterElementFin( liste, dices[1] );
	}

	return liste;
}





/* retourne la case à la position i
		convention :
		- 0 : la barre (gamestate -> bar[macouleur] )
		- 1 à 24 : le plateau 
		- 25 : la sortie (out)
*/
Square getCaseReelle( SGameState* gameState, Player maCouleur, int i ) {
	
	Square laCase;
	
	if( i != 0 ) laCase = gameState -> board[ i - 1 ]; 		// cas particulier : la barre est représentée par 0
	else if( i == 25 ) {
		laCase.owner = maCouleur;
		laCase.nbDames = gameState -> out[ maCouleur ];
	}
	else {		
		laCase.owner = maCouleur;
		laCase.nbDames = gameState -> bar[ maCouleur ];
	}
	
	return laCase;
}







// retourne vrai si le joueur désigné par sa couleur possède des pions sur la barre (pions à remettre en jeu)
int possedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur ) {
	return gameState -> bar[ maCouleur ];
}



//	retourne vrai si un pion à la case depart peut etre déplacer de nbCases
int peutDeplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases ) {

	if( depart < 0 || depart > 24 ) return 0;		// deplacement impossible, depassement de borne
	if( nbCases < 0 ) return 0;

	Square caseDepart = getCaseReelle( gameState, maCouleur, depart );

	if( caseDepart.nbDames <= 0 ) return 0;			// pas de pions à déplacer sur la case de départ
	if( caseDepart.owner != maCouleur ) return 0;	// les pions ne sont pas à moi

	// le noir se déplace dans le sens normal, le blanc dans le sens inverse
	int arrivee;
	if( maCouleur == BLACK ) arrivee = depart + nbCases;
	else if( depart == 0 ) arrivee = 25 - nbCases;		// je suis le WHITE
	else arrivee = depart - nbCases;
	
	if( arrivee > 25 || arrivee < 0 ) arrivee = 25;

	Square caseArrivee = getCaseReelle( gameState, maCouleur, arrivee );
	
	if( caseArrivee.owner != maCouleur && caseArrivee.nbDames > 1 ) return 0;	// il y a plus d'un pion adverse sur la case d'arrivee
	
	if( arrivee == 25 ) {	// si on veut sortir nos pions

		if( gameState -> bar[maCouleur] ) return 0;		// il y a des pions sur la barre.

		int i;
		Square laCase;
		int i_depart = (maCouleur == BLACK) ? 0 : 6;
		for( i = i_depart; i < i_depart + 18; i++ ) {
			laCase = gameState -> board[i];
			if( laCase.owner == maCouleur && laCase.nbDames > 0 ) return 0;		// j'ai encore des pions hors du jar interieur adverse
		}

	}

	return 1;
}





/* déplace un pion sur le plateau du jeu, retourne le nouvel état du jeu.
*
* Attention : ne vérifie pas si l'on peut déplacer le pion, il faut pour cela appeler une autre fonction AVANT celle ci
*
*/
SGameState deplacerUnPion( SGameState gameState, Player maCouleur, SMove mouvement ) {

	int depart = mouvement.src_point;
	int arrivee = mouvement.dest_point;

	// on bouge le pion du plateau
	gameState.board[depart].nbDames--;
	if( ! gameState.board[depart].nbDames ) { 	// == 0
		gameState.board[depart].owner = NOBODY;
	}

	// on ne vérifie pas si il y a un adversaire ici	
	gameState.board[arrivee].nbDames++;
	gameState.board[arrivee].owner = maCouleur;

	return gameState;
}







/*	crée un nouveau mouvement du point 'depart' au point 'arrivee'
*	
*	0 <= depart, arriveee <= 25
*/
SMove creerMouvement( int depart, int arrivee ) {

	SMove mouvement;
	mouvement.src_point = depart;
	mouvement.dest_point = arrivee;

	return mouvement;
}


/*
*	Crée un mouvement en fonction :
*		- de la couleur du joueur (pour le sens de déplacement)
*		- de la case de départ
*		- du nombre de cases à parcourir lors du déplacement
*
* précondition : 	0 <= depart <= 25
*					nbCases > 0
*/
SMove creerMouvementJoueur( Player maCouleur, int depart, int nbCases ) {

	int arrivee;
	if( maCouleur == BLACK ) arrivee = depart + nbCases;
	else if( depart == 0 ) arrivee = 25 - nbCases;		// je suis le WHITE
	else arrivee = depart - nbCases;

	return creerMouvement( depart, arrivee );
}




// initialise un coup vide (pas de mouvements)
void initialiserCoup( Coup* coup ) {
	coup -> nbMouvements = 0; 
}

void ajouterMouvementAuCoup( Coup* coup, SMove mouvement ) {
	coup -> mouvements[ coup -> nbMouvements ] = mouvement;
	coup -> nbMouvements++; 
}

void ajouterMouvementAuCoupDevant( Coup* coup, SMove mouvement ) {
	int i;
	for( i = 0; i < coup -> nbMouvements - 1; i++ ) {
		coup -> mouvements[i+1] = coup -> mouvements[i];
	}
	coup -> mouvements[0] = mouvement;
	coup -> nbMouvements++;
}



void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, ListeChainee* dices, Coup coups[], int* nbCoupsPossibles ) {
	
	Square laCase;
	Cellule* leDe;
	unsigned char valeurDe;

	Coup* coup;
	Coup coupsSuivants[ 15*15*15*15 ];
	int nbCoupsSuivants = 0;
	SMove mouvement;
	SGameState newGameState;


	*nbCoupsPossibles = 0;

	int i, j;
	for( i = 0; i < 25; i++ ) {	 // pour chaque cases du tableau
		
		laCase = getCaseReelle( gameState, maCouleur, i );

		if( possedeDesPionsSurLaBarre( gameState, maCouleur ) && i != 0 ) break;	// il y a des pions sur la barre, je n'ai pas le droit de deplacer autre chose
		if( laCase.owner != maCouleur || laCase.nbDames <= 0 ) continue;	// je n'ai pas de pions sur cette case

		leDe = getPremierElement(dices);
		while( leDe ) {		// pour chaque dé

			valeurDe = getDonnee( leDe );
			if( peutDeplacerUnPion( gameState, maCouleur, i, valeurDe ) ) {

				mouvement = creerMouvementJoueur( maCouleur, i, valeurDe );
				newGameState = deplacerUnPion( *gameState, maCouleur, mouvement );

				nbCoupsSuivants = 0;
				detruireCellule( dices, leDe );
				
				if( listeEstVide(dices) ) {

					coup = &coups[ *nbCoupsPossibles ];
					initialiserCoup( coup );
					ajouterMouvementAuCoup( coup, mouvement );
					*nbCoupsPossibles++;
				}
				else {

					calculerCoupsPossibles( &newGameState, maCouleur, dices, coupsSuivants, &nbCoupsSuivants );

					for( j = 0; j < nbCoupsSuivants; j++ ) {
						ajouterMouvementAuCoupDevant( &coupsSuivants[j], mouvement );
						coups[ *nbCoupsPossibles ] = coupsSuivants[j];
						*nbCoupsPossibles++;
					}

				}

				ajouterElementDebut( dices, valeurDe );
				
				printf("------\n");

				*nbCoupsPossibles++;
			}

			leDe = getCelluleSuivante(leDe);
		}


	}
	
}





