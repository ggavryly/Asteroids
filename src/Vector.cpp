#include "Vector.hpp"

Vector::Vector() : x(0), y(0)
{}
Vector::Vector(float x, float y) : x(x), y(y)
{}
Vector::Vector(float angle)
{
	this->x = cosf(angleToRadian(angle));
	this->y = sinf(angleToRadian(angle));
}
Vector::Vector(Vector const & rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
}
Vector::~Vector()
{

}
float	Vector::length() const
{
	return sqrtf(x * x + y * y);
}
float	Vector::distanceTo(Vector const & rhs) const
{
	return (rhs - *this).length();
}
Vector &Vector::Vector::operator=(const Vector & rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}
Vector &Vector::Vector::operator+=(const Vector & rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}
Vector &Vector::operator-=(const Vector & rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}
Vector &Vector::operator/=(const Vector & rhs)
{
	this->x /= rhs.x;
	this->y /= rhs.y;
	return *this;
}
Vector &Vector::operator*=(const Vector & rhs)
{
	this->x *= rhs.x;
	this->y *= rhs.y;
	return *this;
}
Vector  Vector::normalization()
{
	return Vector(x / this->length(), y / this->length());
}

bool operator==(const Vector & lhs, const Vector & rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const Vector & lhs, const Vector & rhs)
{
	return !(rhs == lhs);
}
bool operator<(const Vector & lhs, const Vector & rhs)
{
	if (lhs.length() < rhs.length())
		return true;
	return false;
}
bool operator>(const Vector & lhs, const Vector & rhs)
{
	return rhs < lhs;
}
bool operator<=(const Vector & lhs, const Vector & rhs)
{
	return !(rhs < lhs);
}
bool operator>=(const Vector & lhs, const Vector & rhs)
{
	return !(lhs < rhs);
}
Vector operator+(const Vector & lhs, const Vector & rhs)
{
	return Vector(lhs.x + rhs.x, lhs.y + rhs.y);
}
Vector operator-(const Vector & lhs, const Vector & rhs)
{
	return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}
Vector operator/(const Vector & lhs, const Vector & rhs)
{
	return Vector(lhs.x / rhs.x, lhs.y / rhs.y);
}
Vector operator*(const Vector & lhs, const Vector & rhs)
{
	return Vector(lhs.x * rhs.x, lhs.y * rhs.y);
}
Vector operator+(const Vector & lhs, const float & rhs)
{
	return Vector(lhs.x + rhs, lhs.y + rhs);
}
Vector operator-(const Vector & lhs, const float & rhs)
{
	return Vector(lhs.x - rhs, lhs.y - rhs);
}
Vector operator/(const Vector & lhs, const float & rhs)
{
	return Vector(lhs.x / rhs, lhs.y / rhs);
}
Vector operator*(const Vector & lhs, const float & rhs)
{
	return Vector(lhs.x * rhs, lhs.y * rhs);
}

Vector operator-(const Vector &lhs)
{
	return Vector(-lhs.x, -lhs.y);
}

Vector operator+(const Vector &lhs)
{
	return Vector(abs(lhs.x), abs(lhs.y));
}

Vector Vector::abs(Vector vector)
{
	return Vector(fabsf(vector.x), fabsf(vector.y));
}

float Vector::angleVector(Vector const &rhs) const
{
	return this->scalarProduct(rhs) / (this->length() * rhs.length());
}

float Vector::scalarProduct(Vector const &rhs) const
{
	return (this->x * rhs.x + this->y * rhs.y);
}

std::ostream &operator<<(std::ostream &os, Vector const &v)
{
	os << "Vector {x = " << v.x << " | y = " << v.y << "}";
	return os;
}
