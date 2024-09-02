#pragma once
#include "Libs.h"
class Tile;
class SelectedTile;
class TilePanel {
	int size_x, size_y;
	int pos_x, pos_y;
	Tile*** pnl;
	sf::RenderTarget* ObjTar;
	std::unique_ptr<SelectedTile> cur;
	std::unique_ptr<sf::RenderTexture> TilePanel_tx;
	std::unique_ptr<sf::Sprite> TilePanel_sp;
public:
	TilePanel(size_t tile_count,size_t rows_count,sf::Vector2i position, sf::Mouse* mouse);
	void draw();
	bool click(std::unique_ptr<SelectedTile>& m);
	void clickRight();
	~TilePanel();
};
std::string normalizeString(int num);