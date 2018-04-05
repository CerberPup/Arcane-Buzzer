#pragma once
class Animable
{
public:
	int animation; //Use enum for var
	int animationcounter;
	virtual bool canAnimate() = 0;
	virtual ~Animable();
	virtual void Update() = 0;
};

