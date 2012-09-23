#include "Vector3.h"

/**
 * Static defaults.
 */
RFMath::Vector3 RFMath::Vector3::xAxis(1.0f, 0.0f, 0.0f);
RFMath::Vector3 RFMath::Vector3::yAxis(0.0f, 1.0f, 0.0f);
RFMath::Vector3 RFMath::Vector3::zAxis(0.0f, 0.0f, 1.0f);
RFMath::Vector3 RFMath::Vector3::origin(0.0f, 0.0f, 0.0f);

/**
 * Default constructor.
 */
RFMath::Vector3::Vector3()
{
	this->_x = 0.0f;
	this->_y = 0.0f;
	this->_z = 0.0f;
}

/**
 * Constructor, setting values for x, y and z.
 * 
 * @param x
 * @param y
 * @param z
 */
RFMath::Vector3::Vector3(float x, float y, float z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

/**
 * Copy constructor.
 *
 * @param other
 */
RFMath::Vector3::Vector3(const Vector3& vector)
{
	this->_x = vector._x;
	this->_y = vector._y;
	this->_z = vector._z;
}

/**
 * Destructor
 */
RFMath::Vector3::~Vector3()
{

}

/**
 * Return whether or not the vector is a zero vector.
 *
 * @return True if zero, false if not
 */
bool RFMath::Vector3::IsZero() const
{
	return RFMathIsZero(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}

/**
 * Return whether or not the vector is of unit length 
 * (length = 1.0f)
 *
 * @return True if unit, false if not
 */
bool RFMath::Vector3::IsUnit() const
{
	return RFMathIsZero(1.0f - (this->_x * this->_x + this->_y * this->_y + this->_z * this->_z));
}

/**
 * Set components close to zero to zero.
 */
void RFMath::Vector3::Clean()
{
	if(RFMathIsZero(_x))
	{
		this->_x = 0.0f;
	}

	if(RFMathIsZero(_y))
	{
		this->_y = 0.0f;
	}

	if(RFMathIsZero(_z))
	{
		this->_z = 0.0f;
	}
}

/**
 * Calculate and return the length of the vector.
 *
 * @return Length of vector
 */
float RFMath::Vector3::Length() const
{
	return sqrtf(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}

/**
 * Calculate and return the squared length of the
 * vector.
 *
 * @return Squared length of vector
 */
float RFMath::Vector3::LengthSquared() const
{
	return this->_x * this->_x + this->_y * this->_y + this->_z * this->_z;
}

/**
 * Normalize the vector and return it.
 *
 * @return Normalized vector
 */
RFMath::Vector3 RFMath::Vector3::Normalize()
{
	float lengthSquared = this->LengthSquared();
	if(RFMathIsZero(lengthSquared))
	{
		this->_x = 0;
		this->_y = 0;
		this->_z = 0;
		return *this;
	}

	float reciprocal = RFMathInvSqrt(lengthSquared);
	this->_x *= reciprocal;
	this->_y *= reciprocal;
	this->_z *= reciprocal;

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
float RFMath::Vector3::Dot(const Vector3& vector) const
{
	return (this->_x * vector._x, this->_y * vector._y, this->_z * vector._z);
}

/**
 * Create the cross product for this and a given
 * vector.
 *
 * @param vector
 *
 * @return New vector containing cross product
 */
RFMath::Vector3 RFMath::Vector3::Cross(const Vector3& vector) const
{
	Vector3 result;
	result._x = this->_y * vector._z - this->_z * vector._y;
	result._y = this->_z * vector._x - this->_x * vector._z;
	result._z = this->_x * vector._y - this->_y * vector._x;
	return result;
}

/**
 * Set all components of the vector.
 *
 * @param x
 * @param y
 * @param z
 */
void RFMath::Vector3::Set(float x, float y, float z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

/**
 * Assignment operator.
 *
 * @param vector
 *
 * @return Modified vector
 */
RFMath::Vector3 RFMath::Vector3::operator=(const Vector3& vector)
{
	if(this == &vector)
	{
		return *this;
	}

	this->_x = vector._x;
	this->_y = vector._y;
	this->_z = vector._z;

	return *this;
}

/**
 * Unary minus operator overload, letting the vector point in
 * opposite direction.
 *
 * @return New vector in opposite direction
 */
RFMath::Vector3 RFMath::Vector3::operator-() const
{
	return Vector3(-this->_x, -this->_y, -this->_z);
}

/**
 * Addition operator overload.
 *
 * @param vector
 *
 * @return New vector with added components
 */
RFMath::Vector3 RFMath::Vector3::operator+(const Vector3& vector) const
{
	return Vector3(this->_x + vector._x, this->_y + vector._y, this->_z + vector._z);
}

/**
 * Addition assignment operator overload, adding components of
 * vector to self.
 *
 * @param vector
 *
 * @return Same vector with modified components
 */
RFMath::Vector3 RFMath::Vector3::operator+=(const Vector3& vector)
{
	this->_x += vector._x;
	this->_y += vector._y;
	this->_z += vector._z;

	return *this;
}

/**
 * Subtraction operator overload.
 *
 * @param vector
 *
 * @return New vector with subtracted components
 */
RFMath::Vector3 RFMath::Vector3::operator-(const Vector3& vector) const
{
	return Vector3(this->_x - vector._x, this->_y - vector._y, this->_z - vector._z);
}

/**
 * Subtraction assignment operator overload, subtracting components of
 * vector from self.
 *
 * @param vector
 * 
 * @return Same vector with modified components
 */
RFMath::Vector3 RFMath::Vector3::operator-=(const Vector3& vector)
{
	this->_x -= vector._x;
	this->_y -= vector._y;
	this->_z -= vector._z;

	return *this;
}

/**
 * Scalar multiplication overload
 *
 * @param scalar
 *
 * @return New vector with multiplied components
 */
RFMath::Vector3 RFMath::Vector3::operator*(const float scalar) const
{
	return Vector3(this->_x * scalar, this->_y * scalar, this->_z * scalar);
}

/**
 * Scalar multiplication overload
 *
 * @param vector
 * @param scalar
 *
 * @return New vector with multiplied components
 */
DLLEX RFMath::Vector3 RFMath::operator*(const float scalar, const Vector3& vector)
{
	return Vector3(vector._x * scalar, vector._y * scalar, vector._z * scalar);
}

/**
 * Multiplication assign operator overload, multiplying vector
 * by a scalar;
 *
 * @param scalar
 *
 * @return Same vector with modified components
 */
RFMath::Vector3 RFMath::Vector3::operator*=(const float scalar)
{
	this->_x *= scalar;
	this->_y *= scalar;
	this->_z *= scalar;
	return *this;
}

/**
 * Array access operator.
 *
 * @param i
 *
 * @return The corresponding component
 */
float RFMath::Vector3::operator[](unsigned int i) const
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
bool RFMath::Vector3::operator==(const Vector3& vector) const
{
	return RFMathIsEqual(this->_x, vector._x)
		&& RFMathIsEqual(this->_y, vector._y)
		&& RFMathIsEqual(this->_z, vector._z);	
}

/**
 * Output stream operator overload
 *
 * @param output
 * @param vector
 *
 * @return Output stream
 */
DLLEX std::ostream& RFMath::operator<<(std::ostream& output, const Vector3& vector)
{
	output << "Vector3 { " << vector._x << ", " << vector._y << ", " << vector._z << " }" << std::endl;
	return output;
}