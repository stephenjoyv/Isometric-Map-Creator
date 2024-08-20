
#include "ButtonsFunctions.h"

void StartNewGame() {
	
	Singleton::instance().getPoolButton().clear();
	game();
	return;
}
void LoadNewGame() {

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
void changeGlobalColor() {

}
void Settings() {

}

void Test() {

}