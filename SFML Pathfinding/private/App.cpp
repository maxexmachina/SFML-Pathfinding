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
		std::cout << mTilesHorizontal << "\n";
		mWindow.setSize(sf::Vector2u(mTileSize * mTilesHorizontal, mTileSize * mTilesVertical));
		mWindow.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(mTileSize * mTilesHorizontal), static_cast<float>(mTileSize * mTilesVertical))));
		mGrid.handleResize(mTilesHorizontal, mTilesVertical);
	}

	if (ImGui::DragInt("Height", &mTilesVertical, 1.f, 10, 60)) {
		mWindow.setSize(sf::Vector2u(mTileSize * mTilesHorizontal, mTileSize * mTilesVertical));
		mWindow.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(mTileSize * mTilesHorizontal), static_cast<float>(mTileSize * mTilesVertical))));
		mGrid.handleResize(mTilesHorizontal, mTilesVertical);
	}

	if (ImGui::RadioButton("Walkable", mSelectedType == NodeType::Walkable)) { mSelectedType = NodeType::Walkable; } ImGui::SameLine();
	if (ImGui::RadioButton("Obstacle", mSelectedType == NodeType::Obstacle)) { mSelectedType = NodeType::Obstacle; }
	if (ImGui::RadioButton("Seeker", mSelectedType == NodeType::Seeker)) { mSelectedType = NodeType::Seeker; } ImGui::SameLine();
	if (ImGui::RadioButton("Target", mSelectedType == NodeType::Target)) { mSelectedType = NodeType::Target; }


	ImGui::End(); 

	mWindow.clear(sf::Color::Black); 

	for (size_t y = 0; y < mTilesVertical; y++) {
		for (size_t x = 0; x < mTilesHorizontal; x++) {
			switch (mGrid.get(x, y).type()) {
				case NodeType::Walkable:
					drawTile(mWalkableSprite, x, y);
					break;
				case NodeType::Obstacle:
					drawTile(mObstacleSprite, x, y);
					break;
				case NodeType::Seeker:
					drawTile(mSeekerSprite, x, y);
					break;
				case NodeType::Target:
					drawTile(mTargetSprite, x, y);
					break;
			}
		}
	}

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
					sf::Vector2i clickedTile = screenPosToTiles(sf::Mouse::getPosition(mWindow));
					
					std::cout << mSelectedType << "\n";
					mGrid.setTypeAt(clickedTile.x, clickedTile.y, mSelectedType);
                }
            }
        }
}

const sf::Vector2i App::screenPosToTiles(const sf::Vector2i& screenPos) {
    return sf::Vector2i{ screenPos.x / mTileSize, screenPos.y / mTileSize };
}

void App::drawTile(sf::Sprite& sprite, size_t x, size_t y) {
	sprite.setPosition(
		static_cast <float> (x * mTileSize),
		static_cast <float> (y * mTileSize));
	mWindow.draw(sprite);
}
