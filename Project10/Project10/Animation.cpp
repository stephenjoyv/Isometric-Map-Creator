#include "Animation.h"

Animation::Animation(std::string dir, int count,double duration, RenderTarget* target)
{
	current_frame = 0;
	ObjTar = target;
	frame_count = count;
	frame_duration = duration;
	for (size_t i = 0; i < count; i++)
	{
		Texture* tx = new sf::Texture;
		Sprite* sp = new sf::Sprite;

		

		tx->loadFromFile(dir+ std::to_string(i)+".png");
		sp->setTexture(*tx);
		sp->setScale(5, 5);
		animation_tx.emplace_back(std::unique_ptr<Texture>(tx));
		animation_sp.emplace_back(std::unique_ptr<Sprite>(sp));
	}
	size_x = animation_tx[0]->getSize().x;
	size_y = animation_tx[0]->getSize().y;
	pos_x = 0;
	pos_y = 0;
	timings = new int[count];
	for (size_t i = 0; i < count; i++)
	{
		timings[i] = ((Singleton::instance().getFPS() * 1.f) / count) * i*duration;
	}
}


void Animation::moveTo(int x, int y)
{
	pos_x = x;
	pos_y = y;
	for (auto s = animation_sp.begin();s!=animation_sp.end();s++)
	{
		s->get()->setPosition(x, y);
	}
}

sf::Vector2f Animation::getPosition()
{
	return animation_sp[0]->getPosition();
}

void Animation::draw()
{
	ObjTar->draw(*animation_sp.at(current_frame));
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
	for (auto s = animation_sp.begin(); s != animation_sp.end(); s++)
	{
		s->get()->setScale(x,y);
	}
}
