#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define ECRAN_ROUGE2 160
#define ECRAN_VERT2 0
#define ECRAN_BLEU2 0
#define HAUTEUR_ECRAN 600
#define LARGEUR_ECRAN 900
#define RIEN 0
#define CROIX 1
#define RONDS 2
#define EPPAISSEUR_BARRES 5
#define LONGUEUR_BARRES 500

int tour (int terrain[3] [3])
{
    int i = 0, j = 0, compteur = 0, tour = 0;
    for (i = 0; i < 3; i++)//parcourt du tableau
    {
        for (j = 0; j < 3; j++)
        {
            if (terrain[i] [j] != 0)
            {
                compteur++;
            }
        }
    }

    compteur = compteur%2;
    if (compteur == 1)
    {
        tour = 2;
    }
    else if (compteur == 0)
    {
        tour = 1;
    }
    return tour;
}

int ouEstClic (int x, int y, int *caseX, int *caseY)
{
    int i = 0, j = 0;
    int hautGaucheX = LARGEUR_ECRAN/2 - LONGUEUR_BARRES/2;
    int hautGaucheY = HAUTEUR_ECRAN/2 - LONGUEUR_BARRES/2;
    int terrain = 0;
    if (x > hautGaucheX && x < hautGaucheX + LONGUEUR_BARRES
        && y > hautGaucheY && y < hautGaucheY + LONGUEUR_BARRES)//si le curseur est sur le terrain
    {
        terrain = 1;
        for (j = 0; j < 3; j++)
        {
            for (i = 0; i<3; i++)
            {
                if (x > hautGaucheX + i*LONGUEUR_BARRES/3 && x < hautGaucheX + (i+1)*(LONGUEUR_BARRES/3)
                    && y > hautGaucheY + j*(LONGUEUR_BARRES/3) && y < hautGaucheY + (j+1)*(LONGUEUR_BARRES/3) )
                {
                    *caseX = i;
                    *caseY = j;
                }
            }
        }
    }
    else
    {
        terrain = 0;
    }
    return terrain;
}

void afficherMorpion(SDL_Surface *ecran)
{
    SDL_Surface *barreHorizontale = SDL_CreateRGBSurface(SDL_HWSURFACE, LONGUEUR_BARRES, EPPAISSEUR_BARRES, 32, 0, 0, 0, 0);
    SDL_Surface *barreVerticale = SDL_CreateRGBSurface(SDL_HWSURFACE, EPPAISSEUR_BARRES, LONGUEUR_BARRES, 32, 0, 0, 0, 0);
    SDL_FillRect(barreHorizontale, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_FillRect(barreVerticale, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    SDL_Rect barre1, barre2, barre3, barre4;

    barre1.x = LARGEUR_ECRAN/2 - LONGUEUR_BARRES/2 + LONGUEUR_BARRES/3;
    barre1.y = HAUTEUR_ECRAN/2 - LONGUEUR_BARRES/2;

    barre2.x = barre1.x + LONGUEUR_BARRES/3;
    barre2.y = barre1.y;

    barre3.x = barre1.x - LONGUEUR_BARRES/3;
    barre3.y = barre1.y + LONGUEUR_BARRES/3;

    barre4.x = barre3.x;
    barre4.y = barre3.y + LONGUEUR_BARRES/3;

    SDL_BlitSurface(barreVerticale, NULL, ecran, &barre1);
    SDL_BlitSurface(barreVerticale, NULL, ecran, &barre2);
    SDL_BlitSurface(barreHorizontale, NULL, ecran, &barre3);
    SDL_BlitSurface(barreHorizontale, NULL, ecran, &barre4);

    SDL_FreeSurface(barreHorizontale);
    SDL_FreeSurface(barreVerticale);

}

void afficherTableau(int terrain [3] [3], SDL_Surface *ecran)
{
    int i = 0, j = 0;
    SDL_Surface *croix = IMG_Load("croix.png");
    SDL_Surface *ronds = IMG_Load("ronds.png");
    SDL_Surface *quitToMenu = IMG_Load("quitToMenu.png");


    SDL_Rect position, positionQuit;

    positionQuit.x = LARGEUR_ECRAN-(quitToMenu->w);
    positionQuit.y = 0;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, ECRAN_ROUGE2, ECRAN_VERT2, ECRAN_BLEU2));
    afficherMorpion(ecran);
    SDL_BlitSurface(quitToMenu, NULL, ecran, &positionQuit);

    int variationX = (LONGUEUR_BARRES/500)*15;
    int variationY = (LONGUEUR_BARRES/500)*20;

    for (i = 0; i<3; i++)
    {
        for (j = 0; j<3; j++)
        {
            if (terrain [i] [j] == CROIX)
            {
                position.x = LARGEUR_ECRAN/2 - LONGUEUR_BARRES/2 + i*(LONGUEUR_BARRES+EPPAISSEUR_BARRES)/3 + variationX;
                position.y = HAUTEUR_ECRAN/2 - LONGUEUR_BARRES/2 + j*(LONGUEUR_BARRES+EPPAISSEUR_BARRES)/3 + variationY;
                SDL_BlitSurface(croix, NULL, ecran, &position);
            }
            else if (terrain [i] [j] == RONDS)
            {
                position.x = LARGEUR_ECRAN/2 - LONGUEUR_BARRES/2 + i*(LONGUEUR_BARRES+EPPAISSEUR_BARRES)/3 + variationX;
                position.y = HAUTEUR_ECRAN/2 - LONGUEUR_BARRES/2 + j*(LONGUEUR_BARRES+EPPAISSEUR_BARRES)/3 + variationY;
                SDL_BlitSurface(ronds, NULL, ecran, &position);
            }
        }
    }

    SDL_Flip(ecran);

    SDL_FreeSurface(croix);
    SDL_FreeSurface(ronds);
    SDL_FreeSurface(quitToMenu);
}

void victoire(SDL_Surface *ecran, int vainqueur, int *totalQuit)
{


    SDL_Surface *ecranVictoireCroix = IMG_Load("ecranVictoireCroix.png");
    SDL_Surface *ecranVictoireRonds = IMG_Load("ecranVictoireRonds.png");
    SDL_Surface *egalite = IMG_Load("egalite.png");

    SDL_Rect positionEgalite;
    positionEgalite.x = LARGEUR_ECRAN/2 - egalite->w/2;
    positionEgalite.y = HAUTEUR_ECRAN/2- egalite->h/2;

    SDL_Rect positionCroix;
    positionCroix.x = LARGEUR_ECRAN/2 - ecranVictoireCroix->w/2;;
    positionCroix.y = HAUTEUR_ECRAN/2 - ecranVictoireCroix->h/2;;

    SDL_Rect positionRonds;
    positionRonds.x = LARGEUR_ECRAN/2 - ecranVictoireRonds->w/2;
    positionRonds.y = HAUTEUR_ECRAN/2 - ecranVictoireRonds->h/2;

    SDL_SetAlpha(ecranVictoireCroix, SDL_SRCALPHA, 128);
    SDL_SetAlpha(ecranVictoireRonds, SDL_SRCALPHA, 128);
    SDL_SetAlpha(egalite, SDL_SRCALPHA, 128);

    if (vainqueur == 1)//croix
    {
        SDL_BlitSurface(ecranVictoireCroix, NULL, ecran, &positionCroix);
    }
    if (vainqueur == 2)//ronds
    {
        SDL_BlitSurface(ecranVictoireRonds, NULL, ecran, &positionRonds);
    }
    if (vainqueur == 3)
    {
        SDL_BlitSurface(egalite, NULL, ecran, &positionEgalite);
    }
    SDL_Flip(ecran);

    SDL_Event event;
    int continuer = 1;
    while (continuer == 1)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            switch(event.button.button);
            {
                case SDL_BUTTON_LEFT:
                    continuer = 0;
                    break;
            }
            break;
        case SDL_QUIT:
            continuer = 0;
            *totalQuit = 0;
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                default:
                    continuer = 1;
                    break;
            }
            break;
        default:
            break;
        }
    }
    SDL_FreeSurface(ecranVictoireCroix);
    SDL_FreeSurface(ecranVictoireRonds);
    SDL_FreeSurface(egalite);
}

int gagne(int terrain[3] [3], int *gagnant)
{
    int retour = 0;
    if (terrain[0] [0] != 0)
    {
        if ((terrain[0] [0] == terrain[0] [1] && terrain[0] [0] == terrain[0] [2])//ligne haut
            || (terrain[0] [0] == terrain[1] [0] && terrain[0] [0] == terrain[2] [0]))//colonne gauche
        {
            retour = terrain[0] [0];
            *gagnant = terrain [0] [0];
        }
    }
    if (terrain [2] [2] != 0)
    {
        if ((terrain[2] [2] == terrain[2] [1] && terrain[2] [2] == terrain[2] [0])//colonne gauche
            || (terrain[2] [2] == terrain[1] [2] && terrain[2] [2] == terrain[0] [2]))//ligne bas
        {
            retour = terrain [2] [2];
            *gagnant = retour;
        }
    }
    if (terrain [1] [1] != 0)
    {
        if ((terrain[1] [1] == terrain[0] [0] && terrain[1] [1] == terrain[2] [2])//diagonale
            ||(terrain[1] [1] == terrain[2] [0] && terrain[1] [1] == terrain[0] [2])//diagonale
            ||(terrain[1] [1] == terrain[1] [0] && terrain[1] [1] == terrain[1] [2])//colonne mileu
            ||(terrain[1] [1] == terrain[0] [1] && terrain[1] [1] == terrain[2] [1]))//ligne milieu
        {
            retour = terrain[1] [1];
            *gagnant = retour;
        }
    }

    int egalite = 0;
    int i = 0, j = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (terrain[i] [j] != 0)
            {
                egalite++;
            }
        }
    }

    if (egalite == 9 && retour == 0)//si egalite
    {
        *gagnant = 3;
    }
    return retour;
}
