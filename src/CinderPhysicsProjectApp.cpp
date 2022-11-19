#include <time.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/CameraUi.h"
#include "cinder/TriMesh.h"
#include "cinder/Rand.h"
#include "cinder/Timer.h"
#include "cinder/Log.h"

#include "Includes/Scene.h"

using namespace ci;
using namespace ci::app;

class CinderPhysicsProjectApp : public App {

public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

public:
	Scene m_Scene;

};

void CinderPhysicsProjectApp::setup()
{
	m_Scene.SetupScene();
	WindowRef windowRef = getWindow();
	
	windowRef->setSize(1920, 1080);
	windowRef->setPos(50, 50);
}

void CinderPhysicsProjectApp::mouseDown( MouseEvent event )
{
}

void CinderPhysicsProjectApp::update()
{
	m_Scene.UpdateScene();
}

void CinderPhysicsProjectApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );

	m_Scene.DrawScene();
}

CINDER_APP( CinderPhysicsProjectApp, RendererGl )
