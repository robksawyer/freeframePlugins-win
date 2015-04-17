#include "ofMain.h"
#include "sfColorRingsApp.h"
#include "ofAppGlutWindow.h"
#include "ofxFFGLPlugin.h"

#if !defined __SF_RUN_AS_STANDALONE_APPLICATION__
// -------------------------------------------
// This code will be used if compiling the application
// as a FreeFrame plugin.
// -------------------------------------------

// This defines the creation function for our plugin
// parameters:
// appType:	 the class name of your App
// minInputs: minimum number of inputs ( textures )
// maxInputs: maximum number of inputs ( textures )
DEFINE_FFGL_PLUGIN( sfColorRingsApp, 0, 0 );

// FFGL Plugin Info Structure
//	!!! Do not change fields marked with *
static CFFGLPluginInfo PluginInfo
(
	// * Create method
	createPluginInstance,
	// Plugin unique ID (4 chars)
	"SF01",
	// Plugin name (16 chars)
	"sfColorRings",
	// * API major version number
	1,
	// * API minor version number
	500,
	// Plugin major version number
	0,
	// Plugin minor version number
	5,
	// Plugin type FF_SOURCE or FF_EFFECT ( filters )
	FF_SOURCE,
	// Plugin description
	"a Soul-Fresh plugin",
	// About
	"by Marc Wren, www.soul-fresh.com, sffreeframe.sourceforge.net",
	0,
	NULL
);

#else
// -------------------------------------------
// This code will be used if compiling the application
// as a standalone application.
// -------------------------------------------
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 640, 480, OF_WINDOW);

	sfApp* vApp = new sfColorRingsApp();
	vApp->runAsApplication( true );
	ofRunApp( vApp );

}

#endif
