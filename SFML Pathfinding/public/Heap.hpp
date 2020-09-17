#pragma once
#include <vector>

template <class T>
class Heap {

public:
	Heap(const size_t maxHeapSize) : mItems(std::vector<T>{ maxHeapSize }) 
	{}
	
	void add(T item);
	T removeFirst();
	
	void updateItem(T item);
	const int count() const { return mCurrentItemCount; }
	bool contains(T item) { return (mItems[item.heapIndex()] == item); }

private:
	void sortDown(T item);
	void sortUp(T item);
	void swap(T itemA, T itemB);

private:
	std::vector<T> mItems;
	int mCurrentItemCount;
};
