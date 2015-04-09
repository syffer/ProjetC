
#include "graphique.h"

#include "../Commun/backgammon.h"
//#include "arbitre.h"
#include <stdio.h>


// pour libJoueur.h
// retourne la position de la case graphique sélectionnée par l'utilisateur (avec la souris)
int selectionnerCaseGraphique() {
    return -1;
}

void ouvrirFenetreDoublerMiseGraphique() {

}

void ouvrirFenetreAccepterDoublerMise() {

}

// retourne 1 si le joueur a cliqué sur "OUI", 0 sinon
int getChoixUtilisateurGraphique() {
    return 0;
}



int initialiserFenetre(){
    return 1;
}
void fermerFenetre(){

}
void initialiserPlateauGraphique( SGameState* gameState ){
}
void updateDesGraphique( unsigned char dices[2] ){
}
void deplacerPionGraphique( SMove mouvement ){
}
void updateTourJoueurGraphique( Player joueur ){
}
void updateScoreJoueurBlanc(int score){
}
void updateScoreJoueurNoir(int score){
}
void updateScoreCibleGraphique( int scoreCible ){
}
void updateMiseCouranteGraphique( int nouvelleMise ){
}
