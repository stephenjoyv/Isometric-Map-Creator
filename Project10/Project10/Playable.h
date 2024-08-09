#pragma once
#include "Libs.h"
#include "interfaceobj.h"
class Playable : public Clicable{
private:
	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Texture> texture;
public:
	enum class Direction {
		left, right, up, down
	};
	Playable(RenderTarget* target);
	void load(const std::string& path);
	void move(Direction dir,int value);
	void setActive() override;
	bool isActive() override;
	void draw() override;
};
