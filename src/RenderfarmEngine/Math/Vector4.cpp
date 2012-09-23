#include "Vector4.h"

/**
 * Static defaults
 */
RFMath::Vector4 RFMath::Vector4::xAxis(1.0f, 0.0f, 0.0f, 0.0f);
RFMath::Vector4 RFMath::Vector4::yAxis(0.0f, 1.0f, 0.0f, 0.0f);
RFMath::Vector4 RFMath::Vector4::zAxis(0.0f, 0.0f, 1.0f, 0.0f);
RFMath::Vector4 RFMath::Vector4::wAxis(0.0f, 0.0f, 0.0f, 1.0f);
RFMath::Vector4 RFMath::Vector4::origin(0.0f, 0.0f, 0.0f, 0.0f);

/**
 * Default constructor
 */
RFMath::Vector4::Vector4()
{
	this->_x = 0.0f;
	this->_y = 0.0f;
	this->_z = 0.0f;
	this->_w = 0.0f;
}

/**
 * Constructor, setting values for x, y, z and w.
 * 
 * @param x
 * @param y
 * @param z
 * @param w
 */
RFMath::Vector4::Vector4(float x, float y, float z, float w)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
	this->_w = w;
}

/**
 * Copy constructor.
 *
 * @param other
 */
RFMath::Vector4::Vector4(const Vector4& vector)
{
	this->_x = vector._x;
	this->_y = vector._y;
	this->_z = vector._z;
	this->_w = vector._w;
}

/**
 * Destructor
 */
RFMath::Vector4::~Vector4()
{

}

/**
 * Return whether or not the vector is a zero vector.
 *
 * @return True if zero, false if not
 */
bool RFMath::Vector4::IsZero() const
{
	return RFMathIsZero(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w);
}

/**
 * Return whether or not the vector is of unit length 
 * (length = 1.0f)
 *
 * @return True if unit, false if not
 */
bool RFMath::Vector4::IsUnit() const
{
	return RFMathIsZero(1.0f - (this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w));
}

/**
 * Set components close to zero to zero.
 */
void RFMath::Vector4::Clean()
{
	if(RFMathIsZero(this->_x))
	{
		this->_x = 0.0f;
	}

	if(RFMathIsZero(this->_y))
	{
		this->_y = 0.0f;
	}

	if(RFMathIsZero(this->_z))
	{
		this->_z = 0.0f;
	}

	if(RFMathIsZero(this->_w))
	{
		this->_w = 0.0f;
	}
}

/**
 * Calculate and return the length of the vector.
 *
 * @return Length of vector
 */
float RFMath::Vector4::Length() const
{
	return sqrtf(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w);
}

/**
 * Calculate and return the squared length of the
 * vector.
 *
 * @return Squared length of vector
 */
float RFMath::Vector4::LengthSquared() const
{
	return this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w;
}

/**
 * Normalize the vector and return it.
 *
 * @return Normalized vector
 */
RFMath::Vector4 RFMath::Vector4::Normalize()
{
	float lengthSquared = this->LengthSquared();
	if(RFMathIsZero(lengthSquared))
	{
		this->_x = 0;
		this->_y = 0;
		this->_z = 0;
		this->_w = 0;
		return *this;
	}

	float reciprocal = RFMathInvSqrt(lengthSquared);
	this->_x *= reciprocal;
	this->_y *= reciprocal;
	this->_z *= reciprocal;
	this->_w *= reciprocal;
	return *this;
}

/**
 * Calculate the dot product for this and a given
 * vector.
 *
 * @param vector
 *
 * @return Dot product
 */
float RFMath::Vector4::Dot(const Vector4& vector) const
{
	return (this->_x * vector._x, this->_y * vector._y, this->_z * vector._z);
}

/**
 * Set all components of the vector.
 *
 * @param x
 * @param y
 * @param z
 */
void RFMath::Vector4::Set(float x, float y, float z, float w)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
	this->_w = w;
}

/**
 * Assignment operator.
 *
 * @param vector
 *
 * @return Modified vector
 */
RFMath::Vector4 RFMath::Vector4::operator=(const Vector4& vector)
{
	if(this == &vector)
	{
		return *this;
	}

	this->_x = vector._x;
	this->_y = vector._y;
	this->_z = vector._z;
	this->_w = vector._w;

	return *this;
}

/**
 * Unary minus operator overload, letting the vector point in
 * opposite direction.
 *
 * @return New vector in opposite direction
 */
RFMath::Vector4 RFMath::Vector4::operator-() const
{
	return Vector4(-this->_x, -this->_y, -this->_z, -this->_w);
}

/**
 * Addition operator overload.
 *
 * @param vector
 *
 * @return New vector with added components
 */
RFMath::Vector4 RFMath::Vector4::operator+(const Vector4& vector) const
{
	return Vector4(this->_x + vector._x, this->_y + vector._y, this->_z + vector._z, this->_w + vector._w);
}

/**
 * Addition assignment operator overload, adding components of
 * vector to self.
 *
 * @param vector
 *
 * @return Same vector with modified components
 */
RFMath::Vector4 RFMath::Vector4::operator+=(const Vector4& vector)
{
	this->_x += vector._x;
	this->_y += vector._y;
	this->_z += vector._z;
	this->_w += vector._w;

	return *this;
}

/**
 * Subtraction operator overload.
 *
 * @param vector
 *
 * @return New vector with subtracted components
 */
RFMath::Vector4 RFMath::Vector4::operator-(const Vector4& vector) const
{
	return Vector4(this->_x - vector._x, this->_y - vector._y, this->_z - vector._z, this->_w - vector._w);
}

/**
 * Subtraction assignment operator overload, subtracting components of
 * vector from self.
 *
 * @param vector
 * 
 * @return Same vector with modified components
 */
RFMath::Vector4 RFMath::Vector4::operator-=(const Vector4& vector)
{
	this->_x -= vector._x;
	this->_y -= vector._y;
	this->_z -= vector._z;
	this->_w -= vector._w;

	return *this;
}

/**
 * Scalar multiplication overload
 *
 * @param scalar
 *
 * @return New vector with multiplied components
 */
RFMath::Vector4 RFMath::Vector4::operator*(const float scalar) const
{
	return Vector4(this->_x * scalar, this->_y * scalar, this->_z * scalar, this->_w * scalar);
}

/**
 * Scalar multiplication overload
 *
 * @param vector
 * @param scalar
 *
 * @return New vector with multiplied components
 */
DLLEX RFMath::Vector4 RFMath::operator*(const float scalar, const Vector4& vector)
{
	return Vector4(vector._x * scalar, vector._y * scalar, vector._z * scalar, vector._w * scalar);
}

/**
 * Multiplication assign operator overload, multiplying vector
 * by a scalar;
 *
 * @param scalar
 *
 * @return Same vector with modified components
 */
RFMath::Vector4 RFMath::Vector4::operator*=(const float scalar)
{
	this->_x *= scalar;
	this->_y *= scalar;
	this->_z *= scalar;
	this->_w *= scalar;
	return *this;
}

/**
 * Array access operator.
 *
 * @param i
 *
 * @return The corresponding component
 */
float RFMath::Vector4::operator[](unsigned int i) const
{
	return (&(this->_x))[i];
}

/**
 * Test whether two vectors are equal.
 *
 * @param vector
 *
 * @return True if equal, false if not
 */
bool RFMath::Vector4::operator==(const Vector4& vector) const
{
	return RFMathIsEqual(this->_x, vector._x)
		&& RFMathIsEqual(this->_y, vector._y)
		&& RFMathIsEqual(this->_z, vector._z)
		&& RFMathIsEqual(this->_w, vector._w);	
}

/**
 * Output stream operator overload
 *
 * @param output
 * @param vector
 *
 * @return Output stream
 */
DLLEX std::ostream& RFMath::operator<<(std::ostream& output, const Vector4& vector)
{
	output << "Vector4 { " << vector._x << ", " << vector._y << ", " << vector._z << ", " << vector._w << " }" << std::endl;
	return output;
}