#ifndef _arbitre
    #define _arbitre
    #include "backgammon.h"
    #include "joueur.h"
    #include "graphique.h"

typedef struct Joueur Joueur;

void afficherDes( unsigned char dices[2] );
void lancerLesDes( unsigned char dices[2] );

int randomINT( int min, int max );

const SGameState const copierEtatJeux( SGameState etatJeux );
void jouerPartie( int nbParties, Joueur joueur1, Joueur joueur2 );
int finPartie(SGameState etatJeux, int triesw, int triesb); //indique si c'est fini ou pas
int verifierCoup(SGameState etatJeux ,unsigned char dices[2], SMove moves[4], int nbMoves, SMove bonsCoups[4]);
//void modifierMap(SGameState etatJeux, SMove moves[4], int nbMoves, int couleur);
//void allerVersAdverse(SGameState etatJeux, SMove move, int couleur_src);

//choper la destination, en gros tester si c'est pas la fin
//void choperDestination(SGameState etatJeux,SMove move,int couleur_src);

///fonctions pour vérifier nombre de coups
int calculerMaxCoup(SGameState etatJeux ,unsigned char dices[2], int couleur);

//transforme les dés en coups
void transformerDesEnCoups(unsigned char dices[2], unsigned int coups[4], int* nbCoups);
//--> copier la SGameState

//jouer les coups obligatoires dus au bar --> retourne le nombre de coups joués
int jouerBar(SGameState etatJeux, int coups[4],int* nbCoups, int couleur);
//algo pour des dés pareils : nbCoups est le nombre de coups qu'il reste à jouer
int algoCoupPareil(SGameState etatJeux, unsigned int coup, int nbCoups, int couleur);
//algo pour deux dés différents
int algoCoupDifferent(SGameState etatJeux, int coup[2], int couleur);

//vérifier si un coup est possible
int coupPossible(Square board[], SMove move, int couleur);
//faire le coup
void jouerCoup(SGameState etatJeux, SMove move, int couleur);

//construire un move
SMove faireMove(int src, int numDe, int couleur);


#endif
