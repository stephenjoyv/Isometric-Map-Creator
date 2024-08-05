#pragma once
#include "Libs.h"
#include "interfaceobj.h"
extern int FPS;
class Animation:public IBaseClass
{
private:
	sf::Texture* animation_tx;
	sf::Sprite* animation_sp;
	int frame_count;
	int current_frame;
	double frame_duration;
	int frame_changing_counter;
	int* timings;
public:
	Animation(std::string dir,int frames_count,double duration,RenderTarget* target);
	~Animation();
	void moveTo(int x, int y);
	void draw() override;
	void changing();
	void scaleImage(double x,double y);
};

