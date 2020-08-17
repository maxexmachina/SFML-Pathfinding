#pragma once
#include <vector>
#include "Node.hpp"

class Grid {
public:
	Grid() {}

	Grid(int sizeX, int sizeY) :
		mSizeX(sizeX), mSizeY(sizeY) {
		createGrid();
	}

	void createGrid();

	void handleResize(int sizeX, int sizeY);

	Node get(int x, int y) { return mGrid.at(y).at(x); }
	void setTypeAt(int x, int y, NodeType type) { mGrid.at(y).at(x).setType(type); }

private:
	int mSizeX, mSizeY;
	std::vector<std::vector<Node>> mGrid;
};
