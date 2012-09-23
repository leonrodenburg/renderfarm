#pragma once

#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <iostream>
#include "Utility.h"

namespace RFMath
{
	class Matrix;

	class DLLEX Vector4
	{
	public:
		/**
		 * Constructors and destructor
		 */
		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector4& vector);
		virtual ~Vector4();

		/**
		 * Methods
		 */
		bool IsZero() const;
		bool IsUnit() const;
		void Clean();

		float Length() const;
		float LengthSquared() const;
		Vector4 Normalize();

		float Dot(const Vector4& vector) const;

		/**
		 * Getters and setters
		 */
		float GetX() const { return this->_x; }
		float GetY() const { return this->_y; }
		float GetZ() const { return this->_z; }
		float GetW() const { return this->_w; }

		void Set(float x, float y, float z, float w);
		void SetX(float x) { this->_x = x; }
		void SetY(float y) { this->_y = y; }
		void SetZ(float z) { this->_z = z; }
		void SetW(float w) { this->_w = w; }

		/**
		 * Operators
		 */
		Vector4 operator=(const Vector4& vector);
		Vector4 operator-() const;
		Vector4 operator+(const Vector4& vector) const;
		Vector4 operator+=(const Vector4& vector);
		Vector4 operator-(const Vector4& vector) const;
		Vector4 operator-=(const Vector4& vector);
		Vector4 operator*(const float scalar) const;
		DLLEX friend Vector4 operator*(const float scalar, const Vector4& vector);
		Vector4 operator*=(const float scalar);
		float operator[](unsigned int i) const;
		bool operator==(const Vector4& vector) const;
		DLLEX friend std::ostream& operator<<(std::ostream& output, const Vector4& vector);

		/**
		 * Defaults
		 */
		static Vector4 xAxis;
		static Vector4 yAxis;
		static Vector4 zAxis;
		static Vector4 wAxis;
		static Vector4 origin;

	protected:
		float _x;
		float _y;
		float _z;
		float _w;
	};
}

#endif