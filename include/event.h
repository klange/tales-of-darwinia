#ifndef EVENT_H_
#define EVENT_H_

enum EventType {
	UNKNOWN = 0,
	DRAW = 1,
	TRANSFORM = 2,
	TOUCH = 3,
	BUTTON_PRESS = 4,
	FRAME_CHANGE = 5,

	/* implement this later */
	COLLISION = 6
};

typedef struct {
	u16 x;
	u16 y;
} ArgumentsTransform;

typedef struct {
	u16 currentFrameNumber;
} ArgumentsFrameChange;

/* defines structs for different arguments you can have */
typedef struct {
	bool enabled;
	u8 type;
	void (*eventCallback)(void*);
} Event;

#endif