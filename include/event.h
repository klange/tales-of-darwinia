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

/* defines structs for different arguments you can have */
typedef struct {
	bool enabled;
	u8 type;
	void (*eventCallback)(void*);
} Event;

#endif