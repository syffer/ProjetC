#ifndef _ListeChainee
	#define _ListeChainee


#include "../Commun/backgammon.h"

// combinaison de mouvements
struct Coup {
	
	SMove mouvements[4];
	int nbMouvements;

	SGameState gameState;
	unsigned char dices[4];
	
};
typedef struct Coup Coup;



typedef Coup Donnee;
typedef struct Cellule Cellule;
typedef struct ListeChainee ListeChainee;




/* operations sur les cellules */
Cellule* getCelluleSuivante( Cellule* cellule );
Cellule* getCellulePrecedente( Cellule* cellule );
Donnee getDonnee( Cellule* cellule );


/* operations dur la liste */

ListeChainee* creerListeChainee();

int listeEstVide( ListeChainee* liste );

Cellule* ajouterElementDebut( ListeChainee* liste, Donnee valeur );
Cellule* ajouterElementFin( ListeChainee* liste, Donnee valeur );
Cellule* ajouterElementApres( ListeChainee* liste, Cellule* cellule, Donnee valeur );

Cellule* getPremierElement( ListeChainee* liste );
Cellule* getDernierElement( ListeChainee* liste );
int getNbElements( ListeChainee* liste );

//void afficherListe( ListeChainee* liste );

void detruireCellule( ListeChainee* liste, Cellule* cellule_aDetruire );
void detruireListeChainee( ListeChainee* liste );




#endif