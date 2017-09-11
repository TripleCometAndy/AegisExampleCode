#include "Orion.h"

player::player(int xCoor, int yCoor, int gWidth, int gHeight, string n, string file, string t, SDL_Renderer * renderer, uGrid * uniformGrid, double TIME){

	x = xCoor;
	y = yCoor;
	width = gWidth;
	height = gHeight;

	rJoystick = false;
	lBumper = false;

  stateTimer = 0;
  attackTimer = 0;

	deltaX = 0;
	deltaY = 0;

  futureX = x;
	futureY = y;
	currentClip = 0;

	attackID = 0;

	timeFactor = TIME;

	jumping = false;
	futureJumping = false;
	jumpTimer = 0;

	xPress = false;

  image = NULL;
	shieldSheet = NULL;
	swordSheet = NULL;

	walking = false;
	futureWalking = false;

	shielding = false;
	futureShielding = false;

	radiusLeft = 0;
	angleLeft = 0;
	radiusRight = 90;
	angleRight = 90;
	angleShield = 90;

	attackPercent = 0.75;

	moveShieldPastVertical = 0;
	moveShieldFutureVertical = 0;
	moveShieldPastHorizontal = 0;
	moveShieldFutureHorizontal = 0;

	moveAttackPastVertical = 0;
	moveAttackFutureVertical = 0;
	moveAttackPastHorizontal = 0;
	moveAttackFutureHorizontal = 0;

	attackClip = 0;
	name = n;
	fileName = file;
	type = t;

	striking = false;
	futureStriking = false;

	direction = true;
	futureDirection = true;



	hitboxes.push_back(hitbox());
	hitboxes[0].left = x;
	hitboxes[0].right = x + width;
	hitboxes[0].top = y;
	hitboxes[0].bottom = y + height;
	hitboxes[0].name = "player_hitbox1";
	hitboxes[0].parentName = name;
	hitboxes[0].parentType = type;
	hitboxes[0].pastLeft = x;
	hitboxes[0].pastRight = x + width;
	hitboxes[0].pastTop = y;
	hitboxes[0].pastBottom = y + height;
	hitboxes[0].ID = PLAYER_HITBOX;

	//doop.push_back(OrionRect());
	//doop[0].X = 0;
	//doop[0].Y = 0;
	//doop[0].W = 0;
	//doop[0].H = 0;

	attackOne = -1;
	futureAttackOne = -1;
	attackTwo = -1;
	futureAttackTwo = -1;
	attackThree = -1;
	futureAttackThree = -1;

	airAttackTimer = -1;
	futureAirAttackTimer = -1;
	airAttack = false;
	futureAirAttack = false;

	attackClip = 0;

	shieldBashing = false;
	futureBashing = false;
	bashNum = 0;
	bashTimer = 0;

	downShielding = false;
	futureDownShielding = false;

	leftTriggerHandler = 0;
	rightTriggerHandler = 0;

	attackInfoFlipper = false;

	if (shieldSheet != NULL)
	{


		SDL_DestroyTexture(shieldSheet);
		shieldSheet = NULL;
		width = 0;
		height = 0;

	}


	SDL_Texture * newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load("images/spriteSheetShieldSmaller.png");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShield.png", IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShield.png", SDL_GetError());
			exit(1);
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

	shieldSheet = newTexture;

	if(swordSheet != NULL){

		SDL_DestroyTexture(swordSheet);
		swordSheet = NULL;
		width = 0;
		height = 0;


	}
	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetPlayer.png");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetPlayer.png", IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetPlayer.png", SDL_GetError());
			exit(1);
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

	swordSheet = newTexture;


	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetAttackWithValues.png");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShieldBash3.png", IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShieldBash3.png", SDL_GetError());
			exit(1);
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

	attackSheet = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldBash3.png");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetAttack.png", IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetAttack.png", SDL_GetError());
			exit(1);
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

	bashSheet1 = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldBash1.png");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetBash1.png", IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetBash1.png", SDL_GetError());
			exit(1);
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

	bashSheet2 = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldBash2.png");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShieldBash2.png", IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShieldBash2.png", SDL_GetError());
			exit(1);
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

	bashSheet3 = newTexture;

	newTexture = NULL;
	loadedSurface = IMG_Load("images/spriteSheetShieldDown.png");

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", "images/spriteSheetShieldDown.png", IMG_GetError());

	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", "images/spriteSheetShieldDown.png", SDL_GetError());
			exit(1);
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

	airShieldSheet = newTexture;


frames[0].x = 25;
frames[0].y = 29;
frames[0].w = 77;
frames[0].h = 258;

frames[1].x = 145;
frames[1].y = 30;
frames[1].w = 77;
frames[1].h = 259;

frames[2].x = 252;
frames[2].y = 32;
frames[2].w = 82;
frames[2].h = 257;

frames[3].x = 357;
frames[3].y = 29;
frames[3].w = 89;
frames[3].h = 257;

frames[4].x = 472;
frames[4].y = 29;
frames[4].w = 90;
frames[4].h = 257;

frames[5].x = 21;
frames[5].y = 306;
frames[5].w = 90;
frames[5].h = 256;

frames[6].x = 138;
frames[6].y = 308;
frames[6].w = 91;
frames[6].h = 254;

frames[7].x = 254;
frames[7].y = 312;
frames[7].w = 103;
frames[7].h = 254;

frames[8].x = 375;
frames[8].y = 313;
frames[8].w = 110;
frames[8].h = 253;

frames[9].x = 500;
frames[9].y = 318;
frames[9].w = 115;
frames[9].h = 252;

frames[10].x = 5;
frames[10].y = 578;
frames[10].w = 129;
frames[10].h = 249;

frames[11].x = 156;
frames[11].y = 592;
frames[11].w = 192;
frames[11].h = 248;

frames[12].x = 387;
frames[12].y = 600;
frames[12].w = 155;
frames[12].h = 244;

frames[13].x = 25;
frames[13].y = 870;
frames[13].w = 140;
frames[13].h = 246;

frames[14].x = 184;
frames[14].y = 881;
frames[14].w = 139;
frames[14].h = 241;

frames[15].x = 347;
frames[15].y = 888;
frames[15].w = 263;
frames[15].h = 240;

frames[16].x = 10;
frames[16].y = 1131;
frames[16].w = 213;
frames[16].h = 241;

frames[17].x = 251;
frames[17].y = 1133;
frames[17].w = 135;
frames[17].h = 248;

frames[18].x = 412;
frames[18].y = 1138;
frames[18].w = 127;
frames[18].h = 250;

frames[19].x = 24;
frames[19].y = 1419;
frames[19].w = 130;
frames[19].h = 247;

frames[20].x = 178;
frames[20].y = 1428;
frames[20].w = 154;
frames[20].h = 242;

frames[21].x = 347;
frames[21].y = 1450;
frames[21].w = 275;
frames[21].h = 239;

frames[22].x = 12;
frames[22].y = 1719;
frames[22].w = 240;
frames[22].h = 236;

frames[23].x = 260;
frames[23].y = 1720;
frames[23].w = 176;
frames[23].h = 243;

frames[24].x = 473;
frames[24].y = 1731;
frames[24].w = 148;
frames[24].h = 243;

frames[25].x = 62;
frames[25].y = 1985;
frames[25].w = 143;
frames[25].h = 246;

frames[26].x = 241;
frames[26].y = 1994;
frames[26].w = 121;
frames[26].h = 250;

frames[27].x = 412;
frames[27].y = 1996;
frames[27].w = 94;
frames[27].h = 253;

frames[28].x = 77;
frames[28].y = 2269;
frames[28].w = 90;
frames[28].h = 257;

frames[29].x = 193;
frames[29].y = 2269;
frames[29].w = 89;
frames[29].h = 257;

frames[30].x = 305;
frames[30].y = 2272;
frames[30].w = 82;
frames[30].h = 257;

frames[31].x = 417;
frames[31].y = 2270;
frames[31].w = 77;
frames[31].h = 259;

frames[32].x = 537;
frames[32].y = 2269;
frames[32].w = 77;
frames[32].h = 258;

frames[33].x = 24;
frames[33].y = 2558;
frames[33].w = 115;
frames[33].h = 252;

frames[34].x = 154;
frames[34].y = 2553;
frames[34].w = 110;
frames[34].h = 253;

frames[35].x = 282;
frames[35].y = 2552;
frames[35].w = 103;
frames[35].h = 254;

frames[36].x = 410;
frames[36].y = 2548;
frames[36].w = 91;
frames[36].h = 254;

frames[37].x = 528;
frames[37].y = 2546;
frames[37].w = 90;
frames[37].h = 256;

frames[38].x = 97;
frames[38].y = 2840;
frames[38].w = 155;
frames[38].h = 244;

frames[39].x = 291;
frames[39].y = 2832;
frames[39].w = 192;
frames[39].h = 248;

frames[40].x = 505;
frames[40].y = 2818;
frames[40].w = 129;
frames[40].h = 249;

frames[41].x = 29;
frames[41].y = 3128;
frames[41].w = 263;
frames[41].h = 240;

frames[42].x = 316;
frames[42].y = 3121;
frames[42].w = 139;
frames[42].h = 241;

frames[43].x = 474;
frames[43].y = 3110;
frames[43].w = 140;
frames[43].h = 246;

frames[44].x = 100;
frames[44].y = 3378;
frames[44].w = 127;
frames[44].h = 250;

frames[45].x = 253;
frames[45].y = 3373;
frames[45].w = 135;
frames[45].h = 248;

frames[46].x = 416;
frames[46].y = 3371;
frames[46].w = 213;
frames[46].h = 241;

frames[47].x = 17;
frames[47].y = 3690;
frames[47].w = 275;
frames[47].h = 239;

frames[48].x = 307;
frames[48].y = 3668;
frames[48].w = 154;
frames[48].h = 242;

frames[49].x = 485;
frames[49].y = 3659;
frames[49].w = 130;
frames[49].h = 247;

frames[50].x = 18;
frames[50].y = 3971;
frames[50].w = 148;
frames[50].h = 243;

frames[51].x = 203;
frames[51].y = 3960;
frames[51].w = 176;
frames[51].h = 243;

frames[52].x = 387;
frames[52].y = 3959;
frames[52].w = 240;
frames[52].h = 236;

frames[53].x = 133;
frames[53].y = 4236;
frames[53].w = 94;
frames[53].h = 253;

frames[54].x = 277;
frames[54].y = 4234;
frames[54].w = 121;
frames[54].h = 250;

frames[55].x = 434;
frames[55].y = 4225;
frames[55].w = 143;
frames[55].h = 246;

///////////////////////////////

frames[56].x = 32;
frames[56].y = 26;
frames[56].w = 183;
frames[56].h = 245;

frames[57].x = 235;
frames[57].y = 26;
frames[57].w = 183;
frames[57].h = 252;

frames[58].x = 432;
frames[58].y = 24;
frames[58].w = 184;
frames[58].h = 257;

frames[59].x = 23;
frames[59].y = 307;
frames[59].w = 186;
frames[59].h = 265;

frames[60].x = 225;
frames[60].y = 309;
frames[60].w = 187;
frames[60].h = 268;

frames[61].x = 434;
frames[61].y = 315;
frames[61].w = 191;
frames[61].h = 273;

frames[62].x = 14;
frames[62].y = 600;
frames[62].w = 189;
frames[62].h = 278;

frames[63].x = 219;
frames[63].y = 602;
frames[63].w = 188;
frames[63].h = 284;

frames[64].x = 427;
frames[64].y = 607;
frames[64].w = 185;
frames[64].h = 282;

frames[65].x = 19;
frames[65].y = 906;
frames[65].w = 185;
frames[65].h = 282;

frames[66].x = 221;
frames[66].y = 907;
frames[66].w = 184;
frames[66].h = 285;

frames[67].x = 423;
frames[67].y = 913;
frames[67].w = 182;
frames[67].h = 286;

frames[68].x = 14;
frames[68].y = 1214;
frames[68].w = 179;
frames[68].h = 287;

frames[69].x = 206;
frames[69].y = 1216;
frames[69].w = 177;
frames[69].h = 287;

frames[70].x = 413;
frames[70].y = 1227;
frames[70].w = 175;
frames[70].h = 282;

frames[71].x = 18;
frames[71].y = 1529;
frames[71].w = 174;
frames[71].h = 285;

frames[72].x = 213;
frames[72].y = 1533;
frames[72].w = 171;
frames[72].h = 284;

frames[73].x = 412;
frames[73].y = 1533;
frames[73].w = 168;
frames[73].h = 283;

frames[74].x = 37;
frames[74].y = 1836;
frames[74].w = 163;
frames[74].h = 283;

frames[75].x = 218;
frames[75].y = 1835;
frames[75].w = 158;
frames[75].h = 284;

frames[76].x = 406;
frames[76].y = 1839;
frames[76].w = 150;
frames[76].h = 285;

frames[77].x = 14;
frames[77].y = 2145;
frames[77].w = 184;
frames[77].h = 257;

frames[78].x = 212;
frames[78].y = 2147;
frames[78].w = 183;
frames[78].h = 252;

frames[79].x = 415;
frames[79].y = 2147;
frames[79].w = 183;
frames[79].h = 245;

frames[80].x = 5;
frames[80].y = 2436;
frames[80].w = 191;
frames[80].h = 273;

frames[81].x = 218;
frames[81].y = 2430;
frames[81].w = 187;
frames[81].h = 268;

frames[82].x = 421;
frames[82].y = 2428;
frames[82].w = 186;
frames[82].h = 265;

frames[83].x = 18;
frames[83].y = 2728;
frames[83].w = 185;
frames[83].h = 282;

frames[84].x = 223;
frames[84].y = 2723;
frames[84].w = 188;
frames[84].h = 284;

frames[85].x = 427;
frames[85].y = 2721;
frames[85].w = 189;
frames[85].h = 278;

frames[86].x = 25;
frames[86].y = 3034;
frames[86].w = 182;
frames[86].h = 286;

frames[87].x = 225;
frames[87].y = 3028;
frames[87].w = 184;
frames[87].h = 285;

frames[88].x = 426;
frames[88].y = 3027;
frames[88].w = 185;
frames[88].h = 282;

frames[89].x = 42;
frames[89].y = 3348;
frames[89].w = 175;
frames[89].h = 282;

frames[90].x = 247;
frames[90].y = 3337;
frames[90].w = 177;
frames[90].h = 287;

frames[91].x = 437;
frames[91].y = 3335;
frames[91].w = 179;
frames[91].h = 287;

frames[92].x = 50;
frames[92].y = 3654;
frames[92].w = 168;
frames[92].h = 283;

frames[93].x = 246;
frames[93].y = 3653;
frames[93].w = 171;
frames[93].h = 285;

frames[94].x = 438;
frames[94].y = 3650;
frames[94].w = 174;
frames[94].h = 285;

frames[95].x = 74;
frames[95].y = 3960;
frames[95].w = 150;
frames[95].h = 285;

frames[96].x = 254;
frames[96].y = 3956;
frames[96].w = 158;
frames[96].h = 284;

frames[97].x = 430;
frames[97].y = 3957;
frames[97].w = 163;
frames[97].h = 283;


///////////////////////////////////////////

frames[98].x = 20; //
frames[98].y = 673;
frames[98].w = 162;
frames[98].h = 247;

frames[99].x = 20;//
frames[99].y = 358;
frames[99].w = 154;
frames[99].h = 247;

frames[100].x = 23;
frames[100].y = 1649;
frames[100].w = 188;
frames[100].h = 247;

frames[101].x = 26;
frames[101].y = 26;
frames[101].w = 149;
frames[101].h = 247;

frames[102].x = 27;
frames[102].y = 1006;
frames[102].w = 162;
frames[102].h = 247;

frames[103].x = 31;
frames[103].y = 1326;
frames[103].w = 167;
frames[103].h = 247;

frames[104].x = 272;
frames[104].y = 32;
frames[104].w = 221;
frames[104].h = 239;

frames[105].x = 284;
frames[105].y = 1002;
frames[105].w = 243;
frames[105].h = 239;

frames[106].x = 286;
frames[106].y = 352;
frames[106].w = 230;
frames[106].h = 239;

frames[107].x = 292;
frames[107].y = 671;
frames[107].w = 244;
frames[107].h = 239;

frames[108].x = 299;
frames[108].y = 1323;
frames[108].w = 246;
frames[108].h = 239;

frames[109].x = 319;
frames[109].y = 1645;
frames[109].w = 261;
frames[109].h = 239;

frames[110].x = 594;
frames[110].y = 22;
frames[110].w = 234;
frames[110].h = 234;

frames[111].x = 623;
frames[111].y = 340;
frames[111].w = 244;
frames[111].h = 234;

frames[112].x = 628;
frames[112].y = 1009;
frames[112].w = 258;
frames[112].h = 234;

frames[113].x = 640;
frames[113].y = 662;
frames[113].w = 251;
frames[113].h = 234;

frames[114].x = 651;
frames[114].y = 1308;
frames[114].w = 264;
frames[114].h = 234;

frames[115].x = 675;
frames[115].y = 1638;
frames[115].w = 277;
frames[115].h = 234;

frames[116].x = 943;
frames[116].y = 23;
frames[116].w = 153;
frames[116].h = 247;

frames[117].x = 978;
frames[117].y = 1000;
frames[117].w = 173;
frames[117].h = 247;

frames[118].x = 982;
frames[118].y = 346;
frames[118].w = 160;
frames[118].h = 247;

frames[119].x = 995;
frames[119].y = 658;
frames[119].w = 169;
frames[119].h = 247;

frames[120].x = 1015;
frames[120].y = 1314;
frames[120].w = 171;
frames[120].h = 247;

frames[121].x = 1016;
frames[121].y = 1637;
frames[121].w = 188;
frames[121].h = 247;

frames[122].x = 1201;
frames[122].y = 40;
frames[122].w = 226;
frames[122].h = 239;

frames[123].x = 1234;
frames[123].y = 1016;
frames[123].w = 244;
frames[123].h = 239;

frames[124].x = 1242;
frames[124].y = 676;
frames[124].w = 238;
frames[124].h = 239;

frames[125].x = 1244;
frames[125].y = 363;
frames[125].w = 235;
frames[125].h = 239;

frames[126].x = 1278;
frames[126].y = 1332;
frames[126].w = 243;
frames[126].h = 239;

frames[127].x = 1291;
frames[127].y = 1641;
frames[127].w = 261;
frames[127].h = 239;

frames[128].x = 1526;
frames[128].y = 43;
frames[128].w = 234;
frames[128].h = 234;

frames[129].x = 1561;
frames[129].y = 1038;
frames[129].w = 254;
frames[129].h = 234;

frames[130].x = 1577;
frames[130].y = 369;
frames[130].w = 244;
frames[130].h = 234;

frames[131].x = 1584;
frames[131].y = 681;
frames[131].w = 257;
frames[131].h = 234;

frames[132].x = 1590;
frames[132].y = 1350;
frames[132].w = 259;
frames[132].h = 234;

frames[133].x = 1646;
frames[133].y = 1665;
frames[133].w = 276;
frames[133].h = 234;

frames[134].x = 1992;
frames[134].y = 76;
frames[134].w = 140;
frames[134].h = 276;

frames[135].x = 2006;
frames[135].y = 439;
frames[135].w = 135;
frames[135].h = 283;

frames[136].x = 2010;
frames[136].y = 1182;
frames[136].w = 135;
frames[136].h = 291;

frames[137].x = 2012;
frames[137].y = 815;
frames[137].w = 135;
frames[137].h = 288;

frames[138].x = 2018;
frames[138].y = 1564;
frames[138].w = 135;
frames[138].h = 294;

frames[139].x = 2227;
frames[139].y = 45;
frames[139].w = 208;
frames[139].h = 310;

frames[140].x = 2246;
frames[140].y = 423;
frames[140].w = 195;
frames[140].h = 319;

frames[141].x = 2255;
frames[141].y = 1569;
frames[141].w = 153;
frames[141].h = 341;

frames[142].x = 2265;
frames[142].y = 800;
frames[142].w = 181;
frames[142].h = 328;

frames[143].x = 2274;
frames[143].y = 1177;
frames[143].w = 167;
frames[143].h = 336;

frames[144].x = 2499;
frames[144].y = 1565;
frames[144].w = 165;
frames[144].h = 338;

frames[145].x = 2537;
frames[145].y = 44;
frames[145].w = 226;
frames[145].h = 307;

frames[146].x = 2549;
frames[146].y = 798;
frames[146].w = 196;
frames[146].h = 326;

frames[147].x = 2551;
frames[147].y = 414;
frames[147].w = 209;
frames[147].h = 318;

frames[148].x = 2553;
frames[148].y = 1173;
frames[148].w = 181;
frames[148].h = 335;

frames[149].x = 2717;
frames[149].y = 1600;
frames[149].w = 135;
frames[149].h = 294;

frames[150].x = 2807;
frames[150].y = 1207;
frames[150].w = 135;
frames[150].h = 292;

frames[151].x = 2823;
frames[151].y = 58;
frames[151].w = 144;
frames[151].h = 276;

frames[152].x = 2825;
frames[152].y = 839;
frames[152].w = 135;
frames[152].h = 286;

frames[153].x = 2826;
frames[153].y = 440;
frames[153].w = 135;
frames[153].h = 281;

frames[154].x = 2903;
frames[154].y = 1538;
frames[154].w = 152;
frames[154].h = 339;

frames[155].x = 3014;
frames[155].y = 1156;
frames[155].w = 168;
frames[155].h = 333;

frames[156].x = 3032;
frames[156].y = 794;
frames[156].w = 181;
frames[156].h = 323;

frames[157].x = 3046;
frames[157].y = 398;
frames[157].w = 195;
frames[157].h = 318;

frames[158].x = 3050;
frames[158].y = 31;
frames[158].w = 208;
frames[158].h = 309;

frames[159].x = 3191;
frames[159].y = 1537;
frames[159].w = 167;
frames[159].h = 338;

frames[160].x = 3260;
frames[160].y = 1155;
frames[160].w = 181;
frames[160].h = 333;

frames[161].x = 3297;
frames[161].y = 769;
frames[161].w = 197;
frames[161].h = 325;

frames[162].x = 3320;
frames[162].y = 41;
frames[162].w = 220;
frames[162].h = 309;

frames[163].x = 3322;
frames[163].y = 401;
frames[163].w = 210;
frames[163].h = 318;

frames[164].x = 31;
frames[164].y = 1959;
frames[164].w = 185;
frames[164].h = 247;

frames[165].x = 36;
frames[165].y = 2264;
frames[165].w = 180;
frames[165].h = 247;

frames[166].x = 42;
frames[166].y = 2588;
frames[166].w = 174;
frames[166].h = 247;

frames[167].x = 51;
frames[167].y = 2907;
frames[167].w = 168;
frames[167].h = 247;

frames[168].x = 315;
frames[168].y = 2264;
frames[168].w = 261;
frames[168].h = 239;

frames[169].x = 318;
frames[169].y = 2591;
frames[169].w = 255;
frames[169].h = 243;

frames[170].x = 337;
frames[170].y = 2895;
frames[170].w = 250;
frames[170].h = 258;

frames[171].x = 337;
frames[171].y = 1957;
frames[171].w = 262;
frames[171].h = 239;

frames[172].x = 652;
frames[172].y = 2251;
frames[172].w = 277;
frames[172].h = 234;

frames[173].x = 665;
frames[173].y = 2901;
frames[173].w = 269;
frames[173].h = 254;

frames[174].x = 681;
frames[174].y = 2580;
frames[174].w = 273;
frames[174].h = 237;

frames[175].x = 690;
frames[175].y = 1949;
frames[175].w = 279;
frames[175].h = 234;

frames[176].x = 1008;
frames[176].y = 2903;
frames[176].w = 179;
frames[176].h = 247;

frames[177].x = 1016;
frames[177].y = 2253;
frames[177].w = 186;
frames[177].h = 247;

frames[178].x = 1028;
frames[178].y = 2574;
frames[178].w = 181;
frames[178].h = 247;

frames[179].x = 1033;
frames[179].y = 1945;
frames[179].w = 187;
frames[179].h = 247;

frames[180].x = 1281;
frames[180].y = 2881;
frames[180].w = 248;
frames[180].h = 258;

frames[181].x = 1287;
frames[181].y = 2263;
frames[181].w = 261;
frames[181].h = 239;

frames[182].x = 1293;
frames[182].y = 2576;
frames[182].w = 256;
frames[182].h = 243;

frames[183].x = 1308;
frames[183].y = 1955;
frames[183].w = 263;
frames[183].h = 239;

frames[184].x = 1600;
frames[184].y = 2872;
frames[184].w = 266;
frames[184].h = 255;

frames[185].x = 1626;
frames[185].y = 2266;
frames[185].w = 277;
frames[185].h = 234;

frames[186].x = 1632;
frames[186].y = 2557;
frames[186].w = 274;
frames[186].h = 241;

frames[187].x = 1641;
frames[187].y = 1967;
frames[187].w = 275;
frames[187].h = 234;

frames[188].x = 1987;
frames[188].y = 2795;
frames[188].w = 135;
frames[188].h = 304;

frames[189].x = 1998;
frames[189].y = 1981;
frames[189].w = 135;
frames[189].h = 295;

frames[190].x = 2009;
frames[190].y = 2365;
frames[190].w = 135;
frames[190].h = 299;

frames[191].x = 2212;
frames[191].y = 1964;
frames[191].w = 150;
frames[191].h = 344;

frames[192].x = 2214;
frames[192].y = 2784;
frames[192].w = 150;
frames[192].h = 347;

frames[193].x = 2221;
frames[193].y = 2373;
frames[193].w = 150;
frames[193].h = 346;

frames[194].x = 2448;
frames[194].y = 2781;
frames[194].w = 162;
frames[194].h = 347;

frames[195].x = 2455;
frames[195].y = 2379;
frames[195].w = 162;
frames[195].h = 345;

frames[196].x = 2462;
frames[196].y = 1978;
frames[196].w = 162;
frames[196].h = 342;

frames[197].x = 2672;
frames[197].y = 2412;
frames[197].w = 135;
frames[197].h = 302;

frames[198].x = 2675;
frames[198].y = 2012;
frames[198].w = 135;
frames[198].h = 299;

frames[199].x = 2685;
frames[199].y = 2818;
frames[199].w = 135;
frames[199].h = 302;

frames[200].x = 2865;
frames[200].y = 2357;
frames[200].w = 150;
frames[200].h = 344;

frames[201].x = 2876;
frames[201].y = 1963;
frames[201].w = 150;
frames[201].h = 343;

frames[202].x = 2877;
frames[202].y = 2765;
frames[202].w = 150;
frames[202].h = 347;

frames[203].x = 3078;
frames[203].y = 2349;
frames[203].w = 162;
frames[203].h = 342;

frames[204].x = 3082;
frames[204].y = 2761;
frames[204].w = 162;
frames[204].h = 345;

frames[205].x = 3098;
frames[205].y = 1951;
frames[205].w = 162;
frames[205].h = 342;

frames[206].x = 58;
frames[206].y = 3218;
frames[206].w = 159;
frames[206].h = 252;

frames[207].x = 324;
frames[207].y = 3206;
frames[207].w = 241;
frames[207].h = 273;

frames[208].x = 675;
frames[208].y = 3214;
frames[208].w = 258;
frames[208].h = 269;

frames[209].x = 997;
frames[209].y = 3233;
frames[209].w = 168;
frames[209].h = 248;

frames[210].x = 1243;
frames[210].y = 3196;
frames[210].w = 241;
frames[210].h = 270;

frames[211].x = 1554;
frames[211].y = 3196;
frames[211].w = 256;
frames[211].h = 271;

frames[212].x = 66;
frames[212].y = 3551;
frames[212].w = 154;
frames[212].h = 261;

frames[213].x = 348;
frames[213].y = 3552;
frames[213].w = 228;
frames[213].h = 288;

frames[214].x = 656;
frames[214].y = 3545;
frames[214].w = 248;
frames[214].h = 282;

frames[215].x = 981;
frames[215].y = 3565;
frames[215].w = 159;
frames[215].h = 260;

frames[216].x = 1221;
frames[216].y = 3524;
frames[216].w = 230;
frames[216].h = 286;

frames[217].x = 1503;
frames[217].y = 3514;
frames[217].w = 244;
frames[217].h = 285;

frames[218].x = 85;
frames[218].y = 3866;
frames[218].w = 147;
frames[218].h = 269;

frames[219].x = 374;
frames[219].y = 3882;
frames[219].w = 217;
frames[219].h = 298;

frames[220].x = 697;
frames[220].y = 3885;
frames[220].w = 234;
frames[220].h = 296;

frames[221].x = 1014;
frames[221].y = 3910;
frames[221].w = 152;
frames[221].h = 268;

frames[222].x = 1224;
frames[222].y = 3880;
frames[222].w = 218;
frames[222].h = 298;

frames[223].x = 1508;
frames[223].y = 3860;
frames[223].w = 229;
frames[223].h = 299;

//////////////////////////////////

frames[224].x = 26;
frames[224].y = 44;
frames[224].w = 120;
frames[224].h = 262;

frames[225].x = 230;
frames[225].y = 40;
frames[225].w = 128;
frames[225].h = 266;

frames[226].x = 422;
frames[226].y = 44;
frames[226].w = 135;
frames[226].h = 261;

frames[227].x = 35;
frames[227].y = 387;
frames[227].w = 140;
frames[227].h = 266;

frames[228].x = 234;
frames[228].y = 412;
frames[228].w = 142;
frames[228].h = 265;

frames[229].x = 417;
frames[229].y = 423;
frames[229].w = 146;
frames[229].h = 266;

frames[230].x = 52;
frames[230].y = 736;
frames[230].w = 146;
frames[230].h = 267;

frames[231].x = 48;
frames[231].y = 1100;
frames[231].w = 135;
frames[231].h = 261;

frames[232].x = 247;
frames[232].y = 1096;
frames[232].w = 128;
frames[232].h = 266;

frames[233].x = 459;
frames[233].y = 1100;
frames[233].w = 120;
frames[233].h = 262;

frames[234].x = 42;
frames[234].y = 1479;
frames[234].w = 146;
frames[234].h = 266;

frames[235].x = 229;
frames[235].y = 1468;
frames[235].w = 142;
frames[235].h = 265;

frames[236].x = 430;
frames[236].y = 1443;
frames[236].w = 140;
frames[236].h = 266;

	extractClipsFromXML("spriteMapDouble.xml");
	//cout << framesVec.size() << endl;
	clip = &frames[currentClip];
	hitbox c = hitboxes[0];
	uniformGrid->addReferenceNoIgnore(c);
	//uniformGrid->update(hitboxes);



}

void player::handleInput(SDL_Event &e, SDL_Joystick* gGameController){

	if(e.type == SDL_JOYBUTTONDOWN){



		if(e.jbutton.button == 5){

			addInput("RIGHT_BUMPER_PRESS");

		}
		if(e.jbutton.button == 0){

			addInput("A_BUTTON_PRESS");

		}
		if(e.jbutton.button == 4){


			addInput("LEFT_BUMPER_PRESS");

		}
		if(e.jbutton.button == 10){


			addInput("RIGHT_STICK_CLICK");


		}
	}
	if(e.type == SDL_JOYBUTTONUP){

		if(e.jbutton.button == 4){

			addInput("LEFT_BUMPER_RELEASE");

		}


	}
	if(e.type == SDL_JOYAXISMOTION){

		int xDirLeft = 3;
		int yDirLeft = 3;
		int xDirRight = 3;
		int yDirRight = 3;

		xDirLeft = SDL_JoystickGetAxis(gGameController, 0);
		yDirLeft = SDL_JoystickGetAxis(gGameController, 1);

		int leftTrigger = SDL_JoystickGetAxis(gGameController, 2);
		int rightTrigger = SDL_JoystickGetAxis(gGameController, 5);


		xDirRight = SDL_JoystickGetAxis(gGameController, 3);
		yDirRight = SDL_JoystickGetAxis(gGameController, 4);


		getJoystickInfo(&radiusLeft, &angleLeft, xDirLeft, yDirLeft);
		getJoystickInfo(&radiusRight, &angleRight, xDirRight, yDirRight);


		if(radiusLeft > 5000 && ((angleLeft >= 0 && angleLeft <= 90) || (angleLeft >= 270 && angleLeft <= 360))){

			addInput("JOYSTICK_LEFT");

		}
		else if(radiusLeft > 5000){

			addInput("JOYSTICK_RIGHT");

		}
		else if(radiusLeft < 5000){

			addInput("JOYSTICK_RELEASE");


		}

		if(radiusRight > 5000){

			addInput("JOYSTICK2_HELD");

		}
		else if(radiusRight < 5000){

			addInput("JOYSTICK2_RELEASE");


		}

		if(leftTrigger >= 32667){

			addInput("LEFT_TRIGGER_PRESS");


		}
		if(rightTrigger >= 32667){

			addInput("RIGHT_TRIGGER_PRESS");

		}
		if(leftTrigger <= 5000){

			addInput("LEFT_TRIGGER_RELEASE");


		}
		if(rightTrigger <= 5000){

			addInput("RIGHT_TRIGGER_RELEASE");


		}

	}


}

void player::handleInputDebug(char c){



	if(c == 'B'){

		addInput("RIGHT_BUMPER_PRESS");

	}
	if(c == 'A'){


		addInput("A_BUTTON_PRESS");

	}
	if(c == 'O'){

		addInput("LEFT_BUMPER_PRESS");

	}
	if(c == 'S'){

		addInput("RIGHT_STICK_CLICK");

	}
	if(c == 'o'){

		addInput("LEFT_BUMPER_RELEASE");
	}
	if(c == 'C'){

		addInput("JOYSTICK_LEFT");

	}
	if(c == 'F'){

		addInput("JOYSTICK_RIGHT");

	}
	if(c == 'G'){

		addInput("JOYSTICK_RELEASE");

	}
	if(c == 'H'){

		addInput("JOYSTICK2_HELD");

	}
	if(c == 'h'){

		addInput("JOYSTICK2_RELEASE");
	}
	if(c == 'I'){

		addInput("LEFT_TRIGGER_PRESS");

	}
	if(c == 'J'){

		addInput("RIGHT_TRIGGER_PRESS");
	}
	if(c == 'i'){

		addInput("LEFT_TRIGGER_RELEASE");
	}
	if(c == 'j'){

		addInput("RIGHT_TRIGGER_RELEASE");
	}

}

void player::handleStateChanges(vector<gameObject *> * objects, uGrid * uniformGrid, thread_pool * pool){

	xMove = 0;

	processInputs();



	if(attackOne == -1 && attackTwo == -1 && attackThree == -1 && (rightTriggerHandler == 1) && jumping == false){

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackOneInfo();
		futureAttackOne = 0;
		futureShielding = false;

	}
	else if(attackOne >= 20 && attackOne < 50 && attackTwo == -1 && attackThree == -1 && (rightTriggerHandler == 3) && jumping == false){

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackTwoInfo();
		futureAttackTwo = 0;
		futureShielding = false;

	}
	else if(attackTwo >= 0 && attackTwo < 20 && attackThree == -1 && (rightTriggerHandler == 5) && jumping == false){

		futureWalking = false;
		futureShielding = false;
		angleAttack = angleRight;
		getAttackThreeInfo();
		futureAttackThree = 0;
		futureShielding = false;

	}
	else if(jumping && rightTriggerHandler == 1){

		getAttackTwoInfo();
		futureAirAttack = true;
		futureAirAttackTimer = 0;


	}

	if(rJoystick && lBumper){

		futureShielding = true;

	}
	else{

		futureShielding = false;

	}

	if(jumping){

		handleJump();

	}
	if(shielding){

		if(jumping && futureJumping){

			handleShieldAir();

		}
		else if(futureBashing || shieldBashing){

				handleShield();

				switch(bashTimer){
					case 0:
					bashNum = 1;
					break;
					case 4:
					bashNum = 2;
					break;
					case 5:
					bashNum = 3;
					break;
					case 10:
					bashNum = 2;
					break;
					case 11:
					bashNum = 1;
					break;
					case 15:
					bashNum = 0;
					futureBashing = false;
					break;
				}
				bashTimer++;

		}
		else{

			handleShield();

		}




	}
	if(direction == true){
		if(walking){
			if(shielding){
				xMove = -8*(1/timeFactor)/(METERS_TO_PIXELS);
			}
			else{

				xMove = -13*(1/timeFactor)/(METERS_TO_PIXELS);

			}
		}
		else if(attackOne != -1){

			groundAttackOneLeft();

		}
		else if(attackTwo != -1){

			groundAttackTwoLeft();

		}
		else if(attackThree != -1){

			groundAttackThreeLeft();

		}
		else if(airAttackTimer != -1){

			airAttackLeft();


		}

	}
	else{

		if(walking){

			if(shielding){
				xMove = 8*(1/timeFactor)/(METERS_TO_PIXELS);
			}
			else{

				xMove = 13*(1/timeFactor)/(METERS_TO_PIXELS);

			}

		}
		else if(attackOne != -1){

			groundAttackOneRight();

		}
		else if(attackTwo != -1){

			groundAttackTwoRight();

		}
		else if(attackThree != -1){

			groundAttackThreeRight();
		}
		else if(airAttackTimer != -1){

			airAttackRight();
		}
	}

	int xMoveInt = 0;
	xMove = xMove * timeFactor;
	xMove = xMove * METERS_TO_PIXELS;
	xMove = xMove * attackPercent;
	xMove = xMove * 0.5;
	xMove = xMove + deltaX;
	xMoveInt = (int)floor(xMove);
	deltaX = xMove - xMoveInt;

	futureX += xMoveInt;

	hitbox future;
	future.top = futureY;
	future.bottom = futureY + height;
	future.left = futureX;
	future.right = futureX + width;
	future.name = "future";
	future.parentName = name;


	if (uniformGrid->findName(future, LEFT_WALL, pool) || uniformGrid->findName(future, RIGHT_WALL, pool)){

		futureX = x;

	}

}

void player::enactStateChanges(vector<gameObject *> * objects, SDL_Renderer * renderer, uGrid * uniformGrid, thread_pool * pool){

	attackOne = futureAttackOne;
	attackTwo = futureAttackTwo;
	attackThree = futureAttackThree;

	walking = futureWalking;
	futureWalking = walking;

	if(shielding && !futureShielding){

		image = swordSheet;
		currentClip = 0;
		clip = &frames[currentClip];

	}

	airAttackTimer = futureAirAttackTimer;
	futureAirAttackTimer = airAttackTimer;

	airAttack = futureAirAttack;
	futureAirAttack = airAttack;

	shielding = futureShielding;
	futureShielding = shielding;

	shieldBashing = futureBashing;
	futureBashing = shieldBashing;



	downShielding = futureDownShielding;
	futureDownShielding = downShielding;

	jumping = futureJumping;
	futureJumping = jumping;



	striking = futureStriking;
	futureStriking = striking;

	if(shielding){


		if(shieldBashing){

			switch(bashNum){
				case 1:
				image = bashSheet1;
				break;
				case 2:
				image = bashSheet2;
				break;
				case 3:
				image = bashSheet3;
				break;
			}

		}
		else if(downShielding){

			image = airShieldSheet;


		}
		else{

			image = shieldSheet;
			bashTimer = 0;
			downShielding = false;
			futureDownShielding = false;



		}


		angleShield = angleRight;
		futureY -= moveShieldPastVertical;
		futureY += moveShieldFutureVertical;
		futureX -= moveShieldPastHorizontal;
		futureX += moveShieldFutureHorizontal;
		moveShieldPastVertical = moveShieldFutureVertical;
		moveShieldPastHorizontal = moveShieldFutureHorizontal;

	}

	if(attackOne == -1 && attackTwo == -1 && attackThree == -1 && airAttackTimer == -1){



	}
	else{

		angleAttack = angleRight;

		if(striking){
			if(attackID == 1){

				if(attackInfoFlipper == false){

					getAttackOneInfo();
					attackInfoFlipper = true;
				}
				else{

				}
			}
			else if(attackID == 2){

				if(attackInfoFlipper == true){

					getAttackTwoInfo();
					attackInfoFlipper = false;
				}
				else{



				}

			}
			else if(attackID == 3){

				if(attackInfoFlipper == false){

					getAttackThreeInfo();
					attackInfoFlipper = true;
				}
				else{



				}

			}

			currentClip = attackClip;

			image = attackSheet;

			clip = &frames[currentClip];

			futureY -= moveAttackPastVertical;
			futureY += moveAttackFutureVertical;
			futureX -= moveAttackPastHorizontal;
			futureX += moveAttackFutureHorizontal;
			moveAttackPastVertical = moveAttackFutureVertical;
			moveAttackPastHorizontal = moveAttackFutureHorizontal;
		}
		else{

			image = swordSheet;
			futureY -= moveAttackPastVertical;
			moveAttackPastVertical = 0;
			futureX -= moveAttackPastHorizontal;
			moveAttackPastHorizontal = 0;
		}

		if(((angleAttack >= 0 && angleAttack <= 90) || (angleAttack >= 270 && angleAttack <= 360))){

			direction = false;
			futureDirection = false;

		}
		else{

			direction = true;
			futureDirection = true;

		}


		futureY -= moveShieldPastVertical;
		moveShieldPastVertical = 0;
		futureX -= moveShieldPastHorizontal;
		moveShieldPastHorizontal = 0;




		walking = false;
		futureWalking = false;




	}
	direction = futureDirection;

	move(futureX - x, futureY - y);

	uniformGrid->update(hitboxes, pool);


}
//wormhole//
void player::getAttackOneInfo(){



	if(3 <= angleAttack && angleAttack < 357){

		if(angleAttack < 237){

			if(angleAttack < 177){

				if(angleAttack < 90){


					if(angleAttack < 21){

						if(angleAttack < 15){

							if(angleAttack < 9){

								//3 <= angle < 9


								attackPercent = 1;
								attackClip = 120;
								moveAttackFutureVertical = 12;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//9 <= angle < 15


								attackPercent = 1;
								attackClip = 117;
								moveAttackFutureVertical = 12;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//15 <= angle < 21


							attackPercent = 1;
							attackClip = 119;
							moveAttackFutureVertical = 12;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 27){

							//21 <= angle < 27


							attackPercent = 1;
							attackClip = 118;
							moveAttackFutureVertical = 12;
							moveAttackFutureHorizontal = 0;



						}
						else{

							//27 <= angle < 90


							attackPercent = 1;
							attackClip = 116;
							moveAttackFutureVertical = 12;
							moveAttackFutureHorizontal = 0;
						}

					}


				}
				else{

					if(angleAttack < 165){


						if(angleAttack < 159){

							if(angleAttack < 153){

								//90 <= angle 153



								attackPercent = 0.6;
								//attackClip = 101;
								attackClip = 106;
								moveAttackFutureVertical = 10;
								moveAttackFutureHorizontal = 0;
								//moveAttackFutureHorizontal = -35;
							}
							else{

								//153 <= angle < 159


								attackPercent = 0.63;
								attackClip = 99;
								moveAttackFutureVertical = 10;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//159 <= angle < 165


							attackPercent = 0.65;
							attackClip = 98;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 171){

							//165 <= angle < 171


							attackPercent = 0.67;
							attackClip = 102;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//171 <= angle < 177


							attackPercent = 0.69;
							attackClip = 103;
							moveAttackFutureHorizontal = 0;
						}

					}


				}

			}
			else{


				if(angleAttack < 207){

					if(angleAttack < 195){

						if(angleAttack < 189){

							if(angleAttack < 183){

								//177 <= angle < 183


								attackPercent = 0.7;
								attackClip = 100;

								moveAttackFutureHorizontal = 0;

							}
							else{

								//183 <= angle < 189


								attackPercent = 0.71;
								attackClip = 164;
								moveAttackFutureVertical = 18;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//189 <= angle < 195


							attackPercent = 0.7;
							attackClip = 165;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 201){

							//195 <= angle < 201


							attackPercent = 0.7;
							attackClip = 166;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//201 <= angle < 207


							attackPercent = 0.7;
							attackClip = 167;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else{

					if(angleAttack < 225){

						if(angleAttack < 219){

							if(angleAttack < 213){

								//207 <= angle < 213


								attackPercent = 0.7;
								attackClip = 206;
								moveAttackFutureVertical = 8;
								moveAttackFutureHorizontal = 0;


							}
							else{

								//213 <= angle < 219


								attackPercent = 0.7;
								attackClip = 212;
								moveAttackFutureVertical = -2;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//219 <= angle < 225


							attackPercent = 0.7;
							attackClip = 218;
							moveAttackFutureVertical = -10;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 231){

							//225 <= angle < 231



							attackPercent = 0.69;
							attackClip = 134;
							moveAttackFutureVertical = -15;
							moveAttackFutureHorizontal = 0;
						}
						else{

							//231 <= angle < 237


							attackPercent = 0.67;
							attackClip = 135;
							moveAttackFutureVertical = -22;
							moveAttackFutureHorizontal = 0;

						}

					}



				}



			}


		}
		else{

			if(angleAttack < 297){

				if(angleAttack < 267){

					if(angleAttack < 255){

						if(angleAttack < 249){

							if(angleAttack < 243){

								//237 <= angle < 243


								attackPercent = 0.65;
								attackClip = 137;
								moveAttackFutureVertical = -33;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//243 <= angle < 249


								attackPercent = 0.63;
								attackClip = 136;
								moveAttackFutureVertical = -33;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//249 <= angle < 255


							attackPercent = 0.6;
							attackClip = 138;
							moveAttackFutureVertical = -33;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 261){

							//255 <= angle < 261


							attackPercent = 0.57;
							attackClip = 189;
							moveAttackFutureVertical = -45;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//261 <= angle < 267


							attackPercent = 0.54;
							attackClip = 190;
							moveAttackFutureVertical = -45;
							moveAttackFutureHorizontal = 0;

						}

					}


				}
				else{

					if(angleAttack < 285){

						if(angleAttack < 279){

							if(angleAttack < 273){

								//267 <= angle < 273


								attackPercent = 0.5;
								attackClip = 188;
								moveAttackFutureVertical = -50;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//273 <= angle < 279


								attackPercent = 1;
								attackClip = 197;
								moveAttackFutureVertical = -44;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//279 <= angle < 285


							attackPercent = 1;
							attackClip = 198;
							moveAttackFutureVertical = -44;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 291){

							//285 <= angle < 291


							attackPercent = 1;
							attackClip = 149;
							moveAttackFutureVertical = -38;
							moveAttackFutureHorizontal = 0;



						}
						else{

							//291 <= angle < 297


							attackPercent = 1;
							attackClip = 150;
							moveAttackFutureVertical = -38;
							moveAttackFutureHorizontal = 0;

						}

					}

				}


			}
			else{

				if(angleAttack < 327){

					if(angleAttack < 315){

						if(angleAttack < 309){

							if(angleAttack < 303){


								//297 <= angle < 303


								attackPercent = 1;
								attackClip = 152;
								moveAttackFutureVertical = -28;
								moveAttackFutureHorizontal = 0;


							}
							else{

								//303 <= angle < 309


								attackPercent = 1;
								attackClip = 153;
								moveAttackFutureVertical = -23;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//309 <= angle < 315


							attackPercent = 1;
							attackClip = 151;
							moveAttackFutureVertical = -18;
							moveAttackFutureHorizontal = 0;
						}

					}
					else{

						if(angleAttack < 321){

							//315 <= angle < 321


							attackPercent = 1;
							attackClip = 221;
							moveAttackFutureVertical = -10;
							moveAttackFutureHorizontal = 0;


						}
						else{

							//321 <= angle < 327


							attackPercent = 1;
							attackClip = 215;
							moveAttackFutureVertical = -3;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else{

					if(angleAttack < 345){

						if(angleAttack < 339){

							if(angleAttack < 333){

								//327 <= angle < 333


								attackPercent = 1;
								attackClip = 209;
								moveAttackFutureVertical = 13;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//333 <= angle < 339


								attackPercent = 1;
								attackClip = 176;
								moveAttackFutureVertical = 10;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//339 <= angle < 345


							attackPercent = 1;
							attackClip = 178;
							moveAttackFutureVertical = 10;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 351){

							//345 <= angle < 351


							attackPercent = 1;
							attackClip = 177;
							moveAttackFutureVertical = 10;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//351 <= angle < 357


							attackPercent = 1;
							attackClip = 179;
							moveAttackFutureVertical = 10;
							moveAttackFutureHorizontal = 0;


						}


					}



				}

			}
		}
	}
	else{


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)

		attackPercent = 1;
		attackClip = 121;
		moveAttackFutureVertical = 12;
		moveAttackFutureHorizontal = 0;


	}


}
//wormhole
void player::getAttackTwoInfo(){

	if(3 <= angleAttack && angleAttack < 357){

		if(angleAttack < 237){

			if(angleAttack < 177){

				if(angleAttack < 90){


					if(angleAttack < 21){

						if(angleAttack < 15){

							if(angleAttack < 9){

								//3 <= angle < 9


								attackPercent = 1;
								attackClip = 126;
								moveAttackFutureVertical = 17;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//9 <= angle < 15


								attackPercent = 1;
								attackClip = 123;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//15 <= angle < 21


							attackPercent = 1;
							attackClip = 124;
							moveAttackFutureVertical = 17;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 27){

							//21 <= angle < 27

							attackPercent = 1;
							attackClip = 125;
							moveAttackFutureVertical = 17;
							moveAttackFutureHorizontal = 0;



						}
						else{

							//27 <= angle < 90



							attackPercent = 1;
							attackClip = 122;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;
						}

					}


				}
				else{

					if(angleAttack < 165){


						if(angleAttack < 159){

							if(angleAttack < 153){

								//90 <= angle 153


								attackPercent = 0.6;
								attackClip = 104;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;
							}
							else{

								//153 <= angle < 159

								attackPercent = 0.63;
								attackClip = 106;
								moveAttackFutureVertical = 15;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//159 <= angle < 165


							attackPercent = 0.65;
							attackClip = 107;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 171){

							//165 <= angle < 171


							attackPercent = 0.67;
							attackClip = 105;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//171 <= angle < 177


							attackPercent = 0.69;
							attackClip = 108;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;
						}

					}


				}

			}
			else{


				if(angleAttack < 207){

					if(angleAttack < 195){

						if(angleAttack < 189){

							if(angleAttack < 183){

								//177 <= angle < 183

								attackPercent = 0.7;
								attackClip = 109;
								moveAttackFutureVertical = 15;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//183 <= angle < 189


								attackPercent = 0.7;
								attackClip = 171;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//189 <= angle < 195


							attackPercent = 0.7;
							attackClip = 168;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 201){

							//195 <= angle < 201


							attackPercent = 0.7;
							attackClip = 169;
							moveAttackFutureVertical = 13;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//201 <= angle < 207


							attackPercent = 0.7;
							attackClip = 170;
							moveAttackFutureVertical = 0;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else{

					if(angleAttack < 225){

						if(angleAttack < 219){

							if(angleAttack < 213){

								//207 <= angle < 213


								attackPercent = 0.7;
								attackClip = 207;
								moveAttackFutureVertical = -20;
								moveAttackFutureHorizontal = 0;


							}
							else{

								//213 <= angle < 219


								attackPercent = 0.7;
								attackClip = 213;
								moveAttackFutureVertical = -30;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//219 <= angle < 225


							attackPercent = 0.7;
							attackClip = 219;
							moveAttackFutureVertical = -37;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 231){

							//225 <= angle < 231



							attackPercent = 0.69;
							attackClip = 139;
							moveAttackFutureVertical = -52;
							moveAttackFutureHorizontal = 0;
						}
						else{

							//231 <= angle < 237



							attackPercent = 0.67;
							attackClip = 140;
							moveAttackFutureVertical = -63;
							moveAttackFutureHorizontal = 0;

						}

					}



				}



			}


		}
		else{

			if(angleAttack < 297){

				if(angleAttack < 267){

					if(angleAttack < 255){

						if(angleAttack < 249){

							if(angleAttack < 243){

								//237 <= angle < 243


								attackPercent = 0.65;
								attackClip = 142;
								moveAttackFutureVertical = -70;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//243 <= angle < 249


								attackPercent = 0.63;
								attackClip = 143;
								moveAttackFutureVertical = -79;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//249 <= angle < 255


							attackPercent = 0.6;
							attackClip = 141;
							moveAttackFutureVertical = -86;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 261){

							//255 <= angle < 261


							attackPercent = 0.57;
							attackClip = 191;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//261 <= angle < 267


							attackPercent = 0.54;
							attackClip = 193;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}

					}


				}
				else{

					if(angleAttack < 285){

						if(angleAttack < 279){

							if(angleAttack < 273){

								//267 <= angle < 273


								attackPercent = 0.5;
								attackClip = 192;
								moveAttackFutureVertical = -85;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//273 <= angle < 279


								attackPercent = 1;
								attackClip = 200;
								moveAttackFutureVertical = -85;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//279 <= angle < 285


							attackPercent = 1;
							attackClip = 201;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 291){

							//285 <= angle < 291


							attackPercent = 1;
							attackClip = 154;
							moveAttackFutureVertical = -78;
							moveAttackFutureHorizontal = 0;


						}
						else{

							//291 <= angle < 297


							attackPercent = 1;
							attackClip = 155;
							moveAttackFutureVertical = -78;
							moveAttackFutureHorizontal = 0;

						}

					}

				}


			}
			else{

				if(angleAttack < 327){

					if(angleAttack < 315){

						if(angleAttack < 309){

							if(angleAttack < 303){


								//297 <= angle < 303


								attackPercent = 1;
								attackClip = 156;
								moveAttackFutureVertical = -68;
								moveAttackFutureHorizontal = 0;


							}
							else{

								//303 <= angle < 309


								attackPercent = 1;
								attackClip = 157;
								moveAttackFutureVertical = -57;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//309 <= angle < 315


							attackPercent = 1;
							attackClip = 158;
							moveAttackFutureVertical = -52;
							moveAttackFutureHorizontal = 0;
						}

					}
					else{

						if(angleAttack < 321){

							//315 <= angle < 321


							attackPercent = 1;
							attackClip = 222;
							moveAttackFutureVertical = -40;
							moveAttackFutureHorizontal = 0;


						}
						else{

							//321 <= angle < 327


							attackPercent = 1;
							attackClip = 216;
							moveAttackFutureVertical = -30;
							moveAttackFutureHorizontal = 0;


						}



					}

				}
				else{

					if(angleAttack < 345){

						if(angleAttack < 339){

							if(angleAttack < 333){

								//327 <= angle < 333


								attackPercent = 1;
								attackClip = 210;
								moveAttackFutureVertical = -15;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//333 <= angle < 339


								attackPercent = 1;
								attackClip = 180;
								moveAttackFutureVertical = 0;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//339 <= angle < 345


							attackPercent = 1;
							attackClip = 182;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 351){

							//345 <= angle < 351


							attackPercent = 1;
							attackClip = 181;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//351 <= angle < 357


							attackPercent = 1;
							attackClip = 183;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;


						}


					}



				}

			}
		}
	}
	else{


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		attackPercent = 1;
		attackClip = 127;
		moveAttackFutureVertical = 17;
		moveAttackFutureHorizontal = 0;


	}


}
//wormhole
void player::getAttackThreeInfo(){

	if(3 <= angleAttack && angleAttack < 357){

		if(angleAttack < 237){

			if(angleAttack < 177){

				if(angleAttack < 90){


					if(angleAttack < 21){

						if(angleAttack < 15){

							if(angleAttack < 9){

								//3 <= angle < 9


								attackPercent = 1;
								attackClip = 132;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//9 <= angle < 15


								attackPercent = 1;
								attackClip = 129;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//15 <= angle < 21


							attackPercent = 1;
							attackClip = 131;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 27){

							//21 <= angle < 27

							attackPercent = 1;
							attackClip = 130;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;



						}
						else{

							//27 <= angle < 90



							attackPercent = 1;
							attackClip = 128;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;
						}

					}


				}
				else{

					if(angleAttack < 165){


						if(angleAttack < 159){

							if(angleAttack < 153){

								//90 <= angle 153



								attackPercent = 0.6;
								attackClip = 110;
								moveAttackFutureVertical = 23;
								moveAttackFutureHorizontal = 0;
							}
							else{

								//153 <= angle < 159


								attackPercent = 0.63;
								attackClip = 111;
								moveAttackFutureVertical = 23;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//159 <= angle < 165


							attackPercent = 0.65;
							attackClip = 113;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 171){

							//165 <= angle < 171


							attackPercent = 0.67;
							attackClip = 112;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//171 <= angle < 177

							attackPercent = 0.69;
							attackClip = 114;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;
						}

					}


				}

			}
			else{


				if(angleAttack < 207){

					if(angleAttack < 195){

						if(angleAttack < 189){

							if(angleAttack < 183){

								//177 <= angle < 183


								attackPercent = 0.7;
								attackClip = 115;
								moveAttackFutureVertical = 23;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//183 <= angle < 189


								attackPercent = 0.7;
								attackClip = 175;
								moveAttackFutureVertical = 20;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//189 <= angle < 195

							attackPercent = 0.7;
							attackClip = 172;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 201){

							//195 <= angle < 201


							attackPercent = 0.7;
							attackClip = 174;
							moveAttackFutureVertical = 20;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//201 <= angle < 207


							attackPercent = 0.7;
							attackClip = 173;
							moveAttackFutureVertical = 0;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else{

					if(angleAttack < 225){

						if(angleAttack < 219){

							if(angleAttack < 213){

								//207 <= angle < 213


								attackPercent = 0.7;
								attackClip = 208;
								moveAttackFutureVertical = -15;
								moveAttackFutureHorizontal = 0;


							}
							else{

								//213 <= angle < 219

								attackPercent = 0.7;
								attackClip = 214;
								moveAttackFutureVertical = -26;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//219 <= angle < 225


							attackPercent = 0.7;
							attackClip = 220;
							moveAttackFutureVertical = -37;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 231){

							//225 <= angle < 231



							attackPercent = 0.69;
							attackClip = 145;
							moveAttackFutureVertical = -52;
							moveAttackFutureHorizontal = 0;
						}
						else{

							//231 <= angle < 237



							attackPercent = 0.67;
							attackClip = 147;
							moveAttackFutureVertical = -63;
							moveAttackFutureHorizontal = 0;

						}

					}



				}



			}


		}
		else{

			if(angleAttack < 297){

				if(angleAttack < 267){

					if(angleAttack < 255){

						if(angleAttack < 249){

							if(angleAttack < 243){

								//237 <= angle < 243


								attackPercent = 0.65;
								attackClip = 146;
								moveAttackFutureVertical = -68;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//243 <= angle < 249


								attackPercent = 0.63;
								attackClip = 148;
								moveAttackFutureVertical = -78;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//249 <= angle < 255


							attackPercent = 0.6;
							attackClip = 144;
							moveAttackFutureVertical = -82;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 261){

							//255 <= angle < 261


							attackPercent = 0.57;
							attackClip = 196;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//261 <= angle < 267


							attackPercent = 0.54;
							attackClip = 195;
							moveAttackFutureVertical = -90;
							moveAttackFutureHorizontal = 0;

						}

					}


				}
				else{

					if(angleAttack < 285){

						if(angleAttack < 279){

							if(angleAttack < 273){

								//267 <= angle < 273


								attackPercent = 0.5;
								attackClip = 194;
								moveAttackFutureVertical = -90;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//273 <= angle < 279


								attackPercent = 1;
								attackClip = 203;
								moveAttackFutureVertical = -85;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//279 <= angle < 285


							attackPercent = 1;
							attackClip = 205;
							moveAttackFutureVertical = -85;
							moveAttackFutureHorizontal = 0;

						}


					}
					else{

						if(angleAttack < 291){

							//285 <= angle < 291


							attackPercent = 1;
							attackClip = 159;
							moveAttackFutureVertical = -82;
							moveAttackFutureHorizontal = 0;


						}
						else{

							//291 <= angle < 297


							attackPercent = 1;
							attackClip = 160;
							moveAttackFutureVertical = -75;
							moveAttackFutureHorizontal = 0;

						}

					}

				}


			}
			else{

				if(angleAttack < 327){

					if(angleAttack < 315){

						if(angleAttack < 309){

							if(angleAttack < 303){


								//297 <= angle < 303


								attackPercent = 1;
								attackClip = 161;
								moveAttackFutureVertical = -70;
								moveAttackFutureHorizontal = 0;


							}
							else{

								//303 <= angle < 309


								attackPercent = 1;
								attackClip = 163;
								moveAttackFutureVertical = -60;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//309 <= angle < 315


							attackPercent = 1;
							attackClip = 162;
							moveAttackFutureVertical = -50;
							moveAttackFutureHorizontal = 0;
						}

					}
					else{

						if(angleAttack < 321){

							//315 <= angle < 321


							attackPercent = 1;
							attackClip = 223;
							moveAttackFutureVertical = -40;
							moveAttackFutureHorizontal = 0;


						}
						else{

							//321 <= angle < 327


							attackPercent = 1;
							attackClip = 217;
							moveAttackFutureVertical = -30;
							moveAttackFutureHorizontal = 0;

						}



					}

				}
				else{

					if(angleAttack < 345){

						if(angleAttack < 339){

							if(angleAttack < 333){

								//327 <= angle < 333


								attackPercent = 1;
								attackClip = 211;
								moveAttackFutureVertical = -15;
								moveAttackFutureHorizontal = 0;

							}
							else{

								//333 <= angle < 339


								attackPercent = 1;
								attackClip = 184;
								moveAttackFutureVertical = 0;
								moveAttackFutureHorizontal = 0;

							}

						}
						else{

							//339 <= angle < 345


							attackPercent = 1;
							attackClip = 186;
							moveAttackFutureVertical = 15;
							moveAttackFutureHorizontal = 0;

						}

					}
					else{

						if(angleAttack < 351){

							//345 <= angle < 351


							attackPercent = 1;
							attackClip = 185;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;

						}
						else{

							//351 <= angle < 357

							attackPercent = 1;
							attackClip = 187;
							moveAttackFutureVertical = 23;
							moveAttackFutureHorizontal = 0;


						}


					}



				}

			}
		}
	}
	else{


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		attackPercent = 1;
		attackClip = 133;
		moveAttackFutureVertical = 20;
		moveAttackFutureHorizontal = 0;


	}

}

void player::processInputs(){

	string * p = inputs.data();
	int numInputs = inputs.size();

	for (int i = 0 ; i < numInputs; i++){

		if ((*p).compare("LEFT_TRIGGER_PRESS") == 0){

			if(leftTriggerHandler % 2 == 0){

				leftTriggerHandler++;

			}


		}
		if((*p).compare("LEFT_TRIGGER_RELEASE") == 0){

			if(leftTriggerHandler % 2 != 0){

					leftTriggerHandler++;


			}

		}


		if ((*p).compare("RIGHT_TRIGGER_PRESS") == 0){

			if(rightTriggerHandler % 2 == 0){

				rightTriggerHandler++;

			}


		}
		if((*p).compare("RIGHT_TRIGGER_RELEASE") == 0){

			if(rightTriggerHandler % 2 != 0){


					rightTriggerHandler++;


			}

		}

		if((*p).compare("RIGHT_BUMPER_PRESS") == 0){

			if(attackOne == -1 && attackTwo == -1 && attackThree == -1){

				if(!jumping){
					futureJumping = true;
					jumpTimer = 0;
				}
			}

		}
		if((*p).compare("JOYSTICK_RIGHT") == 0){

			if(attackOne == -1 && attackTwo == -1 && attackThree == -1){

				futureDirection = true;

				futureWalking = true;

			}

		}
		else if((*p).compare("JOYSTICK_LEFT") == 0){

			if(attackOne == -1 && attackTwo == -1 && attackThree == -1){
				futureDirection = false;
				futureWalking = true;
			}
		}
		else if((*p).compare("JOYSTICK_RELEASE") == 0){

			if(walking){

				futureWalking = false;

			}

		}
		else if((*p).compare("JOYSTICK2_HELD") == 0){

			if(attackOne == -1 && attackTwo == -1 && attackThree == -1){

				rJoystick = true;

			}
			else{

				rJoystick = false;

			}

		}
		else if((*p).compare("LEFT_BUMPER_PRESS") == 0){

			if(attackOne == -1 && attackTwo == -1 && attackThree == -1){

				lBumper = true;

			}
			else{

				lBumper = false;

			}
		}
		else if((*p).compare("LEFT_BUMPER_RELEASE") == 0){

			lBumper = false;

		}
		else if((*p).compare("JOYSTICK2_RELEASE") == 0){

			rJoystick = false;

		}
		else if((*p).compare("RIGHT_STICK_CLICK") == 0){

			futureBashing = true;

		}

		p++;

	}

}

void player::handleShield(){

	if(3 <= angleShield && angleShield < 357){


		if(angleShield < 237){

			if(angleShield < 177){

				if(angleShield < 90){


					if(angleShield < 21){

						if(angleShield < 15){

							if(angleShield < 9){

								//3 <= angle < 9


								moveShieldFutureVertical = -12;
								moveShieldFutureHorizontal = -10;
								currentClip = 81;

								clip = &frames[currentClip];

							}
							else{

								//9 <= angle < 15


								moveShieldFutureVertical = -8;
								moveShieldFutureHorizontal = -10;
								currentClip = 82;

								clip = &frames[currentClip];

							}

						}
						else{

							//15 <= angle < 21


							moveShieldFutureVertical = 0;
							moveShieldFutureHorizontal = -10;
							currentClip = 77;

							clip = &frames[currentClip];

						}


					}
					else{

						if(angleShield < 27){

							//21 <= angle < 27


							moveShieldFutureVertical = 5;
							moveShieldFutureHorizontal = -10;
							currentClip = 78;

							clip = &frames[currentClip];



						}
						else{

							//27 <= angle < 90



							moveShieldFutureVertical = 11;
							moveShieldFutureHorizontal = -10;

							currentClip = 79;

							clip = &frames[currentClip];

						}

					}


				}
				else{

					if(angleShield < 165){


						if(angleShield < 159){

							if(angleShield < 153){

								//90 <= angle 153



								moveShieldFutureVertical = 16;
								moveShieldFutureHorizontal = -32;
								currentClip = 56;

								clip = &frames[currentClip];

							}
							else{

								//153 <= angle < 159


								moveShieldFutureVertical = 8;
								moveShieldFutureHorizontal = -32;
								currentClip = 57;

								clip = &frames[currentClip];

							}

						}
						else{

							//159 <= angle < 165


							moveShieldFutureVertical = 3;
							moveShieldFutureHorizontal = -34;
							currentClip = 58;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 171){

							//165 <= angle < 171


							moveShieldFutureVertical = -3;
							moveShieldFutureHorizontal = -35;
							currentClip = 59;

							clip = &frames[currentClip];

						}
						else{

							//171 <= angle < 177


							moveShieldFutureVertical = -7;
							moveShieldFutureHorizontal = -37;
							currentClip = 60;

							clip = &frames[currentClip];

						}

					}


				}

			}
			else{


				if(angleShield < 207){

					if(angleShield < 195){

						if(angleShield < 189){

							if(angleShield < 183){

								//177 <= angle < 183


								moveShieldFutureVertical = -10;
								moveShieldFutureHorizontal = -40;
								currentClip = 61;

								clip = &frames[currentClip];

							}
							else{

								//183 <= angle < 189


								moveShieldFutureVertical = -17;
								moveShieldFutureHorizontal = -38;
								currentClip = 62;

								clip = &frames[currentClip];

							}

						}
						else{

							//189 <= angle < 195


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -36;
							currentClip = 63;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 201){

							//195 <= angle < 201


							moveShieldFutureVertical = -21;
							moveShieldFutureHorizontal = -35;
							currentClip = 64;

							clip = &frames[currentClip];

						}
						else{

							//201 <= angle < 207


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -35;
							currentClip = 65;

							clip = &frames[currentClip];

						}



					}

				}
				else{

					if(angleShield < 225){

						if(angleShield < 219){

							if(angleShield < 213){

								//207 <= angle < 213


								moveShieldFutureVertical = -22;
								moveShieldFutureHorizontal = -32;
								currentClip = 66;

								clip = &frames[currentClip];


							}
							else{

								//213 <= angle < 219


								moveShieldFutureVertical = -27;
								moveShieldFutureHorizontal = -32;
								currentClip = 67;

								clip = &frames[currentClip];

							}

						}
						else{

							//219 <= angle < 225


							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -29;
							currentClip = 68;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 231){

							//225 <= angle < 231



							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -27;
							currentClip = 69;

							clip = &frames[currentClip];

						}
						else{

							//231 <= angle < 237



							moveShieldFutureHorizontal = -24;
							currentClip = 70;

							clip = &frames[currentClip];

						}

					}



				}



			}


		}
		else{

			if(angleShield < 297){

				if(angleShield < 267){

					if(angleShield < 255){

						if(angleShield < 249){

							if(angleShield < 243){

								//237 <= angle < 243


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -24;
								currentClip = 71;

								clip = &frames[currentClip];

							}
							else{

								//243 <= angle < 249


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -20;
								currentClip = 72;

								clip = &frames[currentClip];

							}

						}
						else{

							//249 <= angle < 255


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -17;
							currentClip = 73;

							clip = &frames[currentClip];

						}


					}
					else{

						if(angleShield < 261){

							//255 <= angle < 261


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -12;
							currentClip = 74;

							clip = &frames[currentClip];

						}
						else{

							//261 <= angle < 267


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -8;
							currentClip = 75;

							clip = &frames[currentClip];

						}

					}


				}
				else{

					if(angleShield < 285){

						if(angleShield < 279){

							if(angleShield < 273){

								//267 <= angle < 273


								moveShieldFutureVertical = -28;
								currentClip = 76;

								clip = &frames[currentClip];


							}
							else{

								//273 <= angle < 279


								moveShieldFutureVertical = -28;
								currentClip = 96;

								clip = &frames[currentClip];

							}

						}
						else{

							//279 <= angle < 285


							moveShieldFutureVertical = -28;
							currentClip = 97;

							clip = &frames[currentClip];

						}


					}
					else{

						if(angleShield < 291){

							//285 <= angle < 291


							moveShieldFutureVertical = -28;
							currentClip = 92;

							clip = &frames[currentClip];


						}
						else{

							//291 <= angle < 297


							moveShieldFutureVertical = -28;
							currentClip = 93;

							clip = &frames[currentClip];

						}

					}

				}


			}
			else{

				if(angleShield < 327){

					if(angleShield < 315){

						if(angleShield < 309){

							if(angleShield < 303){


								//297 <= angle < 303


								moveShieldFutureVertical = -28;
								currentClip = 94;

								clip = &frames[currentClip];


							}
							else{

								//303 <= angle < 309


								moveShieldFutureVertical = -25;
								currentClip = 89;

								clip = &frames[currentClip];

							}

						}
						else{

							//309 <= angle < 315


							moveShieldFutureVertical = -30;
							currentClip = 90;

							clip = &frames[currentClip];
						}

					}
					else{

						if(angleShield < 321){

							//315 <= angle < 321


							moveShieldFutureVertical = -30;
							currentClip = 91;

							clip = &frames[currentClip];


						}
						else{

							//321 <= angle < 327


							moveShieldFutureVertical = -30;
							currentClip = 86;

							clip = &frames[currentClip];

						}



					}

				}
				else{

					if(angleShield < 345){

						if(angleShield < 339){

							if(angleShield < 333){

								//327 <= angle < 333


								moveShieldFutureVertical = -28;
								currentClip = 87;

								clip = &frames[currentClip];

							}
							else{

								//333 <= angle < 339


								moveShieldFutureVertical = -25;
								currentClip = 88;

								clip = &frames[currentClip];

							}

						}
						else{

							//339 <= angle < 345


							moveShieldFutureVertical = -25;
							currentClip = 83;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 351){

							//345 <= angle < 351


							moveShieldFutureVertical = -28;
							currentClip = 84;

							clip = &frames[currentClip];

						}
						else{

							//351 <= angle < 357


							moveShieldFutureVertical = -22;
							currentClip = 85;

							clip = &frames[currentClip];


						}
					}
				}

			}

		}

	}
	else{


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		moveShieldFutureVertical = -18;
		moveShieldFutureHorizontal = -10;
		currentClip = 80;

		clip = &frames[currentClip];


	}



}

void player::handleJump(){
	/*
	switch(jumpTimer){
		case 0:
			futureY = y - 14;
			break;
		case 2:
			futureY = y - 28;
			break;
		case 4:
			futureY = y - 24;
			break;
		case 6:
			futureY = y - 22;
			break;
		case 8:
			futureY = y - 16;
			break;
		case 10:
			futureY = y - 16;
			break;
		case 12:
			futureY = y - 12;
			break;
		case 14:
			futureY = y - 8;
			break;
		case 16:
			futureY = y - 6;
			break;
		case 18:
			futureY = y - 4;
			break;
		case 20:
			futureY = y;
			break;
		case 22:
			futureY = y;
			break;
		case 24:
			futureY = y + 4;
			break;
		case 26:
			futureY = y + 6;
			break;
		case 28:
			futureY = y + 14;
			break;
		case 30:
			futureY = y + 12;
			break;
		case 32:
			futureY = y + 18;
			break;
		case 34:
			futureY = y + 18;
			break;
		case 36:
			futureY = y + 22;
			break;
		case 38:
			futureY = y + 24;
			break;
		case 40:
			futureY = y + 32;
			futureJumping = false;
			futureDownShielding = false;
			rightTriggerHandler = 0;
			break;
	}


	*/
	switch(jumpTimer){
		case 0:
			futureY = y - 11;
			break;
		case 1:
			futureY = y - 11;
			break;
		case 2:
			futureY = y - 16;
			break;
		case 3:
			futureY = y - 16;
			break;
		case 4:
			futureY = y - 15;
			break;
		case 5:
			futureY = y - 15;
			break;
		case 6:
			futureY = y - 14;
			break;
		case 7:
			futureY = y - 14;
			break;
		case 8:
			futureY = y - 12;
			break;
		case 9:
			futureY = y - 12;
			break;
		case 10:
			futureY = y - 12;
			break;
		case 11:
			futureY = y - 12;
			break;
		case 12:
			futureY = y - 11;
			break;
		case 13:
			futureY = y - 11;
			break;
		case 14:
			futureY = y - 9;
			break;
		case 15:
			futureY = y - 9;
			break;
		case 16:
			futureY = y - 9;
			break;
		case 17:
			futureY = y - 9;
			break;
		case 18:
			futureY = y - 8;
			break;
		case 19:
			futureY = y - 8;
			break;
		case 20:
			futureY = y;
			break;
		case 21:
			futureY = y;
			break;
		case 23:
			futureY = y + 8;
			break;
		case 24:
			futureY = y + 8;
			break;
		case 25:
			futureY = y + 9;
			break;
		case 26:
			futureY = y + 9;
			break;
		case 27:
			futureY = y + 11;
			break;
		case 28:
			futureY = y + 11;
			break;
		case 29:
			futureY = y + 11;
			break;
		case 30:
			futureY = y + 11;
			break;
		case 31:
			futureY = y + 13;
			break;
		case 32:
			futureY = y + 13;
			break;
		case 33:
			futureY = y + 13;
			break;
		case 34:
			futureY = y + 13;
			break;
		case 35:
			futureY = y + 14;
			break;
		case 36:
			futureY = y + 14;
			break;
		case 37:
			futureY = y + 15;
			break;
		case 38:
			futureY = y + 15;
			break;
		case 39:
			futureY = y + 46;
			futureJumping = false;
			futureDownShielding = false;
			rightTriggerHandler = 0;
			break;
	}
	jumpTimer++;


}

void player::groundAttackOneLeft(){

	attackID = 1;

	switch(attackOne){
		case 0:
			currentClip = 0;
			clip = &frames[currentClip];
			break;
		case 5:
			currentClip = 1;
			clip = &frames[currentClip];
			break;
		case 10:
			currentClip = 2;
			clip = &frames[currentClip];
			break;
		case 15:
			currentClip = 7;
			clip = &frames[currentClip];
			break;
		case 20:
			currentClip = 8;
			clip = &frames[currentClip];
			break;
		case 25:
			currentClip = 9;
			clip = &frames[currentClip];
			break;
		case 30:
			currentClip = 10;
			clip = &frames[currentClip];
			break;
		case 35:

			futureStriking = true;
			clip = &frames[currentClip];
			xMove = -200*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 40:
			futureStriking = false;
			currentClip = 12;
			clip = &frames[currentClip];
			break;
		case 45:
			currentClip = 12;
			clip = &frames[currentClip];
			break;
		}
		if(attackOne == 50){

			if(attackTwo != 0){

				currentClip = 0;
				xMove = 200*(1/timeFactor)/(METERS_TO_PIXELS);
				clip = &frames[currentClip];
				rightTriggerHandler = 0;
				attackInfoFlipper = false;

			}
			futureAttackOne = -1;

		}
		else{

			futureAttackOne = attackOne + 1;

		}

}

void player::groundAttackTwoLeft(){

	attackID = 2;

	switch(attackTwo){
		case 0:
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = -5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 5:
			currentClip = 14;
			futureStriking = true;
			clip = &frames[currentClip];
			xMove = -17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 10:

			//currentClip = 15;
			clip = &frames[currentClip];
			xMove = -270*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 15:

			futureStriking = false;
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = 286*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		}
		if(attackTwo == 20){

			if(attackThree != 0){
				currentClip = 0;
				clip = &frames[currentClip];
				xMove = 206*(1/timeFactor)/(METERS_TO_PIXELS);
				rightTriggerHandler = 0;
				attackInfoFlipper = false;

			}
			futureAttackTwo = -1;
		}
		else{

			futureAttackTwo = attackTwo + 1;

		}

}

void player::groundAttackThreeLeft(){

		attackID = 3;
		switch(attackThree){
			case 0:
				currentClip = 17;
				clip = &frames[currentClip];
				xMove = 206*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 5:
				currentClip = 18;
				clip = &frames[currentClip];
				break;
			case 10:
				currentClip = 19;
				clip = &frames[currentClip];
				break;
			case 15:
				currentClip = 20;
				clip = &frames[currentClip];
				xMove = -90*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 20:
				futureStriking = true;
				currentClip = 21;
				clip = &frames[currentClip];
				xMove = -290*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 30:
				futureStriking = false;
				clip = &frames[currentClip];
				xMove = 72*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 35:
				currentClip = 23;
				clip = &frames[currentClip];
				xMove = 72*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 40:

				currentClip = 24;
				clip = &frames[currentClip];
				xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 45:

				//currentClip = 25;
				clip = &frames[currentClip];
				xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 50:

				currentClip = 27;
				clip = &frames[currentClip];
				xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
			case 55:
				currentClip = 27;
				clip = &frames[currentClip];
				xMove = 59*(1/timeFactor)/(METERS_TO_PIXELS);
				break;
		}
		if(attackThree == 60){

			currentClip = 0;
			clip = &frames[currentClip];
			futureAttackThree = -1;
			rightTriggerHandler = 0;
			attackInfoFlipper = false;

		}
		else{

			futureAttackThree = attackThree + 1;

		}

}

void player::groundAttackOneRight(){

	attackID = 1;
	switch(attackOne){
		case 0:
			currentClip = 32;
			clip = &frames[currentClip];
			break;
		case 5:
			currentClip = 31;
			clip = &frames[currentClip];
			break;
		case 10:
			currentClip = 30;
			clip = &frames[currentClip];
			break;
		case 15:
			currentClip = 35;
			clip = &frames[currentClip];
			break;
		case 20:
			currentClip = 34;
			clip = &frames[currentClip];
			break;
		case 25:
			currentClip = 33;
			clip = &frames[currentClip];
			break;
		case 30:
			currentClip = 40;
			clip = &frames[currentClip];
			break;
		case 35:
			futureStriking = true;
			currentClip = 39;
			clip = &frames[currentClip];
			xMove = 50*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 45:
			futureStriking = false;
			currentClip = 38;
			clip = &frames[currentClip];
			break;

	}
	if(attackOne == 50){

		if(attackTwo != 0){

			currentClip = 32;
			xMove = -50*(1/timeFactor)/(METERS_TO_PIXELS);
			clip = &frames[currentClip];
			rightTriggerHandler = 0;
			attackInfoFlipper = false;

		}
		futureAttackOne = -1;

	}
	else{

		futureAttackOne = attackOne + 1;

	}



}

void player::groundAttackTwoRight(){
	attackID = 2;
	switch(attackTwo){
		case 0:
			currentClip = 43;
			clip = &frames[currentClip];
			xMove = 5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 5:
			futureStriking = true;
			currentClip = 42;
			clip = &frames[currentClip];
			xMove = 17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 10:
			currentClip = 41;
			clip = &frames[currentClip];
			xMove = 67*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 15:
			futureStriking = false;
			currentClip = 46;
			clip = &frames[currentClip];
			xMove = -71*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		}
		if(attackTwo == 20){

			if(attackThree != 0){
				currentClip = 32;
				clip = &frames[currentClip];
				xMove = -68*(1/timeFactor)/(METERS_TO_PIXELS);
				rightTriggerHandler = 0;
				attackInfoFlipper = false;

			}
			futureAttackTwo = -1;
		}
		else{

			futureAttackTwo = attackTwo + 1;


		}

}

void player::groundAttackThreeRight(){
	attackID = 3;
	switch(attackThree){
		case 0:
			currentClip = 45;
			clip = &frames[currentClip];
			xMove = -62*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 5:
			currentClip = 44;
			clip = &frames[currentClip];
			break;
		case 10:
			currentClip = 49;
			clip = &frames[currentClip];
			break;
		case 15:
			currentClip = 48;
			clip = &frames[currentClip];
			xMove = 22*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 20:
			futureStriking = true;
			currentClip = 47;
			clip = &frames[currentClip];
			xMove = 72*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 30:
			futureStriking = false;
			currentClip = 52;
			clip = &frames[currentClip];
			xMove = -18*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 35:
			currentClip = 51;
			clip = &frames[currentClip];
			xMove = -18*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 40:
			currentClip = 50;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 45:
			currentClip = 55;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 50:
			currentClip = 54;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 55:
			currentClip = 53;
			clip = &frames[currentClip];
			xMove = -16*(1/timeFactor)/(METERS_TO_PIXELS);
			break;


		}
		if(attackThree == 60){

			currentClip = 32;
			clip = &frames[currentClip];
			futureAttackThree = -1;
			rightTriggerHandler = 0;
			attackInfoFlipper = false;

		}
		else{

			futureAttackThree = attackThree + 1;

		}


}

void player::handleShieldAir(){



	if(51 <= angleShield && angleShield < 57){

		futureDownShielding = true;


		currentClip = 234;

		clip = &frames[currentClip];

	}
	else if(123 <= angleShield && angleShield < 129){

		futureDownShielding = true;

		currentClip = 224;

		clip = &frames[currentClip];

	}
	else if(57 <= angleShield && angleShield < 123){

		futureDownShielding = true;

		if(angleShield < 93){

		  if(angleShield < 75){

		    if(angleShield < 69){

		      if(angleShield < 63){

		        //57 <= x < 63
		        //60
						currentClip = 235;

						clip = &frames[currentClip];

		      }
		      else{

		        // 63 <= x < 69
		        //66
						currentClip = 236;

						clip = &frames[currentClip];


		      }

		    }
		    else{

		      // 69 <= x < 75
		      //72

					currentClip = 231;

					clip = &frames[currentClip];

		    }

		  }
		  else{

		    if(angleShield < 87){

		      if(angleShield < 81){

		        // 75 <= x < 81
		        //78

						currentClip = 232;

						clip = &frames[currentClip];

		      }
		      else{

		        // 81 <= x < 87
		        //84

						currentClip = 233;

						clip = &frames[currentClip];


		      }


		    }
		    else{

		      //87 <= x < 93
		      //90
					currentClip = 230;

					clip = &frames[currentClip];

		    }

		  }

		}
		else{

		  if(angleShield < 111){

		    if(angleShield < 105){

		      if(angleShield < 99){

		        // 93 <= x < 99
		        //96

						currentClip = 229;

						clip = &frames[currentClip];

		      }
		      else{

		        // 99 <= x < 105
		        //102

						currentClip = 228;

						clip = &frames[currentClip];

		      }


		    }
		    else{

		      // 105 <= x < 111
		      //108

					currentClip = 227;

					clip = &frames[currentClip];

		    }


		  }
		  else{

		    if(angleShield < 117){

		      //111 <= x < 117
		      //114


					currentClip = 226;

					clip = &frames[currentClip];



		    }
		    else{

		      //117 <= x < 123
		      //120

					currentClip = 225;

					clip = &frames[currentClip];

		    }

		  }

		}


	}
	else if(3 <= angleShield && angleShield < 357){

		futureDownShielding = false;

		if(angleShield < 237){

			if(angleShield < 177){

				if(angleShield < 90){


					if(angleShield < 21){

						if(angleShield < 15){

							if(angleShield < 9){

								//3 <= angle < 9


								moveShieldFutureVertical = -12;
								moveShieldFutureHorizontal = -10;
								currentClip = 81;

								clip = &frames[currentClip];

							}
							else{

								//9 <= angle < 15


								moveShieldFutureVertical = -8;
								moveShieldFutureHorizontal = -10;
								currentClip = 82;

								clip = &frames[currentClip];

							}

						}
						else{

							//15 <= angle < 21


							moveShieldFutureVertical = 0;
							moveShieldFutureHorizontal = -10;
							currentClip = 77;

							clip = &frames[currentClip];

						}


					}
					else{

						if(angleShield < 27){

							//21 <= angle < 27


							moveShieldFutureVertical = 5;
							moveShieldFutureHorizontal = -10;
							currentClip = 78;

							clip = &frames[currentClip];



						}
						else{

							//27 <= angle < 90



							moveShieldFutureVertical = 11;
							moveShieldFutureHorizontal = -10;

							currentClip = 79;

							clip = &frames[currentClip];

						}

					}


				}
				else{

					if(angleShield < 165){


						if(angleShield < 159){

							if(angleShield < 153){

								//90 <= angle 153



								moveShieldFutureVertical = 16;
								moveShieldFutureHorizontal = -32;
								currentClip = 56;

								clip = &frames[currentClip];

							}
							else{

								//153 <= angle < 159


								moveShieldFutureVertical = 8;
								moveShieldFutureHorizontal = -32;
								currentClip = 57;

								clip = &frames[currentClip];

							}

						}
						else{

							//159 <= angle < 165


							moveShieldFutureVertical = 3;
							moveShieldFutureHorizontal = -34;
							currentClip = 58;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 171){

							//165 <= angle < 171


							moveShieldFutureVertical = -3;
							moveShieldFutureHorizontal = -35;
							currentClip = 59;

							clip = &frames[currentClip];

						}
						else{

							//171 <= angle < 177


							moveShieldFutureVertical = -7;
							moveShieldFutureHorizontal = -37;
							currentClip = 60;

							clip = &frames[currentClip];

						}

					}


				}

			}
			else{


				if(angleShield < 207){

					if(angleShield < 195){

						if(angleShield < 189){

							if(angleShield < 183){

								//177 <= angle < 183


								moveShieldFutureVertical = -10;
								moveShieldFutureHorizontal = -40;
								currentClip = 61;

								clip = &frames[currentClip];

							}
							else{

								//183 <= angle < 189


								moveShieldFutureVertical = -17;
								moveShieldFutureHorizontal = -38;
								currentClip = 62;

								clip = &frames[currentClip];

							}

						}
						else{

							//189 <= angle < 195


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -36;
							currentClip = 63;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 201){

							//195 <= angle < 201


							moveShieldFutureVertical = -21;
							moveShieldFutureHorizontal = -35;
							currentClip = 64;

							clip = &frames[currentClip];

						}
						else{

							//201 <= angle < 207


							moveShieldFutureVertical = -22;
							moveShieldFutureHorizontal = -35;
							currentClip = 65;

							clip = &frames[currentClip];

						}



					}

				}
				else{

					if(angleShield < 225){

						if(angleShield < 219){

							if(angleShield < 213){

								//207 <= angle < 213


								moveShieldFutureVertical = -22;
								moveShieldFutureHorizontal = -32;
								currentClip = 66;

								clip = &frames[currentClip];


							}
							else{

								//213 <= angle < 219


								moveShieldFutureVertical = -27;
								moveShieldFutureHorizontal = -32;
								currentClip = 67;

								clip = &frames[currentClip];

							}

						}
						else{

							//219 <= angle < 225


							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -29;
							currentClip = 68;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 231){

							//225 <= angle < 231



							moveShieldFutureVertical = -25;
							moveShieldFutureHorizontal = -27;
							currentClip = 69;

							clip = &frames[currentClip];

						}
						else{

							//231 <= angle < 237



							moveShieldFutureHorizontal = -24;
							currentClip = 70;

							clip = &frames[currentClip];

						}

					}



				}



			}


		}
		else{

			if(angleShield < 297){

				if(angleShield < 267){

					if(angleShield < 255){

						if(angleShield < 249){

							if(angleShield < 243){

								//237 <= angle < 243


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -24;
								currentClip = 71;

								clip = &frames[currentClip];

							}
							else{

								//243 <= angle < 249


								moveShieldFutureVertical = -24;
								moveShieldFutureHorizontal = -20;
								currentClip = 72;

								clip = &frames[currentClip];

							}

						}
						else{

							//249 <= angle < 255


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -17;
							currentClip = 73;

							clip = &frames[currentClip];

						}


					}
					else{

						if(angleShield < 261){

							//255 <= angle < 261


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -12;
							currentClip = 74;

							clip = &frames[currentClip];

						}
						else{

							//261 <= angle < 267


							moveShieldFutureVertical = -24;
							moveShieldFutureHorizontal = -8;
							currentClip = 75;

							clip = &frames[currentClip];

						}

					}


				}
				else{

					if(angleShield < 285){

						if(angleShield < 279){

							if(angleShield < 273){

								//267 <= angle < 273


								moveShieldFutureVertical = -28;
								currentClip = 76;

								clip = &frames[currentClip];


							}
							else{

								//273 <= angle < 279


								moveShieldFutureVertical = -28;
								currentClip = 96;

								clip = &frames[currentClip];

							}

						}
						else{

							//279 <= angle < 285


							moveShieldFutureVertical = -28;
							currentClip = 97;

							clip = &frames[currentClip];

						}


					}
					else{

						if(angleShield < 291){

							//285 <= angle < 291


							moveShieldFutureVertical = -28;
							currentClip = 92;

							clip = &frames[currentClip];


						}
						else{

							//291 <= angle < 297


							moveShieldFutureVertical = -28;
							currentClip = 93;

							clip = &frames[currentClip];

						}

					}

				}


			}
			else{

				if(angleShield < 327){

					if(angleShield < 315){

						if(angleShield < 309){

							if(angleShield < 303){


								//297 <= angle < 303


								moveShieldFutureVertical = -28;
								currentClip = 94;

								clip = &frames[currentClip];


							}
							else{

								//303 <= angle < 309


								moveShieldFutureVertical = -25;
								currentClip = 89;

								clip = &frames[currentClip];

							}

						}
						else{

							//309 <= angle < 315


							moveShieldFutureVertical = -30;
							currentClip = 90;

							clip = &frames[currentClip];
						}

					}
					else{

						if(angleShield < 321){

							//315 <= angle < 321


							moveShieldFutureVertical = -30;
							currentClip = 91;

							clip = &frames[currentClip];


						}
						else{

							//321 <= angle < 327


							moveShieldFutureVertical = -30;
							currentClip = 86;

							clip = &frames[currentClip];

						}



					}

				}
				else{

					if(angleShield < 345){

						if(angleShield < 339){

							if(angleShield < 333){

								//327 <= angle < 333


								moveShieldFutureVertical = -28;
								currentClip = 87;

								clip = &frames[currentClip];

							}
							else{

								//333 <= angle < 339


								moveShieldFutureVertical = -25;
								currentClip = 88;

								clip = &frames[currentClip];

							}

						}
						else{

							//339 <= angle < 345


							moveShieldFutureVertical = -25;
							currentClip = 83;

							clip = &frames[currentClip];

						}

					}
					else{

						if(angleShield < 351){

							//345 <= angle < 351


							moveShieldFutureVertical = -28;
							currentClip = 84;

							clip = &frames[currentClip];

						}
						else{

							//351 <= angle < 357


							moveShieldFutureVertical = -22;
							currentClip = 85;

							clip = &frames[currentClip];


						}
					}
				}

			}

		}

	}
	else{


		//(357 <= angle && angle < 360) || (0 <= angle && angle < 3)


		moveShieldFutureVertical = -18;
		moveShieldFutureHorizontal = -10;
		currentClip = 80;

		clip = &frames[currentClip];


	}



}

void player::airAttackLeft(){

	switch(airAttackTimer){
		case 0:
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = -5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 5:
			currentClip = 14;
			futureStriking = true;
			clip = &frames[currentClip];
			xMove = -17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 10:

			//currentClip = 15;
			clip = &frames[currentClip];
			xMove = -270*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 15:

			futureStriking = false;
			currentClip = 13;
			clip = &frames[currentClip];
			xMove = 286*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		}
		if(airAttackTimer == 20){


				currentClip = 0;
				clip = &frames[currentClip];
				xMove = 206*(1/timeFactor)/(METERS_TO_PIXELS);
				rightTriggerHandler = 0;
				attackInfoFlipper = false;



			futureAirAttackTimer = -1;
		}
		else{

			futureAirAttackTimer = airAttackTimer + 1;

		}


}

void player::airAttackRight(){

	switch(airAttackTimer){
		case 0:
			currentClip = 43;
			clip = &frames[currentClip];
			xMove = 5*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 5:
			futureStriking = true;
			currentClip = 42;
			clip = &frames[currentClip];
			xMove = 17*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 10:
			currentClip = 41;
			clip = &frames[currentClip];
			xMove = 67*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		case 15:
			futureStriking = false;
			currentClip = 46;
			clip = &frames[currentClip];
			xMove = -71*(1/timeFactor)/(METERS_TO_PIXELS);
			break;
		}
		if(airAttackTimer == 20){


				currentClip = 32;
				clip = &frames[currentClip];
				xMove = -68*(1/timeFactor)/(METERS_TO_PIXELS);
				rightTriggerHandler = 0;
				attackInfoFlipper = false;


			futureAirAttackTimer = -1;
		}
		else{

			futureAirAttackTimer = airAttackTimer + 1;


		}

}

void getJoystickInfo(float * radiusLeft, float * angleLeft, int xDir, int yDir){

	*radiusLeft = (float)sqrt(abs((long)(xDir*xDir) + (long)(yDir*yDir)));



	if(xDir == 0){

		if(yDir > 0){

			*angleLeft = 90;

		}
		else if(yDir < 0){

			*angleLeft = 270;

		}
		else if(yDir == 0){

			*angleLeft = 0;

		}

	}
	else if(yDir == 0){

		if(xDir > 0){

			*angleLeft = 0;

		}
		else if(xDir < 0){

			*angleLeft = 180;

		}

	}
	else{

		if(xDir * -1 < 0 && yDir * -1 < 0){

			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			//cout << "Angle: " << *angle << endl;

		}
		else if(xDir * -1 > 0 && yDir * -1 < 0){


			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			*angleLeft = 180 - abs(*angleLeft);

		}
		else if(xDir * -1 > 0 && yDir * -1 > 0){


			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			*angleLeft += 180;

		}
		else if(xDir * -1 < 0 && yDir * -1 > 0){


			*angleLeft = atan((double)((double)yDir)/(double)xDir) * 180 / PI;

			*angleLeft += 360;

		}


	}


}

void player::printDebugInformation(){

	cout << endl;
	cout << endl;
	cout << endl;
	cout << "DEBUG INFO" << endl;
	cout << "attacking: " << attacking << endl;
	cout << "attackOne: " << attackOne << endl;
	cout << "futureAttackOne: " << futureAttackOne << endl;
	cout << "attackTwo: " << attackTwo << endl;
	cout << "futureAttackTwo: " << futureAttackTwo << endl;
	cout << "attackThree: " << attackThree << endl;
	cout << "futureAttackThree: " << futureAttackThree << endl;
	cout << "direction: " << direction << endl;
	cout << "futureDirection: " << futureDirection << endl;
	cout << "jumping: " << jumping << endl;
	cout << "futureJumping: " << futureJumping << endl;
	cout << "jumpTimer: " << jumpTimer << endl;
	cout << "radiusLeft: " << radiusLeft << endl;
	cout << "radiusRight: " << radiusRight << endl;
	cout << "angleShield: " << angleShield << endl;
	cout << "angleAttack: " << angleAttack << endl;
	cout << "striking: " << striking << endl;
	cout << "futureStriking: " << futureStriking << endl;
	cout << "walking: " << walking << endl;
	cout << "futureWalking: " << futureWalking << endl;
	cout << "shielding: " << shielding << endl;
	cout << "futureShielding: " << futureShielding << endl;
	cout << "moveShieldPastVertical: " << moveShieldPastVertical << endl;
	cout << "moveShieldFutureVertical: " << moveShieldFutureVertical << endl;
	cout << "moveShieldPastHorizontal: " << moveShieldPastHorizontal << endl;
	cout << "moveShieldFutureHorizontal: " << moveShieldFutureHorizontal << endl;
	cout << "moveAttackPastVertical: " << moveAttackPastVertical << endl;
	cout << "moveAttackFutureVertical: " << moveAttackFutureVertical << endl;
	cout << "moveAttackPastHorizontal: " << moveAttackPastHorizontal << endl;
	cout << "moveAttackFutureHorizontal: " << moveAttackFutureHorizontal << endl;
	cout << "attackClip: " << attackClip << endl;
	cout << "rJoystick: " << rJoystick << endl;
	cout << "lBumper: " << lBumper << endl;
	cout << "attackPercent: " << attackPercent << endl;
	cout << "xMove" << xMove << endl;
	cout << "attackID: " << attackID << endl;
	cout << "deltaX: " << deltaX << endl;
	cout << "deltaY: " << deltaY << endl;
	cout << "timeFactor: " << timeFactor << endl;
	cout << "xPress: " << xPress << endl;
	cout << "shieldBashing: " << shieldBashing << endl;
	cout << "futureBashing: " << futureBashing << endl;
	cout << "bashNum: " << bashNum << endl;
	cout << "bashTimer: " << bashTimer << endl;
	cout << "downShielding: " << downShielding << endl;
	cout << "futureDownShielding: " << futureDownShielding << endl;
	cout << "leftTriggerHandler: " << leftTriggerHandler << endl;
	cout << "rightTriggerHandler: " << rightTriggerHandler << endl;
	cout << "airAttack: " << airAttack << endl;
	cout << "futureAirAttack: " << futureAirAttack << endl;
	cout << "airAttackTimer: " << airAttackTimer << endl;
	cout << "futureAirAttackTimer" << futureAirAttackTimer << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;


}
