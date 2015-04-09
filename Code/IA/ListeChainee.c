/*
	Fichier contenant toutes les fonctions et structures concernant la liste chainée
	Cette liste est utilisée pour stocker des structures Coup
*/

#include "ListeChainee.h"
#include "Coup.h"

#include <stdlib.h>
#include <stdio.h>


/** Définition de la structure Cellule
 * @attribut valeur : la valeur de la cellule
 * @attribut suivant : la cellule suivante
 * @attribut precedent : la cellule précédente
 * */
struct Cellule {
	Donnee valeur;
	struct Cellule* suivant;
	struct Cellule* precedent;
};

/** Définition de la structure correspondant aux listes chaînées
 * @attribut nbElements : le nombre d'éléments dans la liste
 * @attribut premier : le premier élément de la liste
 * @attribut dernier : le dernier élément de la liste
 * */
struct ListeChainee {
	int nbElements;
	struct Cellule* premier;
	struct Cellule* dernier;
};


/* operations sur les cellules */


/** Retourne un pointeur vers la cellule suivante
 * @param cellule : la cellule actuelle
 * @return : un pointeur de cellule ou NULL s'il n'y a pas de cellule suivante
 * */
Cellule* getCelluleSuivante( Cellule* cellule ) {
	return cellule -> suivant;
}

/** Retourne un pointeur vers la cellule précédente
 * @param cellule : la cellule actuelle
 * @return : un pointeur de cellule ou NULL s'il n'y a pas de cellule précédente
 * */
Cellule* getCellulePrecedente( Cellule* cellule ) {
	return cellule -> precedent;
}

/** Retourne la valeur d'une cellule
 * @param cellule : la cellule actuelle
 * @return : la donnée
 * */
Donnee getDonnee( Cellule* cellule ) {
	return cellule -> valeur;
}


/* operations dur la liste */


/** Créer et initialiser une liste
 * @return : une liste vide
 * */
ListeChainee* creerListeChainee() {
	ListeChainee* liste = (ListeChainee*) malloc( sizeof(ListeChainee) );
	
	liste -> nbElements = 0;
	liste -> premier = NULL;
	liste -> dernier = NULL;

	return liste;
}
 
/** Vérifie si une liste est vide
 * @param liste : la liste à tester
 * @return : un booléen (0 = faux, le reste = vrai)
 * */
int listeEstVide( ListeChainee* liste ) {
	// si il n'y a pas de premier, ou si il n'y a pas de dernier, ou si nbElements == 0
	return liste -> nbElements == 0;
}

/** Ajoute un élément en début de liste
 * @param liste : la liste
 * @param elem : l'élément
 * @return : un pointeur de cellule
 * */
Cellule* ajouterElementDebut( ListeChainee* liste, Donnee elem ) {
	Cellule* p_cellule = (Cellule*) malloc( sizeof(Cellule) );

	// on définit la cellule suivante de la nouvele cellule comme étant la premiere de la liste
	p_cellule -> valeur = elem;
	p_cellule -> suivant = liste -> premier;
	p_cellule -> precedent = NULL;

	// si la liste était vide, elle n'a pas de dernier
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

/** Ajoute un élément en fin de liste
 * @param liste : la liste
 * @param elem : l'élément
 * @return : un pointeur de cellule
 * */
Cellule* ajouterElementFin( ListeChainee* liste, Donnee elem ) {
	Cellule* p_cellule = (Cellule*) malloc( sizeof(Cellule) );

	p_cellule -> valeur = elem;
	p_cellule -> suivant = NULL;
	p_cellule -> precedent = liste -> dernier;

	if( ! liste -> premier ) {		// si il n'y avait pas de premier (liste vide)
		liste -> premier = p_cellule;	// alors la derniere cellule est aussi la premiere
	}

	if( liste -> dernier ) {	// si il y avait deja une derniere cellule
		liste -> dernier -> suivant = p_cellule;	// on dit que la cellule suivante de la derniere est ma nouvelle cellule
	}

	liste -> dernier = p_cellule;

	liste -> nbElements++;

	return p_cellule;
}

/** Ajoute un élément après une cellule
 * @param liste : la liste
 * @param cellule : la cellule après laquelle on veut insérer
 * @param elem : l'élément
 * @return : un pointeur de cellule
 * */
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

/** Renvoi le premier élément de la liste
 * @param liste : la liste
 * @return : un pointeur de cellule
 * */
Cellule* getPremierElement( ListeChainee* liste ) {
	return liste -> premier;
}

/** Renvoi le dernier élément de la liste
 * @param liste : la liste
 * @return : un pointeur de cellule
 * */
Cellule* getDernierElement( ListeChainee* liste ){
	return liste -> dernier;
}

/** Renvoi le nombre d'éléments de la liste
 * @param liste : la liste
 * @return : un entier positif
 * */
int getNbElements( ListeChainee* liste ) {
	return liste -> nbElements;
}

/** Détruit une cellule
 * @param liste : la liste
 * @param cellule : la cellule à détruire
 * */
void detruireCellule( ListeChainee* liste, Cellule* cellule ) {
	if( cellule == liste -> premier ) liste -> premier = cellule -> suivant;
	else cellule -> precedent -> suivant = cellule -> suivant;
	
	if( cellule == liste -> dernier ) liste -> dernier = cellule -> precedent;
	else cellule -> suivant -> precedent = cellule -> precedent;

	free( cellule );
	liste -> nbElements--;
}

/** Détruit une liste et toutes les cellules qu'elle contient
 * @param liste : la liste
 * */
void detruireListeChainee( ListeChainee* liste ) {
	Cellule* p_cellule = liste -> premier;
	Cellule* p_aDetruire;

	// on libère la mémoire allouée à chaque cellule contenue dans la liste
	while( p_cellule ) {	// equivaut à : p_cellule != NULL
		/*
		pour ne pas "casser" le chainage lors de la suppression de la cellule courante,
		on sauvegarde la cellule a détuire (cellule courante) et la cellule suivante 
		*/
		p_aDetruire = p_cellule;			
		p_cellule = p_cellule -> suivant;
		
		free( p_aDetruire );
	}

	// on libère la mémoire allouée à la liste elle-meme
	free( liste );
}

/** Renvoi la donnée maximale contenue dans la liste
 * @param liste : la liste
 * @param comparaison : la fonction de comparaison à utiliser
 * @param donneeMax : la donnée à récupérer
 * @return : un entier
 * */
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

		if( comparaison(&donneeActuelle, &donneeMaximale) == 1 ) donneeMaximale = donneeActuelle; 
	}

	*donneeMax = donneeMaximale;
	return 0;
}

/** Applique une fonction aux éléments de la liste
 * @param liste : la liste
 * @param fonctionElement : la fonction à appliquer
 * */
void appliquerFonctionSurElement( ListeChainee* liste, p_fonctionElement fonctionElement ) {
	Cellule* cellule = getPremierElement(liste);

	while( cellule ) {
		fonctionElement( &(cellule -> valeur) );
		cellule = getCelluleSuivante(cellule);
	}
}