#ifndef __CVECTOR3_H__
#define __CVECTOR3_H__

namespace CZ4004
{
	class CVector3
	{
	public:
		CVector3();
		CVector3(float,float,float);
		void Normalize();
		float Length() const;
		float LengthSqrt() const;
		CVector3 * CrossProduct(const CVector3 * vector);
		CVector3 * Minus(CVector3 * vector);
		void Plus(CVector3 * vector);
		void Multiply(float multi);

	public:
		float x, y, z;
	};
}

#endif // __CVECTOR3_H__