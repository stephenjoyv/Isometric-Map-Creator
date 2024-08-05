#pragma once
#include "Libs.h"
#include "interfaceobj.h"
class Playable : public IBaseClass{
private:
	
public:
	Playable(sf::RenderTarget target);
	void draw() override;
	~Playable();
};