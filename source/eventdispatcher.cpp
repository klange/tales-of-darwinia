#include <nds.h>
#include "eventdispatcher.h"
#include "event.h"
#include <stdio.h>

EventDispatcher::EventDispatcher(void) {
	events = (Event**)malloc(MAX_NUM_EVENTS * sizeof(Event*));
}

bool EventDispatcher::isFull(void) {
	return getNext(endPointer) == startPointer;
}

bool EventDispatcher::isEmpty(void) {
	return !isFull();
}

u8 EventDispatcher::getNext(u8 cur) {
	cur++;
	if (cur > MAX_NUM_EVENTS) {
		cur = 0;
	}
	return cur;
}

int8 EventDispatcher::addEvent(Event *event) {
	if (isFull()) {
		return -1;
	}
	events[endPointer] = event;
	endPointer = getNext(endPointer);
	return endPointer;
}

void EventDispatcher::dispatchEvents(void) {
	Event* currentEvent;
	uint32 downKeys = keysDown();
	uint32 heldKeys = keysHeld();
	uint32 upKeys = keysUp();

	/* This might be an infinite loop if there exists two events that fire each other */
	for (; startPointer != endPointer; startPointer = getNext(startPointer)) {
		currentEvent = events[startPointer];

		if (currentEvent->enabled) {
			void* args = NULL;
			bool callFunc = false;

			/* Build the args here */
			switch (currentEvent->type) {
				case BUTTON_PRESS:
					if (downKeys != 0) {
						callFunc = true;
					}
					break;
				case BUTTON_HOLD:
					if (heldKeys != 0) {
						callFunc = true;
					}
					break;
				case BUTTON_RELEASE:
					if (upKeys != 0) {
						callFunc = true;
					}
					break;
				case FRAME_CHANGE:
					callFunc = true;
					break;
			}

			if (callFunc == true) {
				/* Call that shit */
				currentEvent->eventCallback(args);
			}
		}
	}
}
