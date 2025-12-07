//current plan for shooting - captured_enemies_index[i] for number of enemy (like ghost 1 or 2 or 3...), new array captured_enemies_type[i], need like a Last in First out structure so just use these two arrays ez
//todo add win condition for level one
//To Aazan when an enemy is captured decrease their count by one plz
// i have hanged const float& speed to int and speed because of it i wasted three hours in debugging, hope it won't effect other things 

#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include<cstdlib>
#include<ctime>
#include<string>



using namespace sf;
using namespace std;

int screen_x = 1152;
int screen_y = 1000;




void reload(float& player_x, float& player_y, Sprite &PlayerSprite, int cell_size, int height, int PlayerHeight, bool& FirstRun);// to reload the current level 

//starting work on power ups

bool power_deploy(int enemy_x, int enemy_y,int& power_x, int &power_y,int width , int height, int& power_select);

void power_display(int power_x, int power_y, Texture& texpower, Sprite& power,int power_select );

bool power_up(int power_x, int power_y, float player_x, float player_y, int playerWidth, int playerHeight,bool& powerPlaced,int power_select, int& speed,int& lives, int& vacuum_range, int& vacuum_width,int &prevlife);

bool remove_power(int power_select, int& speed,int& lives, int& vacuum_range, int& vacuum_width);

void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int & lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[], int& ActiveEnemies, int skeleton_x[], int skeleton_y[], int skeletonCount, int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, int GhostCount, int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]);

void chelnovMove(int chelnov_x[], int chelnov_y[], int width, Sprite chelnovSp[], bool chelnovMovingLeft[], int i, float& player_x, float& player_y, char **lvl, Sprite &PlayerSprite, int cell_size, int PlayerHeight, int height, bool chelnovIdle[], int & lives, const int chelnovCount, int currentchelnov, bool posChangeHappened[], int FramePosForChange[], bool& FirstRun, bool chelnovJumping[], int jumpCoolDown[], bool chelnovBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]);


void floatingGhost(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap,int &lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[]);

void check_stuck(char** lvl, float& player_x, float& player_y, float& velocityY, int PlayerWidth, int PlayerHeight, int cell_size, int width, int height);

void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, int& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height, int& vacuum_x, int& vacuum_y);// handle all ingame movement and collision and gun direction aim

void level_one(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]);

void level_two(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], float chelnovShotVelX[], float chelnovShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, int chelnovBounceCount[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]);

void level_three(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]);

void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size);

void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool skeletonIdle[],int & lives,const int skeletonCount, int currentSkeleton, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool skeletonJumping[],int jumpCoolDown[], bool SkeletonBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float SkeletonShotVelX[], float SkeletonShotVelY[], int SkeletonBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]);

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);

void vacuum_suck(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int& vacuum_x, int& vacuum_y, int maxcap, int vacuum_range, int vacuum_width, int captured_enemies_index[], int& captured_count, int Ghost_x[], int Ghost_y[], int num_ghosts, bool GhostBeingPulled[],bool Firstrun,RenderWindow& window, int captured_enemies_type[]);

void invisibleManMove(int invisibleMan_x[],int invisibleMan_y[],int width,Sprite invisibleManSp[],bool invisibleManMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool invisibleManIdle[],int & lives,const int invisibleManCount, int currentinvisibleMan, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool invisibleManJumping[],int jumpCoolDown[], bool invisibleManBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int InvisibleManBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]);

void singleShot(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int vacuum_x, int vacuum_y, int captured_enemies_index[], int captured_enemies_type[], int& captured_count, int Ghost_x[], int Ghost_y[], float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int chelnov_x[], int chelnov_y[], float chelnovShotVelX[], float chelnovShotVelY[]);


void DynamTest();

int main()
{

	
	
	
	
	
	
	
	
	static bool FirstRun=1;
	static int lives=3;
	static int score=0;
	bool ShowStart=1;
	bool pause=0;



	//set up random number seed
	srand(time(0));




//invisibleMan Prototype
 	


	








	
	















	bool facingLeft=true; //cuz start with left sprite


	RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP", Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);



	
	



	//level specifics
	int level=1;
	const int cell_size = 64;
	const int height = 15;
	const int width = 18;
	char** lvl;
	




	
	
	
	








	//gun specifics
	int maxcap = 3;
	int vacuum_range = 200;
	int vacuum_width = 50;
	
	//all enemy arrays
	const int skeletonCount=4;
	const int GhostCount=8;
	const int invisibleManCount=3;
	const int chelnovCount = 4; 
    
	float GhostShotVelX[GhostCount] = {0}; //for gun shoot projectile speed
	float GhostShotVelY[GhostCount] = {0};
	int GhostBounceCount[GhostCount] = {0};
	
	float SkeletonShotVelX[skeletonCount] = {0};
	float SkeletonShotVelY[skeletonCount] = {0};
	int SkeletonBounceCount[skeletonCount] = {0};
	
	float InvisibleManShotVelX[invisibleManCount] = {0};
	float InvisibleManShotVelY[invisibleManCount] = {0};
	int InvisibleManBounceCount[invisibleManCount] = {0};
	
	float chelnovShotVelX[chelnovCount] = {0};
	float chelnovShotVelY[chelnovCount] = {0};
	int chelnovBounceCount[chelnovCount] = {0};
	
	bool GhostIsShot[GhostCount] = {0};
	bool SkeletonIsShot[skeletonCount] = {0};
	bool InvisibleManIsShot[invisibleManCount] = {0};
	bool ChelnovIsShot[chelnovCount] = {0};
	
	int captured_enemies_index[5] = {0}; 
	int captured_enemies_type[5] = {0};
	int captured_count = 0;
	
	int ActiveEnemies = 0;
	
	int vacuum_x = 1;
	int vacuum_y = 0;


	//level and background textures and sprites
	Texture bgTex;
	Sprite bgSprite;
	Texture blockTexture;
	Sprite blockSprite;


	
	bgTex.loadFromFile("Data/bg.png");
	bgSprite.setTexture(bgTex);
	bgSprite.setPosition(0,0);


	float scaleX = (width * cell_size) / (float)bgTex.getSize().x;
	float scaleY = (height * cell_size) / (float)bgTex.getSize().y;
	bgSprite.setScale(scaleX, scaleY);


	blockTexture.loadFromFile("Data/block1.png");
	blockSprite.setTexture(blockTexture);
	

	//Music initialisation
	Music lvlMusic;

	lvlMusic.openFromFile("Data/mus.ogg");
	lvlMusic.setVolume(15);
	//lvlMusic.play();
	//lvlMusic.setLoop(true);

	//player data
	float player_x = 500;
	float player_y = 150;
	int frarmeWidth=64;
	int frameHeight=64;

	int speed=5;
	float velocityX=1;
	float terminal_Velocity_x=5;
	float friction=0.8;
	float acceleration=1;

	const float jumpStrength = 19; // Initial jump velocity
	const float gravity = 1;  // Gravity acceleration

	bool isJumping = false;  // Track if jumping

	bool up_collide = false;
	bool left_collide = false;
	bool right_collide = false;

	Texture PlayerTexture;
	Sprite PlayerSprite;

	bool onGround = true;

	float offset_x = 0;
	float offset_y = 0;
	float velocityY = 0;

	float terminal_Velocity = 20;

	int PlayerHeight = 60;
	int PlayerWidth = 96;

	bool up_button = false;

	char top_left = '\0';
	char top_right = '\0';
	char top_mid = '\0';

	char left_mid = '\0';
	char right_mid = '\0';

	char bottom_left = '\0';
	char bottom_right = '\0';
	char bottom_mid = '\0';

	char bottom_left_down = '\0';
	char bottom_mid_down = '\0';

	char top_right_up = '\0';
	char top_mid_up = '\0';
	char top_left_up = '\0';

	PlayerTexture.loadFromFile("Data/player.png");
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setTextureRect(IntRect(15,41,32,40));
	PlayerSprite.setScale(2.5,2.5);
	player_x=cell_size;
	player_y=(height-2)*cell_size-PlayerHeight;
	PlayerSprite.setPosition(player_x, player_y);




	//creating level array
	lvl = new char* [height];
	for (int i = 0; i < height; i += 1)
	{
		lvl[i] = new char[width];
	}

	//lvl[7][7] = '#';
	//lvl[7][8] = '#';
	//lvl[7][9] = '#';


	Event ev;
	//main loop


	int counter=1;
	//PlayerSprite.setTextureRect(IntRect(counter*frarmeWidth,0,frarmeWidth,frameHeight));





	//All text for the game window


	//handle the font
	Font font;
	font.loadFromFile("Data/Font.otf");




	Text livesText;
	Text ScoreText;
	Text capturedText;

	ScoreText.setFont(font);
	livesText.setFont(font);
	capturedText.setFont(font);

	ScoreText.setCharacterSize(50);
	livesText.setCharacterSize(50);
	capturedText.setCharacterSize(50);

	livesText.setPosition(64,42);
	ScoreText.setPosition((14*64),42);
	capturedText.setPosition((((64)+14*64)/2)-128,42);
	

	// livesText.setString("Lives : %d",lives);

	ScoreText.setFillColor(Color::Red);
	livesText.setFillColor(Color::Red);
	capturedText.setFillColor(Color::Red);

    // Initial string
    livesText.setString("Lives: " + to_string(lives));
	ScoreText.setString("Score: "+ to_string(score));
	capturedText.setString("Enemies Captured: " + to_string(captured_count));


	
	while (window.isOpen())
	{
				Sprite startSprite;
				Texture startTex;Event event;
			while(window.pollEvent(event)) {
    		if(event.type == Event::KeyPressed) {
        		if(event.key.code == Keyboard::P)
            		pause = !pause;		
    			}
			}
			if(pause) {
			continue; //pause the game
			}			
		
			
	
			if(ShowStart)//Show the start screen at the start of each game
			{
				
			
				startTex.loadFromFile("Data/startScreen.png");
				startSprite.setTexture(startTex);
				startSprite.setPosition(0,0);


				float scaleX = (width * cell_size) / (float)startTex.getSize().x;
				float scaleY = (height * cell_size) / (float)startTex.getSize().y;
				startSprite.setScale(scaleX, scaleY);

				window.draw(startSprite);
				window.display();
				
			
			}
		
		
		
		
		if(lives<=0)//lives check 
			{

				bgTex.loadFromFile("Data/GameOver.png");
				bgSprite.setTexture(bgTex);


				float scaleX = (width * cell_size) / (float)bgTex.getSize().x;
				float scaleY = (height * cell_size) / (float)bgTex.getSize().y;
				bgSprite.setScale(scaleX, scaleY);

				window.draw(bgSprite);
				window.display();

				int temp;
				cin>>temp;

				cout<<"game over"<<endl;
					break;

			}

		counter++;
		while (window.pollEvent(ev))
		{
				
			if(ev.type == Event::Resized)
				{ //resize the start screen if the user resizes the window
					
					if(ShowStart){
					startTex.loadFromFile("Data/startScreen.png");
					startSprite.setTexture(startTex);
					startSprite.setPosition(0,0);

					float scaleX = (width * cell_size) / (float)startTex.getSize().x;
					float scaleY = (height * cell_size) / (float)startTex.getSize().y;
					startSprite.setScale(scaleX, scaleY);

					window.draw(startSprite);
					window.display();
					}

				}
			
			if (ev.type == Event::Closed) 
			{
				window.close();
			}
			

			if (ev.type == Event::KeyPressed )
			{
			
				
			}

		}


		if(ShowStart){

			if(Keyboard::isKeyPressed(Keyboard::Space)){
				ShowStart=0;
				
			}
			continue;

		}	//if the user presses the space key dont show start





		

	











		//movement( player_x,velocityY, isJumping, velocityX,PlayerTexture,PlayerSprite, onGround, jumpStrength, speed, friction, counter, terminal_Velocity_x);
			
		// playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y);
		// check_stuck(lvl, player_x,  player_y, velocityY,  PlayerWidth, PlayerHeight,  cell_size,  width,  height);
		// vacuum_suck(player_x, player_y,  PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range,  vacuum_width, captured_enemies_index,  captured_count,  Ghost_x, Ghost_y,  8, GhostBeingPulled);//replcaed num_ghosts with 8 for testing 


		//presing escape to close
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear();

		display_level(window, lvl, bgTex, bgSprite, blockTexture, blockSprite, height, width, cell_size);
		player_gravity(lvl,offset_y,velocityY,onGround,gravity,terminal_Velocity, player_x, player_y, cell_size, PlayerHeight, PlayerWidth);
		PlayerSprite.setPosition(player_x, player_y);
		window.draw(PlayerSprite);
		
		
		
		
		level=2; // changed level for testing
		if(level==1){
			
			if(Keyboard::isKeyPressed(Keyboard::L)) // reload level at pressing l
			reload(player_x, player_y, PlayerSprite, cell_size, height, PlayerHeight, FirstRun);


			level_one(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength,   speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width, captured_enemies_type, GhostShotVelX, GhostShotVelY, SkeletonShotVelX, SkeletonShotVelY, InvisibleManShotVelX, InvisibleManShotVelY, GhostBounceCount, SkeletonBounceCount, InvisibleManBounceCount, ActiveEnemies, chelnovShotVelX, chelnovShotVelY, chelnovBounceCount, GhostIsShot, SkeletonIsShot, InvisibleManIsShot, ChelnovIsShot);



		}else
			if(level==2){
			if(Keyboard::isKeyPressed(Keyboard::L)) // reload level at pressing l
			{
				reload(player_x, player_y, PlayerSprite, cell_size, height, PlayerHeight, FirstRun);}


					if(FirstRun){
					
						livesText.setFillColor(Color::Black);
						ScoreText.setFillColor(Color::Black);
						capturedText.setFillColor(Color::Black);
	

						blockTexture.loadFromFile("Data/block2.png");
						blockSprite.setTexture(blockTexture);


						bgTex.loadFromFile("Data/volcanic.jpeg");
						bgSprite.setTexture(bgTex);

						float scaleX = (width * cell_size) / (float)bgTex.getSize().x;
						float scaleY = (height * cell_size) / (float)bgTex.getSize().y;
						bgSprite.setScale(scaleX, scaleY);


						window.draw(bgSprite);
					}

			


					level_two(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength, speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width, captured_enemies_type, GhostShotVelX, GhostShotVelY, SkeletonShotVelX, SkeletonShotVelY, InvisibleManShotVelX, InvisibleManShotVelY, chelnovShotVelX, chelnovShotVelY, GhostBounceCount, SkeletonBounceCount, InvisibleManBounceCount, ActiveEnemies, chelnovBounceCount, GhostIsShot, SkeletonIsShot, InvisibleManIsShot, ChelnovIsShot);			
				}
			
		
				if(level==3){
					if(Keyboard::isKeyPressed(Keyboard::L)) { 
						reload(player_x, player_y, PlayerSprite, cell_size, height, PlayerHeight, FirstRun);
					}
					
					
					level_three(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength,   speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width, captured_enemies_type, GhostShotVelX, GhostShotVelY, SkeletonShotVelX, SkeletonShotVelY, InvisibleManShotVelX, InvisibleManShotVelY, GhostBounceCount, SkeletonBounceCount, InvisibleManBounceCount, ActiveEnemies, chelnovShotVelX, chelnovShotVelY, chelnovBounceCount, GhostIsShot, SkeletonIsShot, InvisibleManIsShot, ChelnovIsShot);      
				}
		
		
		
		
		ScoreText.setString("Score: "+ to_string(score));
		livesText.setString("Lives: " +to_string(lives));
		capturedText.setString("Enemies Captured: " + to_string(captured_count));


		
		window.draw(livesText);
		window.draw(ScoreText);
		window.draw(capturedText);
		window.display();

		FirstRun=0;
	}

	//stopping music and deleting level array
	lvlMusic.stop();
	for (int i = 0; i < height; i++)
	{
		delete[] lvl[i];
	}
	delete[] lvl;

	return 0;
}




void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap,int &lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[], int& ActiveEnemies, int skeleton_x[], int skeleton_y[], int skeletonCount, int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, int GhostCount, int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[])
{

	static int Frame=5;	
	static int FrameCount=0;
	
	
	if (GhostShotVelX[i] != 0 || GhostShotVelY[i] != 0) { //movement for shot
		GhostIsShot[i] = true;
		
		int next_x = Ghost_x[i] + (int)GhostShotVelX[i]; //x movemnet
		
		int gridX = next_x / cell_size; //coords
		int gridY = Ghost_y[i] / cell_size;
		
		
		if (next_x <= 0 || next_x >= (width - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) 
		{ //if left or right border or hitting a platform
			GhostShotVelX[i] = -GhostShotVelX[i]; //reverse X direction, bounce
			GhostBounceCount[i]++;
		}
		else Ghost_x[i] = next_x;
		
		//y movement
		GhostShotVelY[i] += 1; //gravity is 1, too annoying to pass in fn
		if (GhostShotVelY[i] > 20) 
			GhostShotVelY[i] = 20; //terminal velocity clamp
		
		int next_y = Ghost_y[i] + (int)GhostShotVelY[i];
		gridX = Ghost_x[i] / cell_size; //uses updated x position
		gridY = next_y / cell_size;
		
		if (next_y <= 0 || next_y >= (height - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#'))
		{ //if hit top and bottom border or platforms
			if (GhostShotVelY[i] > 0) { //if moving down
				GhostShotVelY[i] = 0; //stop falling
				if (gridY < height) 
					Ghost_y[i] = (gridY - 1) * cell_size;
				if (GhostShotVelX[i] == 0) {//if fell striagght down choose random directin t roll to
					if (rand() % 2 == 0)
						GhostShotVelX[i] = 15; //right
					else GhostShotVelX[i] = -15; //left
					}
				}
				
			else if (GhostShotVelY[i] < 0) { //moving up
				GhostShotVelY[i] = 0;
				if (GhostShotVelX[i] == 0) { //no vertical movemnt, same random logic
				if (rand() % 2 == 0)
						GhostShotVelX[i] = 15; //right
					else GhostShotVelX[i] = -15; //left
					}
				}
				
		} //if not hitting platforms
		else Ghost_y[i] = next_y;
		
		if (GhostBounceCount[i] >= 5) {
			GhostShotVelX[i] = 0;
			GhostShotVelY[i] = 0;
			GhostIsShot[i] = false;
			Ghost_x[i] = -1000;
			Ghost_y[i] = -1000;
			ActiveEnemies--;
		}
		//--- CONTINUE THIS, REPLICATE FOR SKELLY AND INVIS, ADD GRAV ---
		
		int ghost_size = 64;
		for (int j = 0; j < GhostCount; j++) {
			if(j!=i && Ghost_x[j] > 0 && !(GhostIsShot[i] && GhostIsShot[j])) { //doesnt check itself and off screen ghosts, doesnt collide if both shot
				if (!(Ghost_x[i] < Ghost_x[j] - ghost_size || Ghost_x[i] > Ghost_x[j] + ghost_size) && !(Ghost_y[i] < Ghost_y[j] - ghost_size || Ghost_y[i] > Ghost_y[j] + ghost_size)) { //collision with other ghost
					Ghost_x[i] = -1000; //both die
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					GhostIsShot[i] = false;
					Ghost_x[j] = -1000;
					Ghost_y[j] = -1000;
					
					ActiveEnemies --;
				}
			}
		}
		
		//now collision with skeletons
		for (int j = 0; j < skeletonCount; j++) {
			if (skeleton_x[j] > 0 && !SkeletonIsShot[j]) { //on screen
				if (!(Ghost_x[i] < skeleton_x[j] - ghost_size || Ghost_x[i] > skeleton_x[j] + ghost_size) && !(Ghost_y[i] < skeleton_y[j] - ghost_size || Ghost_y[i] > skeleton_y[j] + ghost_size)) {
					skeleton_x[j] = -1000;
					skeleton_y[j] = -1000;
					Ghost_x[i] = -1000; //both die
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					GhostIsShot[i] = false;
					ActiveEnemies --;
				}
			}
		}
		
		//invisman collision
		for (int j = 0; j < invisibleManCount; j++) {
			if (invisibleMan_x[j] > 0 && !InvisibleManIsShot[j]) {
				if (!(Ghost_x[i] < invisibleMan_x[j] - ghost_size || Ghost_x[i] > invisibleMan_x[j] + ghost_size) && !(Ghost_y[i] < invisibleMan_y[j] - ghost_size || Ghost_y[i] > invisibleMan_y[j] + ghost_size)) {
					invisibleMan_x[j] = -1000;
					invisibleMan_y[j] = -1000;
					Ghost_x[i] = -1000; //both die
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					GhostIsShot[i] = false;
					ActiveEnemies--;
				}
			}
		}
		
		//chelnov collision
		for (int j = 0; j < chelnovCount; j++) {
			if (chelnov_x[j] > 0 && !ChelnovIsShot[j]) {
				if (!(Ghost_x[i] < chelnov_x[j] - ghost_size || Ghost_x[i] > chelnov_x[j] + ghost_size) && !(Ghost_y[i] < chelnov_y[j] - ghost_size || Ghost_y[i] > chelnov_y[j] + ghost_size)) {
					chelnov_x[j] = -1000;
					chelnov_y[j] = -1000;
					Ghost_x[i] = -1000;
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					GhostIsShot[i] = false;
					ActiveEnemies--;
				}
			}
		}
		
		GhostSp[i].setPosition(Ghost_x[i], Ghost_y[i]);
		return;
			
	}	
			
	
	
	
	//vacuum pulling
	float vacuum_start_x, vacuum_start_y;
	
	if (vacuum_x == 1) { //aiming right
	vacuum_start_x = player_x + PlayerWidth; //far right of player png
	} else if (vacuum_x == -1) { //aiming left
	vacuum_start_x = player_x; //far left of player sprite
	} else vacuum_start_x = player_x + PlayerWidth/2; //if aiming up or down, use horizontal center
	
	if (vacuum_y == -1) { //aiming up
	vacuum_start_y = player_y; //top edge
	} else if (vacuum_y == 1) { //aiming down
	vacuum_start_y = player_y + PlayerHeight;
	} else vacuum_start_y = player_y + PlayerHeight/2; //if aiming left or right, use vertical center
	
	//pulling logic
	const float pullspeed = 3;
	if (GhostBeingPulled[i]) {
		
		if (!Keyboard::isKeyPressed(Keyboard::Space)) {
			GhostBeingPulled[i] = false; //stops pulling if let go of space
			return;
		}
		
		float dx = vacuum_start_x - Ghost_x[i]; //horizontal distance
		float dy = vacuum_start_y - Ghost_y[i]; //vertical distance
		if (dx > pullspeed) { //target to the left
			Ghost_x[i] += pullspeed;
		} else if (dx < -pullspeed) { //target to the right
			Ghost_x[i] -= pullspeed;
		} else Ghost_x[i] = vacuum_start_x; //snaps the target to the vacuum to prevent it moving past
		
		if (dy > pullspeed) { //target is up
			Ghost_y[i] += pullspeed;
		} else if (dy < -pullspeed) { //target is down
			Ghost_y[i] -= pullspeed;
		} else Ghost_y[i] = vacuum_start_y; //snaps
		
		//check if capture
		if (Ghost_x[i] == (int)vacuum_start_x && Ghost_y[i] == (int)vacuum_start_y) { //int because ghost_x and ghost_y are integers, woudl alwyas be false with a decimal
			if (captured_count < maxcap) {
				captured_enemies_index[captured_count] = i;
				captured_enemies_type[captured_count] = 0;
				captured_count += 1;
				
				//reset pull and move ghost off camera
				GhostBeingPulled[i] = false;
				Ghost_x[i] = -1000;
				Ghost_y[i] = -1000;
				}
			}
		} 
	else { //if not being pulled, normal patrol
	
	
	
	if (Ghost_x[i]>0) //check if ghost is on screen before checking level, otherwise when ghost gets tped away on suck the game crashes
	{
	
	
	
	
	int grid_x_Ghost=Ghost_x[i]/64;
	int grid_y_Ghost=Ghost_y[i]/64;



	if(!GhostMovingLeft[i]){
		
		
		if(lvl[grid_y_Ghost+1][grid_x_Ghost+1]!='#'||lvl[grid_y_Ghost][grid_x_Ghost+1]=='#'){
			GhostMovingLeft[i]=1;
		}
		else
			if(grid_x_Ghost+1<width-1 ){// prevent right wall colision
				Ghost_x[i]+=1;
			
			}else
				GhostMovingLeft[i]=1;
		
	
	}
	else
	{
	if(GhostMovingLeft[i])

		if(lvl[grid_y_Ghost+1][grid_x_Ghost]!='#'||lvl[grid_y_Ghost][grid_x_Ghost]=='#'){ //for some incredible dumb reason x-1 causes it to not hit the left wall
			GhostMovingLeft[i]=0;
		}
		else
			if(grid_x_Ghost-1>=0 )
			Ghost_x[i]-=1;
			else	
			GhostMovingLeft[i]=0;
		
		

	}
	}
	
	} //end of patrol
	
	GhostSp[i].setPosition(Ghost_x[i],Ghost_y[i]);

	if (!GhostBeingPulled[i] && Ghost_x[i]>0) //disable collision if ghost being pulled or not on screen
	{
	
	if(!(player_x<Ghost_x[i]-50||player_x>Ghost_x[i]+50)&&!(player_y<Ghost_y[i]-32||player_y>Ghost_y[i]+32)) //player collision logic
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);
			lives--;

		}

	GhostSp[i].setTextureRect(IntRect(Frame,0,32,64));//staring x, starting y ,widht,height



	if(FrameCount%120==0)
		Frame+=52;



	
	if(Frame>400)
		Frame=5;


	FrameCount++;
	return;//end of func
	}

}


//same as ghost move just removed the floor detection to make it floaty for level three
void floatingGhost(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap,int &lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[])
{

	static int Frame=5;	
	static int FrameCount=0;
	
	float vacuum_start_x, vacuum_start_y;
	
	if (vacuum_x == 1) { //aiming right
	vacuum_start_x = player_x + PlayerWidth; //far right of player png
	} else if (vacuum_x == -1) { //aiming left
	vacuum_start_x = player_x; //far left of player sprite
	} else vacuum_start_x = player_x + PlayerWidth/2; //if aiming up or down, use horizontal center
	
	if (vacuum_y == -1) { //aiming up
	vacuum_start_y = player_y; //top edge
	} else if (vacuum_y == 1) { //aiming down
	vacuum_start_y = player_y + PlayerHeight;
	} else vacuum_start_y = player_y + PlayerHeight/2; //if aiming left or right, use vertical center
	
	//pulling logic
	const float pullspeed = 3;
	if (GhostBeingPulled[i]) {
		
		if (!Keyboard::isKeyPressed(Keyboard::Space)) {
			GhostBeingPulled[i] = false; //stops pulling if let go of space
			return;
		}
		
		float dx = vacuum_start_x - Ghost_x[i]; //horizontal distance
		float dy = vacuum_start_y - Ghost_y[i]; //vertical distance
		if (dx > pullspeed) { //target to the left
			Ghost_x[i] += pullspeed;
		} else if (dx < -pullspeed) { //target to the right
			Ghost_x[i] -= pullspeed;
		} else Ghost_x[i] = vacuum_start_x; //snaps the target to the vacuum to prevent it moving past
		
		if (dy > pullspeed) { //target is up
			Ghost_y[i] += pullspeed;
		} else if (dy < -pullspeed) { //target is down
			Ghost_y[i] -= pullspeed;
		} else Ghost_y[i] = vacuum_start_y; //snaps
		
		//check if capture
		if (Ghost_x[i] == (int)vacuum_start_x && Ghost_y[i] == (int)vacuum_start_y) { //int because ghost_x and ghost_y are integers, woudl alwyas be false with a decimal
			if (captured_count < maxcap) {
				captured_enemies_index[captured_count] = i;
				captured_enemies_type[captured_count] = 0;
				captured_count += 1;
				
				//reset pull and move ghost off camera
				GhostBeingPulled[i] = false;
				Ghost_x[i] = -1000;
				Ghost_y[i] = -1000;
				}
			}
		} 
	else { //if not being pulled, normal patrol
	
	
	
	if (Ghost_x[i]>0) //check if ghost is on screen before checking level, otherwise when ghost gets tped away on suck the game crashes
	{
	
	
	
	
	int grid_x_Ghost=Ghost_x[i]/64;
	int grid_y_Ghost=Ghost_y[i]/64;



	if(!GhostMovingLeft[i]){
		
		
		if(lvl[grid_y_Ghost][grid_x_Ghost+1]=='#'){
			GhostMovingLeft[i]=1;
		}
		else
			if(grid_x_Ghost+1<width-1 ){// prevent right wall colision
				Ghost_x[i]+=1;
			
			}else
				GhostMovingLeft[i]=1;
		
	
	}
	else
	{
	if(GhostMovingLeft[i])

		if(lvl[grid_y_Ghost][grid_x_Ghost]=='#'){ //for some incredible dumb reason x-1 causes it to not hit the left wall
			GhostMovingLeft[i]=0;
		}
		else
			if(grid_x_Ghost-1>=0 )
			Ghost_x[i]-=1;
			else	
			GhostMovingLeft[i]=0;
		
		

	}
	}
	
	} //end of patrol
	
	GhostSp[i].setPosition(Ghost_x[i],Ghost_y[i]);

	if (!GhostBeingPulled[i] && Ghost_x[i]>0) //disable collision if ghost being pulled or not on screen
	{
	
	if(!(player_x<Ghost_x[i]-50||player_x>Ghost_x[i]+50)&&!(player_y<Ghost_y[i]-32||player_y>Ghost_y[i]+32)) //player collision logic
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);
			lives--;

		}

	GhostSp[i].setTextureRect(IntRect(Frame,0,32,64));//staring x, starting y ,widht,height



	if(FrameCount%120==0)
		Frame+=52;



	
	if(Frame>400)
		Frame=5;


	FrameCount++;
	return;//end of func


}

}

void check_stuck(char** lvl, float& player_x, float& player_y, float& velocityY, int PlayerWidth, int PlayerHeight, int cell_size, int width, int height)

{
    
    int top_y=static_cast<int>(player_y) / cell_size;
    int bottom_y = static_cast<int>(player_y + PlayerHeight) / cell_size;
    int left_x = static_cast<int>(player_x) / cell_size;
    int right_x = static_cast<int>(player_x + PlayerWidth) / cell_size;
    int mid_x = static_cast<int>(player_x + PlayerWidth / 2) / cell_size;
    int mid_y = static_cast<int>(player_y + PlayerHeight / 2) / cell_size;

	//player x and y are in pixels diving by cell_size gives the grid cords



	bool isStuck=true;


	while(isStuck){




		if(lvl[mid_y][mid_x]=='#'||lvl[bottom_y][mid_x]=='#')
		{
			player_y-=2;
		}
		else 
			if(lvl[top_y][mid_x]=='#')
			{

					player_y+=2;


			}else
			{
				isStuck=false;
				break;
			}
			

			return;


	}





}


void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, int& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height, int& vacuum_x, int& vacuum_y)// handle all ingame movement and collision and gun aim
{



	static int frameCount=0;
	static int frame=219;
	int starting_Y_frame=41;
	int Framewidth=33;
	int Frameheight=40;
	
	
	int grid_y=static_cast<int>(player_y+PlayerHeight/2)/cell_size;  
    	
		char top_mid_up1;		
		char top_mid_up2;
		//int top_mid_up=lvl[(static_cast<int>(player_y-cell_size)/cell_size)][static_cast<int>(player_x+PlayerWidth/2)/cell_size];
		char top_left_up1,top_right_up1,top_left_up2,top_right_up2;

		char bottom_mid1;
		char botttom_mid2;





			//calculating 2 places above and below player directly to ensure no ghosting 

			if((static_cast<int>(player_y-cell_size)/cell_size)-2>-1){
				top_mid_up1=lvl[(static_cast<int>(player_y-cell_size)/cell_size)-1][static_cast<int>(player_x+PlayerWidth/2)/cell_size];
				top_mid_up2=lvl[(static_cast<int>((player_y-cell_size)/cell_size)-2)][static_cast<int>(player_x+PlayerWidth/2)/cell_size];
				
				top_left_up1=lvl[(static_cast<int>(player_y-cell_size)/cell_size)-1][static_cast<int>(player_x+PlayerWidth/2)/cell_size-1];
				top_left_up2=lvl[(static_cast<int>((player_y-cell_size)/cell_size)-2)][static_cast<int>(player_x+PlayerWidth/2)/cell_size-1];
				
				top_right_up1=lvl[(static_cast<int>(player_y-cell_size)/cell_size)-1][static_cast<int>(player_x+PlayerWidth/2)/cell_size+1];
				top_right_up2=lvl[(static_cast<int>((player_y-cell_size)/cell_size)-2)][static_cast<int>(player_x+PlayerWidth/2)/cell_size+1];
				
			}




			if((static_cast<int>(player_y-cell_size)/cell_size)+3<height){
				bottom_mid1=lvl[(static_cast<int>(player_y-cell_size)/cell_size)+3][static_cast<int>(player_x+PlayerWidth/2)/cell_size];
				botttom_mid2=lvl[(static_cast<int>(player_y-cell_size)/cell_size)+2][static_cast<int>(player_x+PlayerWidth/2)/cell_size];
			}



			if((Keyboard::isKeyPressed(Keyboard::Up))&&onGround==true){// sometimes gets stuck in the ceilling doesenst always apply downward push

					if(!((top_mid_up1=='#'&&top_mid_up2=='#')/*||(top_left_up1=='#'&&top_left_up2=='#')||(top_right_up1=='#'&&top_right_up2=='#')*/)){
						//i dont remember what this does 
									
							velocityY-=jumpStrength;
							isJumping=true;
					}	
					/*else
					{
						if(top_mid_up!='#')
							velocityY-=jumpStrength;
						else
							velocityY+=jumpStrength;
							isJumping=true;

						}					
				*/
				

				}else if(bottom_mid1=='=') //bounce pad logic
					{	velocityY=jumpStrength+1;// prevents player form shooting up due to some additional 	speed when taking first jump
						velocityY-=jumpStrength*3; //bounce really high 
						
					}
				else
					isJumping=false;
				

				if(velocityY<-jumpStrength*3)// stop excessively high bounce when jumping on bounce pad required for level 3
							velocityY=-jumpStrength*3;

				if(player_y<cell_size)// to stop player when it thouches the roof
					player_y=0;
				if(Keyboard::isKeyPressed(Keyboard::Left)){
				int grid_x = static_cast<int>(player_x+5) / cell_size;
    
					if(lvl[grid_y][grid_x]=='#')
						velocityX=0;
					else{
					//PlayerTexture.loadFromFile("Data/player_left.png");
					//PlayerSprite.setTexture(PlayerTexture);
						velocityX-=speed;
					}
					
				}
				if(Keyboard::isKeyPressed(Keyboard::Right)){
				
				int grid_x=static_cast<int>(player_x+64)/cell_size;
				
				
				
					if(lvl[grid_y][grid_x]=='#')
						velocityX=0;
					else{
					//PlayerTexture.loadFromFile("Data/player_right.png");
					//PlayerSprite.setTexture(PlayerTexture);
						velocityX+=speed;
					}	
					
				}	

				if(Keyboard::isKeyPressed(Keyboard::Down)&&onGround==true){// this doesnt do anything for some reason
						
						if(grid_y<height-2){
							if(!(bottom_mid1=='#'&&botttom_mid2=='#'))
								player_y+=cell_size/2;
						}
					


				}
				


				if(velocityX>terminal_Velocity_x)
					velocityX=terminal_Velocity_x;
				else if(velocityX<-terminal_Velocity_x)
					velocityX=-terminal_Velocity_x;
				 if(!Keyboard::isKeyPressed(Keyboard::Right)&&!Keyboard::isKeyPressed(Keyboard::Left))
					velocityX*=friction;


				player_x+=velocityX;





				counter=counter>8?1:counter;
				


				
			if (Keyboard::isKeyPressed(Keyboard::W)){
				vacuum_y = -1; //aims up (array going up)
				vacuum_x = 0;
			} else if (Keyboard::isKeyPressed(Keyboard::S)){
				vacuum_y = 1; //aims down
				vacuum_x = 0;
			} else if (Keyboard::isKeyPressed(Keyboard::A)){
				vacuum_y = 0; //aims left
				vacuum_x = -1;
			} else if (Keyboard::isKeyPressed(Keyboard::D)){
				vacuum_y = 0; //aims right
				vacuum_x = 1;
			}				
						
				
				

			
				
					if(velocityX<-1){
						PlayerSprite.setTextureRect(IntRect(frame,starting_Y_frame,Framewidth,Frameheight));//starting x starting y widht height
						PlayerSprite.setScale( 2.5,2.5);
						PlayerSprite.setOrigin(0,0);				
					}else
					if(velocityX>1)
					{
						PlayerSprite.setTextureRect(IntRect(frame,starting_Y_frame,Framewidth,Frameheight));//starting x starting y widht height
						PlayerSprite.setScale(-2.5,2.5);
						PlayerSprite.setOrigin(32,0);
						
					}
					else
					{
						if(velocityX<0) //cuz velocity is very rarely zero cuz friction can use this to estimate the direction being faced
						{
							
							PlayerSprite.setTextureRect(IntRect(15,starting_Y_frame,Framewidth,Frameheight));//starting x starting y widht height
							PlayerSprite.setScale( 2.5,2.5);
							PlayerSprite.setOrigin(0,0);
						}
						else
						{ 
							PlayerSprite.setTextureRect(IntRect(15,starting_Y_frame,Framewidth,Frameheight));//starting x starting y widht height
							PlayerSprite.setScale( -2.5,2.5);
							PlayerSprite.setOrigin(32,0);
						}
						}
					
						
				if(velocityY>1||velocityY<-1){
					PlayerSprite.setTextureRect(IntRect(524,30,Framewidth,Frameheight));//starting x starting y widht height

				}

				frameCount++;

		
				if(frameCount%20==0){
						frame+=Framewidth;
					//cout<<"OnGround is"<<onGround;
					//cout<<"Added to player Frame";
				}

				if(frame>350)
				{
					//cout<<"Frame greater than 350";
					frame=219;
				}

				

				return;

}


void level_one(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]) {

	//declare the border


	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){


			if(i==0||i==height-1||j==0||j==width-1)
				lvl[i][j]='#';


			if(i==3&&(j>2&&j<width-3))
					lvl[i][j]='#';


			  if(((i>3 && i<=5)||(i>8 && i<11))&&(j==(width/2)||j==((width/2)-1)) )
    				lvl[i][j] = '#';

			if(((i==5||i==height-6 )&&(( (j>0&&j<=3) || (j>width-5))||(j==(width/2-2)||j==(width/2+1)) )))
				lvl[i][j] ='#';

			if(i>5&&i<10 &&(j==(width/2-2)||j==(width/2+1)))
				lvl[i][j] ='#';
				
				
			if(i==height-4&&(j>2&&j<width-3))
					lvl[i][j]='#';
					
			if( (i==height-8) && ((j>2&&j<8)||(j<width-3&&j>10)))
					lvl[i][j]='#';
					
					
						
						
		
		}
	}

	
	const int skeletonCount=4;
	const int GhostCount=8;
	const int invisibleManCount=3;
	const int chelnovCount = 4;
	
	static Sprite GhostSp[GhostCount];
	static Texture GhostTx;
	GhostTx.loadFromFile("Data/Ghost.png");
	
	static int Ghost_y[GhostCount];
	static int Ghost_x[GhostCount];
	static bool GhostMovingLeft[GhostCount];
	static bool GhostBeingPulled[GhostCount] = {0};
	static bool SkeletonBeingPulled[skeletonCount] = {0}; //added
	
	static int invisibleMan_x[invisibleManCount];
	static int invisibleMan_y[invisibleManCount];
	
	static int chelnov_x[chelnovCount];
	static int chelnov_y[chelnovCount];
	
	
	
	
	static int currentSkeleton=0;
	static bool posChangeHappened[skeletonCount]={0};
	static int FramePosForChange[skeletonCount]={0};

	static Sprite skeletonSp[skeletonCount];
	static Texture skeletonTx;
	if(FirstRun)
	skeletonTx.loadFromFile("Data/skeleton.png");
	


	static bool skeletonJumping[skeletonCount]={0};
	static float skeleton_yVelocity[skeletonCount]={0};
	static int skeleton_y[skeletonCount];
	static int skeleton_x[skeletonCount];
	static bool skeletonMovingLeft[skeletonCount];
	static bool skeletonIdle[skeletonCount]={0};
	static int jumpCoolDown[skeletonCount]={0};

	//power up variables
		static bool power_on=false;// if power up is active 
		static bool powerPlaced =false;// if power up is on stage
		static int power_x;// where is power up 
		static int power_y;//``
		static int power_select=0;// whichh power up
		static int prevlife=lives;// to keep track if player dies prevlife will become > life, for removepower
		static int enemy_x=128;
		static int enemy_y=128;

	// power up sprite
		static Texture texpower;
		static Sprite power;
 
	if(FirstRun){	
			
		lives=3;// resetting lives at level start, metioned in rubrics

		for(int i=0;i<GhostCount;i++)
		{
		
			Ghost_x[i]=150;
			Ghost_y[i]=(i+1)*64;
			GhostSp[i].setTexture(GhostTx);
			GhostSp[i].setTextureRect(IntRect(5,5,32,32));	
			int temp=rand();
			
			if(temp%2==0){
			
				GhostMovingLeft[i]=0;
			}else
				GhostMovingLeft[i]=1;


			//setting the ghost 1 3 5 7
			GhostSp[i].setPosition(Ghost_y[i],Ghost_x[i]);
			GhostSp[i].setScale(2,2);
		}	
			Ghost_x[0]=16*64;
			Ghost_y[0]=4*64;
			
			Ghost_x[2]=11*64;
			Ghost_y[2]=6*64;

			Ghost_x[4]=10*64;
			Ghost_y[4]=10*64;

			Ghost_x[6]=16*64;
			Ghost_y[6]=8*64;


				
		for(int i=0;i<skeletonCount;i++)
		{

			skeleton_x[i]=150;
			skeleton_y[i]=(i+1)*64;
			skeletonSp[i].setTexture(skeletonTx);
			skeletonSp[i].setTextureRect(IntRect(8,0,32,110));
			int temp=rand();
			if(temp%2==0)
				skeletonMovingLeft[i]=0;
			else
				skeletonMovingLeft[i]=1;


			//setting the skeleton 1 3 5 7
			
		}	
			skeleton_x[0]=16*64;
			skeleton_y[0]=(4*64);
			
			skeleton_x[2]=11*64;
			skeleton_y[2]=6*64;

		/*	skeleton_x[4]=10*64;
			skeleton_y[4]=10*64;

			skeleton_x[6]=16*64;
			skeleton_y[6]=8*64;
		*/

		for(int i=0;i<skeletonCount;i++){ //place the skeletons so that they are on top of the blocks and not below them


			skeleton_y[i]-=45;
			skeletonSp[i].setPosition(skeleton_x[i],skeleton_y[i]);
			skeletonSp[i].setScale(2,2);

		}

		for(int i=0; i<invisibleManCount; i++) {
             invisibleMan_x[i] = -1000; // Move offscreen
             invisibleMan_y[i] = -1000;
        }
			
	} //set the postions of the ghosts and skeletons for the first run

	//power up functions
	if(FirstRun && !power_on)// first run to be replaced by triple kill condition 
	powerPlaced = power_deploy( enemy_x, enemy_y, power_x, power_y, width , height, power_select);//power up selection and deployment ok
	
	if(powerPlaced)
	{power_display(power_x,power_y,texpower, power, power_select );
	power_on = power_up(power_x, power_y, player_x, player_y, PlayerWidth, PlayerHeight, powerPlaced, power_select, speed, lives, vacuum_range, vacuum_width,prevlife);
	}
	//removing power
	if(power_on && lives < prevlife)//power active and life decreased 
	power_on = remove_power(power_select, speed, lives, vacuum_range, vacuum_width);//

	





	playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y);
	check_stuck(lvl, player_x,  player_y, velocityY,  PlayerWidth, PlayerHeight,  cell_size,  width,  height);
	vacuum_suck(player_x, player_y,  PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range,  vacuum_width, captured_enemies_index,  captured_count,  Ghost_x, Ghost_y,  8, GhostBeingPulled,FirstRun,window, captured_enemies_type);//replcaed num_ghosts with 8 for testing 
	vacuum_suck(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range, vacuum_width, captured_enemies_index, captured_count, skeleton_x, skeleton_y, 4, SkeletonBeingPulled,FirstRun,window, captured_enemies_type); //ran for skeleton pull, 4 skellies
	singleShot(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, captured_enemies_index, captured_enemies_type, captured_count, Ghost_x, Ghost_y, GhostShotVelX, GhostShotVelY, skeleton_x, skeleton_y, SkeletonShotVelX, SkeletonShotVelY, invisibleMan_x, invisibleMan_y, InvisibleManShotVelX, InvisibleManShotVelY, chelnov_x, chelnov_y, chelnovShotVelX, chelnovShotVelY);

	//moving enemies
	for(int i=0;i<GhostCount;i++){
	  ghostMove(Ghost_x, Ghost_y, width, GhostSp, GhostMovingLeft, i, player_x, player_y, lvl, PlayerSprite, cell_size, PlayerHeight, height, GhostBeingPulled, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, captured_enemies_type, GhostShotVelX, GhostShotVelY, GhostBounceCount, ActiveEnemies, skeleton_x, skeleton_y, skeletonCount, invisibleMan_x, invisibleMan_y, invisibleManCount, GhostCount, chelnov_x, chelnov_y, chelnovCount, chelnovShotVelX, chelnovShotVelY, GhostIsShot, SkeletonIsShot, InvisibleManIsShot, ChelnovIsShot);
	}

	for(int i=0;i<skeletonCount;i++)
	{
 skeletonMove(skeleton_x, skeleton_y, width, skeletonSp, skeletonMovingLeft, i, player_x, player_y,lvl,PlayerSprite, cell_size, PlayerHeight, height,skeletonIdle, lives,  skeletonCount,  currentSkeleton,  posChangeHappened, FramePosForChange, FirstRun,skeletonJumping,jumpCoolDown, SkeletonBeingPulled,captured_enemies_index, captured_count, PlayerWidth,vacuum_x, vacuum_y, maxcap, captured_enemies_type, SkeletonShotVelX, SkeletonShotVelY, SkeletonBounceCount, ActiveEnemies, Ghost_x, Ghost_y, GhostCount, GhostShotVelX, GhostShotVelY, invisibleMan_x, invisibleMan_y, invisibleManCount, InvisibleManShotVelX, InvisibleManShotVelY, chelnov_x, chelnov_y, chelnovCount, chelnovShotVelX, chelnovShotVelY, GhostIsShot, SkeletonIsShot, InvisibleManIsShot, ChelnovIsShot);




	}






	//printing enemies to screen
	for(int i=0;i<GhostCount;i++){
			window.draw(GhostSp[i]);
			
			//window.draw(invisibleManSp[i]);
		}
	
	for(int i=0;i<skeletonCount;i++)
	{
		window.draw(skeletonSp[i]);
	}

	if(powerPlaced)//draw only if not power on
	window.draw(power);
}


void level_two(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], float chelnovShotVelX[], float chelnovShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, int chelnovBounceCount[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[])
{
	if(FirstRun){

					lives=3;//resetting lives at level start





			for(int i=0;i<width;i++)
			{
					for(int j=0;j<height;j++){
						lvl[i][j]==' ';
					}
			} //clear array for new level
				







		for(int i=0;i<height;i++){

			for(int j=0;j<width;j++)



			{



				if(i==0||i==height-1||j==0||j==width-1)	// border 
					lvl[i][j]='#';

				
				if((i==3 && (j<4||(j>6&&j<width-3)))) //row 1
					lvl[i][j]='#';

				if(i==4 && (j>2&&j<5)) //row 2 start of stair case
					lvl[i][j]='#';

				if(i==5 && ((j>3&&j<6) || j==1||(j>width-5) || (j>9&&j<width-5)   ))
					lvl[i][j]='#';

				if(i==6 && (j>4&&j<7))
					lvl[i][j]='#';

				if(i==7 && ((j>5&&j<8) || (j<3) || (j<width-3&&j>=width-7) ))
					lvl[i][j]='#';

				if(i==8 && ((j>6&&j<9)))
					lvl[i][j]='#';
				
				if(i==9 && ((j>7&&j<10) || (j<5) || (j>width-6)))
					lvl[i][j]='#';
				
				if(i==10 && ((j>8&&j<11)))
					lvl[i][j]='#';
				if(i==11 && ( j>9&&j<13 || (j<7) ))
					lvl[i][j]='#';



			}
		}//draw level if first run
	}


	//number of enemies for the lvl
	const int GhostCount=4;
	const int skeletonCount=9;
	const int invisibleManCount=3;
	const int chelnovCount=4;


	//for vacc
	static bool GhostBeingPulled[GhostCount] = {0};
	static bool SkeletonBeingPulled[skeletonCount] = {0};
	static bool invisibleManBeingPulled[invisibleManCount] = {0};
	static bool chelnovBeingPulled[chelnovCount] = {0};





	//define the Ghost
	static Sprite GhostSp[GhostCount];
	static Texture GhostTx;
	GhostTx.loadFromFile("Data/Ghost.png");
	
	static int Ghost_y[GhostCount];
	static int Ghost_x[GhostCount];
	static bool GhostMovingLeft[GhostCount];
	//define the Ghost




	//define the skels
	
	static int currentSkeleton=0;
	static bool posChangeHappenedSkel[skeletonCount]={0};
	static int FramePosForChangeSkel[skeletonCount]={0};

	static Sprite skeletonSp[skeletonCount];
	static Texture skeletonTx;
	if(FirstRun)
	skeletonTx.loadFromFile("Data/skeleton.png");
	


	static bool skeletonJumping[skeletonCount]={0};
	static float skeleton_yVelocity[skeletonCount]={0};
	static int skeleton_y[skeletonCount];
	static int skeleton_x[skeletonCount];
	static bool skeletonMovingLeft[skeletonCount];
	static bool skeletonIdle[skeletonCount]={0};
	static int jumpCoolDownSkel[skeletonCount]={0};
 


	//define the skels



	//define the invis men
	static bool posChangeHappenedInvisible[invisibleManCount]={0};
	static int FramePosForChangeInvisible[invisibleManCount]={0};

	static Sprite invisibleManSp[invisibleManCount];
	static Texture invisibleManTx;

		// variable for powerups
		static bool power_on=false;// if power up is active 
		static bool powerPlaced =false;// if power up is on stage
		static int power_x;// where is power up 
		static int power_y;//``
		static int power_select=0;// whichh power up
		static int prevlife=lives;// to keep track if player dies prevlife will become > life, for removepower
		static int enemy_x=128;//dumy values
		static int enemy_y=128;
		// power up sprite
		static Texture texpower;
		static Sprite power;


	if(FirstRun)
	invisibleManTx.loadFromFile("Data/invisibleMan.png");
	
	int currentInvibleMan=1;
	static bool invisibleManJumping[invisibleManCount]={0};
	static float invisibleMan_yVelocity[invisibleManCount]={0};
	static int invisibleMan_y[invisibleManCount];
	static int invisibleMan_x[invisibleManCount];
	static bool invisibleManMovingLeft[invisibleManCount];
	static bool invisibleManIdle[invisibleManCount]={0};
	static int jumpCoolDownInvisible[invisibleManCount]={0};

	//define the invis men



	//define the chels (ha portal reference)


	static int currentchelnov=0;
	static bool posChangeHappenedChelnov[chelnovCount]={0};
	static int FramePosForChangeChelnov[chelnovCount]={0};

	static Sprite chelnovSp[chelnovCount];
	static Texture chelnovTx;
	if(FirstRun)
	chelnovTx.loadFromFile("Data/chelnov.png");
	


	static bool chelnovJumping[chelnovCount]={0};
	static float chelnov_yVelocity[chelnovCount]={0};
	static int chelnov_y[chelnovCount];
	static int chelnov_x[chelnovCount];
	static bool chelnovMovingLeft[chelnovCount];
	static bool chelnovIdle[chelnovCount]={0};
	static int jumpCoolDownChelnov[chelnovCount]={0};

	//define chels





	if(FirstRun){
		for(int i=0;i<invisibleManCount;i++)
		{

			invisibleMan_x[i]=150;
			invisibleMan_y[i]=(i+1)*64;
			invisibleManSp[i].setTexture(invisibleManTx);
			invisibleManSp[i].setTextureRect(IntRect(8,0,32,110));
			int temp=rand();
			if(temp%2==0)
				invisibleManMovingLeft[i]=0;
			else
				invisibleManMovingLeft[i]=1;


			//setting the invisibleMan 1 3 5 7
			
		}	
			invisibleMan_x[0]=16*64;
			invisibleMan_y[0]=(4*64);
			
			invisibleMan_x[2]=11*64;
			invisibleMan_y[2]=6*64;

		for(int i=0;i<invisibleManCount;i++){

			invisibleMan_y[i]-=15;
			invisibleManSp[i].setPosition(invisibleMan_x[i],invisibleMan_y[i]);
			invisibleManSp[i].setScale(2,2);

		}




	for(int i=0;i<chelnovCount;i++)
		{

			chelnov_x[i]=150;
			chelnov_y[i]=(i+1)*64;
			chelnovSp[i].setTexture(chelnovTx);
			chelnovSp[i].setTextureRect(IntRect(11,5,32,45));
			int temp=rand();
			if(temp%2==0)
				chelnovMovingLeft[i]=0;
			else
				chelnovMovingLeft[i]=1;


			//setting the chelnov 1 3 5 7
			
		}	
			chelnov_x[0]=16*64;
			chelnov_y[0]=(4*64);
			
			chelnov_x[2]=11*64;
			chelnov_y[2]=6*64;

		for(int i=0;i<chelnovCount;i++){

			chelnov_y[i]+=15;
			chelnovSp[i].setPosition(chelnov_x[i],chelnov_y[i]);
			chelnovSp[i].setScale(2,2);

		}








	}

















	//power up functions
	if(FirstRun && !power_on)// first run to be replaced by triple kill condition 
	powerPlaced = power_deploy( enemy_x,enemy_y, power_x, power_y, width , height, power_select);//power up selection and deployment ok
	
	if(powerPlaced)
	{
		power_display(power_x,power_y,texpower, power, power_select );

		power_on = power_up(power_x, power_y, player_x, player_y, PlayerWidth, PlayerHeight, powerPlaced, power_select, speed, lives, vacuum_range, vacuum_width,prevlife);
	}
	//removing power
	if(power_on && lives < prevlife)//power active and life decreased 
	power_on = remove_power(power_select, speed, lives, vacuum_range, vacuum_width);//

	



	playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y);
	check_stuck(lvl, player_x,  player_y, velocityY,  PlayerWidth, PlayerHeight,  cell_size,  width,  height);
	vacuum_suck(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range, vacuum_width, captured_enemies_index, captured_count, chelnov_x, chelnov_y, chelnovCount, chelnovBeingPulled, FirstRun, window, captured_enemies_type);
	vacuum_suck(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range, vacuum_width, captured_enemies_index, captured_count, invisibleMan_x, invisibleMan_y, invisibleManCount, invisibleManBeingPulled, FirstRun, window, captured_enemies_type);
	singleShot(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, captured_enemies_index, captured_enemies_type, captured_count, Ghost_x, Ghost_y, GhostShotVelX, GhostShotVelY, skeleton_x, skeleton_y, SkeletonShotVelX, SkeletonShotVelY, invisibleMan_x, invisibleMan_y, InvisibleManShotVelX, InvisibleManShotVelY, chelnov_x, chelnov_y, chelnovShotVelX, chelnovShotVelY);
	





	for(int i=0;i<invisibleManCount;i++){
		invisibleManMove( invisibleMan_x, invisibleMan_y, width, invisibleManSp, invisibleManMovingLeft, i, player_x, player_y,lvl,PlayerSprite, cell_size,PlayerHeight, height, invisibleManIdle, lives, invisibleManCount,  currentInvibleMan,  posChangeHappenedInvisible,  FramePosForChangeInvisible, FirstRun, invisibleManJumping, jumpCoolDownInvisible, invisibleManBeingPulled,  captured_enemies_index,  captured_count,  PlayerWidth,  vacuum_x,  vacuum_y,  maxcap, captured_enemies_type, InvisibleManShotVelX, InvisibleManShotVelY, InvisibleManBounceCount, ActiveEnemies, Ghost_x, Ghost_y, GhostCount, GhostShotVelX, GhostShotVelY, skeleton_x, skeleton_y, skeletonCount, SkeletonShotVelX, SkeletonShotVelY, chelnov_x, chelnov_y, chelnovCount, chelnovShotVelX, chelnovShotVelY, GhostIsShot, SkeletonIsShot, InvisibleManIsShot, ChelnovIsShot);	 

	}


	for (int i = 0; i < chelnovCount; i++) {
        chelnovMove(chelnov_x, chelnov_y, width, chelnovSp, chelnovMovingLeft, i, player_x, player_y, lvl, PlayerSprite, cell_size, PlayerHeight, height, chelnovIdle, lives, chelnovCount, currentchelnov, posChangeHappenedChelnov, FramePosForChangeChelnov, FirstRun, chelnovJumping, jumpCoolDownChelnov, chelnovBeingPulled, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, captured_enemies_type, chelnovShotVelX, chelnovShotVelY, chelnovBounceCount, ActiveEnemies, Ghost_x, Ghost_y, GhostCount, GhostShotVelX, GhostShotVelY, skeleton_x, skeleton_y, skeletonCount, SkeletonShotVelX, SkeletonShotVelY, invisibleMan_x, invisibleMan_y, invisibleManCount, InvisibleManShotVelX, InvisibleManShotVelY, GhostIsShot, SkeletonIsShot, InvisibleManIsShot, ChelnovIsShot);
    }


	for(int i=0;i<invisibleManCount;i++){
		window.draw(chelnovSp[i]);
		window.draw(invisibleManSp[i]);
	}
	if(powerPlaced)
	window.draw(power);
}

void level_three(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[])
{	// Planned to make it extra hard but left some room for player to breath
	// level design

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i==0||j==0||j==width-1 || i==height-1 && (j<3 || j>width-4))//frame designed
			{
				lvl[i][j]='#';
			}
			else if(i==height-1 && (j>2 && j<width-3))
			{
				lvl[i][j]='=';// = refers to bounce tiles
			}
		}
	}



	const int GhostCount=5;
	static Sprite GhostSp[GhostCount];
	static Texture GhostTx;
	GhostTx.loadFromFile("Data/Ghost.png");
	
	static int Ghost_y[GhostCount];
	static int Ghost_x[GhostCount];
	static bool GhostMovingLeft[GhostCount];
	static bool GhostBeingPulled[GhostCount] = {0};
	int level_speed=speed*2;// i am not that cruel so give this edge to the player

	//deployng ghosts at random positions
	if(FirstRun){	
			
		lives=3;// resetting lives at level start, metioned in rubrics

		for(int i=0;i<GhostCount;i++)
		{
		
			Ghost_x[i]=rand()% (width*64-128 +1)+64;// depley gost at random x positions formula: ((max -64)-(min+64)+1) + (min +64) 
			Ghost_y[i]=(i+5)*64;//ghost in mid
			GhostSp[i].setTexture(GhostTx);
			GhostSp[i].setTextureRect(IntRect(5,5,32,32));	
			int temp=rand();
			
			if(temp%2==0){
			
				GhostMovingLeft[i]=0;
			}else
				GhostMovingLeft[i]=1;


			//setting the ghost 1 3 5 7
			GhostSp[i].setPosition(Ghost_y[i],Ghost_x[i]);
			GhostSp[i].setScale(2,2);
		}


	}



	playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, level_speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y);
	vacuum_suck(player_x, player_y,  PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range,  vacuum_width, captured_enemies_index,  captured_count,  Ghost_x, Ghost_y,  8, GhostBeingPulled,FirstRun,window, captured_enemies_type);
	
	// adding ghost movement
	for(int i=0;i<GhostCount;i++)
	{
	  floatingGhost(Ghost_x, Ghost_y, width, GhostSp, GhostMovingLeft, i, player_x, player_y, lvl, PlayerSprite, cell_size, PlayerHeight, height, GhostBeingPulled, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, captured_enemies_type, GhostShotVelX, GhostShotVelY, GhostBounceCount);
	}









	// draw ghosts
	for(int i=0;i<GhostCount;i++)
		window.draw(GhostSp[i]);
			
		
}


void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size)
{
	window.draw(bgSprite);

	for (int i=0;i<height;i+=1)
	{
		for (int j=0;j<width;j+=1)
		{

			if (lvl[i][j] == '#'|| lvl[i][j]=='=') // bounce(=) and fixed tiles(#)
			{
				blockSprite.setPosition(j*cell_size,(i* (cell_size)+cell_size/2));//so player appears on top of blocks
				window.draw(blockSprite);
			}
		}
	}

}

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth)

{

	offset_y=player_y;

	offset_y+=velocityY;

	char bottom_left_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x ) / cell_size];
	char bottom_right_down = lvl[(int)(offset_y  + Pheight) / cell_size][(int)(player_x + Pwidth) / cell_size];
	char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth / 2) / cell_size];

	if (/*bottom_left_down == '#' ||*/ (bottom_mid_down =='=' || bottom_mid_down == '#') &&velocityY>=0/*|| bottom_right_down == '#'*/) //making falling more precise 
	{
		onGround = true;
		
		
	}
	/*else if (bottom_mid_down == '=' && velocityY>=0) //bounce block
	{
		velocityY -=(velocityY * 0.7); //bounce effect        
		onGround = false; //not on ground after bounce
	}*/
	else
	{




		if(!(player_y+velocityY<cell_size))
		player_y = offset_y;
		
		onGround = false;
	}

	if (!onGround)
	{
		velocityY += gravity;
		
		if (velocityY >= terminal_Velocity) velocityY = terminal_Velocity;
	}

	else
	{
		velocityY = 0;
	}

	//char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth / 2) / cell_size]; //get the center of the player

	
}

void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool skeletonIdle[],int & lives,const int skeletonCount, int currentSkeleton, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool skeletonJumping[],int jumpCoolDown[], bool SkeletonBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float SkeletonShotVelX[], float SkeletonShotVelY[], int SkeletonBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[])
{
	
    static int Frame=192;    //has to be at start or scope errors l8r
    static bool jumpingUp=0;
    static int FrameCount=0;
    
    int grid_x_skeleton=skeleton_x[i]/64;
    int grid_y_skeleton=(skeleton_y[i]+45)/64;
    if((skeleton_y[i]+45)<height)
    	grid_y_skeleton=(skeleton_y[i]+45)/64;
    static int currentIdleFrame[3]={0};
    int IdleFramepos[3]={59,111,149};
    static int Jumping_x=0,Jumping_y=0;
    int JumpingFramePos=727;
    static float dest_x[20]={0};
    static float dest_y[20]={0};
    static bool isMoving[20]={0};

	


	if (SkeletonShotVelX[i] != 0 || SkeletonShotVelY[i] != 0) { //movement for shot
		SkeletonIsShot[i] = true;
		
		int next_x = skeleton_x[i] + (int)SkeletonShotVelX[i]; //x movemnet
		
		int gridX = next_x / cell_size; //coords
		int gridY = skeleton_y[i] / cell_size;
		
		
		if (next_x <= 0 || next_x >= (width - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) 
		{ //if left or right border or hitting a platform
			SkeletonShotVelX[i] = -SkeletonShotVelX[i]; //reverse X direction, bounce
			SkeletonBounceCount[i]++;
		}
		else skeleton_x[i] = next_x;
		
		//y movement
		SkeletonShotVelY[i] += 1; //gravity is 1, too annoying to pass in fn
		if (SkeletonShotVelY[i] > 20) 
			SkeletonShotVelY[i] = 20; //terminal velocity clamp
		
		int next_y = skeleton_y[i] + (int)SkeletonShotVelY[i];
		gridX = skeleton_x[i] / cell_size; //uses updated x position
		gridY = next_y / cell_size;
		
		if (next_y <= 0 || next_y >= (height - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#'))
		{ //if hit top and bottom border or platforms
			if (SkeletonShotVelY[i] > 0) { //if moving down
				SkeletonShotVelY[i] = 0; //stop falling
				if (gridY < height) 
					skeleton_y[i] = (gridY - 1) * cell_size;
				if (SkeletonShotVelX[i] == 0) {//if fell striagght down choose random directin t roll to
					if (rand() % 2 == 0)
						SkeletonShotVelX[i] = 15; //right
					else SkeletonShotVelX[i] = -15; //left
					}
				}
				
			else if (SkeletonShotVelY[i] < 0) { //moving up
				SkeletonShotVelY[i] = 0;
				if (SkeletonShotVelX[i] == 0) { //no vertical movemnt, same random logic
				if (rand() % 2 == 0)
						SkeletonShotVelX[i] = 15; //right
					else SkeletonShotVelX[i] = -15; //left
					}
				}
				
		} //if not hitting platforms
		else skeleton_y[i] = next_y;
		
		if (SkeletonBounceCount[i] >= 5) {
			SkeletonShotVelX[i] = 0;
			SkeletonShotVelY[i] = 0;
			skeleton_x[i] = -1000;
			skeleton_y[i] = -1000;
			SkeletonIsShot[i] = false;
			ActiveEnemies--;
		}
		
		int skeleton_size = 64;
		for (int j = 0; j < GhostCount; j++) {
			if (Ghost_x[j] > 0 && !GhostIsShot[j]) { //doesnt check off screen ghosts
				if (!(skeleton_x[i] < Ghost_x[j] - skeleton_size || skeleton_x[i] > Ghost_x[j] + skeleton_size) && !(skeleton_y[i] < Ghost_y[j] - skeleton_size || skeleton_y[i] > Ghost_y[j] + skeleton_size)) {
					Ghost_x[j] = -1000; //both die
					Ghost_y[j] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					SkeletonIsShot[i] = false;
					skeleton_x[i] = -1000;
					skeleton_y[i] = -1000;
					
					ActiveEnemies --;
				}
			}
		}
		
		//now collision with other skeletons
		for (int j = 0; j < skeletonCount; j++) {
			if (j!= i && skeleton_x[j] > 0 && !(SkeletonIsShot[i] && SkeletonIsShot[j])) { //on screen
				if (!(skeleton_x[i] < skeleton_x[j] - skeleton_size || skeleton_x[i] > skeleton_x[j] + skeleton_size) && !(skeleton_y[i] < skeleton_y[j] - skeleton_size || skeleton_y[i] > skeleton_y[j] + skeleton_size)) {
					skeleton_x[j] = -1000;
					skeleton_y[j] = -1000;
					skeleton_x[i] = -1000; //both die
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					SkeletonIsShot[i] = false;
					ActiveEnemies --;
				}
			}
		}
		
		//invisman collision
		for (int j = 0; j < invisibleManCount; j++) {
			if (invisibleMan_x[j] > 0 && !InvisibleManIsShot[j]) {
				if (!(skeleton_x[i] < invisibleMan_x[j] - skeleton_size || skeleton_x[i] > invisibleMan_x[j] + skeleton_size) && !(skeleton_y[i] < invisibleMan_y[j] - skeleton_size || skeleton_y[i] > invisibleMan_y[j] + skeleton_size)) {
					invisibleMan_x[j] = -1000;
					invisibleMan_y[j] = -1000;
					skeleton_x[i] = -1000; //both die
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					SkeletonIsShot[i] = false;
					ActiveEnemies--;
				}
			}
		}
		
		//chelnov collision
		for (int j = 0; j < chelnovCount; j++) {
			if (chelnov_x[j] > 0 && !ChelnovIsShot[j]) {
				if (!(skeleton_x[i] < chelnov_x[j] - skeleton_size || skeleton_x[i] > chelnov_x[j] + skeleton_size) && !(skeleton_y[i] < chelnov_y[j] - skeleton_size || skeleton_y[i] > chelnov_y[j] + skeleton_size)) {
					chelnov_x[j] = -1000;
					chelnov_y[j] = -1000;
					skeleton_x[i] = -1000;
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					SkeletonIsShot[i] = false;
					ActiveEnemies--;
				}
			}
		}
		
		
		skeletonSp[i].setPosition(skeleton_x[i], skeleton_y[i]);
		return;
			
	}
		
	
	
	
	
	
	
    
    
    //cout<<i<<endl;
    
    
    
    
    
    float vacuum_start_x, vacuum_start_y; //same pulling system as ghost
    if (vacuum_x == 1) { //aiming right
    vacuum_start_x = player_x + PlayerWidth; //far right of player png
    } else if (vacuum_x == -1) { //aiming left
    vacuum_start_x = player_x; //far left of player sprite
    } else vacuum_start_x = player_x + PlayerWidth/2; //if aiming up or down, use horizontal center
    
    if (vacuum_y == -1) { //aiming up
    vacuum_start_y = player_y; //top edge
    } else if (vacuum_y == 1) { //aiming down
    vacuum_start_y = player_y + PlayerHeight;
    } else vacuum_start_y = player_y + PlayerHeight/2; //if aiming left or right, use vertical center
    
    const float pullspeed = 3;
    if (SkeletonBeingPulled[i]) {
        
        if (!Keyboard::isKeyPressed(Keyboard::Space)) {
            SkeletonBeingPulled[i] = false; //stops pulling if let go of space
            return;
        }
        
        float dx = vacuum_start_x - skeleton_x[i]; //horizontal distance
        float dy = vacuum_start_y - skeleton_y[i]; //vertical distance
        if (dx > pullspeed) { //target to the left
            skeleton_x[i] += pullspeed;
        } else if (dx < -pullspeed) { //target to the right
        skeleton_x[i] -= pullspeed;
        } else skeleton_x[i] = vacuum_start_x; //snaps to vacuum otherwise it goes past
        
        if (dy > pullspeed) { //target is up
        	skeleton_y[i] += pullspeed;
        } else if (dy < -pullspeed) { //target is down
        	skeleton_y[i] -= pullspeed;
        } else skeleton_y[i] = vacuum_start_y; //snaps
        
        //check if capture
        if (skeleton_x[i] == (int)vacuum_start_x && skeleton_y[i] == (int)vacuum_start_y) { 
            if (captured_count < maxcap) {
                captured_enemies_index[captured_count] = i;
                captured_enemies_type[captured_count] = 1;
                captured_count ++;
                ActiveEnemies--;
                
                //reset pull and move ghost off camera
                SkeletonBeingPulled[i] = false;
                skeleton_x[i] = -1000;
                skeleton_y[i] = -1000;
            }
        }
        skeletonSp[i].setPosition(skeleton_x[i], skeleton_y[i]);
        return; 
    } 
    else { //normal patrol if not being pulled
    
        if (skeleton_x[i] > 0) { //only runs if on screen
    



	//first calculate if the skeleton is moving if not then find jumping destination 
	//after valid jump spot is found set moving to 1
	//when moving is 1 move skel 10 pxs every frame till reaches jump spot

    if(skeletonJumping[i])
    {

        if(!isMoving[i])
        {
             bool foundSpot = false;

            if(jumpingUp)
            {
                //jumping up

                for(int skelheight=Jumping_y-2;skelheight>Jumping_y-5&&skelheight>0 && skeletonJumping[i]==1;skelheight--) //check 5 rows above dont check above index 1
                {
                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) //check 5 cols above 2 on each side on above
                        {
                            if(lvl[skelheight][row]=='#'){
                                cout<<skelheight<<endl<<row<<endl;
                                dest_x[i]=row*cell_size;
                                dest_y[i]=((skelheight-1)*cell_size)-(cell_size/2)-4;
                                cout<<"skeleton jumped to "<<skeleton_x[i]<<" and "<<skeleton_y[i];
                                // int temp;
                                // cin>>temp;
                                foundSpot=true;
                                break;
                            }
                        
                        }
                    if(foundSpot) break;
                }

            }
            
            else{

                //jumping down
                // cout<<"jumped donwn"<<endl;

                for(int skelheight=Jumping_y+3;skelheight<Jumping_y+7&&skelheight<height-1 && skeletonJumping[i]==1;skelheight++) //check 5 rows above dont check above index 1
                {
                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) //check 5 cols above 2 on each side on above
                        {
                            if(lvl[skelheight][row]=='#'){
                                cout<<skelheight<<endl<<row<<endl;
                                // cout<<"Valid Spot found";
                                // int temp;
                                // cin>>temp;
                                dest_x[i]=row*cell_size;
                                dest_y[i]=((skelheight-1)*cell_size)-(cell_size/2)-4;
                                cout<<"skeleton jumped to "<<skeleton_x[i]<<" and "<<skeleton_y[i];
                                // int temp;
                                // cin>>temp;
                                foundSpot=true;
                                break;
                            }
                    
                        
                        }
                    if(foundSpot) break;
                }

            
             }

             if(foundSpot)
             {
                 isMoving[i]=true;
             }
             else
             {
                 skeletonJumping[i]=0;
             }
        }
        else
        {
            float dx=dest_x[i]-skeleton_x[i]; 
            float dy=dest_y[i]-skeleton_y[i];
            float dist= sqrt(dx*dx + dy*dy);

			 //find the current distance of the skel from the target x and y 
            float Pixels = 10; //no of pixels the skel jumps per iteration

            if(dist <= Pixels)
            {
						skeleton_x[i] = static_cast<int>(dest_x[i]);
						skeleton_y[i] = static_cast<int>(dest_y[i]);
						isMoving[i] = false;
						skeletonJumping[i] = 0;
            }
				else
					{
						skeleton_x[i] += static_cast<int>((dx/dist)*Pixels);
						skeleton_y[i] += static_cast<int>((dy/dist)*Pixels);
					}
            
			
					skeletonSp[i].setTextureRect(IntRect(JumpingFramePos,0,32,110));
        }
    }






    if(!skeletonJumping[i])
    {

    if(skeletonIdle[i]){ //if the skeleton is idle handle the animations
    
    
        if(/*!posChangeHappened[i]*/ FrameCount-FramePosForChange[i]==300ull){
            currentIdleFrame[i]++;
            
        }
        

        //currentIdleFrame[i]=(currentIdleFrame[i]>2?0:currentIdleFrame[i]);

        if(currentIdleFrame[i]>2)
        {
                    skeletonIdle[i]=0;
                    currentIdleFrame[i]=0;

        }
        else
            skeletonSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,110));
        
    }


    if(!skeletonIdle[i]) //if the skeleton is not idle move either left or right
            if(!skeletonMovingLeft[i]){
                
                
                if(lvl[grid_y_skeleton+1][grid_x_skeleton+1]!='#'||lvl[grid_y_skeleton][grid_x_skeleton+1]=='#'){
                    skeletonMovingLeft[i]=1;
                    if((rand()%100)>60 && lvl[grid_y_skeleton+1][grid_x_skeleton+1]!='#' &&  skeletonJumping[i]==0 && jumpCoolDown[i]==0){ 
                        //if the skeleton changes direction because it reached an edge
                            skeletonJumping[i]=1;
                            jumpCoolDown[i]=600;
                            isMoving[i]=0;
                            Jumping_x=grid_x_skeleton;
                            Jumping_y=grid_y_skeleton;
                            if(rand()%100>50)
                                jumpingUp=1;
                            else    
                                jumpingUp=0;
                        }
                }
                else
                    if(grid_x_skeleton+1<width-1 ){
                        skeleton_x[i]+=1;
                        
                    
                    }else{
                        skeletonMovingLeft[i]=1;

                    }
            
            }
            else
            
            if(skeletonMovingLeft[i])

                if(lvl[grid_y_skeleton+1][grid_x_skeleton]!='#'||lvl[grid_y_skeleton][grid_x_skeleton]=='#'){ //for some incredible dumb reason x-1 causes it to not hit the left wall
                    skeletonMovingLeft[i]=0;

                    if((rand()%100)>60 && lvl[grid_y_skeleton+1][grid_x_skeleton]!='#' && skeletonJumping[i]==0 && jumpCoolDown[i]==0){ 
                        //if the skeleton changes direction because it reached an edge
                            skeletonJumping[i]=1;
                            jumpCoolDown[i]=600;
                            isMoving[i]=0;
                            Jumping_x=grid_x_skeleton;
                            Jumping_y=grid_y_skeleton;
                            if(rand()%100>50)
                                jumpingUp=1;
                            else 
                                jumpingUp=0;

                        }
                }
                
                else
                    if(grid_x_skeleton-1>=0 )
                    skeleton_x[i]-=1;
                    else    
                    skeletonMovingLeft[i]=0;
                
        }       
    }


    skeletonSp[i].setPosition(skeleton_x[i],skeleton_y[i]);

    if(!SkeletonBeingPulled)//dont kill player if being sucked
        if(!(player_x<skeleton_x[i]-50||player_x>skeleton_x[i]+50)&&!(player_y<skeleton_y[i]-32||player_y>skeleton_y[i]+32)) //skeleton player collision check
        {
            player_x=cell_size;
            player_y=(height-2)*cell_size-PlayerHeight;
            PlayerSprite.setPosition(player_y,player_x);
            lives--;

        }
    
    if(!skeletonIdle[i] && !skeletonJumping[i])
    skeletonSp[i].setTextureRect(IntRect(Frame,0,32,110));//staring x, staring y ,widht,height
    
    if(!skeletonIdle[i])
        {
            if(!skeletonMovingLeft[i]){
                skeletonSp[i].setScale(-2,2);
                skeletonSp[i].setOrigin(32,0);
            }
            else {
                skeletonSp[i].setScale(2,2);
                skeletonSp[i].setOrigin(0,0);   
            }
        }
        //ensuer enouh frames have passed for random movement change again


    if(FrameCount-FramePosForChange[i]==1200ull)
    {
        cout<<FrameCount-FramePosForChange[i];
        posChangeHappened[i]=0;
    }






    if(!posChangeHappened[i]&&!skeletonJumping[i])
        {
                int check=rand()%100;
    
            if(check<30){ 
                        

                        //change direcation
                    skeletonMovingLeft[currentSkeleton]=!skeletonMovingLeft[currentSkeleton];
                    cout<<"change for skeleton "<<currentSkeleton<<"at frame "<<FrameCount<<endl;
                    currentSkeleton++;
                    posChangeHappened[i]=1;
                    FramePosForChange[i]=FrameCount;
                    currentSkeleton=currentSkeleton>3?0:currentSkeleton;
                    //clamp to zero and 3
            }else if(!skeletonIdle[i] && (FrameCount+i*150)%600<10)
                {
                    //turn idle
                    currentIdleFrame[i]=0;
                    cout<<"\nSkeleton "<<i<<" is Idle\n";
                    skeletonIdle[i]=1;
                    skeletonSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,110));
                    currentIdleFrame[i]=0;
                    FramePosForChange[i]=Frame;
                    
                }   
    
    }

        
    jumpCoolDown[i]-=1;
    jumpCoolDown[i]=jumpCoolDown[i]<0?0:jumpCoolDown[i];


    if(FrameCount%120==0)
        Frame+=33;

    
    if(Frame>300)
        Frame=192;


    FrameCount++;
    return;//end of func


	}
}
	




void vacuum_suck(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int& vacuum_x, int& vacuum_y, int maxcap, int vacuum_range, int vacuum_width, int captured_enemies_index[], int& captured_count, int Ghost_x[], int Ghost_y[], int num_ghosts, bool GhostBeingPulled[],bool Firstrun,RenderWindow& window, int captured_enemies_type[])
{
	static int FrameCount=0;
	static int starting_x=200;
	int starting_y=174;
	int width=15;
	int height=32;

	static Sprite beam;
	static Texture BeamT;
	if(Firstrun)
	{
		
		BeamT.loadFromFile("Data/player.png");
		beam.setTexture(BeamT);
	}

		beam.setTextureRect(IntRect(starting_x,starting_y,width,height));
		
		float scale=vacuum_range/32.0f;
		beam.setScale(vacuum_range,vacuum_range);

		beam.setOrigin(16,16);


	float vacuum_start_x, vacuum_start_y;
	
	if (vacuum_x == 1) { //aiming right
	vacuum_start_x = player_x + PlayerWidth; //far right of player png
	} else if (vacuum_x == -1) { //aiming left
	vacuum_start_x = player_x; //far left of player sprite
	} else vacuum_start_x = player_x + PlayerWidth/2; //if aiming up or down, use horizontal center
	
	if (vacuum_y == -1) { //aiming up
	vacuum_start_y = player_y; //top edge
	} else if (vacuum_y == 1) { //aiming down
	vacuum_start_y = player_y + PlayerHeight;
	} else vacuum_start_y = player_y + PlayerHeight/2; //if aiming left or right, use vertical center
	

	beam.setPosition(vacuum_start_x,vacuum_start_y);

	float beam_start = 0, beam_top = 0, beam_length = 0, beam_width = 0;
	if (vacuum_x == 1) { //right aim
		
		beam_start = vacuum_start_x;
		beam_top = vacuum_start_y - ((float)vacuum_width/2); //vertical center
		beam_length = vacuum_range;
		beam_width = vacuum_width;
		beam.setRotation(180.0); 
        beam.setScale(scale,scale);
		
		

	} else if (vacuum_x == -1) { //left aim
		beam_start = vacuum_start_x - vacuum_range;
		beam_top = vacuum_start_y - ((float)vacuum_width/2); //vertical center
		beam_length = vacuum_range;
		beam_width = vacuum_width;
		beam.setRotation(0.0); 
        beam.setScale(scale,scale);

	} else if (vacuum_y == -1) { //up aim
		beam_start = vacuum_start_x - ((float)vacuum_width/2); //horizontal center
		beam_top = vacuum_start_y - vacuum_range;
		beam_length = vacuum_width;
		beam_width = vacuum_range;
		beam.setRotation(-90.0); 
        beam.setScale(scale,scale);
		

	} else if (vacuum_y == 1) { //down aim
		beam_start = vacuum_start_x - ((float)vacuum_width/2); //horizontal center
		beam_top = vacuum_start_y ;
		beam_length = vacuum_width;
		beam_width = vacuum_range;
		beam.setRotation(90.0); 
        beam.setScale(scale,scale);	}
	
	int ghost_size = 64; //to make the gun collision check the whole box sprite rectangle of the ghost
	
	//enemy capture
	if (Keyboard::isKeyPressed(Keyboard::Space) && captured_count < maxcap) { //if holding space and not at capacity
		
	

		window.draw(beam);

		for (int i = 0; i < num_ghosts; i++) {
			if (Ghost_x[i] > 0 && !GhostBeingPulled[i]) { //if ghost in game on screen and not already being pullled
				bool collisionX = Ghost_x[i] + ghost_size > beam_start && Ghost_x[i] < beam_start + beam_length; //collision with rectangle of ghost 
				bool collisionY = Ghost_y[i] + ghost_size > beam_top && Ghost_y[i] < beam_top + beam_width; //rectangle of ghost 
				
				if (collisionX && collisionY) {
					GhostBeingPulled[i] = true;
					break;
				}
			}
		}
	}



	FrameCount++;

	if(FrameCount%15==0){
		starting_x+=13;
	}

	if(starting_x>574){
		starting_x=200;
	}

}
	
void invisibleManMove(int invisibleMan_x[],int invisibleMan_y[],int width,Sprite invisibleManSp[],bool invisibleManMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool invisibleManIdle[],int & lives,const int invisibleManCount, int currentinvisibleMan, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool invisibleManJumping[],int jumpCoolDown[], bool invisibleManBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int InvisibleManBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[])
{
	static int Frame=155;	 //has to be at start or scope errors l8r
	static bool jumpingUp=0;
	static int FrameCount=0;
	
	
	if (InvisibleManShotVelX[i] != 0 || InvisibleManShotVelY[i] != 0) { //x movement
		InvisibleManIsShot[i] = true;
		
        int next_x = invisibleMan_x[i] + (int)InvisibleManShotVelX[i];
        int gridX = next_x / cell_size;
        int gridY = invisibleMan_y[i] / cell_size;
        
        if (next_x <= 0 || next_x >= (width-1)*cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) {
            InvisibleManShotVelX[i] = -InvisibleManShotVelX[i];
            InvisibleManBounceCount[i]++;
        }
        else invisibleMan_x[i] = next_x;
        
        //y movemetn
        InvisibleManShotVelY[i] += 1;
        if (InvisibleManShotVelY[i] > 20) 
            InvisibleManShotVelY[i] = 20;
        
        int next_y = invisibleMan_y[i] + (int)InvisibleManShotVelY[i];
        gridX = invisibleMan_x[i] / cell_size;
        gridY = next_y / cell_size;
        
        if (next_y <= 0 || next_y >= (height-1)*cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) {
            if (InvisibleManShotVelY[i] > 0) {
                InvisibleManShotVelY[i] = 0;
                if (gridY < height) 
                    invisibleMan_y[i] = (gridY - 1) * cell_size;
                if (InvisibleManShotVelX[i] == 0) {
                    if (rand() % 2 == 0)
                        InvisibleManShotVelX[i] = 15;
                    else InvisibleManShotVelX[i] = -15;
                }
            }
            else if (InvisibleManShotVelY[i] < 0) {
                InvisibleManShotVelY[i] = 0;
                if (InvisibleManShotVelX[i] == 0) {
                    if (rand() % 2 == 0)
                        InvisibleManShotVelX[i] = 15;
                    else InvisibleManShotVelX[i] = -15;
                }
            }
        }
        else invisibleMan_y[i] = next_y;
        
        if (InvisibleManBounceCount[i] >= 5) {
            InvisibleManShotVelX[i] = 0;
            InvisibleManShotVelY[i] = 0;
            invisibleMan_x[i] = -1000;
            invisibleMan_y[i] = -1000;
            InvisibleManIsShot[i] = false;
            ActiveEnemies--;
        }
        
        //collision
        int invis_size = 64;
        
        //ghosts
        for (int j = 0; j < GhostCount; j++) {
            if (Ghost_x[j] > 0 && !GhostIsShot) {
                if (!(invisibleMan_x[i] < Ghost_x[j] - invis_size || invisibleMan_x[i] > Ghost_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < Ghost_y[j] - invis_size || invisibleMan_y[i] > Ghost_y[j] + invis_size)) {
                    Ghost_x[j] = -1000;
                    Ghost_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    InvisibleManIsShot[i] = false;
                    ActiveEnemies--;
                }
            }
        }
        
        //skeletons
        for (int j = 0; j < skeletonCount; j++) {
            if (skeleton_x[j] > 0 && !SkeletonIsShot[i]) {
                if (!(invisibleMan_x[i] < skeleton_x[j] - invis_size || invisibleMan_x[i] > skeleton_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < skeleton_y[j] - invis_size || invisibleMan_y[i] > skeleton_y[j] + invis_size)) {
                    skeleton_x[j] = -1000;
                    skeleton_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    InvisibleManIsShot[i] = true;
                    ActiveEnemies--;
                }
            }
        }
        
        //other invisible mans
        for (int j = 0; j < invisibleManCount; j++) {
            if (j != i && invisibleMan_x[j] > 0 && !(InvisibleManIsShot[i] && InvisibleManIsShot[j])) {
                if (!(invisibleMan_x[i] < invisibleMan_x[j] - invis_size || invisibleMan_x[i] > invisibleMan_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < invisibleMan_y[j] - invis_size || invisibleMan_y[i] > invisibleMan_y[j] + invis_size)) {
                    invisibleMan_x[j] = -1000;
                    invisibleMan_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    InvisibleManIsShot[i] = false;
                    ActiveEnemies--;
                }
            }
        }
        
        //chelnov
        for (int j = 0; j < chelnovCount; j++) {
            if (chelnov_x[j] > 0 && !ChelnovIsShot[i]) {
                if (!(invisibleMan_x[i] < chelnov_x[j] - invis_size || invisibleMan_x[i] > chelnov_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < chelnov_y[j] - invis_size || invisibleMan_y[i] > chelnov_y[j] + invis_size)) {
                    chelnov_x[j] = -1000;
                    chelnov_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    InvisibleManIsShot[i] = false;
                    ActiveEnemies--;
                }
            }
        }
        
        invisibleManSp[i].setPosition(invisibleMan_x[i], invisibleMan_y[i]);
        return;
    }
	
	
	
	
	int grid_x_invisibleMan=invisibleMan_x[i]/64;
	int grid_y_invisibleMan=(invisibleMan_y[i]+45)/64;
	if((invisibleMan_y[i]+45)<height)
	grid_y_invisibleMan=(invisibleMan_y[i]+45)/64;
	static int currentIdleFrame[3]={0};
	int IdleFramepos[3]={49,83,117};
	static int Jumping_x=0;
	static int Jumping_y=0;
	static int tpCounter[4]={0}; //count the frames  for jumping max frames for jumping 
    static bool isFadingIn[4]={0};
    static int TargetJumpX[4]={0}; // Store the target X so we don't find it again
    static int TargetJumpY[4]={0}; // Store the target Y
	int JumpingFramesPos[4]={366,400,435,469};



	
	//cout<<i<<endl;
	
	
	
	
	
	float vacuum_start_x, vacuum_start_y; //same pulling system as ghost
	if (vacuum_x == 1) { //aiming right
	vacuum_start_x = player_x + PlayerWidth; //far right of player png
	} else if (vacuum_x == -1) { //aiming left
	vacuum_start_x = player_x; //far left of player sprite
	} else vacuum_start_x = player_x + PlayerWidth/2; //if aiming up or down, use horizontal center
	
	if (vacuum_y == -1) { //aiming up
	vacuum_start_y = player_y; //top edge
	} else if (vacuum_y == 1) { //aiming down
	vacuum_start_y = player_y + PlayerHeight;
	} else vacuum_start_y = player_y + PlayerHeight/2; //if aiming left or right, use vertical center
	
	const float pullspeed = 3;
	if (invisibleManBeingPulled[i]) {
		
		if (!Keyboard::isKeyPressed(Keyboard::Space)) {
			invisibleManBeingPulled[i] = false; //stops pulling if let go of space
			return;
		}
		
		float dx = vacuum_start_x - invisibleMan_x[i]; //horizontal distance
		float dy = vacuum_start_y - invisibleMan_y[i]; //vertical distance
		if (dx > pullspeed) { //target to the left
			invisibleMan_x[i] += pullspeed;
		} else if (dx < -pullspeed) { //target to the right
			invisibleMan_x[i] -= pullspeed;
		} else invisibleMan_x[i] = vacuum_start_x; //snaps the target to the vacuum to prevent it moving past
		
		if (dy > pullspeed) { //target is up
			invisibleMan_y[i] += pullspeed;
		} else if (dy < -pullspeed) { //target is down
			invisibleMan_y[i] -= pullspeed;
		} else invisibleMan_y[i] = vacuum_start_y; //snaps
		
		//check if capture
		if (invisibleMan_x[i] == (int)vacuum_start_x && invisibleMan_y[i] == (int)vacuum_start_y) { //int because ghost_x and ghost_y are integers, woudl alwyas be false with a decimal
			if (captured_count < maxcap) {
				captured_enemies_index[captured_count] = i;
				captured_enemies_type[captured_count] = 2;
				captured_count += 1;
				
				//reset pull and move ghost off camera
				invisibleManBeingPulled[i] = false;
				invisibleMan_x[i] = -1000;
				invisibleMan_y[i] = -1000;
				}
			}
		} 
	else { //if not being pulled, normal patrol
	
	
	
	
	
	
			
	
	
		if (invisibleMan_x[i] > 0) { //only runs if on screen
	
	




		if(invisibleManJumping[i]) 
	    {

            int renderFrame = tpCounter[i];
            if (renderFrame > 3) renderFrame = 3;
            if (renderFrame < 0) renderFrame = 0;

            invisibleManSp[i].setTextureRect(IntRect(JumpingFramesPos[renderFrame],0,32,110));
            
        
            if(FrameCount%10==0)
            {
                if(!isFadingIn[i])
                {
                    tpCounter[i]++;
                    
                    if(tpCounter[i] > 3)
                    {
                       
                        if (TargetJumpX[i] != 0 && TargetJumpY[i] != 0) {
                            invisibleMan_x[i] = TargetJumpX[i];
                            invisibleMan_y[i] = TargetJumpY[i];
                            cout<<"invisibleMan teleported to "<<invisibleMan_x[i]<<" and "<<invisibleMan_y[i];
                        }
                        
                        isFadingIn[i] = 1;
                        tpCounter[i] = 3;
                    }
                }
                else
                {
                    tpCounter[i]--;
                    if(tpCounter[i] < 0)
                    {
                        invisibleManJumping[i]=0;
                        tpCounter[i]=0;
                        isFadingIn[i]=0;
                    }
                }
            }
        }










	if(invisibleManIdle[i]){ //if the invisibleMan is idle handle the animations
	
	
		if(/*!posChangeHappened[i]*/ FrameCount-FramePosForChange[i]==300ull){
			currentIdleFrame[i]++;
			
		}
		

		//currentIdleFrame[i]=(currentIdleFrame[i]>2?0:currentIdleFrame[i]);

		if(currentIdleFrame[i]>2)
		{
					invisibleManIdle[i]=0;
					currentIdleFrame[i]=0;

		}
		else
			invisibleManSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,110));
		
	}


	if(!invisibleManIdle[i] && !invisibleManJumping[i]) //if the invisibleMan is not idle and not ready to jump move either left or right
			if(!invisibleManMovingLeft[i]){
				
				
				if(lvl[grid_y_invisibleMan+1][grid_x_invisibleMan+1]!='#'||lvl[grid_y_invisibleMan][grid_x_invisibleMan+1]=='#'){
					invisibleManMovingLeft[i]=1;
					if((rand()%100)>60 && lvl[grid_y_invisibleMan+1][grid_x_invisibleMan+1]!='#' &&  invisibleManJumping[i]==0 && jumpCoolDown){ 
						//if the invisibleMan changes direction because it reached an edge
                            
                            // Check for valid spot first
                            bool foundSpot = false;
                            Jumping_x=grid_x_invisibleMan;
							Jumping_y=grid_y_invisibleMan;
							if(rand()%100>50)
								jumpingUp=1;
							else	
								jumpingUp=0;
                            
                            
                            if(jumpingUp)
                            {
                                for(int skelheight=Jumping_y-2;skelheight>Jumping_y-5&&skelheight>0;skelheight--)
                                {
                                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++)
                                    {
                                        if(lvl[skelheight][row]=='#'){
                                            TargetJumpX[i] = row*cell_size;
                                            TargetJumpY[i] = ((skelheight-1)*cell_size)-(cell_size/2);
                                            foundSpot = true;
                                            break;
                                        }
                                    }
                                    if(foundSpot) break;
                                }
                            }
                            else
                            {
                                 for(int skelheight=Jumping_y+3;skelheight<Jumping_y+7&&skelheight<height-1;skelheight++)
                                {
                                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++)
                                    {
                                        if(lvl[skelheight][row]=='#'){
                                            TargetJumpX[i] = row*cell_size;
                                            TargetJumpY[i] = ((skelheight-1)*cell_size)-(cell_size/2);
                                            foundSpot = true;
                                            break;
                                        }
                                    }
                                    if(foundSpot) break;
                                }
                            }

                            if (foundSpot) {
                                invisibleManJumping[i]=1;
                                jumpCoolDown[i]=600;
                                tpCounter[i]=0;
                                isFadingIn[i]=0;
                                invisibleManSp[i].setTextureRect(IntRect(JumpingFramesPos[0],0,32,110));
                            }
						}
				}
				else
					if(grid_x_invisibleMan+1<width-1 ){
						invisibleMan_x[i]+=1;
						
					
					}else{
						invisibleManMovingLeft[i]=1;

					}
			
			}
			else
			
			if(invisibleManMovingLeft[i])

				if(lvl[grid_y_invisibleMan+1][grid_x_invisibleMan]!='#'||lvl[grid_y_invisibleMan][grid_x_invisibleMan]=='#'){ //for some incredible dumb reason x-1 causes it to not hit the left wall
					invisibleManMovingLeft[i]=0;

					if((rand()%100)>60 && lvl[grid_y_invisibleMan+1][grid_x_invisibleMan]!='#' && invisibleManJumping[i]==0 && jumpCoolDown[i]==0){ 
						//if the invisibleMan changes direction because it reached an edge
                            
                            bool foundSpot = false;
                            Jumping_x=grid_x_invisibleMan;
							Jumping_y=grid_y_invisibleMan;
							if(rand()%100>50)
								jumpingUp=1;
							else 
								jumpingUp=0;
                            
                            if(jumpingUp)
                            {
                                for(int skelheight=Jumping_y-2;skelheight>Jumping_y-5&&skelheight>0;skelheight--)
                                {
                                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++)
                                    {
                                        if(lvl[skelheight][row]=='#'){
                                            TargetJumpX[i] = row*cell_size;
                                            TargetJumpY[i] = ((skelheight-1)*cell_size)-(cell_size/2);
                                            foundSpot = true;
                                            break;
                                        }
                                    }
                                    if(foundSpot) break; //check for valid jump spot before starting anims and tping
                                }
                            }
                            else
                            {
                                 for(int skelheight=Jumping_y+3;skelheight<Jumping_y+7&&skelheight<height-1;skelheight++)
                                {
                                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++)
                                    {
                                        if(lvl[skelheight][row]=='#'){
                                            TargetJumpX[i] = row*cell_size;
                                            TargetJumpY[i] = ((skelheight-1)*cell_size)-(cell_size/2);
                                            foundSpot = true;
                                            break;
                                        }
                                    }
                                    if(foundSpot) break;
                                }
                            }

                            if (foundSpot) {
                                invisibleManJumping[i]=1;
                                jumpCoolDown[i]=600;
                                tpCounter[i]=0;
                                isFadingIn[i]=0;
                                invisibleManSp[i].setTextureRect(IntRect(JumpingFramesPos[0],0,32,110));
                            }

						}
				}
				
				else
					if(grid_x_invisibleMan-1>=0 )
					invisibleMan_x[i]-=1;
					else	
					invisibleManMovingLeft[i]=0;
				
				
	}
	}


	invisibleManSp[i].setPosition(invisibleMan_x[i],invisibleMan_y[i]);

	if(!invisibleManBeingPulled[i])//only collide if not being sucked
	if(!(player_x<invisibleMan_x[i]-50||player_x>invisibleMan_x[i]+50)&&!(player_y<invisibleMan_y[i]-55||player_y>invisibleMan_y[i]+55)) //invisibleMan player collision check
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);
			lives--;

		}
	if(!invisibleManIdle[i] && !invisibleManJumping[i])
	invisibleManSp[i].setTextureRect(IntRect(Frame,0,30,110));//staring x, staring y ,widht,height
	
	if(!invisibleManIdle[i] && !invisibleManJumping[i])
		{
			if(!invisibleManMovingLeft[i]){
				invisibleManSp[i].setScale(-2,2);
				invisibleManSp[i].setOrigin(32,0);
			}
			else {
				invisibleManSp[i].setScale(2,2);
				invisibleManSp[i].setOrigin(0,0);	
			}
		}
		//ensuer enuf frames have passed for random movement change again


	if(FrameCount-FramePosForChange[i]==1200ull)
	{
		cout<<FrameCount-FramePosForChange[i];
		posChangeHappened[i]=0;
	}






	if(!posChangeHappened[i]&&!invisibleManJumping[i])
		{
				int check=rand()%100;
	
			if(check<30){ 
						

						//change direcation
					invisibleManMovingLeft[currentinvisibleMan]=!invisibleManMovingLeft[currentinvisibleMan];
					cout<<"change for invisibleMan "<<currentinvisibleMan<<"at frame "<<FrameCount<<endl;
					currentinvisibleMan++;
					posChangeHappened[i]=1;
					FramePosForChange[i]=FrameCount;
					currentinvisibleMan=currentinvisibleMan>3?0:currentinvisibleMan;
					//clamp to zero and 3
			}else if(!invisibleManIdle[i] && (FrameCount+i*150)%600<10)
				{
					//turn idle
					currentIdleFrame[i]=0;
					cout<<"\ninvisibleMan "<<i<<" is Idle\n";
					invisibleManIdle[i]=1;
					invisibleManSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,110));
					currentIdleFrame[i]=0;
					FramePosForChange[i]=Frame;
					
				}	
	
	}

		
	jumpCoolDown[i]-=1;
	jumpCoolDown[i]=jumpCoolDown[i]<0?0:jumpCoolDown[i];






	if(!invisibleManJumping[i])
    {
            if(FrameCount%120==0)
                    Frame+=37;

                
                if(Frame>262)
                    Frame=155;


                
    }



	FrameCount++;
	return;//end of func


}



void reload(float& player_x, float& player_y, Sprite &PlayerSprite, int cell_size, int height, int PlayerHeight, bool& FirstRun)
{
	player_x=cell_size;
	player_y=(height-2)*cell_size-PlayerHeight;
	PlayerSprite.setPosition(player_x,player_y);
	FirstRun=1;
	return;
}


//power up functions

bool power_deploy(int enemy_x, int enemy_y,int& power_x, int &power_y,int width , int height, int& power_select )// to assign to powerplaced
{
	if(enemy_x < width*64 && enemy_x>0 && enemy_y>0 && enemy_y<height*64)//to be replaced by dead treatment
	{
		power_x=enemy_x;
		power_y=enemy_y;
		power_select=rand()%4;
		return true;
	}
	else return false;

}

void power_display(int power_x, int power_y, Texture& texpower, Sprite& power,int power_select)
{	
	texpower.loadFromFile("Data/player.png");
	power.setTexture(texpower);
	switch (power_select)
	{
	case 0:
		power.setTextureRect(IntRect(17,390,28,22));
		power.setScale(2.5f,2.5f);
		power.setPosition(power_x,power_y);
		break;
	case 1:
		power.setTextureRect(IntRect(489,384,26,27));
		power.setScale(2.5f,2.5f);
		power.setPosition(power_x,power_y);
		break;
	case 2:
		power.setTextureRect(IntRect(124,385,21,25));
		power.setScale(3,2.5);
		power.setPosition(power_x,power_y);
		break;
	case 3:
		power.setTextureRect(IntRect(270,390,28,21));
		power.setScale(2.5f,3);
		power.setPosition(power_x,power_y);
		break;
	default:
		break;
	}
	
}

bool power_up(int power_x, int power_y, float player_x, float player_y, int playerWidth, int playerHeight,bool& powerPlaced,int power_select, int& speed,int &lives, int& vacuum_range, int& vacuum_width,int &prevlife)// to be assigned to power on
{
	if(power_x < player_x+playerWidth && power_x+64 > player_x && player_y+playerHeight > power_y && power_y+64>player_y)// colision detected
		{
			powerPlaced=0;// to remove power sprite from game and to stop repeatition of this function
			switch (power_select)
				{
				case 0:
					speed*=2;
					break;
				case 1:
					lives++;
					break;
				case 2:
					vacuum_range+=50;
					break;
				case 3:
					vacuum_width+=10;
					break;
				default:
					break;
				}
			prevlife=lives;// if life increase
			return 1;// for power_on signal power activated
		}
	else return 0;// power on 
}	

bool remove_power(int power_select, int& speed , int& lives, int& vacuum_range, int& vacuum_width)
{			
	switch (power_select)
				{
				case 0:
					speed/=2;
					break;
				case 2:
					vacuum_range-=50;
					break;
				case 3:
					vacuum_width-=10;
					break;
				default:
					break;
				}
			return 0;
}



void singleShot(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int vacuum_x, int vacuum_y, int captured_enemies_index[], int captured_enemies_type[], int& captured_count, int Ghost_x[], int Ghost_y[], float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int chelnov_x[], int chelnov_y[], float chelnovShotVelX[], float chelnovShotVelY[])
{

	static bool keyHeld = false; //using this because if its not there, pressing E will just make them all fire out instantly
	if (Keyboard::isKeyPressed(Keyboard::E)) {
		if (!keyHeld && captured_count > 0) {
			keyHeld = true;
			
			captured_count --;
			int enemyID = captured_enemies_index[captured_count];
			int type = captured_enemies_type[captured_count];
			
			float vacuum_start_x, vacuum_start_y;
			if (vacuum_x == 1) { //aiming right
	vacuum_start_x = player_x + PlayerWidth; //far right of player png
			} else if (vacuum_x == -1) { //aiming left
			vacuum_start_x = player_x; //far left of player sprite
			} else vacuum_start_x = player_x + PlayerWidth/2; //if aiming up or down, use horizontal center
			
			if (vacuum_y == -1) { //aiming up
			vacuum_start_y = player_y; //top edge
			} else if (vacuum_y == 1) { //aiming down
			vacuum_start_y = player_y + PlayerHeight;
			} else vacuum_start_y = player_y + PlayerHeight/2; //if aiming left or right, use vertical center
			
			float speed = 18; //was 15, increased
			float velX = 0, velY = 0;
			
			if (vacuum_x != 0) { //horizotal shot
				velX = vacuum_x * speed; //if x 1, vel = 15 and if x -1 then vel = -15
				velY = vacuum_y * speed/2; //
				}
			else if (vacuum_y != 0) { //vertical shot
				velX = 0; //no horizontal movemtn
				velY = vacuum_y * speed; //if y is 1 vel is 15 and y is -1 vel is -15
				}
				
			if (type==0) { //if ghost
				Ghost_x[enemyID] = (int)vacuum_start_x; //brings ghost to tip of vacuum
				Ghost_y[enemyID] = (int)vacuum_start_y;
				GhostShotVelX[enemyID] = velX;
				GhostShotVelY[enemyID] = velY;
				}
			else if (type == 1) { // if skelly
				skeleton_x[enemyID] = (int)vacuum_start_x;
				skeleton_y[enemyID] = (int)vacuum_start_y;
				SkeletonShotVelX[enemyID] = velX;
				SkeletonShotVelY[enemyID] = velY;
				}
			else if (type == 2) { // if invisman
				invisibleMan_x[enemyID] = (int)vacuum_start_x;
				invisibleMan_y[enemyID] = (int)vacuum_start_y;
				InvisibleManShotVelX[enemyID] = velX;
				InvisibleManShotVelY[enemyID] = velY;
				}
			else if (type == 3) { //if chelnov
				chelnov_x[enemyID] = (int)vacuum_start_x;
				chelnov_y[enemyID] = (int)vacuum_start_y;
				chelnovShotVelX[enemyID] = velX;
				chelnovShotVelY[enemyID] = velY;
				}
			}
		}
	else keyHeld = false;
}





void chelnovMove(int chelnov_x[], int chelnov_y[], int width, Sprite chelnovSp[], bool chelnovMovingLeft[], int i, float& player_x, float& player_y, char **lvl, Sprite &PlayerSprite, int cell_size, int PlayerHeight, int height, bool chelnovIdle[], int & lives, const int chelnovCount, int currentchelnov, bool posChangeHappened[], int FramePosForChange[], bool& FirstRun, bool chelnovJumping[], int jumpCoolDown[], bool chelnovBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[], bool GhostIsShot[], bool SkeletonIsShot[], bool InvisibleManIsShot[], bool ChelnovIsShot[]) 
{
	
    static int Frame=40;    //has to be at start or scope errors l8r
    static bool jumpingUp=0;
    static int FrameCount=0;
    int grid_x_chelnov=chelnov_x[i]/64;
    int grid_y_chelnov=(chelnov_y[i]+45)/64;
    if((chelnov_y[i]+45)<height)
    grid_y_chelnov=(chelnov_y[i]+45)/64;
    static int currentIdleFrame[3]={0};
    int IdleFramepos[3]={143,174,222};
    static int Jumping_x=0,Jumping_y=0;
    int JumpingFramePos=76;
    static float dest_x[20]={0};
    static float dest_y[20]={0};
    static bool isMoving[20]={0};

	


	if (chelnovShotVelX[i] != 0 || chelnovShotVelY[i] != 0) { //movement for shot
		ChelnovIsShot[i] = true;
		
		int next_x = chelnov_x[i] + (int)chelnovShotVelX[i]; //x movemnet
		
		int gridX = next_x / cell_size; //coords
		int gridY = chelnov_y[i] / cell_size;
		
		
		if (next_x <= 0 || next_x >= (width - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) 
		{ //if left or right border or hitting a platform
			chelnovShotVelX[i] = -chelnovShotVelX[i]; //reverse X direction, bounce
			chelnovBounceCount[i]++;
		}
		else chelnov_x[i] = next_x;
		
		//y movement
		chelnovShotVelY[i] += 1; //gravity is 1, too annoying to pass in fn
		if (chelnovShotVelY[i] > 20) 
			chelnovShotVelY[i] = 20; //terminal velocity clamp
		
		int next_y = chelnov_y[i] + (int)chelnovShotVelY[i];
		gridX = chelnov_x[i] / cell_size; //uses updated x position
		gridY = next_y / cell_size;
		
		if (next_y <= 0 || next_y >= (height - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#'))
		{ //if hit top and bottom border or platforms
			if (chelnovShotVelY[i] > 0) { //if moving down
				chelnovShotVelY[i] = 0; //stop falling
				if (gridY < height) 
					chelnov_y[i] = (gridY - 1) * cell_size;
				if (chelnovShotVelX[i] == 0) {//if fell striagght down choose random directin t roll to
					if (rand() % 2 == 0)
						chelnovShotVelX[i] = 15; //right
					else chelnovShotVelX[i] = -15; //left
					}
				}
				
			else if (chelnovShotVelY[i] < 0) { //moving up
				chelnovShotVelY[i] = 0;
				if (chelnovShotVelX[i] == 0) { //no vertical movemnt, same random logic
				if (rand() % 2 == 0)
						chelnovShotVelX[i] = 15; //right
					else chelnovShotVelX[i] = -15; //left
					}
				}
				
		} //if not hitting platforms
		else chelnov_y[i] = next_y;
		
		if (chelnovBounceCount[i] >= 5) {
			chelnovShotVelX[i] = 0;
			chelnovShotVelY[i] = 0;
			chelnov_x[i] = -1000;
			chelnov_y[i] = -1000;
			ChelnovIsShot[i] = false;
			ActiveEnemies--;
		}
		
		int chelnov_size = 64;
		for (int j = 0; j < GhostCount; j++) {
			if(Ghost_x[j] > 0 && !GhostIsShot[i]) { //doesnt check off screen ghosts
				if (!(chelnov_x[i] < Ghost_x[j] - chelnov_size || chelnov_x[i] > Ghost_x[j] + chelnov_size) && !(chelnov_y[i] < Ghost_y[j] - chelnov_size || chelnov_y[i] > Ghost_y[j] + chelnov_size)) {
					Ghost_x[j] = -1000; //both die
					Ghost_y[j] = -1000;
					chelnovShotVelX[i] = 0;
					chelnovShotVelY[i] = 0;
					chelnov_x[i] = -1000;
					chelnov_y[i] = -1000;
					ChelnovIsShot[i] = false;
					
					ActiveEnemies--;
				}
			}
		}
		
		//collision with skeletons
		for (int j = 0; j < skeletonCount; j++) {
			if (skeleton_x[j] > 0 && !SkeletonIsShot[i]) { //on screen
				if (!(chelnov_x[i] < skeleton_x[j] - chelnov_size || chelnov_x[i] > skeleton_x[j] + chelnov_size) && !(chelnov_y[i] < skeleton_y[j] - chelnov_size || chelnov_y[i] > skeleton_y[j] + chelnov_size)) {
					skeleton_x[j] = -1000;
					skeleton_y[j] = -1000;
					chelnov_x[i] = -1000; //both die
					chelnov_y[i] = -1000;
					chelnovShotVelX[i] = 0;
					chelnovShotVelY[i] = 0;
					ChelnovIsShot[i] = false;
					
					ActiveEnemies--;
				}
			}
		}
		
		//invisman collision
		for (int j = 0; j < invisibleManCount; j++) {
			if (invisibleMan_x[j] > 0 && !InvisibleManIsShot[i]) {
				if (!(chelnov_x[i] < invisibleMan_x[j] - chelnov_size || chelnov_x[i] > invisibleMan_x[j] + chelnov_size) && !(chelnov_y[i] < invisibleMan_y[j] - chelnov_size || chelnov_y[i] > invisibleMan_y[j] + chelnov_size)) {
					invisibleMan_x[j] = -1000;
					invisibleMan_y[j] = -1000;
					chelnov_x[i] = -1000; //both die
					chelnov_y[i] = -1000;
					chelnovShotVelX[i] = 0;
					chelnovShotVelY[i] = 0;
					ChelnovIsShot[i] = false;
					
					ActiveEnemies--;
				}
			}
		}
		
		//chelnov collision
		for (int j = 0; j < chelnovCount; j++) {
			if (j!=i && chelnov_x[j] > 0 && !(ChelnovIsShot[i] && ChelnovIsShot[j])) {
				if (!(chelnov_x[i] < chelnov_x[j] - chelnov_size || chelnov_x[i] > chelnov_x[j] + chelnov_size) && !(chelnov_y[i] < chelnov_y[j] - chelnov_size || chelnov_y[i] > chelnov_y[j] + chelnov_size)) {
					chelnov_x[j] = -1000;
					chelnov_y[j] = -1000;
					chelnov_x[i] = -1000;
					chelnov_y[i] = -1000;
					chelnovShotVelX[i] = 0;
					chelnovShotVelY[i] = 0;
					ChelnovIsShot[i] = false;
					
					ActiveEnemies--;
				}
			}
		}
		
		
		chelnovSp[i].setPosition(chelnov_x[i], chelnov_y[i]);
		return;
			
	}
	
	
	
	
	
		if (chelnov_x[i] > 0) { //only runs if on screen
	
	
    
    
    //cout<<i<<endl;
    
    
    
    
    
    float vacuum_start_x, vacuum_start_y; //same pulling system as ghost
    if (vacuum_x == 1) { //aiming right
    vacuum_start_x = player_x + PlayerWidth; //far right of player png
    } else if (vacuum_x == -1) { //aiming left
    vacuum_start_x = player_x; //far left of player sprite
    } else vacuum_start_x = player_x + PlayerWidth/2; //if aiming up or down, use horizontal center
    
    if (vacuum_y == -1) { //aiming up
    vacuum_start_y = player_y; //top edge
    } else if (vacuum_y == 1) { //aiming down
    vacuum_start_y = player_y + PlayerHeight;
    } else vacuum_start_y = player_y + PlayerHeight/2; //if aiming left or right, use vertical center
    
    const float pullspeed = 3;
    if (chelnovBeingPulled[i]) {
        
        if (!Keyboard::isKeyPressed(Keyboard::Space)) {
            chelnovBeingPulled[i] = false; //stops pulling if let go of space
            return;
        }
        
        float dx = vacuum_start_x - chelnov_x[i]; //horizontal distance
        float dy = vacuum_start_y - chelnov_y[i]; //vertical distance
        if (dx > pullspeed) { //target to the left
            chelnov_x[i] += pullspeed;
        } else if (dx < -pullspeed) { //target to the right
            chelnov_x[i] -= pullspeed;
        } else chelnov_x[i] = vacuum_start_x; //snaps the target to the vacuum to prevent it moving past
        
        if (dy > pullspeed) { //target is up
            chelnov_y[i] += pullspeed;
        } else if (dy < -pullspeed) { //target is down
            chelnov_y[i] -= pullspeed;
        } else chelnov_y[i] = vacuum_start_y; //snaps
        
        //check if capture
        if (chelnov_x[i] == (int)vacuum_start_x && chelnov_y[i] == (int)vacuum_start_y) { 
            if (captured_count < maxcap) {
                captured_enemies_index[captured_count] = i;
                captured_enemies_type[captured_count] = 3;
                captured_count += 1;
                ActiveEnemies --;
                
                //reset pull and move ghost off camera
                chelnovBeingPulled[i] = false;
                chelnov_x[i] = -1000;
                chelnov_y[i] = -1000;
            }
        } 
        chelnovSp[i].setPosition(chelnov_x[i], chelnov_y[i]); //for soem reason the sprite doesnt get pulled without this, even though none of the other enemies have this here
    } 
    else { 
    
        if (chelnov_x[i] > 0) { //only runs if on screen
    



	//first calculate if the chelnov is moving if not then find jumping destination 
	//after valid jump spot is found set moving to 1
	//when moving is 1 move skel 10 pxs every frame till reaches jump spot

    if(chelnovJumping[i])
    {

        if(!isMoving[i])
        {
             bool foundSpot = false;

            if(jumpingUp)
            {
                //jumping up

                for(int skelheight=Jumping_y-2;skelheight>Jumping_y-5&&skelheight>0 && chelnovJumping[i]==1;skelheight--) //check 5 rows above dont check above index 1
                {
                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) //check 5 cols above 2 on each side on above
                        {
                            if(lvl[skelheight][row]=='#'){
                                cout<<skelheight<<endl<<row<<endl;
                                dest_x[i]=row*cell_size;
                                dest_y[i]=((skelheight-1)*cell_size);
                                cout<<"chelnov jumped to "<<chelnov_x[i]<<" and "<<chelnov_y[i];
                                // int temp;
                                // cin>>temp;
                                foundSpot=true;
                                break;
                            }
                        
                        }
                    if(foundSpot) break;
                }

            }
            
            else{

                //jumping down
                // cout<<"jumped donwn"<<endl;

                for(int skelheight=Jumping_y+3;skelheight<Jumping_y+7&&skelheight<height-1 && chelnovJumping[i]==1;skelheight++) //check 5 rows above dont check above index 1
                {
                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) //check 5 cols above 2 on each side on above
                        {
                            if(lvl[skelheight][row]=='#'){
                                cout<<skelheight<<endl<<row<<endl;
                                // cout<<"Valid Spot found";
                                // int temp;
                                // cin>>temp;
                                dest_x[i]=row*cell_size;
                                dest_y[i]=((skelheight-1)*cell_size);
                                cout<<"chelnov jumped to "<<chelnov_x[i]<<" and "<<chelnov_y[i];
                                // int temp;
                                // cin>>temp;
                                foundSpot=true;
                                break;
                            }
                    
                        
                        }
                    if(foundSpot) break;
                }

            
             }

             if(foundSpot)
             {
                 isMoving[i]=true;
             }
             else
             {
                 chelnovJumping[i]=0;
             }
        }
        else
        {
            float dx=dest_x[i]-chelnov_x[i]; 
            float dy=dest_y[i]-chelnov_y[i];
            float dist= sqrt(dx*dx + dy*dy);

			 //find the current distance of the skel from the target x and y 
            float Pixels = 10; //no of pixels the skel jumps per iteration

            if(dist <= Pixels)
            {
						chelnov_x[i] = static_cast<int>(dest_x[i]);
						chelnov_y[i] = static_cast<int>(dest_y[i]);
						isMoving[i] = false;
						chelnovJumping[i] = 0;
            }
				else
					{
						chelnov_x[i] += static_cast<int>((dx/dist)*Pixels);
						chelnov_y[i] += static_cast<int>((dy/dist)*Pixels);
					}
            
			
					chelnovSp[i].setTextureRect(IntRect(JumpingFramePos,0,32,45));
        }
    }






    if(!chelnovJumping[i])
    {

    if(chelnovIdle[i]){ //if the chelnov is idle handle the animations
    
    
        if(/*!posChangeHappened[i]*/ FrameCount-FramePosForChange[i]==300ull){
            currentIdleFrame[i]++;
            
        }
        

        //currentIdleFrame[i]=(currentIdleFrame[i]>2?0:currentIdleFrame[i]);

        if(currentIdleFrame[i]>2)
        {
                    chelnovIdle[i]=0;
                    currentIdleFrame[i]=0;

        }
        else
            chelnovSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,45));
        
    }


    if(!chelnovIdle[i]) //if the chelnov is not idle move either left or right
            if(!chelnovMovingLeft[i]){
                
                
                if(lvl[grid_y_chelnov+1][grid_x_chelnov+1]!='#'||lvl[grid_y_chelnov][grid_x_chelnov+1]=='#'){
                    chelnovMovingLeft[i]=1;
                    if((rand()%100)>60 && lvl[grid_y_chelnov+1][grid_x_chelnov+1]!='#' &&  chelnovJumping[i]==0 && jumpCoolDown[i]==0){ 
                        //if the chelnov changes direction because it reached an edge
                            chelnovJumping[i]=1;
                            jumpCoolDown[i]=600;
                            isMoving[i]=0;
                            Jumping_x=grid_x_chelnov;
                            Jumping_y=grid_y_chelnov;
                            if(rand()%100>50)
                                jumpingUp=1;
                            else    
                                jumpingUp=0;
                        }
                }
                else
                    if(grid_x_chelnov+1<width-1 ){
                        chelnov_x[i]+=1;
                        
                    
                    }else{
                        chelnovMovingLeft[i]=1;

                    }
            
            }
            else
            
            if(chelnovMovingLeft[i])

                if(lvl[grid_y_chelnov+1][grid_x_chelnov]!='#'||lvl[grid_y_chelnov][grid_x_chelnov]=='#'){ //for some incredible dumb reason x-1 causes it to not hit the left wall
                    chelnovMovingLeft[i]=0;

                    if((rand()%100)>60 && lvl[grid_y_chelnov+1][grid_x_chelnov]!='#' && chelnovJumping[i]==0 && jumpCoolDown[i]==0){ 
                        //if the chelnov changes direction because it reached an edge
                            chelnovJumping[i]=1;
                            jumpCoolDown[i]=600;
                            isMoving[i]=0;
                            Jumping_x=grid_x_chelnov;
                            Jumping_y=grid_y_chelnov;
                            if(rand()%100>50)
                                jumpingUp=1;
                            else 
                                jumpingUp=0;

                        }
                }
                
                else
                    if(grid_x_chelnov-1>=0 )
                    chelnov_x[i]-=1;
                    else    
                    chelnovMovingLeft[i]=0;
                
        }       
    }


    chelnovSp[i].setPosition(chelnov_x[i],chelnov_y[i]);

    if(!chelnovBeingPulled)//dont kill player if being sucked
        if(!(player_x<chelnov_x[i]-50||player_x>chelnov_x[i]+50)&&!(player_y<chelnov_y[i]-32||player_y>chelnov_y[i]+32)) //chelnov player collision check
        {
            player_x=cell_size;
            player_y=(height-2)*cell_size-PlayerHeight;
            PlayerSprite.setPosition(player_y,player_x);
            lives--;

        }
    
    if(!chelnovIdle[i] && !chelnovJumping[i])
    chelnovSp[i].setTextureRect(IntRect(Frame,0,32,45));//staring x, staring y ,widht,height
    
    if(!chelnovIdle[i])
        {
            if(!chelnovMovingLeft[i]){
                chelnovSp[i].setScale(-2,2);
                chelnovSp[i].setOrigin(32,0);
            }
            else {
                chelnovSp[i].setScale(2,2);
                chelnovSp[i].setOrigin(0,0);   
            }
        }
        //ensuer enouh frames have passed for random movement change again


    if(FrameCount-FramePosForChange[i]==1200ull)
    {
        cout<<FrameCount-FramePosForChange[i];
        posChangeHappened[i]=0;
    }






    if(!posChangeHappened[i]&&!chelnovJumping[i])
        {
                int check=rand()%100;
    
            if(check<30){ 
                        

                        //change direcation
                    chelnovMovingLeft[currentchelnov]=!chelnovMovingLeft[currentchelnov];
                    cout<<"change for chelnov "<<currentchelnov<<"at frame "<<FrameCount<<endl;
                    currentchelnov++;
                    posChangeHappened[i]=1;
                    FramePosForChange[i]=FrameCount;
                    currentchelnov=currentchelnov>3?0:currentchelnov;
                    //clamp to zero and 3
            }//else if(!chelnovIdle[i] && (FrameCount+i*150)%600<10)
            //     {
            //         //turn idle
            //         currentIdleFrame[i]=0;
            //         cout<<"\nchelnov "<<i<<" is Idle\n";
            //         chelnovIdle[i]=1;
            //         chelnovSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,45));
            //         currentIdleFrame[i]=0;
            //         FramePosForChange[i]=Frame;
                    
            //     }   
    
    }

        
    jumpCoolDown[i]-=1;
    jumpCoolDown[i]=jumpCoolDown[i]<0?0:jumpCoolDown[i];


    if(FrameCount%120==0)
        Frame+=33;

    
    if(Frame>142)
        Frame=40;


    FrameCount++;
    return;//end of func


	}
}
}

