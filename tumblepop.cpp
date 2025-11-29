

//todo add skeletons 
//we could maybe move the placement of enemies inside the level fucntions will probably make it easier l8r to do stuff

//todo add skeleton randomness

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
void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height);
void check_stuck(char** lvl, float& player_x, float& player_y, float& velocityY, int PlayerWidth, int PlayerHeight, int cell_size, int width, int height);
void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, const float& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height);// handle all ingame movement and collision
void level_one(char**lvl, int height,int width);
void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size);
void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height);
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





	//defining the skeletons

	Sprite skeletonSp[4];
	Texture skeletonTx;
	skeletonTx.loadFromFile("Data/skeleton.png");
	
	int skeleton_y[4];
	int skeleton_x[4];
	bool skeletonMovingLeft[8];

	for(int i=0;i<4;i++)
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

	for(int i=0;i<4;i++){


		skeleton_y[i]-=45;
		skeletonSp[i].setPosition(skeleton_x[i],skeleton_y[i]);
		skeletonSp[i].setScale(2,2);

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







		for(int i=0;i<8;i++)
		{ //move five ghosts
			ghostMove(Ghost_x,Ghost_y,width,GhostSp,GhostMovingLeft,i,player_x,player_y,lvl,PlayerSprite,cell_size,PlayerHeight,height);
		}

		for(int i=0;i<4;i++){
			skeletonMove( skeleton_x, skeleton_y, width, skeletonSp, skeletonMovingLeft, i, player_x, player_y,lvl,PlayerSprite, cell_size, PlayerHeight, height);
		
		}











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



		for(int i=0;i<8;i++){
			window.draw(GhostSp[i]);
			window.draw(skeletonSp[i]);
		}
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




void ghostMove(int Ghost_x[],int Ghost_y[],int width,Sprite GhostSp[],bool GhostMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height)
{

	static int Frame=5;	
	static int FrameCount=0;
	
	
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

	GhostSp[i].setPosition(Ghost_x[i],Ghost_y[i]);


	if(!(player_x<Ghost_x[i]-50||player_x>Ghost_x[i]+50)&&!(player_y<Ghost_y[i]-32||player_y>Ghost_y[i]+32))
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);

		}

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


void playermovement(float& player_x, float& velocityY, bool& isJumping, float& velocityX, Texture& PlayerTexture, Sprite& PlayerSprite, bool& onGround,const float& jumpStrength, const float& speed, const float& friction, int& counter, const float& terminal_Velocity_x,int top_mid_up,int PlayerWidth,int cell_size,float& player_y,int PlayerHeight,char **lvl,int height)// handle all ingame movement and collision
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

void skeletonMove(int skeleton_x[],int skeleton_y[],int width,Sprite skeletonSp[],bool skeletonMovingLeft[],int i,float& player_x,float& player_y,char **lvl,Sprite &PlayerSprite,int cell_size,int PlayerHeight,int height)
{
	//cout<<i<<endl;
	static int currentSkeleton=0;
	static bool posChangeHappened=0;
	static int FramePosForChange;
	static int Frame=5;	
	static int FrameCount=0;
	int grid_x_skeleton=skeleton_x[i]/64;
	int grid_y_skeleton=(skeleton_y[i]+45)/64;
	if((skeleton_y[i]+45)<height)
	 grid_y_skeleton=(skeleton_y[i]+45)/64;
	
	

	// if(rand()%10==3){
			
	// 		if(grid_y_skeleton+cell_size/2<height-5)
	// 		{
	// 			cout<<"true";
	// 			skeleton_y[i]+=cell_size/2;
	// 			grid_y_skeleton=(skeleton_y[i]+45)/64;
	// 		}	

	// 	}
	



	
	



	if(!skeletonMovingLeft[i]){
		
		
		if(lvl[grid_y_skeleton+1][grid_x_skeleton+1]!='#'||lvl[grid_y_skeleton][grid_x_skeleton+1]=='#'){
			skeletonMovingLeft[i]=1;
		}
		else
			if(grid_x_skeleton+1<width-1 ){
				skeleton_x[i]+=1;
			
			}else
				skeletonMovingLeft[i]=1;
		
	
	}
	else
	{
	if(skeletonMovingLeft[i])

		if(lvl[grid_y_skeleton+1][grid_x_skeleton]!='#'||lvl[grid_y_skeleton][grid_x_skeleton]=='#'){ //for some incredible dumb reason x-1 causes it to not hit the left wall
			skeletonMovingLeft[i]=0;
		}
		else
			if(grid_x_skeleton-1>=0 )
			skeleton_x[i]-=1;
			else	
			skeletonMovingLeft[i]=0;
		
		

	}

	skeletonSp[i].setPosition(skeleton_x[i],skeleton_y[i]);


	if(!(player_x<skeleton_x[i]-50||player_x>skeleton_x[i]+50)&&!(player_y<skeleton_y[i]-32||player_y>skeleton_y[i]+32))
		{
			player_x=cell_size;
			player_y=(height-2)*cell_size-PlayerHeight;
			PlayerSprite.setPosition(player_y,player_x);

		}

	//skeletonSp[i].setTextureRect(IntRect(Frame,0,32,110));//staring x, staring y ,widht,height

	

		//ensuer enouh frames have passed for random movement change again


	if(FrameCount-FramePosForChange==600ull)
	{
		cout<<FrameCount-FramePosForChange;
		posChangeHappened=0;
	}






	if(!posChangeHappened)
	if(rand()%100<3){ //this entire code block is so dumb it makes me want to quit coding
		// cout<<true;
		// int temp;
		// cin>>temp;

		skeletonMovingLeft[currentSkeleton]=!skeletonMovingLeft[currentSkeleton];
		cout<<"change for skeleton "<<currentSkeleton<<"at frame "<<FrameCount<<endl;
		currentSkeleton++;
		posChangeHappened=1;
		FramePosForChange=FrameCount;
		currentSkeleton=currentSkeleton>3?0:currentSkeleton;
		//clamp to zero and 3




		// if((rand()*(1+i))%2==0){
		// 	cout<<"moving left zero for skeleton "<<i<<endl;
		// 	posChangeHappened=1;
		// 	FramePosForChange=FrameCount;
		// 	skeletonMovingLeft[i]=0;

		// }else{
		// 	cout<<"moving left one for skeleton "<<i<<endl;
		// 	skeletonMovingLeft[i]=1;
		// 	posChangeHappened=1;
		// 	FramePosForChange=FrameCount;
		// }
	}


	
	if(Frame>400)
		Frame=8;


	FrameCount++;
	return;//end of func


}