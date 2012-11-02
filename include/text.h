#ifndef TEXT_H_
#define TEXT_H_

#include <nds.h>
#include "entity.h"
#include "renderable.h"
#include "transformable.h"
#include "sprite.h"

/*r*
 * Represents a text object
 */
class TextRenderable : public Entity, public Renderable, public Transformable { // Once the renderable API is better defined, we'll want to call through it

	private:
		void draw(void);
		const char* mText; // The text contained within this renderable
		Sprite* mSprites; // The array of sprites we'll be maintaining
		int mIndex; // Which renderable am I?
		static int sNextIndex; // The next renderable to be allocated
	public:
		TextRenderable(const char* text, const int left, const int up, const int right, const int down); 
		~TextRenderable(void);
};

#endif
