#ifndef _graphique
	#define _graphique


int afficherPlateau();
char* retournerPathDe(char dice);
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2);
int randomINT( int min, int max );
void lancerLesDes( unsigned char dices[2] );

#endif
