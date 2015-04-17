/*
 * sfIterationTracker.h
 * Tracks values in a loop so that you can determine when loop events occur.
 * For example, it can be used in a for loop to loop through an array starting
 * at an arbitray index.
 *
 *  Created on: Nov 30, 2010
 *      Author: marc.wren
 */

#ifndef SFITERATIONTRACKER_H_
#define SFITERATIONTRACKER_H_

class sfLoopTracker
{
	public:
		sfLoopTracker();
		sfLoopTracker( int numberOfIterations, int currentIteration );
		/**
		 * Set the index that is considered the loop point.
		 */
		void setStartIteration( int startIteration );
		/**
		 * Update the tracker (ie. increment the current iteration number).
		 * @return The current index in the loop (ie. same as getCurrentIndex).
		 */
		int update();
		/**
		 * Set the number of iterations within a loop.
		 */
		void setLoopSize( int numberOfIterations );
		int getLoopSize();
		/**
		 * Set the current iteration we are on.
		 */
		void setCurrentIndex( int currentIteration );
		int getCurrentIndex();
		/**
		 * Get the current iteration (ie number of updates called) that the loop tracker is on.
		 */
		int getCurrentIteration();
		/**
		 * Returns how many loops have occured.
		 */
		int getCurrentLoop();
		/**
		 * Set the loop that this tracker has reached.
		 */
		void setCurrentLoop( unsigned int loop );
		/**
		 * True = We have iterated through at least one complete loop.
		 * Use this in combination with hasLooped to know if we are begining
		 * a new loop and at least one loop has occured.
		 */
		bool hasLooped();
		/**
		 * True = This is the begining of a new iteration loop. Use this if you want
		 * to know when loops occur INCLUDING the first loop. IE. if the loop start
		 * index is 0, and this is the first iteration, and the current index is 0, then this
		 * method will return true.
		 */
		bool isLoopStart();
		/**
		 * True = The iteration tracker has reached index 0.
		 */
		bool isMinIndex();
		/**
		 * True = The iteration tracker has reached the max iteration (ie. the next iteration
		 * will be index 0).
		 */
		bool isMaxIndex();
		/**
		 * True = Decrement the iterater with each step (ie. loop in the order 0, end, end - 1, ... 0, end ).
		 */
		void iterateBackwards( bool backwards );
	private:
		/**
		 * True = Increment with each iteration (ie. loop in the order 0, 1, 2 ... 0, 1, 2).
		 */
		bool _forwards;
		/**
		 * The current iteration number (ie. the total number of iterations/updates that have occured).
		 */
		int _iterationNumber;
		/**
		 * The number of iterations before a loop has occurred.
		 */
		int _loopSize;
		/**
		 * The current index in the loop.
		 */
		int _currentIndex;
		/**
		 * True = At least one loop has occured.
		 */
		bool _hasLooped;
		/**
		 * The number of loops that have occured.
		 */
		int _numberOfLoops;
		/**
		 * The iteration at which the tracker was started. This will be used to determine
		 * if a full loop has occured.
		 */
		int _startIndex;
};

#endif /* SFITERATIONTRACKER_H_ */
