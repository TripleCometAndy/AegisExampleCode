#include <vector>
#include <string>
#include <iostream>
//test//
#ifndef _HITBOX
#define _HITBOX
#include "../../hitbox/hitbox/hitbox.h"
#endif

#ifndef _ORECT
#define _ORECT
#include "../../OrionRect/OrionRect/OrionRect.h"
#endif


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef _INPUTHANDLER
#define _INPUTHANDLER
#include "../../inputhandler/inputHandler/inputHandler.h"
#endif



#ifndef _UGRID
#define _UGRID
#include "../../ugrid/uGrid/uGrid.h"
#endif



using namespace std;

class gameObject{

protected:

	unsigned int x, y;
	unsigned int futureX, futureY;
	string name;
	vector<hitbox> hitboxes;
	vector<string> inputs;
	vector<string> stateChanges;
	//vector<OrionRect> doop;        <= This single line causes all my issues

	string fileName;
	SDL_Texture * image;
	unsigned int width;
	unsigned int height;
	string type;
	SDL_Rect * clip;
	SDL_Rect * futureClip;
	unsigned int currentClip;
	unsigned int currentFrame;
	float angleLeft;
	float angleRight;
	bool changedPosition;



public:

	gameObject();


	//collision functions//
	vector<hitbox> getHitboxes();
	void addHitbox(hitbox, hitbox);
	bool collidingWithName(hitbox *, string, string);
	bool collidingWithType(hitbox *, string, string);
	bool futureCollisions(hitbox *, vector<gameObject *>);
	hitbox * findMyHitboxPointer(string);


	// Rendering Functions //
	bool load_files(SDL_Renderer *);
	void show(unsigned int relativeX, unsigned int relativeY, SDL_Renderer *);


	//getters//
	SDL_Texture * getImage();
	unsigned int getX();
	unsigned int getY();
	unsigned int getFutureX();
	unsigned int getFutureY();
	unsigned int getWidth();
	unsigned int getHeight();
	string getName();
	string getFileName();
	string getType();
	SDL_Rect * getClip();
	SDL_Rect * getFutureClip();
	unsigned int getCurrentClip();
	unsigned int getCurrentFrame();


	//cleanup//
	void clearHitboxRecord();
	void clearInputRecord();
	void clearStateChangeRecord();
	void clearRectRecord();
	void destruct();

	void addInput(string input);

	//internal logic//
	virtual void handleInput(SDL_Event& e, SDL_Joystick* gGameController) = 0;
	virtual void handleInputDebug(char c) = 0;
	virtual void handleStateChanges(vector<gameObject *> *, uGrid *, thread_pool * pool) = 0;
	virtual void enactStateChanges(vector<gameObject *> *, SDL_Renderer *, uGrid *, thread_pool * pool) = 0;
	virtual void printDebugInformation() = 0;

	void changeActiveState(bool);

	void move(int, int);
	void addHitbox(hitbox h);
	void extractClipsFromXML(string xmlFileName);
	void setAngleLeft(float angle){

		angleLeft = angle;

	}

	void setAngleRight(float angle){

		angleRight = angle;

	}
//

};
