//David Shaw
//Dr. Brinkman's CSE 274 Data Structures Class

/********CONTROLS FOR CERTAIN FUNCTIONS********
TINT: t
BLUR: b
DRAW SQUARE: left click on the surface
/******************************************/


#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class DavidShaw_HW1App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void drawSquare(uint8_t* pixels,int x, int y);
	void blur(uint8_t* pixels);
	void tint(uint8_t* pixels);
	
private:
	Surface* mySurface_; //The Surface object whose pixel array we will modify 
	uint8_t* dataArray;
	uint8_t* copy;
	Surface space_Marine;
	int gradCount;
	int redCount;

	//Boolean added by Carter 
	bool redDone;
	
};
	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; 

void DavidShaw_HW1App::setup()
{
	//Setting the boolean to false here (Carter):
	redDone = false;


	mySurface_ = new Surface(kTextureSize,kTextureSize,false);

	gradCount = 0;
	redCount = 255;

	space_Marine = (loadImage( loadResource(RES_HAMMER) ));
	dataArray = (*mySurface_).getData();
	copy = (*mySurface_).getData();
	uint8_t* sm = space_Marine.getData();
	for (int i = 0; i < 1024*1024*3; i++) {
		dataArray[i] = sm[i];
		copy[i] = dataArray[i];
	}
}

void DavidShaw_HW1App::prepareSettings(Settings* settings) {
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	//(*settings).setWindowSize(kTextureSize,kTextureSize);
	(*settings).setResizable(false);
}

//Attempt at doing the drawSquare method part of the assignement, couldn't
//figure out how to do the vertical lines.
void DavidShaw_HW1App::drawSquare(uint8_t* pixels,int posX, int posY) {

	int startX = posX*3;
	int startY = posY*3*1024;
	for (int i = startX+startY;i < (startX + startY+ 150); i+=3) {
		pixels[i] = 255;
		pixels[i + 1] = 255;
		pixels[i + 2] = 0;

		pixels[i+150*1024] = 255;
		pixels[i+150*1024 + 1] = 255;
		pixels[i+150*1024 + 2] = 0;

	}

}

void DavidShaw_HW1App::blur(uint8_t* pixels) {
	//Not a pretty method of doing it,  but the plan
	//is to average the red ints of all the neighboring pixels, the blue
	//and the green. The copy is made before this method so it can be used
	//for the actual surface when that one changes. For now it was coded to 
	//only blur everything but a 1 pixel thick frame to avoid boundary math for now.

	//Satisfies PART B.1 of the homework1
	//PRESS B ON THE KEYBOARD TO ACTIVATE BLUR

	for(int i = 1024*3 + 3; i < 1024*1023*3 - 3; i++) {
		pixels[i] = (copy[i] + copy[i+3] + copy[i+6] + 
					 copy[i+1024*3] + copy[i+1024*3 + 3] + copy[i+1024*3 + 6] +
					 copy[i+1024*6] + copy[i+1024*6 + 3] + copy[i+1024*6 + 6])/9;
}
}

//Fufills PART A.6 of homework 1
//HIT THE T KEY TO APPLY TINT
void DavidShaw_HW1App::tint(uint8_t* pixels) {
	
	//For every blue input of a pixel, we add 85 to it, which is 1/3 of the full value of 255. anything higher than 170 we just make it
	//full blue.
	for(int i = 0; i < 1024*1024*3; i+=3) {
		if(pixels[i+2] >= 170) {
			pixels[i+2] = 255;
		}else
			pixels[i + 2] = pixels[i+2] + 85;
	}

}

void DavidShaw_HW1App::mouseDown( MouseEvent event )
{
	if(event.isLeft())
		drawSquare(dataArray,event.getX(), event.getY());
}

void DavidShaw_HW1App::keyDown(KeyEvent event) {
	if(event.getCode() == event.KEY_b)
		blur(dataArray);	
	
	else if(event.getCode() == event.KEY_t)
		tint(dataArray);
}

void DavidShaw_HW1App::update()
{
	//A neater way would be to implement this in a method, and have it called rather than the whole code in the update method. Anyway, the 
	//goal of this is to slowly change from red to black at the top row and then continue down, when full black is reached it starts
	//from red again, the part where it starts over was not made on purpose.
	//Satisfies PART A.4 of the homework 1


	//Comment from Carter:
	//If you want it to stop after one iteration, couldn't you hold a boolean inside it?
	//I'll add one inside an if statement and see it if works for you
	gradCount++;
	redCount--;

	if (redDone == false){
		for(int i = gradCount*3*1024; i < (gradCount+1)*1024*3;i+=3) {
		dataArray[i] = redCount;
		dataArray[i + 1] = 0;
		dataArray[i + 2] = 0;
		}
	}

	//By the way, I commented this out and I don't know what it does
	//if(gradCount > 1024*512*3){
		//gradCount = 0;
	//}
	//From Carter:
	if (redCount == 1)
		redDone = true;

}

void DavidShaw_HW1App::draw()
{
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( DavidShaw_HW1App, RendererGl )