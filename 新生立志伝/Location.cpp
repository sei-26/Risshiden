# include "Location.hpp"

bool Location::isNear(const s3d::Vec2& playerPosition) const
{
	return (m_position.distanceFrom(playerPosition) <= m_interactionRange);
}
