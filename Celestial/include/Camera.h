#ifndef Camera_h
#define Camera_h

#include <string>

#include <SDL3/SDL.h>
#include "utils/Vector2.h"

//Let us not delve into 3d graphics by hand, at least not now
 
//2d orthographic projection camera, it completely ignores the z axis (and does not handle depth)

class Camera {
private:
	bool fullscreen = true;

	Vector2<int> origin; //x, y position in the virtual space
	Vector2<int> size; //width, height of the camera view

	SDL_FRect bounds; //bounds of the camera in the virtual space
	SDL_FRect dest; //destination rectangle for rendering

public:
	Camera() : origin(0, 0), size(1280, 720) {}
	Camera(int x, int y, int w, int h) : origin(x, y), size(w, h) {}
	~Camera() {}

	Vector2<int> getorigin() const { return origin; }
	Vector2<int> getSize() const { return size; }

	void setorigin(int x, int y) {
		origin.set(x, y);
		updateBounds();
	}
	void setSize(int w, int h) {
		size.set(w, h);
		updateBounds();
	}
	void setDest(SDL_FRect idest) { dest = idest; }

	void setAspectRatio(double aspectRatio, std::string anchor) {
		//aspect ratio is width / height
		//anchor is the side of the camera that will be fixed. "width" for width or anything else for height
		if (anchor == "width") {
			size.setY(size.getX() / aspectRatio);
		}
		else {
			size.setX(size.getY() * aspectRatio);
		}
		updateBounds();
	}

	void updateBounds() {
		bounds.x = origin.getX() - size.getX() / 2;
		bounds.y = origin.getY() - size.getY() / 2;
		bounds.w = size.getX();
		bounds.h = size.getY();
	}

	void onWindowResized(int width, int height) {
		if (fullscreen) {
			dest.x = 0;
			dest.y = 0;
			dest.w = width;
			dest.h = height;
		}
	}

	SDL_FRect getBounds() const { return bounds; }
	SDL_FRect getDest() const { return dest; }

	bool isFullscreen() const { return fullscreen; }
};

#endif //Camera_h