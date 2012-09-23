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
 * Get a float pointer to the raw data.
 *
 * @return Float pointer to data
 */
float* RFMath::Matrix::GetPointer()
{
	return this->_elements;
}

/**
 * Assignment operator.
 *
 * @param matrix
 *
 * @return Modified matrix
 */
RFMath::Matrix RFMath::Matrix::operator=(const Matrix& matrix)
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
 * Array access operator.
 *
 * @param i
 *
 * @return Value at index
 */
float RFMath::Matrix::operator[](unsigned int i)
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
float RFMath::Matrix::operator()(unsigned int i)
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
float RFMath::Matrix::operator()(unsigned int i, unsigned int j)
{
	return this->_elements[j + (i * 4)];
}

/**
 * Matrix-scalar multiplication.
 *
 * @param scalar
 *
 * @return Modified matrix
 */
RFMath::Matrix RFMath::Matrix::operator*(float scalar)
{
	for(int i = 0; i < 16; ++i)
	{
		this->_elements[i] = this->_elements[i] * scalar;
	}

	return *this;
}

/**
 * Scalar-matrix multiplication.
 *
 * @param scalar
 * @param matrix
 *
 * @return New matrix with multiplied components
 */
DLLEX RFMath::Matrix RFMath::operator*(float scalar, const Matrix& matrix)
{
	Matrix result;
	
	for(int i = 0; i < 16; ++i)
	{
		result._elements[i] = matrix._elements[i] * scalar;
	}

	return result;
}

/**
 * Output stream operator overload
 *
 * @param output
 * @param matrix
 *
 * @return Output stream
 */
DLLEX std::ostream& RFMath::operator<<(std::ostream& output, const Matrix& matrix)
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
    output << "}" << std::endl;
    return output;
}