
#include "arbitre.h"

#include "backgammon.h"
#include "joueur.h"
#include "graphique.h"
#include <time.h>		// time
#include <stdlib.h> 	// srand
#include <stdio.h>		// printf()
#define ICI printf("ICIIIIII\n");
#include <unistd.h>

/*
* Affiche le contenu du tableau contenant la valeurs des dés.
*
*/
void afficherDes( unsigned char dices[2] ) {
	printf( " des : %i %i \n", dices[0], dices[1] );
}


/*
* Lance les dés
*
*/
void lancerLesDes( unsigned char dices[2] ) {
	dices[0] = (unsigned char) randomINT(1,6);
	dices[1] = (unsigned char) randomINT(1,6);
	actualiserDes(dices);
}



/*
* Retourne un nombre généré aléatoirement entre min et max compris.
*
*/
int randomINT( int min, int max ) {

	// on vérifie si le générateur aléatoire a été initialisé
	static int generateurInitialise = 0;
    if( ! generateurInitialise ) {		// si ce n'est pas le cas, on l'initialise
        generateurInitialise = 1;
        srand( time(NULL) );
    }

	return ( rand() % (max-min+1) ) + min;
}



/**
* board : tableau des cases
* numeroCase : la case à mettre
* couleurJoueur : la couleur du joueur qui la possède
* nbDames : le nombre de jetons à poser
*/
int remplirCase( Square* laCase, Player couleurJoueur, int nbDames ) {
	if( !laCase ){
    perror("laCase pointe vers rien du tout !");
	return -1;
	}

	laCase->owner = couleurJoueur;
	laCase->nbDames = nbDames;
	if(nbDames != 0){
	remplirCaseX(laCase, couleurJoueur, nbDames);//mettre le nombre de pions qu'il faut dans chaque case !
	}


	return 0;
}



SGameState initialiserEtatJeux() {

	SGameState etatJeux;

	// pions sur la barre centrales (ceux pas encore en jeu)
	etatJeux.bar[ BLACK ] = 0;
	etatJeux.bar[ WHITE ] = 0;

	// pions déjà sortis
	etatJeux.out[ BLACK ] = 0;
	etatJeux.out[ WHITE ] = 0;

	// score des joueurs
	etatJeux.whiteScore = 0;
	etatJeux.blackScore = 0;

	etatJeux.turn = WHITE;

	//mise courante (du videau)
	etatJeux.stake = 1;

	// on initialise tout le plateau à "rien/personne/NOBODY"
	int i;
	for( i = 0; i < 24; i++ ) {
		remplirCase( &etatJeux.board[i], NOBODY, 0 );
	}

	return etatJeux;
}



void initialiserPlateau( Square board[24] ) {
	remplirCase( &board[0], WHITE, 2 );
	remplirCase( &board[5], BLACK, 5 );
	remplirCase( &board[7], BLACK, 3 );
	remplirCase( &board[11], WHITE, 5 );
	remplirCase( &board[12], BLACK, 5 );
	remplirCase( &board[16], WHITE, 3 );
	remplirCase( &board[18], WHITE, 5 );
	remplirCase( &board[23], BLACK, 2 );
}


const SGameState const copierEtatJeux( SGameState etatJeux ) {
	return etatJeux;
}



void jouerPartie( int nbParties, Joueur joueur1, Joueur joueur2 ) {

	char nomBot1[50];
	char nomBot2[50];
	joueur1.InitLibrary(nomBot1);
	joueur2.InitLibrary(nomBot2);

	Joueur jW, jB; //joueur blanc et joueur noir


	// variables de jeux
	unsigned int nbMoves;
	SMove moves[4];
	unsigned char dices[2];
	unsigned int triesb = 2, triesw = 2;
	unsigned int couleur[2]; //les couleurs du j1 puis du j2

	SGameState etatCopie, etatJeux = initialiserEtatJeux(); 	// /!\ a initialiser (tableau de cases, nb points ....)

	int score = 5, etatValide; 	// quel est le score à atteindre ??????


	joueur1.StartMatch(score);
	joueur2.StartMatch(score);

	int i;
	for( i = 0; i < nbParties; i++ ) {

		printf("-> partie %i \n", i+1 );
		//SDL --> afficher début partie i

		initialiserPlateau( etatJeux.board );
		//SDL --> Mettre les jetons sur le plateau

		// on lance les dés jusqu'a ce que l'on obtienne deux nombre différents
		do
		{
			lancerLesDes(dices);
		} while( dices[0] == dices[1] );


		// convention pour le début : le joueur 1 a jeté le dés à l'indice 0
		if( dices[0] > dices[1] ) {
			joueur1.StartGame( WHITE );
            couleur[0]=WHITE;
            jW = joueur1;
			joueur2.StartGame( BLACK );
			couleur[1]=BLACK;
			jB = joueur2;

		}
		else {
			joueur1.StartGame( BLACK );
			joueur2.StartGame( WHITE );
			couleur[1]=WHITE;
			couleur[0]=BLACK;
			jW = joueur2;
			jB = joueur1;

		}
        int premierTour = 1;

		while( !finPartie(etatJeux,triesw,triesb) ) {  	// tant que la partie n'est pas terminée

			/*
				!!!! attention, pour le premier tour, le joueur blanc doit utiliser les premiers dés tirés
				(ceux utilisé pour déterminé qui est noir et qui est blanc)

			*/
			if(!premierTour){
                lancerLesDes(dices);
			}
			premierTour = 0;

            ///// HISTOIRE DES MISES --> on passe pour l'instant
			// si le joueur a le videau, alors le proposer à l'autre de le prendre
			// puis demander au 1er joueur si il accept ou non la nouvelle mise
			//

			/*

			if (j1DoubleStack(&gameState))
				j2TakeDouble(&gameState);
			*/
            //////////

            etatValide = 0;
            etatCopie = copierEtatJeux(etatJeux);
            //Penser à COPIER LES DES !!!!!!!!!!!!!!!!!!!!!!!!!!

            if(!etatValide){
                //On lui donne ici normalement l'état copié
                if(etatJeux.turn == WHITE) jW.PlayTurn( &etatCopie, dices, moves, &nbMoves, triesw );
                else jB.PlayTurn( &etatCopie, dices, moves, &nbMoves, triesb );
                //on vérifie que ce que veut faire le joueur est correct
                if(!verifierCoup(etatJeux,dices,moves,nbMoves)){
                    //coup foireux !
                    if(etatJeux.turn == WHITE){
                         triesw--;
                         if(triesw==0) etatValide = 1;
                    }
                    else{
                         triesb--;
                         if(triesb==0) etatValide = 1;
                    }
                }else{
                    //coup valide, on modifie la gameState (qui va appeler les fonctions graphiques) et on passe le tour
                    modifierMap(etatJeux,moves,nbMoves,etatJeux.turn);
                    etatValide = 1;
                }
            }//fin tour

			etatJeux.turn = !etatJeux.turn; //on change le tour



		}//fin de la manche



		joueur1.EndGame();
		joueur2.EndGame();
		printf("-> fin de la partie %i \n", i+1 );
	}//fin du match

	joueur1.EndMatch();
	joueur2.EndMatch();
	printf("fin du match\n");




	// model :
	// j1StartMatch(5);
	// 	//*****// à faire pour chaque jeu
	// 	j1StartGame(BLACK);
	// 		//*****// pour chaque joueur, tant que ce n'est pas fini
	// 		if (j1DoubleStack(&gameState))
	// 			j2TakeDouble(&gameState);
	// 		j1PlayTurn(&gameState,dices,moves,&nbMoves,3);
	// 	j1EndGame();

	// j1EndMatch();

}

int finPartie(SGameState etatJeux, int triesw, int triesb){
    //perte due aux fautes de jeu
    if(!triesw){
        printf("joueur blanc perd par faute de jeu !");
        return 1;
    }
    if(!triesb){
        printf("joueur noir perd par faute de jeu !");
        return 1;
    }
    if(etatJeux.out[0] == 15){
        printf("joueur blanc à gagné !");
        return 1;
    }
    if(etatJeux.out[1] == 15){
        printf("joueur noir à gagné !");
        return 1;
    }
    return 0;
}

int verifierCoup(SGameState etatJeux ,unsigned char dices[2], SMove moves[4], int nbMoves){
    return 1;
}

void modifierMap(SGameState etatJeux, SMove moves[4], int nbMoves, int couleur){
    int testMoves; //doit changer à chaque fois, sinon il y a une erreur
    int i;
    SMove move;
    while(nbMoves != 0){
        testMoves = nbMoves;
        for(i=0;i<nbMoves;i++){
            move = moves[i];
            if(move.src_point == 0){//bar
                if(etatJeux.board[move.dest_point-1].owner == -couleur){//si la destination est une case adverse
                    allerVersAdverse(etatJeux,move,couleur);
                }
                etatJeux.bar[couleur]--;
                //la destination devient notre
                choperDestination(etatJeux,move,couleur);
                //afficher graphiquement
                afficherDeplacementX(move);
                nbMoves--; //un mouvement à été effectué
            }
            //si on est pas dans le bar
            else{
                //si la source est la fin, ya un sérieux problème
                if(move.src_point >= 25){
                    perror("GROS PROBLEME ! la source est la fin >_<'");
                    exit(1);
                }
                //si la source n'est pas une de nos cases, c'est qu'on peut pas encore jouer ce coup
                //sinon on fait le coup
                if(etatJeux.board[move.src_point-1].owner == couleur){
                    if(etatJeux.board[move.dest_point-1].owner == -couleur){//si la destination est une case adverse
                        allerVersAdverse(etatJeux,move,couleur);
                    }
                    //on perd une dame à la source
                    etatJeux.board[move.src_point-1].nbDames--;
                    //si ya plus de dames sur la source, elle devient NOBODY
                    if(!etatJeux.board[move.src_point-1].nbDames){
                        etatJeux.board[move.src_point-1].owner = NOBODY;
                    }
                    //la destination devient notre
                    choperDestination(etatJeux,move,couleur);
                    //afficher graphiquement
                    afficherDeplacementX(move);
                    nbMoves--; //un mouvement à été effectué
                }
            }

        }
        if(testMoves == nbMoves){
            perror("aucun déplacement n'a pu être effectué !");
            exit(1);
        }
    }
}

//Utilisée si on fait un déplacement vers une case adverse
void allerVersAdverse(SGameState etatJeux, SMove move, int couleur_src){
    //la case doit contenir 1 jeton, sinon error
    if(etatJeux.board[move.dest_point].nbDames != 1){
        perror("nombre de pions adverses différent de 1, il aurait pas du pouvoir prendre cette case");
        exit(1);
    }
    //on mange le pion adverse --> on le met dans bar
    etatJeux.board[move.dest_point-1].nbDames = 0;
    etatJeux.bar[!couleur_src]++;
    SMove virerAdversaire = {move.dest_point,25*couleur_src}; //le bar de blanc est 0, le bar de noir est 25...
    afficherDeplacementX(virerAdversaire);

    etatJeux.board[move.dest_point-1].owner == couleur_src;
    //il reste plus qu'à déplacer le pion sur la case adverse
}

//choper la destination, en gros tester si c'est pas la fin
void choperDestination(SGameState etatJeux,SMove move,int couleur_src){
    //vérifier si c'est la fin ou pas
    if(move.dest_point==25){
        etatJeux.out[couleur_src]++;
    }else{
        //on augmente le nbDame et on s'assure que la case est bien à nous
        etatJeux.board[move.dest_point-1].nbDames++;
        etatJeux.board[move.dest_point-1].owner = couleur_src;
    }
}

//calculer le maximum de coups possibles par un joueur
int calculerMaxCoup(SGameState etatJeux ,unsigned char dices[2], SMove moves[4], int nbMoves){

}

