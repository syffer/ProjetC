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
		//*nbDeplacements = 4;
		int i;
		for( i = 0; i < 4; i++ ) ajouterElementFin( liste, dices[0] );
	}
	else {
		ajouterElementFin( liste, dices[0] );
		ajouterElementFin( liste, dices[1] );
		
		/*
		*nbDeplacements = 2;
		deplacements[0] = dices[0];
		deplacements[1] = dices[1];
		*/
	}

	return liste;
}





// crée un nouveau mouvement
// retourne NULL si les 
// depart et arrivée entre 0 et 25
// 0 : représente la barre
// 25 : représente la sortie
// autre : représente les cases du plateau
// pre : 0 <= depart, arrivee <= 25
SMove creerMouvement( int depart, int arrivee ) {

	SMove mouvement;
	mouvement.src_point = depart;
	mouvement.dest_point = arrivee;

	return mouvement;
}




// vrai si pion à la case depart peut etre depalcer de nbCases
/*
	convention :
	- 0 : la barre (gamestate -> bar[macouleur] )
	- 1 à 24 : le plateau 
	- 25 : la sortie (out)
*/
int peutDeplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases ) {

	if( depart < 0 || depart > 24 ) return 0;		// deplacement impossible, depassement de borne
	if( nbCases < 0 ) return 0;

	Square caseDepart;
	if( depart == 0 ) {		// on est sur la barre
		caseDepart.owner = maCouleur;
		caseDepart.nbDames = gameState -> bar[maCouleur];
	}
	else caseDepart = gameState -> board[ depart - 1 ];

	if( caseDepart.nbDames <= 0 ) return 0;			// pas de pions à déplacer sur la case de départ
	if( caseDepart.owner != maCouleur ) return 0;	// les pions ne sont pas à moi

	// le noir se déplace dans le sens normal, le blanc dans le sens inverse
	int arrivee;
	if( maCouleur == BLACK ) arrivee = depart + nbCases;
	else if( depart == 0 ) arrivee = 25 - nbCases;		// je suis le WHITE
	else arrivee = depart - nbCases;
	
	if( arrivee > 25 || arrivee < 0 ) arrivee = 25;

	Square caseArrivee;
	if( arrivee == 25 ) {
		caseArrivee.owner = maCouleur;
		caseArrivee.nbDames = gameState -> out[ maCouleur ];
	}
	else caseArrivee = gameState -> board[ arrivee - 1 ];

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


// ATTENTION ===> NE VERIFIE PAS SI ON PEUT DEPLACER LE PION !!!!!!
// pre : appel de la fonction : peutBougerPion
SMove deplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases ) {

	// le noir se déplace dans le sens normal, le blanc dans le sens inverse
	int arrivee;
	if( maCouleur == BLACK ) arrivee = depart + nbCases;
	else if( depart == 0 ) arrivee = 24 - nbCases;		// je suis le WHITE
	else arrivee = depart - nbCases;

	if( arrivee > 25 || arrivee < 0 ) arrivee = 25;


	SMove mouvement = creerMouvement( depart, arrivee );	


	// on bouge le pion du plateau

	gameState -> board[depart].nbDames--;
	if( ! gameState -> board[depart].nbDames ) { 	// == 0
		gameState -> board[depart].owner = NOBODY;
	}

	// on ne vérifie pas si il y a un adversaire ici	
	gameState -> board[arrivee].nbDames++;
	gameState -> board[arrivee].owner = maCouleur;

	return mouvement;
}



int possedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur ) {
	return gameState -> bar[ maCouleur ];
}



// retourne la case à la position i
Square getCaseActuelle( SGameState gameState, Player maCouleur, int i ) {
    
    Square laCase;
    
    if( i != 0 ) laCase = gameState.board[ i - 1 ]; 		// cas particulier : la barre est représentée par 0
	else {		
		laCase.owner = maCouleur;
		laCase.nbDames = gameState.bar[ maCouleur ];
	}
	
	return laCase;
}



void calculerMouvements( SGameState gameState, Player maCouleur, ListeChainee* dices, SMove mouvements[4], int* nbMouvements ) {

	Square laCase;
	Cellule* leDe;
	Cellule* tmp;
	unsigned char valeurDe;


	// pour chaque case du plateau
	int i;
	for( i = 0; i < 25; i++ ) {

        laCase = getCaseActuelle( gameState, maCouleur, i );

		if( gameState.bar[ maCouleur ] && i != 0 ) break;	// il y a des pions sur la barre, je n'ai pas le droit de deplacer autre chose

		if( laCase.owner != maCouleur || laCase.nbDames <= 0 ) continue;	// je n'ai pas de pions sur cette case


		// pour chaque dé de la liste
		leDe = getPremierElement(dices);
		while( leDe ) {

			valeurDe = getDonnee(leDe);

			// si je ne peux pas déplacer un pion avec ce dé
			// j'essaie avec un autre dé
			if( peutDeplacerUnPion( &gameState, maCouleur, i, valeurDe) ) {

				detruireCellule( dices, leDe );		// on retire le dé de la liste (car on l'a utilisé)


				// si j'ai encore des dés à jouer
				if( ! listeEstVide(dices) ) {	
					calculerMouvements( gameState, maCouleur, dices, mouvements, nbMouvements );
				
					// créée un couple entre le mouvement actuel et chaque mouvement venant d'être généré
					/*
					
					    PARTIE NON FINIE !!! 
					
					*/
					
					
				}


				leDe = ajouterElementDebut( dices, valeurDe ); 	// on remet le dé dans la liste

			}

			leDe = getCelluleSuivante(leDe);
		
		}


	}

}



void calculerCoupsPossibles( SGameState gameState, Player maCouleur, ListeChainee* dices, Coup coups[], int nbCoupsPossibles ) {
    
    Square laCase;
    Cellule* leDe;
    unsigned char valeurDe;
    
    int i;
    for( i = 0; i < 25; i++ ) {     // pour chaque cases du tableau
        
        laCase = getCaseActuelle( gameState, maCouleur, i );
        
        
    }
    
}