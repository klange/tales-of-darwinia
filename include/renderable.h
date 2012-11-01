#ifndef RENDERABLE_H_
#define RENDERABLE_H_

/**
 * An interface to define a renderable object that is drawn to the
 * Nintendo DS screen(s).
 * TODO: where to draw to? how to draw... etc.
 */
class Renderable {
	private:
		virtual void draw(void) = 0;

	public:
		bool hidden;
		void doRender(void*);
};
#endif
