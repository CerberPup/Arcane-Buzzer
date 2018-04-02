#pragma once
class Animable
{
private:
	

public:
	int offset;
	int animationcounter;
	Animable();
	virtual ~Animable();
	virtual void Update() = 0;
};

