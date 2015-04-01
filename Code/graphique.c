#include "graphique.h"
#include "arbitre.h"
#include <stdlib.h>
#include <windows.h>
#include <math.h>

// Permet d'afficher la fenêtre de jeu
int afficherJeu()
{

    // Initialisation de la SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Impossible de démarrer la fenêtre SDL : %s\n", SDL_GetError() );
        return 1;
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
    SDL_SetColorKey(p.imagePion, SDL_SRCCOLORKEY, SDL_MapRGB(p.imagePion->format, 255, 255, 255));
    // program main loop
    int done = 0;
    int tempsPrecedent = 0, tempsActuel = 0;

    while (done != 1)
    {
        // message processing loop
        SDL_PollEvent(&event);

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
                            printf("salut");
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
                        case SDLK_g:

                        break;
                        default:
                            break;
                    }
                }
                break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        deplacerPionVers(&p, event.button.x, event.button.y, tempsPrecedent);
                    }

                break;

            default:
                break;

        }

        // Début de la partie pour redessiner les éléments
        // réinitialisation de l'écran
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));


        // on applique l'image de fond
        SDL_BlitSurface(plateau, 0, screen, &dstrect);

        SDL_BlitSurface(p.imagePion, 0, screen, &p.posPion);
        //int i, j;

        /*for(i = 0; i < 24; i++)
        {
            for(j = 0; j < s_plateau.tabCases[i].nbPions; j++)
            {
                SDL_BlitSurface(s_plateau.tabCases[i].tabPions[j].imagePion, 0, plateau, &s_plateau.tabCases[i].tabPions[j].posPion );
            }

        }*/

        // on applique l'image des dés
        SDL_BlitSurface(de1, 0, screen, &posDe1);
        SDL_BlitSurface(de2, 0, screen, &posDe2);

        // On met à jour l'écran
        SDL_Flip(screen);
    } // end main loop

    // libération des surfaces
    SDL_FreeSurface(plateau);
    SDL_FreeSurface(de1);
    SDL_FreeSurface(de2);
    //freePlateau(&s_plateau);
    SDL_FreeSurface(p.imagePion);
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

    pion.hauteurPion = 59;
    pion.largeurPion = 57;
    pion.posPion = pos;
    //printf("x :%i - y : %i\n", pion.posPion.x, pion.posPion.y);
    pion.imagePion = imagePion;

    return pion;
}
void deplacerPionVers(Pion *pion, int x, int y, int tempsPrecedent)
{
    int distanceX = fabs(pion -> posPion.x - x);
    int distanceY = fabs(pion -> posPion.y - y);
    int tempsActuel;


        tempsActuel = SDL_GetTicks();
        distanceX = fabs(pion -> posPion.x - x);
        distanceY = fabs(pion -> posPion.y - y);
    int increpentPos = 10;
        if (tempsActuel - tempsPrecedent > 30) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            if(distanceX > 0 && distanceY > 0)
            {
                if(pion -> posPion.x < x)
                    pion -> posPion.x +=increpentPos;
                else if(pion -> posPion.x > x)
                    pion -> posPion.x -=increpentPos;


                if(pion -> posPion.y < y)
                    pion -> posPion.y +=increpentPos;
                else if(pion -> posPion.y > y)
                    pion -> posPion.y -=increpentPos;


                tempsPrecedent = tempsActuel;
            }

        }
}
/**
*Calcule la position que doit avoir le pion selon la case où on se déplace et le nombre de dames dessus.
*/
void positionnerPion(Pion *pion, Plateau *plateau, Case case_pos, int numCase){

    int hauteur_screen = plateau -> hauteur;
    int hauteurPion = 54;
    int nbPions = case_pos.nbPions;

    if(numCase >= 0 && numCase <= 11) // cases du bas
    {
        pion -> posPion.x = case_pos.posX;
        pion-> posPion.y = hauteur_screen - nbPions * hauteurPion - hauteurPion;
    }
    else // cases du haut
    {
        pion -> posPion.x = case_pos.posX;
        pion -> posPion.y = nbPions * hauteurPion;
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
        width -= 84;
        case_b.posX = width;
        case_b.posY = height;

        plateau -> tabCases[i] = case_b;
        printf("x : %i - y : %i\n", case_b.posX, case_b.posY);
    }

    for(i = 18; i < 23; i++) // partie supérieure droite
    {
        Case case_b;
        width -= 84;
        case_b.posX = width;
        case_b.posY = 0;

        plateau -> tabCases[i] = case_b;
        printf("x : %i - y : %i\n", case_b.posX, case_b.posY);
    }

    width = 628;
    for(i = 6; i <= 11; i++) // partie inférieure gauche
    {
        Case case_b;
        width -= 84;
        case_b.posX = width;
        case_b.posY = height;

        plateau -> tabCases[i] = case_b;
        printf("x : %i - y : %i\n", case_b.posX, case_b.posY);
    }
    width = 628;
    for(i = 12; i <= 17; i++) // partie superieure gauche
    {
        Case case_b;
        width -= 84;
        case_b.posX = width;
        case_b.posY = 0;

        plateau -> tabCases[i] = case_b;
        printf("x : %i - y : %i\n", case_b.posX, case_b.posY);
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

            plateau -> tabCases[i].tabPions[j] = pion; // ajout du pion dans la bonne case
            plateau -> tabCases[i].nbPions ++;
            positionnerPion(&pion, plateau, plateau -> tabCases[i], i ); // positionnement du pion sur la case
        }
    }
}
void creerPlateau(Plateau *plateau)
{
    plateau -> hauteur = 1280;
    plateau -> largeur = 752;
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
