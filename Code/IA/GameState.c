/*
	
	Fichier contenant les fonctions concernant l'état du jeu (GameState, SMove, Square, Player...)

*/

#include "GameState.h"

#include <stdio.h>		// printf()
#include <stdlib.h> 	// abs() 
#include <time.h>		// time() 


// duplique les dés si nécéssaire, si l'on a deux dés identiques au départ, on doit avoir 4 dés à l'arrivée
// on place la valeur 0 pour un dé qui n'existe pas, ou qui a été utilisé
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




// retourne la couleur de l'adversaire, ou NOBODY si on entre NOBODY
Player getCouleurAdverse( Player maCouleur ) {
	if( maCouleur == WHITE ) return BLACK;
	else if( maCouleur == BLACK ) return WHITE;
	else return NOBODY;
}




// initialise un mouvement 
void initialiserMouvement( SMove* mouvement, Player maCouleur, int depart, int nbCases ) {

	int arrivee;
	if( maCouleur == WHITE ) arrivee = depart + nbCases;
	else if( depart == 0 ) arrivee = 25 - nbCases;		// je suis le BLACK
	else arrivee = depart - nbCases;

	if( arrivee > 25 || arrivee <= 0 ) arrivee = 25;	

	mouvement -> src_point = depart;
	mouvement -> dest_point = arrivee;
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

// renvoie vrai si la case appartient au joueur, faux sinon
int caseEstAuJoueur( Square laCase, Player couleurJoueur ) {
	return laCase.owner == couleurJoueur;
}

// retourne vrai si la case est sécurisée (ne peut pas être prise par un autre joueur)
int caseEstSecurisee( Square laCase ) {
	return laCase.nbDames > 1;
}

// retourne vrai si la case possède au moins 1 pion
int casePossedeDesPions( Square laCase ) {
	return laCase.nbDames > 0;
}







// retourne vrai si le joueur désigné par sa couleur possède des pions sur la barre (pions à remettre en jeu)
int joueurPossedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur ) {
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
	if( ! casePossedeDesPions(caseDepart) ) return 0;			// pas de pions à déplacer sur la case de départ
	if( ! caseEstAuJoueur(caseDepart, maCouleur) ) return 0;	// les pions ne sont pas à moi


	// verification de la case d'arrivee
	if( arrivee == 25 ) {	// si on veut sortir nos pions


		if( joueurPossedeDesPionsSurLaBarre(gameState, maCouleur) ) return 0;		// il y a des pions sur la barre.

		int i;
		Square laCase;
		int i_depart = (maCouleur == WHITE) ? 0 : 6;
		for( i = i_depart; i < i_depart + 18; i++ ) {
			laCase = gameState -> board[i];
			if( caseEstAuJoueur(laCase, maCouleur) && casePossedeDesPions(laCase) ) return 0;		// j'ai encore des pions hors du jar interieur adverse
		}

	}
	else if( !caseEstAuJoueur(caseArrivee, maCouleur) && caseEstSecurisee(caseArrivee) ) return 0;	// il y a plus d'un pion adverse sur la case d'arrivee

	return 1;
}


/* déplace un pion sur le plateau du jeu
*
* Attention : ne vérifie pas si l'on peut déplacer le pion, il faut pour cela appeler la fonction 'peutDeplacerUnPion' AVANT celle ci
*
*	retourne 0 si tout s'est bien passé, -1 sinon (erreur lors du déplacement).
*/
int deplacerUnPion( SGameState* gameState, Player maCouleur, SMove mouvement ) {

	int depart = mouvement.src_point;
	int arrivee = mouvement.dest_point;

	if( depart == 0 ) {		// depart sur la barre
		gameState -> bar[ maCouleur ]--;
	}
	else {

		gameState -> board[ depart - 1 ].nbDames--;
		if( ! gameState -> board[ depart - 1 ].nbDames ) { 	// == 0
			gameState -> board[ depart - 1 ].owner = NOBODY;
		}

	}

	Player couleurAdversaire = getCouleurAdverse(maCouleur);


	if( arrivee == 25 ) {
		gameState -> out[maCouleur]++;
	}
	else {

		Player couleurCase = gameState -> board[ arrivee - 1 ].owner;
		int nbDamesSurLaCase = gameState -> board[ arrivee - 1 ].nbDames;

		// si l'arrivée est déja à moi
		if( couleurCase == maCouleur ) {
			gameState -> board[ arrivee - 1 ].nbDames += 1;
		}
		else if( couleurCase == NOBODY ) {
			gameState -> board[ arrivee - 1 ].nbDames += 1;
			gameState -> board[ arrivee - 1 ].owner = maCouleur;
		}
		else if( couleurCase == couleurAdversaire && nbDamesSurLaCase == 1 ) {
			gameState -> board[ arrivee - 1 ].owner = maCouleur;
			gameState -> bar[ couleurAdversaire ] += 1;
		}
		else {
			printf("ERREUR \n");
			return -1;
		}

	}

	return 0;
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








// retourne le nombre de cases sécurisées d'un joueur. Une case sécurisée est une case possédant au moins 2 pions (donc imprenable par l'adversaire)
int getNbCasesSecurisees( SGameState* gameState, Player maCouleur ) {

	int totaleCasesSecurisees = 0;
	Square laCase;

	int i;
	for( i = 0; i < 24; i++ ) {

		laCase = getCaseReelle( gameState, maCouleur, i );

		if( caseEstAuJoueur(laCase,maCouleur) && caseEstSecurisee(laCase) ) totaleCasesSecurisees++;
	}

	return totaleCasesSecurisees;
}






// retourne la probabilité qu'un joueur se fasse prendre un pion au prochain tour
double getProbabilitePerdreUnPion( SGameState* gameState, Player maCouleur ) {

	int valeurDes[25] = {0};
	
	getEloignementsPointsNonSecurisees( gameState, maCouleur, valeurDes );

	return getProbabiliteeDeFaireUnDesDes(valeurDes);
}


/* 
	remplit un tableau qui contiendra le nombre de cases séparant les cases non sécurisées d'un joueur à celles de son adversaire

	par exemple 
		on a la configuration suivante  : - - B - - N - B - - - 
		le tableau contiendra (si l'on considère le joueur blanc) :
			- tab[0] = 0
			- tab[1] = 0 	
			- tab[2] = 1  	car un pion blanc est éloigné d'une case par rapport à TOUS les pions noirs
			- tab[3] = 1 	car un pion blanc est éloigné de 2 cases par rapport à TOUS les pions noirs
*/
void getEloignementsPointsNonSecurisees( SGameState* gameState, Player maCouleur, int eloignements[25] ) {

	Square caseDepart, caseArrivee;
	Player couleurAdversaire = getCouleurAdverse(maCouleur);

	int eloigement;

	int j_depart = 1;
	int j_arrivee = 24;

	if( maCouleur == BLACK ) {	// les pions blancs avances dans l'autre sens
		j_depart = -24;
		j_arrivee = -1;
	}

	int i, j;
	for( i = 1; i < 25; i++ ) {		// on parcours chaque case du plateau

		caseDepart = getCaseReelle( gameState, maCouleur,  i );

		// la case n'est pas à moi
		// ou la case est sécurisée (a plus d'une dame)
		if( ! caseEstAuJoueur(caseDepart, maCouleur) || caseEstSecurisee(caseDepart) ) continue;	

		for( j = i + j_depart; j < i + j_arrivee; j++ ) {

			if( j > 25 || j < 0 ) continue;	// dépassement de borne du plateau

			if( maCouleur == WHITE && j == 25 ) caseArrivee = getCaseReelle( gameState, couleurAdversaire, 0 );
			else caseArrivee = getCaseReelle( gameState, couleurAdversaire, j );


			if( caseEstAuJoueur(caseArrivee, couleurAdversaire) && casePossedeDesPions(caseArrivee) ) {
				eloigement = abs( i - j );
				eloignements[ eloigement ]++;
			}

		}

	}

}


/* 
	retourne la probabilitée de faire l'une des 25 valeurs de dé possibles, 
	les valeurs que l'on veut considéré dans le calcul auront pour valeur 1 dans un tableau de valeur
	
	par exemple :
		si l'on la probabilité de faire le chiffre 1 ou 24 avec les dés:
		- tab[1] = 1
		- tab[24] = 1

		pour faire la valeur 24 avec les dés, il n'y a qu'une possibilité : 6 - 6
		pour faire la valeur 1 avec les dés, il y a 11 combinaisons de dé possibles ( 1-1, 1-2, ...., 6-1 )

		cette fonction renverra donc : 12 / 36  (car il n'y a que 36 combinaisons de dé possible)
*/
double getProbabiliteeDeFaireUnDesDes( int valeurDes[25] ) {

	int nbLances = 0;
	int i, j;

	for( i = 1; i <= 6; i++ ) {		// on lance le 1er dé

		

		for( j = 1; j <= 6; j++ ) {		// on lance le 2eme dé

			if( valeurDes[i] ) nbLances += 1;		// on fait l'une des valeurs recherchées avec le 1er dé
			else if( valeurDes[j] ) nbLances += 1; 		// on fait l'une des valeurs recherchées avec le 2eme dé

			else if( valeurDes[i+j] ) nbLances += 1;		// on fait l'une des valeurs recherchées avec la somme des deux dés

			else if( i == j ) {		// cas ou l'on possède 4 dés

				if( valeurDes[3*i] || valeurDes[4*i] ) nbLances += 1;
			}

		}
	}

	//printf( " %i %lf \n", nbLances, (double)nbLances/36 );

	// on divise par 36 car il y a 36 lancés de dés possible
	return (double)nbLances / 36.0;
}









int getNbPionsOrJarInterieur( SGameState* gameState, Player maCouleur ) {

	int nbPionsOrJarInterieur = gameState -> bar[ maCouleur ];

	int i_depart = (maCouleur == WHITE) ? 7 : 1;

	Square laCase;
	int i;
	for( i = i_depart; i < i_depart + 18; i++ ) {

		laCase = getCaseReelle( gameState, maCouleur, i );

		if( ! caseEstAuJoueur(laCase, maCouleur) || ! casePossedeDesPions(laCase) ) continue;

		nbPionsOrJarInterieur += laCase.nbDames;
	}

	return nbPionsOrJarInterieur;
}



int getCoefficientEloignementOut( SGameState* gameState, Player maCouleur ) {

	int coefficient = 0;

	Square laCase;

	int eloignement;
	int depart = (maCouleur == WHITE) ? 25 : 0;		// on retire 25 au blanc à cause du sens

	int i;
	for( i = 0; i < 25; i++ ) {

		laCase = getCaseReelle( gameState, maCouleur, i );

		if( ! caseEstAuJoueur(laCase,maCouleur) || ! casePossedeDesPions(laCase) ) continue;

		if( maCouleur == BLACK && i == 0 ) eloignement = 25;	// la barre noire est la plus éloignée du out blanc (mais elle est représentée par 0)
		else eloignement = abs( depart - i ); 

		coefficient += laCase.nbDames * eloignement;
	}

	return coefficient;
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



/*
* Retourne un nombre généré aléatoirement entre min et max compris.
*
*/
int randomINT( int min, int max ) {

	// on vérifie si le générateur aléatoire a été initialisé
	static int generateurInitialise = 0;
    if( ! generateurInitialise ) {		// si ce n'est pas le cas, on l'initialise
        generateurInitialise = 1;
        srand( time(NULL) );
    }

	return ( rand() % (max-min+1) ) + min;
}

