#include "../public/Heap.hpp"

template<class T>
void Heap<T>::add(T item) {
	item.setHeapIndex(mCurrentItemCount);
	mItems.push_back(item);
	sortUp(item);
	mCurrentItemCount++;
}

template<class T>
T Heap<T>::removeFirst() {
	T firstItem = mItems[0];
	mCurrentItemCount--;
	mItems[0] = mItems[mCurrentItemCount];
	mItems[0].setHeapIndex(0);
	sortDown(mItems[0]);
	return firstItem;
}

template<class T>
void Heap<T>::sortDown(T item) {
	while (true) {
		int childIndexLeft = item.heapIndex() * 2 + 1;
		int childIndexRight = item.heapIndex() * 2 + 2;
		int swapIndex = 0;

		if (childIndexLeft < mCurrentItemCount) {
			swapIndex = childIndexLeft;

			if (childIndexRight < mCurrentItemCount) {
				if (mItems[childIndexLeft] < mItems[childIndexRight]) {
					swapIndex = childIndexRight;
				}
			}

			if (item < mItems[swapIndex]) {
				swap(item, mItems[swapIndex]);
			} else {
				return;
			}
		} else {
			return;
		}
	}
}

template<class T>
void Heap<T>::sortUp(T item) {
	int parentIndex = (item.heapIndex() - 1) / 2;

	while (true) {
		T parentItem = mItems[parentIndex];
		if (item > parentItem) {
			swap(item, parentItem);
		} else {
			break;
		}

		parentIndex = (item.heapIndex() - 1) / 2;
	}
}

template<class T>
void Heap<T>::swap(T itemA, T itemB) {
	mItems[itemA.heapIndex()] = itemB;
	mItems[itemB.heapIndex()] = itemA;

	int itemAIndex = itemA.heapIndex();
	itemA.setHeapIndex(itemB.heapIndex());
	itemB.setHeapIndex(itemAIndex);
}

template<class T>
void Heap<T>::updateItem(T item) { sortUp(item); }
