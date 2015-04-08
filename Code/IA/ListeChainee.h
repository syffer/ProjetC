/*

	Fichier contenant toutes les fonctions et structures concernant la liste chainée

	Cette liste est utilisée pour stocké des structures Coup

*/
#ifndef _ListeChainee
	#define _ListeChainee


#include "../Commun/backgammon.h"
#include "GameState.h"
#include "Coup.h"



typedef Coup Donnee;

typedef struct Cellule Cellule;

typedef struct ListeChainee ListeChainee;




/* operations sur les cellules */
Cellule* getCelluleSuivante( Cellule* cellule );
Cellule* getCellulePrecedente( Cellule* cellule );
Donnee getDonnee( Cellule* cellule );


/* operations sur la liste */

ListeChainee* creerListeChainee();

int listeEstVide( ListeChainee* liste );

Cellule* ajouterElementDebut( ListeChainee* liste, Donnee valeur );
Cellule* ajouterElementFin( ListeChainee* liste, Donnee valeur );
Cellule* ajouterElementApres( ListeChainee* liste, Cellule* cellule, Donnee valeur );

Cellule* getPremierElement( ListeChainee* liste );
Cellule* getDernierElement( ListeChainee* liste );
int getNbElements( ListeChainee* liste );

void detruireCellule( ListeChainee* liste, Cellule* cellule_aDetruire );
void detruireListeChainee( ListeChainee* liste );



/*
	retourne :
		1  si c1 > c2
		0  si c1 == c2
		-1 si c1 < c2
*/
typedef int (p_fonctionComparaisonDonnee)( Donnee* c1, Donnee* c2 );

int getDonneeMax( ListeChainee* liste, p_fonctionComparaisonDonnee comparaison, Donnee* donneeMax );



typedef void (p_fonctionElement)(Donnee* donnee);
void appliquerFonctionSurElement( ListeChainee* liste, p_fonctionElement fonctionElement );



#endif