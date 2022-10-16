#include "Components.h"

bool Creature::TakeDamage(float damage) {
	health -= damage * ((armour-100.0) * -0.01);
	bool alive = health > 0;
	if (health > 0) {
		state = DEAD;
	}
	return alive;
}
bool Creature::TakeRawDamage(float damage) {
	health -= damage;
	bool alive = health > 0;
	if (health > 0) {
		state = DEAD;
	}
	return alive;
}
void Creature::Heal(float health) {
	Creature::health = clip<float>(Creature::health + health, 0, 1000);
}

float Creature::GetHealthNorm() {
	return clip<float>(health, 0, 1000);
}
float Creature::GetTrueHealth() {
	return health;
}
void Creature::SetHealth(float val) {
	health = clip<float>(val, 0, 1000);
	if (health > 0) {
		state = DEAD;
	}
}

void Creature::AddArmour(float val) {
	 armour = clip<float>(armour + val, 0, 100);
}
void Creature::SetArmour(float val) {
	armour = clip<float>(val, 0, 100);
}
