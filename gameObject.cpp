#include "gameObject.h"




//gameObject is abstract, so this constructor will never be called//
gameObject::gameObject(){



}




//load image from file name, convert to texture, and store in gameObject's image member//
bool gameObject::load_files(SDL_Renderer * gRenderer){



	if (image != NULL)
	{


		SDL_DestroyTexture(image);
		image = NULL;
		width = 0;
		height = 0;

	}


	SDL_Texture * newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(fileName.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError());
			return false;
		}
		else
		{
			/*
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;

			*/
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	image = newTexture;
	if (image == NULL){

		return false;

	}

	return image != NULL;

}


//render gameObject to screen. Precondition: relativeX and relativeY are greater than or equal to 0//
void gameObject::show(unsigned int relativeX, unsigned int relativeY, SDL_Renderer * gRenderer){

	SDL_Rect renderQuad = { x - relativeX, y - relativeY, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	if(changedPosition){
		SDL_RenderCopy(gRenderer, image, clip, &renderQuad);
	}
}

//getter for this object's hitboxes. stored in a vector//
vector<hitbox> gameObject::getHitboxes(){

	return hitboxes;

}

//returns this gameObject's stored image. This will usually come in the form of a sprite sheet//
SDL_Texture * gameObject::getImage(){

	return image;

}

//returns the x coordinate for gameObject//
unsigned int gameObject::getX(){

	return x;

}

//returns the y coordinate for gameObject//
unsigned int gameObject::getY(){

	return y;

}

//returns where x is to be updated to. a difference between x and futureX indicates movement in the x direction//
unsigned int gameObject::getFutureX(){

	return futureX;

}

//returns where y is to be updated to. a difference between y and futureY indicates movement in the y direction//
unsigned int gameObject::getFutureY(){

	return futureY;

}

//returns the gameObject's width. Precondition: width must be greater than or equal to zero//
unsigned int gameObject::getWidth(){

	return width;

}

//returns the gameObject's height. Precondition: height must be greater than or equal to zero
unsigned int gameObject::getHeight(){

	return height;

}

//returns the current clip of the object//
SDL_Rect * gameObject::getClip(){

	return clip;

}
//returns the clip that is to be used in the future//
SDL_Rect * gameObject::getFutureClip(){

	return futureClip;

}
//returns the number of the current clip. this generally points to an array index of the clips. Precondition: greater than or equal to zero. Not out of bounds
unsigned int gameObject::getCurrentClip(){

	return currentClip;

}
//returns the number of the current frame. this is useful in simple looping animations. Precondition: greater than or equal to zero. Not our of bounds//
unsigned int gameObject::getCurrentFrame(){

	return currentFrame;

}

//clears all memory in gameObject//
void gameObject::destruct(){

	//Free loaded image
	SDL_DestroyTexture(image);
	image = NULL;

	hitboxes.clear();
	inputs.clear();

	hitboxes.swap(hitboxes);
	inputs.swap(inputs);


}

void gameObject::addInput(string input){

	inputs.push_back(input);


}

void gameObject::clearInputRecord(){

	inputs.clear();

}

void gameObject::clearStateChangeRecord(){

	stateChanges.clear();

}

void gameObject::clearRectRecord(){

	//framesVec.clear();

}


//moves hitboxes to new position. Precondition: new values do not rollover//
void gameObject::move(int xDifference, int yDifference){


	//move the gameObject's hitboxes//
	int pPos = 0;
	hitbox * p = hitboxes.data();
	int numHitboxes = hitboxes.size();

	for(int i = 0; i < numHitboxes; i++){


		(*p).pastLeft = (*p).left;
		(*p).pastRight = (*p).right;
		(*p).pastTop = (*p).top;
		(*p).pastBottom = (*p).bottom;

		(*p).left += xDifference;

		(*p).right += xDifference;

		(*p).top += yDifference;

		(*p).bottom += yDifference;


		pPos++;
		p++;


	}
	x = futureX;
	y = futureY;

}

//return name of object//
string gameObject::getName(){

	return name;


}
//return fileName of object's image//
string gameObject::getFileName(){

	return fileName;


}
//return type of object//
string gameObject::getType(){

	return type;


}
//add hitbox h to hitbox record//
void gameObject::addHitbox(hitbox h){

	hitboxes.push_back(h);


}

void gameObject::extractClipsFromXML(string xmlFileName){
	/*
	string line;
  ifstream options(xmlFileName);
  int index = framesVec.size();
  char c;
	int tempX = 0;
	int tempY = 0;
	int tempWidth = 0;
	int tempHeight = 0;
  while(options.get(c)){


    if(c == '<'){

      while(c != '>'){

        line += c;
        options.get(c);

      }

    }

    if(line.compare("<X") == 0){


      line.clear();
			options.get(c);

      while(c != '\n'){

				line += c;
				options.get(c);

			}

      tempX = atoi(line.c_str());



    }
    else if(line.compare("<Y") == 0){

      line.clear();
			options.get(c);

      while(c != '\n'){

				line += c;
				options.get(c);

			}

      tempY = atoi(line.c_str());



    }
    else if(line.compare("<Width") == 0){

      line.clear();
			options.get(c);

      while(c != '\n'){

				line += c;
				options.get(c);

			}

      tempWidth = atoi(line.c_str());



    }
    else if(line.compare("<Height") == 0){

      line.clear();
			options.get(c);

      while(c != '\n'){

				line += c;
				options.get(c);

			}

      tempHeight = atoi(line.c_str());

			OrionRect * tempRect = new OrionRect();
			tempRect->X = tempX;
			tempRect->Y = tempY;
			tempRect->W = tempWidth;
			tempRect->H = tempHeight;

			framesVec.push_back(tempRect);
      index++;

    }
    else{


      line.clear();
    }

  }


	*/

}
