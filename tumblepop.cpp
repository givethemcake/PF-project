

//todo add skeleton jumping
//we could maybe move the placement of enemies inside the level fucntions will probably make it easier l8r to do stuff 
//this would require a complete change of all game systems not do able in current time 
//todo add win condition for level one




//To Aazan when an enemy is captured decrease their count by one plz


#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include<cstdlib>
#include<ctime>



using namespace sf;
using namespace std;

int screen_x = 1152;
int screen_y = 1000;









void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap, int & lives);

void check_stuck(char** lvl, float& player_x, float& player_y, float& velocityY, int PlayerWidth, int PlayerHeight, int cell_size, int width, int height);

void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, const float& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height, int& vacuum_x, int& vacuum_y);// handle all ingame movement and collision and gun direction aim

void level_one(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, const float& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width);

void level_two(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, const float& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width);

void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size);

void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool skeletonIdle[],int & lives,const int skeletonCount, int currentSkeleton, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool skeletonJumping[]);	                                   

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);

void vacuum_suck(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int& vacuum_x, int& vacuum_y, int maxcap, int vacuum_range, int vacuum_width, int captured_enemies_index[], int& captured_count, int Ghost_x[], int Ghost_y[], int num_ghosts, bool GhostBeingPulled[]);

void invisiblaManMove(int invisibleMan_x[],int invisibleMan_y[],int width,Sprite invisibleManSp[],bool invisibleManMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool invisibleManIdle[]);

int main()
{

	
	
	
	
	
	
	
	
	static bool FirstRun=1;
	static int lives=3;
	static int score=0;
	bool ShowStart=1;



	//set up random number seed
	srand(time(0));


	





	//Ghost Prototype
		//moved to levels
	//defining the skeletons
		//moved to levels 
	





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
	
	int captured_enemies_index[5] = {0}; //
	int captured_count = 0;
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

	PlayerTexture.loadFromFile("Data/player_left.png");
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setScale(3,3);
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
	
	while (window.isOpen())
	{
				Sprite startSprite;
				Texture startTex;
		
			
	
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

					float scaleX = ev.size.width / (float)startTex.getSize().x;
					float scaleY = ev.size.height / (float)startTex.getSize().y;
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
		
		
		
		level=1;
		if(level==1){
			level_one(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength,   speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width);
		}else
			level_two(lvl, height, width, FirstRun, player_x, player_y, PlayerSprite, cell_size, PlayerHeight, captured_enemies_index, captured_count, PlayerWidth, vacuum_x, vacuum_y, maxcap, lives, window, velocityY, isJumping, velocityX, PlayerTexture, onGround, jumpStrength,   speed, friction, counter, terminal_Velocity_x, top_mid_up, vacuum_range, vacuum_width);


		
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




void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height, bool GhostBeingPulled[], int captured_enemies_index[], int& captured_count, int PlayerWidth, int vacuum_x, int vacuum_y, int maxcap,int &lives)
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
			if(grid_x_Ghost+1<width-1 ){
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




		if(lvl[mid_y][mid_x]=='#'||lvl[bottom_y][mid_x]=='#'){
			player_y-=2;
		}else 
			if(lvl[top_y][mid_x]=='#'){

					player_y+=2;


			}else
			{
				isStuck=false;
				break;
			}
			

			return;


	}





}


void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, const float& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height, int& vacuum_x, int& vacuum_y)// handle all ingame movement and collision and gun aim
{



	int grid_y=static_cast<int>(player_y+PlayerHeight/2)/cell_size;  
    	
		int top_mid_up1;		
		int top_mid_up2;
		//int top_mid_up=lvl[(static_cast<int>(player_y-cell_size)/cell_size)][static_cast<int>(player_x+PlayerWidth/2)/cell_size];
		int top_left_up1,top_right_up1,top_left_up2,top_right_up2;

		int bottom_mid1;
		int botttom_mid2;





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
				

				}else
					isJumping=false;


				if(Keyboard::isKeyPressed(Keyboard::Left)){
				int grid_x = static_cast<int>(player_x+5) / cell_size;
    
					if(lvl[grid_y][grid_x]=='#')
						velocityX=0;
					else{
					PlayerTexture.loadFromFile("Data/player_left.png");
					PlayerSprite.setTexture(PlayerTexture);
						velocityX-=speed;
					}
					
				}
				if(Keyboard::isKeyPressed(Keyboard::Right)){
				
				int grid_x=static_cast<int>(player_x+64)/cell_size;
				
				
				
					if(lvl[grid_y][grid_x]=='#')
						velocityX=0;
					else{
					PlayerTexture.loadFromFile("Data/player_right.png");
					PlayerSprite.setTexture(PlayerTexture);
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
						
				
				

				//clamp velocity
				
				//if(velocityX<0){
				//	PlayerSprite.setTextureRect(IntRect(counter*frarmeWidth,10,frarmeWidth,frameHeight));
				//}

				return;

}


void level_one(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, const float& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range,     int vacuum_width){

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
	static Sprite GhostSp[GhostCount];
	static Texture GhostTx;
	GhostTx.loadFromFile("Data/Ghost.png");
	
	static int Ghost_y[GhostCount];
	static int Ghost_x[GhostCount];
	static bool GhostMovingLeft[GhostCount];
	static bool GhostBeingPulled[GhostCount] = {0};
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





	if(FirstRun){
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
			
	} //set the postions of the ghosts and skeletons for the first run









	playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y);
	check_stuck(lvl, player_x,  player_y, velocityY,  PlayerWidth, PlayerHeight,  cell_size,  width,  height);
	vacuum_suck(player_x, player_y,  PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range,  vacuum_width, captured_enemies_index,  captured_count,  Ghost_x, Ghost_y,  8, GhostBeingPulled);//replcaed num_ghosts with 8 for testing 

	//moving enemies
	for(int i=0;i<GhostCount;i++){
	  ghostMove(Ghost_x,Ghost_y,width,GhostSp,GhostMovingLeft,i,player_x,player_y,lvl,PlayerSprite,cell_size,PlayerHeight,height,GhostBeingPulled,captured_enemies_index,captured_count,PlayerWidth,vacuum_x,vacuum_y,maxcap,lives);
	}

	for(int i=0;i<skeletonCount;i++)
	{
 skeletonMove(skeleton_x, skeleton_y, width, skeletonSp, skeletonMovingLeft, i, player_x, player_y,lvl,PlayerSprite, cell_size, PlayerHeight, height,skeletonIdle, lives,  skeletonCount,  currentSkeleton,  posChangeHappened, FramePosForChange, FirstRun,skeletonJumping);                                    




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



}


void level_two(char**lvl, int height, int width, bool& FirstRun, float& player_x, float& player_y,Sprite &PlayerSprite, int cell_size, int PlayerHeight, int captured_enemies_index[], int& captured_count, int PlayerWidth, int& vacuum_x, int& vacuum_y, int maxcap,  int& lives, RenderWindow& window, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, bool& onGround, const float& jumpStrength, const float& speed, const float& friction,  int& counter, const float& terminal_Velocity_x, int top_mid_up, int vacuum_range, int vacuum_width){

	if(FirstRun){





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

	const int invisibleManCount=3;
	const int GhostCount=4;
	const int skeletonCount=9;


	static Sprite invisibleManSp[invisibleManCount];
	static Texture invisibleManTx;
	
	if(FirstRun){
		invisibleManTx.loadFromFile("Data/invisibleMan.png");
	}


	static bool invisibleManJumping[invisibleManCount]={0};
	static float invisibleMan_yVelocity[invisibleManCount]={0};
	static int invisibleMan_y[invisibleManCount];
	static int invisibleMan_x[invisibleManCount];
	static bool invisibleManMovingLeft[invisibleManCount];
	static bool invisibleManIdle[invisibleManCount]={0};


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
	}



	playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height, vacuum_x, vacuum_y);
	check_stuck(lvl, player_x,  player_y, velocityY,  PlayerWidth, PlayerHeight,  cell_size,  width,  height);
	//vacuum_suck(player_x, player_y,  PlayerWidth, PlayerHeight, vacuum_x, vacuum_y, maxcap, vacuum_range,  vacuum_width, captured_enemies_index,  captured_count,  Ghost_x, Ghost_y,  8, GhostBeingPulled);//replcaed num_ghosts with 8 for testing 





	for(int i=0;i<invisibleManCount;i++){
		invisiblaManMove(invisibleMan_x,invisibleMan_y, width, invisibleManSp,invisibleManMovingLeft,i,player_x,player_y,lvl,PlayerSprite, cell_size, PlayerHeight,height, invisibleManIdle);

	}


	for(int i=0;i<invisibleManCount;i++){
		window.draw(invisibleManSp[i]);
	}


}








void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size)
{
	window.draw(bgSprite);

	for (int i=0;i<height;i+=1)
	{
		for (int j=0;j<width;j+=1)
		{

			if (lvl[i][j] == '#')
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

	if (/*bottom_left_down == '#' ||*/ bottom_mid_down == '#' &&velocityY>=0/*|| bottom_right_down == '#'*/) //making falling more precise 
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

	//char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth / 2) / cell_size]; //get the center of the player

	
}

void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool skeletonIdle[],int & lives,const int skeletonCount, int currentSkeleton, bool posChangeHappened[], int FramePosForChange[],bool& FirstRun,bool skeletonJumping[])                                    
{
	//cout<<i<<endl;
	
	static int Frame=192;	
	static int FrameCount=0;
	int grid_x_skeleton=skeleton_x[i]/64;
	int grid_y_skeleton=(skeleton_y[i]+45)/64;
	if((skeleton_y[i]+45)<height)
	 grid_y_skeleton=(skeleton_y[i]+45)/64;


	
	static int currentIdleFrame[3]={0};
	int IdleFramepos[3]={59,111,149};
	



	// if(skeletonJumping[i])
	// {

	// 	if(rand()%2)
	// 	{
	// 		//jumping up

	// 		for(int height=grid_y_skeleton;height>grid_y_skeleton-5&&height>0;height--) //check 5 rows above dont check above index 1
	// 		{
	// 			for(int row=grid_x_skeleton-2;row<grid_x_skeleton+2&&row>0&&row<width-3;row++) //check 5 cols above 2 on each side on above
	// 				{
	// 					if(lvl[height][row]=='#'){
	// 						cout<<height<<endl<<row<<endl;
	// 						skeleton_x[i]=row*cell_size;
	// 						skeleton_y[i]=(cell_size+height)*cell_size;
	// 						break;
	// 					}
					
	// 				}
	// 		}

	// 	}
		
	// 	else{

	// 		//jumping down
	// 		for(int height=grid_y_skeleton;height>grid_y_skeleton-5  && height>0;   height--) //check 5 rows above dont check above index 1
	// 		{
	// 			for(int row=grid_x_skeleton-2;(row<grid_x_skeleton+2) && row>1 && row<width-3 ;row++) //check 5 cols above 2 on each side on above
	// 				{
	// 					if(lvl[height][row]=='#'){
	// 						cout<<height<<endl<<row<<endl;
	// 						skeleton_x[i]=row*cell_size;
	// 						skeleton_y[i]=(cell_size+height)*cell_size;
	// 						break;

	// 					}
					
					
	// 				}
	// 		}

	// 	}

	// 	skeletonJumping[i]=0;
	// }










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
					if((rand()%100)>60 && lvl[grid_y_skeleton+1][grid_x_skeleton+1]!='#' ){ 
						//if the skeleton changes direction because it reached an edge
							skeletonJumping[i]=1;
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

					if((rand()%100)>60 && lvl[grid_y_skeleton+1][grid_x_skeleton]!='#' ){ 
						//if the skeleton changes direction because it reached an edge
							skeletonJumping[i]=1;
						}
				}
				
				else
					if(grid_x_skeleton-1>=0 )
					skeleton_x[i]-=1;
					else	
					skeletonMovingLeft[i]=0;
				
				

	


	skeletonSp[i].setPosition(skeleton_x[i],skeleton_y[i]);


	if(!(player_x<skeleton_x[i]-50||player_x>skeleton_x[i]+50)&&!(player_y<skeleton_y[i]-32||player_y>skeleton_y[i]+32)) //skeleton player collision check
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);
			lives;

		}
	if(!skeletonIdle[i])
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

		

	if(FrameCount%120==0)
		Frame+=33;

	
	if(Frame>300)
		Frame=192;


	FrameCount++;
	return;//end of func


}


void vacuum_suck(float player_x, float player_y, int PlayerWidth, int PlayerHeight, int& vacuum_x, int& vacuum_y, int maxcap, int vacuum_range, int vacuum_width, int captured_enemies_index[], int& captured_count, int Ghost_x[], int Ghost_y[], int num_ghosts, bool GhostBeingPulled[])
{
	
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
	
	float beam_start = 0, beam_top = 0, beam_length = 0, beam_width = 0;
	if (vacuum_x == 1) { //right aim
		beam_start = vacuum_start_x;
		beam_top = vacuum_start_y - ((float)vacuum_width/2); //vertical center
		beam_length = vacuum_range;
		beam_width = vacuum_width;
	} else if (vacuum_x == -1) { //left aim
		beam_start = vacuum_start_x - vacuum_range;
		beam_top = vacuum_start_y - ((float)vacuum_width/2); //vertical center
		beam_length = vacuum_range;
		beam_width = vacuum_width;
	} else if (vacuum_y == -1) { //up aim
		beam_start = vacuum_start_x - ((float)vacuum_width/2); //horizontal center
		beam_top = vacuum_start_y - vacuum_range;
		beam_length = vacuum_width;
		beam_width = vacuum_range;
	} else if (vacuum_y == 1) { //down aim
		beam_start = vacuum_start_x - ((float)vacuum_width/2); //horizontal center
		beam_top = vacuum_start_y ;
		beam_length = vacuum_width;
		beam_width = vacuum_range;
	}
	
	int ghost_size = 64; //to make the gun collision check the whole box sprite rectangle of the ghost
	
	//enemy capture
	if (Keyboard::isKeyPressed(Keyboard::Space) && captured_count < maxcap) { //if holding space and not at capacity
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
}
	
void invisiblaManMove(int invisibleMan_x[],int invisibleMan_y[],int width,Sprite invisibleManSp[],bool invisibleManMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height,bool invisibleManIdle[])
{
	//cout<<i<<endl;
	static int currentinvisibleMan=0;
	static bool posChangeHappened[4]={0};
	static int FramePosForChange[4]={0};
	static int Frame=192;	
	static int FrameCount=0;
	int grid_x_invisibleMan=invisibleMan_x[i]/64;
	int grid_y_invisibleMan=(invisibleMan_y[i]+45)/64;
	if((invisibleMan_y[i]+45)<height)
	 grid_y_invisibleMan=(invisibleMan_y[i]+45)/64;

	
	static int currentIdleFrame[4]={0};
	int IdleFramepos[3]={59,111,149};
	

	if(invisibleManIdle[i]){
	
	
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


	if(!invisibleManIdle[i])
	if(!invisibleManMovingLeft[i]){
		
		
		if(lvl[grid_y_invisibleMan+1][grid_x_invisibleMan+1]!='#'||lvl[grid_y_invisibleMan][grid_x_invisibleMan+1]=='#'){
			invisibleManMovingLeft[i]=1;
		}
		else
			if(grid_x_invisibleMan+1<width-1 ){
				invisibleMan_x[i]+=1;
			
			}else
				invisibleManMovingLeft[i]=1;
		
	
	}
	else
	{
	if(invisibleManMovingLeft[i])

		if(lvl[grid_y_invisibleMan+1][grid_x_invisibleMan]!='#'||lvl[grid_y_invisibleMan][grid_x_invisibleMan]=='#'){ //for some incredible dumb reason x-1 causes it to not hit the left wall
			invisibleManMovingLeft[i]=0;
		}
		else
			if(grid_x_invisibleMan-1>=0 )
			invisibleMan_x[i]-=1;
			else	
			invisibleManMovingLeft[i]=0;
		
		

	}


	invisibleManSp[i].setPosition(invisibleMan_x[i],invisibleMan_y[i]);


	if(!(player_x<invisibleMan_x[i]-50||player_x>invisibleMan_x[i]+50)&&!(player_y<invisibleMan_y[i]-32||player_y>invisibleMan_y[i]+32))
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);

		}
	if(!invisibleManIdle[i])
	invisibleManSp[i].setTextureRect(IntRect(Frame,0,32,110));//staring x, staring y ,widht,height
	
	if(!invisibleManIdle[i])
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
		//ensuer enouh frames have passed for random movement change again


	if(FrameCount-FramePosForChange[i]==1200ull)
	{
		cout<<FrameCount-FramePosForChange[i];
		posChangeHappened[i]=0;
	}






	if(!posChangeHappened[i])
		{
				int check=rand()%100;
	
			if(check<30){ //this entire code block is so dumb it makes me want to quit coding
						// cout<<true;
						// int temp;
						// cin>>temp;

			
					invisibleManMovingLeft[currentinvisibleMan]=!invisibleManMovingLeft[currentinvisibleMan];
					cout<<"change for invisibleMan "<<currentinvisibleMan<<"at frame "<<FrameCount<<endl;
					currentinvisibleMan++;
					posChangeHappened[i]=1;
					FramePosForChange[i]=FrameCount;
					currentinvisibleMan=currentinvisibleMan>3?0:currentinvisibleMan;
					//clamp to zero and 3
			}else if(!invisibleManIdle[i] && (FrameCount+i*150)%600<10)
				{
					currentIdleFrame[i]=0;
					cout<<"\ninvisibleMan "<<i<<" is Idle\n";
					invisibleManIdle[i]=1;
					invisibleManSp[i].setTextureRect(IntRect(IdleFramepos[currentIdleFrame[i]],0,32,110));
					currentIdleFrame[i]=0;
					FramePosForChange[i]=Frame;
					
				}	
	
	}

		

	if(FrameCount%120==0)
		Frame+=33;

	
	if(Frame>300)
		Frame=192;


	FrameCount++;
	return;//end of func


}
