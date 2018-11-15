// ExtendedController.c++

#include "ExtendedController.h"
#include "ModelView.h"

ExtendedController::ExtendedController(const std::string& name, int rcFlags):
	GLFWController(name, rcFlags)
{
}

																		// 1. Get a pixel (dx, dy)
void ExtendedController::handleMouseMotion(int x, int y)
{
	// 2. update screenBaseX, screenBaseY
	float dx = x - screenBaseX;
	float dy = y - screenBaseY;
	screenBaseX = x;
	screenBaseY = y;

	// 3. if translation, map (dx, dy) to (dxInLDS, dyInLDS) and pass to
	//    ModelView::addToGlobalPan
	if(mouseMotionIsTranslate){
		int width, height;
		glfwGetWindowSize(theWindow, &width, &height);
		ModelView::addToGlobalPan(dx*2/(width), -dy*2/(height), 0);
	}

	// 4. else if rotation, map (dx, dy) to rotation angles and pass to
	//    ModelView::addToGlobalRotationDegrees.
	else if(mouseMotionIsRotate){
		ModelView::addToGlobalRotationDegrees(dy/3.2, dx/3.2, 0.0);
	}


	// 5. do a redraw() (happens automatically at termination of function)
	redraw();
}
