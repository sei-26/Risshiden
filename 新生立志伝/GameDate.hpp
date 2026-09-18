#pragma once
# include <Siv3D.hpp>

enum class Season
{
	Spring,
	Summer,
	Autumn,
	Winter,
};

class GameDate
{
private:
	int m_year = 1560;
	int m_month = 1;

public:
	// 年が変わった場合は true を返す
	bool nextMonth();

	int getYear() const;
	int getMonth() const;

	Season getSeason() const;
	s3d::String getSeasonText() const;
	s3d::String getText() const;
};
