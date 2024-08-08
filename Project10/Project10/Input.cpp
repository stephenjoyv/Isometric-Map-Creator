#include "Input.h"

InputTab::InputTab(int width, int heigth, int pos_ex, int pos_ey, Color ecolor, RenderTarget*&target, const String& etitle)
{
	title = nullptr;
	if (etitle.getSize() != 0) title = new String{ etitle };

	size_x = width; size_y = heigth;
	pos_x = pos_ex; pos_y = pos_ey;
	ObjTar = target;
	color = ecolor;



	backgr = std::make_unique<RectangleShape>();
	backgr->setSize(Vector2f(size_x, size_y*11/8));
	backgr->setFillColor(color);
	backgr->setPosition(pos_x, pos_y);

	text_string = new String{"Dwad"};

	text_front = std::make_unique<Text>();
	if (color.r + color.g + color.b <= 305) text_front->setFillColor(Color::White);
	else text_front->setFillColor(Color::Black);
	text_front->setCharacterSize(size_y*0.5);
	text_front->setPosition(pos_x, pos_y);
	text_front->setFont(*Singleton::instance().getGlobalFont());
	if (title != nullptr) text_front->setString(*title +'\n' + *text_string);
	else text_front->setString(*text_string);
	

	/*if (color.r + color.g + color.b <= 305) text_front.setFillColor(Color::White);
	else text_front.setFillColor(Color::Black);
	text_front.setCharacterSize(size_y);
	text_front.setPosition(pos_x, pos_y);
	text_front.setFont(*font_global);
	text_front.setString(*text_string);*/

}
InputTab::~InputTab()
{
}
void InputTab::input(const Uint32& character)
{
	text_string->insert(text_string->getSize(), String{character});
	std::cout << "CHARACTER" << character << '\n';
	//Uint32 m = 5;
	//std::basic_string<Uint32> m{140,225,226};
	//(Uint32)'a';
	//m.insert(m.size(),1,character);
	//m.append(m.size(), character);
	//text_front->setString(*text_string);
	/*std::basic_string<Uint32>* tm = new std::basic_string<Uint32>[1];
	tm[0] = character;
	
	text_front->setString(tm[0]);*/
	//std::cout << (float)character  << '\n';
	//m.clear();
	/*delete text_front;
	text_front = new Text;
	if (color.r + color.g + color.b <= 305) text_front->setFillColor(Color::White);
	else text_front->setFillColor(Color::Black);
	text_front->setCharacterSize(size_y);
	text_front->setPosition(pos_x, pos_y);
	text_front->setFont(*font_global);
	text_front->setString(*text_string);*/

	if (title != nullptr) text_front->setString(*title + String{ '\n' } + *text_string);
	else text_front->setString(*text_string);

}

void InputTab::draw()
{
	ObjTar->draw(*backgr);
	ObjTar->draw(*text_front);
	
}

void InputTab::clear()
{
	delete text_string;
	text_string = new String{ "" };
	if (title != nullptr) text_front->setString(*title + String{ '\n' } + *text_string);
	else text_front->setString(*text_string);
}

void InputTab::deleteLast()
{
	//text_string->erase(text_string->getSize()-1);
	std::wstring  temp_str = (text_string->toWideString());
	if(temp_str.size()!=0)temp_str.erase(temp_str.size() - 1,1);
	//temp_str.end() -= 1;
	/*std::wcout << "str1  " << temp_str << " size1 = " << temp_str.size()<< '\n';
	String* tms = new String{temp_str};
	std::wcout << "str2 = " << tms->toWideString() << " size2 = " << tms->getSize()<<'\n';*/


	delete text_string;
	text_string = new String{temp_str};
	
	//temp_str
	//std::cout << "tx size = " << text_string->getSize() << '\n';
	if (title != nullptr) text_front->setString(*title + String{ '\n' } + *text_string);
	else text_front->setString(*text_string);
}



