#include "../public/App.hpp"

void App::init() {
    mWindow.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(mWindow);

    mWalkableTexture.loadFromFile("textures/white.png");
    mTargetTexture.loadFromFile("textures/red.png");
    mSeekerTexture.loadFromFile("textures/green.png");
    mObstacleTexture.loadFromFile("textures/black.png");

    mWalkableSprite = sf::Sprite(mWalkableTexture);
    mTargetSprite = sf::Sprite(mTargetTexture);
    mSeekerSprite = sf::Sprite(mSeekerTexture);
    mObstacleSprite = sf::Sprite(mObstacleTexture);
}

void App::update() {
	handleEvents();
	ImGui::SFML::Update(mWindow, mDeltaClock.restart());

	ImGui::Begin("Grid editor"); 

	if (ImGui::DragInt("Width", &mTilesHorizontal, 1.f, 10, 60)) {
		mWindow.setSize(sf::Vector2u(mTileSize * mTilesHorizontal, mTileSize * mTilesVertical));
		mWindow.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(mTileSize * mTilesHorizontal), static_cast<float>(mTileSize * mTilesVertical))));
	}

	if (ImGui::DragInt("Height", &mTilesVertical, 1.f, 10, 60)) {
		mWindow.setSize(sf::Vector2u(mTileSize * mTilesHorizontal, mTileSize * mTilesVertical));
		mWindow.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(mTileSize * mTilesHorizontal), static_cast<float>(mTileSize * mTilesVertical))));
	}

	ImGui::End(); 

	mWindow.clear(sf::Color::Black); 

	for (std::size_t i = 0; i < mTilesHorizontal; ++i) {
		for (std::size_t j = 0; j < mTilesVertical; ++j) {
			mWalkableSprite.setPosition(
				static_cast <float> (i * mTileSize),
				static_cast <float> (j * mTileSize));

			mWindow.draw(mWalkableSprite);
		}
	}

	sf::Vector2i clickedTile = screenPosToTiles(mLastClickPosition);
	mObstacleSprite.setPosition(
		static_cast <float> (clickedTile.x * mTileSize),
		static_cast <float> (clickedTile.y * mTileSize));

	mWindow.draw(mObstacleSprite);

	ImGui::SFML::Render(mWindow);
	mWindow.display();
}

void App::run() {
	init();
	while (mWindow.isOpen()) {
		update();
	}
	ImGui::SFML::Shutdown();
}

void App::handleEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed) {
			mWindow.close();
		}

		if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    mWindow.close();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Right) {
					mMousePosition = sf::Mouse::getPosition(mWindow);
                    mLastClickPosition = mMousePosition;
                }
            }

        }
}

const sf::Vector2i App::screenPosToTiles(sf::Vector2i screenPos) {
    return sf::Vector2i{ screenPos.x / mTileSize, screenPos.y / mTileSize };
}
