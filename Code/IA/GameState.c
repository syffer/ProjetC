/*
	Fichier contenant les fonctions concernant l'état du jeu (GameState, SMove, Square, Player...)
	
	Auteurs :
	- Pauline HOULGATTE
	- Maxime PINEAU	

*/

#include "GameState.h"

#include <stdio.h>
#include <stdlib.h>  
#include <time.h>

/** Renvoi la valeur des dés
 * @param dice : les dés tirés
 * @param newDices : la récupération des dés (les duplique en cas de double)
 * */
void getDices( const unsigned char dices[2], unsigned char newDices[4] ) {
	// on a fait un double (exemple : 1-1 , 2-2 , ... 6-6 )
	if( dices[0] == dices[1] ) {
		int i;
		for( i = 0; i < 4; i++ ) newDices[i] = dices[0];
	}
	else {
		newDices[0] = dices[0];
		newDices[1] = dices[1];
		newDices[2] = newDices[3] = 0; // dés déjà utilisés ou non existants
	}
}

/** Fonction pour libJoueur.c
 * @param dices : les dés
 * @param valeurDe : la valeur du dé cherchée
 * @return : la position ou -1 si non trouvée
 * */
int rechercherPositionValeurDe( unsigned char dices[2], char valeurDe ) {
	int i;
	for( i = 0; i < 4; i++ ) {
		if( dices[i] == valeurDe ) return i;
	}
	return -1;
}

/** Indique si un joueur peut encore jouer un coup
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @param dices : les dés
 * @return : un boolée
 * */
int peutEncoreJoueur( SGameState* gameState, Player maCouleur, unsigned char dices[2] ) {
	int i, j;
	for( i = 0; i < 25; i++ ) {
		for( j = 0; j < 4; j++ ) {
			if( peutDeplacerUnPion( gameState, maCouleur, i, dices[j] ) ) return 1;
		}	
	}
	return 0;
}

/** Retourne la couleur de l'adversaire
 * @param maCouleur : la couleur du joueur
 * @return : la couleur de l'adversaire ou NOBODY si la paramètre == NOBODY
 * */
Player getCouleurAdverse( Player maCouleur ) {
	if( maCouleur == WHITE ) return BLACK;
	else if( maCouleur == BLACK ) return WHITE;
	else return NOBODY;
}

/** Initilise un mouvement
 * @param mouvement : le mouvement
 * @param maCouleur : la couleur du joueur
 * @param depart : la case départ
 * @param nbCases : le nombre de cases
 * */
void initialiserMouvement( SMove* mouvement, Player maCouleur, int depart, int nbCases ) {
	int arrivee;
	if( maCouleur == WHITE ) arrivee = depart + nbCases;
	else if( depart == 0 ) arrivee = 25 - nbCases;		// j'ai la couleur noire
	else arrivee = depart - nbCases;

	if( arrivee > 25 || arrivee <= 0 ) arrivee = 25;	

	mouvement -> src_point = depart;
	mouvement -> dest_point = arrivee;
}

/** Récupère la case à la position i
 * @param gameState :
 * @param maCouleur : la couleur du joueur
 * @param i : la position
 * @return : la case
 * 
 * Convention :
 * - 0 : la barre (gamestate -> bar[macouleur] )
 * - 1 à 24 : le plateau 
 * - 25 : la sortie (out)
 * */
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

/** Vérifie si une case possède un ou plusieurs pions
 * @param laCase : la case à vérifier
 * @return : un booléen
 * */
int casePossedeDesPions( Square laCase ) {
	return laCase.nbDames > 0;
}

/** Vérifie si un case appartient au joueur
 * @param laCase : la case à contrôler
 * @param couleurJoueur : la couleur du joueur
 * @return : un booléen
 * */
int caseEstAuJoueur( Square laCase, Player couleurJoueur ) {
	return laCase.owner == couleurJoueur;
}

/** Vérifie si un case contient au moins deux pions
 * @param laCase : la case à contrôler
 * @return : un booléen
 * */
int caseEstSecurisee( Square laCase ) {
	return laCase.nbDames > 1;
}

/** Indique si il y a des pions sur la barre
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @return : un booléen
 * */
int joueurPossedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur ) {
	return gameState -> bar[ maCouleur ];
}

/** Déplace un pion sur le plateau
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @param mouvement : le mouvement
 * @return : 0 si tout s'est bien passé, -1 sinon
 * */
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

/** Indique si un pion peut être déplacé d'un certain nombre de case
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @param depart : la case de départ
 * @param nbCases : le nombre de cases du déplacement
 * @return : un booléen
 * */
int peutDeplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases ) {
	// déplacements impossibles
	if( depart < 0 || depart > 24 ) return 0;
	if( nbCases <= 0 ) return 0;

	// initialisation du mouvement
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

/** Affiche le plateau
 * @param gameState : le plateau
 * */
void afficherGameState( SGameState gameState ) {
	char* nom;
	printf("\n");
		
	printf( "   out BLACK nbDames %i \n", gameState.out[BLACK] );
	printf( "   bar WHITE nbDames %i \n", gameState.bar[WHITE] );

	int i;
	for( i = 0; i < 24; i++ ) {
		if( gameState.board[i].owner == BLACK ) nom = "BLACK";
		else if( gameState.board[i].owner == WHITE  ) nom = "WHITE";
		else nom = "NOBODY";
		printf( "   case %i nbDames %i %s \n", i+1, gameState.board[i].nbDames, nom );
	}

	printf( "   bar BLACK nbDames %i \n", gameState.bar[BLACK] );
	printf( "   out WHITE nbDames %i \n", gameState.out[WHITE] );
	printf("\n");
}

/** Retourne le nombre de cases contenant au moins deux pions
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @return : un entier positif
 * */
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

/** Retourne la probalité qu'un joueur se fasse prendre un pion au prochain tour
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @return : un flottant (la probabilité)
 * */
double getProbabilitePerdreUnPion( SGameState* gameState, Player maCouleur ) {
	int valeurDes[25] = {0};
	getEloignementsPointsNonSecurisees( gameState, maCouleur, valeurDes );
	return getProbabiliteeDeFaireUnDesDes(valeurDes);
}

/** Remplit un tableau qui contiendra le nombre de cases séparant les cases non sécurisées d'un joueur à celles de son adversaire
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @param eloignement : le tableau
 * 
 * Exemple : on a la configuration suivante  : - - B - - N - B - - - 
 * 	le tableau contiendra (si l'on considère le joueur blanc) :
 * - tab[0] = 0
 * - tab[1] = 0 
 * - tab[2] = 1  	car un pion blanc est éloigné de deux cases par rapport à tous les pions noirs
 * - tab[3] = 1 	car un pion blanc est éloigné de trois cases par rapport à tous les pions noirs
 * */
void getEloignementsPointsNonSecurisees( SGameState* gameState, Player maCouleur, int eloignements[25] ) {
	Square caseDepart, caseArrivee;
	Player couleurAdversaire = getCouleurAdverse(maCouleur);

	int eloigement;
	int j_depart = 1;
	int j_arrivee = 24;

	if( maCouleur == BLACK ) {	// les pions blancs avancent dans le sens inverse
		j_depart = -24;
		j_arrivee = -1;
	}

	int i, j;
	for( i = 1; i < 25; i++ ) {		// on parcourt chaque case du plateau
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

/** Retourne la probabilitée de faire l'une des 25 valeurs de dé possibles
 * @param  valeurDes : la valeur des dés
 * @return :  un flottant
 * 
 * Exemple : si l'on la probabilité de faire les chiffres 1 et 24 avec les dés:
 * - tab[1] = 11
 * - tab[24] = 1
 * - cette fonction renverra donc : 12 / 36  (car il n'y a que 36 combinaisons de dés possibles)
 * */
double getProbabiliteeDeFaireUnDesDes( int valeurDes[25] ) {
	int nbLances = 0;
	int i, j;

	for( i = 1; i <= 6; i++ ) {		// on lance le 1er dé
		for( j = 1; j <= 6; j++ ) {		// on lance le 2eme dé
			if( valeurDes[i] ) nbLances += 1;		// on fait l'une des valeurs recherchées avec le 1er dé
			else if( valeurDes[j] ) nbLances += 1; 		// on fait l'une des valeurs recherchées avec le 2eme dé
			else if( valeurDes[i+j] ) nbLances += 1;		// on fait l'une des valeurs recherchées avec la somme des deux dés
			else if( i == j ) {		// cas où l'on possède 4 dés
				if( valeurDes[3*i] || valeurDes[4*i] ) nbLances += 1;
			}
		}
	}
	// on divise par 36 car il y a 36 lancés de dés possibles
	return (double)nbLances / 36.0;
}

/** Calcule le nombre de pions hors des jans
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @return : un entier positif
 * */
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

/** Calcule l'éloignement des pions par rapport à la sortie
 * @param gameState : le plateau
 * @param maCouleur : la couleur du joueur
 * @return : un entier positif
 * */
int getEloignementOut( SGameState* gameState, Player maCouleur ) {
	// déclaration des variables
	int nbPions = 15;
	Square laCase;
	int i;
	int j = (maCouleur==WHITE) ? 25 : 7;

	// on récupère les pions sur se situant près de la sortie (position 19 à 25 || position 1 à 6 et 25)
	for( i = (j-6); i < j; i++ ) {
		laCase = getCaseReelle( gameState, maCouleur, i );
		if( caseEstAuJoueur(laCase,maCouleur) && casePossedeDesPions(laCase) ) nbPions -= laCase.nbDames;
	}
	laCase = getCaseReelle( gameState, maCouleur, 25 );
	if( casePossedeDesPions(laCase) ) nbPions -= laCase.nbDames;
	
	return nbPions;
}

/** Calcule un coût à une cellule  
 * @param gameState : le plateau
 * @return : un entier positif
 * */
int calculerCout( SGameState* gameState ) {
	Player maCouleur = gameState -> turn;
	int totalePoints = 0;
	int i;
	
	/* on augmente le coût d'une cellule si elle :
	- est adverse et peut être prise (cas que l'on favorise)
	- est vide
	- est à nous et seulement un de nos jetons l'occupe
	- est à nous et plus de deux jetons l'occupent
	*/
	for( i = 1; i < 25; i++ ) {
		if( gameState -> board[i].owner != maCouleur && gameState -> board[i].nbDames == 1 ) totalePoints += 3;
		else if( gameState -> board[i].owner != maCouleur && gameState -> board[i].nbDames == 0 ) totalePoints += 2;
		else if( gameState -> board[i].owner == maCouleur && gameState -> board[i].nbDames == 1 ) totalePoints += 2;
		else if( gameState -> board[i].owner == maCouleur && gameState -> board[i].nbDames > 1 ) totalePoints++;
	}

	return totalePoints;
}

/** Retourne un nombre généré aléatoirement dans un intervalle
 * @param min : le minimum
 * @param max : le maximum
 * @return : un entier
 * */
int randomINT( int min, int max ) {
	// on vérifie si le générateur aléatoire a été initialisé
	static int generateurInitialise = 0;
    if( ! generateurInitialise ) {		// si ce n'est pas le cas, on l'initialise
        generateurInitialise = 1;
        srand( time(NULL) );
    }
	return ( rand() % (max-min+1) ) + min;
}