
#include "ButtonsFunctions.h"

void StartNewGame() {
	
	pool_button.clear();
	
	game();
	return;
}
void LoadNewGame() {

}
void Exit() {
	for (int i = 0; i < pool_window.size(); i++)
	{
		pool_window[i].get()->close();
	}
}
void changeGlobalColor() {

}
void Settings() {

}

void Test() {

}