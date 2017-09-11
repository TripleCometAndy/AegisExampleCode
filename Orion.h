#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <thread>
#include <atomic>
//////
////
//#include <wtypes.h>
////////////////////////////////////
#include <cmath>
#include <ctime>
#include <X11/Xlib.h>

#ifndef _UGRID
#define _UGRID
#include "lib/ugrid/uGrid/uGrid.h"
#endif

#include "lib/sdlhandlers/sdlHandlers/sdlHandlers.h"
#include "lib/timer/timer/Timer.h"

#ifndef _INPUTHANDLER
#define _INPUTHANDLER
#include "lib/inputhandler/inputHandler/inputHandler.h"
#endif

#ifndef _GAMEOBJECT
#define _GAMEOBJECT
#include "lib/gameobject/gameObject/gameObject.h"
#endif
//
#include "lib/loadallfiles/loadAllFiles/loadAllFiles.h"
#include "lib/cleanloop/cleanLoop/cleanLoop.h"
#include "lib/handleallstatechanges/handleAllStateChanges/handleAllStateChanges.h"
#include "lib/handleevents/handleEvents/handleEvents.h"
#include "lib/enactallstatechanges/enactAllStateChanges/enactAllStateChanges.h"
#include "lib/renderall/renderAll/renderAll.h"
//////
#ifndef _THREADPOOL
#define _THREADPOOL
#include "lib/threadpool/threadPool/threadPool.h"
#endif

#ifndef _ORECT
#define _ORECT
#include "lib/OrionRect/OrionRect/OrionRect.h"
#endif

//////////////////
#define PLAYER_HITBOX 1
#define TOP_WALL 2
#define RIGHT_WALL 3
#define LEFT_WALL 4
#define BOTTOM_WALL 5

///////
#define PI 3.14159265


//////////

using namespace std;

#define PIXELS_TO_METERS 1/10
#define METERS_TO_PIXELS 10



//
class background : public gameObject{

private:

	SDL_Rect frames[1];
	int renderTimer;


public:


	background(int, int, int, int, string, string, string, SDL_Renderer *, uGrid * uniformGrid);

	void handleInput(SDL_Event& e, SDL_Joystick* gGameController);
	void handleInputDebug(char c);
	void handleStateChanges(vector<gameObject *> *, uGrid *, thread_pool * pool);

	void enactStateChanges(vector <gameObject *> *, SDL_Renderer * renderer, uGrid *, thread_pool * pool);
	void printDebugInformation();

};

class wall : public gameObject{

private:

	SDL_Rect frames[1];


public:

//
	wall(int, int, int, int, string, string, string, SDL_Renderer *, uGrid * uniformGrid);

	void handleInput(SDL_Event& e, SDL_Joystick* gGameController);
	void handleStateChanges(vector<gameObject *> *, uGrid *);
	void enactStateChanges(vector <gameObject *> *, SDL_Renderer * renderer, uGrid *);

};

class player : public gameObject{

private:

	double xVel;
	double yVel;
	double velocity;

	//stateHandlers//
	bool attacking;
	int attackOne;
	int futureAttackOne;
	int attackTwo;
	int futureAttackTwo;
	int attackThree;
	int futureAttackThree;

	//left = true//
	//right = false//
	bool direction;
	bool futureDirection;

	bool jumping;
	bool futureJumping;
	int jumpTimer;

	int stateTimer;
	int attackTimer;

	float radiusLeft;
	float radiusRight;
	float angleShield;
	float angleAttack;

	bool striking;
	bool futureStriking;

	bool walking;
	bool futureWalking;
	bool shielding;
	bool futureShielding;

	int moveShieldPastVertical;
	int moveShieldFutureVertical;
	int moveShieldPastHorizontal;
	int moveShieldFutureHorizontal;

	int moveAttackPastVertical;
	int moveAttackFutureVertical;
	int moveAttackPastHorizontal;
	int moveAttackFutureHorizontal;

	int attackClip;

	bool rJoystick;
	bool lBumper;

	double attackPercent;
	double xMove;

	int attackID;

	double deltaX;
	double deltaY;

	double timeFactor;

	bool xPress;
	
	SDL_Texture * shieldSheet;
	SDL_Texture * swordSheet;
	SDL_Texture * attackSheet;
	SDL_Texture * bashSheet1;
	SDL_Texture * bashSheet2;
	SDL_Texture * bashSheet3;

	SDL_Texture * airShieldSheet;

	bool shieldBashing;
	bool futureBashing;
	int bashNum;
	int bashTimer;

	bool downShielding;
	bool futureDownShielding;

	int leftTriggerHandler;
	int rightTriggerHandler;

	bool airAttack;
	bool futureAirAttack;
	int airAttackTimer;
	int futureAirAttackTimer;

	bool attackInfoFlipper;


	SDL_Rect frames[237];


//

public:


	player(int, int, int, int, string, string, string, SDL_Renderer *, uGrid * uniformGrid, double);

	void handleInput(SDL_Event& e, SDL_Joystick* gGameController);
	void handleInputDebug(char c);
	void handleStateChanges(vector<gameObject *> *, uGrid *, thread_pool * pool);
	void enactStateChanges(vector<gameObject *> *, SDL_Renderer * renderer, uGrid *, thread_pool * pool);
	void getAttackOneInfo();
	void getAttackTwoInfo();
	void getAttackThreeInfo();
	void processInputs();
	void handleShield();
	void handleJump();
	void groundAttackOneLeft();
	void groundAttackTwoLeft();
	void groundAttackThreeLeft();
	void groundAttackOneRight();
	void groundAttackTwoRight();
	void groundAttackThreeRight();
	void handleShieldAir();
	void airAttackLeft();
	void airAttackRight();
	void printDebugInformation();



};

////
class Camera{

private:

	int x, y;
	int width, height;
	vector<hitbox> hitboxes;
	hitbox screen;

public:

	Camera(int, int, int, int);
	hitbox getScreen();

};

class frameTimeInfo{

private:

	//used with frame independent movement//
	int currentTime;
	int pastTime;
	int deltaTime;
	int tempTime;

public:

	frameTimeInfo();
	void update(Timer * t);
	int getDeltaTime();


};

void renderAll(vector<gameObject *> gameObjects, SDL_Renderer * renderer);
int loop(int FPS, int screenWidth, int screenHeight, bool fullScreen);
int loopWrite(int FPS, int screenWidth, int screenHeight, bool fullScreen);
int loopDebug(int FPS, int screenWidth, int screenHeight, bool fullScreen);
int loopDebugSingleStep(int FPS, int screenWidth, int screenHeight, bool fullScreen);
int loopDebug_SDLDecoupled(int FPS, int screenWidth, int screenHeight, bool fullScreen);
void getJoystickInfo(float * radius, float * angle, int xDir, int yDir);
