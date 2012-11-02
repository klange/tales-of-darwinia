#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <nds.h>
#include "event.h"

#define MAX_NUM_EVENTS 128

/**
 * A class that will dispatch events based on events sensed by the NDS hardware
 * Dispatch should be called at the end of the game loop. All events are performed in fifo order
 */
class EventDispatcher {
	private:
		/**
		 * A circular buffer of events. Events may fire events.
		 */
		Event** events;

		/**
		 * Start of the circular buffer
		 */
		u8 startPointer;

		/**
		 * End of the circular buffer
		 */
		u8 endPointer;

		/**
		 * Gets the next index of this circular buffer
		 */
		u8 getNext(u8);
	public:
		void Init();

		/**
		 * Adds an event to the circular event buffer
		 *
		 * Returns -1 if the event was added successfully
		 */
		int8 addEvent(Event*);

		/**
		 * Called on the end of the game loop. Parses the Event buffer and performs the
		 * event logic for each Event
		 *
		 */
		void dispatchEvents(void);

		/**
		 * Is the queue of Events empty?
		 */
		bool isEmpty(void);

		/**
		 * Is the queue of events full?
		 */
		bool isFull(void);
};

// Singleton
extern EventDispatcher gEventDispatcher;

#endif
