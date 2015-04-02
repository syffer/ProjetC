#ifndef _fonctionsBot
    #define _fonctionsBot


#include "backgammon.h"
#include "ListeChainee.h"


// signature des fonctions communes
struct Bot {
    
    char nom[50];
    Player maCouleur;
    unsigned int scoreCible;    // ??
    
    SGameState gameState;       // ??
    
};
typedef struct Bot Bot;




// combinaison de mouvements
struct Coup {
    
    SMove mouvements[4];
    int nbMouvements;

};
typedef struct Coup Coup;



ListeChainee* getDices( const unsigned char dices[2] );

SMove creerMouvement( int depart, int arrivee );

Square getCaseActuelle( SGameState gameState, Player maCouleur, int i );
int peutDeplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases ) ;
SMove deplacerUnPion( SGameState* gameState, Player maCouleur, int depart, int nbCases );       // a modifier peut être
int possedeDesPionsSurLaBarre( SGameState* gameState, Player maCouleur );

void calculerMouvements( SGameState gameState, Player maCouleur, ListeChainee* dices, SMove mouvements[4], int* nbMouvements );
    
#endif