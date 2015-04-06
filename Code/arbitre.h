#ifndef _arbitre
    #define _arbitre


#include "backgammon.h"


typedef struct Joueur Joueur;



void afficherDes( unsigned char dices[2] );
void lancerLesDes( unsigned char dices[2] );

int randomINT( int min, int max );





SGameState initialiserEtatJeux();
void initialiserPlateau( Square board[24] );
int remplirCase( Square board[], int laCase, int couleurJoueur, int nbDames );




#endif
