#include "Playable.h"
Playable::Playable(sf::RenderTarget* target)
{
	ObjTar = target;
}

void Playable::load(const std::string& path)
{
	texture = std::unique_ptr<Texture>(new sf::Texture{});
	texture->loadFromFile(path);
	sprite = std::make_unique<Sprite>(*texture);
}

void Playable::move(Direction dir,int value)
{
	switch (dir)
	{
	case Playable::Direction::left:
		sprite->move(-value, 0);
		break;
	case Playable::Direction::right:
		sprite->move(value, 0);
		break;
	case Playable::Direction::up:
		sprite->move(0, -value);
		break;
	case Playable::Direction::down:
		sprite->move(0,value);
		break;
	default:
		break;
	}
	
}

void Playable::setActive()
{
}

void Playable::isActive()
{
}

void Playable::draw()
{
	ObjTar->draw(*sprite);
}

