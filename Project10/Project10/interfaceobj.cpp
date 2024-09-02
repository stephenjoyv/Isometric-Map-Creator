#include "interfaceobj.h"



void globalDraw() {
	for (auto c : Singleton::instance().getPoolButton()) {
		c->draw();
	}
}

void buttonWork()
{
	for (auto c: Singleton::instance().getPoolButton())
	{
		if (c->isActive())
		{
			break;
		}
	}
}

bool Clicable::Click() {
	RenderWindow* temp = Singleton::instance().getPoolWindow()[0].get();

	bool tmp = Mouse::isButtonPressed(Mouse::Left) && (mouse->getPosition(*temp).y >= pos_y) &&
		(mouse->getPosition(*temp).y <= pos_y + size_y) && (mouse->getPosition(*temp).x >= pos_x) && (mouse->getPosition(*temp).x <= pos_x + size_x);
	return tmp;
}

bool Clicable::Click(const sf::View& view)
{
	RenderWindow* temp = Singleton::instance().getPoolWindow()[0].get();
	bool tmp = Mouse::isButtonPressed(Mouse::Left) && (mouse->getPosition(*temp).y >= pos_y) &&
		(mouse->getPosition(*temp).y <= pos_y + size_y) && (mouse->getPosition(*temp).x >= pos_x) && (mouse->getPosition(*temp).x <= pos_x + size_x);
	return tmp;
}

bool Clicable::Click(int difference_x, int difference_y)
{
	RenderWindow* temp = Singleton::instance().getPoolWindow()[0].get();

	bool tmp = Mouse::isButtonPressed(Mouse::Left) && (mouse->getPosition(*temp).y >= pos_y+difference_y) &&
		(mouse->getPosition(*temp).y <= pos_y + size_y+difference_y) && (mouse->getPosition(*temp).x >= pos_x+difference_x) && (mouse->getPosition(*temp).x <= pos_x + size_x+difference_x);
	return tmp;
}

void Clicable::setActive(const sf::View&)
{
}




//Определение Button
Button::Button(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color) {
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
	this->text.setFont(*Singleton::instance().getGlobalFont());


	this->text.setFillColor(Color::White);
	this->text.setString(String{ text });
	std::cout << "x= " << this->text.getGlobalBounds().getSize().x;
	this->text.setPosition(pos_x+size_x/2 - (this->text.getGlobalBounds().getSize().x)/2, pos_y+size_y/2 - (this->text.getGlobalBounds().getSize().y)/2);


	
	//but_shape.setSize(Vector2f(size_x, size_y));
	//but_shape.setPosition(Vector2f(pos_x, pos_y));
	//pool_button.emplace_back(a);
	//std::cout << (pool_pair[0].get());
	this->run = run;
	id = "";
}
Button::Button(int pos_x, int pos_y, int frames, std::function<void()> run, RenderTarget* space, Mouse* mouse)
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

	
	//pool_button.emplace_back(a);
	//std::cout << (pool_pair[0].get());
	this->run = run;
	id = "";
}
Button::Button()
{
}
Button::~Button()
{
}
void Button::setActive() {
	if (!active && Click()) {
		active = true;
		//изменить цвет фигуры
		std::cout << "CLICK!!!";
		buttonShape->setFillColor(Color::Color(color.r + 40, color.g + 40, color.b + 40));
	}
}
void Button::setId(const std::string& newId)
{
	id = newId;
}
std::string Button::getId()
{
	return id;
}
void Button::setRunFunction(std::function<void()> fun)
{
	run = fun;
}
void Button::standart() {
	buttonShape->setFillColor(color);
	active = false;
	run();
}
void Button::scale(float x, float y)
{
}
void Button::draw() {
	ObjTar->draw(*buttonShape);
	ObjTar->draw(text);
}
void Button::pushToDrawingVector()
{
	std::shared_ptr<Button> a(this);
	Singleton::instance().getPoolButton().emplace_back(a);
}
bool Button::getActive() {
	return active;
}

int Button::getFrames()
{
	return frames[1];
}

bool Button::isActive() {
	if (active)
	{
		if (this->getFrames() != 0) {
			frames[1] -= 1;
			std::cout << "is active called\n";
		}
		else {
			active = false;
			buttonShape->setFillColor(color);
			frames[1] = frames[0];
			standart();
		}
		return true;
	}
	return false;
}
//Определение Pair Array
CircleButton::CircleButton(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color) :
	Button(size_x, size_y, pos_x, pos_y, frames, text, run,  space,  mouse, color) {
	size_y = size_x;
	std::unique_ptr<CircleShape> tempshape = std::make_unique<CircleShape>();
	tempshape->setRadius(size_x / 2);
	tempshape->setFillColor(color);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(4);
	tempshape->setPosition(pos_x, pos_y);
	buttonShape = std::move(tempshape);
}
//	Button(size_x, size_y, pos_x, pos_y, frames, text, run, space, mouse, color)
RectButton::RectButton(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color)
{
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
	this->text.setFont(*Singleton::instance().getGlobalFont());


	this->text.setFillColor(Color::White);
	this->text.setString(String{ text });
	std::cout << "x= " << this->text.getGlobalBounds().getSize().x;
	this->text.setPosition(pos_x + size_x / 2 - (this->text.getGlobalBounds().getSize().x) / 2, pos_y + size_y / 2 - (this->text.getGlobalBounds().getSize().y) / 2);



	//but_shape.setSize(Vector2f(size_x, size_y));
	//but_shape.setPosition(Vector2f(pos_x, pos_y));

	
	//pool_button.emplace_back(a);
	//std::cout << (pool_pair[0].get());
	this->run = run;
	std::unique_ptr<RectangleShape> tempshape = std::make_unique<RectangleShape>();
	tempshape->setSize(Vector2f(size_x, size_y));
	tempshape->setPosition(pos_x, pos_y);
	tempshape->setFillColor(color);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(4);
	buttonShape = std::move(tempshape);
}
void RectButtonImage::pushToDrawingVector()
{
	std::shared_ptr<Button> a(this);
	Singleton::instance().getPoolButton().emplace_back(a);
}
CustomButton::CustomButton(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()> run, RenderTarget* space, Mouse* mouse, Color color) :
	Button(size_x, size_y, pos_x, pos_y, frames, text, run, space, mouse, color) {
	std::unique_ptr<ConvexShape> tempshape = std::make_unique<ConvexShape>();
	tempshape->setPointCount(4);
	tempshape->setPoint(0, Vector2f(pos_x, pos_y));
	double tmpn = size_y * tan((30 * 3.14) / 180);
	tempshape->setPoint(1, Vector2f(pos_x - tmpn, pos_y + size_y));
	tempshape->setPoint(2, Vector2f(pos_x + size_x, pos_y + size_y));
	tempshape->setPoint(3, Vector2f(pos_x + size_x + tmpn, pos_y));
	tempshape->setFillColor(color);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(4);
	buttonShape = std::move(tempshape);
}
RectButtonImage::RectButtonImage(int pos_x, int pos_y, int frames,std::string img, std::function<void()> run, RenderTarget* space, Mouse* mouse) :
	Button(pos_x, pos_y, frames, run, space,  mouse) {
	texture = std::make_unique<sf::Texture>();
	sprite = std::make_unique<sf::Sprite>();
	texture->loadFromFile(img);
	
	sprite->setTexture(*texture);
	size_x = texture->getSize().x;
	size_y = texture->getSize().y;
	sprite->setPosition(pos_x, pos_y);

	std::unique_ptr<RectangleShape> tempshape = std::make_unique<RectangleShape>();
	tempshape->setSize(Vector2f(size_x,size_y));
	tempshape->setPosition(pos_x, pos_y);
	tempshape->setOutlineColor(Color::White);
	tempshape->setOutlineThickness(4);
	tempshape->setFillColor(Color(0, 0, 0, 0));
	buttonShape = std::move(tempshape);
}

void RectButtonImage::draw() {
	ObjTar->draw(*sprite);
	ObjTar->draw(*buttonShape);
}

RectButtonImageRolled::RectButtonImageRolled(int pos_x, int pos_y, int time, std::string img, std::function<void()> rn, RenderTarget* space, Mouse* mouse) :
	RectButtonImage(pos_x, pos_y, time, img, rn, space, mouse)
{
	this->time = time;
	angle = 0;
	frames[0] = time*Singleton::instance().getFPS();
	frames[1] = frames[0];
	setCenter();
	k = 15;
}

bool RectButtonImageRolled::isActive()
{
	if (active && frames[0]>0) {
		sprite->rotate(360 / (Singleton::instance().getFPS() * time));
		frames[0] -= 1;
		return false;
	}
	else if(frames[0]==0) {
		active = false;
		frames[0] = frames[1];
		run();
	}
	return true;
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

void RectButtonImageRolled::scale(float x, float y)
{
	sprite->scale(x, y);
}

void RectButtonImageRolled::pushToDrawingVector()
{
	std::shared_ptr<Button> a(this);
	Singleton::instance().getPoolButton().emplace_back(a);
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
	k = 0;
	std::cout << "RECTDEST\n";
}

