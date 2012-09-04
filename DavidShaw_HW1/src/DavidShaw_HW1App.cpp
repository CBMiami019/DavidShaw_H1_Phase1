
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
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void drawSquare(uint8_t* pixels,int x, int y);
	//void DavidShaw_HW1App::drawSquare(uint8_t* pixels,int centerX, int centerY);

private:
	Surface* mySurface_; //The Surface object whose pixel array we will modify
	gl::Texture* myTexture_; //The Texture object that we use to display our Surface 
	uint8_t* dataArray;
	Surface space_Marine;
	
};

	//uint8_t* myPixels;
	
	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; 

void DavidShaw_HW1App::setup()

{
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	myTexture_ = new gl::Texture(*mySurface_);

	space_Marine = (loadImage( loadResource(RES_HAMMER) ));
	//gl::Texture space_Marine(loadImage( loadResource(RES_HAMMER) ));
	dataArray = (*mySurface_).getData();

}

void DavidShaw_HW1App::prepareSettings(Settings* settings) {
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void DavidShaw_HW1App::drawSquare(uint8_t* pixels,int centerX, int centerY) {

	int startX = centerX*3*1024;//(centerX - 25)*3;
	int startY = centerY*3;//(centerY - 25)*3;
	for (int i = startX+startY;i < startX + 150; i+=3) {
		pixels[i] = 255;
		pixels[i + 1] = 255;
		pixels[i + 2] = 0;


	}

}

void DavidShaw_HW1App::mouseDown( MouseEvent event )
{
	if(event.isLeft())
		drawSquare(dataArray,event.getX(), event.getY());
}

void DavidShaw_HW1App::update()
{
	//uint8_t* 
		dataArray = (*mySurface_).getData();
		(*myTexture_).update(*mySurface_,(*mySurface_).getBounds());
		
}

void DavidShaw_HW1App::draw()
{
	//gl::draw(space_Marine);
	//gl::draw(*mySurface_);
	gl::draw(*myTexture_);
	
}

CINDER_APP_BASIC( DavidShaw_HW1App, RendererGl )
