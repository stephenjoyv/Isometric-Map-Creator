
#include "ButtonsFunctions.h"

void StartNewGame() {
	
	pool_button.clear();	
	game(pool_window[0].get());
	return;
}
void LoadNewGame() {
	vector<shared_ptr<RenderWindow>>::iterator a = pool_window.begin();
	pool_window[0].get()->close();
	pool_window.erase(a);
	RenderWindow* nw = new RenderWindow(VideoMode(1000, 500), "application");
	shared_ptr<RenderWindow> nws{nw};
	pool_window.emplace_back(nws);
	std::cout << pool_window.size() << '\n';
}
void Exit() {
	for (int i = 0; i < pool_window.size(); i++)
	{
		pool_window[i].get()->close();
	}
}