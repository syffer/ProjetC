#ifndef _fonctionsBot
	#define _fonctionsBot


#include "backgammon.h"
#include "ListeChainee.h"


// signature des fonctions communes
struct Bot {
	
	char nom[50];
	Player maCouleur;
	unsigned int scoreCible;	// ??
	
	SGameState gameState;	   // ??
	
};
typedef struct Bot Bot;




// combinaison de mouvements
struct Coup {
	
	SMove mouvements[4];
	int nbMouvements;

};
typedef struct Coup Coup;



ListeChainee* getDices( const unsigned char dices[2] );


Square getCaseReelle( SGameState* gameState, Player maCouleur, int i );
int possedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur );
int peutDeplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases );
SGameState deplacerUnPion( SGameState gameState, Player maCouleur, SMove mouvement );

SMove creerMouvement( int depart, int arrivee );
SMove creerMouvementJoueur( Player maCouleur, int depart, int nbCases );

void initialiserCoup( Coup* coup );
void ajouterMouvementAuCoup( Coup* coup, SMove mouvement );

void calculerCoupsPossibles( SGameState* gameState, Player maCouleur, ListeChainee* dices, Coup coups[], int* nbCoupsPossibles );


/*
chaque fonction de comparaison renvoie :
- 1 si la première valeur est supérieur à la seconde,
- 0 si les deux valeurs sont égales (au niveau des rangs)
- -1 si la première valeur est inférieur à la seconde
*/

typedef int (*pFonctionComparaison)( Coup c1, Coup c2 );
int test( Coup c1, Coup c2);

typedef Coup Data;
void triRapide_rec( Data tableau[], pFonctionComparaison f_comparaison, int borneInf, int borneSup );
void triRapide( Data tableau[], int taille, pFonctionComparaison f_comparaison );



#endif