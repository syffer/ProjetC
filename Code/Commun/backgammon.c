/*
	Fichier contenant la fonction main du programme.

*/
#include "verifications.h"
#include "joueur.h"
#include "arbitre.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>	// dup2()
#include <fcntl.h> 	// open()


int main( int argc, char* argv[] ) {

	/*
	*	Création du fichier de log (redirection de la sortie standard vers se fichier)
	*/
	int fichier_log = open( "./backgammon.log", O_WRONLY | O_APPEND | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO );
	if( fichier_log == -1 ) {
		printf(" Erreur lors de l'ouverture ou la création du fichier de log.\n");
		exit( EXIT_FAILURE );
	}

	// redirection de la sortie standard vers le fichier log
	if( dup2( fichier_log, STDOUT_FILENO ) == -1 ) {
		printf(" Erreur lors de la redirection de la sortie standard vers le fichier log \n");
		exit( EXIT_FAILURE );
	}
	



	/*
	*	vérification des paramètres entrés par l'utilisateur
	*/

	if( argc <= 1 ) {
		printf(" Erreur, il manque les parametres : \n");
		printf(" 	%s <nbPoints> <chemin librairie 1> <chemin librairie 2> \n", argv[0] );
		exit( EXIT_FAILURE );
	}

	// chargement par défaut
	char* cheminLibrairie_1 = "./Commun/libJoueur.so";		// on charge un joueur réel
	char* cheminLibrairie_2 = "./Commun/libJoueur.so";


	// on récupère les librairies entrées (qui sont optionnels)
	int estUnBot[2] = {0};
	if( argc >= 3 ) {
		estUnBot[ BLACK ] = 1;
		cheminLibrairie_1 = argv[2];
	}
	if( argc >= 4 ) {
		estUnBot[ WHITE ] = 1;
		cheminLibrairie_2 = argv[3];
	}


	// on récupère le nombre de parties à jouer
	int nbPoints;
	if( stringToPositiveInteger(argv[1],&nbPoints) || nbPoints <= 0 ) {
		printf(" Erreur, le parametre representant le nombre de points n'est pas valide. \n");
		printf(" Ce parametre doit etre un entier positif superieur a zero. \n");
		exit( EXIT_FAILURE );
	}


	int tailleLibrairie_1 = strlen( cheminLibrairie_1 );
	int tailleLibrairie_2 = strlen( cheminLibrairie_2 );
	char librairie_1[ tailleLibrairie_1 + 10 ]; 	// "./" + chemin + ".copy"
	char librairie_2[ tailleLibrairie_2 + 10 ];

	int librairie_copiee;	// est à vrai si une librairie a été copiée
	if( verifierLibrairies( cheminLibrairie_1, cheminLibrairie_2, librairie_1, librairie_2, &librairie_copiee ) ) {
		printf( " Erreur lors de la copie de la librairie. \n" );
		exit( EXIT_FAILURE );
	}



	// chargement des joueurs
	Joueur joueurs[2];
	joueurs[ BLACK ] = chargerJoueur( librairie_1 );
	joueurs[ WHITE ] = chargerJoueur( librairie_2 );

	jouerPartie( nbPoints, joueurs, estUnBot );


	/*
	*	libération des ressources utilisées
	*/

	libererJoueur( joueurs[ BLACK ] );		// attention, on ne peut plus appeler les fonctions du joueur
	libererJoueur( joueurs[ WHITE ] );


	if( librairie_copiee ) {

		if( remove(librairie_2) ) {
			printf(" Erreur lors de la suppression du fichier temporaire. \n");
		}

	}

	return 0;
}

