#pragma once
# include "Location.hpp"

// Player.cpp を読み込まず、Player というクラスが存在することだけを伝える
class Player;

class Castle : public Location
{
public:
	Castle(const s3d::String& name, const s3d::Vec2& position)
		: Location(name, position)
	{
	}

	LocationType getType() const override;
	void draw(const s3d::Font& font) const override;
	s3d::String getDescription() const override;

	s3d::String applyForService(Player& player) const;
	s3d::String performDuty(Player& player) const;
};
