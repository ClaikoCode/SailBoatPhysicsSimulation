#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderPhysicsProjectApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void CinderPhysicsProjectApp::setup()
{
}

void CinderPhysicsProjectApp::mouseDown( MouseEvent event )
{
}

void CinderPhysicsProjectApp::update()
{
}

void CinderPhysicsProjectApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( CinderPhysicsProjectApp, RendererGl )
