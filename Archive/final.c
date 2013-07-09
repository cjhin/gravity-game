/*
 Ashley Taylor, Charles Jhin
 CSE 20211
 final.c
 */

//TODO instructions screen for arcade mode

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "gfx.h"
#include "alphanum.h"

#define G .0000000000673
#define JOKES 14
#define MAXSHIPS 10
#define MAXPLANETS 10

void readLevels();
void seedIntro();
void introScreen();
int animate();
void drawBall();
void seedPlanets(int level);
void placePlanet(int x, int y);
int click(double x, double y, int clickNum);
void updateShipPosition(int n);
void checkCollision(int n);
void drawScore(int level);
void drawCreativeButtons();
void drawIntroButtons();
int introButtons(int x, int y);
void creative();
void arcade();
void levelScreen(int level);
void 	arcadeInstructionScreen();

//used for planets and ship
struct Ball
{
	double mass;
	double radius;
	double xPos;
	double yPos;
	double xVel;
	double yVel;
};

typedef struct Ball Ball;

Ball planets[MAXPLANETS];
Ball ships[MAXSHIPS];
Ball levels[10][10];

int score=-1;
int totalScore=0;
int highScore=0;
int p=0;
int s=0;

//The Gravity Sim v9.8 allows the user to interact with a "planetary gravity simulator"
//The ships interact with the planets according to newtons law of gravity.

//In creative mode, the user can freely place up to 10 planets and ships and observe and play with the simulator
//In arcade mode, the user is timed to see how long a ship can be kept alive given a set placement of planets
int main()
{
	srand(time(NULL));
	
	//for use in the quirky random sayings on the intro screen
	int ran = rand()%JOKES+1;
	
	int ysize = 600;
	int xsize = 700;
	
	gfx_open(xsize,ysize,"Gravity Sim v 9.8");
	
	seedIntro();
	
	readLevels();
	
	while(1)
	{       		
		if(gfx_event_waiting())
		{			
			char c = gfx_wait();
			int x = gfx_xpos();
			int y = gfx_ypos();
			
			switch (c)
			{  	
				case 1:
					//creative button
					if ((x>=160) && (x<=310) && (y>=500) && (y<=550))
					{
						creative();
						ran = rand()%JOKES+1;
						seedIntro();
					}
					//arcade button
					else if ((x>=380) && (x<=530) && (y>=500) && (y<=550))
					{
						arcade();
						ran = rand()%JOKES+1;
						seedIntro();
					}
					//seed new splash joke
					else if((x>=300) && (x<=650) && (y>=150) && (y<=170))
						ran = rand()%JOKES+1;
					break;
				case 'q':
				case 'Q':
					return;
					break;
			}
		}

		introScreen(ran);
		
		animate();	
		
		//sleep and wait so that the ball animates/moves smoothly.
		gfx_flush();
		usleep(100000);
		gfx_clear();
	}
}	
//In creative game mode, the user can freely place up to 10 planets and 10 ships that will interact with each other according
//to Newtons laws of gravity
void creative()		
{	
	//mode=0 -> adding planets, mode=1 -> adding ships, mode=-1 -> default
	int mode=-1;
	int clickNum=1;
	
	while(1)
	{  
		drawCreativeButtons();
		
		if(gfx_event_waiting())
		{       
			char c = gfx_wait();
			
			int x = gfx_xpos();
			int y = gfx_ypos();
			
			switch(c)
			{
				case 1: 
					//if they clicked in the button area
					if((y>=550) && (y<=600))
					{ 
						//add planets and ships
						if((x>=50) && (x<=200))
							mode=1;
						else if((x>200) && (x<=330))
							mode=2;
						
						//reset buttons
						else if((x>330) && (x<=500))
							p=0;
						else if((y>500) && (y<=650))
							s=0;
					}
					
					//currently in planet placing mode
					else if (mode==1)
						placePlanet(x,y);

					//curently in ship placing mode
					else if (mode==2)
						clickNum=click(x, y, clickNum);
					
					break;
				case 'q':
				case 'Q':
					gfx_clear();
					return;
			}
		}
		
		//if the user has placed the ship but has not chosen the init velocity yet, show a line to where the vel would be as a guide
		
		/*TODO Unfortunately it doesnt work because xpos() and ypos() get the position through gfx_wait(), aka the last time anything was pressed...
		 if(clickNum==1)
		 {
		 gfx_color(255, 255, 255);
		 gfx_line(ships[0].xPos, ships[0].yPos, gfx_xpos(), gfx_ypos());
		 }*/
		
		animate();
		
		//sleep and wait so that the ball animates/moves smoothly.
		gfx_flush();
		usleep(100000);
		gfx_clear();
	}
}

//In arcade mode the user places a ship in a "field" of predetermined planets and tries to keep the ship alive for as long as possible
void arcade()
{
	arcadeInstructionScreen();
	
	totalScore=0;
	int clickNum=1;
	int level=1;
	
	//levels 1-10
	for(level; level<=10; level++)
	{
		s=0;
		levelScreen(level);
		
		seedPlanets(level);
	
		//main animation loop
		while(1)
		{  
			if(gfx_event_waiting())
			{ 
				char c = gfx_wait();
			
				int x = gfx_xpos();
				int y = gfx_ypos();
			
				switch(c)
				{
					case 1:
						if(!(s==1 && clickNum==1))
							clickNum=click(x, y, clickNum);
						break;   	
					case 'q':
					case 'Q':
						//quit
						return;
						break;
				}
			}
		
			//if == 1, ship is dead, so move to next level
			if(animate()==1)
				break;
			//if the score is >200, then move to the next level as well
			if(score>199)
			{
				totalScore+=score;
				ships[0].mass=0;
				break;
			}
			
			drawScore(level);
		
			gfx_flush();
			usleep(100000);
			gfx_clear();
		}
		score=-1;
	}
	
	//game over screen
	gfx_clear();
	gfx_color(255, 0, 0);
	drawString("GAME OVER", 150, 200, 50);
	gfx_color(0, 255, 0);
	drawString("SCORE:", 150, 350, 50);
	char buf[10];
	sprintf(buf, "%d", totalScore);
	drawString(buf, 400, 350, 50);
	
	//set high score if applicable
	if(totalScore>highScore)
		highScore=totalScore;
	
	gfx_color(255, 255, 255);
	drawString("press any key to return", 150, 450, 10);
	gfx_flush();
	char c=gfx_wait();
	gfx_clear();
	
	return;
}

//seed the intro animation
void seedIntro()
{
	//2 ships orbiting 2 planets
	s=2;
	p=2;
	planets[0].mass=2000000000000;
	planets[0].radius=10;
	planets[0].xPos=260;
	planets[0].yPos=320;
	
	planets[1].mass=2000000000000;
	planets[1].radius=10;
	planets[1].xPos=400;
	planets[1].yPos=340;
	
	ships[0].xPos=340;
	ships[0].yPos=200;
	ships[0].radius=5;
	ships[0].mass=1000;
	ships[0].xVel=15;
	ships[0].yVel=0;
	
	ships[1].xPos=330;
	ships[1].yPos=350;
	ships[1].radius=5;
	ships[1].mass=1000;
	ships[1].xVel=-3;
	ships[1].yVel=20;
	
	return;
}

//intro/main menu screen with funny saying, as well buttons to choose arcade or creative mode
void introScreen(int c)
{
	gfx_color(240, 220, 130);
	drawString("Gravity Sim v9.8", 80, 80, 45);
	gfx_color(255, 255, 255);
	drawString("Press 'q' to quit at any time.", 5, 575, 10);
	
	char buf[10];
	drawString("high score:", 405, 565, 10);
	sprintf(buf, "%d", highScore);
	drawString(buf, 500, 565, 10);
	
	gfx_color(255, 120, 0);
	drawString("Click this!!!", 600, 210, 9);
	//arrow
	gfx_line(600, 180, 610, 200);
	gfx_line(600, 180, 608, 185);
	gfx_line(600, 180, 598, 186);
	
	gfx_color(255, 255, 255);
	//funny intro screen sayings randomed from main
	switch (c) 
	{
		case 1:
			drawString("As Seen On TV!", 482, 150, 15);
			break;
		case 2:
			drawString("Fund Comp Rulez!", 456, 150, 15);
			break;
		case 3:
			drawString("Turing Complete!", 460, 150, 15);
			break;
		case 4:
			drawString("Zero Calories!", 482, 150, 15);
			break;
		case 5:
			drawString("Limited Edition!", 455, 150, 15);
			break;
		case 6:
			drawString("Have a Nice Day!", 460, 150, 15);
			break;
		case 7:
			drawString("4 out of 5 Dentists Agree!", 340, 150, 15);
			break;
		case 8:
			drawString("Bigger than a Breadbox!", 375, 150, 15);
			break;
		case 9:
			drawString("Theyrrrrreee Greattttt!", 374, 150, 15);
			break;
		case 10:
			drawString("Truthiness!", 519, 150, 15);
			break;
		case 11:
			drawString("Made in South Bend!", 425, 150, 15);
			break;
		case 12:
			drawString("Supercalifragilisticexpialidocious!", 232, 150, 15);
			break;
		case 13:
			drawString("Go Irish!", 530, 150, 15);
			break;
		case 14:
			gfx_color(0,255,0);
			drawString("Merry", 470, 150, 15);
			gfx_color(255, 0, 0);
			drawString("Christmas!", 540, 150, 15);			
			break;
		default:
			drawString("This Message Means Something is Broken!", 200, 150, 15);
			break;
	}
	
	drawIntroButtons();
	return;
}

//update all of the ship positions through updateShipPosition, 
//also draws planets, and ships 
int animate()
{		
	//draw planets
	int i=0;
	gfx_color(0, 100, 255);
	for(i; i<p; i++)
	{
		drawBall(planets[i].xPos, planets[i].yPos, planets[i].radius);
	}
	
	//draw ships
	int n=0;
	gfx_color(50, 250, 30);
	for(n; n<s; n++)
	{
		//if the ship has been placed, in other words mass>0
		if(ships[n].mass>0)
		{
			updateShipPosition(n);
			checkCollision(n);
			drawBall(ships[n].xPos, ships[n].yPos, ships[n].radius);
		}
		//if the ship has been placed but hasnt moved yet which is related to radius=4.
		else if(ships[n].radius==4)
		{
			gfx_color(0, 255, 0);
			drawBall(ships[n].xPos, ships[n].yPos, ships[n].radius);
		}
		//unless its dead, in which case explosion animation!!!!!
		else if(ships[n].mass<0 && ships[n].mass>-15)
		{
			double sx = ships[n].xPos;
			double sy = ships[n].yPos;
			double mod = ships[n].mass;
			gfx_color(255,0,0);
			drawString("BOOM",sx-50,sy+30,35);
			gfx_line(sx-mod,sy-mod,sx+mod,sy+mod);
			gfx_line(sx+mod,sy-mod,sx-mod,sy+mod);
			gfx_line(sx,sy+mod,sx,sy-mod);
			gfx_line(sx-mod,sy,sx+mod,sy);
			gfx_color(255, 140, 0);
			drawBall(sx, sy, mod*1.3);
			gfx_color(255, 140, 90);
			drawBall(sx, sy, mod/1.5);
			gfx_color(250, 100, 120);
			drawBall(sx, sy, mod/2.5);
			gfx_color(20, 250, 30);
			ships[n].mass--;	
		}
		//for arcade mode, at this point its dead so move to the next level
		if(ships[n].mass<=-15)
		{
			ships[n].mass=0;
			gfx_color(255, 255, 255);
			return 1;
		}
	}
	gfx_color(255, 255, 255);
	return 0;
}

//if the user clicks, there are two options decided by int mode
//on the first click, (clickNum=1) place the ship by setting the xPos and yPos.  mass=0 so that it wont move yet
//on the second click, (clickNum=2) set the initial velocity relative to the xPos and yPos of the ship with a velocity cap.
int click(double x, double y, int clickNum)
{  
	//max 10 ships allowed
	if(s<MAXSHIPS)
	{
		//first click, radius is set = to 4 to tell animate not to move it yet.
		if(clickNum==1)
		{
			ships[s].xPos=x;
			ships[s].yPos=y;
			ships[s].radius=4;
			ships[s].mass=0;
			score=-1;
			clickNum=2;
			s++;
		}
		//second click
		else if(clickNum==2)
		{
			s--;
			ships[s].radius=5;
			ships[s].mass=1000;
			ships[s].xVel=(x-ships[s].xPos)/4.0;
			ships[s].yVel=(y-ships[s].yPos)/4.0;
					
			//velocity cap
			double velMax=15;
					
			if(ships[s].xVel>velMax)
				ships[s].xVel=velMax;
			else if(ships[s].xVel<-1*velMax)
				ships[s].xVel=-1*velMax;
			if(ships[s].yVel>velMax)
				ships[s].yVel=velMax;
			else if(ships[s].yVel<-1*velMax)
				ships[s].yVel=-1*velMax;
				
			score=0;
			clickNum=1;
			s++;
		}
	}
	else
	{
		drawString("Too Many Ships",x,y,30);
		gfx_flush();        
		usleep(100000);
	}
	return clickNum;
}

//find the net force on the ship due to the planets, 
//derive and apply the acceleration to get the new velocity and thus new position
void updateShipPosition(int n)
{
	double netXForce=0;
	double netYForce=0;
	
	int i=0;
	for(i; i<p; i++)
	{
		double x1=ships[n].xPos;
		double y1=ships[n].yPos;
		double x2=planets[i].xPos;
		double y2=planets[i].yPos;
		double dist=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
		double gForce=0;
		
		//don't add any gravitational force if the planet is within 5, as its probably about to collide anyways, and by applying such a large force, 
		//the ship will be catapulted "through" the planet to a galaxy far far away
		if(dist<5.0)
			gForce=0;
		else {
			gForce=G*ships[n].mass*planets[i].mass/dist;
		}
		
		//split this force into x and y components
		double theta=atan((y2-y1)/(x2-x1+.01));
		
		//depending on the relative positioning the force will either be in the positive
		//or negative x and y directions
		if(x1>x2)
		{
			netXForce-=gForce*cos(theta);		
			netYForce-=gForce*sin(theta);
		}
		else 
		{
			netXForce+=gForce*cos(theta);		
			netYForce+=gForce*sin(theta);
		}			
	}
	
	ships[n].xPos+=ships[n].xVel+netXForce/ships[n].mass;
	ships[n].yPos+=ships[n].yVel+netYForce/ships[n].mass;
	
	ships[n].xVel+=netXForce/ships[n].mass;
	ships[n].yVel+=netYForce/ships[n].mass;
	
	return;
}

//check to see if the ship has collided with any of the planets.  
//If so set the ship to "dead" by changing mass ->-1
void checkCollision(int n)
{
	int i=0;
	double sx = ships[n].xPos;
	double sy = ships[n].yPos;
	double sr = ships[n].radius+20;
	double svx = ships[n].xVel;
	double svy = ships[n].yVel;
	
	for(i; i<p; i++)
	{
		double px=planets[i].xPos;
		double py=planets[i].yPos;
		double pr=planets[i].radius;
		
		//collision has occured
		//sx+.5*svx = current position + 1/2 of the velocity, (second set of conditionals)
		//are for when the current and future positions are/will not be within the planet radius,
		//but the path will go through the planet. (in other words when the ship is going too fast to catch the collision)
		//Checking the "midpoint" effectively takes care of most of these instances.
		//TODO Better collision detection?
		if((sx>px-pr && sx<px+pr && sy>py-pr && sy<py+pr) || (sx+.5*svx>px-pr && sx+.5*svx<px+pr && sy+.5*svy>py-pr && sy+.5*svy<py+pr))
		{
			ships[n].mass=-1;//this will signal to animate that the ship is "dead"
			totalScore+=score;
			score=-1;
			return;
		}
	}
	
	return;
}

//draw a ball on the screen given x, y, r
void drawBall(double x, double y, double r)
{
	float theta=0;
	float x1=x+r;
	float y1=y;
	float x2=x;
	float y2=y;
	for(theta; theta<6.3; theta+=.1)
	{
		x2=r*cos(theta)+x;
		y2=r*sin(theta)+y;
		gfx_line(x1,y1,x2,y2);
		x1=x2;
		y1=y2;
	}
	return;
}

//read in the levels from the txt file and save in levels[][] for later use
void readLevels()
{
	FILE *pFile;
  char input[100][100];
	int counter=0;
  
	//read the file data in to input[flightsAmount]
  pFile = fopen("levels.txt", "r");
	
  if (pFile == NULL) 
		printf("ERROR: File Not Found!\n");
  else 
	{
    while(fgets(input[counter], 50, pFile))
		{
			counter++;
		}
    fclose(pFile);
  }
	
	counter=0;

	//parse the data in input[] and add to levels[]
  int i;
	//for each level
  for(i = 0; i < 10; i++) 
	{
		int j;
		//there are i planets in every level
		for(j=0; j<=i; j++)
		{
			sscanf(input[counter], "%lf %lf %lf %lf", &levels[i][j].mass, &levels[i][j].radius, &levels[i][j].xPos, &levels[i][j].yPos);
			counter++;
		}
  }
  return;
}

//seed the planets with the current level from levels[] read from levels.txt in readLevels()
void seedPlanets(int level)
{
	p=level;
	int i;
	
	//get the planets from levels and assign to the planets for use in the current "level"
	for(i=0; i<level; i++)
	{
		planets[i].mass=levels[level-1][i].mass;
		planets[i].radius=levels[level-1][i].radius;

		planets[i].xPos=levels[level-1][i].xPos;
		planets[i].yPos=levels[level-1][i].yPos;
	}
	return;
}

//place a planet given an x and y position
void placePlanet(int x, int y)
{
	if(p<MAXPLANETS)
	{
		planets[p].mass=2000000000000;
		planets[p].radius=10;
		planets[p].xPos=x;
		planets[p].yPos=y;
		p++; 
	}
	//if max number of planets has been placed
	else
	{
		drawString("Too Many Planets",x,y,30);
		gfx_flush();
		usleep(100000);
	}
}

//draw the current score in a corner as well as the high score at the top of the string
void drawScore(int level)
{
	char buf[10];
	
	//high score
	int tempScore=totalScore;
	
	drawString("total:", 100, 35, 15);
	//transfer tempScore to string and then call drawString from alphanum.c
	sprintf(buf, "%d", tempScore);
	drawString(buf, 175, 35, 15);
	
	drawString("Level:", 300, 35, 15);
	sprintf(buf, "%d", level);
	drawString(buf, 375, 35, 15);
	
	drawString("score:", 500, 35, 15);
	//draw current score only if a ship has been placed
	if(score>=0)
	{
		tempScore=score;
		score++;
		
		sprintf(buf, "%d", tempScore);
		drawString(buf, 575, 35, 15);
	}
	
	return;
}

//screen for in between levels
void levelScreen(int level)
{
	gfx_clear();
	drawScore(level);
	
	drawString("Level ", 230, 275, 50);
	char buf[3];
	sprintf(buf, "%d", level);
	gfx_color(200, 200, 0);
	drawString(buf, 450, 275, 50);
	
	gfx_color(255, 255, 255);
	drawString("click to continue", 290, 340, 10);
	
	gfx_wait();
	return;
}

//instruction screen for beginning of arcade mode
void arcadeInstructionScreen()
{
	gfx_clear();
	drawScore(0);
	
	gfx_color(175, 100, 230);
	drawString("Instructions:", 100, 100, 30);
	
	gfx_color(200, 200, 200);
	drawString("Try and keep your ship alive", 100, 160, 20);
	drawString("for as long as possible!", 100, 190, 20);
	drawString("...Or until 200 seconds", 100, 230, 20);
	
	drawString("Click once to place the ship,", 100, 370, 20);
	drawString("Click again to", 100, 420, 20);
	drawString("set the initial velocity.", 100, 450, 20);
	
	gfx_color(255, 255, 255);

	gfx_flush();
	gfx_wait();
	
	return;
}

//buttons for the intro screen
void drawIntroButtons()
{
	gfx_color(255, 100, 70);
	drawBox(160, 500, 310, 550);
	drawBox(380, 500, 530, 550);
	
	drawString("SANDBOX", 180,515,20);
	drawString("ARCADE", 410,515,20);
	gfx_color(255, 255, 255);
}

//buttons for creative mode
void drawCreativeButtons()
{
	drawBox(50, 550, 200, 600);	
	drawBox(200, 550, 330, 600);	
	drawBox(330, 550, 500, 600);	
	drawBox(500, 550, 650, 600);	

	drawString("Place Planet", 60, 565, 14);
	drawString("Place Ship", 213, 565, 14);
	drawString("Reset Planets",345,565,14);
	drawString("Reset Ships",515,565,14);
}