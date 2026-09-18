#pragma once
# include <Siv3D.hpp>

enum class LocationType
{
	Town,
	Castle,
};

class Location
{
protected:
	s3d::String m_name;
	s3d::Vec2 m_position;
	double m_interactionRange = 65.0;

public:
	Location(const s3d::String& name, const s3d::Vec2& position)
		: m_name(name)
		, m_position(position) {
	}

	virtual ~Location() = default;

	virtual LocationType getType() const = 0;
	virtual void draw(const s3d::Font& font) const = 0;
	virtual s3d::String getDescription() const = 0;

	bool isNear(const s3d::Vec2& playerPosition) const;
};
