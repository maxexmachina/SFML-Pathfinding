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
	Node() {}

	Node(NodeType type, size_t gridX, size_t gridY) :
		mGridX(gridX), mGridY(gridY) {
		mType = type;
	}

	Node(const Node& node) {
		mGridX = node.mGridX;
		mGridY = node.mGridY;
		mType = node.mType;
		mGCost = node.mGCost;
		mHCost = node.mHCost;
		mHeapIndex = node.mHeapIndex;
		mParent = node.mParent;
	}

	const size_t fCost() const { return mGCost + mHCost; }
	const size_t hCost() const { return mHCost; }
	const size_t gCost() const { return mGCost; }
	void setHCost(int cost) { mHCost = cost; }
	void setGCost(int cost) { mGCost = cost; }
	NodeType type() { return mType; }
	void setType(NodeType type) { mType = type; }
	const int gridX() { return mGridX; }
	const int gridY() { return mGridY; }
	const int heapIndex() const { return mHeapIndex; }
	void setHeapIndex(int index) { mHeapIndex = index; }
	const std::shared_ptr<Node> parent() { return mParent; }
	void setParent(std::shared_ptr<Node> p) { mParent = p; }
	
	void operator= (const Node& node) {
		mGridX = node.mGridX;
		mGridY = node.mGridY;
		mType = node.mType;
		mGCost = node.mGCost;
		mHCost = node.mHCost;
		mHeapIndex = node.mHeapIndex;
		mParent = node.mParent;
	}

	bool operator> (const Node& n2) {
		if (fCost() == n2.fCost()) {
			return !(hCost() > n2.hCost());
		}
		return !(fCost() > n2.fCost());
	}

	bool operator< (const Node& n2) {
		if (fCost() == n2.fCost()) {
			return !(hCost() < n2.hCost());
		}
		return !(fCost() < n2.fCost());
	}

	friend bool operator< (const Node& n1, const Node& n2) {
		if (n1.fCost() == n2.fCost()) {
			return !(n1.hCost() < n2.hCost());
		}
		return !(n1.fCost() < n2.fCost());
	}

	friend bool operator== (const Node& n1, const Node& n2) {
		return (n1.mType == n2.mType && n1.mGridX == n2.mGridX &&
			n1.mGridY == n2.mGridY && n1.mGCost == n2.mGCost &&
			n1.mHCost == n2.mHCost && n1.mHeapIndex == n2.mHeapIndex &&
			n1.mParent == n2.mParent);

	}

	bool operator== (const Node& n) {
		return (mType == n.mType && mGridX == n.mGridX &&
			mGridY == n.mGridY && mGCost == n.mGCost &&
			mHCost == n.mHCost && mHeapIndex == n.mHeapIndex &&
			mParent == n.mParent);
	}

	friend bool operator!= (const Node& n1, const Node& n2) {
		return !(n1 == n2);
	}

private:
	NodeType mType;
	size_t mGridX, mGridY;

private:
	std::shared_ptr<Node> mParent;
	size_t mGCost, mHCost;
	int mHeapIndex;
};

