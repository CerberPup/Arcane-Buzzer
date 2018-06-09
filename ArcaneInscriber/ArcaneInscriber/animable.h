#pragma once
//!Base clase for enabling object animation 
class Animable
{
public:
	//!Current animation.
	int animation; //Use enum for var.
	//!Current frame in animation.
	int animationcounter;
	//!Determine if animation is over.
	/*!
	\return true if animation is over.
	*/
	virtual bool canAnimate() = 0;
	//!Changes sprite based on animation and animationcounter.	
	virtual void Update() = 0;
	virtual ~Animable();
};

