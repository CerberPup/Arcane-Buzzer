#pragma once
class HasLife
{
public:
	int HP;
	int damageCooldown, damageCooldownReset;
	bool tookDamage;

	HasLife(int _hp, int _damageCoolDown);
	void TakeDamage();
	~HasLife();
};

