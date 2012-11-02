#include <nds.h>
#include <stdio.h>
#include "text.h"

/**
 * Performs the actual text rendering operation
 */
void TextRenderable::draw(void) {
  // No-op, since console text is persistent
}

/** 
 * Creates a new TextRenderable
 */
TextRenderable::TextRenderable(char* text, //! The text to be rendered 
			       int x, //! The x position of the console 
			       int y, //! The y position of the console 
			       int width, //! The width of the console 
			       int height //! The height of the console 
			       ) {
	mText = text;
	mConsole = consoleDemoInit();
	//consoleInit(mConsole, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
	consoleSetWindow(mConsole, x, y, width, height);

	consoleSelect(mConsole);
	iprintf(mText);
}

/**
 * Destroys a TextRenderable
 */
TextRenderable::~TextRenderable(void) {
  	if (mConsole) delete mConsole;
  	if (mText) delete mText;
}
