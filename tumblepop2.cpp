#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

int screen_x = 1136;
int screen_y = 896;

void display_level(RenderWindow& window, char**lvl, Texture& bgTex,Sprite& bgSprite,Texture& blockTexture,Sprite& blockSprite, const int height, const int width, const int cell_size)
{
	window.draw(bgSprite);

	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{

			if (lvl[i][j] == '#')
			{
				blockSprite.setPosition(j * cell_size, i * cell_size);
				window.draw(blockSprite);
			}
		}
	}

}

void player_diplay(RenderWindow& Window,int player_x, int player_y, Texture PlayerTexture, Sprite PlayerSprite) 
{	//if()
		//else

{
	PlayerTexture.loadFromFile("Data/player.png");
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setScale(3,3);
	PlayerSprite.setPosition(player_x, player_y);
	Window.draw(PlayerSprite);
}

}

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth)
{
	offset_y = player_y;
	if(player_y< 0 && velocityY <0)
	{
			player_y = Pheight;
	}
	else
	offset_y += velocityY;

	char bottom_left_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x ) / cell_size];
	char bottom_right_down = lvl[(int)(offset_y  + Pheight) / cell_size][(int)(player_x + Pwidth/2) / cell_size];
	char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth) / cell_size];

	if ((bottom_left_down == '#' || bottom_right_down == '#'|| bottom_mid_down == '#')&& velocityY >=0)
	{
		onGround = true;
	}
	else
	{
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

// vaccum display 
void vaccum(RenderWindow& Window,int PlayerHeight,int PlayerWidth,float player_x,float player_y,char** lvl, const int cell_size,bool&vaccum_on, float vaccum_range, float vaccum_radius, int vaccum_direction, int vaccum_strength)
{
		Texture vaccum_wave;
		Sprite vaccumSprite;
		

	if(vaccum_on)
	{
		if(vaccum_direction == 1)//right
		{
			vaccum_wave.loadFromFile("Data/vaccum_r.png"); 
			vaccumSprite.setTexture(vaccum_wave);
			vaccumSprite.setScale(vaccum_range/cell_size,3);
			vaccumSprite.setPosition(player_x + PlayerWidth, player_y +PlayerHeight/4);
			Window.draw(vaccumSprite);
		}
		else if(vaccum_direction == -1)//left
		{
			vaccum_wave.loadFromFile("Data/vaccum_l.png"); 
			vaccumSprite.setTexture(vaccum_wave);
			vaccumSprite.setScale(vaccum_range/cell_size,3);;
			vaccumSprite.setPosition(player_x - vaccum_range  + PlayerWidth +cell_size, player_y + PlayerHeight/4);
			Window.draw(vaccumSprite);
		}
		else if(vaccum_direction == 2)//up
		{
			vaccum_wave.loadFromFile("Data/vaccum_u.png");
			vaccumSprite.setTexture(vaccum_wave);
			vaccumSprite.setScale(3,vaccum_range/cell_size);
			vaccumSprite.setPosition(player_x , player_y - vaccum_range + PlayerHeight + cell_size);
			Window.draw(vaccumSprite);
		}
		else if(vaccum_direction == 0)//down
		{
			vaccum_wave.loadFromFile("Data/vaccum_d.png");
			vaccumSprite.setTexture(vaccum_wave);
			vaccumSprite.setScale(3,vaccum_range/cell_size);
			vaccumSprite.setPosition(player_x , player_y + PlayerHeight );
			Window.draw(vaccumSprite);
		}	
	}
		

}
// vaccum pull (to be added in enemy functions later)
void vaccum_pull(int enemy_x, int enemy_y,int player_x, int player_y, int vaccum_direction, int vaccum_strength,float vaccum_range, float vaccum_radius, int PlayerWidth, int PlayerHeight)
{
	if(vaccum_direction == 1)//right
	{
		if(enemy_y > player_y - vaccum_radius && enemy_y < player_y + vaccum_radius)// in vaccum radius
		{
			if(enemy_x < player_x + vaccum_range && enemy_x > player_x + PlayerWidth)//in vaccum range and at right side
			{
				enemy_x -= vaccum_strength;// move enemy to left (towards player)
			}
		}
	}
	else if(vaccum_direction == -1)//left
	{
		if(enemy_y > player_y - vaccum_radius && enemy_y < player_y + vaccum_radius)// in vaccum radius
		{
			if(enemy_x > player_x - vaccum_range && enemy_x < player_x)// in vaccum range and at left side
			{
				enemy_x += vaccum_strength;
			}
		}
	}
	else if(vaccum_direction == 2)//up
	{
		if(enemy_x > player_x - vaccum_radius && enemy_x < player_x + vaccum_radius)// radius check 
		{
			if(enemy_y > player_y - vaccum_range && enemy_y < player_y)// in range and above player
			{
				enemy_y += vaccum_strength;
			}
		}
	}
	else if(vaccum_direction == 0)//down
	{
		if(enemy_x > player_x - vaccum_radius && enemy_x < player_x + vaccum_radius)
		{
			if(enemy_y < player_y + vaccum_range && enemy_y > player_y + PlayerHeight)
			{
				enemy_y -= vaccum_strength;
			}
		}
	}

}

int main()
{

	RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP", Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//level specifics
	const int cell_size = 64;// size of each block
	const int height = 14;
	const int width = 18;
	char** lvl1;

	//level and background textures and sprites
	Texture bgTex;
	Sprite bgSprite;
	Texture blockTexture;
	Sprite blockSprite;

	bgTex.loadFromFile("Data/bg.png");
	bgSprite.setTexture(bgTex);
	bgSprite.setPosition(0,0);

	blockTexture.loadFromFile("Data/block1.png");
	blockSprite.setTexture(blockTexture);

	//Music initialisation
	Music lvlMusic;

	lvlMusic.openFromFile("Data/mus.ogg");
	lvlMusic.setVolume(20);
	lvlMusic.play();
	lvlMusic.setLoop(true);

	//player data
	float player_x = 10;
	float player_y = height * cell_size - 200;
	
	float speed = 10; // horizontal speed
	int player_action=0; // 0=idle, 1=running right,2=jumping
	int player_direction = 1; //1=right, -1=left
	const float jumpStrength = -22; // Initial jump velocity
	const float gravity = 1;  // Gravity acceleration

	bool isJumping = false;  // Track if jumping

	bool up_collide = false;
	bool left_collide = false;
	bool right_collide = false;

	Texture PlayerTexture;
	Sprite PlayerSprite;

	bool onGround = false;

	float offset_x = 0;
	float offset_y = 0;
	float velocityY = 0;

	float terminal_Velocity = 20;

	int PlayerHeight = 102;
	int PlayerWidth = 96;
	bool up_button = false;

	//vaccum variables
	bool vaccum_on = false;
	float vaccum_range = 10*48;//radius
	float vaccum_radius = cell_size;//width
	int vaccum_strength = 5;
	int vaccum_direction; //1=right, -1=left, 2=top, 0=down
	// initialising player sprite
	


	//creating level array
	lvl1 = new char* [height];
	for (int i = 0; i < height; i += 1)
	{
		lvl1[i] = new char[width];
	}
	//top middle platform
	
	for(int i=5;i<13;i++)
	lvl1[6][i]= '#';
	//middle tiles

	for(int i=5;i<9;i++)
	lvl1[10][i]= '#';
	
	//center block
	//center pillar
	for(int i=7;i<13;i++)
	lvl1[i][8]= '#';

	for(int i=7;i<13;i++)
	lvl1[i][9]= '#';

	// bottom middle 	
	for(int i=2;i<16;i++)
	lvl1[10][i]= '#';

	
	//side platforms
	for(int i=0;i<3;i++)
	lvl1[4][i]= '#';
	
	for(int i=15;i<width;i++)
	lvl1[4][i]= '#';
	//top

	// bottom
	for(int i=0;i<width;i++)
	lvl1[13][i]= '#';

	
		
	Event ev;
	//main loop
	while (window.isOpen())
	{	
		//checking left and right collisions
		char left = lvl1[(int)player_y / cell_size][(int)(player_x -1)/cell_size];
		char right = lvl1[(int)player_y / cell_size][(int)(player_x + PlayerWidth +1) / cell_size];

		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed) 
			{
				window.close();
			}
		}
				if (ev.type == Event::KeyPressed)
				{
					if (ev.key.code == Keyboard::Up && onGround) // jump
					{
						velocityY = jumpStrength; // player jumps
						player_action=2;
					}	
				}
				else if(player_action!=1) 
				{
					player_action=0; // idle
				}
				if ( Keyboard::isKeyPressed(Keyboard::Right)) // right movement
				{	
					if(!(right == '#') && player_x < width*cell_size - PlayerWidth )
					{	player_x += speed; // player right move
						player_action=1; // running 
						player_direction = -1;// (right for sprite)
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) // left movement
				{	if(left != '#' && player_x > 0) 
					player_x -= speed; // player left move
					player_action=1; //running
					player_direction = 1;//left (for sprite)
				}
				else if (player_action!=2) 
				{
					player_action=0; // idle
				}

				//vaccum control
				if (Keyboard::isKeyPressed(Keyboard::D)) //right vaccum
				{	
					vaccum_on = true;
					vaccum_direction = 1;// right
				}
				else if (Keyboard::isKeyPressed(Keyboard::A)) //left vaccum
				{	
					vaccum_on = true;
					vaccum_direction = -1;// left
				}
				else if(Keyboard::isKeyPressed(Keyboard::W)) //up vaccum
				{	
					vaccum_on = true;
					vaccum_direction = 2;// up
				}
				else if(Keyboard::isKeyPressed(Keyboard::S)) //down vaccum
				{	
					vaccum_on = true;
					vaccum_direction = 0;// down
				}
				else
				{
					vaccum_on = false;
				}
        	
		

	

		//presing escape to close
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear();

		display_level(window, lvl1, bgTex, bgSprite, blockTexture, blockSprite, height, width, cell_size);
		player_gravity(lvl1,offset_y,velocityY,onGround,gravity,terminal_Velocity, player_x, player_y, cell_size, PlayerHeight, PlayerWidth);
		
		//displaying player
		PlayerSprite.setPosition(player_x, player_y);

		vaccum(window,PlayerHeight,PlayerWidth,player_x,player_y,lvl1, cell_size,vaccum_on, vaccum_range, vaccum_radius, vaccum_direction, vaccum_strength);

		window.draw(PlayerSprite);
		player_diplay(window,player_x, player_y, PlayerTexture, PlayerSprite);

		window.display();
	}

	//stopping music and deleting level array
	lvlMusic.stop();
	for (int i = 0; i < height; i++)
	{
		delete[] lvl1[i];
	}
	delete[] lvl1;

	return 0;
}


