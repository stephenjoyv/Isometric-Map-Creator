#include "ButtonsFunctions.h"
#include "interfaceobj.h"
#include "Libs.h"
#include "Game.h"
#include "Gameplay.h"
#include "Testing.h"
void StartNewGame() {
	Singleton::instance().getPoolButton().clear();
	GameplayScene scene{};
	scene.eventLoop();
	ButtonLoader(Singleton::instance().getPoolWindow()[0].get(), &Singleton::instance().getMouse(), *Singleton::instance().getMainColor(), "notes/buttons.json");
	return;
}
void LoadNewGame() {
	Singleton::instance().getPoolButton().clear();
	EditorScene scene{};
	scene.eventLoop();
	ButtonLoader(Singleton::instance().getPoolWindow()[0].get(), &Singleton::instance().getMouse(), *Singleton::instance().getMainColor(), "notes/buttons.json");
	return;
}
void Exit() {
	for (auto c: Singleton::instance().getPoolWindow()) {
		c.get()->close();
	}
	/*for (int i = 0; i < Singleton::instance().getPoolWindow().size(); i++)
	{
		pool_window[i].get()->close();
	}*/
}
void loadDefaultColor() {

}
void Settings() {

}

void Test() {

}

void testing()
{
	Singleton::instance().getPoolButton().clear();
	Testing scene{};
	scene.eventLoop();
}
