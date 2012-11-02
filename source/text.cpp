#include <nds.h>
#include <stdio.h>
#include "entitymanager.h"
#include "text.h"
#include "man.h"
#include "inconsolata.h"
#include "enemyentity.h"

extern EntityManager gEntityManager;

/**
 * Performs the actual text rendering operation
 */
void TextRenderable::draw(void) {
}

/** 
 * Creates a new TextRenderable
 */
TextRenderable::TextRenderable(const char* text, //! The text to be rendered
			       int len, //! The length of mText
			       int x, //! The x position of the console 
			       int y, //! The y position of the console 
			       int width, //! The width of the console 
			       int height //! The height of the console 
			       ) {
  	mText = text;
	mSpriteData = new SpriteData(SpriteSize_32x32, SpriteColorFormat_256Color, (u8*)manTiles, 3);
	for (int i = 0; i < len; ++i) {
	  mSprites[i] = new TextChar(mSpriteData);
	  mSprites[i]->Init();
	  mSprites[i]->size = Vector3<s16>(16,16,0);
	  mSprites[i]->setPosition(Vector3<s16>(x+1,y,1));
	  mSprites[i]->setFrame(4);
	}
}

/** 
 * Destroys a TextRenderable
 */
TextRenderable::~TextRenderable(void) {
  if (mText) delete mText;
  if (mLen > 0) {
    for (int i = 0; i < mLen; ++i) {
      delete mSprites[i];
    }
  }
  if (mSpriteData) delete mSpriteData;
}
