#include "Matrix.h"

/**
 * Default constructor
 */
RFMath::Matrix::Matrix()
{
	this->Identity();
}

/**
 * Copy constructor
 *
 * @param matrix
 */
RFMath::Matrix::Matrix(const Matrix& matrix)
{
	for(int i = 0; i < 16; ++i)
	{
		this->_elements[i] = matrix._elements[i];
	}
}

/**
 * Destructor
 */
RFMath::Matrix::~Matrix()
{
    
}

/**
 * Make this matrix an identity matrix.
 */
void RFMath::Matrix::Identity()
{
	this->_elements[0] = 1.0f;
	this->_elements[1] = 0.0f;
	this->_elements[2] = 0.0f;
	this->_elements[3] = 0.0f;
	
	this->_elements[4] = 0.0f;
	this->_elements[5] = 1.0f;
	this->_elements[6] = 0.0f;
	this->_elements[7] = 0.0f;

	this->_elements[8] = 0.0f;
	this->_elements[9] = 0.0f;
	this->_elements[10] = 1.0f;
	this->_elements[11] = 0.0f;

	this->_elements[12] = 0.0f;
	this->_elements[13] = 0.0f;
	this->_elements[14] = 0.0f;
	this->_elements[15] = 1.0f;
}

/**
 * Set all components that are near to zero, to zero.
 */
void RFMath::Matrix::Clean()
{
	for(int i = 0; i < 16; ++i)
	{
		if(RFMathIsZero(this->_elements[i]))
		{
			this->_elements[i] = 0.0f;
		}
	}
}

/**
 * Test whether or not the matrix is identity.
 *
 * @return True if identity, false if not
 */
bool RFMath::Matrix::IsIdentity()
{
	return RFMathIsEqual(this->_elements[0], 1.0f)
		&& RFMathIsEqual(this->_elements[5], 1.0f)
		&& RFMathIsEqual(this->_elements[10], 1.0f)
		&& RFMathIsEqual(this->_elements[15], 1.0f)
		&& RFMathIsZero(this->_elements[1])
		&& RFMathIsZero(this->_elements[2])
		&& RFMathIsZero(this->_elements[3])
		&& RFMathIsZero(this->_elements[4])
		&& RFMathIsZero(this->_elements[6])
		&& RFMathIsZero(this->_elements[7])
		&& RFMathIsZero(this->_elements[8])
		&& RFMathIsZero(this->_elements[9])
		&& RFMathIsZero(this->_elements[11])
		&& RFMathIsZero(this->_elements[12])
		&& RFMathIsZero(this->_elements[13])
		&& RFMathIsZero(this->_elements[14]);
}

/**
 * Test whether or not all components of the matrix are
 * zero.
 *
 * @return True if zero, false if not
 */
bool RFMath::Matrix::IsZero()
{
	for(int i = 0; i < 16; ++i)
	{
		if(RFMathIsZero(this->_elements[i]))
		{
			return false;
		}
	}

	return true;
}

/**
 * Get a float pointer to the raw data.
 *
 * @return Float pointer to data
 */
float* RFMath::Matrix::GetPointer()
{
	return this->_elements;
}

/**
 * Set the translation in the matrix using a Vector3.
 *
 * @param vector
 *
 * @return Translation matrix
 */
RFMath::Matrix& RFMath::Matrix::Translate(const Vector3& vector)
{
	this->Identity();
	this->_elements[12] = vector.GetX();
	this->_elements[13] = vector.GetY();
	this->_elements[14] = vector.GetZ();

	return *this;
}

/**
 * Set the x-axis translation in the matrix.
 *
 * @param x
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::TranslateX(float x)
{
	this->_elements[12] = x;
	return *this;
}

/**
 * Set the y-axis translation in the matrix.
 *
 * @param y
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::TranslateY(float y)
{
	this->_elements[13] = y;
	return *this;
}

/**
 * Set the z-axis translation in the matrix.
 *
 * @param z
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::TranslateZ(float z)
{
	this->_elements[14] = z;
	return *this;
}

/**
 * Assignment operator.
 *
 * @param matrix
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::operator=(const Matrix& matrix)
{
	if(this == &matrix)
	{
		return *this;
	}

	for(int i = 0; i < 16; ++i)
	{
		this->_elements[i] = matrix._elements[i];
	}

	return *this;
}

/**
 * Equality operator.
 *
 * @param matrix
 *
 * @return True if equal, false if not
 */
bool RFMath::Matrix::operator==(const Matrix& matrix)
{
	for(int i = 0; i < 16; ++i)
	{
		if(!RFMathIsEqual(this->_elements[i], matrix._elements[i]))
		{
			return false;
		}
	}

	return true;
}

/**
 * Inequality operator.
 *
 * @param matrix
 *
 * @return True if inequal, false if equal
 */
bool RFMath::Matrix::operator!=(const Matrix& matrix)
{
	for(int i = 0; i < 16; ++i)
	{
		if(!RFMathIsEqual(this->_elements[i], matrix._elements[i]))
		{
			return true;
		}
	}

	return false;
}

/**
 * Array access operator.
 *
 * @param i
 *
 * @return Value at index
 */
float RFMath::Matrix::operator[](unsigned int i) const
{
	return this->_elements[i];
}

/**
 * Array access operator.
 *
 * @param i
 *
 * @return Value at index
 */
float RFMath::Matrix::operator()(unsigned int i) const
{
	return this->_elements[i];
}

/**
 * 2D array access operator.
 *
 * @param i
 * @param j
 *
 * @return Value at index
 */
float RFMath::Matrix::operator()(unsigned int i, unsigned int j) const
{
	return this->_elements[j + (i * 4)];
}

/**
 * Matrix-scalar multiplication.
 *
 * @param scalar
 *
 * @return New multiplied matrix
 */
RFMath::Matrix RFMath::Matrix::operator*(float scalar) const
{
	Matrix result;

	// TODO: implement

	return result;
}

/**
 * Scalar-matrix multiplication.
 *
 * @param scalar
 * @param matrix
 *
 * @return New matrix with multiplied components
 */
DLL_API RFMath::Matrix RFMath::operator*(float scalar, const Matrix& matrix)
{
	Matrix result;
	
	for(int i = 0; i < 16; ++i)
	{
		result._elements[i] = matrix._elements[i] * scalar;
	}

	return result;
}

/**
 * Matrix-scalar multiplication assignment operator.
 *
 * @param scalar
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::operator*=(float scalar)
{
	// TODO: implement

	return *this;
}

/**
 * Multiplication operator.
 *
 * @param matrix
 *
 * @return New multiplied matrix
 */
RFMath::Matrix RFMath::Matrix::operator*(const Matrix& matrix) const
{
	Matrix result;

	// First row
	result._elements[0] = _elements[0] * matrix[0] + _elements[4] * matrix[1] + _elements[8] * matrix[2] + _elements[12] * matrix[3];		
	result._elements[1] = _elements[1] * matrix[0] + _elements[5] * matrix[1] + _elements[9] * matrix[2] + _elements[13] * matrix[3];
	result._elements[2] = _elements[2] * matrix[0] + _elements[6] * matrix[1] + _elements[10] * matrix[2] + _elements[14] * matrix[3];
	result._elements[3] = _elements[3] * matrix[0] + _elements[7] * matrix[1] + _elements[11] * matrix[2] + _elements[15] * matrix[3];

	// Second row
	result._elements[4] = _elements[0] * matrix[4] + _elements[4] * matrix[5] + _elements[8] * matrix[6] + _elements[12] * matrix[7];
	result._elements[5] = _elements[1] * matrix[4] + _elements[5] * matrix[5] + _elements[9] * matrix[6] + _elements[13] * matrix[7];
	result._elements[6] = _elements[2] * matrix[4] + _elements[6] * matrix[5] + _elements[10] * matrix[6] + _elements[14] * matrix[7];
	result._elements[7] = _elements[3] * matrix[4] + _elements[7] * matrix[5] + _elements[11] * matrix[6] + _elements[15] * matrix[7];

	// Third row
	result._elements[8] = _elements[0] * matrix[8] + _elements[4] * matrix[9] + _elements[8] * matrix[10] + _elements[12] * matrix[11];
	result._elements[9] = _elements[1] * matrix[8] + _elements[5] * matrix[9] + _elements[9] * matrix[10] + _elements[13] * matrix[11];
	result._elements[10] = _elements[2] * matrix[8] + _elements[6] * matrix[9] + _elements[10] * matrix[10] + _elements[14] * matrix[11];
	result._elements[11] = _elements[3] * matrix[8] + _elements[7] * matrix[9] + _elements[11] * matrix[10] + _elements[15] * matrix[11];

	// Second row
	result._elements[12] = _elements[0] * matrix[12] + _elements[4] * matrix[13] + _elements[8] * matrix[14] + _elements[12] * matrix[15];
	result._elements[13] = _elements[1] * matrix[12] + _elements[5] * matrix[13] + _elements[9] * matrix[14] + _elements[13] * matrix[15];
	result._elements[14] = _elements[2] * matrix[12] + _elements[6] * matrix[13] + _elements[10] * matrix[14] + _elements[14] * matrix[15];
	result._elements[15] = _elements[3] * matrix[12] + _elements[7] * matrix[13] + _elements[11] * matrix[14] + _elements[15] * matrix[15];

	return result;
}

/**
 * Matrix-matrix multiplication assignment operator.
 *
 * @param matrix
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::operator*=(const Matrix& matrix)
{
	// TODO: implement

	return *this;
}

/**
 * Output stream operator overload
 *
 * @param output
 * @param matrix
 *
 * @return Output stream
 */
DLL_API std::ostream& RFMath::operator<<(std::ostream& output, const Matrix& matrix)
{
    output << "Matrix {" << std::endl;
	for(int i = 0; i < 4; ++i) 
	{
		for(int j = 0; j < 4; ++j) 
		{
			output << matrix._elements[j + (i * 4)] << ", ";
			if(j == 3) 
			{
				output << std::endl;
			}
		}
	}
    output << "}";
    return output;
}