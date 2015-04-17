/*
 * sfApp.h
 *
 *  Created on: Nov 24, 2010
 *      Author: marc.wren
 */

#ifndef SFAPP_H_
#define SFAPP_H_

#include "ofxFFGLApp.h"
#include "sfResolumeBeatEventTracker.h"

class sfApp : public ofFFGLApp
{

	public:
		sfApp();
		void setup();
		void draw();

		/**
		 * The update method should not be defined in subclasses
		 * of sfApp. Instead use the iterate method. This allows
		 * the preIterate and postIterate hooks to be called.
		 */
		void update();
		/**
		 * A hook intended to be used to setup test/application
		 * scenarios when your project is run as an open frameworks
		 * application. This method is called before the iterate method
		 * and is only called if the project is running as a standalone
		 * application.
		 */
		virtual void preIterate();
		/**
		 * This is meant to replace the update function in subclasses
		 * of sfApp. Place the code that would normally go in your
		 * update method in this method instead. You can then
		 * place any code that needs to be run when your project
		 * is run as an application in the pre and post iterate methods.
		 */
		virtual void iterate();
		/**
		 * A hook intended to be used to setup test/application
		 * scenarios when your project is run as an open frameworks
		 * application. This method is called after the iterate method
		 * and the project is running as a standalone application.
		 */
		virtual void postIterate();
		/**
		 * Can be used to specify whether or not the project is being run
		 * as a stand alone application or as a FreeFrame plugin. You should
		 * set this in your main application file (ie. main.cpp; not testApp.cpp).
		 * You should not set it anywhere else.
		 * @param isApplication True = The project is running as
		 * a standalone application.
		 */
		void runAsApplication( bool isApplication );
		/**
		 * Can be used to determine if the project is being run as a
		 * stand alone application.
		 * @return True = The project is running as an application.
		 */
		bool isApplication();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		/**
		 * Add a host parameter that can be used to simulate beat events.
		 * @param name The name to display for this parameter in the host application.
		 * @param tracker A pointer to the object used to track beat events.
		 */
		void addBeatEventParameter( const char * name, sfResolumeBeatEventTracker * tracker );

	private:
		/**
		 * True = The project is running as a standalone application and NOT as
		 * a plugin.
		 */
		bool _isRunningAsApplication;
};

#endif /* SFAPP_H_ */
