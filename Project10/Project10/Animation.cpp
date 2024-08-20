#include "Animation.h"

Animation::Animation(std::string dir, int count,double duration, RenderTarget* target)
{
	current_frame = 0;
	ObjTar = target;
	frame_count = count;
	frame_duration = duration;
	animation_tx = new sf::Texture[count];
	animation_sp = new sf::Sprite[count];
	for (size_t i = 0; i < count; i++)
	{
		animation_tx[i].loadFromFile(dir+ std::to_string(i)+".png");
		animation_sp[i].setTexture(animation_tx[i]);
		animation_sp[i].setScale(5, 5);
	}
	size_x = animation_tx[0].getSize().x;
	size_y = animation_tx[0].getSize().y;
	pos_x = 0;
	pos_y = 0;
	timings = new int[count];
	for (size_t i = 0; i < count; i++)
	{
		timings[i] = ((Singleton::instance().getFPS() * 1.f) / count) * i*duration;
	}
}

Animation::~Animation()
{
	for (size_t i = 0; i < frame_count; i++)
	{
		delete animation_tx, animation_sp;
		animation_sp = nullptr;
		animation_tx = nullptr;
	}
}

void Animation::moveTo(int x, int y)
{
	pos_x = x;
	pos_y = y;
	for (size_t i = 0; i < frame_count; i++)
	{
		animation_sp[i].setPosition(x, y);
	}
}

void Animation::draw()
{
	ObjTar->draw(animation_sp[current_frame]);
}

void Animation::changing()
{
	frame_changing_counter++;
	if (frame_changing_counter>= Singleton::instance().getFPS() *frame_duration)
	{
		current_frame = 0;
		frame_changing_counter = 0;
	}
	else {
		if (current_frame+1<frame_count)
		{
			if (frame_changing_counter > timings[current_frame + 1])
			{
				current_frame++;
			}
		}
	}
	if (current_frame==frame_count)
	{
		current_frame == 0;
		frame_changing_counter = 0;
	}
}

void Animation::scaleImage(double x, double y)
{
	for (size_t i = 0; i < frame_count; i++)
	{
		animation_sp[i].setScale(x, y);
		
	}
}
