#include "SelectedTile.h"
SelectedTile::SelectedTile(Image* img) {
	image = img;
	loadCur();
	enableCur();
}

void SelectedTile::loadCur()
{
	std::cout << "\ncursor loaded " << cur.loadFromPixels(image->getPixelsPtr(), Vector2u(image->getSize().x, image->getSize().y), Vector2u(0, 0)) << '\n';
}

void SelectedTile::enableCur()
{
	pool_window[0].get()->setMouseCursor(cur);
}
