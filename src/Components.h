#pragma once
#include "Types.h"
#include "Math.h"
#include <cstdint>
#include <vector>
#include "Dialog.h"

struct Renderer {
	bool active{false};
};
struct Transform {
	Vec2 position;
	float rotation{0};
	Vec2 scale;
};
struct RigidBody
{
	Vec2 gravity;
	Vec2 velocity;
	bool debug{false};
	//bool sleeping;
	//TODO
};
struct Creature
{
	std::string name;
	float health = 100;
	float armour = 0;
	CreatureState state = UNACTIVE;

	bool TakeDamage(float damage);
	bool TakeRawDamage(float damage);
	void Heal(float health);

	//Returns health clamped between 0 and 1000
	float GetHealthNorm();
	//Returns health unclamped
	float GetTrueHealth();
	//Sets healths, clamped between 0-1000
	void SetHealth(float val);

	void AddArmour(float val);
	void SetArmour(float val);

};

struct NPC : Creature{
	int16_t relationship;

	Dialog dialog;

	std::string cool = "s";

	NPC(std::string name, float health, float armour, CreatureState = UNACTIVE) {
		this->name = name;
		this->health = health;
		this->armour = armour;

		dialog = Dialog(name);
	}

};

