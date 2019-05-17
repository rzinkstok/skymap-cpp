// StarMapper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../StarMap/Geometry/Point2D.h"
#include "../StarMap/Tikz/Tikz.h"
#include "../StarMap/Tikz/TikzPicture.h"
#include "../StarMap/Geometry/Shapes.h"

using namespace std;

int top_level_error(const char * const msg) {
	cout << "Application error: " << msg << std::endl;
	return 1;
}

int main(int argc, const char * argv[]) {
	try {
		Tikz t = Tikz();
		t.set_landscape(true);

		TikzPicture p = TikzPicture(Point2D(0, 0), Point2D(90, 60));
		p.set_origin(Point2D(45, 30));
		p.set_boxed(true);

		t.add(p);

		p.draw_line(Line(Point2D(10, 10), Point2D(80, 50)));
		p.dashed_on();
		p.draw_rectangle(Rectangle(Point2D(5, 5), Point2D(85, 55)));
		p.dotted_on();
		p.draw_circle(Circle(Point2D(30, 40), 25));
		p.fill_circle(Circle(Point2D(65, 25), 10));
		p.fill_rectangle(Rectangle(Point2D(100, 140), Point2D(120, 150)));
		p.unbroken();
		{
			TikzClip tc = p.clip(p.get_bounding_box_path());
			p.draw_arc(Arc(Point2D(70, 50), 50, 45, 370));
		}
		p.fill_circle(Circle(Point2D(70, 50), 1));

		t.finish();
		t.render();
	}
	catch (...) {
		return top_level_error("Unexpected C++ exception.");
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
