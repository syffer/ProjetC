#include "graphique.h"
#include "arbitre.h"

#include <stdlib.h>
#include <stdio.h>

#include <math.h>

#define HAUTEUR_FENETRE 1280
#define LARGEUR_FENETRE 752

#define TAILLE_TEXTE 30

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
* Actualise tous les éléments graphiques, actualise l'écran puis libère les ressources
*/
void rafraichirGraphique()
{

    SDL_Rect position;

    //rafraichissement del'image de fond
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(graphique.fond, NULL, graphique.ecran, &position);

    //rafraichissement de la mise courante
    position.x = 25;
    position.y = 330;
    SDL_BlitSurface( graphique.texte_MiseCourante, NULL, graphique.ecran, &position );

    //rafraichissement du texte du score blanc
    position.x = 200;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_ScoreBlanc, NULL, graphique.ecran, &position );

    //rafraichissement du texte du score noir
    position.x = 900;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_ScoreNoir, NULL, graphique.ecran, &position );

    //rafraichissement du texte du score cible
    position.x = 500;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_ScoreCible, NULL, graphique.ecran, &position );

    position.x = 25;
    position.y = 300;
    SDL_BlitSurface( graphique.texte_LabelMiseCourante, NULL, graphique.ecran, &position );


    position.x = 200;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_LabelScoreBlanc, NULL, graphique.ecran, &position );


    position.x = 800;
    position.y = 30;
    SDL_BlitSurface( graphique.texte_LabelScoreNoir, NULL, graphique.ecran, &position );


    position.x = 40;
    position.y = 40;
    SDL_BlitSurface( graphique.texte_LabelScoreCible, NULL, graphique.ecran, &position );

    rafraichirDes();

    updatePionsGraphique();

    SDL_Flip( graphique.ecran );

    /*SDL_FreeSurface(graphique.texte_MiseCourante);
    SDL_FreeSurface(graphique.texte_ScoreBlanc);
    SDL_FreeSurface(graphique.texte_ScoreNoir);
    SDL_FreeSurface(graphique.texte_ScoreCible);*/

}

int initialiserFenetre() {

    /* ---------- Initialisation de la fenetre ---------- */


    // Initialisation de la SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ) {      // | SDL_INIT_TIMER
        printf( "Impossible de charger SDL : %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
        //return -1;
    }

    // create a new window
    graphique.ecran = SDL_SetVideoMode( HAUTEUR_FENETRE, LARGEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    if ( ! graphique.ecran ) {
        printf("Impossible d'afficher la fenetre SDL a l'ecran : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Titre de la fenêtre
    SDL_WM_SetCaption("Backgammon", NULL);


    // chargement de l'image du plateau
    graphique.fond = SDL_LoadBMP("./Images/plateau.bmp");

    if ( ! graphique.fond ) {
        printf("Impossible de charger l'image de fond du plateau : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
        //return -1;
    }


    // avoir un fonc blanc au cas ou
    SDL_FillRect( graphique.ecran, NULL, SDL_MapRGB( graphique.ecran->format, 255, 255, 255) );

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
    graphique.police = TTF_OpenFont( "Polices/arial.ttf", TAILLE_TEXTE );
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


    TTF_CloseFont( graphique.police ); //fermeture de la police d'écriture
    TTF_Quit();

    SDL_FreeSurface( graphique.fond );
    SDL_FreeSurface( graphique.ecran );

    SDL_Quit();

    printf("Terminé correctement\n");


}

/**
* Initialise les pions à leur bonne position sur le plateau et les affecte aux bonnes cases
*/
void initialiserPlateauGraphique( SGameState* gameState ) {

    // attention aux cases BAR et OUT à l'initialisation (ils peuvent changés)

    int i;
    int j;
    for(i = 0; i < 24; i++)//pour chaque Square
    {
        Case case_b = graphique.plateau.tabCases[i];

        for(j = 0; j < gameState-> board[i].nbDames; j++) // pour chaque dame dans la case, on créé un pion et on l'ajoute à la case
        {
            Pion pion;

            if(gameState -> board[i].owner == WHITE) // si joueur blanc
              pion  = creerPion(graphique.plateau.tabCases[i].posX, graphique.plateau.tabCases[i].posY, "./Images/blanc.bmp");
            else if (gameState ->board[i].owner == BLACK)// si joueur noir
               pion = creerPion(graphique.plateau.tabCases[i].posX, graphique.plateau.tabCases[i].posY, "./Images/noir.bmp");

            SDL_Rect pos = positionnerPion(&graphique.plateau.tabCases[i], i ); // positionnement du pion sur la case
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
    // updateTourJoueurGraphique( gameState -> turn );
}

/**
* Permet de blitter les pions sur le plateau
*/
void updatePionsGraphique()
{
    int i, j;

    for(i = 0; i < 24; i++)
    {
        Case case_b = graphique.plateau.tabCases[i];
        for(j = 0; j < case_b.nbPions; j++)
        {
            Pion pion = case_b.tabPions[j];
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

    SDL_Flip( graphique.ecran );

   // SDL_FreeSurface( graphique.de1 );
  //  SDL_FreeSurface( graphique.de2 );
}

void updateTourJoueurGraphique( Player joueur ) {

}

void updateScoreJoueurBlanc( int score ) {

}

void updateScoreJoueurNoir(int score) {

}

void updateScoreCibleGraphique( int scoreCible ) {

}

/**
* Met à jour la valeur de la mise courante et l'affiche sur le plateau
*/
void updateMiseCouranteGraphique( int nouvelleMise ) {

    SDL_Color couleurNoire = {0, 0, 0};

    char chaine[15];
    sprintf( chaine, "%d", nouvelleMise );


    graphique.texte_MiseCourante = TTF_RenderText_Blended( graphique.police, chaine, couleurNoire );

    rafraichirGraphique();

}







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







/**
* Met en pause le jeu en attendant un évènement
*/
void pause() {

    int continuer = 1;
    SDL_Event event;


    unsigned char dices[2];
    SMove move;
    int numCase;
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
                    case SDLK_g:
                        updateOutGraphic(1);
                    break;
                    case SDLK_h:
                        updateOutGraphic(0);
                    break;
                    default:
                        lancerLesDes(dices);
                        updateDesGraphique(dices);
                        break;
                }

            break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    move.dest_point = retournerNumCase(event.motion.x, event.motion.y, graphique.plateau);
                    printf("destination : %i\n", move.dest_point);
                    deplacerPionGraphique(move, 1);

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
            return "./Images/Des/de1.bmp";
        case 2:
            return "./Images/Des/de2.bmp";
        case 3:
            return "./Images/Des/de3.bmp";
        case 4:
            return "./Images/Des/de4.bmp";
        case 5:
            return "./Images/Des/de5.bmp";
        case 6:
            return "./Images/Des/de6.bmp";
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
    int x = 50;
    int i;
    int epaisseurPion = 10;

    int nbOut;

    if(numJoueur == BLACK){
        graphique.plateau.outGraphique[BLACK].valeur = graphique.plateau.out[BLACK];
        nbOut = graphique.plateau.outGraphique[BLACK].valeur;
        graphique.plateau.outGraphique[BLACK].valeur ++;
        nbOut++;
    }
    else if(numJoueur == WHITE){
        graphique.plateau.outGraphique[WHITE].valeur = graphique.plateau.out[WHITE];
        nbOut = graphique.plateau.outGraphique[WHITE].valeur;
        graphique.plateau.outGraphique[WHITE].valeur ++;
        nbOut++;
    }


   // nbOut ++; //ajout d'un pion dans le out du joueur

    int hauteurARemplir = nbOut*epaisseurPion;
    SDL_Rect posOut;

    SDL_Surface *outJoueur = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, hauteurARemplir, 32, 0, 0, 0, 0);
    if(numJoueur == WHITE){

        SDL_FillRect(outJoueur, NULL, SDL_MapRGB(graphique.ecran->format, 255, 255, 255));
        posOut.x = graphique.plateau.outGraphique[WHITE].posX;
        posOut.y = graphique.plateau.outGraphique[WHITE].posY;

        SDL_BlitSurface(outJoueur, NULL, graphique.fond, &posOut);
       // drawEmptyRect(outJoueur, posOut.x-1, posOut.y-1, 150, 50, 255, 0, 0 );
    }
    else if(numJoueur == BLACK){

        SDL_FillRect(outJoueur, NULL, SDL_MapRGB(graphique.ecran->format, 0, 0, 0));
        posOut.x = graphique.plateau.outGraphique[BLACK].posX;
        posOut.y = graphique.plateau.outGraphique[BLACK].posY;

        SDL_BlitSurface(outJoueur, NULL, graphique.fond, &posOut);

        //drawEmptyRect(outJoueur, posOut.x-1, posOut.y-1, 150, 50, 255, 0, 0 );
    }


    rafraichirGraphique();
}

/**
*   Retourne la bonne position que devra avoir le pion qui se déplace sur cette case
*/
SDL_Rect positionnerPion(Case *case_pos, int numCase){


    int nbPions = case_pos -> nbPions;
    printf("[--ENTREE DANS POSITIONNER PION-- La case destination contient %i pions]\n ", nbPions);
    SDL_Rect pos;

    int hauteurPion = 54;


    if(numCase >= 0 && numCase <= 11) // cases du bas
    {
        pos.x = case_pos->posX;
        pos.y = case_pos->posY - nbPions * hauteurPion - hauteurPion;

    }
    else // cases du haut
    {
        pos.x = case_pos->posX;
        pos.y = case_pos->posY + nbPions * hauteurPion;

    }

    return pos;
}

/**
* Fonction à appeler qui permet de déplacer le dernier pion d'une case vers une autre avec le SMove passé en paramètre
*/
void deplacerPionGraphique(SMove move, Player couleur)
{
    if(move.src_point != move.dest_point)
    {
        if(move.dest_point >=0)
        {
            int src = move.src_point;
            int dest = move.dest_point;

            if(src == 0 || dest == 0){}//bar
            else if(dest == 25){
                graphique.plateau.out[couleur] ++; // on ajoute 1 dans le comteur des pions sortis du joueur
                updateOutGraphic(couleur);
            } // out
            else{

                graphique.deplacement.dest = dest;
                graphique.deplacement.source = src;

                //on décrémente la source et la destination pour correspondre avec les bonnes valeurs du tableau
                src --;
                dest --;

                Case case_src = graphique.plateau.tabCases[src];
                Case case_dest = graphique.plateau.tabCases[dest];

                printf("Case %i possède %i pions\n", src, case_src.nbPions);

                int nbPionsSrc = case_src.nbPions; //nombre de pions dans la case source
                int nbPionsDest = case_dest.nbPions; // nombre de pions dans la case destination

                if(nbPionsSrc > 0)
                {
                    //transfert du pion d'une case à une autre
                    Pion pion = case_src.tabPions[nbPionsSrc-1];

                    graphique.plateau.tabCases[src] = case_src;
                    graphique.plateau.tabCases[dest] = case_dest;

                    //on effectue le déplacement
                    deplacerPionVers(&case_src.tabPions[nbPionsSrc -1]);

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

                    printf("Après deplacement : src contient %i pions, dest contient %i pions\n", case_src.nbPions, case_dest.nbPions);
                    printf("[Case tableau]Après deplacement : src contient %i pions, dest contient %i pions\n", graphique.plateau.tabCases[src].nbPions, graphique.plateau.tabCases[dest].nbPions);

                }

            }

        rafraichirGraphique();
        
        }
    }


}

/**
*   fonction qui déplace le pion passé en paramètre
*/
void deplacerPionVers(Pion *pion)
{
    int source = graphique.deplacement.source;
    int dest = graphique.deplacement.dest;

    Case case_dest = graphique.plateau.tabCases[dest -1]; //case de destination
    Case case_src = graphique.plateau.tabCases[source -1]; //case source
    SDL_Rect posFinale = positionnerPion(&case_dest, dest -1);

    int x = posFinale.x;
    int y = posFinale.y;

   // printf("x : %i, y : %i\n", pion ->posPion.x, pion->posPion.y);

    int distanceX = fabs(pion->posPion.x - x);
    int distanceY = fabs(pion->posPion.y - y);

    int incrementPos = 1;
    int deplacement = 1;

    while(deplacement)
    {
        if(distanceX/incrementPos > 0 || distanceY/incrementPos > 0)
        {
            printf("distanceX :%i - distanceY : %i\n", distanceX, distanceY);
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
            SDL_Rect pos;

            pos.x = 0;
            pos.y = 0;

            //SDL_BlitSurface(graphique.fond, NULL, graphique.ecran, &pos);
            SDL_BlitSurface(pion->imagePion, NULL, graphique.ecran, &pion ->posPion);
           // updatePionsGraphique();
            SDL_Flip( graphique.ecran );
            //rafraichirGraphique();
        }
        else
            deplacement = 0;

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

    for(i = 0; i <= 5; i++) // partie inférieure droite
    {
        Case case_b;
        width -= LARGEUR_CASE;
        case_b.posX = width;

        case_b.posY = height;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        SDL_Surface* surface;
        case_b.imageCase = surface;

        plateau -> tabCases[i] = case_b;

       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }
    width = 760;
    for(i = 18; i <= 23; i++) // partie supérieure droite
    {
        Case case_b;

        case_b.posX = width;
        width += LARGEUR_CASE;
        case_b.posY = 90;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        SDL_Surface* surface;
        case_b.imageCase = surface;

        plateau -> tabCases[i] = case_b;
       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }

    width = 640; // début de la partie inferieure droite - le bord noir
    for(i = 6; i <= 11; i++) // partie inférieure gauche
    {
        Case case_b;
        width -= LARGEUR_CASE;
        case_b.posX = width;

        case_b.posY = height;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        SDL_Surface* surface;
        case_b.imageCase = surface;

        plateau -> tabCases[i] = case_b;
       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }
    width = 140;
    for(i = 12; i <= 17; i++) // partie superieure gauche
    {
        Case case_b;

        case_b.posX = width;
        width += LARGEUR_CASE;
        case_b.posY = 90;
        case_b.nbPions = 0;
        case_b.largeur = LARGEUR_CASE;
        case_b.hauteur = HAUTEUR_CASE;

        SDL_Surface* surface;
        case_b.imageCase = surface;

        plateau -> tabCases[i] = case_b;
      //  printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }

    //initialisation des outGraphique
    OutGraphique outG;

    outG.valeur = 0;
    outG.hauteur = 150;
    outG.largeur = 50;
    outG.posX = 20;
    outG.posY = 200;

    plateau ->outGraphique[0] = outG;

    outG.posY = 400;
    plateau ->outGraphique[1] = outG;

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
* Retourne le numéro de la case dans laquelle on clique
*/
int retournerNumCase(int sourisX, int sourisY, Plateau plateau)
{
    int i;
    int numCase;

    for(i = 0; i < 12; i++) //cases du bas
    {
        Case case_b = plateau.tabCases[i];
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY <= case_b.posY && sourisY >= case_b.posY - case_b.hauteur)
            return i+1;
    }

    i = 12;
    for(i = 12; i < 24; i++)//cases du haut
    {
        Case case_b = plateau.tabCases[i];
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY <= case_b.posY + case_b.hauteur && sourisY >= case_b.posY)
            return i+1;
    }

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
    SDL_Rect posEcran;
    posCase.x = graphique.plateau.tabCases[numCase].posX;
    posCase.y = graphique.plateau.tabCases[numCase].posY;

    posEcran.x = 0;
    posEcran.y = 0;
    SDL_BlitSurface(graphique.plateau.tabCases[numCase].imageCase, NULL, graphique.fond, &posCase);
    //rafraichirGraphique();
    //SDL_BlitSurface(graphique.fond, NULL, graphique.ecran, &posEcran);
    SDL_Flip(graphique.ecran);
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
