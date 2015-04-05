
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
	SGameState copie;
	copie.bar[0] = etatJeux.bar[0];
	copie.bar[1] = etatJeux.bar[1];
	copie.out[0] = etatJeux.out[0];
	copie.out[1] = etatJeux.out[1];
	//copie de la board
	int i;
	for(i=0;i<25;i++){
        copie.board[i].nbDames = etatJeux.board[i].nbDames;
        copie.board[i].owner = etatJeux.board[i].owner;
	}
	copie.turn = etatJeux.turn;
	//pour l'instant on copie que ça
	return copie;
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
	SMove bonsCoups[4];
	SMove move; //move utilisé une fois...

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
                if(!verifierCoup(etatJeux,dices,moves,nbMoves,bonsCoups)){
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
                    //coup valide, on modifie la gameState, on appele les fonctions graphiques et on passe le tour
                    for(i=0;i<nbMoves;i++){
                        if(etatJeux.board[bonsCoups[i].dest_point-1].owner == -etatJeux.turn){ //on vérifie ici pour afficher le déplacement d'un jeton mangé
                            move.src_point = bonsCoups[i].dest_point;
                            move.dest_point = 0;
                            afficherDeplacementX(move);
                        }
                        jouerCoup(etatJeux,bonsCoups[i],etatJeux.turn);
                        afficherDeplacementX(bonsCoups[i]);
                    }
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

//la couleur est dans etatJeux.turn
int verifierCoup(SGameState etatJeux ,unsigned char dices[2], SMove moves[4], int nbMoves, SMove bonsCoups[4]){
    int x=calculerMaxCoup(etatJeux,dices, etatJeux.turn);
    if(x != nbMoves){
        printf("Le joueur n'a pas maximisé le nombre de coups");
        printf("Coups du joueur : %d",nbMoves);
        printf("Coups possibles : %d",x);
        return 0;
    }
    SGameState copie = copierEtatJeux(etatJeux);
    int modificationEffectuee, i, nbCoupsRestants = nbMoves;
    int movesEffectues[4] = {0,0,0,0};

    while(nbCoupsRestants != 0){
        modificationEffectuee = 0;
        for(i=0;i<nbMoves;i++){
            //si le move n'a pas déjà été fait
            if(movesEffectues[i] = 0){
                //on regarde si on peut jouer le coup
                if(coupPossible(etatJeux.board,moves[i],etatJeux.turn)){
                    //on le joue, on le définit comme joué, on réduit le nombre de coups restants
                    jouerCoup(etatJeux,moves[i],etatJeux.turn);
                    movesEffectues[i] = 1;

                    //on ajoute le coups aux bons coups, ce qui permet de gagner du temps après lorsqu'on les fera un par un dans l'ordre
                    bonsCoups[nbMoves-nbCoupsRestants] = moves[i];

                    nbCoupsRestants--;
                    //on a fait une modif
                    modificationEffectuee = 1;
                }
            }
        }
        if(modificationEffectuee == 0) return 0;
    }
    return 1;
}


//calculer le maximum de coups possibles par un joueur
int calculerMaxCoup(SGameState etatJeux, unsigned char dices[2], int couleur){
    //combien on peut faire de coups avec les dés qu'on à
    unsigned int coups[4];
    int nbCoups = 0, coupsJoues = 0;
    transformerDesEnCoups(dices, coups, &nbCoups);


    //copie de gameState
    SGameState copieGame = copierEtatJeux(etatJeux);

    //on enlève les coups obligatoires dus au bar
    coupsJoues = jouerBar(copieGame, coups, &nbCoups, couleur);

    if(nbCoups == 0){
        return coupsJoues;
    }else if(nbCoups == 1){
        return coupsJoues + algoCoupPareil(copieGame,coups[0],1,couleur);
    }else{
        //il y a au moins deux coups.
        //si les dés sont les même, on prend le premier algo, sinon le deuxième
        if(coups[0] == coups[1]){
            return coupsJoues + algoCoupPareil(copieGame,*coups,nbCoups, couleur);
        }else{
            if(nbCoups != 2){
                perror("PAS NORMAL : erreur pas possible à ce stade, on ne doit pas pouvoir faire l'algo de dés différents si il y en a plus de 2");
                exit(1);
            }
            return coupsJoues + algoCoupDifferent(copieGame,coups, couleur);
        }
    }
}

///fonctions pour vérifier nombre de coups
void transformerDesEnCoups(unsigned char dices[2], unsigned int coups[4], int* nbCoups){
    if(dices[0] == dices[1]){
        unsigned int num = (unsigned int) dices[0];
        coups[0] = num;
        coups[1] = num;
        coups[2] = num;
        coups[3] = num;
        *nbCoups = 4;
    }else{
        unsigned int num1, num2;
        num1 = (unsigned int) dices[0];
        num2 = (unsigned int) dices[1];
        coups[0] = num1;
        coups[1] = num2;
        *nbCoups = 2;
    }
}

//retourne le nombre de coups joués
int jouerBar(SGameState etatJeux, int coups[4],int* nbCoups, int couleur){
    if(etatJeux.bar[couleur] == 0){
        return 0;
    }
    //cas particulier à traiter : un jeton en bar, et 2 dés différents --> il peut perdre un coup si il joue mal
    //on traite donc le cas ici, fais chier...
    if(*nbCoups > 1 && etatJeux.bar[couleur] == 1 && coups[0] != coups[1]){
        //si on peut pas faire le coup avec le premier dé
        if(!coupPossible(etatJeux.board,faireMove(0,coups[0],couleur),couleur)){
            *nbCoups--;
            return jouerBar(etatJeux,&coups[1],nbCoups,couleur); //on réapplique l'algo avec un dé
        }else if(!coupPossible(etatJeux.board,faireMove(0,coups[1],couleur),couleur)){
            *nbCoups--;
            return jouerBar(etatJeux,&coups[0],nbCoups,couleur); //on réapplique l'algo avec l'autre dé
        }else{
            //les deux dés peuvent être joués, fais chier...
            //on teste avec le premier dé
            int dest;
            if(couleur = WHITE) dest = coups[0];
            else dest = 25-coups[0];

            etatJeux.board[dest-1].nbDames++;
            etatJeux.board[dest-1].owner = couleur;
            etatJeux.bar[couleur]  = 0;
            //on applique l'algo à dés unique sur cette map
            if(algoCoupPareil(etatJeux,coups[1],1,couleur) == 1) return 2;
            else{
                //le test avec le premier dé n'a pasfonctionné, on annule et on teste avec le deuxième
                etatJeux.board[dest-1].nbDames--;
                if(etatJeux.board[dest-1].nbDames == 0) etatJeux.board[dest-1].owner = NOBODY;
                jouerCoup(etatJeux,faireMove(0,coups[1],couleur),couleur);
                return 1+algoCoupPareil(etatJeux,coups[0],1,couleur);
            }
        }
    }
    //la on est dans un cas normal, c'est bon, ouf !
    int coupsJoues = 0;
    int coupATester = *nbCoups-1;
    SMove move;
    int coupsRestants[4] = {0,0,0,0}, courant = 0; //servent à recrééer le tableau de coups
    while(etatJeux.bar[couleur] != 0 && coupATester != -1){
        move = faireMove(0,coups[coupATester],couleur);
        if(coupPossible(etatJeux.board,move,couleur)){
            jouerCoup(etatJeux,move,couleur);
            *nbCoups--;
            coupsJoues++;
        }else{
            coupsRestants[courant] = coups[coupATester];
            courant++;
        }
        coupATester--;
    }
    coups = coupsRestants; //coups deviennent les coups restants --> A TESTER !!! j'ai jamais fait ça !
    return coupsJoues;
}

//retourne le nombre de coups joués
int algoCoupPareil(SGameState etatJeux, unsigned int coup, int nbCoups, int couleur){
    int coupJoues = 0;
    SMove move;
    int courant; //case courante à tester
    if(couleur == WHITE) courant = 1;
    else courant = 24;
    while(nbCoups != 0 && courant != 0 && courant != 25){
        if(etatJeux.board[courant-1].owner == couleur){
            move = faireMove(courant-1,coup,couleur);
            while(nbCoups != 0 && coupPossible(etatJeux.board,move,couleur)){
                jouerCoup(etatJeux,move,couleur);
                coupJoues++;
                nbCoups--;
            }
        }else{
            if(couleur == WHITE) courant++;
            else courant--;
        }
    }
    return coupJoues;
}


int algoCoupDifferent(SGameState etatJeux, int coup[2], int couleur){
    //si on en trouve un qui peut se faire que avec un dé, on le fait puis on lance l'autre algo avec le dé restant.
    //on peut regarder aussi si un pion peut être joué avec les deux dés et qu'il y a au moins deux pions
    int coupJoues = 0;
    SMove move1, move2, move3;
    int courant; //case courante à tester
    if(couleur == WHITE) courant = 1;
    else courant = 24;
    int iJetonChiant = 0,coup1,coup2;
    while(courant != 0 && courant != 25){
        if(etatJeux.board[courant-1].owner == couleur){
            move1 = faireMove(courant-1,coup[0],couleur);
            move2 = faireMove(courant-1,coup[1],couleur);
            move3 = faireMove(courant-1,coup[0]+coup[1],couleur);
            coup1 = coupPossible(etatJeux.board,move1,couleur);
            coup2 = coupPossible(etatJeux.board,move2,couleur);
            if(coup1 && coup2){
                //les deux coups sont possibles
                //s'il y a au moins 2 jetons, c'est bon
                //si ya qu'un jeton mais qu'on peut faire la somme des dés, c'est bon aussi
                if(etatJeux.board[courant-1].nbDames >= 2 || coupPossible(etatJeux.board,move3,couleur)) return 2;
                //sinon on ajoute ce pion au tableau des "jetons chiants", mais on a pas besoin de savoir sa valeur, juste le nombre de jeton Chiants
                //si on ajoute le deuxième jeton chiant, c'est bon car on a deux jetons différents où on peut faire les deux combinaisons
                if(iJetonChiant == 1) return 2;
                iJetonChiant++;
            }else if(coup1){
                jouerCoup(etatJeux,move1,couleur);
                return 1 + algoCoupPareil(etatJeux,coup[1],1,couleur);
            }else if(coup2){
                jouerCoup(etatJeux,move2,couleur);
                return 1 + algoCoupPareil(etatJeux,coup[0],1,couleur);
            }//sinon on peut rien faire avec ce jeton
        }
        //passer au jeton suivant
        if(couleur == WHITE) courant++;
        else courant--;
    }
    return iJetonChiant; //si y'en a 1, alors on peut jouer qu'un coup, sinon on peut en jouer aucun
}

int coupPossible(Square board[], SMove move, int couleur){
    if(move.dest_point == 25) return 1;
    //sinon faut que ça soit pas une case adverse, ou alors y a qu'un jeton
    else return (board[move.dest_point-1].owner != -couleur || board[move.dest_point-1].nbDames == 1);
}

void jouerCoup(SGameState etatJeux, SMove move, int couleur){
    if(move.src_point == 0){
         etatJeux.bar[couleur]--;
         //si c'est une case adverse, on mange le pion
         if(etatJeux.board[move.dest_point-1].owner == -couleur){
            etatJeux.bar[-couleur]++;
            etatJeux.board[move.dest_point-1].nbDames = 0;
         }
         etatJeux.board[move.dest_point-1].nbDames++;
         etatJeux.board[move.dest_point-1].owner = couleur;

    }
    else if(move.dest_point == 25){
         etatJeux.out[couleur]++;
         etatJeux.board[move.src_point-1].nbDames--;
         if(etatJeux.board[move.src_point-1].nbDames == 0) etatJeux.board[move.src_point-1].owner = NOBODY;
    }else{
        etatJeux.board[move.src_point-1].nbDames--;
        if(etatJeux.board[move.src_point-1].nbDames == 0) etatJeux.board[move.src_point-1].owner = NOBODY;
        //si c'est une case adverse, on mange le pion
         if(etatJeux.board[move.dest_point-1].owner == -couleur){
            etatJeux.bar[-couleur]++;
            etatJeux.board[move.dest_point-1].nbDames = 0;
         }
         etatJeux.board[move.dest_point-1].owner = couleur;
         etatJeux.board[move.dest_point-1].nbDames++;
    }
}

SMove faireMove(int src, int numDe, int couleur){
    int dest;
    if(couleur == WHITE){
        dest = src + dest;
        if(dest > 25) dest = 25;
    }else{
        dest = src - dest;
        if(dest < 1) dest = 25;
    }
    SMove move = {src,dest};
    return move;
}
