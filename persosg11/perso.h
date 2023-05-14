#ifndef perso_H_INCLUDED  
#define perso_H_INCLUDED

#include <stdio.h>  
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "utilitaire.h"
#include <SDL/SDL_mixer.h>
#include <time.h>  
#include <math.h>
#include <SDL/SDL_ttf.h>

#include "utilitaire.h"





typedef struct { 

	SDL_Surface *image;
	SDL_Rect position;
	SDL_Rect frame;
	
	int curframe; 
	Text vie;
	int direction; 
	Text score; 
	double acceleration; 
	double decelere;	 
	double vitesse;   
	double v_x;
	double v_grav ;
	double v_saut ;
	double v_y ; 
	
}Personne;



typedef struct
{
	SDL_Surface *map ;
	SDL_Rect pos_map;
	SDL_Surface *mini_perso;
	SDL_Rect perso_pos_map;

}map;
/*typedef struct  {
    SDL_Surface* textSurface;
    SDL_Rect positionText;
    char txt[20];
    SDL_Color couleurTxt;
    TTF_Font* police;
}Text;
*/

typedef struct
{
    int tempsdebut;
    int mm;
    int ss;
    Text temps;

} Time;
typedef struct enemie
{
    SDL_Surface *spritesheet;  // Sprite sheet de l'ennemi
    SDL_Rect pos;    // Position et frame de l'ennemi
    SDL_Rect frame;    
    int direction;            // Direction de l'ennemi
    SDL_Rect posmin,posmax;   // Positions maximale et minimale de l'ennemi
    int curframe;                // Frame actuelle de l'ennemi
} enemie;




void initPerso(Personne *p);  
void initPerso2(Personne *p);

void afficherPerso(Personne p,SDL_Surface *screen,SDL_Rect camera_rect);
void deplacerPerso(Personne *p ,SDL_Surface *screen,int dt);
void animerPerso(Personne *p);
void saut(Personne *p);
void vitesseUP(Personne *p);
void vitesseDOWN(Personne *p);
void sautgauche(Personne *p);
void scrolling(SDL_Rect *b, int direction, int pas);
void initialiser_map (map *m,SDL_Surface *screen) ;
	void perso_map(map *m,Personne *p);
	void affiche_map(map m, SDL_Surface *screen);
void inittemps(Time *t);// initialisaton lel temps l koulo
void inittempsenig(Time *t);
void Timer(int *tempsdebut);// tehseb l temps
int initTexttime(Text* T);//initialisation du text  khw eli besh nektbo bih
int initTexttimeenig(Text* T);
int loadFonttime(Text* T, char* angelina);//tloadi l font mtaa l text
void update_time(Time* T);//mise a jour du temps
void update_timeenig(Time* T);
void displaytime(Time T,SDL_Surface *screen);//afficher le temps aal back
void freeTexttime(Text T);//besh ykoun fema optimisation
SDL_Color getpixel(SDL_Surface *psurface,int x,int y);
int collisionparfaite(SDL_Surface *psurface,Personne perso);
void collision(SDL_Surface *psurface,Personne *perso);
void intro (SDL_Surface **ecran);
void initennemi(enemie*e,int y,int x,int z);
void afficherennemi(enemie *e, SDL_Surface * screen,SDL_Surface * backg);
void animerennemi( enemie * e)  ;
void deplacer( enemie * e)  ;
int collisionbb(SDL_Rect E, SDL_Rect p);
void deplacerIA(enemie *E, SDL_Rect posPerso1);
void deplacerIA_2players(enemie *E, SDL_Rect posPerso1, SDL_Rect posPerso2);




#endif
