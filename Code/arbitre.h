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
int finPartie(SGameState etatJeux, int tries1, int tries2); //indique si c'est fini ou pas
int verifierCoup(SGameState etatJeux ,unsigned char dices[2], SMove moves[4], int nbMoves);
void modifierMap(SGameState etatJeux, SMove moves[4], int nbMoves, int couleur);
void allerVersAdverse(SGameState etatJeux, SMove move, int couleur_src);
//choper la destination, en gros tester si c'est pas la fin
void choperDestination(SGameState etatJeux,SMove move,int couleur_src);

///fonctions pour vérifier nombre de coups
//transforme les dés en coups
transformerDesEnCoups(unsigned char dices[2], unsigned int coups[4], int nbCoups);
//--> copier la SGameState

//jouer les coups obligatoires dus au bar
jouerBar(SGameState etatJeux, coups[4],int nbCoups);
//algo pour des dés pareils : nbCoups est le nombre de coups qu'il reste à jouer
algoCoupPareil(SGameState etatJeux, int coup, int nbCoups);


#endif
