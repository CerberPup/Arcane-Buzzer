#pragma once
class Animable
{
public:
	Animable();
	virtual ~Animable();
	virtual void Update() = 0;
};

