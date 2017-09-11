#include <string>

using namespace std;

struct hitbox{
	unsigned int left; //left bound of the hitbox//
	unsigned int right; //right bound of the hitbox//
	unsigned int top; //top bound of the hitbox//
	unsigned int bottom; //bottom bound of the hitbox//

	//bounds of the hitbox in the previous frame. used in uGrid efficiency//
	unsigned int pastLeft;
	unsigned int pastRight;
	unsigned int pastTop;
	unsigned int pastBottom;

	//unsigned int width;
	//unsigned int height;
	//unsigned int xpw; //x + width. used in ugrid//
	//unsigned int yph; //y + height. used in ugrid//

	string name; //name of the hitbox//
	int ID;
	string parentName; //name of the hitbox's parent//
	string parentType; //type of the hitbox's parent//
	//vector<int> collidingWithID;

};
