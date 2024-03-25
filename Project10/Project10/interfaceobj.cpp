#include "interfaceobj.h"


IBaseClass::~IBaseClass() { std::cout << "Destructor\n"; }


void globalDraw() {
	for (auto c : pool_button) {
		c.get()->draw();
	}
}

void buttonWork()
{
	for (size_t i = 0; i < pool_button.size(); i++)
	{
		pool_button[i].get()->isActive();
	}
}

bool Clicable::Click() {
	RenderWindow* temp = pool_window[0].get();

	bool tmp = Mouse::isButtonPressed(Mouse::Left) && (mouse->getPosition(*temp).y >= pos_y) &&
		(mouse->getPosition(*temp).y <= pos_y + size_y) && (mouse->getPosition(*temp).x >= pos_x) && (mouse->getPosition(*temp).x <= pos_x + size_x);
	return tmp;
}


//Определение Button
Button::Button(int size_x, int size_y, int pos_x, int pos_y,int frames,char* text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color) {
	this->size_x = size_x;
	this->size_y = size_y;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->ObjTar = space;
	this->mouse = mouse;
	this->color = color;
	this->frames[0] = frames;
	this->frames[1] = frames;
	active = false;
	this->text.setFont(*font_global);
	
	
	this->text.setFillColor(Color::White);
	this->text.setString(String(text));
	std::cout << "x= " << this->text.getGlobalBounds().getSize().x;
	this->text.setPosition(pos_x+size_x/2 - (this->text.getGlobalBounds().getSize().x)/2, pos_y+size_y/2 - (this->text.getGlobalBounds().getSize().y)/2);


	
	//but_shape.setSize(Vector2f(size_x, size_y));
	//but_shape.setPosition(Vector2f(pos_x, pos_y));

	std::shared_ptr<Button> a(this);
	pool_button.emplace_back(a);
	//std::cout << (pool_pair[0].get());
	this->run = run;
}
Button::Button(int pos_x, int pos_y, int frames, std::function<void()>, RenderTarget* space, Mouse* mouse)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->ObjTar = space;
	this->mouse = mouse;
	this->frames[0] = frames;
	this->frames[1] = frames;
	active = false;


	//but_shape.setSize(Vector2f(size_x, size_y));
	//but_shape.setPosition(Vector2f(pos_x, pos_y));

	std::shared_ptr<Button> a(this);
	pool_button.emplace_back(a);
	//std::cout << (pool_pair[0].get());
	this->run = run;
}
void Button::setActive() {
	//std::cout << "is clicked\n";
	//std::cout << !active << '\n';
	//std::cout << Clicable::click(*mouse) << '\n';

	
	if (!active && Click()) {
		active = true;
		//std::cout << "called" << '\n';
		
		//изменить цвет фигуры
		std::cout << "CLICK!!!";
		but_shape->setFillColor(Color::Color(color.r + 40, color.g + 40, color.b + 40));
	}
}
void Button::standart() {
	but_shape->setFillColor(color);
	active = false;
	run();
}
void Button::draw() {
	ObjTar->draw(*but_shape);
	ObjTar->draw(text);
}
bool Button::getActive() {
	return active;
}

int Button::getFrames()
{
	return frames[1];
}

void Button::isActive() {
	if (active)
	{
		if (this->getFrames() != 0) {
			frames[1] -= 1;
			std::cout << "is active called\n";
		}
		else {
			active = false;
			but_shape->setFillColor(color);
			frames[1] = frames[0];
			standart();
		}
	}
	
}
Button::~Button() {
	std::cout << '\n' << this << '\n';
}

//Определение Pair Array
CircleButton::CircleButton(int size_x, int size_y, int pos_x, int pos_y, int frames, char* text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color) :
	Button(size_x, size_y, pos_x, pos_y, frames, text, run,  space,  mouse, color) {
	size_y = size_x;
	CircleShape* tempshape = new CircleShape;
	tempshape->setRadius(size_x / 2);
	tempshape->setFillColor(color);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(3);
	tempshape->setPosition(pos_x, pos_y);
	but_shape = tempshape;
}
RectButton::RectButton(int size_x, int size_y, int pos_x, int pos_y, int frames, char* text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color) :
	Button(size_x, size_y, pos_x, pos_y, frames, text, run, space, mouse, color) {
	RectangleShape* tempshape = new RectangleShape;
	but_shape = new RectangleShape;
	tempshape->setSize(Vector2f(size_x, size_y));
	tempshape->setPosition(pos_x, pos_y);
	tempshape->setFillColor(color);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(3);
	but_shape = tempshape;
}
CustomButton::CustomButton(int size_x, int size_y, int pos_x, int pos_y, int frames, char* text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color) :
	Button(size_x, size_y, pos_x, pos_y, frames, text, run, space, mouse, color) {
	ConvexShape* tempshape = new ConvexShape;
	tempshape->setPointCount(4);
	tempshape->setPoint(0, Vector2f(pos_x, pos_y));
	double tmpn = size_y * tan((30 * 3.14) / 180);
	tempshape->setPoint(1, Vector2f(pos_x - tmpn, pos_y + size_y));
	tempshape->setPoint(2, Vector2f(pos_x + size_x, pos_y + size_y));
	tempshape->setPoint(3, Vector2f(pos_x + size_x + tmpn, pos_y));
	tempshape->setFillColor(color);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(3);
	but_shape = tempshape;
}
RectButtonImage::RectButtonImage(int pos_x, int pos_y, int frames,std::string img, std::function<void()> run, RenderTarget* space, Mouse* mouse) :
	Button(pos_x, pos_y, frames, run, space,  mouse) {
	texture = new Texture;
	sprite = new Sprite;
	texture->loadFromFile(img);
	
	sprite->setTexture(*texture);
	size_x = texture->getSize().x;
	size_y = texture->getSize().y;
	sprite->setPosition(pos_x, pos_y);

	RectangleShape* tempshape = new RectangleShape;
	//but_shape = new RectangleShape;
	tempshape->setSize(Vector2f(size_x,size_y));
	tempshape->setPosition(pos_x, pos_y);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(3);
	tempshape->setFillColor(Color(0, 0, 0, 0));
	but_shape = tempshape;
}

void RectButtonImage::draw() {
	ObjTar->draw(*sprite);
	ObjTar->draw(*but_shape);
}

RectButtonImageRolled::RectButtonImageRolled(int pos_x, int pos_y, int time, std::string img, std::function<void()> rn, RenderTarget* space, Mouse* mouse) :
	RectButtonImage(pos_x, pos_y, time, img, rn, space, mouse)
{
	
	delete but_shape;
	this->time = time;
	angle = 0;
	frames[0] = time*FPS;
	frames[1] = frames[0];
	setCenter();
}
void RectButtonImageRolled::isActive()
{
	if (active && frames[0]>0) {
		sprite->rotate(360 / (FPS * time));
		frames[0] -= 1;
	}
	else if(frames[0]==0) {
		active = false;
		frames[0] = frames[1];
	}
}
void RectButtonImageRolled::setCenter()
{
	int tx = sprite->getPosition().x, ty = sprite->getPosition().y;
	sprite->setOrigin(texture->getSize().x/2, texture->getSize().y / 2);
	sprite->setPosition(tx + texture->getSize().x / 2, ty + texture->getSize().y / 2);
}

void RectButtonImageRolled::draw()
{
	ObjTar->draw(*sprite);
}

void RectButtonImageRolled::setActive()
{
	std::cout << "frames = " << frames[0] << " and " << frames[1]<<'\n';
	if (!active && Click()) {
		active = true;
		std::cout << "RectButtonImageRolled is active\n";
	}
}

RectButtonImageRolled::~RectButtonImageRolled()
{
	if (texture != nullptr) delete texture;
	if (sprite != nullptr) delete sprite;
}

