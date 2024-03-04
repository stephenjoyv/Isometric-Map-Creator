
#include "ButtonsFunctions.h"

void StartNewGame() {
	
	pool_button.clear();
	
	game(pool_window[0].get());
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