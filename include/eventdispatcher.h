#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <nds.h>
#include "event.h"

#define MAX_NUM_EVENTS 32

class EventDispatcher {
	public:
		Event** events;
		u8 eventArrayPointer;

		EventDispatcher(void);
		int8 addEvent(Event*);
		int8 dispatchEvents(void);
};

#endif
