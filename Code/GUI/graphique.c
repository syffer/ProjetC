
#include "graphique.h"
//#include "arbitre.h"

#include <stdlib.h>
#include <stdio.h>

#include <math.h>


#define HAUTEUR_FENETRE 752
#define LARGEUR_FENETRE 1422

#define HAUTEUR_POPUP 342
#define LARGEUR_POPUP 594

// position de la zone de clic des boutons (en prenant pour origine (0,0) le bord haut gauche de la fenetre popup)
#define BORNE_INF_Y_BOUTON 244
#define BORNE_SUP_Y_BOUTON 309

#define BORNE_INF_X_YES 53
#define BORNE_SUP_X_YES 280

#define BORNE_INF_X_NO 311
#define BORNE_SUP_X_NO 539

#define ZONE_CLIC_Y_INF ( (HAUTEUR_FENETRE / 2) - (HAUTEUR_POPUP / 2) + BORNE_INF_Y_BOUTON )
#define ZONE_CLIC_Y_SUP ( (HAUTEUR_FENETRE / 2) - (HAUTEUR_POPUP / 2) + BORNE_SUP_Y_BOUTON )

#define ZONE_CLIC_X_YES_INF ( (LARGEUR_FENETRE / 2) - (LARGEUR_POPUP / 2) + BORNE_INF_X_YES )
#define ZONE_CLIC_X_YES_SUP ( (LARGEUR_FENETRE / 2) - (LARGEUR_POPUP / 2) + BORNE_SUP_X_YES )

#define ZONE_CLIC_X_NO_INF ( (LARGEUR_FENETRE / 2) - (LARGEUR_POPUP / 2) + BORNE_INF_X_NO )
#define ZONE_CLIC_X_NO_SUP ( (LARGEUR_FENETRE / 2) - (LARGEUR_POPUP / 2) + BORNE_SUP_X_NO )




#define TAILLE_TEXTE 30

#define LARGEUR_CASE        84 // 84 px de large pour chaque case
#define HAUTEUR_CASE        260
#define NB_CASES_LARGEUR    12 // 12 cases de largeur




struct Graphique {

    SDL_Surface* ecran;
    SDL_Surface* fond;

    SDL_Surface* de1;
    SDL_Surface* de2;

    TTF_Font* police;

    SDL_Surface* texte_MiseCourante;
    SDL_Surface* texte_ScoreBlanc;
    SDL_Surface* texte_ScoreNoir;
    SDL_Surface* texte_ScoreCible;
    SDL_Surface* texte_Tour;

    SDL_Surface* texte_LabelMiseCourante;
    SDL_Surface* texte_LabelScoreBlanc;
    SDL_Surface* texte_LabelScoreNoir;
    SDL_Surface* texte_LabelScoreCible;


    Plateau plateau;
    Deplacement deplacement;
    SDL_TimerID timer;
};
typedef struct Graphique Graphique;

static Graphique graphique;


/**
* Actualise tous les éléments graphiques et actualise l'écran
*/
void rafraichirGraphique()
{

    SDL_Rect position;

    //rafraichissement del'image de fond
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(graphique.fond, NULL, graphique.ecran, &position);

    //rafraichissement de la mise courante
    position.x = 40;
    position.y = 420;
    SDL_BlitSurface( graphique.texte_MiseCourante, NULL, graphique.ecran, &position );

    //rafraichissement du texte du score blanc
    position.x = 490;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_ScoreBlanc, NULL, graphique.ecran, &position );

    //rafraichissement du texte du score noir
    position.x = 1120;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_ScoreNoir, NULL, graphique.ecran, &position );

    //rafraichissement du texte du score cible
    position.x = 750;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_ScoreCible, NULL, graphique.ecran, &position );

    position.x = 25;
    position.y = 380;
    SDL_BlitSurface( graphique.texte_LabelMiseCourante, NULL, graphique.ecran, &position );


    position.x = 220;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_LabelScoreBlanc, NULL, graphique.ecran, &position );


    position.x = 860;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_LabelScoreNoir, NULL, graphique.ecran, &position );


    position.x = 580;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_LabelScoreCible, NULL, graphique.ecran, &position );

    /*
    *
    *
    *   TOUR !!!!
    *
    *
    *
    */
    position.x = 580;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_Tour, NULL, graphique.ecran, &position );




    //Rafraichissement des dés
    rafraichirDes();

    updatePionsGraphique();

    SDL_Flip( graphique.ecran );


}

int initialiserFenetre() {

    /* ---------- Initialisation de la fenetre ---------- */


    // Initialisation de la SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) {      // | SDL_INIT_TIMER
        fprintf( stderr,  "Impossible de charger SDL : %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
        //return -1;
    }

    // create a new window
    graphique.ecran = SDL_SetVideoMode( LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    if ( ! graphique.ecran ) {
        fprintf( stderr, "Impossible d'afficher la fenetre SDL a l'ecran : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Titre de la fenêtre
    SDL_WM_SetCaption("Backgammon", NULL);


    // chargement de l'image du plateau
    graphique.fond = SDL_LoadBMP("./GUI/Images/plateau.bmp");

    if ( ! graphique.fond ) {
        fprintf( stderr, "Impossible de charger l'image de fond du plateau : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
        //return -1;
    }


    // avoir un fonc blanc au cas ou
    SDL_FillRect( graphique.ecran, NULL, SDL_MapRGB( graphique.ecran->format, 255, 255, 255 ) );


    //SDL_FreeSurface(mapRGB);



    // on applique l'image de fond sur l'écran
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface( graphique.fond, NULL, graphique.ecran, &position );



    /* ---------- Affichage des textes ---------- */


    // démarrage de la bibliothèque ttf pour écrire du texte
    if( TTF_Init() == -1 ) {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
        //return -1;
    }

    // polices d'écriture sur le plateau
    graphique.police = TTF_OpenFont( "./GUI/Polices/arial.ttf", TAILLE_TEXTE );
    if( ! graphique.police ) {
        fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }


    SDL_Color couleurNoire = {0, 0, 0};

    // ----------------- labels


    graphique.texte_LabelMiseCourante = TTF_RenderText_Blended( graphique.police, "Mise : ", couleurNoire );
    graphique.texte_LabelScoreBlanc = TTF_RenderText_Blended( graphique.police, "Score joueur blanc : ", couleurNoire );
    graphique.texte_LabelScoreNoir = TTF_RenderText_Blended( graphique.police, "Score joueur noir : ", couleurNoire );
    graphique.texte_LabelScoreCible = TTF_RenderText_Blended( graphique.police, "Score cible : ", couleurNoire );


    // ----------------- texte informatifs

    graphique.texte_MiseCourante = TTF_RenderText_Blended( graphique.police, "", couleurNoire );
    graphique.texte_ScoreBlanc = TTF_RenderText_Blended( graphique.police, "", couleurNoire );
    graphique.texte_ScoreNoir = TTF_RenderText_Blended( graphique.police, "", couleurNoire );
    graphique.texte_ScoreCible = TTF_RenderText_Blended( graphique.police, "", couleurNoire );
    graphique.texte_Tour = TTF_RenderText_Blended( graphique.police, "", couleurNoire );

    //rafraichissement de l'image
    rafraichirGraphique();

    creerPlateau( &(graphique.plateau) );
    initCases( &(graphique.plateau) );


    graphique.deplacement.plateau = graphique.plateau;

    return EXIT_SUCCESS;
}

/**
* Libère les ressources du plateau (le fond et l'écran)
*/
void fermerFenetre() {


    TTF_CloseFont(graphique.police); //fermeture de la police d'écriture
    TTF_Quit();

    SDL_FreeSurface(graphique.fond);
    SDL_FreeSurface(graphique.ecran);

    SDL_FreeSurface(graphique.texte_MiseCourante);
    SDL_FreeSurface(graphique.texte_ScoreBlanc);
    SDL_FreeSurface(graphique.texte_ScoreNoir);
    SDL_FreeSurface(graphique.texte_ScoreCible);
    SDL_FreeSurface(graphique.texte_Tour);

    SDL_FreeSurface(graphique.texte_LabelMiseCourante);
    SDL_FreeSurface(graphique.texte_LabelScoreBlanc);
    SDL_FreeSurface(graphique.texte_LabelScoreNoir);
    SDL_FreeSurface(graphique.texte_LabelScoreCible);

    SDL_FreeSurface( graphique.de1 );
    SDL_FreeSurface( graphique.de2 );

    freeTousLesPions();

    SDL_Quit();

    printf("(graphique) Terminé correctement\n");
}

void freeTousLesPions()
{
    int i, j;
    Case case_b;
    SDL_Surface* imagePion;

    //libération des pions du tableau
    for( i = 0; i < 24; i++)
    {
        case_b = graphique.plateau.tabCases[i];
        for( j = 0; j < case_b.nbPions -1; j++)
        {
            imagePion = case_b.tabPions[j].imagePion;
            SDL_FreeSurface( imagePion );
            freePion(&case_b.tabPions[j]);
        }
    }

    // on libère les pions du bar
    for (i = 0; i < 2; i++)
    {
        OutGraphique g = graphique.plateau.outGraphique[i];

        for(j = 0; j < g.caseOut.nbPions -1; j++)
        {
            if(g.caseOut.nbPions > 0) // si il y a au moins1 pion dans le bar
            {
                imagePion = g.caseOut.tabPions[j].imagePion;
                SDL_FreeSurface( imagePion );
                freePion(&g.caseOut.tabPions[j]);
            }
        }
    }
}

/**
* Initialise les pions à leur bonne position sur le plateau et les affecte aux bonnes cases
*/
void initialiserPlateauGraphique( SGameState* gameState ) {

    // attention aux cases BAR et OUT à l'initialisation (ils peuvent changés)
    int i;
    int j;
    Pion pion;
    SDL_Rect pos;


    //on réinitialise le nombre de pions sortis
    graphique.plateau.out[0] = 0;
    graphique.plateau.out[1] = 0;

    // on réinitialise le nombre de pions de chaque bar
    graphique.plateau.barGraphique[0].nbPions = 0;
    graphique.plateau.barGraphique[1].nbPions = 0;

    //updateOutGraphic(gameState ->turn);

    for(i = 0; i < 24; i++)//pour chaque Square
    {
        graphique.plateau.tabCases[i].nbPions = 0;
        for(j = 0; j < gameState-> board[i].nbDames; j++) // pour chaque dame dans la case, on créé un pion et on l'ajoute à la case
        {

            if(gameState -> board[i].owner == WHITE) // si joueur blanc
                pion  = creerPion(graphique.plateau.tabCases[i].posX, graphique.plateau.tabCases[i].posY, "./GUI/Images/blanc.bmp");
            else if (gameState ->board[i].owner == BLACK)// si joueur noir
                pion = creerPion(graphique.plateau.tabCases[i].posX, graphique.plateau.tabCases[i].posY, "./GUI/Images/noir.bmp");

            pos = positionnerPion(&graphique.plateau.tabCases[i], i ); // positionnement du pion sur la case
            pion.posPion = pos;

            graphique.plateau.tabCases[i].tabPions[j] = pion; // ajout du pion dans la bonne case
            graphique.plateau.tabCases[i].nbPions ++;
            SDL_SetColorKey(graphique.plateau.tabCases[i].tabPions[j].imagePion, SDL_SRCCOLORKEY, SDL_MapRGB(graphique.plateau.tabCases[i].tabPions[j].imagePion->format, 255, 255, 255));
            SDL_BlitSurface(graphique.plateau.tabCases[i].tabPions[j].imagePion, NULL, graphique.ecran, &graphique.plateau.tabCases[i].tabPions[j].posPion);
        }
    }

    SDL_Flip( graphique.ecran );


    updateScoreJoueurBlanc( gameState -> whiteScore );
    updateScoreJoueurNoir( gameState -> blackScore );
    updateMiseCouranteGraphique( gameState -> stake );
    updateScoreCibleGraphique(0);
    updateTourJoueurGraphique( gameState -> turn );
}

/**
* Permet de blitter les pions sur le plateau
*/
void updatePionsGraphique()
{
    int i, j;

    Case case_b;
    Pion pion;

    //blit des pions du plateau
    for(i = 0; i < 24; i++)
    {
        case_b = graphique.plateau.tabCases[i];
        for(j = 0; j < case_b.nbPions; j++)
        {
            pion = case_b.tabPions[j];
            SDL_BlitSurface(pion.imagePion, NULL, graphique.ecran, &pion.posPion);
        }
    }

    // blit des pions du bar
    for(i = 0; i < 2; i++)
    {
        case_b = graphique.plateau.barGraphique[i];

        for(j = 0; j < case_b.nbPions; j++)
        {
            pion = case_b.tabPions[j];
            SDL_BlitSurface(pion.imagePion, NULL, graphique.ecran, &pion.posPion);
        }
    }

}

/**
* Permet de blitter les dés sur le plateau
*/
void updateDesGraphique( unsigned char dices[2] ) {

    char* pathCompletDe1 = retournerPathDe( dices[0] );
    char* pathCompletDe2 = retournerPathDe( dices[1] );

    SDL_FreeSurface( graphique.de1 );
    SDL_FreeSurface( graphique.de2 );

    graphique.de1 = SDL_LoadBMP(pathCompletDe1);
    graphique.de2 = SDL_LoadBMP(pathCompletDe2);

    rafraichirDes();
    // les positions des dés peuvent être sauvegardés quelque part pour ne pas à avoir à les recréer à chaque fois.

}

void rafraichirDes()
{
    SDL_Rect posDe1;
    posDe1.x = 883;
    posDe1.y = 360;

    SDL_Rect posDe2;
    posDe2.x = 945;
    posDe2.y = 360;

    SDL_BlitSurface( graphique.de1, 0, graphique.ecran, &posDe1 );
    SDL_BlitSurface( graphique.de2, 0, graphique.ecran, &posDe2 );

    SDL_Flip(graphique.ecran);

}

void updateTourJoueurGraphique( Player joueur ) {

    printf("__________________ (graphique) graphique update tour joueur \n");

    SDL_Color couleurNoire = {0, 0, 0};

    char chaine[50];
    if(joueur == WHITE)
        sprintf( chaine, "Au tour de WHITE de jouer");
    if(joueur == BLACK)
        sprintf( chaine, "Au tour de BLACK de jouer");

    SDL_FreeSurface(graphique.texte_Tour);
    graphique.texte_Tour = TTF_RenderText_Blended( graphique.police, chaine, couleurNoire );

    rafraichirGraphique();

    printf("__________________ (graphique) fin graphique update tour joueur \n");
}

/**
* Met à jour la valeur du score du joueur blanc et l'affiche sur le plateau
*/
void updateScoreJoueurBlanc( int score ) {

    SDL_Color couleurNoire = {0, 0, 0};

    char chaine[15];
    sprintf( chaine, "%d", score );

    SDL_FreeSurface(graphique.texte_ScoreBlanc);
    graphique.texte_ScoreBlanc = TTF_RenderText_Blended( graphique.police, chaine, couleurNoire );

    rafraichirGraphique();
}

/**
* Met à jour la valeur du score du joueur noir et l'affiche sur le plateau
*/
void updateScoreJoueurNoir(int score) {

    SDL_Color couleurNoire = {0, 0, 0};

    char chaine[15];
    sprintf( chaine, "%d", score );

    SDL_FreeSurface(graphique.texte_ScoreNoir);
    graphique.texte_ScoreNoir = TTF_RenderText_Blended( graphique.police, chaine, couleurNoire );

    rafraichirGraphique();
}

/**
* Met à jour la valeur du score de la cible et l'affiche sur le plateau
*/
void updateScoreCibleGraphique( int scoreCible ) {

    SDL_Color couleurNoire = {0, 0, 0};
    char chaine[15];
    sprintf( chaine, "%d", scoreCible );

    SDL_FreeSurface(graphique.texte_ScoreCible);
    graphique.texte_ScoreCible = TTF_RenderText_Blended( graphique.police, chaine, couleurNoire );


    rafraichirGraphique();
}

/**
* Met à jour la valeur de la mise courante et l'affiche sur le plateau
*/
void updateMiseCouranteGraphique( int nouvelleMise ) {

    SDL_Color couleurNoire = {0, 0, 0};

    char chaine[15];
    sprintf( chaine, "%d", nouvelleMise );

    SDL_FreeSurface(graphique.texte_MiseCourante);
    graphique.texte_MiseCourante = TTF_RenderText_Blended( graphique.police, chaine, couleurNoire );

    rafraichirGraphique();
}



// pour libJoueur.h
// retourne la position de la case graphique sélectionnée par l'utilisateur (avec la souris)
int selectionnerCaseGraphique() {
    // SDL event clic souris sur une des cases
    int posX, posY;

    int numeroCase;

    SDL_Event event;
    while( 1 ) {

        SDL_WaitEvent(&event);

        switch(event.type) {

            case SDL_QUIT:
                exit( EXIT_SUCCESS );   // pas bien de faire comme ça
                break;

            case SDL_MOUSEBUTTONUP:

                if (event.button.button == SDL_BUTTON_LEFT ) {

                    posX = event.motion.x;
                    posY = event.motion.y;

                    numeroCase = retournerNumCase( event.motion.x, event.motion.y, graphique.plateau );

                    printf("(graphique selectionner case) %i %i %i \n", posX, posY, numeroCase );


                    if( numeroCase != -1 ) return numeroCase;
                    // sinon, le joueur n'a pas cliqué sur uen zone valide

                }

                break;

            default:
                break;
        }
    }

    return -1;
}


// retourne 1 si le joueur a cliqué sur "OUI", 0 sinon
int getChoixUtilisateurGraphique() {


    // sdl event clic souris sur bouton "YES/NO"
    SDL_Event event;

    int posX, posY;

    while( 1 ) {

        SDL_WaitEvent(&event);

        switch(event.type) {


            case SDL_QUIT:
                return 0;
                break;
            case SDL_MOUSEBUTTONUP:

                if (event.button.button == SDL_BUTTON_LEFT ) {

                    posX = event.motion.x;
                    posY = event.motion.y;

                    if( ZONE_CLIC_Y_INF <= posY && posY <= ZONE_CLIC_Y_SUP ) {

                        if( ZONE_CLIC_X_YES_INF <= posX && posX <= ZONE_CLIC_X_YES_SUP ) {      // bouton "OUI"
                            return 1;
                        }
                        else if( ZONE_CLIC_X_NO_INF <= posX && posX <= ZONE_CLIC_X_NO_SUP ) { // bouton "NON"
                            return 0;
                        }
                        // sinon, on est pas dans l'une des zones des boutons

                    }
                    // sinon on est pas dans la zone des boutons

                }

                break;

            default:
                break;
        }
    }

    return 0;
}


void ouvrirFenetreDoublerMiseGraphique( int miseCourante ) {
    char message[50];
    sprintf( message, "Mise actuelle : %i ", miseCourante );
    creerFenetrePopup( message, "Voulez-vous doubler la mise ?" );
}

void ouvrirFenetreAccepterDoublerMise( int nouvelleMise ) {
    char message[50];
    sprintf( message, "Nouvelle mise : %i ", nouvelleMise );
    creerFenetrePopup( message, "Acceptez-vous la nouvelle mise ?" );
}


void creerFenetrePopup( char* messageMise, char* messageQuestion ) {

    // chargement de l'image
    SDL_Surface* imagePopup = SDL_LoadBMP("./GUI/Images/popup.bmp");
    if ( ! imagePopup ) {
        fprintf( stderr, "Impossible de charger l'image de la fenetre popup : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // création du texte de la fenêtre
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Surface* texteMessageMise = TTF_RenderText_Blended( graphique.police, messageMise, couleurNoire );
    if ( ! texteMessageMise ) {
        fprintf( stderr, "Impossible de creer le texte de la fenetre popup : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }



    SDL_Surface* texteMessageQuestion = TTF_RenderText_Blended( graphique.police, messageQuestion, couleurNoire );
    if ( ! texteMessageQuestion ) {
        fprintf( stderr, "Impossible de creer le texte de la fenetre popup : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    int hauteurTexte, largeurTexte;

    // affichage de la fenetre
    SDL_Rect position;
    position.x = ( LARGEUR_FENETRE / 2 ) - ( LARGEUR_POPUP / 2 );
    position.y = ( HAUTEUR_FENETRE / 2 ) - ( HAUTEUR_POPUP / 2 );
    SDL_SetColorKey( imagePopup, SDL_SRCCOLORKEY, SDL_MapRGB(imagePopup->format, 255, 255, 255) );
    SDL_BlitSurface( imagePopup, NULL, graphique.ecran, &position );

    // affichage du texte de la fenetre
    TTF_SizeText( graphique.police, messageMise, &largeurTexte, &hauteurTexte );    // taille tu texte
    position.x = ( LARGEUR_FENETRE / 2 ) - ( largeurTexte / 2 );
    position.y = ( HAUTEUR_FENETRE / 2 ) - ( HAUTEUR_POPUP / 2 ) + 80;
    SDL_BlitSurface( texteMessageMise, NULL, graphique.ecran, &position );

    TTF_SizeText( graphique.police, messageQuestion, &largeurTexte, &hauteurTexte );
    position.x = ( LARGEUR_FENETRE / 2 ) - ( largeurTexte / 2 );
    position.y = ( HAUTEUR_FENETRE / 2 ) - ( HAUTEUR_POPUP / 2 ) + 160;
    SDL_BlitSurface( texteMessageQuestion, NULL, graphique.ecran, &position );


    // liberation des ressources non utilisés
    SDL_FreeSurface( texteMessageMise );
    SDL_FreeSurface( texteMessageQuestion );

    SDL_FreeSurface( imagePopup );

    // mise à jour de l'écran
    SDL_Flip( graphique.ecran );
}


/**
* Met en pause le jeu en attendant un évènement
*/

void pause() {

    int continuer = 1;
    SDL_Event event;

    SMove move;

    while (continuer) {

        SDL_WaitEvent(&event);

        switch(event.type) {

            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:

                switch(event.key.keysym.sym) {

                    case SDLK_ESCAPE:
                        printf("leave \n");
                        continuer = 0;
                        break;

                    case SDLK_SPACE:
                        printf("leave \n");
                        continuer = 0;

                        break;
                    case SDLK_g: // mettre pion blanc dans le out
                        move.dest_point = 25;
                        move.src_point = 12;
                        deplacerPionGraphique(move, WHITE);
                    break;
                    case SDLK_h: // mettre pion noir dans le out
                        move.dest_point = 25;
                        move.src_point = 13;
                        deplacerPionGraphique(move, BLACK);
                    break;
                    case SDLK_j: // mettre pion blanc dans le bar
                        move.dest_point = 0;
                        move.src_point = 12;
                        deplacerPionGraphique(move, WHITE);
                    break;
                    case SDLK_k: // mettre pion noir dans le bar
                        move.dest_point = 0;
                        move.src_point = 13;
                        deplacerPionGraphique(move, BLACK);
                    break;

                    case SDLK_l: // enlever pion blanc du bar
                        move.dest_point = 12;
                        move.src_point = 0;
                        deplacerPionGraphique(move, WHITE);
                    break;
                    case SDLK_a: // enlever pion noir du bar
                        move.dest_point = 13;
                        move.src_point = 0;
                        deplacerPionGraphique(move, BLACK);
                    break;

                    default:

                        break;
                }

            break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    move.dest_point = retournerNumCase(event.motion.x, event.motion.y, graphique.plateau);
                    printf("destination : %i\n", move.dest_point);
                    deplacerPionGraphique(move, 0);

                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    move.src_point = retournerNumCase(event.motion.x, event.motion.y, graphique.plateau);
                    printf("source : %i\n", move.src_point);
                   // surlignerCase(move.src_point);
                }
            break;

            default:
                break;
        }
    }
}



/**
* retourne le chemin de l'image selon la valeur retournée par le lancement de dés
*/
char* retournerPathDe(char dice)
{
    switch(dice)
    {
        case 1:
            return "./GUI/Images/Des/de1.bmp";
        case 2:
            return "./GUI/Images/Des/de2.bmp";
        case 3:
            return "./GUI/Images/Des/de3.bmp";
        case 4:
            return "./GUI/Images/Des/de4.bmp";
        case 5:
            return "./GUI/Images/Des/de5.bmp";
        case 6:
            return "./GUI/Images/Des/de6.bmp";
        default:
            return NULL;
    }
}


/**
*Initialisation de la position des dés
**/
void positionnerDes(SDL_Rect* posDe1, SDL_Rect* posDe2)
{
    posDe1 -> x = 883;
    posDe1 -> y = 360;

    posDe2 -> x = 945;
    posDe2 -> y = 360;
}

/**
*Créé un pion à la position spécifiée et avec l'image spécifiée
**/
Pion creerPion(int posX, int posY, char* image)
{
    Pion pion;
    SDL_Rect pos;
    SDL_Surface* imagePion = SDL_LoadBMP(image);

    pos.x = posX;
    pos.y = posY;

    pion.posPion = pos;
    pion.imagePion = imagePion;

    return pion;
}

void updateOutGraphic(int numJoueur)
{
    int epaisseurPion = 10;

    int nbOut;

    if(numJoueur == WHITE){
        graphique.plateau.outGraphique[WHITE].valeur = graphique.plateau.out[WHITE];
        graphique.plateau.outGraphique[WHITE].valeur ++; // on incrémente le nombre de pions sortis du joueur
        nbOut = graphique.plateau.outGraphique[WHITE].valeur;

    }
    else if(numJoueur == BLACK){
        graphique.plateau.outGraphique[BLACK].valeur = graphique.plateau.out[BLACK];
        graphique.plateau.outGraphique[BLACK].valeur ++;
        nbOut = graphique.plateau.outGraphique[BLACK].valeur;
    }

    int hauteurARemplir = nbOut*epaisseurPion;
    SDL_Rect posOut;

    SDL_Surface *outJoueur = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, hauteurARemplir, 32, 0, 0, 0, 0);
    if(numJoueur == BLACK){

        SDL_FillRect(outJoueur, NULL, SDL_MapRGB(graphique.ecran->format, 0, 0, 0));
        posOut.x = graphique.plateau.outGraphique[BLACK].posX;
        posOut.y = graphique.plateau.outGraphique[BLACK].posY;

        SDL_BlitSurface(outJoueur, NULL, graphique.fond, &posOut);
       // drawEmptyRect(outJoueur, posOut.x-1, posOut.y-1, 150, 50, 255, 0, 0 );
    }
    else if(numJoueur == WHITE){

        SDL_FillRect(outJoueur, NULL, SDL_MapRGB(graphique.ecran->format, 255, 255, 255));
        posOut.x = graphique.plateau.outGraphique[WHITE].posX;
        posOut.y = graphique.plateau.outGraphique[WHITE].posY;

        SDL_BlitSurface(outJoueur, NULL, graphique.fond, &posOut);

        //drawEmptyRect(outJoueur, posOut.x-1, posOut.y-1, 150, 50, 255, 0, 0 );
    }


    SDL_FreeSurface(outJoueur);


    rafraichirGraphique();
}

/**
*   Retourne la bonne position que devra avoir le pion qui se déplace sur cette case
*/
SDL_Rect positionnerPion(Case *case_pos, int numCase){


    int nbPions = case_pos -> nbPions;
    SDL_Rect pos;

    int hauteurPion = 54;


    if(numCase >= 0 && numCase <= 11) // cases du bas
    {
        pos.x = case_pos->posX;
        pos.y = case_pos->posY - nbPions * (hauteurPion - 20) - hauteurPion;

    }
    else // cases du haut
    {
        pos.x = case_pos->posX;
        pos.y = case_pos->posY + nbPions * (hauteurPion - 20);

    }

    return pos;
}

/**
* Fonction à appeler qui permet de déplacer le dernier pion d'une case vers une autre avec le SMove passé en paramètre
*/
void deplacerPionGraphique(SMove move, Player couleur)
{

    if(move.src_point != move.dest_point && move.src_point != 25) // pas de déplacement si déplacement sur lui même et pas de déplacement venant du out
    {

        printf( "(graphique) move : src = %i, dest = %i\n", move.src_point, move.dest_point );

        if(move.dest_point >=0 && move.src_point >= 0)
        {

            // pas de déplacement si déplacement sur lui même et pas de déplacement venant du out
            if( move.src_point == move.dest_point ) return;
            if( move.src_point == 25 ) return;


            if( move.dest_point == -1 ) {
                return;
            }

            if( move.src_point == -1 ) {
                return;
            }


            if( move.dest_point >= 0 && move.src_point >= 0 )
            {

                int src = move.src_point;
                int dest = move.dest_point;

                graphique.deplacement.dest = dest;
                graphique.deplacement.source = src;

                if(src == 0 || dest == 0){ // on teste si le mouvement concerne le bar

                    if(dest == 0) // on déplace le pion vers le bar
                    {
                        src --;

                        Case case_src = graphique.plateau.tabCases[src];
                        Case case_dest = graphique.plateau.barGraphique[couleur];

                        int nbPionsSrc = case_src.nbPions; //nombre de pions dans la case source
                        int nbPionsDest = case_dest.nbPions; // nombre de pions dans la case destination

                        if(nbPionsSrc > 0 && nbPionsDest < 15)
                        {

                            graphique.plateau.tabCases[src] = case_src;
                            graphique.plateau.barGraphique[couleur] = case_dest;

                            //on effectue le déplacement
                            deplacerPionVers(&case_src.tabPions[nbPionsSrc -1], &case_dest);

                            case_dest.nbPions++;// on augmente le nombre de pions de la case destinataire
                            nbPionsDest = case_dest.nbPions;

                            // affectation du pion à la nouvelle case
                            case_dest.tabPions[nbPionsDest-1] = case_src.tabPions[nbPionsSrc-1];

                            case_src.nbPions --; // on décrémente le nombre de pions de la source
                            // printf("Après déplacement, pos pion : x = %i, y = %i\n", graphique.plateau.tabCases[src].tabPions[nbPionsSrc-1].posPion.x, graphique.plateau.tabCases[src].tabPions[nbPionsSrc-1].posPion.y);
                            nbPionsSrc = case_src.nbPions ;
                            nbPionsDest = case_dest.nbPions;

                            graphique.plateau.tabCases[src] = case_src;
                            graphique.plateau.barGraphique[couleur] = case_dest;
                            printf("(graphique) Nb cases dans dest : %i\n", nbPionsDest);
                        }
                    }

                    else if(src == 0 && dest != 25) // on sort le pion du bar
                    {
                        dest --;

                        Case case_src = graphique.plateau.barGraphique[couleur];
                        Case case_dest = graphique.plateau.tabCases[dest];

                        int nbPionsSrc = case_src.nbPions; //nombre de pions dans la case source
                        int nbPionsDest = case_dest.nbPions; // nombre de pions dans la case destination

                        //printf("Nb cases dans src : %i\n", nbPionsSrc);

                        if(nbPionsSrc > 0)
                        {

                            graphique.plateau.barGraphique[couleur] = case_src;
                            graphique.plateau.tabCases[dest] = case_dest;

                            //on effectue le déplacement
                            deplacerPionVers(&case_src.tabPions[nbPionsSrc -1], &case_dest);

                            case_dest.nbPions++;// on augmente le nombre de pions de la case destinataire
                            nbPionsDest = case_dest.nbPions;

                            // affectation du pion à la nouvelle case
                            case_dest.tabPions[nbPionsDest-1] = case_src.tabPions[nbPionsSrc-1];

                            case_src.nbPions --; // on décrémente le nombre de pions de la source
                            // printf("Après déplacement, pos pion : x = %i, y = %i\n", graphique.plateau.tabCases[src].tabPions[nbPionsSrc-1].posPion.x, graphique.plateau.tabCases[src].tabPions[nbPionsSrc-1].posPion.y);
                            nbPionsSrc = case_src.nbPions ;
                            nbPionsDest = case_dest.nbPions;

                            graphique.plateau.barGraphique[couleur] = case_src;
                            graphique.plateau.tabCases[dest] = case_dest;
                        }

                    }

                }//bar
                else if(dest == 25) // out
                {
                    int nbDames = graphique.plateau.tabCases[src - 1].nbPions -1;

                    Case case_src = graphique.plateau.tabCases[src - 1];
                    Case case_dest = graphique.plateau.outGraphique[couleur].caseOut;
                    case_dest.nbPions = 0;
                    //graphique.plateau.tabCases[src-1].nbPions --;

                    int nbPionsSrc = case_src.nbPions;

                    // graphique.plateau.outGraphique[couleur].caseOut.nbPions ++;
                    if(nbPionsSrc > 0)
                    {
                        //déplacement du pion vers le out
                        deplacerPionVers(&case_src.tabPions[nbPionsSrc -1], &case_dest);

                        //on diminue le nombre de pions de la source
                        case_src.nbPions --;

                        case_dest.tabPions[0] = case_src.tabPions[nbPionsSrc-1]; // on affecte tout le temps à la première case du tableau le pion que l'on veut retirer

                        graphique.plateau.tabCases[src-1] = case_src;
                        graphique.plateau.outGraphique[couleur].caseOut = case_dest;

                        graphique.plateau.out[couleur] ++; // on ajoute 1 dans le compteur des pions sortis du joueur
                        freePion(&graphique.plateau.tabCases[src -1].tabPions[nbDames]); // on libère la surface du pion
                        updateOutGraphic(couleur);
                    }

                }
                else
                {

                    //on décrémente la source et la destination pour correspondre avec les bonnes valeurs du tableau
                    src --;
                    dest --;

                    Case case_src = graphique.plateau.tabCases[src];
                    Case case_dest = graphique.plateau.tabCases[dest];

                    //printf("Case %i possède %i pions\n", src, case_src.nbPions);

                    int nbPionsSrc = case_src.nbPions; //nombre de pions dans la case source
                    int nbPionsDest = case_dest.nbPions; // nombre de pions dans la case destination

                    if(nbPionsSrc > 0)
                    {

                        graphique.plateau.tabCases[src] = case_src;
                        graphique.plateau.tabCases[dest] = case_dest;

                        //on effectue le déplacement
                        deplacerPionVers(&case_src.tabPions[nbPionsSrc -1], &case_dest);

                        case_dest.nbPions++;// on augmente le nombre de pions de la case destinataire
                        nbPionsDest = case_dest.nbPions;

                        // affectation du pion à la nouvelle case
                        case_dest.tabPions[nbPionsDest-1] = case_src.tabPions[nbPionsSrc-1];

                        case_src.nbPions --; // on décrémente le nombre de pions de la source
                        // printf("Après déplacement, pos pion : x = %i, y = %i\n", graphique.plateau.tabCases[src].tabPions[nbPionsSrc-1].posPion.x, graphique.plateau.tabCases[src].tabPions[nbPionsSrc-1].posPion.y);
                        nbPionsSrc = case_src.nbPions ;
                        nbPionsDest = case_dest.nbPions;

                        graphique.plateau.tabCases[src] = case_src;
                        graphique.plateau.tabCases[dest] = case_dest;

                        // printf("Après deplacement : src contient %i pions, dest contient %i pions\n", case_src.nbPions, case_dest.nbPions);
                        //printf("[Case tableau]Après deplacement : src contient %i pions, dest contient %i pions\n", graphique.plateau.tabCases[src].nbPions, graphique.plateau.tabCases[dest].nbPions);

                    }
                }

                rafraichirGraphique();
            }
        }

    }
}

/**
*   fonction qui déplace le pion passé en paramètre
*/
void deplacerPionVers(Pion *pion, Case* case_dest)
{
    int dest = graphique.deplacement.dest;

    SDL_Rect posFinale = positionnerPion(case_dest, dest -1);

    int x = posFinale.x;
    int y = posFinale.y;

   // printf("x : %i, y : %i\n", pion ->posPion.x, pion->posPion.y);

    // calcul de la valeur absolue entre la position du pion et sa position d'arrivée
    int distanceX = fabs(pion->posPion.x - x);
    int distanceY = fabs(pion->posPion.y - y);

    int incrementPos = 1;

    while(distanceX > 1 || distanceY > 1)
    {
        //test de la position en x du pion par rapport à la position finale
        if(pion->posPion.x < x)
            pion->posPion.x +=incrementPos;
        else if(pion->posPion.x >= x)
            pion->posPion.x  -= incrementPos;

        //test de la position en y du pion par rapport à la position finale
        if(pion-> posPion.y < y)
            pion-> posPion.y +=incrementPos;
        else if(pion-> posPion.y >= y)
            pion-> posPion.y -= incrementPos;

        //MàJ de la distance entre le pion et sa position finale
        distanceX = fabs(pion->posPion.x - x);
        distanceY = fabs(pion->posPion.y - y);
        //updatePionsGraphique();

        /*
        SDL_Rect pos;
        pos.x = 0;
        pos.y = 0;
        */

        //SDL_BlitSurface(graphique.fond, NULL, graphique.ecran, &pos);
        SDL_BlitSurface(pion->imagePion, NULL, graphique.ecran, &pion ->posPion);
       // updatePionsGraphique();
        SDL_Flip( graphique.ecran );
        //rafraichirGraphique();

    }
}

/**
*Initialise les cases du plateau avec leur bonne position
**/
void initCases(Plateau *plateau)
{
    int i;
    int width = plateau ->largeur;
    int height = plateau -> hauteur;

    Case case_b;
    for(i = 0; i <= 5; i++) // partie inférieure droite
    {

        width -= LARGEUR_CASE;
        case_b.posX = width;

        case_b.posY = height;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        plateau -> tabCases[i] = case_b;

       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }
    width = 760;
    for(i = 18; i <= 23; i++) // partie supérieure droite
    {

        case_b.posX = width;
        width += LARGEUR_CASE;
        case_b.posY = 90;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        plateau -> tabCases[i] = case_b;
       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }


    width = 640; // début de la partie inferieure droite - le bord noir
    for(i = 6; i <= 11; i++) // partie inférieure gauche
    {
        width -= LARGEUR_CASE;
        case_b.posX = width;

        case_b.posY = height;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        plateau -> tabCases[i] = case_b;
       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }
    width = 140;
    for(i = 12; i <= 17; i++) // partie superieure gauche
    {

        case_b.posX = width;
        width += LARGEUR_CASE;
        case_b.posY = 90;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        plateau -> tabCases[i] = case_b;
      //  printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }

    //initialisation du bar

    case_b.hauteur = HAUTEUR_CASE *2;
    case_b.largeur = LARGEUR_CASE;
    case_b.nbPions = 0;
    case_b.posX = 650;
    case_b.posY = 100;

    plateau ->barGraphique[0] = case_b;

    case_b.posX = 650;
    case_b.posY = 500;

    plateau ->barGraphique[1] = case_b;

    //initialisation des outGraphique
    OutGraphique outG;

    outG.valeur = 0;
    outG.hauteur = 150;
    outG.largeur = 50;
    outG.posX = 1285;
    outG.posY = 120;

    case_b.posX = 1285;
    case_b.posY = 120;

    outG.caseOut = case_b;

    plateau ->outGraphique[1] = outG;

    case_b.posY = 544;

    outG.caseOut = case_b;
    outG.posY = 544;
    plateau ->outGraphique[0] = outG;

}

/**
*Affecte les bonnes dimensions au plateau
**/
void creerPlateau(Plateau *plateau)
{
    plateau -> hauteur = 725;
    plateau -> largeur = 1270;
}

/**
* Libère la surface d'un pion
*/
void freePion(Pion *pion)
{
    SDL_FreeSurface(pion ->imagePion);
}
/**
* Retourne le numéro de la case dans laquelle on clique
*/
int retournerNumCase(int sourisX, int sourisY, Plateau plateau)
{
    int i;
    Case case_b;
    for(i = 0; i < 12; i++) //cases du bas
    {
        // on calcule la position pour les cases normales du bas
        case_b = plateau.tabCases[i];
       // printf("case : x :%i, y : %i\n", case_b.posX, case_b.posY);

        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY <= case_b.posY && sourisY >= case_b.posY - case_b.hauteur)
            return i+1;
    }

    i = 12;
    for(i = 12; i < 24; i++)//cases du haut
    {
         // on calcule la position pour les cases normales du haut
        case_b = plateau.tabCases[i];
      //  printf("case : x :%i, y : %i\n", case_b.posX, case_b.posY);
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY <= case_b.posY + case_b.hauteur && sourisY >= case_b.posY)
            return i+1;
    }

    // on teste pour le out
        case_b = plateau.outGraphique[0].caseOut;
     //   printf("case : x :%i, y : %i\n", case_b.posX, case_b.posY);
            //out du haut
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY >= case_b.posY && sourisY <= case_b.posY + case_b.hauteur)
            return 25;

         // out du bas
        case_b = plateau.outGraphique[1].caseOut;
      //  printf("case : x :%i, y : %i\n", case_b.posX, case_b.posY);
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY >= case_b.posY && sourisY <= case_b.posY + case_b.hauteur)
            return 25;

         // on teste pour détecter le bar
        case_b = plateau.barGraphique[0];
      //  printf("case : x :%i, y : %i\n", case_b.posX, case_b.posY);
        //bar du haut
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY >= case_b.posY && sourisY <= case_b.posY + case_b.hauteur)
            return 0;
        // bar du bas
        case_b = plateau.barGraphique[1];
     //   printf("case : x :%i, y : %i\n", case_b.posX, case_b.posY);
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY >= case_b.posY && sourisY <= case_b.posY + case_b.hauteur)
            return 0;

    //printf(" --------------------------------------------------------------> (graphique) fonction retournerNumCase() ==> ne devrait pas arriver la, car il retourne -1 \n");

    return -1;
}

void surlignerCase(int numCase)
{
    int x = graphique.plateau.tabCases[numCase-1].posX;
    int y = graphique.plateau.tabCases[numCase-1].posY;
    int largeur = LARGEUR_CASE;
    int hauteur = HAUTEUR_CASE;

    drawEmptyRect(graphique.plateau.tabCases[numCase-1].imageCase, x, y, hauteur, largeur, 0,255,0 );

    SDL_Rect posCase;

    posCase.x = graphique.plateau.tabCases[numCase].posX;
    posCase.y = graphique.plateau.tabCases[numCase].posY;

    SDL_BlitSurface(graphique.plateau.tabCases[numCase].imageCase, NULL, graphique.fond, &posCase);
    //rafraichirGraphique();
    //SDL_BlitSurface(graphique.fond, NULL, graphique.ecran, &posEcran);
    //SDL_Flip(graphique.ecran);
}


void drawEmptyRect(SDL_Surface* surf,int posX, int posY, int width, int length, int R, int G, int B)
{
	SDL_Rect ligneHaut;
	ligneHaut.x = posX-1;
	ligneHaut.y = posY-1;
	ligneHaut.w = length;
	ligneHaut.h = 1;
	SDL_FillRect(surf, &ligneHaut, SDL_MapRGB(surf->format, R, G, B));

	SDL_Rect ligneDroite;
	ligneDroite.x = posX+length-1;
	ligneDroite.y = posY-1;
	ligneDroite.w = 1;
	ligneDroite.h = width;

	SDL_FillRect(surf, &ligneDroite, SDL_MapRGB(surf->format, R, G, B));

	SDL_Rect ligneGauche;
	ligneGauche.x = posX-1;
	ligneGauche.y = posY-1;
	ligneGauche.w = 1;
	ligneGauche.h = width;

	SDL_FillRect(surf, &ligneGauche, SDL_MapRGB(surf->format, R, G, B));

	SDL_Rect ligneBas;
	ligneBas.x = posX-1;
	ligneBas.y = posY+width-1;
	ligneBas.w = length;
	ligneBas.h = 1;

	SDL_FillRect(surf, &ligneBas, SDL_MapRGB(surf->format, R, G, B));
}
