#pragma once
#include <memory>

enum NodeType {
	Walkable,
	Obstacle,
	Seeker,
	Target
};

class Node {
public:
	Node(NodeType type, size_t gridX, size_t gridY, size_t penalty) :
		mGridX(gridX), mGridY(gridY) {
		mType = type;
	}

	Node(const Node& node) {
		mGridX = node.mGridX;
		mGridY = node.mGridY;
		mType = node.mType;
	}

	const size_t fCost() { return mGCost + mHCost; }
	const size_t hCost() { return mHCost; }
	const size_t gCost() { return mGCost; }
	NodeType type() { return mType; }
	void setType(NodeType type) { mType = type; }
	const size_t gridX() { return mGridX; }
	const size_t gridY() { return mGridY; }

private:
	NodeType mType;
	size_t mGridX, mGridY;

private:
	std::unique_ptr<Node> parent;
	size_t mGCost, mHCost;
};
