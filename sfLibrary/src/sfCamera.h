#pragma once

#include "ofMain.h"
#include "ofxVectorMath.h"

/**
 * This class is a copy of ofxCamera. It is used so that I can
 * extend that camera class as well as to clarify its interface
 * (make it more consistent with what I'm used).
 */
class sfCamera
{
	public:
		// TODO Ditch these view port methods or move them into a child class.
		/**
		 * Get the width and height of the viewport.
		 */
		ofxVec3f getViewportSize();
		/**
		 * Get the location of the lower left corner of the viewport.
		 */
		ofxVec3f getViewportLowerLeft();
		/**
		 * Get the center position of the viewport.
		 */
		ofxVec3f getViewportCenter();
		/**
		 * Get the location of the left edge of the viewport.
		 */
		float getViewportLeft();
		/**
		 * Get the location of the right edge of the viewport.
		 */
		float getViewportRight();
		/**
		 * Get the location of the top edge of the viewport.
		 */
		float getViewportTop();
		/**
		 * Get the location of the bottom edge of the viewport.
		 */
		float getViewportBottom();

		// THE FOLLOWING ARE TAKEN FROM ofxCamera:
		// -----------------------------------------------
		sfCamera();
		void focalPoint(float x, float y, float z);
		void focalPoint(ofxVec3f _pos);
		void focalPoint(); //reset the position to initial values
		void lerpPosition(float _x, float _y, float _z, float _step); //step should be a value between 0 and 1
		void lerpPosition(ofxVec3f _pos, float _step); //step should be a value between 0 and 1
		void location(float _x, float _y, float _z);
		void location(ofxVec3f _eye);
		void location(); //reset eye psition to the initial values
		void up(float _x, float _y, float _z);
		void up(ofxVec3f _up);
		void up(); //reset up vector to initial values
		void perspective(float _fov, float _aspect, float _zNear, float _zFar);
		void perspective();//reset perspective to initial values
		virtual void place(); //this must go in the draw function!!!!
		void remove(); //Removes the camera, so it returns as if there was no camera
		void moveLocal(float _x, float _y, float _z); //Moves the camera along it's own coordinatesystem
		void moveLocal(ofxVec3f move);
		void moveGlobal(float _x, float _y, float _z); //Moves the camera along the global coordinatesystem
		void moveGlobal(ofxVec3f move);
		/**
		 * @param target The target point around which you wish to rotate. Be sure
		 * to place the camera where you want it before calling orbitAround as rotation
		 * moves the camera using its current position.
		 * @param axis The axis' you wish to rotate around. This should be a vector like
		 * {0, 0, 1}, {0, -1, 0}, {0, 1, 1}, etc.
		 * @param value The number of degrees you wish to rotate with this call. In other
		 * words, if you wish to rotate around an object 10 degrees every frame, use 10
		 * as the value. Do not increment value with each frame (0, 10, 20, 30) unless you
		 * want the rotation to speed up with each frame.
		 */
		void orbitAround(ofxVec3f target, ofxVec3f axis, float value);
		void rotate(ofxVec3f axis, float value);
		ofxVec3f getDir();
		ofxVec3f getFocalPoint();
		ofxVec3f getLocation();
		ofxVec3f getUp();
// -----------------------------------------------

	protected:
		/**
		 * The point that the camera is looking at.
		 */
		ofxVec3f focalPointCoord;
		/**
		 * The location of the camera/eye.
		 */
		ofxVec3f cameraCoord;

		// THE FOLLOWING ARE TAKEN FROM ofxCamera:
		// -----------------------------------------------
		ofxVec3f upVec;
		float	fieldOfView;
		int	w;
		int	h;
		float	aspectRatio;
		float zNear, zFar;
		// -----------------------------------------------

	private:
		/**
		 * The lower left corner of our world viewport.
		 */
		ofxVec3f _viewportLowerLeft;
		/**
		 * The width and height of our world viewport.
		 */
		ofxVec3f _viewportSize;
		/**
		 * The center of the world for this application.
		 */
		ofxVec3f _viewportCenter;
};

