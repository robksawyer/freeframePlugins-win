/*
 * sfResolumeBeatEventTracker.h
 *
 *  Created on: Nov 24, 2010
 *      Author: marc.wren
 */

#ifndef SFRESOLUMEBEATEVENTTRACKER_H_
#define SFRESOLUMEBEATEVENTTRACKER_H_

class sfResolumeBeatEventTracker
{
	public:
		sfResolumeBeatEventTracker();
		/**
		 * Get the address of the variable used to track beat events.
		 */
		float* getParameterAddress();
		/**
		 * Get the maximum value that the beat parameter can be.
		 */
		float getMaxChangeValue();
		/**
		 * Set the minimum amount that the beat parameter must change in order
		 * for the change to trigger a beat event.
		 */
		void setThreshhold( float threshhold );
		/**
		 * True = We are currently in a beat event.
		 */
		bool isBeatEvent();
		/**
		 * Get the strength of the current beat.
		 */
		float getBeatStrength();
		/**
		 * Track the current state of the beat parameter.
		 * IMPORTANT: You will need to call isBeatEvent before
		 * calling update otherwise isBeatEvent will always return false.
		 */
		void update();
		/**
		 * True = The application is running as a standalone program (not from within a host
		 * application). As a result, beat events will be tracked based on frame number.
		 */
		void setStandalone( bool isStandalone );
		/**
		 * The number of frames between beat events (used if in standalone mode).
		 */
		void setFramesPerBeat( int framesPerSecond );
	private:
		/**
		 * The previous value of the beat parameter.
		 */
		float _lastBeatValue;
		/**
		 * The current value of the beat slider.
		 */
		float _beatTracker;
		/**
		 * The minimum amount by which the beat parameter must change
		 * before it is considered a beat event.
		 */
		float _beatThreshhold;
		/**
		 * The maximum value of the beat tracker.
		 */
		float _maxBeatChange;
		/**
		 * True = The application is running as a standalone program and not from within a host.
		 */
		bool _isStandalone;
		/**
		 * If we are in standalone app mode, the frame rate will be used to determine when beat events occur.
		 */
		int _framesPerBeat;
};

#endif /* SFRESOLUMEBEATEVENTTRACKER_H_ */
