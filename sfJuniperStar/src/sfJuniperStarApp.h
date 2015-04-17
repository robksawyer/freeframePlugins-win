#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxFFGLApp.h"
#include "sfCamera.h"
#include "sfJuniperStar.h"
#include "sfApp.h"
#include "sfResolumeBeatEventTracker.h"
#include "sfLoopTracker.h"

class sfJuniperStarApp : public sfApp
{
	public:
		sfJuniperStarApp();
		void setup();
		void draw();

		void preIterate();
		void iterate();
		void postIterate();

		/**
		 * Move all stars into a new, random position on screen.
		 */
		void moveStars();
		/**
		 * Updates the stars to reflect that a beat occured.
		 */
		void beatEvent();

	private:
		/**
		 * The object used to track beat events from resolume.
		 */
		sfResolumeBeatEventTracker _beatEventTracker;
		/**
		 * The object tracking the current beat.
		 */
		sfLoopTracker _beat;
		/**
		 * The object used to track move events from resolume.
		 */
		sfResolumeBeatEventTracker _moveEventTracker;
		/**
		 * The amount of time it takes for stars to move into
		 * a new position once all points on the star have been
		 * highlighted.
		 */
		float _starMoveDuration;
		/**
		 * The max distance that stars can move during move events.
		 */
		float _starMoveDistance;
		/**
		 * The number of points on each star. This is a float so it can be set by the host application.
		 */
		float _numberOfPoints;
		/**
		 * The offset of points from their center on the Y axis.
		 */
		float _pointYOffset;
		/**
		 * The offset of points from their center on the X axis.
		 */
		float _pointXOffset;
		/**
		 * The height of the points in a star.
		 */
		float _pointHeight;
		/**
		 * The width of the points in a star.
		 */
		float _pointWidth;
		/**
		 * The rotation of star points around the point's center.
		 */
		float _pointRotation;
		/**
		 * True = sort the points in a star so the active point is in the front.
		 */
		bool _sortPoints;
		/**
		 * The current beat event. There are only as many beats as there
		 * are points in a star.
		 */
		float _currentBeat;
		/**
		 * Determines the amount of spacing between star points.
		 * This value is multiplied by the amount of rotation
		 * to determine the final spacing between points of a
		 * star.
		 */
		float _starDepthFactor;
		/**
		 * The amount that the camera should be rotated.
		 */
		float _rotation;
		/**
		 * The camera viewing our scene.
		 */
		sfCamera camera;
		/**
		 * The location of the camera on the z axis.
		 */
		float _zoom;
		/**
		 * The height of the application.
		 */
		int _height;
		/**
		 * The width of the application.
		 */
		int _width;
		/**
		 * The number of stars to display. This is a float so it can be set by the host as such.
		 */
		float _numberOfStars;
		/**
		 * The list of stars being animated.
		 */
		vector<sfJuniperStar*> _stars;
		/**
		 * Create a new star and add it to the list of stars.
		 */
		void _createStar();
		/**
		 * Set the number of stars to display.
		 * @param number The number of stars to display.
		 */
		void _setNumberOfStars( unsigned int number );
		/**
		 * Add stars to display
		 * @param number The number of stars to add.
		 */
		void _addStars( unsigned int number );
		/**
		 * Hide stars we want to get rid of.
		 * @param number The number of stars to remove.
		 */
		void _hideStars( unsigned int number );
		/**
		 * Remove hidden stars from the display.
		 */
		void _removeOldStars();
		/**
		 * Move the specified star to a new location.
		 * @param star The star to move.
		 */
		void _moveStar( sfJuniperStar* star );
		/**
		 * Update the given star with the current star properties.
		 * @param star The star to update.
		 */
		void _updateStar( sfJuniperStar* star );
		/**
		 * Compare two stars and return whether star 1 is further away
		 * than star 2.
		 */
		struct StarLocationCompare
		{
			bool operator()( sfJuniperStar* vStar1, sfJuniperStar* vStar2 )
			{
				ofxVec3f vLoc1 = vStar1->getLocation();
				ofxVec3f vLoc2 = vStar2->getLocation();
				return ( vLoc1.z < vLoc2.z );
			};
		} _compareStarLocations;
//		bool _compareStarLocations( JuniperStar* star1, JuniperStar* star2 );
};

#endif
