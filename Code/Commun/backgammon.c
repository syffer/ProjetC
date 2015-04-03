
#include "verifications.h"
#include "joueur.h"
#include "arbitre.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( int argc, char* argv[] ) {

	/*
	*	vérification des paramètres entrés par l'utilisateur
	*/

	if( argc <= 1 ) {
		printf(" Erreur, il manque les parametres : \n");
		printf(" 	%s <nbPoints> <chemin librairie 1> <chemin librairie 2> \n", argv[0] );
		exit( EXIT_FAILURE );
	}


	char* cheminLibrairie_1 = "./IA/libBotSimplet.so";	// chargement par défaut
	char* cheminLibrairie_2 = "./IA/libBotSimplet.so";


	// on récupère les librairies entrées (qui sont optionnels)
	if( argc >= 3 ) cheminLibrairie_1 = argv[2];
	if( argc >= 4 ) cheminLibrairie_2 = argv[3];

	// on récupère le nombre de parties à jouer
	int nbPoints;
	if( stringToPositiveInteger(argv[1],&nbPoints) ) {
		printf(" Erreur, le parametre representant le nombre de points n'est pas valide. \n");
		printf(" Ce parametre doit etre un entier positif. \n");
		exit( EXIT_FAILURE );
	}


	int tailleLibrairie_1 = strlen( cheminLibrairie_1 );
	int tailleLibrairie_2 = strlen( cheminLibrairie_2 );
	char librairie_1[ tailleLibrairie_1 + 10 ]; 	// "./" + chemin + ".copy"
	char librairie_2[ tailleLibrairie_2 + 10 ];

	int librairie_copiee; 
	if( verifierLibrairies( cheminLibrairie_1, cheminLibrairie_2, librairie_1, librairie_2, &librairie_copiee ) ) {
		printf( " Erreur lors de la copie de la librairie. \n" );
		exit( EXIT_FAILURE );
	}



	// chargement des joueurs
	Joueur joueur1 = chargerJoueur( librairie_1 );
	Joueur joueur2 = chargerJoueur( librairie_2 );


    //afficherPlateau(); // affichage de la fenêtre de jeu et de la partie grapique
	jouerPartie( nbPoints, joueur1, joueur2 );


	/*
	*	libération des ressources utilisées
	*/

	libererJoueur( joueur1 );		// attention, on ne peut plus appeler les fonctions du joueur
	libererJoueur( joueur2 );


	if( librairie_copiee ) {

		if( remove(librairie_2) ) {
			printf(" Erreur lors de la suppression du fichier temporaire. \n");
		}

	}

	return 0;
}

