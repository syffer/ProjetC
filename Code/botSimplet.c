
/*

	Bot ne faisant qu'avancer ses pions les plus éloignés.

*/

#include <stdio.h>
#include <string.h>

#include "backgammon.h"
#include "ListeChainee.h"


char nom[] = "SimpletBot";
unsigned int score;
static Player maCouleur;


/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associé à la librairie
 */
void InitLibrary( char name[50] ) {
	strcpy( name, nom );
	score = 0;
	maCouleur = NOBODY;
}


/**
 * Initialiser l'IA pour un match
 * @param const unsigned int target_score
 *	score cible pour gagner un match
 */
void StartMatch( const unsigned int target_score ) {
	score = target_score;
}


/**
 * Initialiser l'IA pour une manche (d'un match)
 */
void StartGame(Player p) {
	maCouleur = p;
}


/**
 * Fin d'une manche (d'un match)
 */
void EndGame() {
	maCouleur = NOBODY;
}


/**
 * Fin d'un match
 */
void EndMatch() {

	///////////////////////////////////////////////
	// LIBERATION PROPRE DE TOUTES LES RESSOURCES
	//						TOUTES
	///////////////////////////////////////////////
}


/**
 * Doubler la mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on propose de doubler : faux sinon
 */
int DoubleStack( const SGameState * const gameState ) {
	// on ne double jamais la mise
	return(0);		
}


/**
 * Accepter ou refuser la nouvelle mise
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @return int
 *	vrai si on accepte la nouvelle mise ; faux sinon
 */
int TakeDouble( const SGameState * const gameState ) {
	// on ne refuse jamais la nouvelle mise
	return(1);
}

















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
int peutDeplacerUnPion( SGameState* gameState, int depart, int nbCases ) {

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
SMove deplacerUnPion( SGameState* gameState, int depart, int nbCases ) {

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



int possedeDesPionsSurLaBarre( SGameState* gameState ) {
	return gameState -> bar[ maCouleur ];
}



/**
 * Prise de décision de la part de l'IA
 * @param const SGameState * const gameState
 *	l'état du jeu courant
 * @param SMove moves[4]
 *	tableau des mouvements à effectuer par l'IA
 * @param unsigned int tries
 *	nombre d'essais restants (3 initialement).
 */
// !!!!!!!!!!!!!!!!!!! on an enlevé les const pour pouvoir modifier gameState
void PlayTurn( SGameState * gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries ) {
	

	*nbMove = 0;

	// on est obligé d'utiliser tout les dés SAUF lorsque ce n'est pas possible....
	ListeChainee* mesDes = getDices( dices ); 	// mes dés
	
	
	Cellule* dice;	// variable utilisée pour parcourir la liste des dés.


	// on est obligé de remettre en jeu TOUS nos pions
	if( possedeDesPionsSurLaBarre(gameState) ) {

		printf(" -> je dois rerentrer les pions sortie du plateau...\n");

		dice = getPremierElement(mesDes);
		while( gameState -> bar[maCouleur] ) {

			if( !dice ) break;

			if( peutDeplacerUnPion( gameState, 0, getDonnee(dice) ) ) {
				
				printf("on peut bouger un pion avec ce dé...\n");

				moves[ *nbMove ] = deplacerUnPion( gameState, 0, getDonnee(dice) );
				*nbMove++;
			

				dice = getCelluleSuivante(dice);
				detruireCellule( mesDes, getCellulePrecedente(dice) );
			}
			else dice = getCelluleSuivante(dice);
		}

	}



	/*
	regarder si, avec les dés, on peut :
	- prendre un pion adverse
	- prendre un piont (au moins deux pions sur le même triangle)
	(- créer une ancre ?)
	*/


	// si j'ai utilisé tout mes dés, ou qu'il y a encore des pions sur la barre (alors que j'ai utilisé tout les dés)
	if( listeEstVide(mesDes) || possedeDesPionsSurLaBarre(gameState) ) return;


	// si je n'ai pas utilisé tout mes dés, et qu'il n'y a plus rien en dehors du plateau

	int i;
	int position;

	for( i = 1; i < 25; i++ ) {

		if( listeEstVide(mesDes) ) break;

		dice = getPremierElement(mesDes);
		while( dice ) {
		
			position = (maCouleur == BLACK) ? i : 24 - i;

			if( peutDeplacerUnPion(gameState, position, getDonnee(dice) ) ) {

				moves[ *nbMove ] = deplacerUnPion( gameState, position, getDonnee(dice) );
				*nbMove++;

				dice = getCelluleSuivante(dice);
				detruireCellule( mesDes, getCellulePrecedente(dice) );
			}
			else dice = getCelluleSuivante(dice);
		}


	}



}




