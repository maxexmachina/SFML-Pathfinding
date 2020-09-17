#pragma once
#include <vector>
#include "Node.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Grid {
public:
	Grid(int sizeX, int sizeY) :
		mSizeX(sizeX), mSizeY(sizeY) {
		createGrid();
	}

	void createGrid();
	void handleResize(int sizeX, int sizeY);

	Node get(int x, int y) { return mGrid.at(y).at(x); }
	sf::Vector2i getSize() { return sf::Vector2i{ mSizeX, mSizeY }; }
	void setTypeAt(int x, int y, NodeType type) { mGrid.at(y).at(x).setType(type); }

private:
	int mSizeX, mSizeY;
	std::vector<std::vector<Node>> mGrid;
};
