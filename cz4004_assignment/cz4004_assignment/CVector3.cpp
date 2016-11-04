#include <cmath>

#include "CVector3.h"

using namespace CZ4004;

CVector3::CVector3()
	:x(0.0f), y(0.0f), z(0.0f)
{
}

CVector3::CVector3(float px, float py, float pz)
	:x(px), y(py), z(pz)
{
}

void CVector3::Set(float px, float py, float pz)
{
	x = px; y = py; z = pz;
}

void CVector3::Normalize()
{
	float l = Length();
	this->x /= l;
	this->y /= l;
	this->z /= l;
}

void CVector3::Negative()
{
	this->x *= -1;
	this->y *= -1;
	this->z *= -1;
}

float CVector3::Length() const
{
	return sqrt(this->LengthSqrt());
}

float CVector3::LengthSqrt() const
{
	return (x*x + y*y + z*z);
}

CVector3 * CVector3::CrossProduct(const CVector3 * vector)
{
	// Notice: the sequence of two vectors
	CVector3 * new_vec = new CVector3();
	new_vec->x = this->y * vector->z - this->z * vector->y;
	new_vec->y = this->z * vector->x - this->x * vector->z;
	new_vec->z = this->x * vector->y - this->y * vector->x;
	return new_vec;
}

CVector3 * CVector3::Minus(CVector3 * vector)
{
	CVector3 * new_vec = new CVector3();
	new_vec->x = this->x - vector->x;
	new_vec->y = this->y - vector->y;
	new_vec->z = this->z - vector->z;
	return new_vec;
}

void CVector3::Plus(CVector3 * vector)
{
	this->x += vector->x;
	this->y += vector->y;
	this->z += vector->z;
}

void CVector3::Multiply(float multi)
{
	this->x *= multi;
	this->y *= multi;
	this->z *= multi;
}