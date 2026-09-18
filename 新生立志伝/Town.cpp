# include "Town.hpp"
# include "Player.hpp"

LocationType Town::getType() const
{
	return LocationType::Town;
}

void Town::draw(const s3d::Font& font) const
{
	const s3d::Circle town{ m_position, 42 };

	town.draw(s3d::ColorF{ 0.72, 0.42, 0.22 });
	town.drawFrame(3, s3d::Palette::White);

	font(m_name).drawAt(
		m_position.movedBy(0, 65),
		s3d::Palette::White
	);
}

s3d::String Town::getDescription() const
{
	return U"町に入った。商い、宿、道場を利用できる。";
}

s3d::String Town::work(Player& player) const
{
	if (not player.consumeStamina(20))
	{
		return U"体力が足りず、働けない。";
	}

	player.earnGold(30);
	return U"商家で働き、30文を得た。体力を20使った。";
}

s3d::String Town::rest(Player& player) const
{
	constexpr int innCost = 15;

	if (not player.spendGold(innCost))
	{
		return U"宿代の15文が足りない。";
	}

	player.restoreStamina(50);
	return U"宿で休んだ。体力が50回復した。";
}

s3d::String Town::train(Player& player) const
{
	constexpr int trainingCost = 20;

	if (not player.spendGold(trainingCost))
	{
		return U"稽古代の20文が足りない。";
	}

	if (not player.consumeStamina(15))
	{
		player.earnGold(trainingCost);
		return U"体力が足りず、稽古できない。";
	}

	player.improveMartial(1);
	return U"道場で稽古した。武芸が1上がった。";
}
