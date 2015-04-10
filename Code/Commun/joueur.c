/*
	Fichier contenant toutes les fonctions concernant le chargement des libraires.
	Les fonctions d'une librairie chargée seront stockées dans une structure Joueur, 
	celle-ci ne contient que des pionteurs de fonctions.
	
	Auteurs :
	- Pauline HOULGATTE
	- Maxime PINEAU	

*/

#include "joueur.h"
#include "backgammon.h"
#include "libJoueur.h"

#include <stdlib.h> 	// malloc()
#include <stdio.h>
#include <assert.h>		// assert()




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
Joueur chargerJoueur( char nomLibrairie[] ) {
	
	//printf(" --> %s \n", nomLibrairie );

	// on charge la librairie
	Librairie lib = chargerLibrairie( nomLibrairie );
	if( !lib ) {	// lib == NULL
		printf( " Erreur, impossible de charger la librairie : %s \n", nomLibrairie );
		printf( " %s \n", getError() );
		exit( EXIT_FAILURE );
	}
	getError();    /* Clear any existing error */


	int nbErreursDetectees = 0;

	Joueur joueur;

	joueur.estUnBot = 1;

	joueur.librairie = lib;

	joueur.InitLibrary = (pfInitLibrary) extraireLibrairie( lib, "InitLibrary" );	// on extrait la fonction
	nbErreursDetectees += dlerrorDetectee();

	joueur.StartMatch = (pfStartMatch) extraireLibrairie( lib, "StartMatch" );
	nbErreursDetectees += dlerrorDetectee();

	joueur.StartGame = (pfStartGame) extraireLibrairie( lib, "StartGame" );
	nbErreursDetectees += dlerrorDetectee();

	joueur.EndGame = (pfEndGame) extraireLibrairie( lib, "EndGame" );
	nbErreursDetectees += dlerrorDetectee();

	joueur.EndMatch = (pfEndMatch) extraireLibrairie( lib, "EndMatch" );
	nbErreursDetectees += dlerrorDetectee();

	joueur.DoubleStack = (pfDoubleStack) extraireLibrairie( lib, "DoubleStack" );
	nbErreursDetectees += dlerrorDetectee();

	joueur.TakeDouble = (pfTakeDouble) extraireLibrairie( lib, "TakeDouble" );
	nbErreursDetectees += dlerrorDetectee();

	joueur.PlayTurn = (pfPlayTurn) extraireLibrairie( lib, "PlayTurn" );
	nbErreursDetectees += dlerrorDetectee();


	// si il y a eu une erreur, on sort du programme OBLIGATOIREMENT
	if( nbErreursDetectees ) {
		fermerLibrairie( lib );
		//free(joueur);
		exit( EXIT_FAILURE );
	}

	return joueur;
}


Joueur chargerJoueurReel() {
	Joueur joueur;

	joueur.estUnBot = 0;
	joueur.librairie = NULL;

	joueur.InitLibrary = InitLibrary;
	joueur.StartMatch = StartMatch;
	joueur.StartGame = StartGame;
	joueur.EndGame = EndGame;
	joueur.EndMatch = EndMatch;
	joueur.DoubleStack = DoubleStack;
	joueur.TakeDouble = TakeDouble;
	joueur.PlayTurn = PlayTurn;

	return joueur;
}


#ifdef _WIN32
	// la fonction dlerror() n'a pas d'équivalent sur windows, il faut la fabriquer manuellement
    char* getError() {

		DWORD errorMessageID = GetLastError();

		if( errorMessageID == 0 ) return NULL;

		LPSTR messageBuffer = NULL;

		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		return messageBuffer;
	}
#endif


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



void libererJoueur( Joueur joueur ) {
	fermerLibrairie( joueur.librairie );
	//free( joueur );
}





