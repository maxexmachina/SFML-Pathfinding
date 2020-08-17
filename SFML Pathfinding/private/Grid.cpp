#include "../public/Grid.hpp"

void Grid::createGrid() {
	for (size_t y = 0; y < mSizeY; y++) {
		std::vector<Node> tempVector;
		for (size_t x = 0; x < mSizeX; x++) {
			tempVector.push_back(Node(NodeType::Walkable, x, y, 0));
		}
		mGrid.push_back(tempVector);
	}
}

void Grid::handleResize(int sizeX, int sizeY) {
	mSizeX = sizeX;
	mSizeY = sizeY;
	mGrid.clear();
	createGrid();
}
