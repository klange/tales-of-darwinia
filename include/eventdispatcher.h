#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <nds.h>
#include "event.h"

#define MAX_NUM_EVENTS 32

class EventDispatcher {
	private:
		Event** events;
		u8 startPointer;
		u8 endPointer;
		
	public:
		EventDispatcher(void);
		int8 addEvent(Event*);
		int8 dispatchEvents(void);
		bool isEmpty(void);
		bool isFull(void);
		u8 getNext(u8);
};

#endif
