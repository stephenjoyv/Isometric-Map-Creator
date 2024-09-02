#pragma once
#include "Libs.h"
#include "interfaceobj.h"
class Animation:public IBaseClass
{
private:
	std::vector<std::unique_ptr<sf::Texture>> animation_tx;
	std::vector<std::unique_ptr<sf::Sprite>> animation_sp;
	int frame_count;
	int current_frame;
	double frame_duration;
	int frame_changing_counter;
	int* timings;
public:
	Animation(std::string dir,int frames_count,double duration,RenderTarget* target);
	void moveTo(int x, int y);
	sf::Vector2f getPosition();
	void draw() override;
	void changing();
	void scaleImage(double x,double y);
};

