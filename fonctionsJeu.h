#ifndef DEF_FONCTIONSJEU
#define DEF_FONCTIONSJEU

void afficherTableau(int terrain [3] [3], SDL_Surface *ecran);
void afficherMorpion(SDL_Surface *ecran);
int ouEstClic (int x, int y, int *caseX, int *caseY);
int tour(int terrain[3] [3]);
int gagne(int terrain[3] [3], int *gagnant);
void victoire(SDL_Surface *ecran, int vainqueur, int *totalQuit);





#endif // DEF_MENU

