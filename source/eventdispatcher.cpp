#include <nds.h>
#include "eventdispatcher.h"
#include "event.h"

EventDispatcher::EventDispatcher(void) {
	events = (Event**)malloc(MAX_NUM_EVENTS * sizeof(Event*));
}

int8 EventDispatcher::addEvent(Event *event) {
	if (eventArrayPointer > MAX_NUM_EVENTS) {
		return -1;
	}
	events[eventArrayPointer] = event;
	eventArrayPointer++;
	return eventArrayPointer;
}

int8 EventDispatcher::dispatchEvents(void) {
	Event* currentEvent;
	for (int lcv = 0; lcv < eventArrayPointer; lcv++) {
		currentEvent = events[lcv];

		if (currentEvent->enabled) {
			void* args = NULL;

			/* Build the args here */
			switch (currentEvent->type) {
				case DRAW:
					break;
				case TRANSFORM:
					break;
				case TOUCH:
					break;
				case BUTTON_PRESS:
					break;
				case FRAME_CHANGE:
					break;
			}

			/* Call that shit */
			currentEvent->eventCallback(args);
		}

		/* Cleanup the event */
		delete currentEvent;
	}
	
	eventArrayPointer = 0;
}

