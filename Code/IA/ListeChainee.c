
#include "ListeChainee.h"
#include "Coup.h"

#include <stdlib.h>
#include <stdio.h>


struct Cellule {
	Donnee valeur;
	Cellule* suivant;
	Cellule* precedent;
};

struct ListeChainee {
	int nbElements;
	Cellule* premier;
	Cellule* dernier;
};





/* operations sur les cellules */
Cellule* getCelluleSuivante( Cellule* cellule ) {
	return cellule -> suivant;
}

Cellule* getCellulePrecedente( Cellule* cellule ) {
	return cellule -> precedent;
}

Donnee getDonnee( Cellule* cellule ) {
	return cellule -> valeur;
}




/* operations dur la liste */

ListeChainee* creerListeChainee() {
	ListeChainee* liste = (ListeChainee*) malloc( sizeof(ListeChainee) );
	
	liste -> nbElements = 0;
	liste -> premier = NULL;
	liste -> dernier = NULL;

	return liste;
}
 


int listeEstVide( ListeChainee* liste ) {
	// si il n'y a pas de premier, ou si il n'y a pas de dernier, ou si nbElements == 0
	return liste -> nbElements == 0;
	//return ! liste -> dernier;
}




Cellule* ajouterElementDebut( ListeChainee* liste, Donnee elem ) {

	Cellule* p_cellule = (Cellule*) malloc( sizeof(Cellule) );

	// on défini la cellule suivante de la nouvele cellule comme étant la premiere de la liste
	p_cellule -> valeur = elem;
	p_cellule -> suivant = liste -> premier;
	p_cellule -> precedent = NULL;

	// si la liste était vide
	// si elle n'avait donc pas de dernier
	if( ! liste -> dernier ) {
		liste -> dernier = p_cellule;
	} 

	// si la liste avait déjà un premier élement
	if( liste -> premier ) {		// liste -> premier != NULL
		liste -> premier -> precedent = p_cellule;
	}

	liste -> premier = p_cellule; 	// on change la premiere cellule de la liste

	liste -> nbElements++;

	return p_cellule;
}



Cellule* ajouterElementFin( ListeChainee* liste, Donnee elem ) {

	Cellule* p_cellule = (Cellule*) malloc( sizeof(Cellule) );

	p_cellule -> valeur = elem;
	p_cellule -> suivant = NULL;
	p_cellule -> precedent = liste -> dernier;

	if( ! liste -> premier ) {			// si il n'y avait pas de premier (liste vide)
		liste -> premier = p_cellule;	// alors la derniere cellule est aussi la premiere
	}

	if( liste -> dernier ) {		// si il y avait deja une derniere cellule
		liste -> dernier -> suivant = p_cellule;		// on dit que la cellule suivante de la derniere est ma nouvelle cellule
	}

	liste -> dernier = p_cellule;

	liste -> nbElements++;

	return p_cellule;
}


Cellule* ajouterElementApres( ListeChainee* liste, Cellule* cellule, Donnee elem ) {
	if( cellule == liste -> dernier ) {
		return ajouterElementFin( liste, elem );
	}

	Cellule *p_cellule = (Cellule*) malloc( sizeof(Cellule) );

	p_cellule -> valeur = elem;
	p_cellule -> suivant = cellule -> suivant;
	p_cellule -> precedent = cellule;

	cellule -> suivant -> precedent = p_cellule;
	cellule -> suivant = p_cellule;

	liste -> nbElements++;

	return p_cellule;
}



Cellule* getPremierElement( ListeChainee* liste ) {
	return liste -> premier;
}


Cellule* getDernierElement( ListeChainee* liste ){
	return liste -> dernier;
}

int getNbElements( ListeChainee* liste ) {
	return liste -> nbElements;
}








/*
void afficherListe( ListeChainee* liste ) {

	printf("\n NULL -> ");

	Cellule* cellule = getPremierElement( liste );
	while( cellule ) {
		printf( " %i -> ", getDonnee(cellule) );
		cellule = getCelluleSuivante(cellule);
	}
	printf(" NULL\n ");

	cellule = getDernierElement( liste );
	while( cellule ) {
		printf( " %i <- ", getDonnee(cellule) );
		cellule = getCellulePrecedente(cellule);
	}


}
*/





void detruireCellule( ListeChainee* liste, Cellule* cellule ) {

	if( cellule == liste -> premier ) liste -> premier = cellule -> suivant;
	else cellule -> precedent -> suivant = cellule -> suivant;
	
	if( cellule == liste -> dernier ) liste -> dernier = cellule -> precedent;
	else cellule -> suivant -> precedent = cellule -> precedent;

	free( cellule );

	liste -> nbElements--;
}


void detruireListeChainee( ListeChainee* liste ) {

	Cellule* p_cellule = liste -> premier;
	Cellule* p_aDetruire;

	// on libère la mémoire allouée à chaque cellule contenu dans la liste
	while( p_cellule ) {	// equivaux à : p_cellule != NULL

		p_aDetruire = p_cellule;			

		p_cellule = p_cellule -> suivant;	

		free( p_aDetruire );

		/*
		pour ne pas "casser" le chainage lors de la suppression de la cellule courante,
		on sauvegarde la cellule a détuire (cellule courante) et la cellule suivante 
		*/
	}

	// on libère la mémoire allouée à la liste elle meme
	free( liste );
}





int getDonneeMax( ListeChainee* liste, p_fonctionComparaisonDonnee comparaison, Donnee* donneeMax ) {

	int nbCoups = getNbElements(liste);
	if( nbCoups == 0 ) {
		printf("la liste est vide, pas de maximum \n");
		return -1;
	}

	Cellule* cellule = getPremierElement(liste);
	Donnee donneeMaximale = getDonnee(cellule);
	Donnee donneeActuelle;


	int i;
	for( i = 1; i < nbCoups; i++ ) {

		cellule = getCelluleSuivante(cellule);
		donneeActuelle = getDonnee(cellule);

		if( comparaison(&donneeActuelle, &donneeMaximale) ) donneeMaximale = donneeActuelle; 
	}

	*donneeMax = donneeMaximale;

	return 0;
}

