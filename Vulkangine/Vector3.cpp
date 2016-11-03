#include "Vector3.h"

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Vector3 * vec)
{
	this->x = vec->x;
	this->y = vec->y;
	this->z = vec->z;
}

void Vector3::add(Vector3 * vec)
{
	this->x += vec->x;
	this->y += vec->y;
	this->z += vec->z;
}

Vector3::Vector3()
{
	this->x = this->y = this->z = 0;
}

std::string Vector3::toString()
{
	std::stringstream ss;
	ss << "{\"x\":"<<x<<",\"y\":"<<y<<",\"z\":"<<z<<"}";
	return ss.str();
}



Vector3 Vector3::operator+(const Vector3 & other)
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator*(const float & other)
{
	return Vector3(this->x * other, this->y * other, this->z * other);
	
}
