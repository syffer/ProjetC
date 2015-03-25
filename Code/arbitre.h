#ifndef _arbitre
    #define _arbitre
    
typedef struct Joueur Joueur;

void afficherDes( unsigned char dices[2] );
void lancerLesDes( unsigned char dices[2] );

int randomINT( int min, int max );


void jouerPartie( int nbParties, Joueur* joueur1, Joueur* joueur2 );


#endif