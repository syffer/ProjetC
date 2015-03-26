
// windows de merde qui n'est pas foutu d'avoir <dlfcn.h>
#ifdef _WIN32
	#include <windows.h>

	#define Librairie HMODULE
	#define chargerLibrairie(nomLib) LoadLibrary(nomLib)
	#define TypeFonction FARPROC
	#define extraireLibrairie(libType, nomFonction) GetProcAddress(libType, nomFonction)
	#define fermerLibrairie(libType) FreeLibrary(libType)

#endif

#ifdef linux
	#include <dlfcn.h>

	#define Librairie void*
	#define chargerLibrairie(nomLib) dlopen(nomLib, RTLD_LAZY)
	#define TypeFonction void
	#define extraireLibrairie(libType, nomFonction) dlsym(libType, nomFonction)
	#define fermerLibrairie(libType) dlclose(libType)

#endif


#include "backgammon.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// time pour aléatoire
#include "graphique.h"


struct Joueur {
	Librairie librairie;

	pfInitLibrary InitLibrary;
	pfStartMatch StartMatch;
	pfStartGame StartGame;
	pfEndGame EndGame;
	pfEndMatch EndMatch;
	pfDoubleStack DoubleStack;
	pfTakeDouble TakeDouble;
	pfPlayTurn PlayTurn;
};
typedef struct Joueur Joueur;



void erreurChargementFonction( char* nomLib, char* nomFonction ) {
	printf(" Erreur lors du chargement de la fonction %s du joueur %s \n", nomFonction, nomLib );
	exit(-1);
}


/*
* Charge une librairie statégie et retourne la structure joueur correspondante.
* La structure joueur contiendra sa librairie (pour pouvoir la fermée plus tard) et ses propres fonctions
*
* Attention, cette fonction termine le programme avec exit(-1) si elle n'arrive pas à charger la librairie ou l'une des fonctions attendues
*
* @param char* nomLibrairie
*	le chemin de la librairie a chargé
*
* @return Joueur
*	la structure joueur contenant la librairie et les fonctions qui lui sont associé.
*/
Joueur chargerJoueur( char* nomLibrairie ) {

	Librairie lib;

	// on charge la librairie
	if( !( lib = chargerLibrairie(nomLibrairie) ) ) {
		printf( " Erreur, impossible de charger la librairie %s \n", nomLibrairie );
		exit(-1);
	}

	Joueur* joueur = malloc( sizeof(Joueur) );

	joueur -> librairie = lib;
	joueur -> InitLibrary = (pfInitLibrary) extraireLibrairie( lib, "InitLibrary" );
	joueur -> StartMatch = (pfStartMatch) extraireLibrairie( lib, "StartMatch" );
	joueur -> StartGame = (pfStartGame) extraireLibrairie( lib, "StartGame" );
	joueur -> EndGame = (pfEndGame) extraireLibrairie( lib, "EndGame" );
	joueur -> EndMatch = (pfEndMatch) extraireLibrairie( lib, "EndMatch" );
	joueur -> DoubleStack = (pfDoubleStack) extraireLibrairie( lib, "DoubleStack" );
	joueur -> TakeDouble = (pfTakeDouble) extraireLibrairie( lib, "TakeDouble" );

	// on vérifie si toutes les fonctions on bien été chargées
	// /!\ ces fonctions peuvent faire sortir du programme principal ( exit(-1) )
	if( !joueur -> InitLibrary ) erreurChargementFonction( nomLibrairie, "InitLibrary" );
	if( !joueur -> StartMatch ) erreurChargementFonction( nomLibrairie, "StartMatch" );
	if( !joueur -> StartGame ) erreurChargementFonction( nomLibrairie, "StartGame" );
	if( !joueur -> EndGame ) erreurChargementFonction( nomLibrairie, "EndGame" );
	if( !joueur -> EndMatch ) erreurChargementFonction( nomLibrairie, "EndMatch" );
	if( !joueur -> DoubleStack ) erreurChargementFonction( nomLibrairie, "DoubleStack" );
	if( !joueur -> TakeDouble ) erreurChargementFonction( nomLibrairie, "TakeDouble" );

	return *joueur;
}


/*
* Convertie une chaine de caractere en nombre entier positif,
* et place la valeur de ce nombre à l'adresse pointé par le pointeur *nombre
*
* @param const char* string
*	la chaine a convertir en nombre entier positif
*
* @param int* nombre
*	pointeur d'entier vers l'adresse mémoire ou sera stocké le nombre correspondant en mémoire
*
* @return int
*	retourne 0 si la conversion s'est bien passé, -1 sinon.
*/
int stringToPositiveInteger( const char* string, int* nombre ) {

	*nombre = 0;

	int i;
	char c;
	for( i = 0; i < strlen(string); i++ ) {
		c = string[i];

		if( c >= '0' && c <= '9' ) {
			*nombre = *nombre * 10 + (c - '0');
		}
		else return -1;
	}
	return 0;
}



/*
* Retourne un nombre généré aléatoirement entre min et max compris.
*
* @pre
*	initialiser le générateur de nombre aléatoire avec srand(time(NULL)
*
*/
int randomINT( int min, int max ) {
	return ( rand() % max ) + min;
}


void lancerLesDes( unsigned char dices[2] ) {
	dices[0] = (unsigned char) randomINT(1,6);
	dices[1] = (unsigned char) randomINT(1,6);
}

void afficherDes( unsigned char dices[2] ) {
	printf( " des : %i %i \n", dices[0], dices[1] );
}



int main( int argc, char* argv[] ) {

	/*
	*	vérification des paramètres entrés par l'utilisateur
	*/

	if( argc <= 1 ) {
		printf(" Erreur, il manque les parametres : \n");
		printf(" 	%s <nbParties> <cheminStategie1> <cheminStrategie2>", argv[0] );
		exit(-1);
	}

	char* cheminLibrairie_1;
	char* cheminLibrairie_2;

	// récupération de la premiere librairie
	if( argc >= 3 ) cheminLibrairie_1 = argv[2];
	else cheminLibrairie_1 = "libBot.so";					// chargement par défaut

	// recuperation de la deuxieme librairie
	if( argc >= 4 ) cheminLibrairie_2 = argv[3];
	else cheminLibrairie_2 = "libBot.so";

	// récupération du nombre de parties à jouer
	int nbParties;
	if( stringToPositiveInteger(argv[1],&nbParties) ) {
		printf(" Erreur, le parametre representant le nombre de parties n'est pas valide. \n");
		printf(" Ce parametre doit etre un entier positif");
		exit(-1);
	}


	// chargement des joueurs
	Joueur joueur1 = chargerJoueur( cheminLibrairie_1 );
	Joueur joueur2 = chargerJoueur( cheminLibrairie_2 );


	/*
	*	déroulement d'une partie....
	*
	*/

	srand( time(NULL) ); 		// initialise générateur aléatoire

	unsigned int nbMoves;
	unsigned char dices[2];

	char nomBot1[50];
	char nomBot2[50];
	joueur1.InitLibrary(nomBot1);
	joueur2.InitLibrary(nomBot2);


	// ...........................................................................

    afficherPlateau(); // affichage de la fenêtre de jeu et de la partie grapique

	lancerLesDes( dices );
	afficherDes( dices );


	// ??? score cible pour gagner un match ???
	joueur1.StartMatch(-1);
	joueur2.StartMatch(-1);



	joueur1.StartGame( BLACK );
	joueur2.StartGame( WHITE );


	joueur1.EndGame();
	joueur2.EndGame();


	joueur1.EndMatch();
	joueur2.EndMatch();


	/*
	*	libération des ressources utilisées
	*/
	fermerLibrairie( joueur1.librairie );
	fermerLibrairie( joueur2.librairie );

	free( &joueur1 );
	free( &joueur2 );

	return 0;
}

