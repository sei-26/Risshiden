# include "Game.hpp"
# include "Town.hpp"
# include "Castle.hpp"

Game::Game()
{
	m_locations.push_back(
		std::make_unique<Castle>(U"清洲城", s3d::Vec2{ 150, 300 })
	);

	m_locations.push_back(
		std::make_unique<Town>(U"清洲の町", s3d::Vec2{ 650, 300 })
	);
}

void Game::update()
{
	if (m_state == GameState::Map)
	{
		updateMap();
	}
	else if (m_state == GameState::TownMenu)
	{
		updateTownMenu();
	}
	else if (m_state == GameState::CastleMenu)
	{
		updateCastleMenu();
	}
}

void Game::updateMap()
{
	m_player.update();

	if (s3d::KeySpace.down())
	{
		for (const auto& location : m_locations)
		{
			if (not location->isNear(m_player.getPosition()))
			{
				continue;
			}

			m_currentLocation = location.get();

			if (location->getType() == LocationType::Town)
			{
				m_state = GameState::TownMenu;
			}
			else if (location->getType() == LocationType::Castle)
			{
				m_state = GameState::CastleMenu;
			}

			return;
		}

		m_message = U"近くに入れる場所はない。";
	}
}

void Game::updateTownMenu()
{
	if (s3d::Key1.down())
	{
		m_message = m_currentTown->work(m_player);
		advanceTime();
	}
	else if (s3d::Key2.down())
	{
		m_message = m_currentTown->rest(m_player);
		advanceTime();
	}
	else if (s3d::Key3.down())
	{
		m_message = m_currentTown->train(m_player);
		advanceTime();
	}
	else if (s3d::Key0.down() || s3d::KeyEscape.down())
	{
		m_currentLocation = nullptr;
		m_state = GameState::Map;
		m_message = U"マップへ戻った。";
	}
}

void Game::draw() const
{
	drawMap();

	if (m_state == GameState::TownMenu)
	{
		drawTownMenu();
	}
	else if (m_state == GameState::CastleMenu)
	{
		drawCastleMenu();
	}

}	

void Game::drawMap() const
{
	s3d::ColorF fieldColor;

	switch (m_date.getSeason())
	{
	case Season::Spring:
		fieldColor = s3d::ColorF{ 0.45, 0.70, 0.38 };
		break;

	case Season::Summer:
		fieldColor = s3d::ColorF{ 0.25, 0.55, 0.22 };
		break;

	case Season::Autumn:
		fieldColor = s3d::ColorF{ 0.62, 0.48, 0.20 };
		break;

	case Season::Winter:
		fieldColor = s3d::ColorF{ 0.68, 0.76, 0.78 };
		break;
	}

	// 地面
	s3d::Rect{ 0, 0, 800, 600 }.draw(fieldColor);

	// 道
	s3d::Line{ 80, 300, 720, 300 }
	.draw(24, s3d::ColorF{ 0.66, 0.53, 0.33 });

	// 町・城
	for (const auto& location : m_locations)
	{
		location->draw(m_font);
	}

	// 主人公
	m_player.draw();

	// 上部メッセージ
	s3d::Rect{ 0, 0, 800, 55 }
	.draw(s3d::ColorF{ 0.10, 0.12, 0.18 });

	m_font(m_message).draw(15, 14, s3d::Palette::White);

	// 主人公の能力と日付
	m_player.drawStatus(m_font);

	m_font(U"{}・{}"_fmt(
		m_date.getText(),
		m_date.getSeasonText()
	)).draw(620, 62, s3d::Palette::White);
}

void Game::drawTownMenu() const
{
	s3d::Rect{ 130, 120, 540, 360 }
	.draw(s3d::ColorF{ 0.08, 0.10, 0.15, 0.94 });

	s3d::Rect{ 130, 120, 540, 360 }
	.drawFrame(3, s3d::Palette::White);

	m_font(m_currentLocation->getDescription())
		.drawAt(400, 170, s3d::Palette::White);

	m_font(U"1：商家で働く").draw(200, 240, s3d::Palette::White);
	m_font(U"2：宿で休む").draw(200, 290, s3d::Palette::White);
	m_font(U"3：道場で稽古する").draw(200, 340, s3d::Palette::White);
	m_font(U"0 または Esc：町を出る").draw(200, 410, s3d::Palette::Lightgray);
}

void Game::updateCastleMenu()
{
	const auto* castle = dynamic_cast<const Castle*>(m_currentLocation);

	if (castle == nullptr)
	{
		m_state = GameState::Map;
		return;
	}

	if (s3d::Key1.down())
	{
		m_message = castle->applyForService(m_player);
		advanceTime();
	}
	else if (s3d::Key2.down())
	{
		m_message = castle->performDuty(m_player);
		advanceTime();
	}
	else if (s3d::Key0.down() || s3d::KeyEscape.down())
	{
		m_currentLocation = nullptr;
		m_state = GameState::Map;
		m_message = U"城を出て、マップへ戻った。";
	}
}
void Game::drawCastleMenu() const
{
	s3d::Rect{ 130, 120, 540, 360 }
	.draw(s3d::ColorF{ 0.08, 0.10, 0.15, 0.94 });

	s3d::Rect{ 130, 120, 540, 360 }
	.drawFrame(3, s3d::Palette::White);

	m_font(U"清洲城").drawAt(400, 170, s3d::Palette::White);

	m_font(U"1：仕官を願い出る").draw(200, 240, s3d::Palette::White);
	m_font(U"2：任務を受ける").draw(200, 300, s3d::Palette::White);
	m_font(U"0 または Esc：城を出る").draw(200, 410, s3d::Palette::Lightgray);
}
void Game::advanceTime()
{
	const bool isNewYear = m_date.nextMonth();

	m_message += U"\n時は {} へ進んだ。"_fmt(m_date.getText());

	if (isNewYear)
	{
		m_player.growOlder();

		m_message += U"\n{}歳になった。"_fmt(
			m_player.getAge()
		);
	}
}
