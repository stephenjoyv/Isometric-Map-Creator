#pragma once
#include "Libs.h"
#include "Menu.h"

class ColorSel;
class SliderBar;

class SettingsScene : public Scene {
private:
	std::unique_ptr<ColorSel> RectColor;
	std::unique_ptr<SliderBar> sb,sb1,sb2;
	bool leftJammed;
protected:
	virtual bool verifyEvents(const sf::Event&) override;
	virtual void runEvents() override;
	virtual void drawing() override;
public:
	SettingsScene();
	~SettingsScene();
	virtual void eventLoop() override;
};