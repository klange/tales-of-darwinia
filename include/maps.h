#ifndef MAPS_H_
#define MAPS_H_

#include <nds.h>

/**
 * A class that deals with the loading and unloading of viewable map
 * area to the hardware
 */
class MapEngine {
	private:
		/**
		 * Gets the next index of this circular buffer
		 */
		u8 dummy(u8);

	public:
		MapEngine(void);
};

#endif
