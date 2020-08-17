#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class App {

public:
	App(int tilesHorizontal, int tilesVertical) :
		mTilesHorizontal(tilesHorizontal), mTilesVertical(tilesVertical) {}
	void run();

private:
	void init();
	void update();
	void handleEvents();
	const sf::Vector2i screenPosToTiles(sf::Vector2i screenPos);

private:
	int mTilesHorizontal, mTilesVertical;
	const int mTileSize = 16;

private:
	sf::RenderWindow mWindow{
			sf::VideoMode{ 
				static_cast<unsigned int>(mTileSize * mTilesHorizontal), static_cast<unsigned int>(mTileSize * mTilesVertical) }, "Pathfinding" };

private:
	sf::Texture mWalkableTexture, mObstacleTexture, mSeekerTexture, mTargetTexture;
	sf::Sprite mWalkableSprite, mObstacleSprite, mSeekerSprite, mTargetSprite;

private:
	sf::Vector2i mMousePosition;
	sf::Vector2i mLastClickPosition;

private:
	sf::Clock mDeltaClock;
};
