
// windows de merde qui n'est pas foutu d'avoir <dlfcn.h>
#ifdef _WIN32
	#include <windows.h>
	
	#define Librairie HMODULE
	#define chargerLibrairie(nomLib) LoadLibrary(nomLib)
	#define TypeFonction FARPROC
	#define extraireLibrairie(libType, nomFonction) GetProcAddress(libType, nomFonction)
	#define fermerLibrairie(libType) FreeLibrary(libType)
	//#define getError() GetLastError()

	char* getError() {
		DWORD errorMessageID = GetLastError();

		if( errorMessageID == 0 ) return NULL;

		LPSTR messageBuffer = NULL;

		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		return messageBuffer;
	}
	
#endif



#ifdef linux
	#include <dlfcn.h>

	#define Librairie void*
	#define chargerLibrairie(nomLib) dlopen( nomLib, RTLD_LOCAL || RTLD_LAZY ) 		// http://stackoverflow.com/questions/3433522/loading-two-instances-of-a-shared-library
	#define TypeFonction void
	#define extraireLibrairie(libType, nomFonction) dlsym(libType, nomFonction)
	#define fermerLibrairie(libType) dlclose(libType)
	#define getError() dlerror()
#endif



#include "jeux.h"
#include "backgammon.h"



#include <time.h>		// time pour aléatoire
#include <assert.h>		// assert pour vérifier si une allocation mémoire a bien été faite
#include <stdlib.h>		// malloc
#include <stdio.h>
#include <string.h>



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






void jouerPartie( int nbParties, Joueur* joueur1, Joueur* joueur2 ) {



	//unsigned int nbMoves;
	unsigned char dices[2];

	char nomBot1[50];
	char nomBot2[50];
	joueur1 -> InitLibrary(nomBot1);
	joueur2 -> InitLibrary(nomBot2);

	printf(" %p \n %p \n ", joueur1 -> StartMatch, joueur2 -> StartMatch );
	
	// ........................................................................... 
	

	lancerLesDes( dices );
	afficherDes( dices );


	// ??? score cible pour gagner un match ???
	joueur1 -> StartMatch(-1);
	joueur2 -> StartMatch(-1);



	joueur1 -> StartGame( WHITE );
	joueur2 -> StartGame( BLACK );


	joueur1 -> EndGame();
	joueur2 -> EndGame();


	joueur1 -> EndMatch();
	joueur2 -> EndMatch();

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
Joueur* chargerJoueur( char nomLibrairie[] ) {
	
	// on charge la librairie
	Librairie lib = chargerLibrairie( nomLibrairie );
	if( !lib ) {	// lib == NULL
		printf( " Erreur, impossible de charger la librairie : %s \n", nomLibrairie );
		printf( " %s \n", getError() );
		exit( EXIT_FAILURE );
	}
	getError();    /* Clear any existing error */


	int nbErreursDetectees = 0;

	Joueur* joueur = (Joueur*) malloc( sizeof(Joueur) );
	assert(joueur);		// on vérifie que l'on a bien réussi à faire le malloc

	joueur -> librairie = lib;

	joueur -> InitLibrary = (pfInitLibrary) extraireLibrairie( lib, "InitLibrary" );	// on extrait la fonction
	nbErreursDetectees += dlerrorDetectee();

	joueur -> StartMatch = (pfStartMatch) extraireLibrairie( lib, "StartMatch" );
	nbErreursDetectees += dlerrorDetectee();

	joueur -> StartGame = (pfStartGame) extraireLibrairie( lib, "StartGame" );
	nbErreursDetectees += dlerrorDetectee();

	joueur -> EndGame = (pfEndGame) extraireLibrairie( lib, "EndGame" );
	nbErreursDetectees += dlerrorDetectee();

	joueur -> EndMatch = (pfEndMatch) extraireLibrairie( lib, "EndMatch" );
	nbErreursDetectees += dlerrorDetectee();

	joueur -> DoubleStack = (pfDoubleStack) extraireLibrairie( lib, "DoubleStack" );
	nbErreursDetectees += dlerrorDetectee();

	joueur -> TakeDouble = (pfTakeDouble) extraireLibrairie( lib, "TakeDouble" );
	nbErreursDetectees += dlerrorDetectee();


	// si il y a eu une erreur, on sort du programme OBLIGATOIREMENT
	if( nbErreursDetectees ) {
		fermerLibrairie( lib );
		free(joueur);
		exit( EXIT_FAILURE );
	}

	return joueur;
}



/*
* Si une erreur est renvoyée par dlerror(), alors on affiche cette erreur et l'on renvoie 1, 
* sinon on renvoie 0.
*
*/
int dlerrorDetectee() {
	char* erreur = getError();
	if( erreur ) {
		printf( " %s \n", erreur );
		return 1;
	}
	else return 0;
}



void libererJoueur( Joueur* joueur ) {
	fermerLibrairie( joueur -> librairie );
	free( joueur );
}





/*
* Affiche le contenu du tableau contenant la valeurs des dés.
*
*/
void afficherDes( unsigned char dices[2] ) {
	printf( " des : %i %i \n", dices[0], dices[1] );
}


/*
* Lance les dés
*
*/
void lancerLesDes( unsigned char dices[2] ) {
	dices[0] = (unsigned char) randomINT(1,6);
	dices[1] = (unsigned char) randomINT(1,6);
}



/*
* Retourne un nombre généré aléatoirement entre min et max compris.
*
*/
int randomINT( int min, int max ) {
	
	// on vérifie si le générateur aléatoire a été initialisé
	static int generateurInitialise = 0;
    if( ! generateurInitialise ) {		// si ce n'est pas le cas, on l'initialise
        generateurInitialise = 1;
        srand( time(NULL) );
    }
    
	return ( rand() % (max-min+1) ) + min;
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
* Copie le contenu d'un fichier source vers un fichier destination (ecrase le contenu existant)
*/
int copierFichier( char* source, char* destination ) {

	// ouverture du fichier à copier
	FILE* p_fichierAcopier = fopen( source, "r" );
	if( ! p_fichierAcopier ) {
		return -1;
	}

	// ouverture du fichier de destination
	FILE* p_nouveauFichier = fopen( destination, "w" );
	if( ! p_nouveauFichier ) {
		fclose( p_fichierAcopier );
		return -1;
	}

	// on copie le contenu
	int c;
	while( (c=fgetc(p_fichierAcopier) ) != EOF && !feof(p_nouveauFichier) ) fputc( c, p_nouveauFichier );

	// on ferme les fichiers utilisés
	fclose( p_fichierAcopier );
	fclose( p_nouveauFichier );

	return 0;
}




