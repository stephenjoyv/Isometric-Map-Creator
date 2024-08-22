#pragma once
#include "Libs.h"
class Animation;
class Scene {
protected:
	virtual bool verifyEvents(const sf::Event&) = 0;
	virtual void runEvents() = 0;
	virtual void drawing() = 0;
public:
	virtual void eventLoop() = 0;
};
class WelcomeScene : public Scene {
	std::vector<std::unique_ptr<Animation>> anims;
protected:
	virtual bool verifyEvents(const sf::Event&) override;
	virtual void runEvents() override;
	virtual void drawing() override;
public:
	virtual void eventLoop() override;
	WelcomeScene();
};