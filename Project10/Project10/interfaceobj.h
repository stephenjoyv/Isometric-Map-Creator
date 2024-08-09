#pragma once
#include "Libs.h"
#include "Singleton.h"
using namespace sf;
class IBaseClass;
class Button;
class Clicable;


class IBaseClass {
protected:
	int size_x, size_y, pos_x, pos_y;
	RenderTarget* ObjTar;
public:
	virtual void draw() = 0;
	IBaseClass();
	virtual ~IBaseClass();
};


//Класс изображения
//Вспомогательный класс для отслеживания нажатий
class Clicable : public virtual IBaseClass
{
protected:
	Mouse* mouse;
public:
	virtual bool Click();
	virtual bool Click(int difference_x, int difference_y);
	virtual void setActive() = 0;
	virtual bool isActive() = 0;
	Clicable() = default;
	virtual ~Clicable() = default;
};

//Сетчатая панель для спавнера
class Button;

//Парный класс хранящий число кадров для отображения активности кнопки


//Класс кнопки
class Button :public virtual Clicable, public virtual IBaseClass {
protected:
	Shape* but_shape;
	Color color;
	Text text;
	bool active = false;
	int frames[2];
	std::function<void()> run;
	std::string id;
public:
	Button(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()>, RenderTarget* space, Mouse* mouse, Color color);
	Button(int pos_x, int pos_y, int frames, std::function<void()>, RenderTarget* space, Mouse* mouse);
	Button();
	void setActive() override;
	void setId(const std::string&);
	std::string getId();
	void setRunFunction(std::function<void()>);
	void standart();
	void scale(float x, float y);
	void draw() override;
	bool getActive();
	int getFrames();
	bool isActive() override;
	virtual ~Button() override;
};
class CircleButton : public Button {
public:
	CircleButton(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()>, RenderTarget* space, Mouse* mouse, Color color);
	~CircleButton() = default;
};
class RectButton : public Button {
public:
	RectButton(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()>, RenderTarget* space, Mouse* mouse, Color color);
	~RectButton();
};
class CustomButton : public Button {
public:
	CustomButton(int size_x, int size_y, int pos_x, int pos_y, int frames, std::string text, std::function<void()>, RenderTarget* space, Mouse* mouse, Color color);
	~CustomButton() = default;
};
class RectButtonImage : public Button {
protected:
	Texture* texture;
	Sprite* sprite;
public:
	RectButtonImage(int pos_x, int pos_y, int frames, std::string img, std::function<void()>, RenderTarget* space, Mouse* mouse);
	void draw() override;
	~RectButtonImage() = default;
};
class RectButtonImageRolled : public RectButtonImage {
private:
	int angle, time;
public:
	int k;
	RectButtonImageRolled(int pos_x, int pos_y, int time, std::string img, std::function<void()>, RenderTarget* space, Mouse* mouse);
	RectButtonImageRolled() = default;
	void setCenter();
	void setActive() override;
	bool isActive() override;
	void draw() override;
	void scale(float x, float y);
	~RectButtonImageRolled();
};
void globalDraw();
void buttonWork();

void ButtonLoader(sf::RenderTarget* space, sf::Mouse* mouse, sf::Color color, String adress);