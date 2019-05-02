#pragma once
#include "Shape.h"
class Square :
	public Shape
{
public:
	Square();
	Square(const Square& s) {};


	~Square();
};

