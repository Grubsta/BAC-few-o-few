// ANSI Tower for a Teensy utilising a PewPew board.
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <sprite.h>
#include <macros.h>
#include "bitmaps.h"
// check snake game for sprite trailing hero.

// Configuration (sprite L & W).
#define HW 16 // Hero.
#define HH 8
#define TH 21 // Tower.
#define TW 80
#define DH 11 // Door.
#define DW 24
#define EH 5 // Enemy.
#define EW 8
#define KH 3 // Key.
#define KW 8
#define VWH 44 // Vetical wall.
#define VWW 3
#define HWH 3 // horizontal wall.
#define HWW 44

#define thresh (1000)


// TODO : ###
//  KEY collision + collision still buggy (probs bool value somewher)
// 9. Treasure
// 10. Door & key (key not working)
// 12. Random location generator (apply to all array sprites)
// 13. Scrolling map
// 14. Random map generator
// 15. Character attack/defense mechanisms
// 16. USB Serial Debugging Interface

// NEED TO KNOWS
// SCREEN = 84x48

// Global variables.
// Location / movement.
float speed = 1.0;
double dx = 0;
double dy = 0;
int dxdy[1];
// Player.
int level = 1;
int lives = 3;
int score = 0;
// Timer.
int seconds = 0;
int minutes = 0;
int timeCounter = 0;
// Sprite amounts.
int enemyAm = 1;
int treasureAm = 0;
int wallAm;
// Gameplay / Collisions.
int XYarray[50];
int screenHeight = 48;
int screenWidth = 84;
// int XYarray[NW - 1][2];
bool keyColl = false;
bool activated = false;
bool lvlInit = false;
bool wallInitialised = false;
bool mapInitialised = false;
bool enemyInitialised = false;
uint16_t closedCon = 0;
uint16_t openCon = 0;

int wallX1 = -33, wallX2 = 117;
int wallY1 = -21, wallY2 = 69;


// Initialise sprites.
Sprite hero; Sprite tower; Sprite door; Sprite key;
Sprite enemy[5]; Sprite treasure[5]; Sprite wall[5];

// Initialise hero.
void initHero(void) {
	int x = LCD_X / 2 - HW / 2;
	int y = LCD_Y / 2 + HH + 3;
	sprite_init(&hero, x, y, HW, HH, heroBitmap);
}

// Moves enemy sprite towards hero's location.
void enemyMovement() { // ### Fix to allow enemy array.
	float enemySpeed = 0.1;
	for (int i = 0; i < enemyAm; i++) {
		if (enemy[i].x < hero.x) enemy[i].x += enemySpeed;
		else if (enemy[i].x > hero.x) enemy[i].x -= enemySpeed;
		if (enemy[i].y < hero.y) enemy[i].y += enemySpeed;
		else if (enemy[i].y > hero.y) enemy[i].y -= enemySpeed;
		sprite_draw(&enemy[i]);
	}
}


// Draws layered border around map. ### soooo broken.
void drawBorder(int dx, int dy) {
	wallX1 += dx; wallX2 += dx;
	wallY1 += dy; wallY2 += dy;
	// int y2 = 69 + dy;
	for (int i = 0; i <= 4; i++) {
		draw_line(wallX1 - i, wallY1 - i, wallX2 + i, wallY1 - i, FG_COLOUR);
	}
	for (int i = 0; i <= 4; i++) {
		draw_line(wallX1 - i, wallY1 - i, wallX1 - i, wallY2 + i, FG_COLOUR);
	}
	for (int i = 0; i <= 4; i++) {
		draw_line(wallX1 - i, wallY2 - i, wallX2 + i, wallY2 - i, FG_COLOUR);
	}
	for (int i = 0; i <= 4; i++) {
		draw_line(wallX2 - i, wallY1 - i, wallX2 - i, wallY2 + i, FG_COLOUR);
	}

}

// Colision detection for static map walls.
void staticMap(void) {
  int x = round(hero.x); int y = round(hero.y);
  if (x < 1 || x + HW >= LCD_X ) hero.x -= dx;
  if (y - 2  < 0 || y + HH >= LCD_Y - 1) hero.y -= dy;
}

// Collision detection between 2 sprites.
bool spriteCollision(Sprite sprite1, Sprite sprite2) {
  // Sprite 1.
  int spr1Bottom = round(sprite1.x + sprite1.height);
  int spr1Top = round(sprite1.y);
  int spr1Left = round(sprite1.x);
  int spr1Right = round(sprite1.x + sprite1.width);
  // Sprite 2.
  int spr2Bottom = round(sprite2.y + sprite2.height);
  int spr2Top = round(sprite2.y);
  int spr2Left = round(sprite2.x);
  int spr2Right = round(sprite2.x + sprite2.width);
  // Creates a perimter arround sprites and checks for collision.
	if (spr1Bottom < spr2Top || spr1Top > spr2Bottom || spr1Right < spr2Left|| spr1Left > spr2Right) {
		return false;
	}
	else {
		return true;
	}
}


bool gapCollision(Sprite sprite1, Sprite sprite2, int gap) {
  // Sprite 1.
  int spr1Bottom = round(sprite1.x + sprite1.height + gap);
  int spr1Top = round(sprite1.y - gap);
  int spr1Left = round(sprite1.x - gap);
  int spr1Right = round(sprite1.x + sprite1.width + gap);
  // Sprite 2.
  int spr2Bottom = round(sprite2.y + sprite2.height + gap);
  int spr2Top = round(sprite2.y - gap);
  int spr2Left = round(sprite2.x - gap);
  int spr2Right = round(sprite2.x + sprite2.width + gap);
  // Creates a perimter arround sprites and checks for collision.
	if (spr1Bottom < spr2Top || spr1Top > spr2Bottom || spr1Right < spr2Left|| spr1Left > spr2Right) {
		return false;
	}
	else {
		return true;
	}
}

// Initialises all sprites on first level.
void level1Init(void) {
	// Useful vairables.
	int midX = LCD_X / 2;
	initHero();
	sprite_init(&enemy[0], LCD_X * 0.85, LCD_Y * 0.50, EW, EH, enemyBitmap); // ### relocate enemy to allow for movement
	sprite_init(&key, LCD_X * 0.15 - KW, LCD_Y * 0.50, KW, KH, keyBitmap);
	sprite_init(&tower, 2, 0, TW, TH, towerBitmap);
	sprite_init(&door, midX - DW / 2, TH - DH, DW, DH, doorBitmap);
	lvlInit = true;
}

// Moves all sprites dependent on xy values.
void moveAll(int x, int y) {
	if (level == 1) {
		tower.x += x; tower.y += y;
	}
	else {
		for(int i = 0; i < wallAm; i++) {
			wall[i].x += x; wall[i].y += y;
		}
	}
	for(int i = 0; i < treasureAm; i++) {
		treasure[i].x += x; treasure[i].y += y;
	}
	for(int i = 0; i < enemyAm; i++) {
		enemy[i].x += x; enemy[i].y += y;
	}
	key.x += x; key.y += y;
	door.x += x; door.y += y;
	hero.x += x; hero.y += y;
}

// Scrolling map feature.
void scrollMap(void) {
	int x = 0;
	int y = 0;
	if (hero.x < round(LCD_X * 0.15) && hero.x > wallX1 && hero.x < wallX2) x += 1;
	else if (hero.x + HW > round(LCD_X * 0.85) && hero.x > -33 && hero.x < wallX2) x -= 1;
	if (hero.y < round(LCD_Y * 0.15) && hero.y > wallY1 && hero.y < wallY2) y += 1;
	else if (hero.y + HH > round(LCD_Y * 0.85) && hero.y > wallY1 && hero.y < wallY2) y -= 1;
	moveAll(x, y);
	drawBorder(x, y);
}


// Initialises set amount of walls.
void wallInit(void) {
	wallAm = 6;
	int x, y;
	int drawnWall = 0;
	bool valid = true;
	for (int i = 0; i < wallAm; i++) {
		do {
			x = rand() % 50;
			y = rand() % 50;
			int direction = rand() % 2;
			if (direction == 1) { // Vertical direction.
				sprite_init(&wall[i], x, y, VWW, VWH, vertWallBitmap);
			} else { // horizontal direction.
				sprite_init(&wall[i], x, y, HWW, HWH, horWallBitmap);
			}
			if (drawnWall > 0) {
				for (int a = 0; a < drawnWall; a++) { // 5-1 and make the fifth start at the same x1y1 as another
					if (gapCollision(wall[i], wall[a], 8)) valid = false; // ### NEED to compensate for wall gaps.
					else valid = true;
				}
			}
		} while (!valid);
		sprite_draw(&wall[i]);
		drawnWall =+ 1;
	}
	wallInitialised = true;
}


// Initialises all the sprites on the map.
void mapInit(void) {
	for (int i = 0; i < 50; i++) {
		XYarray[i] = rand() % 40;
	}
	sprite_init(&door, XYarray[8], XYarray[43], DW, DH, doorBitmap);
	sprite_init(&key, XYarray[2], XYarray[33], KW, KH, keyBitmap);
	for(int i = 0; i < treasureAm; i++) {
		int x = rand() % 50, y = rand() % 50;
		sprite_init(&treasure[i], XYarray[x], XYarray[y], TW, TH, treasureBitmap);
	}
	wallInit();
	initHero();
	// enemyInit();
	mapInitialised = true;
}

// Initialises level skeleton and draws it.
void drawLvl(void) {
	// int screenSizeX = 84; // ### Change for scrolling map feature.
	// int screenSizeY = 48;
	// Useful variables.
	int maxY = LCD_Y - 1;
	int maxX = LCD_X - 1;
	// Static level 1 sprites.
  if (level == 1) {
		if (!lvlInit) level1Init();
    draw_line(0, 0, maxX, 0, FG_COLOUR);
    draw_line(0, 0, 0, maxY, FG_COLOUR);
    draw_line(0, maxY, maxX, maxY, FG_COLOUR);
    draw_line(maxX, 0, maxX, maxY, FG_COLOUR);
    sprite_draw(&tower); sprite_draw(&door);
    sprite_draw(&key);
		enemyMovement();
  }
	// Random level sprites.
  else {
		if (!mapInitialised) mapInit();
		for (int i = 0; i < wallAm; i++)sprite_draw(&wall[i]);
		for (int i = 0; i < enemyAm; i++) sprite_draw(&enemy[i]);
		for (int i = 0; i < treasureAm; i++) sprite_draw(&treasure[i]);
		sprite_draw(&door); sprite_draw(&key);


  }
}

// Destroys entire level. ###
void destroyGame(void) {
	if (level == 1) {
		free(&tower);
	}
	else {
		for (int i = 0; i < wallAm; i++) free(&wall[i]);
	}
	for (int i = 0; i < enemyAm; i++) free(&enemy[i]);
	free(&hero); free(&key); free(&door);
	mapInitialised = false; lvlInit = false;
	keyColl = false;
}

// Loading screen between levels.
void loadingScreen(void) {
	clear_screen();
	char lev[50];char scor[50];
	sprintf(lev, "Next level %d", level); draw_string(0, 20, lev, FG_COLOUR);
	sprintf(scor, "Score: %d", score); draw_string(0, 40, scor, FG_COLOUR);
	show_screen();
	_delay_ms(2000);
}

// Display Menu during gameplay.
void displayMenu(void) {
	clear_screen();
	char lev[50]; char liv[50]; char scor[50]; char timer[20];
	sprintf(lev, "Level: %d", level); draw_string(0, 0, lev, FG_COLOUR);
	sprintf(liv, "Lives: %d", lives); draw_string(0, 10, liv, FG_COLOUR);
	sprintf(scor, "Score: %d", score); draw_string(0, 20, scor, FG_COLOUR);
	sprintf(timer, "Time: %02d:%02d", minutes, seconds); draw_string(0, 30, timer, FG_COLOUR);
	show_screen();
}

// User input from PewPew switches.
void userControlls(void) {
	if (BIT_IS_SET(PIND, 1)){ // Up switch.
		dy = -speed;
	}
	else if (BIT_IS_SET(PINB, 7)){ // Down switch.
		dy = speed;
	}
	else if (BIT_IS_SET(PINB, 1)){ // Left switch.
		dx = -speed;
	}
	else if (BIT_IS_SET(PIND, 0)){ // Right switch.
		dx = speed;
	}
	else if (BIT_IS_SET(PINB, 0)){ // Centre switch.
		// Acts as a debouncer whilst user hold switch down.
		closedCon++;
		openCon = 0;
		if (closedCon > thresh) {
			if (!activated) {
				closedCon = 0;
			}
			activated = true;
		}
		else {
			openCon++;
			closedCon = 0;
			if (openCon > thresh) {
				if (activated) {
					openCon = 0;
				}
				activated = false;
			}
			displayMenu();
		}
	}
	dxdy[0] = dx; dxdy[1] = dy;
}

// Hero movement.
void moveHero(void) {
	// Useful variables.
	float xx = dx; float yy = dy;
	dx = 0; dy = 0;
	dxdy[0] = 0; dxdy[1] = 0;
	bool enColl = false;
	// User Input.
	userControlls();
	dx = dxdy[0];
	dy = dxdy[1];
	// Array sprite Collisions.
	for (int i = 0; i < enemyAm; i++) {
		if (spriteCollision(hero, enemy[i])) {
			enColl = true;
		}
	}
	// Checking for collisions.
	if (enColl) {
		lives -= 1;
		enColl = false;
		destroyGame();
	}
	else if (spriteCollision(hero, key)) { // ### HIDE sprites
		keyColl = true;
		key.x = 150;
		key.y = 150;
	}
	else if (spriteCollision(hero, door)) {
		if (keyColl) {
			level += 1;
			score += 100;
			destroyGame();
			loadingScreen();
		}
		else {
			hero.y -= yy;
			hero.x -= xx;
		}
	}
	else if (spriteCollision(hero, tower)) {
		hero.y -= yy;
		hero.x -= xx;
	}
	// If no collisions occur, move hero.
	else {
		hero.y += dy;
		hero.x += dx;
	}
	scrollMap();
	// Wall collision.
  if (level == 1) {
		// staticMap();
	}
}

// Welcome Screen.
void welcomeScreen(void) {
  clear_screen();
  draw_string(LCD_X / 2 - 25, LCD_Y / 2 - 6, "Corey Hull", FG_COLOUR);
  draw_string(LCD_X / 2 - 23, LCD_Y / 2 + 6, "N10007164", FG_COLOUR);
  show_screen();
  _delay_ms(2000);
	char* countDwn[3] = {"3", "2", "1"};
	bool start = false;
	do {
		if (BIT_IS_SET(PINF, 6) || 	BIT_IS_SET(PINF, 5)) start = true;
	} while (!start);
	for (int i = 0; i <= 2; i++) {
		clear_screen();
		draw_string(LCD_X / 2 - (9 / 2), LCD_Y / 2, countDwn[i], FG_COLOUR);
		show_screen();
		_delay_ms(333); // ### CHANGE to 3Hz frequency
	}
}

// Game over menu.
void gameOverScreen(void) {
	clear_screen();
	char lev[50];char scor[50];
	draw_string(0, 0, "You died in ANZI!", FG_COLOUR);
	sprintf(lev, "level: %d", level); draw_string(0, 10, lev, FG_COLOUR);
	sprintf(scor, "final score: %d", score); draw_string(0, 20, scor, FG_COLOUR);
	draw_string(0, 40, "SW2/3 to restart", FG_COLOUR);
	show_screen(); //### Add button press to restart gameplay.
}

// Initialise Timer.
void timer(void) {
	timeCounter++;
	if (timeCounter == 10) {
	seconds++;
	timeCounter = 0;
		if (seconds == 60) {
		seconds = 0;
		minutes++;
			if (minutes == 100) {
			  // game_over = true;
			}
		}
	}
}

// Enables input from PewPew switches.
void initControls(void) {
  // D-pad Controlls.
  CLEAR_BIT(DDRB, 0); // Centre.
  CLEAR_BIT(DDRB, 1); // Left.
  CLEAR_BIT(DDRB, 7); // Down.
  CLEAR_BIT(DDRD, 0); // Right.
  CLEAR_BIT(DDRD, 1); // Up.
	// SW2 & SW3 Controlls.
	CLEAR_BIT(DDRF, 6); // Left.
	CLEAR_BIT(DDRF, 5); // Right.
}

// Setup (ran on start).
void setup(void) {
  set_clock_speed(CPU_8MHz);
  initControls();
  lcd_init(LCD_DEFAULT_CONTRAST);
	timer();
	// welcomeScreen();
  clear_screen();
  drawLvl();
  sprite_draw(&hero);
  show_screen();

}

// Process (ran every frame).
void process(void) {
	if (lives > 0) {
		clear_screen();
		timer();
		drawLvl();
		moveHero();
		sprite_draw(&hero);
		show_screen();
	}
	else {
		gameOverScreen();
	}
}

// Main loop.
int main(void) {
  setup();
  for ( ;; ) {
    process();
    _delay_ms(10);
	}
}
