/*
	Fichier contenant toutes les fonctions concernant la vérification des librairies.
	On regarde si les librairies ont le même nom, et si c'est le cas (le même fichier), 
	on crée une copie de la librairie ( extention .copy )



*/
#ifndef _verifications
	#define _verifications



int stringToPositiveInteger( const char* string, int* nombre );
int copierFichier( char* source, char* destination );

void ajouterRepertoireCourant( char* chemin, char nouveauChemin[] );
int verifierLibrairies( char* cheminLibrairie_1, char* cheminLibrairie_2, char* librairie_1, char* librairie_2, int* copieEffectuee ) ;

#endif