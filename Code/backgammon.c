
/*
	/!\ sur windows, on ne peut pas charger deux fois la même librairie !
		(il ne veut pas charger uen librairie qui a été copiée)
*/


#include <stdio.h>
#include <string.h>		// strlen(), strcmp()
#include <stdlib.h>		// exit()

#include "verifications.h"
#include "joueur.h"
#include "arbitre.h"
#include "graphique.h"





int main( int argc, char* argv[] ) {

	/*
	*	vérification des paramètres entrés par l'utilisateur
	*/

	if( argc <= 1 ) {
		printf(" Erreur, il manque les parametres : \n");
		printf(" 	%s <nbParties> <chemin librairie 1> <chemin librairie 2> \n", argv[0] );
		exit( EXIT_FAILURE );
	}
	
	char* cheminLibrairie_1 = "./libBot.so";	// chargement par défaut
	char* cheminLibrairie_2 = "./libBot.so";					

	// on récupère les librairies entrées (qui sont optionnels)
	if( argc >= 3 ) cheminLibrairie_1 = argv[2];
	if( argc >= 4 ) cheminLibrairie_2 = argv[3];

	// on récupère le nombre de parties à jouer
	int nbParties;
	if( stringToPositiveInteger(argv[1],&nbParties) ) {
		printf(" Erreur, le parametre representant le nombre de parties n'est pas valide. \n");
		printf(" Ce parametre doit etre un entier positif. \n");
		exit( EXIT_FAILURE );
	}


	// cas ou on entre deux fois la même librairie
	// on copie la librairie pour pouvoir l'ouvrir deux fois
	int taille = strlen( cheminLibrairie_2 );
	char nouveauChemin[ taille ];
	int librairie_copiee = 0;		// utilisé pour la suppression de la copie
	if( ! strcmp(cheminLibrairie_1, cheminLibrairie_2) ) { 		// strcmp renvoie 0 si les deux chaines sont identiques

		// ajout de l'extention .copy
		strcpy( nouveauChemin, cheminLibrairie_2 );				
		strcat( nouveauChemin, ".copy" );
		cheminLibrairie_2 = nouveauChemin;


		// on copie la librairie
		if( copierFichier( cheminLibrairie_1, cheminLibrairie_2 ) ) {
			printf( " Erreur lors de la copie de la librairie. \n" );
			exit( EXIT_FAILURE );
		}

		librairie_copiee = 1;
	}


	// chargement des joueurs
	Joueur* joueur1 = chargerJoueur( cheminLibrairie_1 );
	Joueur* joueur2 = chargerJoueur( cheminLibrairie_2 );


	jouerPartie( nbParties, joueur1, joueur2 );




	/*
	*	libération des ressources utilisées
	*/

	libererJoueur( joueur1 );
	libererJoueur( joueur2 );


	if( librairie_copiee ) {

		if( remove(cheminLibrairie_2) ) {
			printf(" Erreur lors de la suppression du fichier temporaire. \n");
		}

	}


	return 0;
}

