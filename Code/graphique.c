#include "graphique.h"
#include "arbitre.h"
#include <stdlib.h>

#include <math.h>

#define HAUTEUR_FENETRE 1280
#define LARGEUR_FENETRE 752


int initialiserFenetre() {

    // plateau graphique à initialiser ici !!!


    // Initialisation de la SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) {
        printf( "Impossible de démarrer la fenêtre SDL : %s\n", SDL_GetError() );
        return -1;
    }

    //démarrage de la bibliothèque ttf pour écrire du texte
    if( TTF_Init() == -1 ) {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        //exit(EXIT_FAILURE);
        return -1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ) {
        printf("Impossible d'afficher l'écran : %s\n", SDL_GetError());
        return -1;
    }

    // Titre de la fenêtre
    SDL_WM_SetCaption("Backgammon", NULL);



    return 0;
}

void fermerFenetre() {

    // -------------------------------------------
    // libération propre de TOUTES les ressources 
    // -------------------------------------------

    /*
    // libération des surfaces
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(de1);
    SDL_FreeSurface(de2);
    //freePlateau(&s_plateau);
    SDL_FreeSurface(p.imagePion);
    SDL_FreeSurface(p2.imagePion);
    SDL_FreeSurface(s_stake);

    TTF_CloseFont(stake); //fermeture dela police d'écriture
    TTF_Quit();
    printf("Terminé correctement\n");
    */

}

void initialiserPlateauGraphique( SGameState* gameState ) {

}

void updateDesGraphique( unsigned char dices[2] ) {

}

void deplacerPionGraphique( SMove mouvement ) {

}

void updateTourJoueurGraphique( Player joueur ) {

}

void updateScoreJoueurBlanc(int score) {

}

void updateScoreJoueurNoir(int score) {

}

void updateScoreCibleGraphique( int scoreCible ) {

}

void updateMiseCouranteGraphique( int nouvelleMise ) {

}




void pause() {

    int continuer = 1;

    SDL_Event event;

    while (continuer) {

        SDL_WaitEvent(&event);

        switch(event.type) {

            case SDL_QUIT:
                printf("leave \n");
                continuer = 0; 
                break;

            
            case SDL_KEYDOWN:

                switch(event.key.keysym.sym) {

                    case SDLK_SPACE:
                        printf("espace \n");
                        continuer = 0;
                        break;

                    default:
                        break;
                }

                break;


            default:
                break;
        }

    }

}





// Permet d'afficher la fenêtre de jeu
int afficherJeu()
{

    // Initialisation de la SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "Impossible de démarrer la fenêtre SDL : %s\n", SDL_GetError() );
        return 1;
    }

    //démarrage de la bibliothèque ttf pour écrire du texte
    if(TTF_Init() == -1)
    {
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();

    int maxW=videoInfo->current_w;
    int maxH=videoInfo->current_h;
  // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(maxW, maxH, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface* de1;
    SDL_Surface* de2;

    char* pathCompletDe1 = "./Images/Des/de1.bmp";
    char* pathCompletDe2 = "./Images/Des/de1.bmp";
    SDL_Event event;

    Plateau s_plateau;

    unsigned char dices[2];

    if ( !screen )
    {
        printf("Impossible d'afficher l'écran : %s\n", SDL_GetError());
        return 1;
    }

    // Titre de la fenêtre
    SDL_WM_SetCaption("Backgammon", NULL);


    // chargement de l'image du plateau
    SDL_Surface* plateau = SDL_LoadBMP("./Images/plateau.bmp");

    if (!plateau)
    {
        printf("Impossible de charger l'image bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centrer l'image à l'écran
    SDL_Rect dstrect;
    dstrect.x = (screen->w - plateau->w) / 2;
    dstrect.y = (screen->h - plateau->h) / 2;

    SDL_Rect posDe1; // rect du dé1
    SDL_Rect posDe2; // rect du dé2

    //initialisation des dés
    de1 = SDL_LoadBMP(pathCompletDe1);
    de2 = SDL_LoadBMP(pathCompletDe2);

    SDL_Rect posStake;
    posStake.x = 80;
    posStake.y = 300;
    //mise courante de la partie
    TTF_Font *stake = TTF_OpenFont("angelina.ttf", 30);

    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Surface* s_stake;
    s_stake = TTF_RenderGlyph_Blended(stake, "Blabla", couleurNoire);

    // si impossible de charger les images des dés
    if (!de1 || !de2)
    {
        printf("Impossible de charger l'image : %s", SDL_GetError());
        return 1;
    }

    positionnerDes(&posDe1, &posDe2);
    creerPlateau(&s_plateau);
    //création des cases et affectation de leur position
    initCases(&s_plateau);
    //initPions(&s_plateau, etatJeux);
    Pion p = creerPion(130, 100, "./Images/noir.bmp");
    Pion p2 = creerPion(200, 200, "./Images/blanc.bmp");

    s_plateau.tabCases[0].tabPions[0] = p;
    s_plateau.tabCases[0].tabPions[1] = p2;
    s_plateau.tabCases[0].nbPions = 2;

    int tempsPrecedent = 0, tempsActuel;

    SDL_Rect pos1 = positionnerPion(&s_plateau, &s_plateau.tabCases[0], 0);
   // printf("Position du pion : x : %d - y : %d\n", pos.x, pos.y);
   //initialisation de la position des 2 pions
    //deplacerPionVers(&p, tempsPrecedent, pos1);

   // deplacerPionVers(&p2, tempsPrecedent, pos1);

    SDL_Surface *out1;

    SDL_TimerID timer;
    Deplacement deplacement;
    deplacement.plateau = s_plateau;

    //movePion(move, &s_plateau, tempsPrecedent);
    SDL_SetColorKey(p.imagePion, SDL_SRCCOLORKEY, SDL_MapRGB(p.imagePion->format, 255, 255, 255));
    SDL_SetColorKey(p2.imagePion, SDL_SRCCOLORKEY, SDL_MapRGB(p2.imagePion->format, 255, 255, 255));
    // program main loop
    int done = 0;


    while (done != 1)
    {
        // message processing loop
        SDL_WaitEvent(&event);

            // Gestion des évènements
            switch (event.type)
            {
                // sortie si on ferme la fenêtre
            case SDL_QUIT:
                done = 1;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        // si appui sur touche echap
                        case SDLK_ESCAPE:
                            done = 1;
                        break;
                        // si appui sur touche espace
                        case SDLK_SPACE:
                                lancerLesDes(dices);

                            // on actualise le chemin de l'image des dés
                            pathCompletDe1 = retournerPathDe(dices[0]);
                            pathCompletDe2 = retournerPathDe(dices[1]);

                            printf("%i - %i\n", dices[0], dices[1]);
                            de1 = SDL_LoadBMP(pathCompletDe1);
                            de2 = SDL_LoadBMP(pathCompletDe2);

                        break;

                        default:
                            break;
                    }
                }
                break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        SMove move;
                        move.src_point = 1;
                        move.dest_point = retournerNumCase(event.motion.x, event.motion.y, s_plateau)+1;
                        //movePion(move, &s_plateau);
                        deplacement.source = move.src_point;
                        deplacement.dest = move.dest_point;

                        timer = SDL_AddTimer(30, deplacerPionVers2, &deplacement);
                    }
                break;

            default:
                break;
        }


        // Début de la partie pour redessiner les éléments
        // réinitialisation de l'écran
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        updateOutGraphic(out1, 1, &s_plateau, screen);

        /*int numJoueur = -1;
        out1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
        if(numJoueur == WHITE)
            SDL_FillRect(out1, 0, SDL_MapRGB(screen->format, 255, 255, 255));
        else if(numJoueur == BLACK)
            SDL_FillRect(out1, 0, SDL_MapRGB(screen->format, 0, 0, 0));*/

        // on applique l'image de fond
        SDL_BlitSurface(plateau, 0, screen, &dstrect);

       // SDL_BlitSurface(out1, 0, screen, &dstrect);

        SDL_BlitSurface(deplacement.plateau.tabCases[0].tabPions[0].imagePion, 0, screen, &deplacement.plateau.tabCases[0].tabPions[0].posPion);
        SDL_BlitSurface(deplacement.plateau.tabCases[0].tabPions[1].imagePion, 0, screen, &deplacement.plateau.tabCases[0].tabPions[1].posPion);
        //SDL_BlitSurface(p2.imagePion, 0, screen, &p2.posPion);

        // on applique l'image des dés
        SDL_BlitSurface(de1, 0, screen, &posDe1);
        SDL_BlitSurface(de2, 0, screen, &posDe2);
        SDL_BlitSurface(s_stake, NULL, plateau, &posStake);
        // On met à jour l'écran
        SDL_Flip(screen);
    } // end main loop

    // libération des surfaces
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(de1);
    SDL_FreeSurface(de2);
    //freePlateau(&s_plateau);
    SDL_FreeSurface(p.imagePion);
    SDL_FreeSurface(p2.imagePion);
    SDL_FreeSurface(s_stake);

    TTF_CloseFont(stake); //fermeture dela police d'écriture
    TTF_Quit();
    printf("Terminé correctement\n");
    return 0;
}

// retourne le chemin de l'image selon la valeur retournée par le lancement de dés
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
*Créé un pion à la position spécifiéd et avec l'image spécifiée
**/
Pion creerPion(int posX, int posY, char* image)
{

    Pion pion;
    SDL_Rect pos;
    SDL_Surface* imagePion = SDL_LoadBMP(image);

    pos.x = posX;
    pos.y = posY;

    pion.posPion = pos;
    //printf("x :%i - y : %i\n", pion.posPion.x, pion.posPion.y);
    pion.imagePion = imagePion;

    return pion;
}

void updateOutGraphic(SDL_Surface *outJoueur, int numJoueur, Plateau *plateau, SDL_Surface *ecran)
{
    int x = 50;
    int i;
    int epaisseurPion = 10;

    int nbOut;
    if(numJoueur == -1)
        nbOut =plateau->out[0];
    else if(numJoueur == 1)
        nbOut =plateau->out[1];


    nbOut ++; //ajout d'un pion dans le out du joueur

    int hauteurARemplir = nbOut*epaisseurPion;
    outJoueur = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, hauteurARemplir, 32, 0, 0, 0, 0);
    /*if(numJoueur == WHITE)
       // SDL_FillRect(outJoueur, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    else if(numJoueur == BLACK)
      //  SDL_FillRect(outJoueur, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));*/
}
/**
*   Effectue le déplacement du pion vers la case spécifiée en paramètre
*/
void deplacerPionVers(Pion *pion, int tempsPrecedent, SDL_Rect posPion)
{
   // printf("Entrée dans deplacerPionVers");
    int x = posPion.x;
    int y = posPion.y;

    int distanceX = fabs(pion -> posPion.x - x);
    int distanceY = fabs(pion -> posPion.y - y);
    int tempsActuel;

    tempsActuel = SDL_GetTicks();
    distanceX = fabs(pion -> posPion.x - x);
    distanceY = fabs(pion -> posPion.y - y);
    int incrementPos = 15;
   // printf("Temps précédent : %i\n", tempsPrecedent);
    if (tempsActuel - tempsPrecedent > 30) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
    {
        if(distanceX > 0 && distanceY > 0)
        {
            if(pion -> posPion.x < x)
                pion -> posPion.x +=incrementPos;
            else if(pion -> posPion.x > x)
                pion -> posPion.x -=incrementPos;

            if(pion -> posPion.y < y)
                pion -> posPion.y +=incrementPos;
            else if(pion -> posPion.y > y)
                pion -> posPion.y -=incrementPos;

            tempsPrecedent = tempsActuel;
            //pion -> posPion = posPion;
        }
        else
        {
            pion -> posPion = posPion;
        }

        /*if(pion ->posPion.x == posPion.x && pion ->posPion.y == posPion.y)
        {
            case_b ->nbPions ++;
            case_b -> tabPions[case_b -> nbPions -1] = *pion;
        }*/

    }
}

Uint32 deplacerPionVers2(Uint32 intervalle, void *parametre)
{
    Deplacement* d = parametre;
    int source = d -> source;
    int dest = d-> dest;

    Plateau *plateau = &d->plateau;
    Case* case_dest = &plateau->tabCases[dest -1]; //case de destination
    Case* case_src = &plateau->tabCases[source -1]; //case source
    int nbPions = case_src -> nbPions;
    SDL_Rect posFinale = positionnerPion(plateau, case_dest, dest -1);
    // récupération du pion situé en haut de la case de départ
    Pion *pion = &case_src -> tabPions[nbPions - 1];

    int x = posFinale.x;
    int y = posFinale.y;

    printf("x : %i, y : %i\n", pion ->posPion.x, pion ->posPion.y);

    int distanceX = fabs(pion -> posPion.x - x);
    int distanceY = fabs(pion -> posPion.y - y);
    int incrementPos = 15;
    if(distanceX >= 0 && distanceY >= 0)
    {
        if(pion -> posPion.x < x)
            pion -> posPion.x +=incrementPos;
        else if(pion -> posPion.x > x)
            pion -> posPion.x -=incrementPos;

        if(pion -> posPion.y < y)
            pion -> posPion.y +=incrementPos;
        else if(pion -> posPion.y > y)
            pion -> posPion.y -=incrementPos;
    }
    else
    {
        SDL_Rect posPion;
        posPion.x = x;
        posPion.y = y;
        pion ->posPion = posPion;
    }

    return intervalle;
}
/**
*   Retourne la bonne position que devra avoir le pion qui se déplace sur cette case
*/
SDL_Rect positionnerPion(Plateau *plateau, Case *case_pos, int numCase){

    int nbPions = case_pos -> nbPions;
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
    printf("Case n° %i, de position x: %i, y : %i, nbPions = : %i\n",numCase, case_pos->posX, case_pos->posY, nbPions);
    return pos;
}


void movePion(SMove move, Plateau *plateau)
{
    int src = move.src_point;
    int dest = move.dest_point;
    Deplacement dep;

    dep.source = move.src_point;
    dep.dest = move.dest_point;
    dep.plateau = *plateau;

    if(src == 0 || dest == 0){}//bar
    else if(src == 25 || dest == 25){} // out
    else{

        src --;
        dest --;
        Case case_src = plateau ->tabCases[src];
        Case case_dest = plateau ->tabCases[dest];

        int nbPionsSrc = case_src.nbPions ; //index du pion a déplacer
        int nbPionsDest = case_dest.nbPions;

        if(nbPionsSrc > 0)
        {
            //transfert du pion d'une case à une autre
            Pion pion = plateau ->tabCases[src].tabPions[nbPionsSrc-1];

            printf("Avant deplacement : src contient %i pions, dest contient %i pions\n", nbPionsSrc, nbPionsDest);
            case_dest.nbPions ++; // on augmente le nombre de pions de la case destinataire
            int nbPionsDest = case_dest.nbPions;

            SDL_Rect newPos = positionnerPion(plateau, &plateau->tabCases[dest], dest); //calcul de la position qu'aura le pion
            //printf("Destination : %i - Position que le pion est censé avoir : x : %d, y : %d\n", dest, newPos.x, newPos.y);
            SDL_TimerID timer = SDL_AddTimer(30, deplacerPionVers2, &dep);
            // affectation du pion à la nouvelle case
            case_dest.tabPions[nbPionsDest-1] = pion;

            case_src.nbPions --;

            nbPionsSrc = case_src.nbPions ;
            nbPionsDest = case_dest.nbPions;

            printf("Après deplacement : src contient %i pions, dest contient %i pions\n", nbPionsSrc, nbPionsDest);
        }

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
    int hauteurCase = 260;
    int largeurCase = 84;
    for(i = 0; i <= 5; i++) // partie inférieure droite
    {
        Case case_b;

        case_b.posX = width;
        width -= largeurCase;
        case_b.posY = height;
        case_b.nbPions = 0;
        case_b.largeur = largeurCase;
        case_b.hauteur = hauteurCase;
        plateau -> tabCases[i] = case_b;
       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }
    width = 800;
    for(i = 18; i <= 23; i++) // partie supérieure droite
    {
        Case case_b;

        case_b.posX = width;
        width += largeurCase;
        case_b.posY = 100;
        case_b.nbPions = 0;
        case_b.largeur = largeurCase;
        case_b.hauteur = hauteurCase;

        plateau -> tabCases[i] = case_b;
       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }

    width = 600; // début de la partie inferieure droite - le bord noir
    for(i = 6; i <= 11; i++) // partie inférieure gauche
    {
        Case case_b;

        case_b.posX = width;
        width -= largeurCase;
        case_b.posY = height;
        case_b.nbPions = 0;
        case_b.largeur = largeurCase;
        case_b.hauteur = hauteurCase;

        plateau -> tabCases[i] = case_b;
       // printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }
    width = 180;
    for(i = 12; i <= 17; i++) // partie superieure gauche
    {
        Case case_b;

        case_b.posX = width;
        width += largeurCase;
        case_b.posY = 100;
        case_b.nbPions = 0;
        case_b.largeur = largeurCase;
        case_b.hauteur = hauteurCase;

        plateau -> tabCases[i] = case_b;
      //  printf("%i : x : %i - y : %i\n", i, case_b.posX, case_b.posY);
    }
}

/**
* initialise les pions aux bonnes cases
**/
void initPions(Plateau *plateau, SGameState gameState)
{
    int i;
    int j;
    for(i = 0; i < 24; i++)//pour chaque Square
    {
        for(j = 0; j < gameState.board[i].nbDames; j++) // pour chaque dame dans la case, on créé un pion et on l'ajoute à la case
        {
            Pion pion;
            if(gameState.board[i].owner == WHITE) // si joueur blanc
              pion  = creerPion(0,0, "./Images/blanc.bmp");
            else if (gameState.board[i].owner == BLACK)// si joueur noir
               pion = creerPion(0,0, "./Images/blanc.bmp");

            SDL_Rect pos = positionnerPion(plateau, &plateau -> tabCases[i], i ); // positionnement du pion sur la case
            pion.posPion = pos;

            plateau -> tabCases[i].tabPions[j] = pion; // ajout du pion dans la bonne case
            plateau -> tabCases[i].nbPions ++;

        }
    }
}
void creerPlateau(Plateau *plateau)
{
    plateau -> hauteur = 725;
    plateau -> largeur = 1225;
}

void freePlateau(Plateau *plateau)
{
    int i;
    int j;

    for(i = 0; i < 24; i++)
    {
        for(j = 0; j < plateau ->tabCases[i].nbPions; j++)
            SDL_FreeSurface(plateau ->tabCases[i].tabPions[j].imagePion);
    }
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
            return i;
    }

    i = 12;
    for(i = 12; i < 24; i++)//cases du haut
    {
        Case case_b = plateau.tabCases[i];
        if(sourisX >= case_b.posX && sourisX <= case_b.posX + case_b.largeur && sourisY <= case_b.posY + case_b.hauteur && sourisY >= case_b.posY)
            return i;
    }

    return -1;
}

