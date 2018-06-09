#pragma once
//!Class for inherence of objects that have life.
class HasLife
{
public:
	//!Health points left.
	int HP;
	//!Number of ticks until object can take damage again.
	int damageCooldown;
	//!Number of ticks of invulnerability of object.
	int damageCooldownReset;
	//!Used to lock taking damage for period of ticks.
	bool tookDamage;
	//!Initialize HP and damageCooldownReset variable.
	HasLife(int _hp, int _damageCoolDown);
	//!Decrese HP and lock tooking damage.
	void TakeDamage();
	~HasLife();
};

