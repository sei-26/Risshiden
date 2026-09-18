# include "Castle.hpp"
# include "Player.hpp"

LocationType Castle::getType() const
{
	return LocationType::Castle;
}

void Castle::draw(const s3d::Font& font) const
{
	const s3d::Rect castle{
		m_position.asPoint().movedBy(-50, -45),
		100,
		90
	};

	castle.draw(s3d::ColorF{ 0.30, 0.32, 0.38 });
	castle.drawFrame(3, s3d::Palette::White);

	font(m_name).drawAt(
		m_position.movedBy(0, 65),
		s3d::Palette::White
	);
}

s3d::String Castle::getDescription() const
{
	return U"清洲城。仕官や任務を受けられる。";
}

s3d::String Castle::applyForService(Player& player) const
{
	if (player.isRetainer())
	{
		return U"すでに主家へ仕官している。";
	}

	const int ability = (player.getMartial() + player.getFame());

	if (ability < 15)
	{
		return U"「武芸か名声が足りぬ」と、仕官を断られた。";
	}

	player.becomeRetainer();
	return U"才能を認められた。家臣として召し抱えられた！";
}

s3d::String Castle::performDuty(Player& player) const
{
	if (not player.isRetainer())
	{
		return U"仕官していないため、任務は受けられない。";
	}

	if (not player.consumeStamina(25))
	{
		return U"体力が足りず、任務に出られない。";
	}

	player.earnGold(40);
	player.addFame(2);

	return U"調査任務を果たした。40文と名声2を得た。";
}
