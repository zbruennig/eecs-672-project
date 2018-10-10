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
	// 2. update screenbaseX, screenBaseY
	int dx = x - screenbaseX;
	int dy = y - screenbaseY;
	screenbaseX = x;
	screenbaseY = y;

	// 3. if translation, map (dx, dy) to (dxInLDS, dyInLDS) and pass to
	//    ModelView::addToGlobalPan
	// 4. else if rotation, map (dx, dy) to rotation angles and pass to
	//    ModelView::addToGlobalRotationDegrees.

	ModelView::addToGlobalRotationDegrees(dy/3.2, dx/3.2, 0.0);

	// ModelView::addToGlobalPan(dy/40000.0, 0, dx/40000.0); //This one is cool with how my code is set up now


	// 5. do a redraw() (happens automatically at termination of function)
}
