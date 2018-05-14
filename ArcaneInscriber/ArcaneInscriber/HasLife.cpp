#include "HasLife.h"



HasLife::HasLife(int _hp,int _damageCoolDown):HP(_hp), damageCooldownReset(_damageCoolDown)
{
	damageCooldown = 0;
}

void HasLife::TakeDamage()
{
	if (!tookDamage){
		tookDamage = true;
		HP--;
		damageCooldown = damageCooldownReset;
	}
}

HasLife::~HasLife()
{
}
