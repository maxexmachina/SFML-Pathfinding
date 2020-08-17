#include <iostream>
#include "public/App.hpp"

int main() {
	const size_t tilesHorizontal = 40;
	const size_t tilesVertical = 40;

	App app{ tilesHorizontal, tilesVertical };
	app.run();
}