#include "perso.h"
#include "utilitaire.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

void initPerso(Personne *p){

int vi,sc;
vi=initTextvie(&p->vie);
sc=initTextscore(&p->score);

(*p).image=IMG_Load("perso1.png");  

p->position.x=0;
p->position.y=450;
p->position.w=100;
p->position.h=100;

p->frame.w=180; 
p->frame.h=218;
p->frame.x=0;
p->frame.y=0;

p->curframe=3;

p->direction=0;
p->v_x = 5;
p->v_grav = 0.3;
p->v_saut = -6.5;
p->v_y = p->v_saut;

p->acceleration=5;
p->vitesse=0;

}




void afficherPerso (Personne p,SDL_Surface *screen,SDL_Rect camera_rect){
    SDL_Rect drawingRect= {p.position.x-camera_rect.x,p.position.y-camera_rect.y,p.position.w,p.position.h};
    displayvie(p.vie,screen);
    displayscore(p.score,screen);
    SDL_BlitSurface(p.image,&(p.frame),screen,&(drawingRect));
}



void deplacerPerso(Personne *p ,SDL_Surface *screen,int dt){ 
	
	
	
	if (dt==0){
		while(p->position.y<450) 
   		{ 
     			p->position.y+=3;
    		}
    		p->direction=dt;
    		animerPerso(p);
	
	}
	
	if (dt==1){
		p->position.x+=p->vitesse; 
		p->direction=dt; 
		animerPerso(p);
	
	}
   	
 	if (dt==2){
   		p->position.x-=p->vitesse;
   		p->direction=dt;
   		animerPerso(p);
	
	}
	
	if (dt==3){
		 
		p->position.y-=2; 
	 
	}
	
}


void animerPerso(Personne *p){
	if(p->direction==1)
	{
		p->frame.y=0;
		p->curframe++;
	if(p->curframe>=7)
	{
		p->curframe=3;
	}
		p->frame.x=p->curframe * 180;  

	}	
	else
		if(p->direction==2)
		{ 
			p->frame.y=218;
			p->curframe++;
		if(p->curframe>=7)
		{
			p->curframe=3;
		}
		p->frame.x=p->curframe * 180;  
  
		}
	else 
		if(p->direction==0) 
		{
			p->frame.x=0;

		}

}


void saut(Personne *p){
	
	if(p->position.y<450){
   	p->position.x += p->v_x;
   	p->position.y+= p->v_y;
   	p->v_y += p->v_grav;
   }
  	if (p->position.y> 450)
    	p->v_y = p->v_saut;
}

void sautgauche(Personne *p){
	if(p->position.y<450){
   	p->position.x -= p->v_x;
   	p->position.y+= p->v_y;
   	p->v_y += p->v_grav;
   }
  	if (p->position.y> 450)
    	p->v_y = p->v_saut;


}
void vitesseUP(Personne *p){
	 
       
         p->vitesse+=p->acceleration;
         p->position.x+=p->vitesse; 
         p->direction=1;
         if(p->vitesse>=30)
         {
          p->vitesse=30;
         }
}
void vitesseDOWN(Personne *p){
 	p->vitesse=0; 

}
void scrolling(SDL_Rect *b, int direction, int pas) {
    if (direction == 0) {
        b->x += pas;
    }
    else if (direction == 1) {
        b->x -= pas;
    }
}
SDL_Color getpixel(SDL_Surface *pSurface,int x,int y)//lezem n3dilha el masque 5tr hia fih elloun ak7el //mini
{
	SDL_Color color;
	Uint32 col=0;
	char* pPosition=(char* ) pSurface->pixels;
	pPosition+= (pSurface->pitch * y);
	pPosition+= (pSurface->format->BytesPerPixel *x);
	memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel);
	SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
	return (color);
}
int  collisionparfaite(SDL_Surface *psurface,Personne p)
{
	int tabx[7],taby[7],i;//7atit les position de x fi tableau mta3 x o hatit les position mat3 y fi tableau mta3 y o 3mlt coleur chntstih bih
	SDL_Color color1,color;//color lil test
	color1.r = 0;
	color1.g = 0;
	color1.b = 0;
	tabx[0]=p.position.x;
	tabx[1]=(p.position.x)+((p.position.w)/2);
	tabx[2]=(p.position.x+p.position.w);
	tabx[3]=p.position.x;
	tabx[4]=p.position.x;
	tabx[5]=(p.position.x)+((p.position.w)/2);
	tabx[6]=(p.position.x+p.position.w);
	tabx[7]=(p.position.x+p.position.w);
	taby[0]=p.position.y;
	taby[1]=p.position.y;
	taby[2]=p.position.y;
	taby[3]=(p.position.y)+((p.position.h)/2);
	taby[4]=(p.position.y+p.position.h);
	taby[5]=(p.position.y+p.position.h);
	taby[6]=(p.position.y+p.position.h);
	taby[7]=(p.position.y)+((p.position.h)/2);

	for(i=0;i<8;i++)
	{
	color=getpixel(psurface,tabx[i],taby[i]);//trj3lik el coleur ili inty fih
	if(color.r==color1.r && color.b==color1.b && color.g==color1.g)
	{
		return i;//trj3li indice win saret collision

	}
	}
	return 10;//maasartch collision kain raja3li 1

}

void collision(SDL_Surface *psurface,Personne *p)//il suffit saret collision scrolling leze nwkfo wktli collisionparfaite traja3 10 ya3ni mfmfch collision
{	int i;
	i=collisionparfaite(psurface,*p);

	switch (i)//wkt tsir collisision el perso idizo chwya
	{
		case 0 :p->position.y=p->position.y+20;
			break;
		case 1 :p->position.y=p->position.y+20;
			 break;
		case 2 :p->position.y=p->position.y+20;
			break;
		case 3 :p->position.x=p->position.x+20;
			break;
	        case 4 :p->position.y=p->position.y-20;
			break;
		case 5 :p->position.y=p->position.y-50;
			break;
		case 6 :p->position.y=p->position.y-30;
			break;
		case 7 :p->position.x=p->position.x-20;
			break;


	}
}
void Timer(int *tempsdebut)//t5rjli kdch 3ndi min seconde mili bdit nl3eb
{

   if( SDL_GetTicks() - *tempsdebut >= 1000 )//kain el wkt b3ed ili bdit fih -wakt bdit fih 3mlt seconde rw tempsdebut hot fih wakt el jdid
    {
        *tempsdebut = SDL_GetTicks() ;


    }

}

void inittemps(Time *t)
{   int test;
	t->tempsdebut=SDL_GetTicks();//thseblk kdch el wakt ili bdit fih execution
	t->mm=0;
	t->ss=0;
	test=initTexttime(&t->temps);
}
void inittempsenig(Time *t)
{   int test;
	t->tempsdebut=0;
	t->mm=0;
	t->ss=0;
	test=initTexttimeenig(&t->temps);
}
int initTexttime(Text* T)
{ int testload;
    T->couleurTxt.r = 0;
    T->couleurTxt.g = 0;
    T->couleurTxt.b = 0;

    strcpy(T->txt,"");
    T->positionText.x = 850;
    T->positionText.y = 50;
    testload=loadFonttime(T,"angelina.TTF");//fct 3mltha bich tlodili el font trj3li zero kain loadfont sar mrigl
    T->textSurface=NULL;
    return testload;
}
int initTexttimeenig(Text* T)
{ int testload;
    T->couleurTxt.r = 255;
    T->couleurTxt.g = 255;
    T->couleurTxt.b = 255;

    strcpy(T->txt, "");
    T->positionText.x = 0;
    T->positionText.y = 0;
    testload=loadFonttime(T,"angelina.TTF");
    T->textSurface=NULL;
    return testload;
}
int loadFonttime(Text* T, char* path)
{
    if(TTF_Init() == -1) {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return -1;
    }
    T->police= TTF_OpenFont(path,60);//pathn hoa esm l font o 60 l taile
    if (T->police == NULL) {
        printf("Unable to load Font: %s\n", SDL_GetError());
        return (-1);
    }
    return (0);
}

void update_time(Time* T)
{   int ts;
    Timer(&T->tempsdebut);//raj3tli kdch min milliseconde
    ts=T->tempsdebut/1000;//rdithom b seconde
    T->mm=ts/60;//kdch min min
    T->ss=ts % 60;//kdch min seconde ts mode 60
    if(T->mm<10&&T->ss<10)
       sprintf(T->temps.txt,"*** time :0%d:0%d  ***",T->mm,T->ss);
    else if(T->mm<10&&T->ss>10)
        sprintf(T->temps.txt,"*** time :0%d:%d  ***",T->mm,T->ss);
    else if(T->mm>10&&T->ss<10)
          sprintf(T->temps.txt,"*** time :%d:0%d  ***",T->mm,T->ss);//s y3ni chnktb fi variable chaine
    else
         sprintf(T->temps.txt,"*** time :%d:%d  ***",T->mm,T->ss);

    T->temps.textSurface=TTF_RenderText_Solid(T->temps.police,T->temps.txt,T->temps.couleurTxt);//ttfrender tekho l police o txt o couleur taa l text eli besh taficchiih
}
void update_timeenig(Time* T)
{   int ts;

    Timer(&T->tempsdebut);
    ts=T->tempsdebut/1000;
    T->mm=ts/ 60;
    T->ss=ts % 60;
    if(T->mm<10&&T->ss<10)//idhkain minute et seconde asgher min 10
       sprintf(T->temps.txt,"*** time :0%d:0%d  ***",T->mm,T->ss);
    else if(T->mm<10&&T->ss>10)
        sprintf(T->temps.txt,"*** time :0%d:%d  ***",T->mm,T->ss);
    else if(T->mm>10&&T->ss<10)
          sprintf(T->temps.txt,"*** time :%d:0%d  ***",T->mm,T->ss);
    else
         sprintf(T->temps.txt,"*** time :%d:%d  ***",T->mm,T->ss);
    T->temps.textSurface=TTF_RenderText_Solid(T->temps.police,T->temps.txt,T->temps.couleurTxt);//ttfrender tekho l police o txt o couleur taa l text eli besh taficchiih
}
void displaytime(Time T,SDL_Surface *screen)
{


     SDL_BlitSurface(T.temps.textSurface,NULL,screen,&(T.temps.positionText));

}

void freeTexttime(Text T)
{
    TTF_CloseFont(T.police);
    TTF_Quit();
}
void initialiser_map (map *m,SDL_Surface *screen)
{
	m->map=IMG_Load("ppppp.png");
	m->pos_map.x = 0;// equiv (*m).pos_map.x=1000;
	m->pos_map.y = 120;
	m->mini_perso=SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF,10,10,32,0,0,0,0);//hedhy taaml mouraba fil mini map ali houwa l perso mlwn mich bich nlskfih tswira o cht5dmli sur 32 bit 3al qualite ta image o sout
	SDL_FillRect(m->mini_perso,NULL,SDL_MapRGB(screen->format,0,255,0));// lel couleur
	m->perso_pos_map.x=0;
	m->perso_pos_map.y=0;

}


void perso_map(map *m,Personne *p)
{
	m->perso_pos_map.x=p->position.x/10+m->pos_map.x;//9otlo kif perso ikdem b 5otha el perso ta mini map lezem 1/10 5otwa ili 3mlha fil 7kika ikadem o m->pos_map.x bich ijibnifil minimap bidhbt
	m->perso_pos_map.y=p->position.y/10+10+m->pos_map.y;// besh l position ta" l mini perso iji kad kad maa l perso lekbir 3al axe y 5tr perso taille ta3o y akber dima ybda 3ndi probleme k3de nzid fi y wa7di bich tjini kadkad
}



void affiche_map(map m , SDL_Surface *screen)
{
	SDL_BlitSurface(m.map, NULL, screen,&m.pos_map);
	SDL_BlitSurface(m.mini_perso, NULL, screen,&m.perso_pos_map);
}

void initText(text *t)//n3mr les donnes du text 
{
    t->position.x = 410;
    t->position.y = 35;
    t->textColor.r = 200;
    t->textColor.g = 150;
    t->textColor.b = 40;
    t->font = TTF_OpenFont("pol.ttf", 50);
}
void freeText(text A)
{
    SDL_FreeSurface(A.surfaceTexte);
}
void displayText(text t, SDL_Surface *screen)
{
    t.surfaceTexte = TTF_RenderText_Solid(t.font, "Welcome", t.textColor);//fi west el variable t.surfacetext ctji el klma bil font o taille o colleur
    SDL_BlitSurface(t.surfaceTexte, NULL, screen, &t.position);//chnhot el kelma fil screen fil position ili 3amartha
}
void initMus(Music *M, int *volume)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_VolumeMusic(*volume);//fct teb3 sdl cht5dmli sout b volume mo3ayen
    M->music = Mix_LoadMUS("son.mp3");
    Mix_PlayMusic(M->music, -1);
    M->bref = Mix_LoadWAV("click.wav");
}

void freeMusic(Music M)
{
    Mix_FreeMusic(M.music);
    Mix_FreeChunk(M.bref);
    Mix_CloseAudio();
    Mix_Quit();
}

void volumeUp(int *niv_volume, int *volume)//
{
    if (*niv_volume == 5)
    {
        *niv_volume = 4;
        Mix_VolumeMusic(*volume * 2);
        *volume = *volume * 2;
    }
    else if (*niv_volume == 4)
    {
        *niv_volume = 3;
        Mix_VolumeMusic(*volume * 2);
        *volume = *volume * 2;
    }
    else if (*niv_volume == 3)
    {
*niv_volume = 2;
        Mix_VolumeMusic(*volume * 2);
        *volume = *volume * 2;
    }
    else if (*niv_volume == 2)
    {
        *niv_volume = 1;
        Mix_VolumeMusic(128);
        *volume = 128;
    }
}
//idhakain niv_volume=1 o nzid n3ali mysir chy o idhakain ninzel dwn niv_volume iwli 2 o 

void volumeDown(int *niv_volume, int *volume)//
{
    if (*niv_volume == 1)
    {
        *niv_volume = 2;
        Mix_VolumeMusic(*volume / 2);
        *volume = *volume / 2;
    }
    else if (*niv_volume == 2)
    {
        *niv_volume = 3;
        Mix_VolumeMusic(*volume / 2);
        *volume = *volume / 2;
    }
    else if (*niv_volume == 3)
    {
        *niv_volume = 4;
        Mix_VolumeMusic(*volume / 2);
        *volume = *volume / 2;
    }
    else if (*niv_volume == 4)
    {
        *niv_volume = 5;
        Mix_VolumeMusic(0);
        *volume = 0;
    }
}
/*void Newback(SDL_Surface *screen,int *run)//bich kif nenzel 3ala bouton newgame n3aytlil fct hedi chtjibli background ekher
{
    Background Newback;
    SDL_Event event;
    int continuer = 1;
    
    initBack(&Newback);
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            
               
                
            
             case SDLK_SPACE:
               *run=0;
continuer=0;
}
            break;
        } 
        Afficherback(Newback,screen);
        SDL_Flip(screen);//refrech
    }
    freeBack(Newback);
}
*/

void NewGame(SDL_Surface *screen, int *Mode,int *g)//bich kif nenzel 3ala bouton newgame n3aytlil fct hedi chtjibli background ekher
{

   tic t; int coup=1;//////////////////////////////
SDL_Surface * ecran,*screen1;///////////////////////////////
TTF_Init();////////////////////////////////////////
    int cont=1;////////////////////////
SDL_Init(SDL_INIT_VIDEO);  /////////////////////// 
enigme  enigme;
enigme.num_enigme=-1;
	int s,r=0,run =1,running=1,alea;

int i3;



 Background NGame;
Personne p2;
int hauteur_fenetre = 640,largeur_fenetre = 2000;

	Personne p;
SDL_Rect b;
enemie e;
enemie e1;
enemie e2;
enemie e3;
Time temps;
	Time tempsenig;
SDL_Surface *backgm;
SDL_Rect backgm_pos;
	map m;
    SDL_Event event;
    int continuer = 1,dt=0;
/*do{
	
	printf("donner le mode de jouer  : \n 1 ->  1 joueur || 2 -> 2 joueurs ");
	scanf("%d",&g);}while(g!=1 && g!=2);*/
b.x=0;
b.y=0;
b.w=largeur_fenetre;
b.h=hauteur_fenetre;
backgm = IMG_Load("backgroundMasque.png");
	backgm_pos.x = 0;
	backgm_pos.y = 0;
int sautt;
SDL_Surface *backg;
	SDL_Rect backg_pos;
	backg = IMG_Load("newgame.png");
	backg_pos.x = 0;
	backg_pos.y = 0;
       
    initennemi(&e,0,500,500);
    initennemi(&e1,500,750,1000);
    initennemi(&e2,1000,1250,1500);
    initennemi(&e3,1500,1750,2000);
	
	initPerso(&p2);
	initPerso(&p);
inittemps(&temps);

	inittempsenig(&tempsenig);
	initialiser_map (&m,screen) ;
//controller configuration
    int arduino = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (arduino == -1)
    {
        perror("Unable to open Arduino serial port");
        
    }

    struct termios arduino_options;
    tcgetattr(arduino, &arduino_options);

    cfsetispeed(&arduino_options, B115200);
    cfsetospeed(&arduino_options, B115200);

    arduino_options.c_cflag |= (CLOCAL | CREAD);
    arduino_options.c_cflag &= ~PARENB;
    arduino_options.c_cflag &= ~CSTOPB;
    arduino_options.c_cflag &= ~CSIZE;
    arduino_options.c_cflag |= CS8;

    tcsetattr(arduino, TCSANOW, &arduino_options);

    char buf[256];
    ssize_t n;
    while (continuer)
    {


int coll=collisionbb(e.pos,p.position);
b.x=p.position.x-320;
b.y=p.position.y-1000;
//////////////////////////////////////////////////////////////////////////////////////////////5edemt nassim


   if(p.position.x>8100)
{
    ecran=SDL_SetVideoMode(552,541,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    initialisation(&t);
    int a,b1;
    while(cont)
    {//

affichage(t,ecran); 
SDL_Flip(ecran);
if( t.tour<9 &&atilganer(t.tabsuivi)==0)
{//
if((t.tour)%2==0)//tour du PC
            {//
 calcul_coup(t.tabsuivi);
printf("\nhellooo before switch\n");
 t.tour++;
}///
        else
       {//
        SDL_WaitEvent(&event);
        switch(event.type)
        {//
        case SDL_QUIT:
            cont=0;
            break;
        case SDL_MOUSEBUTTONUP:
 if (event.button.button == SDL_BUTTON_LEFT)
                {
            a=event.button.x/184;
            b1=event.button.y/180;
            coup=3*b1+a;
            t.tour++;
    t.tabsuivi[coup]=-1;
          }
            break;
        }///


}///

}///
else
{ 
 Resultat(t,ecran);
 SDL_Delay(2000);
 cont=0;   
printf("%d", t.tour);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////5edmet aziz enigme
 screen1=SDL_SetVideoMode(1280,853,32 ,SDL_HWSURFACE  |  SDL_DOUBLEBUF  );

if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
{
printf("%s",Mix_GetError()); 
}
Mix_Music *music ; 
music = Mix_LoadMUS("sound.mp3");
Mix_PlayMusic(music,-1); 
	 
	 while (run)
	 {
         int prevt=SDL_GetTicks();
             init_enigme(&enigme,"enigme.txt");
             afficherEnigme(enigme,screen); 

	     SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                run = 0;
	        break ;
        }

        int time=0;
       	r=0;
   do{     	
        time=(SDL_GetTicks()-prevt)/1000;	// igeneri mn 0 l 30      
        SDL_BlitSurface(enigme.anim.spritesheet,&enigme.anim.clips[enigme.anim.cliploaded],screen,&enigme.anim.pos); //mtaa l wehed mtaa l wakt
        SDL_Flip(screen);
        printf("%d\n",time);

switch (time)
        {
    case 5:
        animer(&enigme);
    break;

    case 10:
        animer(&enigme);
    break;

    case 15:
        animer(&enigme);
    break;

    case 20:
        animer(&enigme);
    break;

    case 25:
        animer(&enigme);
    break;

    case 30:
        animer(&enigme);
    break;
        }
    r=resolution (&running,&run); 


   } while(time<=30 && (r>3 || r<1) && running!=0);
			
      while(running) 
      {
          afficher_resultat(screen,enigme.reponsevrai,r,&enigme); 
          
			  SDL_WaitEvent(&event);
        switch(event.type)
            {
			case SDL_QUIT :
                        running =0 ;
                             run=0;
                          
			
					  break ;

            case SDL_KEYDOWN :
						    
                switch( event.key.keysym.sym )
                {
	             case  SDLK_ESCAPE: 
		        running= 0 ;
                              run=0;
                              SaveScreenMode(screen, Mode);
                               SDL_Flip(screen);
			            break ;

                        case SDLK_SPACE:
                          running=0;
                            run=0;
                        break;
			  
			   
			    }
		break ;
            }
				
		}
 }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////fin aziz



continuer=0;
SaveScreenMode(screen, Mode);
}
}

     
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////fin nassim




	
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
/*if((p.position.x>150)&&(p.position.x<800))
{*/
afficherennemi(&e, screen,backg);
deplacerIA(&e, p.position);
 animerennemi(&e);
afficherennemi(&e1, screen,backg);
deplacerIA(&e1, p.position);
 animerennemi(&e1);
afficherennemi(&e2,screen,backg);
deplacerIA(&e2, p.position);
 animerennemi(&e2);
afficherennemi(&e3,screen, backg);
deplacerIA(&e3, p.position);
 animerennemi(&e3);
//}
if (*g==1){
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
if(*g==2){
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
//read the charcter from arduino and print it
    	 
    n = read(arduino, buf, sizeof(buf));
    if (n > 0) {
        // Null-terminate the string
        buf[n] = '\0';
        
        // Check the contents of buf to determine which action to take
        if (strcmp(buf, "l") == 0) {
                           	dt=2;
                sautt=2;
               	deplacerPerso(&p ,screen,dt);

		scrolling(&b, 1, 10);
        } else if (strcmp(buf, "r") == 0) {
                           	dt=1;
                sautt=1;
               	deplacerPerso(&p ,screen,dt);

		scrolling(&b, 0, 10);
        } else if (strcmp(buf, "u") == 0) {
            			dt=3;
               	deplacerPerso(&p ,screen,dt);
        } 
        }
        
       
        ///////////////////////////////////////////
        SDL_PollEvent(&event);
        switch (event.type)
        {
//AfficherNGame(NGame, screen);
        case SDL_QUIT:
            continuer = 0;
SaveScreenMode(screen, Mode);
            
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
 
		case SDLK_s: 
               	dt=0;
               	deplacerPerso(&p ,screen,dt);
		break;

		
		case SDLK_d: 
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
               	deplacerPerso(&p ,screen,dt);

	
			
		break;
case SDLK_k:
                dt=0;
                deplacerPerso(&p2,screen,dt);
                break;

            case SDLK_l:
                dt=1;
                sautt=1;
                deplacerPerso(&p2,screen,dt);
                break;

            case SDLK_j:
                dt=2;
                sautt=2;
                deplacerPerso(&p2,screen,dt);
                break;
            case SDLK_i:
                dt=3;
                deplacerPerso(&p2,screen,dt);


                break;
		
		case SDLK_UP:
			vitesseUP(&p);
vitesseUP(&p2);
		break;
		
		case SDLK_DOWN:
			vitesseDOWN(&p);
vitesseDOWN(&p2);
		break;
               
		case SDLK_ESCAPE: 
              		continuer=0;
SaveScreenMode(screen, Mode);
		break; 
		
               

                
            }
break;
      
     } ;



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


		
	
     	SDL_Flip(screen);
    }
    freeBackNGame(NGame);
freeTexttime(temps.temps);
liberationmemoire(t);///////////////////////////////////////////nassim

}

void Settings(SDL_Surface *screen,int *Mode, int *niv_volume, int *volume)
{

    
    SDL_Event event;
    Buttons B;
    Background Set;
    int continuer = 2;
    
    
    initBackSet(&Set);
    initButSet(&B);
   
   
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
 SaveScreenMode1(screen, Mode);
            
            break;

        case SDL_KEYDOWN://chnst3ml clavier
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                SDL_BlitSurface(B.Quit, NULL, screen, &B.positionQuit);
                SDL_Flip(screen);
 SaveScreenMode1(screen, Mode);
                
                break;
            case SDLK_LEFT:
                volumeDown(niv_volume, volume);
                SDL_BlitSurface(B.Moins, NULL, screen, &B.positionMoins);
                SDL_Flip(screen);
                break;
            case SDLK_RIGHT:
                volumeUp(niv_volume, volume);
                SDL_BlitSurface(B.Plus, NULL, screen, &B.positionPlus);
                SDL_Flip(screen);
                break;
case SDLK_f:
                SetFull(screen, Mode);
 SDL_Flip(screen);

                break;
            
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > 260 && event.button.x < 380 && event.button.y > 210 && event.button.y < 330)
                {
                    volumeDown(niv_volume, volume);
                    SDL_BlitSurface(B.Moins, NULL, screen, &B.positionMoins);
                    SDL_Flip(screen);
                }
                else if (event.button.x > 610 && event.button.x < 730 && event.button.y > 210 && event.button.y < 330)
                {
                    volumeUp(niv_volume, volume);
                    SDL_BlitSurface(B.Plus, NULL, screen, &B.positionPlus);
                    SDL_Flip(screen);
                }
else if (event.button.x > 410 && event.button.x < 494 && event.button.y > 343 && event.button.y < 431)
                {
                    SetFull(screen, Mode);
 SDL_Flip(screen);
                }
                
                
                else if (event.button.x > 410 && event.button.x < 531 && event.button.y > 430 && event.button.y < 549)
                {
                    SDL_BlitSurface(B.Quit, NULL, screen, &B.positionQuit);
                    //ba3ed sdlblitsurface n3ml flip

                    
                    continuer = 0;
SDL_BlitSurface(B.Quit, NULL, screen, &B.positionQuit);
 SDL_Flip(screen);
SaveScreenMode(screen, Mode);
 
                    break;
                }
            }
            break;
        }
        AfficherSet(Set, screen);
        AfficherButOption(B, screen);
        AfficherButMoins(B, screen);
        AfficherButPlus(B, screen);
        AfficherButScreen(B, screen, Mode);
AfficherButQuit( B, screen);
        SDL_Flip(screen);
    }
    freeBackSet(Set);
    freeButSet(B);
}
void SaveScreenMode(SDL_Surface *screen, int *Mode)
{
    if (*Mode == 0)
    {
       
        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);//mode normal
 SDL_Flip(screen);
    }
    else
    {
        
        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_FULLSCREEN);//mode fullscren
 SDL_Flip(screen);
    }
    SDL_WM_SetCaption("Game Menu", NULL);
}
void SaveScreenMode1(SDL_Surface *screen, int *Mode)
{
    if (*Mode == 0)
    {
       
        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);//mode normal
 SDL_Flip(screen);
    }
    else
    {
        
        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_FULLSCREEN);//mode fullscren
 SDL_Flip(screen);
    }
    SDL_WM_SetCaption("Game Menu", NULL);
}
void SetFull(SDL_Surface *screen, int *Mode)
{
    *Mode = 1;
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_FULLSCREEN);
}
void SetNorm(SDL_Surface *screen, int *Mode)
{
    *Mode = 0;
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //SDL_DOUBLEBUF 
}
void toggleFullscreen(SDL_Surface* screen,int fullscreen)
{
    fullscreen = !fullscreen;
    SDL_WM_ToggleFullScreen(screen);
}

void initBackMain(Background *Back)
{
    Back->back[0] = IMG_Load("background.png");
    Back->back[1] = IMG_Load("Background2.png");
    Back->positionBack.x = 0;
    Back->positionBack.y = 0;
    Back->positionBack.w = SCREEN_W;
    Back->positionBack.h = SCREEN_H;
}

void initBackSet(Background *Back)
{
    Back->back[3] = IMG_Load("Settings.png");
    Back->positionBack.x = 0;
    Back->positionBack.y = 0;
    Back->positionBack.w = SCREEN_W ;
    Back->positionBack.h = SCREEN_H;
}
/*void initBack(Background *Back)
{
    Back->back[4] = IMG_Load("ppppp.png");
    Back->positionBack.x = 0;
    Back->positionBack.y = 0;
    Back->positionBack.w = SCREEN_W ;
    Back->positionBack.h = SCREEN_H;
}*/
void Afficherback(Background Main, SDL_Surface *screen)
{
    SDL_BlitSurface(Main.back[4], NULL, screen, &Main.positionBack);
}

void AfficherMain(Background Main, SDL_Surface *screen, int i)
{
    SDL_BlitSurface(Main.back[i], NULL, screen, &Main.positionBack);
}

void AfficherNGame(Background NGame, SDL_Surface *screen)
{
    SDL_BlitSurface(NGame.back[2], NULL, screen, &NGame.positionBack);
}

void AfficherSet(Background Set, SDL_Surface *screen)
{
    SDL_BlitSurface(Set.back[3], NULL, screen, &Set.positionBack);
}

void freeBackMain(Background Back)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        SDL_FreeSurface(Back.back[i]);
    }
}
void freeBackNGame(Background Back)
{

    SDL_FreeSurface(Back.back[2]);
}
void freeBackSet(Background Back)
{

    SDL_FreeSurface(Back.back[3]);
}
void freeBack(Background Back)
{

    SDL_FreeSurface(Back.back[4]);
}

void initButMain(Buttons *B)//initialisation les bouton ili fil menu
{
    //////////////////////////////
    B->Button1A = IMG_Load("newgameON.png");//7amra
    B->Button1NA = IMG_Load("newgameOFF.png");

    B->Button2A = IMG_Load("settingsON.png");
    B->Button2NA = IMG_Load("settingsOFF.png");

    B->Button3A = IMG_Load("quitON.png");
    B->Button3NA = IMG_Load("quitOFF.png");

    B->Button1_position.x = 350;
    B->Button1_position.y = 250;

    B->Button2_position.x = 350;
    B->Button2_position.y = 350;

    B->Button3_position.x = 350;
    B->Button3_position.y = 450;
}
void initButSet(Buttons *B)//kif nod5el setting initialisation lil les boutons ili fi setting 
{
    
    B->Moins = IMG_Load("Moins.png");
    B->moins = IMG_Load("moins.png");
    B->positionMoins.x = 260;
    B->positionMoins.y = 210;
    //////////////////////////////
    B->Plus = IMG_Load("Plus.png");
    B->plus = IMG_Load("plus.png");
    B->positionPlus.x = 610;
    B->positionPlus.y = 210;
B->Normal = IMG_Load("Normal.png");
    B->FullScreen = IMG_Load("FullScreen.png");
    B->positionFullscreen.x = 410;
    B->positionFullscreen.y = 343;
    
    
    //////////////////////////////
    B->Quit = IMG_Load("Quit.png");
    B->positionQuit.x = 410;
    B->positionQuit.y = 430;
}

void AfficherBut1(Buttons B, SDL_Surface *screen, int hover1,int presses)
{
if(presses!=1)//moch bech yesta3mel el clavier 
{


    
    
        if (hover1 == 1)//hover bich ntasti biha mra nlasak bouton ka7la mara 7amra 
        {
            SDL_BlitSurface(B.Button1NA, NULL, screen, &B.Button1_position);
        }
        else if (hover1 == 0)
        {
            SDL_BlitSurface(B.Button1A, NULL, screen, &B.Button1_position);
        }
}
else if (hover1 != 0)//ma3adech  kerser souris 3al bouton 
    {
        if (presses != 1)
        {
            SDL_BlitSurface(B.Button1NA, NULL, screen, &B.Button1_position);
        }
        else if (presses == 1)
        {
            SDL_BlitSurface(B.Button1A, NULL, screen, &B.Button1_position);
        }
    }
    
    
}

void AfficherBut2(Buttons B, SDL_Surface *screen, int hover2,int presses)//
{
if(presses!=2)
{

    
    
        if (hover2 == 1)
        {
            SDL_BlitSurface(B.Button2NA, NULL, screen, &B.Button2_position);
        }
        else if (hover2 == 0)
        {
            SDL_BlitSurface(B.Button2A, NULL, screen, &B.Button2_position);
        }
}
else if (hover2 != 0)
    {
        if (presses != 2)
        {
            SDL_BlitSurface(B.Button2NA, NULL, screen, &B.Button2_position);
        }
        else if (presses == 2)
        {
            SDL_BlitSurface(B.Button2A, NULL, screen, &B.Button2_position);
        }
    }
    
    
}
void AfficherBut3(Buttons B, SDL_Surface *screen, int hover3,int presses)//
{
if(presses!=3)
{

    
    
        if (hover3 == 1)
        {
            SDL_BlitSurface(B.Button3NA, NULL, screen, &B.Button3_position);
        }
        else if (hover3 == 0)
        {
            SDL_BlitSurface(B.Button3A, NULL, screen, &B.Button3_position);
        }
}
else if (hover3 != 0)
    {
        if (presses != 3)
        {
            SDL_BlitSurface(B.Button3NA, NULL, screen, &B.Button3_position);
        }
        else if (presses == 3)
        {
            SDL_BlitSurface(B.Button3A, NULL, screen, &B.Button3_position);
        }
    }
    
    
}
void freeButMain(Buttons B)
{
    SDL_FreeSurface(B.Button1A);
    SDL_FreeSurface(B.Button1NA);
    SDL_FreeSurface(B.Button2A);
    SDL_FreeSurface(B.Button2NA);
    SDL_FreeSurface(B.Button3A);
    SDL_FreeSurface(B.Button3NA);
}
void AfficherButPlus(Buttons B, SDL_Surface *screen)
{
    SDL_BlitSurface(B.plus, NULL, screen, &B.positionPlus);
}
void AfficherButMoins(Buttons B, SDL_Surface *screen)
{
    SDL_BlitSurface(B.moins, NULL, screen, &B.positionMoins);
}
void AfficherButOption(Buttons B, SDL_Surface *screen)
{
    SDL_BlitSurface(B.Option, NULL, screen, &B.positionOption);
}
void AfficherButQuit(Buttons B, SDL_Surface *screen)
{
    SDL_BlitSurface(B.Quit, NULL, screen, &B.positionQuit);
}
void AfficherButScreen(Buttons B, SDL_Surface *screen, int *Mode)//
{
    if (*Mode == 0)
    {
        SDL_BlitSurface(B.Normal, NULL, screen, &B.positionFullscreen);
    }
    else
    {
        SDL_BlitSurface(B.FullScreen, NULL, screen, &B.positionFullscreen);
    }
}
void freeButSet(Buttons B)
{
    SDL_FreeSurface(B.Option);
    SDL_FreeSurface(B.Moins);
    SDL_FreeSurface(B.moins);
    SDL_FreeSurface(B.Plus);
    SDL_FreeSurface(B.plus);
SDL_FreeSurface(B.Normal);
    SDL_FreeSurface(B.FullScreen);
    
    SDL_FreeSurface(B.Quit);
}


/////////////////////////////////
void initialisation(tic * t)
{
    int i;
    for(i=0;i<9;i++)

       t-> tabsuivi[i]=0;
    t->image1=SDL_LoadBMP("fond.bmp");
    t->image2=SDL_LoadBMP("croix.bmp");
    t->image3=SDL_LoadBMP("rond.bmp");
    t->joueur=1;
    t->tour=0;
    t->comic=TTF_OpenFont("comic.ttf",40);
    t->couleur.r=0;
    t->couleur.g=0;
    t->couleur.b=0;
    t->posMSG.x=0;
    t->posMSG.y=0;
}

void affichage(tic t,SDL_Surface *ecran ) 
{
    int i;
         SDL_BlitSurface(t.image1,NULL,ecran,NULL);

    for(i=0;i<9;i++)
   {
		t.pos.x=184*(i%3); //calculer la position d'affichgage de chaque petit carreau exemple
		t.pos.y=180*(i/3);
         printf("valeur de tabsuiv[%d]=%d dans fct ",i,t.tabsuivi[i]);
        	switch(t.tabsuivi[i])// selon 
        	{
            		case -1:
                		SDL_BlitSurface(t.image2,NULL,ecran,&t.pos);	
            		break;
            		case 1:
                		SDL_BlitSurface(t.image3,NULL,ecran,&t.pos);
            		break;
        	}

	
    }
    
}
//////////////////////////////////////////////////////////////////////////////////////////////

 

void Resultat (tic t,SDL_Surface* ecran)
{

char msg[20];

 
affichage(t,ecran);
    switch(atilganer(t.tabsuivi))
    {
        case 0:
            strcpy(msg, "NUL");
        break;
        case 1:
            strcpy(msg, "Defaite");
        break;
        case -1:  
            strcpy(msg, "Victoire");
    }

 SDL_BlitSurface(TTF_RenderText_Solid(t.comic,msg,t.couleur),NULL,ecran,&t.posMSG);
 SDL_Flip(ecran);
    SDL_Delay(4000);
    
}

void liberationmemoire(tic t)
{
    SDL_FreeSurface(t.image1);
    SDL_FreeSurface(t.image2);
    SDL_FreeSurface(t.image3);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int atilganer(int tabsuivi[])
{
//remplir cette matrice avec les combinaisons de succees
    int lignes_gagnantes[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i=0;i<8;++i)
        if(tabsuivi[lignes_gagnantes[i][0]]!=0&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][1]]&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][2]])
                return tabsuivi[lignes_gagnantes[i][2]];
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void calcul_coup(int tabsuivi[])
{
 
int i=0;
while(i<9 && tabsuivi[i]!=0)
{
i++;
}
if(i<9)
{
tabsuivi[i]=1;
}
}
/////////////////////////////////////////////////////////////////////////////////

void generate_afficher (int *alea) 
{
	int test=*alea ;
       srand(SDL_GetTicks());    

 do
  {
     *alea = 1+ rand()%3; 
  }
while(*alea==test) ; 
}
//////////////////////////////////////////////////////////////////////////////////////

void init_enigme(enigme * e, char *nomfichier) 
{ 
int j , y ;
	e->anim.pos.x=100; 
	e->anim.pos.y=20; 
	e->anim.spritesheet=IMG_Load("ourglasse1.png");
	e->anim.cliploaded=1; 
 
	 for(j=0,y=0;j<6;j++,y+=20)
	 {
		 e->anim.clips[j].x=6; 
		 e->anim.clips[j].y=y+6;
		 e->anim.clips[j].w=200; 
		 e->anim.clips[j].h=20;
	 }	
	int i=1;

	e->p.x=0;
	e->p.y=0;
	e->img=NULL;
	 
	 generate_afficher(&e->num_enigme);
	char nomimage[20];
	FILE *f=fopen("enigme.txt","r");
	if(f!=NULL)
	{

		while(fscanf(f,"%s %d\n",nomimage,&e->reponsevrai)!=EOF && i!=e->num_enigme)
		{
			i++;
		}
		printf("%s",nomimage);
		e->img=IMG_Load(nomimage);
		fclose(f);
	}
	else printf("erreur");
} 

 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficherEnigme(enigme e, SDL_Surface * screen) 
{
	SDL_BlitSurface(e.img,NULL,screen,&e.p); 
	SDL_Flip(screen); 
}



 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int resolution (int * running,int *run )
{
        Mix_Chunk *son; 
	SDL_Event event ;
        int r=0 ;
	SDL_PollEvent(&event);
        son= Mix_LoadWAV( "click_effect.wav" );
	switch(event.type)
	{
		  case SDL_QUIT:
			        *running= 0 ;
              		        *run = 0;
				break ;

       case SDL_KEYDOWN :
            switch( event.key.keysym.sym )
                {
			  case  SDLK_q:
                                  Mix_PlayChannel( -1, son, 0 ); 
			   r= 1;
			   break ;
			   case  SDLK_w:
                                  Mix_PlayChannel( -1, son, 0 ); 
			   r= 2;
			   break;
			   case SDLK_e:
                                  Mix_PlayChannel( -1, son, 0 ); 
			   r=3 ;
			   break;

			    }
       break ;
	}
  return r ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void afficher_resultat (SDL_Surface * screen,int s,int r,enigme *en)
 {

 	if (r==s)
 	{
 		en->img=IMG_Load("win.png");
 		SDL_BlitSurface(en->img, NULL, screen, &(en->p)) ;
        SDL_Flip(screen);
 	}
 	else
 	{
 		en->img=IMG_Load("lose.png");
 		SDL_BlitSurface(en->img, NULL, screen, &(en->p)) ;
        SDL_Flip(screen);
 	}
 }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void animer (enigme * e)
{
	e->anim.cliploaded++;
	if(e->anim.cliploaded>=6)
	e->anim.cliploaded=1;
}


void animation_back(SDL_Surface *backg[], SDL_Rect pos_backg,SDL_Surface *screen,int x)
{ 

   SDL_BlitSurface(backg[x], NULL, screen,&pos_backg ) ;
}















