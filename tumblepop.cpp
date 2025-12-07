
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace sf;
using namespace std;

int screen_x = 1152;
int screen_y = 1000;

 
void reload(float& player_x, float& player_y, Sprite &PlayerSprite, int cell_size, int height, int PlayerHeight, bool& FirstRun);

bool power_deploy(int enemy_x, int enemy_y,int& power_x, int &power_y,int width , int height, int& power_select);

void power_display(int power_x, int power_y, Texture& texpower, Sprite& power,int power_select );

bool power_up(int power_x, int power_y, float player_x, float player_y, int playerWidth, int playerHeight,bool& powerPlaced,int power_select, int& speed,int& lives, int& vacuum_range, int& vacuum_width,int &prevlife);

bool remove_power(int power_select, int& speed,int& lives, int& vacuum_range, int& vacuum_width);

void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int & lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[], int& ActiveEnemies, int skeleton_x[], int skeleton_y[], int skeletonCount, int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, int GhostCount, int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[],int&score);

void chelnovMove(int chelnov_x[], int chelnov_y[], int width, Sprite chelnovSp[], bool chelnovMovingLeft[], int i, float& player_x, float& player_y, char **lvl, Sprite &PlayerSprite, int cell_size, int PlayerHeight, int height, bool chelnovshooting[], int & lives, const int chelnovCount, int currentchelnov, bool posChangeHappened[], int FramePosForChange[], bool& FirstRun, bool chelnovJumping[], int jumpCoolDown[], bool chelnovBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float chelnovShotVelX[], float chelnovShotVelY[],bool projectileActive[], int projectilePos[][2], RenderWindow& window, int chelnovBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[],int&score);

void floatingGhost(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap,int &lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[],int&score);

void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool skeletonIdle[],int & lives,const int skeletonCount, int currentSkeleton, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool skeletonJumping[],int jumpCoolDown[], bool SkeletonBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float SkeletonShotVelX[], float SkeletonShotVelY[], int SkeletonBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[],int&score);

void invisibleManMove(int invisibleMan_x[],int invisibleMan_y[],int width,Sprite invisibleManSp[],bool invisibleManMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool invisibleManIdle[],int & lives,const int invisibleManCount, int currentinvisibleMan, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool invisibleManJumping[],int jumpCoolDown[], bool invisibleManBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int InvisibleManBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[],int&score);

void check_stuck(char** lvl, float& player_x, float& player_y, float& velocityY, int PlayerWidth, int PlayerHeight, int cell_size, int width, int height);

void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, int& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height, int& vacuum_x, int& vacuum_y, int player);

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);

void vacuum_suck(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int& vacuum_x, int& vacuum_y, int maxcap, int vacuum_range, int vacuum_width, int captured_enemies_index[], int& captured_count, int Ghost_x[], int Ghost_y[], int num_ghosts, bool GhostBeingPulled[],bool Firstrun,RenderWindow& window, int player);

void singleShot(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int vacuum_x, int vacuum_y, int captured_enemies_index[], int captured_enemies_type[], int& captured_count, int Ghost_x[], int Ghost_y[], float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], float InvisibleManShotVelX[], float InvisibleManShotVelY[]);

void CreateNewArrays(int& numberEnemies, Sprite** EnemySp, int** EnemyType, int** EnemyX, int** EnemyY, float** EnemyVelX, float** EnemyVelY, bool** EnemyMovingLeft, int** EnemyBounceCount, bool** EnemyBeingPulled, bool** EnemyIdle, bool** EnemyJumping, int** EnemyCoolDown, bool** EnemyPosChange, int** EnemyFrameChange, bool** EnemyShooting, bool** ProjectileActive, int (**ProjectilePos)[2]);

void SpawnEnemy(int YPos, int enemyClass, int width, int& enemyCount, int& arrayCapacity, int& ActiveEnemies,Sprite** EnemySp, int** EnemyType, int** EnemyX, int** EnemyY, float** EnemyVelX, float** EnemyVelY, bool** EnemyMovingLeft, int** EnemyBounceCount, bool** EnemyBeingPulled,bool** EnemyIdle, bool** EnemyJumping, int** EnemyCoolDown, bool** EnemyPosChange, int** EnemyFrameChange, bool** EnemyShooting, bool** ProjectileActive, int (**ProjectilePos)[2]);

void DisplayEnemies(RenderWindow& Window, int Index, int* EnemyType, int** EnemyPos, Sprite* EnemySp);

void level_one(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], int player,int&score);

void level_two(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], float chelnovShotVelX[], float chelnovShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, int chelnovBounceCount[], int player,int&score);

void level_three(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], int player,int&score);

void level_four(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[],int player,int&score);

void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size);

int main()
{
	static bool FirstRun=1;
	static int lives=3;
	static int score=0;
	bool ShowStart=1;//diplay starting window
	bool menuload=0;//for menu screen
	bool pause=0;
	bool playerload=0;
	int player;// 1 for green and two for yellow
	Clock overclock;
	bool clockreset=1;//for wat in game over

	//set up random number seed
	srand(time(0));

	bool facingLeft=true; //cuz start with left sprite

	RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP", Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

// level specifications
	int level=1;
	const int cell_size = 64;
	const int height = 15;
	const int width = 18;
	int b_height=23;    //for boss level
	int b_width=27;
	int boss_cell=42;
	char** lvl;        //others 
	char** blvl;       //boss level
	blvl=new char *[b_height];
	for(int i=0;i<b_height;i++)
		blvl[i]= new char [b_width];

	//gun specifics
	int maxcap = 3;
	int vacuum_range = 200;
	int vacuum_width = 50;
	if(player==2)//yellow tumble poper power bonus
	{
		vacuum_range=static_cast<float>(vacuum_range)*1.2;
		vacuum_width=static_cast<float>(vacuum_range)*1.2;
	}
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
	// menu texture and sprite
	Texture menutex;
	Sprite menupage;
	
	bgTex.loadFromFile("Data/bg.png");
	bgSprite.setTexture(bgTex);
	bgSprite.setPosition(0,0);

	float scaleX = (width * cell_size) / (float)bgTex.getSize().x;
	float scaleY = (height * cell_size) / (float)bgTex.getSize().y;
	bgSprite.setScale(scaleX, scaleY);

	blockTexture.loadFromFile("Data/block1.png");
	blockSprite.setTexture(blockTexture);
	float bscaleX = (cell_size * cell_size) / (float)blockTexture.getSize().x;
	float bscaleY = (cell_size * cell_size) / (float)blockTexture.getSize().y;
	
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
	if(player==1)
	speed=static_cast<float>(speed)*1.5;
	float velocityX=1;
	float terminal_Velocity_x=5;
	float friction=0.8;
	float acceleration=1;

	const float jumpStrength = 19; // Initial jump velocity
	const float gravity = 1;  // Gravity acceleration

	bool isJumping = false;  // Track if jumping
	bool onGround = true;

	float offset_x = 0;
	float offset_y = 0;
	float velocityY = 0;

	float terminal_Velocity = 20;

	int PlayerHeight = 60;
	int PlayerWidth = 96;

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

	Texture PlayerTexture;
	Sprite PlayerSprite;

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

	Event ev;
	int counter=1;
	
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
	ScoreText.setFillColor(Color::Red);
	livesText.setFillColor(Color::Red);
	capturedText.setFillColor(Color::Red);

    // Initial string
    livesText.setString("Lives: " + to_string(lives));
	ScoreText.setString("Score: "+ to_string(score));
	capturedText.setString("Enemies Captured: " + to_string(captured_count));
	
	while (window.isOpen())
	{			
		//score=captured_count*200;
		
		
		//presing escape to close
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
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
			
			if(playerload)
			{	Texture selecttex;
				Sprite selectsp;
				selecttex.loadFromFile("Data/selection.png");
				selectsp.setTexture(selecttex);
				selectsp.setPosition(0,0);

				float scaleX = (width * cell_size) / (float)selecttex.getSize().x;
				float scaleY = (height * cell_size) / (float)selecttex.getSize().y;
				selectsp.setScale(scaleX, scaleY);

				window.draw(selectsp);
				window.display();

				
				if(Keyboard::isKeyPressed(Keyboard::Num2))
				{
					player =2;
					playerload=0;
				}
				else if(Keyboard::isKeyPressed(Keyboard::Num1))
				{
					player =1;
					playerload=0;
				}
				else continue;
			}

			if(menuload){ // module to load menu 
				menutex.loadFromFile("Data/menu-min.png");
				menupage.setTexture(menutex);
				menupage.setPosition(0,0);

				float scaleX = (width * cell_size) / (float)menutex.getSize().x;
				float scaleY = (height * cell_size) / (float)menutex.getSize().y;
				menupage.setScale(scaleX, scaleY);

				window.draw(menupage);
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

				if(clockreset)
				{
					overclock.restart();
					clockreset=0;
				}
					if(overclock.getElapsedTime().asSeconds()<=3)
					{
						continue;
					}
				
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
		}

		if(ShowStart){

			if(Keyboard::isKeyPressed(Keyboard::Space)){
				ShowStart=0;
				menuload=1;
			}
			continue;
		}	//if the user presses the space key dont show start

		while (window.pollEvent(ev))
		{
				
			if(ev.type == Event::Resized)
				{ //resize the start screen if the user resizes the window
					
					if(menuload){
						menutex.loadFromFile("Data/menu-min.png");
						menupage.setTexture(menutex);
						menupage.setPosition(0,0);

						float scaleX = (width * cell_size) / (float)menutex.getSize().x;
						float scaleY = (height * cell_size) / (float)menutex.getSize().y;
						menupage.setScale(scaleX, scaleY);

						window.draw(menupage);
						window.display();
					}
				}
			
			if (ev.type == Event::Closed) 
			{
				window.close();
			}
		}

		if(menuload){

			if(Keyboard::isKeyPressed(Keyboard::Num1)){
				menuload=0;
				clockreset=1;//for reset clock of lost agian
				level=1;
				FirstRun=1;
				playerload=1;
				
			}
			else if(Keyboard::isKeyPressed(Keyboard::Num2))
			{	clockreset=1;//for reset clock of lost agian
				menuload=0;
				level=2;
				FirstRun=1;
				playerload=1;
			}
			else if(Keyboard::isKeyPressed(Keyboard::Num3)){
				clockreset=1;//for reset clock of lost agian
				menuload=0;
				level=3;
				FirstRun=1;
				playerload=1;
			}
			else if(Keyboard::isKeyPressed(Keyboard::Num4)){
				clockreset=1;//for reset clock of lost agian
				menuload=0;
				level=4;
				FirstRun=1;
				playerload=1;
			}
		}	//level selection module
		if(menuload)
		{lives=3;
		continue;
		}

		window.clear();
		if(level==4)
		
		display_level(window, blvl, bgTex, bgSprite, blockTexture, blockSprite, b_height, b_width, boss_cell);
		
		else
		display_level(window, lvl, bgTex, bgSprite, blockTexture, blockSprite, height, width, cell_size);
		
		//specifying player features to adjust acording to boss level
		if(level==4)
		{
			PlayerHeight=39;
			PlayerWidth=63;

			player_gravity(blvl,offset_y,velocityY,onGround,gravity,terminal_Velocity, player_x, player_y, boss_cell, PlayerHeight, PlayerWidth);
		}
		else 
		{
			PlayerHeight=60;
			PlayerWidth=96;

			player_gravity(lvl,offset_y,velocityY,onGround,gravity,terminal_Velocity, player_x, player_y, cell_size, PlayerHeight, PlayerWidth);
		}
		
		PlayerSprite.setPosition(player_x, player_y);
		window.draw(PlayerSprite);
		
		if(level==1){
			
			if(Keyboard::isKeyPressed(Keyboard::L)) // reload level at pressing l
			reload(player_x, player_y, PlayerSprite, cell_size, height, PlayerHeight, FirstRun);

			level_one(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength,   speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width, captured_enemies_type, GhostShotVelX, GhostShotVelY, SkeletonShotVelX, SkeletonShotVelY, InvisibleManShotVelX, InvisibleManShotVelY, GhostBounceCount, SkeletonBounceCount, InvisibleManBounceCount, ActiveEnemies, chelnovShotVelX, chelnovShotVelY, chelnovBounceCount, player,score);

		}else
			if(level==2){
			if(Keyboard::isKeyPressed(Keyboard::L)) // reload level at pressing l
			{
				reload(player_x, player_y, PlayerSprite, cell_size, height, PlayerHeight, FirstRun);
			}

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

					level_two(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength, speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width, captured_enemies_type, GhostShotVelX, GhostShotVelY, SkeletonShotVelX, SkeletonShotVelY, InvisibleManShotVelX, InvisibleManShotVelY, chelnovShotVelX, chelnovShotVelY, GhostBounceCount, SkeletonBounceCount, InvisibleManBounceCount, ActiveEnemies, chelnovBounceCount, player,score);			
				}
			
			else if(level==3){
					if(Keyboard::isKeyPressed(Keyboard::L)) { 
						reload(player_x, player_y, PlayerSprite, cell_size, height, PlayerHeight, FirstRun);
					}
					
					level_three(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength,   speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width, captured_enemies_type, GhostShotVelX, GhostShotVelY, SkeletonShotVelX, SkeletonShotVelY, InvisibleManShotVelX, InvisibleManShotVelY, GhostBounceCount, SkeletonBounceCount, InvisibleManBounceCount, ActiveEnemies, chelnovShotVelX, chelnovShotVelY, chelnovBounceCount, player,score);      
				}
			
			else if(level == 4){

				if(Keyboard::isKeyPressed(Keyboard::L)) { 
					reload(player_x, player_y, PlayerSprite, boss_cell, b_height, PlayerHeight, FirstRun);
				}
					if(FirstRun)
					{
					blockTexture.loadFromFile("Data/block1.png");
					blockSprite.setTexture(blockTexture);
					 bscaleX = (boss_cell) / (float)blockTexture.getSize().x;
					 bscaleY = (boss_cell) / (float)blockTexture.getSize().y;
						blockSprite.setScale(bscaleX,bscaleY);
					}
                // Call Level 4 (Boss) logic passing Boss Cell size and arrays
				level_four(blvl, b_height, b_width, FirstRun, player_x, player_y, PlayerSprite, boss_cell, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength, speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width, captured_enemies_type, GhostShotVelX, GhostShotVelY, SkeletonShotVelX, SkeletonShotVelY, InvisibleManShotVelX, InvisibleManShotVelY, GhostBounceCount, SkeletonBounceCount, InvisibleManBounceCount, ActiveEnemies, chelnovShotVelX, chelnovShotVelY, chelnovBounceCount, player,score);
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

	for (int i = 0; i < b_height; i++)
	{
		delete[] blvl[i];
	}
	delete[] blvl;

	return 0;
}

void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap,int &lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[], int& ActiveEnemies, int skeleton_x[], int skeleton_y[], int skeletonCount, int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, int GhostCount, int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[],int & score)
{

	static int Frame=5;	
	static int FrameCount=0;
	
	
	if (GhostShotVelX[i] != 0 || GhostShotVelY[i] != 0) { //movement for shot
	
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
			Ghost_x[i] = -1000;
			Ghost_y[i] = -1000;
			ActiveEnemies--;
						score*=2;
		}
		
		int ghost_size = 64;
		for (int j = 0; j < GhostCount; j++) {
			if(j!=i && Ghost_x[j] > 0) { //doesnt check itself and off screen ghosts
				if (!(Ghost_x[i] < Ghost_x[j] - ghost_size || Ghost_x[i] > Ghost_x[j] + ghost_size) && !(Ghost_y[i] < Ghost_y[j] - ghost_size || Ghost_y[i] > Ghost_y[j] + ghost_size)) { //collision with other ghost
					Ghost_x[i] = -1000; //both die
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					Ghost_x[j] = -1000;
					Ghost_y[j] = -1000;
					
					ActiveEnemies --;
					score*=2;


				}
			}
		}
		
		//now collision with skeletons
		for (int j = 0; j < skeletonCount; j++) {
			if (skeleton_x[j] > 0) { //on screen
				if (!(Ghost_x[i] < skeleton_x[j] - ghost_size || Ghost_x[i] > skeleton_x[j] + ghost_size) && !(Ghost_y[i] < skeleton_y[j] - ghost_size || Ghost_y[i] > skeleton_y[j] + ghost_size)) {
					skeleton_x[j] = -1000;
					skeleton_y[j] = -1000;
					Ghost_x[i] = -1000; //both die
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					ActiveEnemies --;
					score*=2;
				}
			}
		}
		
		//invisman collision
		for (int j = 0; j < invisibleManCount; j++) {
			if (invisibleMan_x[j] > 0) {
				if (!(Ghost_x[i] < invisibleMan_x[j] - ghost_size || Ghost_x[i] > invisibleMan_x[j] + ghost_size) && !(Ghost_y[i] < invisibleMan_y[j] - ghost_size || Ghost_y[i] > invisibleMan_y[j] + ghost_size)) {
					invisibleMan_x[j] = -1000;
					invisibleMan_y[j] = -1000;
					Ghost_x[i] = -1000; //both die
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					ActiveEnemies--;
						score*=2;
				}
			}
		}
		
		//chelnov collision
		for (int j = 0; j < chelnovCount; j++) {
			if (chelnov_x[j] > 0) {
				if (!(Ghost_x[i] < chelnov_x[j] - ghost_size || Ghost_x[i] > chelnov_x[j] + ghost_size) && !(Ghost_y[i] < chelnov_y[j] - ghost_size || Ghost_y[i] > chelnov_y[j] + ghost_size)) {
					chelnov_x[j] = -1000;
					chelnov_y[j] = -1000;
					Ghost_x[i] = -1000;
					Ghost_y[i] = -1000;
					GhostShotVelX[i] = 0;
					GhostShotVelY[i] = 0;
					ActiveEnemies--;
						score*=2;
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
				score+=50;
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
void floatingGhost(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap,int &lives, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], int GhostBounceCount[],int &score)
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
				score+=50;


	
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


void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, int& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height, int& vacuum_x, int& vacuum_y, int player)// handle all ingame movement and collision and gun aim
{

	static int frameCount=0;
	static int frame=219;//value for green and yellow is same along x
	int Framewidth=33;
	int Frameheight=40;
	int starting_Y_frame;

	if(player==1){	
		starting_Y_frame=41;
	
	}
	else{
		starting_Y_frame=230;
	}
	
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
						

						if(player==1){
							PlayerSprite.setTextureRect(IntRect(594,45,Framewidth,Frameheight));//starting x starting y widht height
							//PlayerSprite.setScale(2,1);
							PlayerSprite.setPosition(player_x,player-32);
						}
						else
						{
							PlayerSprite.setTextureRect(IntRect(594,234,Framewidth,Frameheight));//starting x starting y widht height
							//PlayerSprite.setScale(2,1);
							PlayerSprite.setPosition(player_x,player-32);
						}
						


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
						
				
				
			if(!Keyboard::isKeyPressed(Keyboard::Down))
			{
				
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
					if(player==1)
						PlayerSprite.setTextureRect(IntRect(524,30,Framewidth,Frameheight));//starting x starting y widht height
					else
						PlayerSprite.setTextureRect(IntRect(524,219,Framewidth,Frameheight));//starting x starting y widht height

				}
			}else
				PlayerSprite.setPosition(player_x,player-32);

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


void level_one(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[],int player,int& score) {

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

	





	playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y,player);
	check_stuck(lvl, player_x,  player_y, velocityY,  PlayerWidth, PlayerHeight,  cell_size,  width,  height);
	vacuum_suck(player_x, player_y,  PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range,  vacuum_width, captured_enemies_index,  captured_count,  Ghost_x, Ghost_y,  8, GhostBeingPulled,FirstRun,window,player);//replcaed num_ghosts with 8 for testing 
	vacuum_suck(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range, vacuum_width, captured_enemies_index, captured_count, skeleton_x, skeleton_y, 4, SkeletonBeingPulled,FirstRun,window,player); //ran for skeleton pull, 4 skellies
	singleShot(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, captured_enemies_index, captured_enemies_type, captured_count, Ghost_x, Ghost_y, GhostShotVelX, GhostShotVelY, skeleton_x, skeleton_y, SkeletonShotVelX, SkeletonShotVelY, invisibleMan_x, invisibleMan_y, InvisibleManShotVelX, InvisibleManShotVelY);

	//moving enemies
	for(int i=0;i<GhostCount;i++){
	  ghostMove(Ghost_x, Ghost_y, width, GhostSp, GhostMovingLeft, i, player_x, player_y, lvl, PlayerSprite, cell_size, PlayerHeight, height, GhostBeingPulled, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, captured_enemies_type, GhostShotVelX, GhostShotVelY, GhostBounceCount, ActiveEnemies, skeleton_x, skeleton_y, skeletonCount, invisibleMan_x, invisibleMan_y, invisibleManCount, GhostCount, chelnov_x, chelnov_y, chelnovCount, chelnovShotVelX, chelnovShotVelY,score);
	}

	for(int i=0;i<skeletonCount;i++)
	{
 	skeletonMove(skeleton_x, skeleton_y, width, skeletonSp, skeletonMovingLeft, i, player_x, player_y,lvl,PlayerSprite, cell_size, PlayerHeight, height,skeletonIdle, lives,  skeletonCount,  currentSkeleton,  posChangeHappened, FramePosForChange, FirstRun,skeletonJumping,jumpCoolDown, SkeletonBeingPulled,captured_enemies_index, captured_count, PlayerWidth,vacuum_x, vacuum_y, maxcap, captured_enemies_type, SkeletonShotVelX, SkeletonShotVelY, SkeletonBounceCount, ActiveEnemies, Ghost_x, Ghost_y, GhostCount, GhostShotVelX, GhostShotVelY, invisibleMan_x, invisibleMan_y, invisibleManCount, InvisibleManShotVelX, InvisibleManShotVelY, chelnov_x, chelnov_y, chelnovCount, chelnovShotVelX, chelnovShotVelY,score);




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

	if(ActiveEnemies==0){
		cout<<"Level Cleared";
	}

}


void level_two(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], float chelnovShotVelX[], float chelnovShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, int chelnovBounceCount[],int player,int& score)
{
    if (FirstRun) {

        lives = 3; //resetting lives at level start

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++) {
                lvl[i][j] = ' ';
            }
        } //clear array for new level

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1)	// border 
                    lvl[i][j] = '#';

                if ((i == 3 && (j < 4 || (j > 6 && j < width - 3)))) //row 1
                    lvl[i][j] = '#';

                if (i == 4 && (j > 2 && j < 5)) //row 2 start of stair case
                    lvl[i][j] = '#';

                if (i == 5 && ((j > 3 && j < 6) || j == 1 || (j > width - 5) || (j > 9 && j < width - 5)))
                    lvl[i][j] = '#';

                if (i == 6 && (j > 4 && j < 7))
                    lvl[i][j] = '#';

                if (i == 7 && ((j > 5 && j < 8) || (j < 3) || (j < width - 3 && j >= width - 7)))
                    lvl[i][j] = '#';

                if (i == 8 && ((j > 6 && j < 9)))
                    lvl[i][j] = '#';

                if (i == 9 && ((j > 7 && j < 10) || (j < 5) || (j > width - 6)))
                    lvl[i][j] = '#';

                if (i == 10 && ((j > 8 && j < 11)))
                    lvl[i][j] = '#';
                if (i == 11 && (j > 9 && j < 13 || (j < 7)))
                    lvl[i][j] = '#';

            }
        }//draw level if first run
    }


    //number of enemies for the lvl
    const int GhostCount = 4;
    const int skeletonCount = 9;
    const int invisibleManCount = 3;
    const int chelnovCount = 4;


    //for vacc
    static bool GhostBeingPulled[GhostCount] = { 0 };
    static bool SkeletonBeingPulled[skeletonCount] = { 0 };
    static bool invisibleManBeingPulled[invisibleManCount] = { 0 };
    static bool chelnovBeingPulled[chelnovCount] = { 0 };


    //define the Ghost
    static Sprite GhostSp[GhostCount];
    static Texture GhostTx;
    GhostTx.loadFromFile("Data/Ghost.png");

    static int Ghost_y[GhostCount];
    static int Ghost_x[GhostCount];
    static bool GhostMovingLeft[GhostCount];
    //define the Ghost


    //define the skels

    static int currentSkeleton = 0;
    static bool posChangeHappenedSkel[skeletonCount] = { 0 };
    static int FramePosForChangeSkel[skeletonCount] = { 0 };

    static Sprite skeletonSp[skeletonCount];
    static Texture skeletonTx;
    if (FirstRun)
        skeletonTx.loadFromFile("Data/skeleton.png");


    static bool skeletonJumping[skeletonCount] = { 0 };
    static float skeleton_yVelocity[skeletonCount] = { 0 };
    static int skeleton_y[skeletonCount];
    static int skeleton_x[skeletonCount];
    static bool skeletonMovingLeft[skeletonCount];
    static bool skeletonIdle[skeletonCount] = { 0 };
    static int jumpCoolDownSkel[skeletonCount] = { 0 };


    //define the skels


    static Sprite invisibleManSp[invisibleManCount];
    static Texture invisibleManTx;

    // variable for powerups
    static bool power_on = false;// if power up is active 
    static bool powerPlaced = false;// if power up is on stage
    static int power_x;// where is power up 
    static int power_y;//``
    static int power_select = 0;// whichh power up
    static int prevlife = lives;// to keep track if player dies prevlife will become > life, for removepower
    static int enemy_x = 128;//dumy values
    static int enemy_y = 128;
    // power up sprite
    static Texture texpower;
    static Sprite power;


    if (FirstRun)
        invisibleManTx.loadFromFile("Data/invisibleMan.png");
    static bool posChangeHappenedInvisible[invisibleManCount] = { 0 };
    static int FramePosForChangeInvisible[invisibleManCount] = { 0 };
    int currentInvibleMan = 1;
    static bool invisibleManJumping[invisibleManCount] = { 0 };
    static float invisibleMan_yVelocity[invisibleManCount] = { 0 };
    static int invisibleMan_y[invisibleManCount];
    static int invisibleMan_x[invisibleManCount];
    static bool invisibleManMovingLeft[invisibleManCount];
    static bool invisibleManIdle[invisibleManCount] = { 0 };
    static int jumpCoolDownInvisible[invisibleManCount] = { 0 };

    //define the invis men


    //define the chels (ha portal reference)
    static int currentchelnov = 0;
    static bool posChangeHappenedChelnov[chelnovCount] = { 0 };
    static int FramePosForChangeChelnov[chelnovCount] = { 0 };

    static Sprite chelnovSp[chelnovCount];
    static Texture chelnovTx;
    if (FirstRun)
        chelnovTx.loadFromFile("Data/chelnov.png");


    static bool chelnovJumping[chelnovCount] = { 0 };
    static float chelnov_yVelocity[chelnovCount] = { 0 };
    static int chelnov_y[chelnovCount];
    static int chelnov_x[chelnovCount];
    static bool chelnovMovingLeft[chelnovCount];
    static bool chelnovIdle[chelnovCount] = { 0 };
    static int jumpCoolDownChelnov[chelnovCount] = { 0 };
    static bool projectileActice[chelnovCount] = { 0 };
    static int projectilePos[skeletonCount][2] = { 0 };

    //define chels


    if (FirstRun) {
        for (int i = 0; i < invisibleManCount; i++)
        {
            invisibleMan_x[i] = 150;
            invisibleMan_y[i] = (i + 1) * 64;
            invisibleManSp[i].setTexture(invisibleManTx);
            invisibleManSp[i].setTextureRect(IntRect(8, 0, 32, 110));
            int temp = rand();
            if (temp % 2 == 0)
                invisibleManMovingLeft[i] = 0;
            else
                invisibleManMovingLeft[i] = 1;

            //setting the invisibleMan 1 3 5 7
        }
        invisibleMan_x[0] = 16 * 64;
        invisibleMan_y[0] = (4 * 64);

        invisibleMan_x[2] = 11 * 64;
        invisibleMan_y[2] = 6 * 64;

        for (int i = 0; i < invisibleManCount; i++) {
            invisibleMan_y[i] -= 15;
            invisibleManSp[i].setPosition(invisibleMan_x[i], invisibleMan_y[i]);
            invisibleManSp[i].setScale(2, 2);
        }

        for (int i = 0; i < chelnovCount; i++)
        {
            chelnov_x[i] = 150;
            chelnov_y[i] = (i + 1) * 64;
            chelnovSp[i].setTexture(chelnovTx);
            chelnovSp[i].setTextureRect(IntRect(11, 5, 32, 45));
            int temp = rand();
            if (temp % 2 == 0)
                chelnovMovingLeft[i] = 0;
            else
                chelnovMovingLeft[i] = 1;

            //setting the chelnov 1 3 5 7
        }
        chelnov_x[0] = 16 * 64;
        chelnov_y[0] = (4 * 64);
		

        chelnov_x[2] = 11 * 64;
        chelnov_y[2] = 6 * 64;

		chelnov_x[7] = 11 * 64;
        chelnov_y[7] = 14 * 64;






        for (int i = 0; i < chelnovCount; i++) {
            chelnov_y[i] += 15; // This matches the working version in tumblepop.cpp
            chelnovSp[i].setPosition(chelnov_x[i], chelnov_y[i]);
            chelnovSp[i].setScale(2, 2);
        }
    }


    //power up functions
    if (FirstRun && !power_on)// first run to be replaced by triple kill condition 
        powerPlaced = power_deploy(enemy_x, enemy_y, power_x, power_y, width, height, power_select);//power up selection and deployment ok

    if (powerPlaced)
    {
        power_display(power_x, power_y, texpower, power, power_select);

        power_on = power_up(power_x, power_y, player_x, player_y, PlayerWidth, PlayerHeight, powerPlaced, power_select, speed, lives, vacuum_range, vacuum_width, prevlife);
    }
    //removing power
    if (power_on && lives < prevlife)//power active and life decreased 
        power_on = remove_power(power_select, speed, lives, vacuum_range, vacuum_width);//


    playermovement(player_x, velocityY, isJumping, velocityX, PlayerTexture, PlayerSprite, onGround, jumpStrength, speed, friction, counter, terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight, lvl, height, vacuum_x, vacuum_y,player);
    check_stuck(lvl, player_x, player_y, velocityY, PlayerWidth, PlayerHeight, cell_size, width, height);
    vacuum_suck(player_x, player_y, PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range, vacuum_width, captured_enemies_index, captured_count, invisibleMan_x, invisibleMan_y, 4, invisibleManBeingPulled, FirstRun, window,player); //ran for skeleton pull, 4 skellies


    // for (int i = 0; i < invisibleManCount; i++) {
    //     invisibleManMove(invisibleMan_x, invisibleMan_y, width, invisibleManSp, invisibleManMovingLeft, i, player_x, player_y, lvl, PlayerSprite, cell_size, PlayerHeight, height, invisibleManIdle, lives, invisibleManCount, currentInvibleMan, posChangeHappenedInvisible, FramePosForChangeInvisible, FirstRun, invisibleManJumping, jumpCoolDownInvisible, invisibleManBeingPulled, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, captured_enemies_type, InvisibleManShotVelX, InvisibleManShotVelY, InvisibleManBounceCount, ActiveEnemies);



	for(int i=0;i<invisibleManCount;i++){
		invisibleManMove( invisibleMan_x, invisibleMan_y, width, invisibleManSp, invisibleManMovingLeft, i, player_x, player_y,lvl,PlayerSprite, cell_size,PlayerHeight, height, invisibleManIdle, lives, invisibleManCount,  currentInvibleMan,  posChangeHappenedInvisible,  FramePosForChangeInvisible, FirstRun, invisibleManJumping, jumpCoolDownInvisible, invisibleManBeingPulled,  captured_enemies_index,  captured_count,  PlayerWidth,  vacuum_x,  vacuum_y,  maxcap, captured_enemies_type, InvisibleManShotVelX, InvisibleManShotVelY, InvisibleManBounceCount, ActiveEnemies, Ghost_x, Ghost_y, GhostCount, GhostShotVelX, GhostShotVelY, skeleton_x, skeleton_y, skeletonCount, SkeletonShotVelX, SkeletonShotVelY, chelnov_x, chelnov_y, chelnovCount, chelnovShotVelX, chelnovShotVelY,score);	 

    }


    for (int i = 0; i < chelnovCount; i++) {
        chelnovMove(chelnov_x, chelnov_y, width, chelnovSp, chelnovMovingLeft, i, player_x, player_y, lvl, PlayerSprite, cell_size, PlayerHeight, height, chelnovIdle, lives, chelnovCount, currentchelnov, posChangeHappenedChelnov, FramePosForChangeChelnov, FirstRun, chelnovJumping, jumpCoolDownChelnov, chelnovBeingPulled, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, captured_enemies_type, chelnovShotVelX, chelnovShotVelY, projectileActice, projectilePos, window, chelnovBounceCount, ActiveEnemies, Ghost_x, Ghost_y, GhostCount, GhostShotVelX, GhostShotVelY, skeleton_x, skeleton_y, skeletonCount, SkeletonShotVelX, SkeletonShotVelY, invisibleMan_x, invisibleMan_y, invisibleManCount, InvisibleManShotVelX, InvisibleManShotVelY,score);
    }


    for (int i = 0; i < chelnovCount; i++) {
        window.draw(chelnovSp[i]);
    }
    for (int i = 0; i < invisibleManCount; i++) {
        window.draw(invisibleManSp[i]);
    }

    if (powerPlaced)
        window.draw(power);
}




void level_three(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[],int player,int& score)
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



	playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, level_speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y,player);
	vacuum_suck(player_x, player_y,  PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range,  vacuum_width, captured_enemies_index,  captured_count,  Ghost_x, Ghost_y,  8, GhostBeingPulled,FirstRun,window,player);
	
	// adding ghost movement
	for(int i=0;i<GhostCount;i++)
	{
	  floatingGhost(Ghost_x, Ghost_y, width, GhostSp, GhostMovingLeft, i, player_x, player_y, lvl, PlayerSprite, cell_size, PlayerHeight, height, GhostBeingPulled, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, captured_enemies_type, GhostShotVelX, GhostShotVelY, GhostBounceCount,score);
	}









	// draw ghosts
	for(int i=0;i<GhostCount;i++)
		window.draw(GhostSp[i]);
			
		
}

void level_four(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, int& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width, int captured_enemies_type[], float GhostShotVelX[], float GhostShotVelY[], float SkeletonShotVelX[], float SkeletonShotVelY[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int GhostBounceCount[], int SkeletonBounceCount[], int InvisibleManBounceCount[], int& ActiveEnemies, float chelnovShotVelX[], float chelnovShotVelY[], int chelnovBounceCount[], int player,int& score)
{
	//caldren spawner
    static int producerHealth=10;
    static int producerX=0;
    static int producerY=0;
    static bool producerActive=true;
    
	//cloud     
    static int cloudX=0;
    static int cloudY=0;
    static int cloudDirection=1;
    static int cloudMoveSpeed=1;
    
	// ghost 
    static int* Ghost_x=nullptr;
    static int* Ghost_y=nullptr;
    static bool* GhostMovingLeft=nullptr;
    static bool* GhostBeingPulled=nullptr;
    static Sprite* GhostSp=nullptr;
    static int ghostCapacity=0;
    static int ghostCount=0;
    
	//dynamic 
    static int* skeleton_x=nullptr;
    static int* skeleton_y=nullptr;
    static bool* skeletonMovingLeft=nullptr;
    static bool* SkeletonBeingPulled=nullptr;
    static bool* skeletonIdle=nullptr;
    static bool* skeletonJumping=nullptr;
    static int* jumpCoolDown=nullptr;
    static bool* posChangeHappened=nullptr;
    static int* FramePosForChange=nullptr;
    static Sprite* skeletonSp=nullptr;
    static int skeletonCapacity=0;
    static int skeletonCount=0;
    
	//invisibleman 
    static int* invisibleMan_x=nullptr;
    static int* invisibleMan_y=nullptr;
    static bool* invisibleManMovingLeft=nullptr;
    static bool* invisibleManBeingPulled=nullptr;
    static bool* invisibleManIdle=nullptr;
    static bool* invisibleManJumping=nullptr;
    static int* jumpCoolDownInvis=nullptr;
    static bool* posChangeHappenedInvis=nullptr;
    static int* FramePosForChangeInvis=nullptr;
    static Sprite* invisibleManSp=nullptr;
    static int invisCapacity=0;
    static int invisCount=0;
    
	//chelnov  
    static int* chelnov_x=nullptr;
    static int* chelnov_y=nullptr;
    static bool* chelnovMovingLeft=nullptr;
    static bool* chelnovBeingPulled=nullptr;
    static bool* chelnovShooting=nullptr;
    static bool* chelnovJumping=nullptr;
    static int* jumpCoolDownChel=nullptr;
    static bool* posChangeHappenedChel=nullptr;
    static int* FramePosForChangeChel=nullptr;
    static bool* projectileActive=nullptr;
    static int** projectilePos=nullptr;
    static Sprite* chelnovSp=nullptr;
    static int chelCapacity=0;
    static int chelCount=0;
    
    static Texture GhostTex,SkeletonTex,InvisibleManTex,ChelnovTex;
    static Texture ProducerTex,CloudTex;
    static Sprite ProducerSprite,CloudSprite;
    static bool texturesLoaded=false;
    
    static Clock spawnClock;
    
    if(FirstRun){
        lives=3;//reset lives
        producerHealth=10;
        producerActive=1;
        spawnClock.restart();
        
		//clear the level array
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                lvl[i][j]=' ';
            }
        }
        
		//make level borders and platforms
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                if(i==0||i==height-1||j==0||j==width-1)
                    lvl[i][j]='#';
                
                if(i==height-5&&((j>2&&j<7)||(j>10&&j<15)))
                    lvl[i][j]='#';
                
                if(i==height-8&&((j>4&&j<9)||(j>11&&j<14)))
                    lvl[i][j]='#';
                
                if(i==4&&(j>3&&j<width-4))
                    lvl[i][j]='#';
                
                if(i==7&&(j>7&&j<11))
                    lvl[i][j]='#';
            }
        }
        
		//load textures first time
        if(!texturesLoaded){
            GhostTex.loadFromFile("Data/Ghost.png");
            SkeletonTex.loadFromFile("Data/skeleton.png");
            InvisibleManTex.loadFromFile("Data/invisibleMan.png");
            ChelnovTex.loadFromFile("Data/chelnov.png");
			CloudTex.loadFromFile("Data/cloud.png");
			ProducerTex.loadFromFile("Data/spawn.png");
            texturesLoaded=true;
        }
        
		//setup cloud and producer positions
        cloudX=width*cell_size/2;
        cloudY=3*cell_size;
        producerX=cloudX;
        producerY=cloudY-cell_size;
        
		//initialize all counts to zero no memory allocated yet
        ghostCount=0;
        ghostCapacity=0;
        skeletonCount=0;
        skeletonCapacity=0;
        invisCount=0;
        invisCapacity=0;
        chelCount=0;
        chelCapacity=0;
    }
    
	//draw the cloud platform
    CloudSprite.setTexture(CloudTex);
    
	//cloud movement logic up and down
    if(cloudY>=14*cell_size)
	cloudDirection=-1;
    else if(cloudY<=2*cell_size)
	cloudDirection=1;
    
	cloudY+=cloudDirection*cloudMoveSpeed;
    
	producerX = cloudX + 16;
	producerY = cloudY - 20;

	// Draw Cloud
	CloudSprite.setPosition(cloudX, cloudY);
	CloudSprite.setScale(0.5, 0.5);
	window.draw(CloudSprite);

	// Draw Producer if alive
	if(producerActive){
		ProducerSprite.setTexture(ProducerTex);
		ProducerSprite.setPosition(producerX, producerY);
		ProducerSprite.setScale(0.25, 0.25);
		window.draw(ProducerSprite);
	}

	//spawn enemies every 3 seconds from producer
	if(lvl[producerY/cell_size][producerX/cell_size]=='#')
    if(producerActive&&spawnClock.getElapsedTime().asSeconds()>3.0){
        int enemyType=rand()%4+1;//1 ghost 2 skeleton 3 invis 4 chelnov
        int spawnX=producerX;
        int spawnY=producerY-cell_size;

        if(enemyType==1){// create new arr
            int* newX=new int[ghostCount+1];
            int* newY=new int[ghostCount+1];
            bool* newMovingLeft=new bool[ghostCount+1];
            bool* newBeingPulled=new bool[ghostCount+1];
            Sprite* newSp=new Sprite[ghostCount+1];
            
			//copy old data
            for(int i=0;i<ghostCount;i++){
                newX[i]=Ghost_x[i];
                newY[i]=Ghost_y[i];
                newMovingLeft[i]=GhostMovingLeft[i];
                newBeingPulled[i]=GhostBeingPulled[i];
                newSp[i]=GhostSp[i];
            }
            
            newX[ghostCount]=spawnX;
            newY[ghostCount]=spawnY;
            newMovingLeft[ghostCount]=(rand()%2==0);
            newBeingPulled[ghostCount]=0;
            newSp[ghostCount].setTexture(GhostTex);
            newSp[ghostCount].setTextureRect(IntRect(5,5,32,32));
            newSp[ghostCount].setScale(2,2);
            
			//delete old arrays
            delete[] Ghost_x;
            delete[] Ghost_y;
            delete[] GhostMovingLeft;
            delete[] GhostBeingPulled;
            delete[] GhostSp;
            
			//assign new arrays
            Ghost_x=newX;
            Ghost_y=newY;
            GhostMovingLeft=newMovingLeft;
            GhostBeingPulled=newBeingPulled;
            GhostSp=newSp;
            ghostCount++;
            ActiveEnemies++;
        }
        else if(enemyType==2){//spawn skeleton
            int* newX=new int[skeletonCount+1];
            int* newY=new int[skeletonCount+1];
            bool* newMovingLeft=new bool[skeletonCount+1];
            bool* newBeingPulled=new bool[skeletonCount+1];
            bool* newIdle=new bool[skeletonCount+1];
            bool* newJumping=new bool[skeletonCount+1];
            int* newCoolDown=new int[skeletonCount+1];
            bool* newPosChange=new bool[skeletonCount+1];
            int* newFrameChange=new int[skeletonCount+1];
            Sprite* newSp=new Sprite[skeletonCount+1];

			//copy
            for(int i=0;i<skeletonCount;i++){
                newX[i]=skeleton_x[i];
                newY[i]=skeleton_y[i];
                newMovingLeft[i]=skeletonMovingLeft[i];
                newBeingPulled[i]=SkeletonBeingPulled[i];
                newIdle[i]=skeletonIdle[i];
                newJumping[i]=skeletonJumping[i];
                newCoolDown[i]=jumpCoolDown[i];
                newPosChange[i]=posChangeHappened[i];
                newFrameChange[i]=FramePosForChange[i];
                newSp[i]=skeletonSp[i];
            }

            //new enemy data
            newX[skeletonCount]=spawnX;
            newY[skeletonCount]=spawnY-45;//adjust for skeleton height
            newMovingLeft[skeletonCount]=(rand()%2==0);
            newBeingPulled[skeletonCount]=0;
            newIdle[skeletonCount]=0;
            newJumping[skeletonCount]=0;
            newCoolDown[skeletonCount]=0;
            newPosChange[skeletonCount]=0;
            newFrameChange[skeletonCount]=0;
            newSp[skeletonCount].setTexture(SkeletonTex);
            newSp[skeletonCount].setTextureRect(IntRect(8,0,32,110));
            newSp[skeletonCount].setScale(2,2);
            
            delete[] skeleton_x;
            delete[] skeleton_y;
            delete[] skeletonMovingLeft;
            delete[] SkeletonBeingPulled;
            delete[] skeletonIdle;
            delete[] skeletonJumping;
            delete[] jumpCoolDown;
            delete[] posChangeHappened;
            delete[] FramePosForChange;
            delete[] skeletonSp;
            
            skeleton_x=newX;
            skeleton_y=newY;
            skeletonMovingLeft=newMovingLeft;
            SkeletonBeingPulled=newBeingPulled;
            skeletonIdle=newIdle;
            skeletonJumping=newJumping;
            jumpCoolDown=newCoolDown;
            posChangeHappened=newPosChange;
            FramePosForChange=newFrameChange;
            skeletonSp=newSp;
            skeletonCount++;
            ActiveEnemies++;
        }
        else if(enemyType==3){//spawn invisibleman
            int* newX=new int[invisCount+1];
            int* newY=new int[invisCount+1];
            bool* newMovingLeft=new bool[invisCount+1];
            bool* newBeingPulled=new bool[invisCount+1];
            bool* newIdle=new bool[invisCount+1];
            bool* newJumping=new bool[invisCount+1];
            int* newCoolDown=new int[invisCount+1];
            bool* newPosChange=new bool[invisCount+1];
            int* newFrameChange=new int[invisCount+1];
            Sprite* newSp=new Sprite[invisCount+1];

            //copy to new arr
            for(int i=0;i<invisCount;i++){
                newX[i]=invisibleMan_x[i];
                newY[i]=invisibleMan_y[i];
                newMovingLeft[i]=invisibleManMovingLeft[i];
                newBeingPulled[i]=invisibleManBeingPulled[i];
                newIdle[i]=invisibleManIdle[i];
                newJumping[i]=invisibleManJumping[i];
                newCoolDown[i]=jumpCoolDownInvis[i];
                newPosChange[i]=posChangeHappenedInvis[i];
                newFrameChange[i]=FramePosForChangeInvis[i];
                newSp[i]=invisibleManSp[i];
            }

            //define new enemy
            newX[invisCount]=spawnX;
            newY[invisCount]=spawnY-(cell_size/2+5);
            newMovingLeft[invisCount]=(rand()%2==0);
            newBeingPulled[invisCount]=false;
            newIdle[invisCount]=false;
            newJumping[invisCount]=false;
            newCoolDown[invisCount]=0;
            newPosChange[invisCount]=false;
            newFrameChange[invisCount]=0;
            newSp[invisCount].setTexture(InvisibleManTex);
            newSp[invisCount].setTextureRect(IntRect(8,0,32,110));
            newSp[invisCount].setScale(2,2);

            delete[] invisibleMan_x;
            delete[] invisibleMan_y;
            delete[] invisibleManMovingLeft;
            delete[] invisibleManBeingPulled;
            delete[] invisibleManIdle;
            delete[] invisibleManJumping;
            delete[] jumpCoolDownInvis;
            delete[] posChangeHappenedInvis;
            delete[] FramePosForChangeInvis;
            delete[] invisibleManSp;

            invisibleMan_x=newX;
            invisibleMan_y=newY;
            invisibleManMovingLeft=newMovingLeft;
            invisibleManBeingPulled=newBeingPulled;
            invisibleManIdle=newIdle;
            invisibleManJumping=newJumping;
            jumpCoolDownInvis=newCoolDown;
            posChangeHappenedInvis=newPosChange;
            FramePosForChangeInvis=newFrameChange;
            invisibleManSp=newSp;
            invisCount++;
            ActiveEnemies++;
        }
        else if(enemyType==4){//spawn chelnov
            int* newX=new int[chelCount+1];
            int* newY=new int[chelCount+1];
            bool* newMovingLeft=new bool[chelCount+1];
            bool* newBeingPulled=new bool[chelCount+1];
            bool* newShooting=new bool[chelCount+1];
            bool* newJumping=new bool[chelCount+1];
            int* newCoolDown=new int[chelCount+1];
            bool* newPosChange=new bool[chelCount+1];
            int* newFrameChange=new int[chelCount+1];
            bool* newProjActive=new bool[chelCount+1];
            Sprite* newSp=new Sprite[chelCount+1];

			//create 2d array for the projectiles
            int** newProjPos=new int*[chelCount+1];
			for(int i=0;i<chelCount+1;i++){
				newProjPos[i]=new int[2];
			}
            
            for(int i=0;i<chelCount;i++){
                newX[i]=chelnov_x[i];
                newY[i]=chelnov_y[i];
                newMovingLeft[i]=chelnovMovingLeft[i];
                newBeingPulled[i]=chelnovBeingPulled[i];
                newShooting[i]=chelnovShooting[i];
                newJumping[i]=chelnovJumping[i];
                newCoolDown[i]=jumpCoolDownChel[i];
                newPosChange[i]=posChangeHappenedChel[i];
                newFrameChange[i]=FramePosForChangeChel[i];
                newProjActive[i]=projectileActive[i];
                newSp[i]=chelnovSp[i];
				if(projectilePos){
					newProjPos[i][0]=projectilePos[i][0];
					newProjPos[i][1]=projectilePos[i][1];
				}
            }
            
            newX[chelCount]=spawnX;
            newY[chelCount]=spawnY+15;
            newMovingLeft[chelCount]=(rand()%2==0);
            newBeingPulled[chelCount]=false;
            newShooting[chelCount]=false;
            newJumping[chelCount]=false;
            newCoolDown[chelCount]=0;
            newPosChange[chelCount]=false;
            newFrameChange[chelCount]=0;
            newProjActive[chelCount]=false;
            newSp[chelCount].setTexture(ChelnovTex);
            newSp[chelCount].setTextureRect(IntRect(11,5,32,45));
            newSp[chelCount].setScale(2,2);
			newProjPos[chelCount][0]=-1000;
			newProjPos[chelCount][1]=-1000;
            
            delete[] chelnov_x;
            delete[] chelnov_y;
            delete[] chelnovMovingLeft;
            delete[] chelnovBeingPulled;
            delete[] chelnovShooting;
            delete[] chelnovJumping;
            delete[] jumpCoolDownChel;
            delete[] posChangeHappenedChel;
            delete[] FramePosForChangeChel;
            delete[] projectileActive;
			//if projectilePos is not  null ptr delete it
			if(projectilePos!=nullptr){
				for(int i=0;i<chelCount;i++){
					delete[] projectilePos[i];
				}
				delete[] projectilePos;
			}
            delete[] chelnovSp;
            
            chelnov_x=newX;
            chelnov_y=newY;
            chelnovMovingLeft=newMovingLeft;
            chelnovBeingPulled=newBeingPulled;
            chelnovShooting=newShooting;
            chelnovJumping=newJumping;
            jumpCoolDownChel=newCoolDown;
            posChangeHappenedChel=newPosChange;
            FramePosForChangeChel=newFrameChange;
            projectileActive=newProjActive;
            projectilePos=newProjPos;
            chelnovSp=newSp;
            chelCount++;
            ActiveEnemies++;
        }
        
        spawnClock.restart();
    }  // handle all enemy spawning
    
	//player movement
    playermovement(player_x,velocityY,isJumping,velocityX,PlayerTexture,PlayerSprite,onGround,jumpStrength,speed,friction,counter,terminal_Velocity_x,top_mid_up,PlayerWidth,cell_size,player_y,PlayerHeight,lvl,height,vacuum_x,vacuum_y,player);   
    check_stuck(lvl,player_x,player_y,velocityY,PlayerWidth,PlayerHeight,cell_size,width,height);
    
	//check if shot enemies hit the producer
    for(int i=0;i<ghostCount;i++){
        if(GhostShotVelX[i]!=0||GhostShotVelY[i]!=0){
            if(producerActive){
                if(!(Ghost_x[i]<producerX-cell_size||Ghost_x[i]>producerX+cell_size)&&!(Ghost_y[i]<producerY-cell_size||Ghost_y[i]>producerY+cell_size)){
						producerHealth--;
						if(producerHealth<=0){
							producerActive=0;
						}
                }
            }
        }
    }
    
	//same check for skeletons hitting producer
	for(int i=0;i<skeletonCount;i++){
		if(SkeletonShotVelX[i]!=0||SkeletonShotVelY[i]!=0){
			if(producerActive){
				if(!(skeleton_x[i]<producerX-cell_size||skeleton_x[i]>producerX+cell_size)&&!(skeleton_y[i]<producerY-cell_size||skeleton_y[i]>producerY+cell_size)){
					producerHealth--;
					if(producerHealth<=0){
						producerActive=0;
					}
				}
			}
		}
	}
    
	//move and draw all ghosts
    for(int i=0;i<ghostCount;i++){
        if(Ghost_x[i]>0){
            ghostMove(Ghost_x,Ghost_y,width,GhostSp,GhostMovingLeft,i,player_x,player_y,lvl,PlayerSprite,cell_size,PlayerHeight,height,GhostBeingPulled,captured_enemies_index,captured_count,PlayerWidth,vacuum_x,vacuum_y,maxcap,lives,captured_enemies_type,GhostShotVelX,GhostShotVelY,GhostBounceCount,ActiveEnemies,skeleton_x,skeleton_y,skeletonCount,invisibleMan_x,invisibleMan_y,invisCount,ghostCount,chelnov_x,chelnov_y,chelCount,chelnovShotVelX,chelnovShotVelY,score);
            window.draw(GhostSp[i]);
        }
    }
    
	//move and draw skeletons
    for(int i=0;i<skeletonCount;i++){
        if(skeleton_x[i]>0){
            skeletonMove(skeleton_x,skeleton_y,width,skeletonSp,skeletonMovingLeft,i,player_x,player_y,lvl,PlayerSprite,cell_size,PlayerHeight,height,skeletonIdle,lives,skeletonCount,0,posChangeHappened,FramePosForChange,FirstRun,skeletonJumping,jumpCoolDown,SkeletonBeingPulled,captured_enemies_index,captured_count,PlayerWidth,vacuum_x,vacuum_y,maxcap,captured_enemies_type,SkeletonShotVelX,SkeletonShotVelY,SkeletonBounceCount,ActiveEnemies,Ghost_x,Ghost_y,ghostCount,GhostShotVelX,GhostShotVelY,invisibleMan_x,invisibleMan_y,invisCount,InvisibleManShotVelX,InvisibleManShotVelY,chelnov_x,chelnov_y,chelCount,chelnovShotVelX,chelnovShotVelY,score);
            window.draw(skeletonSp[i]);
        }
    }
    
	//move and draw invisiblemen
    for(int i=0;i<invisCount;i++){
        if(invisibleMan_x[i]>0){
            invisibleManMove(invisibleMan_x,invisibleMan_y,width,invisibleManSp,invisibleManMovingLeft,i,player_x,player_y,lvl,PlayerSprite,cell_size,PlayerHeight,height,invisibleManIdle,lives,invisCount,0,posChangeHappenedInvis,FramePosForChangeInvis,FirstRun,invisibleManJumping,jumpCoolDownInvis,invisibleManBeingPulled,captured_enemies_index,captured_count,PlayerWidth,vacuum_x,vacuum_y,maxcap,captured_enemies_type,InvisibleManShotVelX,InvisibleManShotVelY,InvisibleManBounceCount,ActiveEnemies,Ghost_x,Ghost_y,ghostCount,GhostShotVelX,GhostShotVelY,skeleton_x,skeleton_y,skeletonCount,SkeletonShotVelX,SkeletonShotVelY,chelnov_x,chelnov_y,chelCount,chelnovShotVelX,chelnovShotVelY,score);
            window.draw(invisibleManSp[i]);
        }
    }
    
	//move and draw chelnov
    for(int i=0;i<chelCount;i++){
        if(chelnov_x[i]>0){
			//convert int** to int[][2] for function call
			int tempProjectilePos[20][2];
			for(int j=0;j<chelCount;j++){
				if(projectilePos){
					tempProjectilePos[j][0]=projectilePos[j][0];
					tempProjectilePos[j][1]=projectilePos[j][1];
				}else{
					tempProjectilePos[j][0]=-1000;
					tempProjectilePos[j][1]=-1000;
				}
			}
            chelnovMove(chelnov_x,chelnov_y,width,chelnovSp,chelnovMovingLeft,i,player_x,player_y,lvl,PlayerSprite,cell_size,PlayerHeight,height,chelnovShooting,lives,chelCount,0,posChangeHappenedChel,FramePosForChangeChel,FirstRun,chelnovJumping,jumpCoolDownChel,chelnovBeingPulled,captured_enemies_index,captured_count,PlayerWidth,vacuum_x,vacuum_y,maxcap,captured_enemies_type,chelnovShotVelX,chelnovShotVelY,projectileActive,tempProjectilePos,window,chelnovBounceCount,ActiveEnemies,Ghost_x,Ghost_y,ghostCount,GhostShotVelX,GhostShotVelY,skeleton_x,skeleton_y,skeletonCount,SkeletonShotVelX,SkeletonShotVelY,invisibleMan_x,invisibleMan_y,invisCount,InvisibleManShotVelX,InvisibleManShotVelY,score);
			//copy back the values
			if(projectilePos){
				for(int j=0;j<chelCount;j++){
					projectilePos[j][0]=tempProjectilePos[j][0];
					projectilePos[j][1]=tempProjectilePos[j][1];
				}
			}

            window.draw(chelnovSp[i]);
        }
    }
    
	//vacuum suck for all enemy types
    if(ghostCount>0){
        vacuum_suck(player_x,player_y,PlayerWidth,PlayerHeight,vacuum_x,vacuum_y,maxcap,vacuum_range,vacuum_width,captured_enemies_index,captured_count,Ghost_x,Ghost_y,ghostCount,GhostBeingPulled,FirstRun,window,player);
    }
    
    if(skeletonCount>0){
        vacuum_suck(player_x,player_y,PlayerWidth,PlayerHeight,vacuum_x,vacuum_y,maxcap,vacuum_range,vacuum_width,captured_enemies_index,captured_count,skeleton_x,skeleton_y,skeletonCount,SkeletonBeingPulled,FirstRun,window,player);
    }
    
    if(invisCount>0){
        vacuum_suck(player_x,player_y,PlayerWidth,PlayerHeight,vacuum_x,vacuum_y,maxcap,vacuum_range,vacuum_width,captured_enemies_index,captured_count,invisibleMan_x,invisibleMan_y,invisCount,invisibleManBeingPulled,FirstRun,window,player);
    }
    
    if(chelCount>0){
        vacuum_suck(player_x,player_y,PlayerWidth,PlayerHeight,vacuum_x,vacuum_y,maxcap,vacuum_range,vacuum_width,captured_enemies_index,captured_count,chelnov_x,chelnov_y,chelCount,chelnovBeingPulled,FirstRun,window,player);
    }
    
    if(ghostCount>0||skeletonCount>0||invisCount>0){
        singleShot(player_x,player_y,PlayerWidth,PlayerHeight,vacuum_x,vacuum_y,captured_enemies_index,captured_enemies_type,captured_count,Ghost_x,Ghost_y,GhostShotVelX,GhostShotVelY,skeleton_x,skeleton_y,SkeletonShotVelX,SkeletonShotVelY,invisibleMan_x,invisibleMan_y,InvisibleManShotVelX,InvisibleManShotVelY);
    }
}

void CreateNewArrays(int& numberEnemies, Sprite** EnemySp, int** EnemyType, int** EnemyX, int** EnemyY, float** EnemyVelX, float** EnemyVelY, bool** EnemyMovingLeft, int** EnemyBounceCount, bool** EnemyBeingPulled, bool** EnemyIdle, bool** EnemyJumping, int** EnemyCoolDown, bool** EnemyPosChange, int** EnemyFrameChange, bool** EnemyShooting, bool** ProjectileActive, int (**ProjectilePos)[2])
{
	//declare new arr with 10 more slots
	Sprite* newSp = new Sprite[numberEnemies + 10];
	int* newType = new int[numberEnemies + 10];
	int* newX = new int[numberEnemies + 10];
	int* newY = new int[numberEnemies + 10];
	float* newVelX = new float[numberEnemies + 10];
	float* newVelY = new float[numberEnemies + 10];
	bool* newMovingLeft = new bool[numberEnemies + 10];
	int* newBounce = new int[numberEnemies + 10];
	bool* newBeingPulled = new bool[numberEnemies + 10];
	
	bool* newIdle = new bool[numberEnemies + 10];
	bool* newJumping = new bool[numberEnemies + 10];
	int* newCoolDown = new int[numberEnemies + 10];
	bool* newPosChange = new bool[numberEnemies + 10];
	int* newFrameChange = new int[numberEnemies + 10];
	bool* newShooting = new bool[numberEnemies + 10];
	bool* newProjActive = new bool[numberEnemies + 10];
	int (*newProjPos)[2] = new int[numberEnemies + 10][2];

	for (int i = 0; i < numberEnemies; i++) { //copy data
		newSp[i] = (*EnemySp)[i];
		newType[i] = (*EnemyType)[i];
		newX[i] = (*EnemyX)[i];
		newY[i] = (*EnemyY)[i];
		newVelX[i] = (*EnemyVelX)[i];
		newVelY[i] = (*EnemyVelY)[i];
		newMovingLeft[i] = (*EnemyMovingLeft)[i];
		newBounce[i] = (*EnemyBounceCount)[i];
		newBeingPulled[i] = (*EnemyBeingPulled)[i];
		
		newIdle[i] = (*EnemyIdle)[i];
		newJumping[i] = (*EnemyJumping)[i];
		newCoolDown[i] = (*EnemyCoolDown)[i];
		newPosChange[i] = (*EnemyPosChange)[i];
		newFrameChange[i] = (*EnemyFrameChange)[i];
		newShooting[i] = (*EnemyShooting)[i];
		newProjActive[i] = (*ProjectileActive)[i];
		newProjPos[i][0] = (*ProjectilePos)[i][0];
		newProjPos[i][1] = (*ProjectilePos)[i][1];
	}

	//delete old arr
	delete[] *EnemySp; 
	delete[] *EnemyType; 
	delete[] *EnemyX; 
	delete[] *EnemyY;
	delete[] *EnemyVelX; 
	delete[] *EnemyVelY; 
	delete[] *EnemyMovingLeft; 
	delete[] *EnemyBounceCount;
	delete[] *EnemyBeingPulled; 
	delete[] *EnemyIdle; 
	delete[] *EnemyJumping; 
	delete[] *EnemyCoolDown;
	delete[] *EnemyPosChange; 
	delete[] *EnemyFrameChange; 
	delete[] *EnemyShooting; 
	delete[] *ProjectileActive; 
	delete[] *ProjectilePos;
	
	//store new addresses in ptrs
	*EnemySp = newSp; 
	*EnemyType = newType; 
	*EnemyX = newX; 
	*EnemyY = newY;
	*EnemyVelX = newVelX; 
	*EnemyVelY = newVelY; 
	*EnemyMovingLeft = newMovingLeft; 
	*EnemyBounceCount = newBounce;
	*EnemyBeingPulled = newBeingPulled; 
	*EnemyIdle = newIdle; 
	*EnemyJumping = newJumping; 
	*EnemyCoolDown = newCoolDown;
	*EnemyPosChange = newPosChange; 
	*EnemyFrameChange = newFrameChange; 
	*EnemyShooting = newShooting;
	*ProjectileActive = newProjActive; 
	*ProjectilePos = newProjPos;

	return;
}

void SpawnEnemy(int YPos, int enemyClass, int width, int& enemyCount, int& arrayCapacity, int& ActiveEnemies, Sprite** EnemySp, int** EnemyType, int** EnemyX, int** EnemyY, float** EnemyVelX, float** EnemyVelY, bool** EnemyMovingLeft, int** EnemyBounceCount, bool** EnemyBeingPulled, bool** EnemyIdle, bool** EnemyJumping, int** EnemyCoolDown, bool** EnemyPosChange, int** EnemyFrameChange, bool** EnemyShooting, bool** ProjectileActive, int (**ProjectilePos)[2])
{
    if (enemyCount >= arrayCapacity-2) {
        CreateNewArrays(arrayCapacity, EnemySp, EnemyType, EnemyX, EnemyY, EnemyVelX, EnemyVelY, EnemyMovingLeft, EnemyBounceCount, EnemyBeingPulled, EnemyIdle, EnemyJumping, EnemyCoolDown, EnemyPosChange, EnemyFrameChange, EnemyShooting, ProjectileActive, ProjectilePos);
        
        for(int k=arrayCapacity;k<arrayCapacity+10;k++){
             (*EnemyX)[k]=-1000; 
			 (*EnemyY)[k]=-1000; 
             (*ProjectilePos)[k][0] = -1000; 
			 (*ProjectilePos)[k][1] = -1000;
             (*EnemyVelX)[k]=0; 
			 (*EnemyVelY)[k]=0;
			 (*EnemyMovingLeft)[k]=0; 
             (*EnemyBounceCount)[k]=0; 
			 (*EnemyBeingPulled)[k]=0;
             (*EnemyIdle)[k]=0; 
			 (*EnemyJumping)[k]=0; 
			 (*EnemyCoolDown)[k]=0; 
             (*EnemyPosChange)[k]=0; 
			 (*EnemyFrameChange)[k]=0; 
			 (*EnemyShooting)[k]=0; 
             (*ProjectileActive)[k]=0;
        }
        arrayCapacity += 10;
    }

    if ((*EnemyX)[enemyCount] ==-1000) {
        (*EnemyType)[enemyCount]=enemyClass;
        (*EnemyX)[enemyCount]=64*enemyCount;
        
        if(enemyCount> 0) 
		(*EnemyX)[enemyCount]=(rand()%(width-2) + 1)*64;
        
        (*EnemyY)[enemyCount] = YPos;
        (*EnemySp)[enemyCount].setPosition((*EnemyX)[enemyCount], (*EnemyY)[enemyCount]);
        ActiveEnemies++;
        enemyCount++; 
    }
}

void DisplayEnemies(RenderWindow& Window, int Index, int* EnemyType, int** EnemyPos, Sprite* EnemySp) {
    static Texture GhostTex;
    static Texture SkeletonTex;
    static Texture InvisibleManTex;
    static Texture ChelnovTex;
    static bool texturesLoaded = 0;
    
    if (!texturesLoaded) {
        GhostTex.loadFromFile("Data/Ghost.png");
        SkeletonTex.loadFromFile("Data/skeleton.png");
        InvisibleManTex.loadFromFile("Data/invisibleMan.png");
        ChelnovTex.loadFromFile("Data/chelnov.png");
        texturesLoaded = 1;
    }
    
    if (EnemyType[Index]==1) { // ghost
		EnemySp[Index].setTexture(GhostTex);
        EnemySp[Index].setTextureRect(IntRect(5,5,32,32));
    	EnemySp[Index].setScale(2,2);
	}
    else 
	if (EnemyType[Index]==2) { // skeleton
		EnemySp[Index].setTexture(SkeletonTex);
        EnemySp[Index].setTextureRect(IntRect(8,0,32,110));
        EnemySp[Index].setScale(2,2);
	}
    else 
	if (EnemyType[Index]==3) { // invisible man
		EnemySp[Index].setTexture(InvisibleManTex);
        EnemySp[Index].setTextureRect(IntRect(8,0,32,110));
    	EnemySp[Index].setScale(2,2);
	}
    else 
	if (EnemyType[Index] == 4) { // chelnov
		EnemySp[Index].setTexture(ChelnovTex);
        EnemySp[Index].setTextureRect(IntRect(11,5,32,45));
        EnemySp[Index].setScale(2,2);
	}
    
    EnemySp[Index].setPosition(EnemyPos[Index][0], EnemyPos[Index][1]);
    Window.draw(EnemySp[Index]);
}

void reload(float& player_x, float& player_y, Sprite &PlayerSprite, int cell_size, int height, int PlayerHeight, bool& FirstRun)
{
	player_x=cell_size;
	player_y=(height-2)*cell_size-PlayerHeight;
	PlayerSprite.setPosition(player_x,player_y);
	FirstRun=1;
	return;
}

bool power_deploy(int enemy_x, int enemy_y,int& power_x, int &power_y,int width , int height, int& power_select )
{
	if(enemy_x < width*64 && enemy_x>0 && enemy_y>0 && enemy_y<height*64)
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
	static bool texLoaded = false;
    if(!texLoaded){
	    texpower.loadFromFile("Data/player.png");
        texLoaded = true;
    }
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

bool power_up(int power_x, int power_y, float player_x, float player_y, int playerWidth, int playerHeight,bool& powerPlaced,int power_select, int& speed,int &lives, int& vacuum_range, int& vacuum_width,int &prevlife)
{
	if(power_x < player_x+playerWidth && power_x+64 > player_x && player_y+playerHeight > power_y && power_y+64>player_y)
		{
			powerPlaced=0;
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
			prevlife=lives;
			return 1;
		}
	else return 0;
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

void singleShot(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int vacuum_x, int vacuum_y, int captured_enemies_index[], int captured_enemies_type[], int& captured_count, int Ghost_x[], int Ghost_y[], float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], float InvisibleManShotVelX[], float InvisibleManShotVelY[])
{
	static bool keyHeld = false; 
	if (Keyboard::isKeyPressed(Keyboard::E)) {
		if (!keyHeld && captured_count > 0) {
			keyHeld = true;
			
			captured_count --;
			int enemyID = captured_enemies_index[captured_count];
			int type = captured_enemies_type[captured_count];
			
			float vacuum_start_x, vacuum_start_y;
			if (vacuum_x == 1) { 
	            vacuum_start_x = player_x + PlayerWidth; 
			} else if (vacuum_x == -1) { 
			    vacuum_start_x = player_x; 
			} else vacuum_start_x = player_x + PlayerWidth/2; 
			
			if (vacuum_y == -1) { 
			    vacuum_start_y = player_y; 
			} else if (vacuum_y == 1) { 
			    vacuum_start_y = player_y + PlayerHeight;
			} else vacuum_start_y = player_y + PlayerHeight/2; 
			
			float speed = 18; 
			float velX = 0, velY = 0;
			
			if (vacuum_x != 0) { 
				velX = vacuum_x * speed; 
				velY = vacuum_y * speed/2; 
				}
			else if (vacuum_y != 0) { 
				velX = 0; 
				velY = vacuum_y * speed; 
				}
				
			if (type==0) { 
				Ghost_x[enemyID] = static_cast<int>(vacuum_start_x); 
				Ghost_y[enemyID] = static_cast<int>(vacuum_start_y);
				GhostShotVelX[enemyID] = velX;
				GhostShotVelY[enemyID] = velY;
				}
			else if (type == 1) { 
				skeleton_x[enemyID] = static_cast<int>(vacuum_start_x);
				skeleton_y[enemyID] = static_cast<int>(vacuum_start_y);
				SkeletonShotVelX[enemyID] = velX;
				SkeletonShotVelY[enemyID] = velY;
				}
			else if (type == 2) { 
				invisibleMan_x[enemyID] = static_cast<int>(vacuum_start_x);
				invisibleMan_y[enemyID] = static_cast<int>(vacuum_start_y);
				InvisibleManShotVelX[enemyID] = velX;
				InvisibleManShotVelY[enemyID] = velY;
				}
			}
		}
	else keyHeld = false;
}

void vacuum_suck(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int& vacuum_x, int& vacuum_y, int maxcap, int vacuum_range, int vacuum_width, int captured_enemies_index[], int& captured_count, int Ghost_x[], int Ghost_y[], int num_ghosts, bool GhostBeingPulled[],bool Firstrun,RenderWindow& window, int player)
{
	static int FrameCount=0;
	static int starting_x=200;

	int starting_y;
	if(player==1)
		 starting_y=174;
	else	
		starting_y=337;
	
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
    beam.setScale(vacuum_range/2,vacuum_range/2);

    beam.setOrigin(16,16);

	float vacuum_start_x, vacuum_start_y;
	
	if (vacuum_x == 1) { 
	    vacuum_start_x = player_x + PlayerWidth; 
	} else if (vacuum_x == -1) { 
	    vacuum_start_x = player_x; 
	} else vacuum_start_x = player_x + PlayerWidth/2; 
	
	if (vacuum_y == -1) { 
	    vacuum_start_y = player_y; 
	} else if (vacuum_y == 1) { 
	    vacuum_start_y = player_y + PlayerHeight;
	} else vacuum_start_y = player_y + PlayerHeight/2; 
	
	beam.setPosition(vacuum_start_x,vacuum_start_y);

	float beam_start = 0, beam_top = 0, beam_length = 0, beam_width = 0;
	if (vacuum_x == 1) { 
		beam_start = vacuum_start_x;
		beam_top = vacuum_start_y - ((float)vacuum_width/2); 
		beam_length = vacuum_range;
		beam_width = vacuum_width;
		beam.setRotation(180.0); 
        beam.setScale(scale,scale);
	} else if (vacuum_x == -1) { 
		beam_start = vacuum_start_x - vacuum_range;
		beam_top = vacuum_start_y - ((float)vacuum_width/2); 
		beam_length = vacuum_range;
		beam_width = vacuum_width;
		beam.setRotation(0.0); 
        beam.setScale(scale,scale);
	} else if (vacuum_y == -1) { 
		beam_start = vacuum_start_x - ((float)vacuum_width/2); 
		beam_top = vacuum_start_y - vacuum_range;
		beam_length = vacuum_width;
		beam_width = vacuum_range;
		beam.setRotation(-90.0); 
        beam.setScale(scale,scale);
	} else if (vacuum_y == 1) { 
		beam_start = vacuum_start_x - ((float)vacuum_width/2); 
		beam_top = vacuum_start_y ;
		beam_length = vacuum_width;
		beam_width = vacuum_range;
		beam.setRotation(90.0); 
        beam.setScale(scale,scale);	
    }
	
	int ghost_size = 64; 
	
	if (Keyboard::isKeyPressed(Keyboard::Space) && captured_count < maxcap) { 
		window.draw(beam);
		for (int i = 0; i < num_ghosts; i++) {
			if (Ghost_x[i] > 0 && !GhostBeingPulled[i]) { 
				bool collisionX = Ghost_x[i] + ghost_size > beam_start && Ghost_x[i] < beam_start + beam_length; 
				bool collisionY = Ghost_y[i] + ghost_size > beam_top && Ghost_y[i] < beam_top + beam_width; 
				
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

void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool skeletonIdle[],int & lives,const int skeletonCount, int currentSkeleton, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool skeletonJumping[],int jumpCoolDown[], bool SkeletonBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float SkeletonShotVelX[], float SkeletonShotVelY[], int SkeletonBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[],int & score)
{
    static int Frame=192;    
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

	if (SkeletonShotVelX[i] != 0 || SkeletonShotVelY[i] != 0) { 
		int next_x = skeleton_x[i] + static_cast<int>(SkeletonShotVelX[i]); 
		int gridX = next_x / cell_size; 
		int gridY = skeleton_y[i] / cell_size;
		
		if (next_x <= 0 || next_x >= (width - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) 
		{ 
			SkeletonShotVelX[i] = -SkeletonShotVelX[i]; 
			SkeletonBounceCount[i]++;
		}
		else skeleton_x[i] = next_x;
		
		SkeletonShotVelY[i] += 1; 
		if (SkeletonShotVelY[i] > 20) 
			SkeletonShotVelY[i] = 20; 
		
		int next_y = skeleton_y[i] + static_cast<int>(SkeletonShotVelY[i]);
		gridX = skeleton_x[i] / cell_size; 
		gridY = next_y / cell_size;
		
		if (next_y <= 0 || next_y >= (height - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#'))
		{ 
			if (SkeletonShotVelY[i] > 0) { 
				SkeletonShotVelY[i] = 0; 
				if (gridY < height) 
					skeleton_y[i] = (gridY - 1) * cell_size;
				if (SkeletonShotVelX[i] == 0) {
					if (rand() % 2 == 0)
						SkeletonShotVelX[i] = 15; 
					else SkeletonShotVelX[i] = -15; 
					}
				}
			else if (SkeletonShotVelY[i] < 0) { 
				SkeletonShotVelY[i] = 0;
				if (SkeletonShotVelX[i] == 0) { 
				if (rand() % 2 == 0)
						SkeletonShotVelX[i] = 15; 
					else SkeletonShotVelX[i] = -15; 
					}
				}
		} 
		else skeleton_y[i] = next_y;
		
		if (SkeletonBounceCount[i] >= 5) {
			SkeletonShotVelX[i] = 0;
			SkeletonShotVelY[i] = 0;
			skeleton_x[i] = -1000;
			skeleton_y[i] = -1000;
			ActiveEnemies--;
						score*=2;
		}
		
		int skeleton_size = 64;
		for (int j = 0; j < GhostCount; j++) {
			if (Ghost_x[j] > 0) { 
				if (!(skeleton_x[i] < Ghost_x[j] - skeleton_size || skeleton_x[i] > Ghost_x[j] + skeleton_size) && !(skeleton_y[i] < Ghost_y[j] - skeleton_size || skeleton_y[i] > Ghost_y[j] + skeleton_size)) {
					Ghost_x[j] = -1000; 
					Ghost_y[j] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					skeleton_x[i] = -1000;
					skeleton_y[i] = -1000;
					ActiveEnemies --;
					score*=2;
				}
			}
		}
		
		for (int j = 0; j < skeletonCount; j++) {
			if (j!= i && skeleton_x[j] > 0) { 
				if (!(skeleton_x[i] < skeleton_x[j] - skeleton_size || skeleton_x[i] > skeleton_x[j] + skeleton_size) && !(skeleton_y[i] < skeleton_y[j] - skeleton_size || skeleton_y[i] > skeleton_y[j] + skeleton_size)) {
					skeleton_x[j] = -1000;
					skeleton_y[j] = -1000;
					skeleton_x[i] = -1000; 
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					ActiveEnemies --;
					score*=2;
				}
			}
		}
		
		for (int j = 0; j < invisibleManCount; j++) {
			if (invisibleMan_x[j] > 0) {
				if (!(skeleton_x[i] < invisibleMan_x[j] - skeleton_size || skeleton_x[i] > invisibleMan_x[j] + skeleton_size) && !(skeleton_y[i] < invisibleMan_y[j] - skeleton_size || skeleton_y[i] > invisibleMan_y[j] + skeleton_size)) {
					invisibleMan_x[j] = -1000;
					invisibleMan_y[j] = -1000;
					skeleton_x[i] = -1000; 
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					ActiveEnemies--;
						score*=2;
				}
			}
		}
		
		for (int j = 0; j < chelnovCount; j++) {
			if (chelnov_x[j] > 0) {
				if (!(skeleton_x[i] < chelnov_x[j] - skeleton_size || skeleton_x[i] > chelnov_x[j] + skeleton_size) && !(skeleton_y[i] < chelnov_y[j] - skeleton_size || skeleton_y[i] > chelnov_y[j] + skeleton_size)) {
					chelnov_x[j] = -1000;
					chelnov_y[j] = -1000;
					skeleton_x[i] = -1000;
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					ActiveEnemies--;
						score*=2;
				}
			}
		}
		
		skeletonSp[i].setPosition(skeleton_x[i], skeleton_y[i]);
		return;
	}
    
    float vacuum_start_x, vacuum_start_y; 
    if (vacuum_x == 1) { 
    vacuum_start_x = player_x + PlayerWidth; 
    } else if (vacuum_x == -1) { 
    vacuum_start_x = player_x; 
    } else vacuum_start_x = player_x + PlayerWidth/2; 
    
    if (vacuum_y == -1) { 
    vacuum_start_y = player_y; 
    } else if (vacuum_y == 1) { 
    vacuum_start_y = player_y + PlayerHeight;
    } else vacuum_start_y = player_y + PlayerHeight/2; 
	
    const float pullspeed = 3;
    if (SkeletonBeingPulled[i]) {
		if (!Keyboard::isKeyPressed(Keyboard::Space)) {
            SkeletonBeingPulled[i] = false; 
            return;
        }
        
        float dx = vacuum_start_x - skeleton_x[i]; 
        float dy = vacuum_start_y - skeleton_y[i]; 
        if (dx > pullspeed) { 
            skeleton_x[i] += pullspeed;
        } else if (dx < -pullspeed) { 
        skeleton_x[i] -= pullspeed;
        } else skeleton_x[i] = vacuum_start_x; 
        
        if (dy > pullspeed) { 
        	skeleton_y[i] += pullspeed;
        } else if (dy < -pullspeed) { 
        	skeleton_y[i] -= pullspeed;
        } else skeleton_y[i] = vacuum_start_y; 

		skeletonSp[i].setPosition(skeleton_x[i], skeleton_y[i]);
        
        if (skeleton_x[i] == static_cast<int>(vacuum_start_x) && skeleton_y[i] == static_cast<int>(vacuum_start_y)) { 
            if (captured_count < maxcap) {
                captured_enemies_index[captured_count] = i;
                captured_enemies_type[captured_count] = 1;
                captured_count ++;
                ActiveEnemies--;
						score*=2;
                
                SkeletonBeingPulled[i] = false;
                skeleton_x[i] = -1000;
                skeleton_y[i] = -1000;
                
                skeletonSp[i].setPosition(skeleton_x[i], skeleton_y[i]); 
            }
        }
        skeletonSp[i].setPosition(skeleton_x[i], skeleton_y[i]);
        return; 
    } 
    else { 
        if (skeleton_x[i] > 0) { 
            if(skeletonJumping[i])
            {
                if(!isMoving[i])
                {
                    bool foundSpot = false;
                    if(jumpingUp)
                    {
                        for(int skelheight=Jumping_y-2;skelheight>Jumping_y-5&&skelheight>0 && skeletonJumping[i]==1;skelheight--) 
                        {
                            for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) 
                                {
                                    if(lvl[skelheight][row]=='#'){
                                        dest_x[i]=row*cell_size;
                                        dest_y[i]=((skelheight-1)*cell_size)-(cell_size/2)-4;
                                        foundSpot=true;
                                        break;
                                    }
                                }
                            if(foundSpot) break;
                        }
                    }
                    else{
                        for(int skelheight=Jumping_y+3;skelheight<Jumping_y+7&&skelheight<height-1 && skeletonJumping[i]==1;skelheight++) 
                        {
                            for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) 
                                {
                                    if(lvl[skelheight][row]=='#'){
                                        dest_x[i]=row*cell_size;
                                        dest_y[i]=((skelheight-1)*cell_size)-(cell_size/2)-4;
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

                    float Pixels = 10; 

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
                if(skeletonIdle[i]){ 
                    if(FrameCount-FramePosForChange[i]==300ull){
                        currentIdleFrame[i]++;
                    }
                    if(currentIdleFrame[i]>2)
                    {
                                skeletonIdle[i]=0;
                                currentIdleFrame[i]=0;
                    }
                    else
                        skeletonSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,110));
                }

                if(!skeletonIdle[i]) 
                        if(!skeletonMovingLeft[i]){
                            if(lvl[grid_y_skeleton+1][grid_x_skeleton+1]!='#'||lvl[grid_y_skeleton][grid_x_skeleton+1]=='#'){
                                skeletonMovingLeft[i]=1;
                                if((rand()%100)>60 && lvl[grid_y_skeleton+1][grid_x_skeleton+1]!='#' &&  skeletonJumping[i]==0 && jumpCoolDown[i]==0){ 
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
                            if(lvl[grid_y_skeleton+1][grid_x_skeleton]!='#'||lvl[grid_y_skeleton][grid_x_skeleton]=='#'){ 
                                skeletonMovingLeft[i]=0;

                                if((rand()%100)>60 && lvl[grid_y_skeleton+1][grid_x_skeleton]!='#' && skeletonJumping[i]==0 && jumpCoolDown[i]==0){ 
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

    if(!SkeletonBeingPulled[i])
        if(!(player_x<skeleton_x[i]-50||player_x>skeleton_x[i]+50)&&!(player_y<skeleton_y[i]-32||player_y>skeleton_y[i]+32)) 
        {
            player_x=cell_size;
            player_y=(height-2)*cell_size-PlayerHeight;
            PlayerSprite.setPosition(player_y,player_x);
            lives--;
        }
    
    if(!skeletonIdle[i] && !skeletonJumping[i])
    skeletonSp[i].setTextureRect(IntRect(Frame,0,32,110));
    
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

    if(FrameCount-FramePosForChange[i]==1200ull)
    {
        posChangeHappened[i]=0;
    }

    if(!posChangeHappened[i]&&!skeletonJumping[i])
        {
                int check=rand()%100;
    
            if(check<30){ 
                    skeletonMovingLeft[currentSkeleton]=!skeletonMovingLeft[currentSkeleton];
                    currentSkeleton++;
                    posChangeHappened[i]=1;
                    FramePosForChange[i]=FrameCount;
                    currentSkeleton=currentSkeleton>3?0:currentSkeleton;
            }else if(!skeletonIdle[i] && (FrameCount+i*150)%600<10)
                {
                    currentIdleFrame[i]=0;
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
    return;
	}
}

void invisibleManMove(int invisibleMan_x[],int invisibleMan_y[],int width,Sprite invisibleManSp[],bool invisibleManMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool invisibleManIdle[],int & lives,const int invisibleManCount, int currentinvisibleMan, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool invisibleManJumping[],int jumpCoolDown[], bool invisibleManBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float InvisibleManShotVelX[], float InvisibleManShotVelY[], int InvisibleManBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int chelnov_x[], int chelnov_y[], int chelnovCount, float chelnovShotVelX[], float chelnovShotVelY[],int & score)
{
	static int Frame=155;	 
	static bool jumpingUp=0;
	static int FrameCount=0;
	
	if (InvisibleManShotVelX[i] != 0 || InvisibleManShotVelY[i] != 0) { 
        int next_x = invisibleMan_x[i] + static_cast<int>(InvisibleManShotVelX[i]);
        int gridX = next_x / cell_size;
        int gridY = invisibleMan_y[i] / cell_size;
        
        if (next_x <= 0 || next_x >= (width-1)*cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) {
            InvisibleManShotVelX[i] = -InvisibleManShotVelX[i];
            InvisibleManBounceCount[i]++;
        }
        else invisibleMan_x[i] = next_x;
        
        InvisibleManShotVelY[i] += 1;
        if (InvisibleManShotVelY[i] > 20) 
            InvisibleManShotVelY[i] = 20;
        
        int next_y = invisibleMan_y[i] + static_cast<int>(InvisibleManShotVelY[i]);
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
            ActiveEnemies--;
			score*=2;
		
		
		}
        
        int invis_size = 64;
        
        for (int j = 0; j < GhostCount; j++) {
            if (Ghost_x[j] > 0) {
                if (!(invisibleMan_x[i] < Ghost_x[j] - invis_size || invisibleMan_x[i] > Ghost_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < Ghost_y[j] - invis_size || invisibleMan_y[i] > Ghost_y[j] + invis_size)) {
                    Ghost_x[j] = -1000;
                    Ghost_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    ActiveEnemies--;

						score*=2;
                }	
            }
        }
        
        for (int j = 0; j < skeletonCount; j++) {
            if (skeleton_x[j] > 0) {
                if (!(invisibleMan_x[i] < skeleton_x[j] - invis_size || invisibleMan_x[i] > skeleton_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < skeleton_y[j] - invis_size || invisibleMan_y[i] > skeleton_y[j] + invis_size)) {
                    skeleton_x[j] = -1000;
                    skeleton_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    ActiveEnemies--;
						score*=2;
                }
            }
        }
        
        for (int j = 0; j < invisibleManCount; j++) {
            if (j != i && invisibleMan_x[j] > 0) {
                if (!(invisibleMan_x[i] < invisibleMan_x[j] - invis_size || invisibleMan_x[i] > invisibleMan_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < invisibleMan_y[j] - invis_size || invisibleMan_y[i] > invisibleMan_y[j] + invis_size)) {
                    invisibleMan_x[j] = -1000;
                    invisibleMan_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    ActiveEnemies--;
						score*=2;
                }
            }
        }
        
        for (int j = 0; j < chelnovCount; j++) {
            if (chelnov_x[j] > 0) {
                if (!(invisibleMan_x[i] < chelnov_x[j] - invis_size || invisibleMan_x[i] > chelnov_x[j] + invis_size) && 
                    !(invisibleMan_y[i] < chelnov_y[j] - invis_size || invisibleMan_y[i] > chelnov_y[j] + invis_size)) {
                    chelnov_x[j] = -1000;
                    chelnov_y[j] = -1000;
                    invisibleMan_x[i] = -1000;
                    invisibleMan_y[i] = -1000;
                    InvisibleManShotVelX[i] = 0;
                    InvisibleManShotVelY[i] = 0;
                    ActiveEnemies--;
						score*=2;
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
	static int tpCounter[4]={0}; 
    static bool isFadingIn[4]={0};
    static int TargetJumpX[4]={0}; 
    static int TargetJumpY[4]={0}; 
	int JumpingFramesPos[4]={366,400,435,469};

	float vacuum_start_x, vacuum_start_y; 
	if (vacuum_x == 1) { 
	vacuum_start_x = player_x + PlayerWidth; 
	} else if (vacuum_x == -1) { 
	vacuum_start_x = player_x; 
	} else vacuum_start_x = player_x + PlayerWidth/2; 
	
	if (vacuum_y == -1) { 
	vacuum_start_y = player_y; 
	} else if (vacuum_y == 1) { 
	vacuum_start_y = player_y + PlayerHeight;
	} else vacuum_start_y = player_y + PlayerHeight/2; 
	
	const float pullspeed = 3;
	if (invisibleManBeingPulled[i]) {
		
		if (!Keyboard::isKeyPressed(Keyboard::Space)) {
			invisibleManBeingPulled[i] = false; 
			return;
		}
		
		float dx = vacuum_start_x - invisibleMan_x[i]; 
		float dy = vacuum_start_y - invisibleMan_y[i]; 
		if (dx > pullspeed) { 
			invisibleMan_x[i] += pullspeed;
		} else if (dx < -pullspeed) { 
			invisibleMan_x[i] -= pullspeed;
		} else invisibleMan_x[i] = vacuum_start_x; 
		
		if (dy > pullspeed) { 
			invisibleMan_y[i] += pullspeed;
		} else if (dy < -pullspeed) { 
			invisibleMan_y[i] -= pullspeed;
		} else invisibleMan_y[i] = vacuum_start_y; 
		
		if (invisibleMan_x[i] == static_cast<int>(vacuum_start_x) && invisibleMan_y[i] == static_cast<int>(vacuum_start_y)) { 
			if (captured_count < maxcap) {
				captured_enemies_index[captured_count] = i;
				captured_enemies_type[captured_count] = 2;
				captured_count += 1;
				score+=150;
				invisibleManBeingPulled[i] = false;
				invisibleMan_x[i] = -1000;
				invisibleMan_y[i] = -1000;
				}
			}
		} 
	else { 
	
		if (invisibleMan_x[i] > 0) { 
	
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

	if(invisibleManIdle[i]){ 
		if( FrameCount-FramePosForChange[i]==300ull){
			currentIdleFrame[i]++;
		}
		if(currentIdleFrame[i]>2)
		{
					invisibleManIdle[i]=0;
					currentIdleFrame[i]=0;
		}
		else
			invisibleManSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,110));
	}

	if(!invisibleManIdle[i] && !invisibleManJumping[i]) 
			if(!invisibleManMovingLeft[i]){
				if(lvl[grid_y_invisibleMan+1][grid_x_invisibleMan+1]!='#'||lvl[grid_y_invisibleMan][grid_x_invisibleMan+1]=='#'){
					invisibleManMovingLeft[i]=1;
					if((rand()%100)>60 && lvl[grid_y_invisibleMan+1][grid_x_invisibleMan+1]!='#' &&  invisibleManJumping[i]==0 && jumpCoolDown){ 
                            
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

				if(lvl[grid_y_invisibleMan+1][grid_x_invisibleMan]!='#'||lvl[grid_y_invisibleMan][grid_x_invisibleMan]=='#'){ 
					invisibleManMovingLeft[i]=0;

					if((rand()%100)>60 && lvl[grid_y_invisibleMan+1][grid_x_invisibleMan]!='#' && invisibleManJumping[i]==0 && jumpCoolDown[i]==0){ 
                            
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
					if(grid_x_invisibleMan-1>=0 )
					invisibleMan_x[i]-=1;
					else	
					invisibleManMovingLeft[i]=0;
	}
	}

	invisibleManSp[i].setPosition(invisibleMan_x[i],invisibleMan_y[i]);

	if(!invisibleManBeingPulled[i])
	if(!(player_x<invisibleMan_x[i]-50||player_x>invisibleMan_x[i]+50)&&!(player_y<invisibleMan_y[i]-55||player_y>invisibleMan_y[i]+55)) 
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);
			lives--;
		}
	if(!invisibleManIdle[i] && !invisibleManJumping[i])
	invisibleManSp[i].setTextureRect(IntRect(Frame,0,30,110));
	
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

	if(FrameCount-FramePosForChange[i]==1200ull)
	{
		posChangeHappened[i]=0;
	}

	if(!posChangeHappened[i]&&!invisibleManJumping[i])
		{
				int check=rand()%100;
	
			if(check<30){ 
					invisibleManMovingLeft[currentinvisibleMan]=!invisibleManMovingLeft[currentinvisibleMan];
					currentinvisibleMan++;
					posChangeHappened[i]=1;
					FramePosForChange[i]=FrameCount;
					currentinvisibleMan=currentinvisibleMan>3?0:currentinvisibleMan;
			}else if(!invisibleManIdle[i] && (FrameCount+i*150)%600<10)
				{
					currentIdleFrame[i]=0;
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
	return;
}

void chelnovMove(int chelnov_x[], int chelnov_y[], int width, Sprite chelnovSp[], bool chelnovMovingLeft[], int i, float& player_x, float& player_y, char **lvl, Sprite &PlayerSprite, int cell_size, int PlayerHeight, int height, bool chelnovshooting[], int & lives, const int chelnovCount, int currentchelnov, bool posChangeHappened[], int FramePosForChange[], bool& FirstRun, bool chelnovJumping[], int jumpCoolDown[], bool chelnovBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int captured_enemies_type[], float chelnovShotVelX[], float chelnovShotVelY[],bool projectileActive[], int projectilePos[][2], RenderWindow& window, int chelnovBounceCount[], int& ActiveEnemies, int Ghost_x[], int Ghost_y[], int GhostCount, float GhostShotVelX[], float GhostShotVelY[], int skeleton_x[], int skeleton_y[], int skeletonCount, float SkeletonShotVelX[], float SkeletonShotVelY[], int invisibleMan_x[], int invisibleMan_y[], int invisibleManCount, float InvisibleManShotVelX[], float InvisibleManShotVelY[],int&score)
{
    static int Frame=40;    
    static bool jumpingUp=0;
    static int FrameCount=0;
    int grid_x_chelnov=chelnov_x[i]/64;
    int grid_y_chelnov=(chelnov_y[i]+45)/64;
    if((chelnov_y[i]+45)<height)
    grid_y_chelnov=(chelnov_y[i]+45)/64;
    static int currentshootingFrame[3]={0};
	int shootingY=94;
    int shootingFramepos[3][2]={{143,32},{174,45},{222,45}};
    static int Jumping_x=0,Jumping_y=0;
    int JumpingFramePos=76;
    static float dest_x[20]={0};
    static float dest_y[20]={0};
    static bool isMoving[20]={0};
	static float ProjectileDest[20][2]={{0}};
	
	static Sprite projectileSp[20];
	static Texture projectileTex;
	static bool texLoaded=false;

	if(FrameCount%240==0)
	{
		int temp=rand()%chelnovCount;
		chelnovshooting[temp]=1;
	}

	if(!texLoaded){ 
		projectileTex.loadFromFile("Data/chelnov.png");
		for(int j=0;j<20;j++){
			projectileSp[j].setTexture(projectileTex);
			projectileSp[j].setTextureRect(IntRect(232,60,14,14));
			projectileSp[j].setScale(2,2);
		}
		texLoaded=true;
	}

	if(projectileActive[i])
	{
		if(ProjectileDest[i][0]==0||ProjectileDest[i][0]==width||ProjectileDest[i][1]==0||ProjectileDest[i][1]==height)
			projectileActive[i]=0;

		 float dx=ProjectileDest[i][0]-projectilePos[i][0]; 
         float dy=ProjectileDest[i][1]-projectilePos[i][1];
         float dist= sqrt(dx*dx + dy*dy);

         float Pixels = 10; 

         if(dist<=Pixels)
         {
			projectilePos[i][0]=-1000;
			projectilePos[i][1]=-1000;
			projectileActive[i]=0;
		 }
		 else
		 {
			projectilePos[i][0]+= static_cast<int>((dx/dist)*Pixels);
			projectilePos[i][1]+= static_cast<int>((dy/dist)*Pixels);
		 }
            
		projectileSp[i].setPosition(projectilePos[i][0],projectilePos[i][1]);
		window.draw(projectileSp[i]);
		
		if(!(player_x<projectilePos[i][0]-14||player_x>projectilePos[i][0]+14)&&!(player_y<projectilePos[i][1]-14||player_y>projectilePos[i][1]+14))
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);
			lives--;
			projectileActive[i]=0;
			projectilePos[i][0]=-1000;
			projectilePos[i][1]=-1000;
		}
	}

	if (chelnovShotVelX[i] != 0 || chelnovShotVelY[i] != 0) { 
		int next_x = chelnov_x[i] + static_cast<int>(chelnovShotVelX[i]); 
		int gridX = next_x / cell_size; 
		int gridY = chelnov_y[i] / cell_size;
		
		if (next_x <= 0 || next_x >= (width - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#')) 
		{ 
			chelnovShotVelX[i] = -chelnovShotVelX[i]; 
			chelnovBounceCount[i]++;
		}
		else chelnov_x[i] = next_x;
		
		chelnovShotVelY[i] += 1; 
		if (chelnovShotVelY[i] > 20) 
			chelnovShotVelY[i] = 20; 
		
		int next_y = chelnov_y[i] + static_cast<int>(chelnovShotVelY[i]);
		gridX = chelnov_x[i] / cell_size; 
		gridY = next_y / cell_size;
		
		if (next_y <= 0 || next_y >= (height - 1) * cell_size || (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height && lvl[gridY][gridX] == '#'))
		{ 
			if (chelnovShotVelY[i] > 0) { 
				chelnovShotVelY[i] = 0; 
				if (gridY < height) 
					chelnov_y[i] = (gridY - 1) * cell_size;
				if (chelnovShotVelX[i] == 0) {
					if (rand() % 2 == 0)
						chelnovShotVelX[i] = 15; 
					else chelnovShotVelX[i] = -15; 
					}
				}
				
			else if (chelnovShotVelY[i] < 0) { 
				chelnovShotVelY[i] = 0;
				if (chelnovShotVelX[i] == 0) { 
				if (rand() % 2 == 0)
						chelnovShotVelX[i] = 15; 
					else chelnovShotVelX[i] = -15; 
					}
				}
		} 
		else chelnov_y[i] = next_y;
		
		if (chelnovBounceCount[i] >= 5) {
			chelnovShotVelX[i] = 0;
			chelnovShotVelY[i] = 0;
			chelnov_x[i] = -1000;
			chelnov_y[i] = -1000;
			ActiveEnemies--;
			score*=2;
		}
		
		int chelnov_size = 64;
		for (int j = 0; j < GhostCount; j++) {
			if(Ghost_x[j] > 0) { 
				if (!(chelnov_x[i] < Ghost_x[j] - chelnov_size || chelnov_x[i] > Ghost_x[j] + chelnov_size) && !(chelnov_y[i] < Ghost_y[j] - chelnov_size || chelnov_y[i] > Ghost_y[j] + chelnov_size)) {
					Ghost_x[j] = -1000; 
					Ghost_y[j] = -1000;
					chelnovShotVelX[i] = 0;
					chelnovShotVelY[i] = 0;
					chelnov_x[i] = -1000;
					chelnov_y[i] = -1000;
					ActiveEnemies --;
				}
			}
		}
		
		for (int j = 0; j < skeletonCount; j++) {
			if (skeleton_x[j] > 0) { 
				if (!(chelnov_x[i] < skeleton_x[j] - chelnov_size || chelnov_x[i] > skeleton_x[j] + chelnov_size) && !(chelnov_y[i] < skeleton_y[j] - chelnov_size || chelnov_y[i] > skeleton_y[j] + chelnov_size)) {
					skeleton_x[j] = -1000;
					skeleton_y[j] = -1000;
					skeleton_x[i] = -1000; 
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					ActiveEnemies --;
					score*=2;
				}
			}
		}
		
		for (int j = 0; j < invisibleManCount; j++) {
			if (invisibleMan_x[j] > 0) {
				if (!(chelnov_x[i] < invisibleMan_x[j] - chelnov_size || chelnov_x[i] > invisibleMan_x[j] + chelnov_size) && !(chelnov_y[i] < invisibleMan_y[j] - chelnov_size || chelnov_y[i] > invisibleMan_y[j] + chelnov_size)) {
					invisibleMan_x[j] = -1000;
					invisibleMan_y[j] = -1000;
					chelnov_x[i] = -1000; 
					chelnov_y[i] = -1000;
					chelnovShotVelX[i] = 0;
					chelnovShotVelY[i] = 0;
					ActiveEnemies--;
						score*=2;
				}
			}
		}
		
		for (int j = 0; j < chelnovCount; j++) {
			if (j!=i && chelnov_x[j] > 0) {
				if (!(chelnov_x[i] < chelnov_x[j] - chelnov_size || chelnov_x[i] > chelnov_x[j] + chelnov_size) && !(chelnov_y[i] < chelnov_y[j] - chelnov_size || chelnov_y[i] > chelnov_y[j] + chelnov_size)) {
					chelnov_x[j] = -1000;
					chelnov_y[j] = -1000;
					skeleton_x[i] = -1000;
					skeleton_y[i] = -1000;
					SkeletonShotVelX[i] = 0;
					SkeletonShotVelY[i] = 0;
					ActiveEnemies--;
						score*=2;
				}
			}
		}
		
		chelnovSp[i].setPosition(chelnov_x[i], chelnov_y[i]);
		return;
	}
	
	if (chelnov_x[i] <= 0) { 
		return;
	}
	
    float vacuum_start_x, vacuum_start_y; 
    if (vacuum_x == 1) { 
		vacuum_start_x = player_x + PlayerWidth; 
    } else if (vacuum_x == -1) { 
		vacuum_start_x = player_x; 
    } else {
		vacuum_start_x = player_x + PlayerWidth/2; 
	}
    
    if (vacuum_y == -1) { 
		vacuum_start_y = player_y; 
    } else if (vacuum_y == 1) { 
		vacuum_start_y = player_y + PlayerHeight;
    } else {
		vacuum_start_y = player_y + PlayerHeight/2; 
	}
    
    const float pullspeed = 3;
    if (chelnovBeingPulled[i]) {
        if (!Keyboard::isKeyPressed(Keyboard::Space)) {
            chelnovBeingPulled[i] = false; 
            return;
        }
        
        float dx = vacuum_start_x - chelnov_x[i]; 
        float dy = vacuum_start_y - chelnov_y[i]; 
        if (dx > pullspeed) { 
            chelnov_x[i] += pullspeed;
        } else if (dx < -pullspeed) { 
            chelnov_x[i] -= pullspeed;
        } else {
			chelnov_x[i] = static_cast<int>(vacuum_start_x); 
		}
        
        if (dy > pullspeed) { 
            chelnov_y[i] += pullspeed;
        } else if (dy < -pullspeed) { 
            chelnov_y[i] -= pullspeed;
        } else {
			chelnov_y[i] = static_cast<int>(vacuum_start_y); 
		}
		
		chelnovSp[i].setPosition(chelnov_x[i], chelnov_y[i]);
        
        if (chelnov_x[i] == static_cast<int>(vacuum_start_x) && chelnov_y[i] == static_cast<int>(vacuum_start_y)) { 
            if (captured_count < maxcap) {
                captured_enemies_index[captured_count] = i;
                captured_enemies_type[captured_count] = 3;
                captured_count += 1;
                score+=200;
                chelnovBeingPulled[i] = false;
                chelnov_x[i] = -1000;
                chelnov_y[i] = -1000;
            }
        }
		return;
    }

    if(chelnovJumping[i])
    {
        if(!isMoving[i])
        {
             bool foundSpot = false;

            if(jumpingUp)
            {
                for(int skelheight=Jumping_y-2;skelheight>Jumping_y-5&&skelheight>0 && chelnovJumping[i]==1;skelheight--) 
                {
                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) 
                        {
                            if(lvl[skelheight][row]=='#'){
                                cout<<skelheight<<endl<<row<<endl;
                                dest_x[i]=row*cell_size;
                                dest_y[i]=((skelheight-1)*cell_size);
                                cout<<"chelnov jumped to "<<chelnov_x[i]<<" and "<<chelnov_y[i];
                                foundSpot=true;
                                break;
                            }
                        }
                    if(foundSpot) break;
                }
            }
            else{
                for(int skelheight=Jumping_y+3;skelheight<Jumping_y+7&&skelheight<height-1 && chelnovJumping[i]==1;skelheight++) 
                {
                    for(int row=Jumping_x-2;row<Jumping_x+2&&row>0&&row<width-3;row++) 
                        {
                            if(lvl[skelheight][row]=='#'){
                                cout<<skelheight<<endl<<row<<endl;
                                dest_x[i]=row*cell_size;
                                dest_y[i]=((skelheight-1)*cell_size);
                                cout<<"chelnov jumped to "<<chelnov_x[i]<<" and "<<chelnov_y[i];
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

            float Pixels = 10; 

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
    if(chelnovshooting[i]){ 
        if(FrameCount-FramePosForChange[i]>=20){
            currentshootingFrame[i]++;
			FramePosForChange[i]=FrameCount;
        }

        if(currentshootingFrame[i]==3 && !projectileActive[i])
		{	
			ProjectileDest[i][0]=player_x;
			ProjectileDest[i][1]=player_y;
			projectilePos[i][0]=chelnov_x[i];
			projectilePos[i][1]=chelnov_y[i];
			projectileActive[i]=1;
		}

        if(currentshootingFrame[i]>3)
        {
                    chelnovshooting[i]=0;
                    currentshootingFrame[i]=0;

        }
        else if(currentshootingFrame[i]<3)
            chelnovSp[i].setTextureRect(IntRect(shootingFramepos[currentshootingFrame[i]][0],shootingY,shootingFramepos[currentshootingFrame[i]][1],40));
    }


    if(!chelnovshooting[i]) 
	{
            if(!chelnovMovingLeft[i]){
                if(lvl[grid_y_chelnov+1][grid_x_chelnov+1]!='#'||lvl[grid_y_chelnov][grid_x_chelnov+1]=='#'){
                    chelnovMovingLeft[i]=1;
                    if((rand()%100)>60 && lvl[grid_y_chelnov+1][grid_x_chelnov+1]!='#' &&  chelnovJumping[i]==0 && jumpCoolDown[i]==0){ 
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
            else if(chelnovMovingLeft[i])
			{
                if(lvl[grid_y_chelnov+1][grid_x_chelnov]!='#'||lvl[grid_y_chelnov][grid_x_chelnov]=='#'){ 
                    chelnovMovingLeft[i]=0;

                    if((rand()%100)>60 && lvl[grid_y_chelnov+1][grid_x_chelnov]!='#' && chelnovJumping[i]==0 && jumpCoolDown[i]==0){ 
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
    }

    chelnovSp[i].setPosition(chelnov_x[i],chelnov_y[i]);

    if(!chelnovBeingPulled[i])
        if(!(player_x<chelnov_x[i]-50||player_x>chelnov_x[i]+50)&&!(player_y<chelnov_y[i]-32||player_y>chelnov_y[i]+32)) 
        {
            player_x=cell_size;
            player_y=(height-2)*cell_size-PlayerHeight;
            PlayerSprite.setPosition(player_y,player_x);
            lives--;
        }
    
    if(!chelnovshooting[i] && !chelnovJumping[i])
    chelnovSp[i].setTextureRect(IntRect(Frame,0,32,45));
    
    if(!chelnovshooting[i])
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

    if(FrameCount-FramePosForChange[i]==1200ull)
    {
        cout<<FrameCount-FramePosForChange[i];
        posChangeHappened[i]=0;
    }

    if(!posChangeHappened[i]&&!chelnovJumping[i])
        {
                int check=rand()%100;
    
            if(check<30){ 
                    chelnovMovingLeft[currentchelnov]=!chelnovMovingLeft[currentchelnov];
                    cout<<"change for chelnov "<<currentchelnov<<"at frame "<<FrameCount<<endl;
                    currentchelnov++;
                    posChangeHappened[i]=1;
                    FramePosForChange[i]=FrameCount;
                    currentchelnov=currentchelnov>3?0:currentchelnov;
            }else if(!chelnovshooting[i] && (FrameCount+i*150)%600<10)
                {
                    currentshootingFrame[i]=0;
                    cout<<"\nchelnov "<<i<<" is shooting\n";
                    chelnovshooting[i]=1;
                    chelnovSp[i].setTextureRect(IntRect(shootingFramepos[currentshootingFrame[i]][0],shootingY,shootingFramepos[currentshootingFrame[i]][1],40));
                    currentshootingFrame[i]=0;
                    FramePosForChange[i]=FrameCount;
                }   
    }
        
    jumpCoolDown[i]-=1;
    jumpCoolDown[i]=jumpCoolDown[i]<0?0:jumpCoolDown[i];

    if(FrameCount%120==0)
        Frame+=33;
    
    if(Frame>142)
        Frame=40;

    FrameCount++;
    return;
}

void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size)
{
	window.draw(bgSprite);

	for (int i=0;i<height;i+=1)
	{
		for (int j=0;j<width;j+=1)
		{

			if (lvl[i][j] == '#'|| lvl[i][j]=='=') 
			{
				blockSprite.setPosition(j*cell_size,(i* (cell_size)+cell_size/2));
				window.draw(blockSprite);
			}
		}
	}

}

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth)

{

	offset_y=player_y;

	offset_y+=velocityY;

	char bottom_left_down = lvl[static_cast<int>((offset_y + Pheight)) / cell_size][static_cast<int>((player_x )) / cell_size];
	char bottom_right_down = lvl[static_cast<int>((offset_y  + Pheight)) / cell_size][static_cast<int>((player_x + Pwidth)) / cell_size];
	char bottom_mid_down = lvl[static_cast<int>((offset_y + Pheight)) / cell_size][static_cast<int>((player_x + Pwidth / 2)) / cell_size];

	if ( (bottom_mid_down =='=' || bottom_mid_down == '#') &&velocityY>=0) 
	{
		onGround = true;
	}
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
}