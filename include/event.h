#ifndef EVENT_H_
#define EVENT_H_

enum EventType {
	UNKNOWN = 0,
	BUTTON_PRESS = 3,
	BUTTON_HOLD = 4,
	BUTTON_RELEASE = 5,
	FRAME_CHANGE = 6,

	/* implement this later */
	COLLISION = 7
};

/** 
 * Defines an event to be fired upon next invocation of EventDispatcher.dispatchEvents()
 * enabled - whether this event is enabled, if not, skip over it
 * type - the type of event to fire, see the enum above
 * eventCallback - the callback we want to call when an event is detected
 *
 * TODO: Make this a class that sets defaults for enabled and type?
 */
typedef struct {
	bool enabled;
	u8 type;
	void (*eventCallback)(void*);
} Event;

#endif