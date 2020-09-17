#include "../public/Grid.hpp"

void Grid::createGrid() {
	for (size_t y = 0; y < mSizeY; y++) {
		std::vector<Node> tempVector;
		for (size_t x = 0; x < mSizeX; x++) {
			tempVector.push_back(Node(NodeType::Walkable, x, y));
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

std::vector<Node> Grid::getNeighbours(Node node) {
	std::vector<Node> neighbours;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0) {
				continue;
			}

			int checkX = node.gridX() + x;
			int checkY = node.gridY() + y;

			if (checkX >= 0 && checkX < mSizeX && checkY >= 0 && checkY < mSizeY) {
				neighbours.push_back(mGrid.at(checkX).at(checkY));
			}
		}
	}
	return neighbours;
}
