# include "Player.hpp"

void Player::update()
{
	// キーを押している間、主人公の座標を動かす
	if (s3d::KeyLeft.pressed())
	{
		m_position.x -= (m_speed * s3d::Scene::DeltaTime());
	}

	if (s3d::KeyRight.pressed())
	{
		m_position.x += (m_speed * s3d::Scene::DeltaTime());
	}

	if (s3d::KeyUp.pressed())
	{
		m_position.y -= (m_speed * s3d::Scene::DeltaTime());
	}

	if (s3d::KeyDown.pressed())
	{
		m_position.y += (m_speed * s3d::Scene::DeltaTime());
	}

	// 画面外へ出ないようにする
	m_position.x = s3d::Clamp(m_position.x, 20.0, 780.0);
	m_position.y = s3d::Clamp(m_position.y, 80.0, 580.0);
}

void Player::draw() const
{
	// オレンジの円を主人公として描画
	s3d::Circle{ m_position, 18 }.draw(s3d::Palette::Orange);
	s3d::Circle{ m_position, 18 }.drawFrame(3, s3d::Palette::White);
}

const s3d::Vec2& Player::getPosition() const
{
	return m_position;
}

int Player::getGold() const
{
	return m_gold;
}

int Player::getStamina() const
{
	return m_stamina;
}

int Player::getMartial() const
{
	return m_martial;
}

void Player::earnGold(const int amount)
{
	m_gold += amount;
}

bool Player::spendGold(const int amount)
{
	if (m_gold < amount)
	{
		return false;
	}

	m_gold -= amount;
	return true;
}

bool Player::consumeStamina(const int amount)
{
	if (m_stamina < amount)
	{
		return false;
	}

	m_stamina -= amount;
	return true;
}

void Player::restoreStamina(const int amount)
{
	m_stamina = s3d::Min(m_stamina + amount, 100);
}

void Player::improveMartial(const int amount)
{
	m_martial += amount;
}

void Player::drawStatus(const s3d::Font& font) const
{
	font(U"金: {}　体力: {}　武芸: {}"_fmt(
		m_gold, m_stamina, m_martial
	)).draw(15, 62, s3d::Palette::White);
}
// Player.cpp に追加
int Player::getFame() const
{
	return m_fame;
}

bool Player::isRetainer() const
{
	return m_isRetainer;
}

void Player::addFame(const int amount)
{
	m_fame += amount;
}

void Player::becomeRetainer()
{
	m_isRetainer = true;
}
int Player::getAge() const
{
	return m_age;
}

void Player::growOlder()
{
	++m_age;
}
