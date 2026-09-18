#pragma once
# include "Location.hpp"

class Player;

class Town : public Location
{
public:
	Town(const s3d::String& name, const s3d::Vec2& position)
		: Location(name, position) {
	}

	LocationType getType() const override;
	void draw(const s3d::Font& font) const override;
	s3d::String getDescription() const override;

	s3d::String work(Player& player) const;
	s3d::String rest(Player& player) const;
	s3d::String train(Player& player) const;
};
