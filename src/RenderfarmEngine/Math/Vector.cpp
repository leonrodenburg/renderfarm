#include "Vector.h"

RFMath::Vector::Vector()
{
	this->_x = 0.0f;
	this->_y = 0.0f;
	this->_z = 0.0f;
}

RFMath::Vector::Vector(float x, float y, float z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

RFMath::Vector::~Vector()
{

}