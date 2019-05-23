#pragma once
#include "Vector2.h"

#include <iostream>


class MaterialPoint{
public:
	double mass;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	MaterialPoint();

	void UpdatePosition(double dt);
	Vector2 GetImpulse() const;
};

class Ball : public MaterialPoint{
public:
	float radius;
	int type;

	Ball();
};

MaterialPoint::MaterialPoint() 
{
	mass = 1;
	acceleration = Vector2(0, 0);
	velocity = Vector2(rand() % 400 - 200 , rand() % 400 - 200);
	position = Vector2(0, 0);
}

void MaterialPoint::UpdatePosition(double dt) 
{
	position += velocity * dt;
}

Vector2 MaterialPoint::GetImpulse() const 
{
	return Vector2(velocity * mass);
}

Ball::Ball()
{
	radius = 5;
	type = 1;

	position = Vector2(radius + 1, radius + 1);
}
