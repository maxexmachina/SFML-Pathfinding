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
	std::vector<Node> getNeighbours(Node node);

	Node get(int x, int y) const { return mGrid.at(y).at(x); }
	sf::Vector2i getSize() const { return sf::Vector2i{ mSizeX, mSizeY }; }
	const int maxSize() const { return mSizeX * mSizeY; }
	void setTypeAt(int x, int y, NodeType type) { mGrid.at(y).at(x).setType(type); }
	const Node seeker() const { return mSeeker; }
	const Node target() const { return mTarget; }
	void setSeeker(const Node& node) { mSeeker = node; }
	void setTarget(const Node& node) { mTarget = node; }

private:
	int mSizeX, mSizeY;
	std::vector<std::vector<Node>> mGrid;
	Node mSeeker, mTarget;
};
