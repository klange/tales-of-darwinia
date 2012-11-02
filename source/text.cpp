#include <nds.h>
#include <stdio.h>
#include "text.h"

/**
 * Performs the actual text rendering operation
 */
void TextRenderable::draw(void) {
  // Automate the generation of sprites from our text
  
}

/** 
 * Creates a new TextRenderable
 */
TextRenderable::TextRenderable(const char* text, //! The text to be rendered 
			       int x, //! The x position of the console 
			       int y, //! The y position of the console 
			       int width, //! The width of the console 
			       int height //! The height of the console 
			       ) {
  	mText = text;
	mSprites = NULL; // Sprite[sizeof(text)];
}

/** 
 * Destroys a TextRenderable
 */
TextRenderable::~TextRenderable(void) {
  if (mText) delete mText;
}
