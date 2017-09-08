#include <math.h>
#include <stdlib.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <curses.h>

// TODO : ###
// Zombie hitboxes on other levels (bats)
// Add zombies to required max
// Add dy physics to Zombie
// Fix when you jump into right of platform you glitch out of map
// implement character animation when falling off of platform

// Configuration.
#define DELAY (10)
#define HERO_WIDTH (3)
#define HERO_HEIGHT (3)
#define PLATFORM_HEIGHT (1)

// Initialising game variables.
bool game_over = false;
bool update_screen = true;
bool right = false;
bool left = false;
bool air = false;
bool collision = true;
bool topCollision = false;
bool ground = false;
bool roof = false;
bool switcher = true;
bool spriteDrawn = false;
bool treasureColl = false;
bool keyColl = false;
double dx = 0;
double dy = 0;
double Edx = -0.3;
int Edy = 0;
double velocity = 0;
double gravity = 0.04;
int seconds = 0;
int minutes = 0;
int timeCounter = 0;
int levelTime = 0;
int score = 0;
int level = 1;
int lives = 10;
int treasureVar = 1;
int keyVar = 1;
int platformAmount = 1;
int sprite1Bottom;
int sprite1Top;
int sprite1Left;
int sprite1Right;
int sprite2Bottom;
int sprite2Top;
int sprite2Left;
int sprite2Right;


// Declaring interactive sprites/ characters.
char * charGround =
/**/	" o "
/**/	"/|\\"
/**/	"/ \\";

char * charAir =
/**/ "\\o/"
/**/	" | "
/**/	"/ \\";

char * batEnemy1 =
/**/	"\\ /"
/**/	 " | ";

char * batEnemy2 =
/**/	 " | "
/**/	 "/ \\";

char * boulderEnemy =
/**/	"/''\\"
/**/  "\\__/";

char * zombieEnemy =
/**/	"ZZZZ"
/**/	"  Z "
/**/	" Z  "
/**/	"ZZZZ";

char * platformBase =
/**/ "==================================================================================================================================================================================";

char * exitImg =
/**/ "EXIT"
/**/ "|  |"
/**/ "| .|"
/**/ "|  |";

char * treasure1 =
/**/ "'  "
/**/ " $ "
/**/ "  ,";

char * treasure2 =
/**/ "  '"
/**/ " $ "
/**/ ",  ";

char * treasure3 =
/**/ "   "
/**/ "'$'"
/**/ "   ";

char * key1 =
/**/ "  '  "
/**/ " O-+ "
/**/ ",    ";

char * key2 =
/**/ "  '  "
/**/ " O-+ "
/**/ ",    ";

char * key3 =
/**/ "   ' "
/**/ " O-+ "
/**/ ",    ";

char * seperator =
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|"
/**/ "|";

char * gateImg =
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]";

// Declaring sprites.
sprite_id hero; sprite_id enemy; sprite_id platform[10];
sprite_id door; sprite_id treasure;

// Windows main borders.
void drawArena(void) {
  draw_line(0, 2, screen_width(), 2, '-');
  draw_line(screen_width(), 1, screen_width() - 1, screen_height(), '|');
  draw_line(0, 2, 0, screen_height(), '|');
}

// Creates platform sprites in game.
sprite_id initPlatforms(double x1, double y1, double width) {
  sprite_id platformSprite = sprite_create(x1, y1, width, 1, platformBase);
  return platformSprite;
}

// Draw platform/s.
void DrawPlatforms() {
  switch (level) {
    case 1:
      // level 1.
      if (spriteDrawn == false) {
        // Set up the hero at the left of the screen.
        hero = sprite_create(2 + HERO_WIDTH, screen_height()-HERO_HEIGHT-1, HERO_WIDTH, HERO_HEIGHT, charGround);
        // Set up zombie at the right of the screen.
        enemy = sprite_create(screen_width() - 9, screen_height() - 5, 4, 4, zombieEnemy);
        // Resetting value.
        spriteDrawn = true; right = false; left = false;
      }
      platform[0] = initPlatforms(0, screen_height() - 1, screen_width());
      platform[1] = initPlatforms((screen_width() * 0.3), screen_height() - (1 + (HERO_HEIGHT * 3.5)), (screen_width() * 0.3));
      sprite_draw(platform[0]); sprite_draw(platform[1]);
      break;
    case 2:
      // level 2.
      if (spriteDrawn == false) {
        hero = sprite_create(2 + HERO_WIDTH, screen_height()-HERO_HEIGHT-1, HERO_WIDTH, HERO_HEIGHT, charGround);
        enemy = sprite_create(screen_width() - 9, screen_height() - 4, 3, 2, batEnemy1);
        treasure = sprite_create(screen_width() * 0.5, (8 + (HERO_HEIGHT * 7)), 3, 3, treasure1);
        spriteDrawn = true; right = false; left = false; treasureColl = false;
        platform[0] = initPlatforms(0, screen_height() - 1, screen_width());
        platform[1] = initPlatforms((screen_width() * 0.3), screen_height() - (1 + (HERO_HEIGHT * 3.5)), (screen_width() * 0.4));
        platform[2] = initPlatforms((screen_width() * 0.45), screen_height() - (2 + (HERO_HEIGHT * 7)), (screen_width() * 0.1));
      }
      platformAmount = 2;

      sprite_draw(platform[0]); sprite_draw(platform[1]); sprite_draw(platform[2]); break;
    case 3:
      // level 3.
      if (spriteDrawn == false) {
        hero = sprite_create(2 + HERO_WIDTH, screen_height()-HERO_HEIGHT-1, HERO_WIDTH, HERO_HEIGHT, charGround);
        enemy = sprite_create(screen_width() - 9, (screen_height() - (2 + (HERO_HEIGHT * 7) + 3)), 3, 2, batEnemy1);
        treasure = sprite_create(screen_width() * 0.5, (8 + (HERO_HEIGHT * 7)), 3, 3, treasure1);
        spriteDrawn = true; right = false; left = false; treasureColl = false;
      }
      platformAmount = 3;
      platform[0] = initPlatforms(0, screen_height() - 1, screen_width() * 0.25);
      platform[1] = initPlatforms(screen_width() * 0.75, screen_height() - 1, screen_width() * 0.25);
      platform[2] = initPlatforms(screen_width() * 0.25, screen_height() - (2 + (HERO_HEIGHT * 3.5)), (screen_width() * 0.5));
      platform[3] = initPlatforms(screen_width() * 0.40, screen_height() - (2 + (HERO_HEIGHT * 7)), (screen_width() * 0.20));
      sprite_draw(platform[0]); sprite_draw(platform[1]); sprite_draw(platform[2]); sprite_draw(platform[3]); break;
    case 4:
      // Level 4.
      if (spriteDrawn == false) {
        hero = sprite_create(2 + HERO_WIDTH, screen_height()-HERO_HEIGHT-1, HERO_WIDTH, HERO_HEIGHT, charGround);
        enemy = sprite_create(-20, -20, 3, 2, batEnemy1);
        spriteDrawn = true; right = false; left = false; keyColl = false;
      }
      platformAmount = 3;
      platform[0] = initPlatforms(0, screen_height() - 1, screen_width());
      platform[1] = initPlatforms(screen_width() * 0.35, screen_height() - (2 + (HERO_HEIGHT * 3.5)), screen_width());
      platform[2] = initPlatforms(0, screen_height() - (2 + (HERO_HEIGHT * 7)), screen_width() * 0.65);
      platform[3] = initPlatforms(screen_width() * 0.35, screen_height() - (2 + (HERO_HEIGHT * 10.5)), screen_width());
      sprite_draw(platform[0]); sprite_draw(platform[1]); sprite_draw(platform[2]); sprite_draw(platform[3]); break;
    case 5:
    // Level 4.
    if (spriteDrawn == false) {
      hero = sprite_create(2 + HERO_WIDTH, screen_height()-HERO_HEIGHT-1, HERO_WIDTH, HERO_HEIGHT, charGround);
      enemy = sprite_create(screen_width() - 9, (screen_height() - (2 + (HERO_HEIGHT * 7) - 1)), 3, 2, batEnemy1);
      treasure = sprite_create(screen_width() - 9, screen_height() - (8 + (HERO_HEIGHT * 10.5)), 3, 3, treasure1); // key should go here and be copied on level 4
      spriteDrawn = true; right = false; left = false; treasureColl = false; keyColl = false;
    }
    platformAmount = 4;
    platform[0] = initPlatforms(0, screen_height() - 1, screen_width() * 0.70); // ### 0.70 is end of platform.
    platform[1] = initPlatforms(screen_width() * 0.35, screen_height() - (2 + (HERO_HEIGHT * 3.5)), screen_width());
    platform[2] = initPlatforms(0, screen_height() - (2 + (HERO_HEIGHT * 7)), screen_width() * 0.65);
    platform[3] = initPlatforms(screen_width() * 0.35, screen_height() - (2 + (HERO_HEIGHT * 10.5)), screen_width());
    platform[4] = initPlatforms(screen_width() * 0.80, screen_height() - 1, screen_width() * 0.20); // ### 0.80 is start of platform.
    sprite_draw(platform[0]); sprite_draw(platform[1]); sprite_draw(platform[2]); sprite_draw(platform[3]); sprite_draw(platform[4]);
    break;
  }
}

// Destroys all the sprites.
void destroyGame(void) {
  for (int i = 0; i <= platformAmount; i++){
    sprite_destroy(platform[i]);
  }
  // if (level == 3 || 4 || 5) destroy key and treasure
  sprite_destroy(enemy); sprite_destroy(hero); sprite_destroy(door);
  if (level == 2 || level == 3 || level ==  5) sprite_destroy(treasure);
  spriteDrawn = false;
}

// Level treasure entity (if required).
void treasureEnt(void) {
  if (treasureVar == 1) {
        sprite_set_image(treasure, treasure1);
        treasureVar = 2;
  }
  else if (treasureVar == 2) {
        sprite_set_image(treasure, treasure2);
        treasureVar = 3;
  }
  else {
        sprite_set_image(treasure, treasure3);
        treasureVar = 1;
  }
}

// Level key entity (if required).
void keyEnt(void) {
  // if (keyVar == 1) {
  //       sprite_set_image(key, key1);
  //       keyVar = 2;
  // }
  // else if (keyVar == 2) {
  //       sprite_set_image(key, key2);
  //       keyVar = 3;
  // }
  // else {
  //       sprite_set_image(key, key3);
  //       keyVar = 1;
  // }
}

// Wall collision detection.
bool wallCollision(sprite_id sprite){
  int spriteLeft = sprite_x(sprite);
  int spriteRight = sprite_x(sprite) + sprite_width(sprite) - 1;
  // Return true on collision occurance.
  if (spriteRight > screen_width() - 3 || spriteLeft < 1) {
    return true;
  }
	else {
  	return false;
	}
}

// Animation for bat enemy.
void batAnimation(void) {
  // Repeatedly switches values; causes bat image to change.
  if (switcher == false) {
    sprite_set_image(enemy, batEnemy1);
    switcher = true;
  }
  else if (switcher == true) {
    sprite_set_image(enemy, batEnemy2);
    switcher = false;
  }
}

// Function for enemy movement.
void enemyMovement(sprite_id opponent) {
  // Switch for bat animation.
  if (level == 2 || level == 3 ){
    batAnimation();
  }
  if (wallCollision(opponent)) {
    if (sprite_x(opponent) < screen_width() * 0.5) {
      Edx = 0.3;
    }
    else if (sprite_x(opponent) > screen_width() * 0.5) {
      Edx = -0.3;
    }
  }
  if (level == 5) {
    // ### add dy physics here.
  }
}

// X-value collision detection.
bool xCollision(sprite_id sprite1, sprite_id sprite2){
  // Sprite 1.
  sprite1Left = sprite_x(sprite1);
  sprite1Right = sprite_x(sprite1) + sprite_width(sprite1);
  // Sprite 2.
  sprite2Left = sprite_x(sprite2);
  sprite2Right = sprite_x(sprite2) + sprite_width(sprite2);
  // If collision is occuring.
  if (sprite1Left <= sprite2Right + 1 && sprite1Right >= sprite2Left - 1) return true;
  else return false; // Else return no collision.
}

// Y-value collision detection.
bool yCollision(sprite_id sprite1, sprite_id sprite2){
  // Sprite 1.
  sprite1Bottom = round(sprite_y(sprite1)) + HERO_HEIGHT;
  sprite1Top = round(sprite_y(sprite1));
  // Sprite 2.
  sprite2Bottom = round(sprite_y(sprite2));
  sprite2Top = round(sprite_y(sprite2));
  if (air == true && sprite1Bottom == sprite2Top + 1) {
    roof = false; ground = true; return true;
  }
  else if (sprite1Bottom == sprite2Top) {
    roof = false; ground = true; return true;
  }
  // If collision with bottom of platform.
  else if (sprite1Top == sprite2Bottom + 1) {
    roof = true; ground = false; return true;
  }
  else {
    roof = false; ground = false; return false;
  }
}

// All user movement and collision checks.
void moveChar(void){
  // User input.
  int key = get_char();
  // Collision checks between platform/s and hero.
  for (int i = 0; i <= platformAmount; i++){
    if (xCollision(hero, platform[i])){
      if (yCollision(hero, platform[i])){
          if (roof == true){
            sprite_back(hero);
            dy = 0;
            dy += gravity;
            // velocity = 0;
            if (air == true) sprite_set_image(hero, charAir);
          }
          else if (ground == true){
            // if (air == true) { ### Used to be fix.
            //   sprite_back(hero);
            // }
            sprite_set_image(hero, charGround);
            dy = 0;
            air = false;
          }
        }
      }
    }
  // Gravity if character is in air.
  if (ground == false && roof == false) {
    dy += gravity;
  }
  if (ground == false && roof == false && dy < 0) {
    sprite_set_image(hero, charAir);
  }
  if (ground == false && roof == false && dy < 0) {
    sprite_set_image(hero, charAir);
  }
  // Treasure collision.
  if (level == 2 || level == 3 || level == 5) {
    if (!treasureColl){
      if (xCollision(hero, treasure) && yCollision(hero, treasure)){
        score += 50;
        treasureColl = true;
        sprite_hide(treasure);
      }
    }
  }
  // Wall collision.
  if (sprite1Right > screen_width() - 3 || sprite1Left < 1){
    if (air == true) sprite_back(hero);
    dx = 0;
    velocity = 0;
    sprite_back(hero);
  }
  // Level indicator.
  if (key == 'l') {
    level ++;
    destroyGame();
  }
  // If sprite falls through map.
  else if (sprite1Bottom > screen_height() + 3) {
    lives -= 1;
    dx = 0;
    velocity = 0;
    destroyGame();
  }
  // Roof collision.
  else if (sprite_y(hero) <= 3) {
    dy = 0;
    dy += gravity;
    velocity = 0;
    // sprite_back(hero);
  }
  // Enemy collision.
  else if (xCollision(hero, enemy) && yCollision(hero, enemy)){
    lives -= 1;
    dx = 0;
    velocity = 0;
    destroyGame();
  }

  // Door collision.
  else if (xCollision(hero, door) && yCollision(hero, door)){
    level += 1;
    score += 100;
    velocity = 0;
    dx = 0;
    destroyGame();
  }
  // Else, continue with user controls.
  else {
    if (air == false){
      // Checks for left arrow input.
      if (key == KEY_LEFT){
        if (left == true){
          left = true;
          right = false;
          velocity = 1;
        }
        else if (right == true && velocity == 1) velocity = 0.5;
        else if (right == true && velocity == 0.5){
          left = false;
          right = false;
          velocity = 0;
        }
        else {
          left = true;
          right = false;
          velocity = 0.5;
        }
        if (velocity != 0) dx = velocity * -1;
        else dx = 0;
      }
      // Checks for right arrow input.
      else if (key == KEY_RIGHT){
        if (right == true) velocity = 1;
        else if (left == true && velocity == 1) velocity = 0.5;
        else if (left == true && velocity == 0.5){
          left = false;
          right = false;
          velocity = 0;
        }
        else {
          left = false;
          right = true;
          velocity = 0.5;
        }
        if (velocity != 0 ) dx = velocity;
        else dx = 0;

      }
      // Checks for up arrow input.
      else if (key == KEY_UP){
          air = true;
          dy = -1;
          sprite_set_image(hero, charAir);

      }
    }
  }
}

// Creates Exit door.
void createExit(void){
  door = sprite_create(screen_width() - 8, screen_height() - 5, 4, 4, exitImg);
  sprite_draw(door);
 }

// Ends game when player reaches end or runs out of lives.
void endGame(void) {
  show_screen();
  clear_screen();
  if (lives <= 0) {
    draw_formatted(screen_width() * 0.3, screen_height() * 0.5, "You have ran out of lives... Game Over!");
    draw_formatted(screen_width() * 0.3, (screen_height() * 0.5) + 1, "press any key to exit");
  }
  if (level >= 6) {
    draw_formatted(screen_width() * 0.3, screen_height() * 0.5, "You successfully completed the game!?!");
    draw_formatted(screen_width() * 0.3, (screen_height() * 0.5) + 1, "Congraulations! Your final score is %d", score);
    draw_formatted(screen_width() * 0.3, (screen_height() * 0.5) + 2, "     press any key to exit");
  }
  show_screen();
  game_over = true;
  wait_char();
}

// Draws components of game.
void drawGame(void) {
  // Creates Arena elements.
	drawArena();
  DrawPlatforms();
  createExit();
  // Draws previously initialised sprites.
	sprite_draw(hero);
  sprite_draw(enemy);
}

// Initialise game hud.
void gameHud(void) {
  int width = screen_width() / 4;
  draw_formatted(2, 1, "Time: %02d:%02d", minutes, seconds);
  draw_formatted(width, 1, "Lives: %d", lives);
  draw_formatted(width * 2, 1, "Level: %d", level);
  draw_formatted(width * 3, 1, "Score: %d", score);
}

// Initialise Timer.
void timer(void) {
  timeCounter++;
	if (timeCounter == 100) {
		seconds++;
		levelTime++;
		timeCounter = 0;
		if (seconds == 60) {
			seconds = 0;
			minutes++;
      if (minutes == 100) {
        game_over = true;
      }
		}
	}
}

// Play one turn of game.
void process(void) {
  if (lives > 0 && level <= 5) {
    // Clear current Frame & then redraw.
    clear_screen();
    // Create game.
    drawGame();
    // Draw treasure.
    if (level == 2 || level == 3 || level == 5) {
      treasureEnt();
      sprite_draw(treasure);
    }
    // Enemy movement.
    enemyMovement(enemy);
    sprite_turn_to(enemy, Edx, round(Edy));
    sprite_step(enemy);
    // Character movement.
    moveChar();
    sprite_turn_to(hero, dx, round(dy));
    sprite_step(hero);

  }
  else {
    endGame();
  }
}

// Initial setup.
void setup(void) {
  // Set up the hero at the left of the screen.
  hero = sprite_create(2 + HERO_WIDTH, screen_height()-HERO_HEIGHT-1, HERO_WIDTH, HERO_HEIGHT, charGround);
  // Set up zombie at the right of the screen.
  enemy = sprite_create(screen_width() - 9, screen_height() - 5, 4, 4, zombieEnemy);
  // Draw the game.
  drawGame();
}

// Main loop.
int main(void) {
  // Draw game environment.
  setup_screen();
	setup();

	while ( !game_over ) {
    // Continue drawing frames.
    process();
    timer();
    gameHud();

		if ( update_screen ) {
			show_screen();

		}

		timer_pause(DELAY);
	}

	return 0;
}
