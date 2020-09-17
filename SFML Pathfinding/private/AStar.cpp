#include "../public/AStar.hpp"

 std::vector<sf::Vector2i> AStar::findPath() {

	std::vector<sf::Vector2i> waypoints;
	auto pathSuccess = false;
	
	auto startNode = mGrid.seeker();
	auto targetNode = mGrid.target();
	
	Heap<Node> openSet{ static_cast<size_t>(mGrid.maxSize()) };
	std::set<Node> closedSet;
	openSet.add(startNode);

	while (openSet.count() > 0) {

		auto currentNode = openSet.removeFirst();
		closedSet.insert(currentNode);

		if (currentNode == targetNode) {
			std::cout << "Path found\n";
			pathSuccess = true;
			break;
		}

		auto neighbours = mGrid.getNeighbours(currentNode);
		for (auto& neighbour : neighbours) {
			if (neighbour.type() != NodeType::Walkable || closedSet.find(neighbour) != closedSet.end()) {
				continue;
			}

			auto newMovementCostToNeighbour = currentNode.gCost() + getDistance(currentNode, neighbour);
			if (newMovementCostToNeighbour < neighbour.gCost() || !openSet.contains(neighbour)) {
				neighbour.setGCost(newMovementCostToNeighbour);
				neighbour.setHCost(getDistance(neighbour, targetNode));
				neighbour.setParent(std::make_shared<Node>(currentNode));

				if (!openSet.contains(neighbour)) {
					openSet.add(neighbour);
				} else {
					openSet.updateItem(neighbour);
				}
			}
		}
	}

	if (pathSuccess) {
		waypoints = retracePath(startNode, targetNode);
		pathSuccess = waypoints.size() > 0;
	}
	return waypoints;
}

const std::vector<sf::Vector2i> AStar::retracePath(const Node& startNode, const Node& targetNode) {
	std::vector<sf::Vector2i> path;
	auto currentNode = targetNode;
	
	while (currentNode != startNode) {
		path.push_back(sf::Vector2i{ currentNode.gridX(), currentNode.gridY() });
		currentNode = *currentNode.parent();
	}
	std::reverse(path.begin(), path.end());
	return path;
}

const int AStar::getDistance(Node& nodeA, Node& nodeB) {
	auto dstX = abs(nodeA.gridX() - nodeB.gridX());
	auto dstY = abs(nodeA.gridY() - nodeB.gridY());

	if (dstX > dstY) {
		return 14 * dstY + 10 * (dstX - dstY);
	}

	return 14 * dstX + 10 * (dstY - dstX);
}