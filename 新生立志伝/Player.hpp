#pragma once
# include <Siv3D.hpp>

class Player
{
private:
	s3d::Vec2 m_position{ 400, 300 };
	double m_speed = 220.0; // 1秒あたりの移動量（ピクセル）

	int m_gold = 100;
	int m_stamina = 100;
	int m_martial = 10;
	int m_fame = 0;
	bool m_isRetainer = false;
	int m_age = 17;

public:
	void update();
	void draw() const;
	void drawStatus(const s3d::Font& font) const;
	int getAge() const;
	void growOlder();

	const s3d::Vec2& getPosition() const;

	int getGold() const;
	int getStamina() const;
	int getMartial() const;

	void earnGold(int amount);
	bool spendGold(int amount);

	bool consumeStamina(int amount);
	void restoreStamina(int amount);

	void improveMartial(int amount);

	int getFame() const;
	bool isRetainer() const;

	void addFame(int amount);
	void becomeRetainer();
};
