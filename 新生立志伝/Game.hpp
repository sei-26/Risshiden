#pragma once
# include <Siv3D.hpp>
# include <memory>
# include <vector>
# include "Player.hpp"
# include "Location.hpp"
# include "Town.hpp"
# include "GameDate.hpp"

enum class GameState
{
	Map,
	TownMenu,
	CastleMenu,
};

class Game
{
private:
	Player m_player;
	s3d::Font m_font{ 24 };
	std::vector<std::unique_ptr<Location>> m_locations;

	GameState m_state = GameState::Map;
	const Location* m_currentLocation = nullptr;
	const Town* m_currentTown = nullptr;
	GameDate m_date;

	s3d::String m_message = U"矢印キーで移動。町の近くで Space を押す。";

	void updateMap();
	void updateTownMenu();
	void drawMap() const;
	void drawTownMenu() const;
	void updateCastleMenu();
	void drawCastleMenu() const;
	void advanceTime();
public:
	Game();

	void update();
	void draw() const;
};
