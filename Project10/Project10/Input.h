#pragma once
#include "Libs.h"
#include "interfaceobj.h"
using namespace sf;
class InputTab :IBaseClass {
private:
	RectangleShape* backgr;
	Text* text_front;
	Color color;
	String* text_string;
	String* title;
public:
	InputTab(int width, int heigth, int pos_x, int pos_y, Color color, RenderTarget*& target, const String& title);
	~InputTab();
	void input(const Uint32& character);
	void draw();
	void clear();
	void deleteLast();
};