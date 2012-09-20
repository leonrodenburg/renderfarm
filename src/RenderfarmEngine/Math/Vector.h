#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_
#define DLLEX __declspec(dllexport)

#include <iostream>
#include "Utility.h"

namespace RFMath
{
	class DLLEX Vector
	{
	public:
		/**
		 * Constructors and destructor
		 */
		Vector();
		Vector(float x, float y, float z);
		virtual ~Vector();

		/**
		 * Methods
		 */
		bool IsZero() const;
		bool IsUnit() const;
		void Clean();

		float Length() const;
		float LengthSquared() const;
		Vector Normalize();

		float Dot(const Vector& vector) const;
		Vector Cross(const Vector& vector) const;

		/**
		 * Getters and setters
		 */
		float GetX() const { return _x; }
		float GetY() const { return _y; }
		float GetZ() const { return _z; }

		void Set(float x, float y, float z);
		void SetX(float x) { _x = x; }
		void SetY(float y) { _y = y; }
		void SetZ(float z) { _z = z; }

		/**
		 * Operators
		 */
		Vector operator-() const;
		Vector operator+(const Vector& vector) const;
		Vector operator+=(const Vector& vector);
		Vector operator-(const Vector& vector) const;
		Vector operator-=(const Vector& vector);
		Vector operator*(const float scalar) const;
		DLLEX friend Vector operator*(const float scalar, const Vector& vector);
		Vector operator*=(const float scalar);
		DLLEX friend std::ostream& operator<<(std::ostream& output, const Vector& vector);

	protected:
		float _x;
		float _y;
		float _z;
	};
}

#endif