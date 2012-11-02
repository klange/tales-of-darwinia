#ifndef TEXT_H_
#define TEXT_H_

#include <nds.h>
#include "entity.h"
#include "renderable.h"
#include "transformable.h"
#include "textchar.h"

#define MAX_TEXT_SPRITES 64

/**
 * Represents a text object
 */
class TextRenderable : public Entity, public Renderable, public Transformable { // Once the renderable API is better defined, we'll want to call through it

	private:
		void draw(void);
		const char* mText; // The text contained within this renderable
		int mLen; // The length of the text in this buffer
		SpriteData* mSpriteData; // The data used for our font array
		TextChar* mSprites[MAX_TEXT_SPRITES]; // Our fixed array of Sprite pointers
	public:
		TextRenderable(const char* text, int len, int left, int up, int right, int down); 
		~TextRenderable(void);
};

#endif
