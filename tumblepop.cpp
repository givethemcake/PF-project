

//todo add skeletons 
//we could maybe move the placement of enemies inside the level fucntions will probably make it easier l8r to do stuff



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








void skeletonMove();
void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,int player_x,int player_y);
void check_stuck(char** lvl, float& player_x, float& player_y, float& velocityY, int PlayerWidth, int PlayerHeight, int cell_size, int width, int height);
void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, const float& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height);// handle all ingame movement and collision
void level_one(char**lvl, int height,int width);
void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size);


void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth);

int main()
{


	//set up random number seed
	srand(time(0));





	//Ghost Prototype

	Sprite GhostSp[8];
	Texture GhostTx;
	GhostTx.loadFromFile("Data/Ghost.png");
	
	int Ghost_y[8];
	int Ghost_x[8];
	bool GhostMovingLeft[8];

	for(int i=0;i<8;i++)
	{

		Ghost_x[i]=150;
		Ghost_y[i]=(i+1)*64;
		GhostSp[i].setTexture(GhostTx);
		GhostSp[i].setTextureRect(IntRect(5,5,32,32));	
		int temp=rand();
		if(temp%2==0)
			GhostMovingLeft[i]=0;
		else
			GhostMovingLeft[i]=1;


		//setting the ghost
		GhostSp[i].setPosition(Ghost_x[i],Ghost_y[i]);
		GhostSp[i].setScale(2,2);
	}


	





	
	















	bool facingLeft=true; //cuz start with left sprite


	RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP", Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//level specifics
	int level=1;
	const int cell_size =64;
	const int height = 15;
	const int width = 18;
	char** lvl;

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

	const float jumpStrength = 20; // Initial jump velocity
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
	player_y=(height - 2) * cell_size - PlayerHeight;
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

	if(level==1)
		level_one(lvl,height,width);

	Event ev;
	//main loop


	int counter=1;
	//PlayerSprite.setTextureRect(IntRect(counter*frarmeWidth,0,frarmeWidth,frameHeight));
	
	while (window.isOpen())
	{
		counter++;
		while (window.pollEvent(ev))
		{
				
			
			if (ev.type == Event::Closed) 
			{
				window.close();
			}
			

			if (ev.type == Event::KeyPressed )
			{
			
				
			}

		}







		for(int i=0;i<8;i++) //move five ghosts
			ghostMove(Ghost_x,Ghost_y,width,GhostSp,GhostMovingLeft,i,player_x,player_y);












		//movement( player_x,velocityY, isJumping, velocityX,PlayerTexture,PlayerSprite, onGround, jumpStrength, speed, friction, counter, terminal_Velocity_x);
			
		playermovement( player_x, velocityY,  isJumping,  velocityX, PlayerTexture,  PlayerSprite,  onGround,jumpStrength, speed, friction,  counter,  terminal_Velocity_x, top_mid_up, PlayerWidth, cell_size, player_y, PlayerHeight,lvl, height);

		check_stuck(lvl, player_x,  player_y, velocityY,  PlayerWidth, PlayerHeight,  cell_size,  width,  height);



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



		for(int i=0;i<8;i++)
		window.draw(GhostSp[i]);

		window.display();
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




void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,int player_x,int player_y)
{

	static int Frame=5;	
	static int FrameCount=0;
	
	
	int grid_x_Ghost=Ghost_x[i]/64;




	if(!GhostMovingLeft[i])
		if(grid_x_Ghost+1<width-2 ){
			Ghost_x[i]+=1;
			
		}else
			GhostMovingLeft[i]=1;
		

	else

	if(GhostMovingLeft[i])
		if(grid_x_Ghost-1>0 )
			Ghost_x[i]-=1;
		else	
		GhostMovingLeft[i]=0;

	GhostSp[i].setPosition(Ghost_x[i],Ghost_y[i]);


	if(!(player_x<Ghost_x[i]-50||player_x>Ghost_x[i]+50)&&!(player_y<Ghost_y[i]-32||player_y>Ghost_y[i]+32))
		exit(0);

	GhostSp[i].setTextureRect(IntRect(Frame,0,32,64));//staring x, staring y ,widht,height



	if(FrameCount%120==0)
		Frame+=52;



	
	if(Frame>400)
		Frame=5;


	FrameCount++;
	return;//end of func


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
			player_y-=1;
		}else 
			if(lvl[top_y][mid_x]=='#'){

					player_y+=1;


			}else
			{
				isStuck=false;
				break;
			}
			

			return;


	}





}


void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, const float& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height)// handle all ingame movement and collision
{



	int grid_y=static_cast<int>(player_y+PlayerHeight/2)/cell_size;  
    				  

			top_mid_up=lvl[static_cast<int>(player_y-cell_size)/cell_size][static_cast<int>(player_x+PlayerWidth/2)/cell_size];
			
			
			if((Keyboard::isKeyPressed(Keyboard::W))&&onGround==true){// sometimes gets stuck in the ceilling doesenst always apply downward push
				
					velocityY-=jumpStrength;
					isJumping=true;

				}else
					isJumping=false;


				if(Keyboard::isKeyPressed(Keyboard::A)){
				int grid_x = static_cast<int>(player_x+5) / cell_size;
    
					if(lvl[grid_y][grid_x]=='#')
						velocityX=0;
					else{
					PlayerTexture.loadFromFile("Data/player_left.png");
					PlayerSprite.setTexture(PlayerTexture);
						velocityX-=speed;
					}
					
				}
				if(Keyboard::isKeyPressed(Keyboard::D)){
				
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
							player_y+=cell_size/2;
						}
					
				}
				
				
				
				
				
				

				//clamp velocity
				if(velocityX>terminal_Velocity_x)
					velocityX=terminal_Velocity_x;
				else if(velocityX<-terminal_Velocity_x)
					velocityX=-terminal_Velocity_x;
				 if(!Keyboard::isKeyPressed(Keyboard::D)&&!Keyboard::isKeyPressed(Keyboard::A))
					velocityX*=friction;


				player_x+=velocityX;





				counter=counter>8?1:counter;
				

				//if(velocityX<0){
				//	PlayerSprite.setTextureRect(IntRect(counter*frarmeWidth,10,frarmeWidth,frameHeight));
				//}

				return;

}


void level_one(char**lvl, int height,int width)
{

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