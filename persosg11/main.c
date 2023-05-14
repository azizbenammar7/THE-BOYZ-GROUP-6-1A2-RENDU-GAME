#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include<string.h>
#include <time.h>
#include "perso.h"
#include "utilitaire.h"


int main()
{
	int hauteur_fenetre = 600,a=1,done=1,vi=1,sc=1,dt=0,
        	largeur_fenetre = 800;
int continuer,g;
//SDL_Rect b;
int hover1 = 1;
    int hover2 = 1;
    int hover3 = 1;
	int presses=5;
int Mode = 0;
    int run=1;
    
    int j;
    int volume = 128;
    int niv_volume = 1;
    Buttons B;
    text t;
    Music M;
    Background Main;
	
/*SDL_Surface *backgm;
SDL_Rect backgm_pos;
Time temps;
	Time tempsenig;
	map m;*/


/*b.x=0;
b.y=0;
b.w=largeur_fenetre;
b.h=hauteur_fenetre;
backgm = IMG_Load("Background2.png");
	backgm_pos.x = 0;
	backgm_pos.y = 0;*/

int sautt;
	SDL_Event event;
TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
do{
	
	printf("donner le mode de jouer  : \n 1 ->  1 joueur || 2 -> 2 joueurs ");
	scanf("%d",&g);}while(g!=1 && g!=2);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	SDL_Surface *screen;
 intro (&screen);
	 if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("unable to initialize SDL: %s\n",SDL_GetError());
        return 1;
    }
 	screen=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if(screen==NULL)
    {
        printf("unable to set video mode:%s\n",SDL_GetError());
        return 1;
    }
  
	SDL_WM_SetCaption("JEUX", NULL); 

 	/*SDL_Surface *backg;
	SDL_Rect backg_pos;
	backg = IMG_Load("Background2.png");
	backg_pos.x = 0;
	backg_pos.y = 0;*/
enemie e;
   


initMus(&M, &volume);
   
    initButMain(&B);
    
    initBackMain(&Main);
    initText(&t);

 /*Personne p2;
	Personne p;
initennemi(&e);
	
	initPerso(&p2);
	initPerso(&p);
inittemps(&temps);
	inittempsenig(&tempsenig);
	initialiser_map (&m,screen) ;*/
	 while(done)
    {  
for (j = 0; j < 2; j++)
            {
                AfficherMain(Main, screen, j);
                displayText(t, screen);
                AfficherBut1(B, screen, hover1,presses);
                AfficherBut2(B, screen, hover2,presses);
                AfficherBut3(B, screen, hover3,presses);
                SDL_Flip(screen);
                hover1 = 1;
                hover2 = 1;
                hover3 = 1;
	
/* int coll=collisionbb(e.pos,p.position);
b.x=p.position.x-320;
b.y=p.position.y-1000;
if(b.x < 0)
    b.x=0;
    if(b.y < 0)
    b.y=0; 
collision(backgm,&p);
		update_time(&temps); 
perso_map(&m,&p);
	SDL_BlitSurface(backg,&b,screen,&backg_pos);
displaytime(temps,screen);

		affiche_map(m,screen);
	
		//afficherPerso (p,screen,b);
if((p.position.x>150)&&(p.position.x<800))
{
afficherennemi(&e, screen);
deplacerIA(&e, p.position);
 animerennemi(&e);}*/
    	SDL_PollEvent(&event);

     switch(event.type)

     {  
     	case SDL_QUIT: 
		done=0;
		break;
	case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {  
		/*case SDLK_v: 
               	dt=0;
               	deplacerPerso(&p ,screen,dt);*/
		break;
case SDLK_j:
                        Mix_PlayChannel(-1, M.bref, 0);
                        NewGame(screen ,&Mode,&g);
                        break;
case SDLK_s:
                        Mix_PlayChannel(-1, M.bref, 0);
                        Settings(screen, &Mode, &niv_volume, &volume);
                        break;
case SDLK_UP:
                        presses = 
presses % 3 - 1;
                        if (presses == 0)
                            presses = 3;
                        if (presses == -1)
                            presses = 2;
                        SDL_Delay(100);
                        break;

                    case SDLK_DOWN:
                        presses = presses % 3 + 1;
                        SDL_Delay(100);
                        break;

                    case SDLK_SPACE:
                        switch (presses)
                        {
                        case 1:
screen=SDL_SetVideoMode(2000,640,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if(screen==NULL)
    {
        printf("unable to set video mode:%s\n",SDL_GetError());
        return 1;
    }
                            NewGame(screen, &Mode,&g);
                            break;
                        case 2:
                            Settings(screen, &Mode, &niv_volume, &volume);
                            break;
}


		
		/*case SDLK_d: 
               	dt=1;
                sautt=1;
               	deplacerPerso(&p ,screen,dt);

		scrolling(&b, 0, 10);

		break;
			
		case SDLK_q: 
               	dt=2;
                sautt=2;
               	deplacerPerso(&p ,screen,dt);

		scrolling(&b, 1, 10);

		break;
		case SDLK_SPACE:
			dt=3;
               	deplacerPerso(&p ,screen,dt);*/

	
			
		
 case SDL_MOUSEMOTION://win bich n7arek el souris
                    if (event.motion.x > 350 && event.motion.x < 500 && event.motion.y > 250 && event.motion.y < 291)
                    {
                        hover1 = 0;
presses=5;
                        
                        Mix_FadeInChannel(-1, M.bref, 0,0);
                    }
                    else if (event.motion.x > 350 && event.motion.x < 500 && event.motion.y > 350 && event.motion.y < 391)
                    {
                        hover2 = 0;
presses=5;
                        
                        Mix_FadeInChannel(-1, M.bref, 0, 0);
                    }
                    else if (event.motion.x > 350 && event.motion.x < 500 && event.motion.y > 450 && event.motion.y < 491)
                    {
                        hover3 = 0;
presses=5;
                        
                        Mix_FadeInChannel(-1, M.bref, 0, 0);
                    }
                    break;

                case SDL_MOUSEBUTTONUP://bech nenzel 3al souris
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (event.button.x > 350 && event.button.x < 500 && event.button.y > 250 && event.button.y < 291)
                        {
                            NewGame(screen, &Mode,&g);
                        }
                        else if (event.button.x > 350 && event.button.x < 500 && event.button.y > 350 && event.button.y < 391)
                        {
                            Settings(screen, &Mode, &niv_volume, &volume);
                        }
                        else if (event.button.x > 350 && event.button.x < 500 && event.button.y > 450 && event.button.y < 491)
                        {
                            continuer = 0;
                            break;
                        }
                    }
                    break;
		
		/*case SDLK_UP:
			vitesseUP(&p);
		break;*/
		
		/*case SDLK_DOWN:
			vitesseDOWN(&p);
		break;*/
               
		case SDLK_ESCAPE: 
              		done=0;
		break; 
/*case SDLK_m: 
               	dt=1;
                sautt=1;
               	deplacerPerso(&p2 ,screen,dt);
		break;
			
		case SDLK_k: 
               	dt=2;
                sautt=2;
               	deplacerPerso(&p2 ,screen,dt);
		break;
		case SDLK_o:
			dt=3;
               	deplacerPerso(&p2 ,screen,dt);
			
		break;
		
		case SDLK_u:
			vitesseUP(&p2);
		break;
		
		case SDLK_i:
			vitesseDOWN(&p2);
		break;*/
		
               

                
            }
      
     
}



           /*if (g==1){
		afficherPerso (p,screen,b);
           if(sautt==1)
          {
		saut(&p);
          }
         else if(sautt==2)
               {
              sautgauche(&p);
              }
	}
if(g==2){
		afficherPerso (p,screen,b);
		afficherPerso (p2,screen,b);
           if(sautt==1)
         {
		saut(&p);
		saut(&p2);
         }
       else if(sautt==2)
      {
                     sautgauche(&p);
                                   sautgauche(&p2);
      }
	}
*/
	/*if(p.position.x==100){
afficherenigme(e,screen);
}*/

/*while(done){
		update_timeenig(&tempsenig);
afficherenigme(e,screen);
		
		displaytime(tempsenig,screen);
		
		if(tempsenig.ss==temps.ss+15)
		{
                  done=0;
		}}

}*/

	}	
	
     	SDL_Flip(screen);
    }
freeBackMain(Main);
    freeButMain(B);
    freeText(t);
    freeMusic(M);
    TTF_CloseFont(t.font);
	//freeTexttime(temps.temps);	
	//SDL_FreeSurface(backg);
	SDL_Quit();
SDL_Quit();

    return 0;
}










