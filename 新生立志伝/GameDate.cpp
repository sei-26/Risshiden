# include "GameDate.hpp"

bool GameDate::nextMonth()
{
	++m_month;

	if (m_month > 12)
	{
		m_month = 1;
		++m_year;
		return true;
	}

	return false;
}

int GameDate::getYear() const
{
	return m_year;
}

int GameDate::getMonth() const
{
	return m_month;
}

Season GameDate::getSeason() const
{
	if (m_month >= 3 && m_month <= 5)
	{
		return Season::Spring;
	}

	if (m_month >= 6 && m_month <= 8)
	{
		return Season::Summer;
	}

	if (m_month >= 9 && m_month <= 11)
	{
		return Season::Autumn;
	}

	return Season::Winter;
}

s3d::String GameDate::getSeasonText() const
{
	switch (getSeason())
	{
	case Season::Spring:
		return U"春";

	case Season::Summer:
		return U"夏";

	case Season::Autumn:
		return U"秋";

	case Season::Winter:
		return U"冬";
	}

	return U"";
}

s3d::String GameDate::getText() const
{
	return U"{}年 {}月"_fmt(m_year, m_month);
}
