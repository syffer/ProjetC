#ifndef _jeux
	#define _jeux




typedef struct Joueur Joueur;



Joueur* chargerJoueur( char nomLibrairie[] );
int dlerrorDetectee();
void jouerPartie( int nbParties, Joueur* joueur1, Joueur* joueur2 );
void libererJoueur( Joueur* joueur );


void afficherDes( unsigned char dices[2] );
void lancerLesDes( unsigned char dices[2] );
int randomINT( int min, int max );

int stringToPositiveInteger( const char* string, int* nombre );
int copierFichier( char* source, char* destination );




#endif