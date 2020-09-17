#pragma once

#include <set>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "Heap.hpp"
#include "Grid.hpp"

class AStar {
public:
	AStar(const Grid& grid) : mGrid(grid) {}
	
	std::vector<sf::Vector2i> findPath();

private:
	const std::vector<sf::Vector2i> retracePath(const Node& startNode, const Node& targetNode);
	const int getDistance(Node& nodeA, Node& nodeB);

private:
	Grid mGrid;
};

