#include "Menu.h"
#include <iostream>

/* 
This is a 3D rendering program created for my unit Mathematics for Computer Graphics.
It utilizes the MCG GFX Framework.

All colors and shape vertices are example values, 
as the point of this program is to showcase the algorithms.
*/

int main(int argc, char *argv[])
{
	Menu* menu = new Menu;
	if (menu == nullptr)
	{
		std::cout << "Error initializing menu object";
	}
	else
		menu->Run();
	delete menu;
	return 0;
}

/*References:
[1]https://csustan.csustan.edu/~tom/Lecture-Notes/Graphics/Bresenham-Line/Bresenham-Line.pdf
[2]http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html#algo3
[3]https://wiki.planetchili.net/index.php/3D_Fundamentals_Tutorial_5
[4]https://learnopengl.com/Lighting/Basic-Lighting
[5]https://math.la.asu.edu/~surgent/mat272/dotcross.pdf
[6]https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
[7]https://www.slideshare.net/tahersb/bresenham-circle
[8]https://stackoverflow.com/questions/13488957/interpolate-from-one-color-to-another
[9]https://en.wikipedia.org/wiki/Unit_circle
*/
