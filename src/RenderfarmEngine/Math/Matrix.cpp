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
 * Transform a point described by the vector.
 *
 * @param vector
 *
 * @return Transformed vector
 */
RFMath::Vector3 RFMath::Matrix::Transform(const Vector3& vector)
{
    Vector3 result;

    result.SetX(this->_elements[0] * vector.GetX() + this->_elements[4] * vector.GetY() + this->_elements[8] * vector.GetZ() + this->_elements[12]);
    result.SetY(this->_elements[1] * vector.GetX() + this->_elements[5] * vector.GetY() + this->_elements[9] * vector.GetZ() + this->_elements[13]);
    result.SetZ(this->_elements[2] * vector.GetX() + this->_elements[6] * vector.GetY() + this->_elements[10] * vector.GetZ() + this->_elements[14]);

    result.Clean();

    return result;
}

/**
 * Get the transpose of this matrix.
 *
 * @return Tranposed matrix
 */
RFMath::Matrix& RFMath::Matrix::Transpose()
{
    // Swap elements 1 / 4
    float temp = this->_elements[1];
    this->_elements[1] = this->_elements[4];
    this->_elements[4] = temp;

    // Swap elements 2 / 8
    temp = this->_elements[2];
    this->_elements[2] = this->_elements[8];
    this->_elements[8] = temp;

    // Swap elements 6 / 9
    temp = this->_elements[6];
    this->_elements[6] = this->_elements[9];
    this->_elements[9] = temp;

    // Swap elements 7 / 13
    temp = this->_elements[7];
    this->_elements[7] = this->_elements[13];
    this->_elements[13] = temp;

    // Swap elements 11 / 14
    temp = this->_elements[11];
    this->_elements[11] = this->_elements[14];
    this->_elements[14] = temp;

    return *this;
}

/**
 * Calculate the transpose of a matrix and return a new
 * matrix.
 *
 * @param matrix
 *
 * @return New transposed matrix
 */
DLL_API RFMath::Matrix RFMath::Transpose(const Matrix& matrix)
{
    Matrix result;

    result._elements[0] = matrix[0];
    result._elements[1] = matrix[4];
    result._elements[2] = matrix[8];
    result._elements[3] = matrix[12];

    result._elements[4] = matrix[1];
    result._elements[5] = matrix[5];
    result._elements[6] = matrix[9];
    result._elements[7] = matrix[13];

    result._elements[8] = matrix[2];
    result._elements[9] = matrix[6];
    result._elements[10] = matrix[10];
    result._elements[11] = matrix[14];

    result._elements[12] = matrix[3];
    result._elements[13] = matrix[7];
    result._elements[14] = matrix[11];
    result._elements[15] = matrix[15];

    return result;
}

/**
 * Calculate the inverse of this matrix and return
 * the inverse (if it exists).
 *
 * @return Inverted matrix
 */
RFMath::Matrix& RFMath::Matrix::Inverse()
{
    *this = RFMath::Inverse(*this);
    return *this;
}

/**
 * Calculate the inverse of the given matrix and
 * return a new matrix that is the inverse. Return
 * identity matrix if not invertible.
 *
 * @param matrix
 *
 * @return New inverted matrix or identity if no inversion possible
 */
DLL_API RFMath::Matrix RFMath::Inverse(const Matrix& matrix)
{
    Matrix result;

    // Compute determinant of upper-left 3x3 matrix
    float cofactor0 = matrix[5] * matrix[10] - matrix[6] * matrix[9];
    float cofactor4 = matrix[2] * matrix[9] - matrix[1] * matrix[10];
    float cofactor8 = matrix[1] * matrix[6] - matrix[2] * matrix[5];
    float det = matrix[0] * cofactor0 + matrix[4] * cofactor4 + matrix[8] * cofactor8;

    // If the determinant is zero (and the matrix is not invertible)
    if(RFMathIsZero(det))
    {
        return result;
    }

    // Create adjunct matrix and multiply by 1 / determinant to get upper 3x3
    float invDet = 1.0f / det;

    result._elements[0] = invDet * cofactor0;
    result._elements[1] = invDet * cofactor4;
    result._elements[2] = invDet * cofactor8;

    result._elements[4] = invDet * (matrix[6] * matrix[8] - matrix[4] * matrix[10]);
    result._elements[5] = invDet * (matrix[0] * matrix[10] - matrix[2] * matrix[8]);
    result._elements[6] = invDet * (matrix[2] * matrix[4] - matrix[0] * matrix[6]);

    result._elements[8] = invDet * (matrix[4] * matrix[9] - matrix[5] * matrix[8]);
    result._elements[9] = invDet * (matrix[1] * matrix[8] - matrix[0] * matrix[9]);
    result._elements[10] = invDet * (matrix[0] * matrix[5] - matrix[1] * matrix[4]);

    result._elements[12] = -result[0] * matrix[12] - result[4] * matrix[13] - result[8] * matrix[14];
    result._elements[13] = -result[1] * matrix[12] - result[5] * matrix[13] - result[9] * matrix[14];
    result._elements[14] = -result[2] * matrix[12] - result[6] * matrix[13] - result[10] * matrix[14];

    result.Clean();

    return result;
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
    this->_elements[12] = vector[0];
    this->_elements[13] = vector[1];
    this->_elements[14] = vector[2];

    return *this;
}

/**
 * Set the translation in the matrix using x, y and z values.
 *
 * @param x
 * @param y
 * @param z
 *
 * @return Translation matrix
 */
RFMath::Matrix& RFMath::Matrix::Translate(float x, float y, float z)
{
    this->Identity();
    this->_elements[12] = x;
    this->_elements[13] = y;
    this->_elements[14] = z;

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
 * Create a scaling matrix using a vector.
 *
 * @param vector
 *
 * @return Scaling matrix
 */
RFMath::Matrix& RFMath::Matrix::Scale(const Vector3& vector)
{
    this->Identity();
    this->_elements[0] = vector[0];
    this->_elements[5] = vector[1];
    this->_elements[10] = vector[2];

    return *this;
}

/**
 * Create a scaling matrix using x, y and z values.
 *
 * @param x
 * @param y
 * @param z
 *
 * @return Scaling matrix
 */
RFMath::Matrix& RFMath::Matrix::Scale(float x, float y, float z)
{
    this->Identity();
    this->_elements[0] = x;
    this->_elements[5] = y;
    this->_elements[10] = z;

    return *this;
}

/**
 * Set the x-scaling of the matrix.
 *
 * @param x
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::ScaleX(float x)
{
    this->_elements[0] = x;
    return *this;
}

/**
 * Set the y-scaling of the matrix.
 *
 * @param y
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::ScaleY(float y)
{
    this->_elements[5] = y;
    return *this;
}

/**
 * Set the z-scaling of the matrix.
 *
 * @param z
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::ScaleZ(float z)
{
    this->_elements[10] = z;
    return *this;
}

/**
 * Calculate the rotation matrix. The resulting matrix's order is
 * roll - pitch - yaw.
 *
 * @param yaw
 * @param pitch
 * @param roll
 *
 * @return Rotation matrix
 */
RFMath::Matrix& RFMath::Matrix::Rotate(float yaw, float pitch, float roll)
{
    this->Identity();

    Matrix yawMatrix;
    Matrix pitchMatrix;
    Matrix rollMatrix;

    yawMatrix.RotateY(yaw);
    pitchMatrix.RotateX(pitch);
    rollMatrix.RotateZ(roll);

    Matrix result = yawMatrix * pitchMatrix * rollMatrix;

    for(int i = 0; i < 16; ++i)
    {
        this->_elements[i] = result[i];
    }

    return *this;
}

/**
 * Set the x-rotation for this matrix.
 *
 * @param angle
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::RotateX(float angle)
{
    float cos, sin;
    RFMathSinCos(-angle, sin, cos);

    this->_elements[5] = cos;
    this->_elements[6] = sin;
    this->_elements[9] = -sin;
    this->_elements[10] = cos;

    return *this;
}

/**
 * Set the y-rotation for this matrix.
 *
 * @param angle
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::RotateY(float angle)
{
    float cos, sin;
    RFMathSinCos(angle, sin, cos);

    this->_elements[0] = cos;
    this->_elements[2] = -sin;
    this->_elements[8] = sin;
    this->_elements[10] = cos;

    return *this;
}

/**
 * Set the z-rotation for this matrix.
 *
 * @param angle
 *
 * @return Modified matrix
 */
RFMath::Matrix& RFMath::Matrix::RotateZ(float angle)
{
    float cos, sin;
    RFMathSinCos(-angle, sin, cos);

    this->_elements[0] = cos;
    this->_elements[1] = sin;
    this->_elements[4] = -sin;
    this->_elements[5] = cos;

    return *this;
}

/**
 * Negate self and return new matrix.
 *
 * @return Negated matrix
 */
RFMath::Matrix RFMath::Matrix::operator-() const
{
    Matrix result;

    for(int i = 0; i < 16; ++i)
    {
        result._elements[i] = -(this->_elements[i]);
    }

    return result;
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
 * Addition operator, returning a new, added operator.
 *
 * @param matrix
 *
 * @return New matrix with added components
 */
RFMath::Matrix RFMath::Matrix::operator+(const Matrix& matrix) const
{
    Matrix result;

    for(int i = 0; i < 16; ++i)
    {
        result._elements[i] = this->_elements[i] + matrix[i];
    }

    return result;
}

/**
 * Addition operator, modifying the current matrix.
 *
 * @param matrix
 *
 * @return Matrix with modified components
 */
RFMath::Matrix& RFMath::Matrix::operator+=(const Matrix& matrix)
{
    for(int i = 0; i < 16; ++i)
    {
        this->_elements[i] += matrix[i];
    }

    return *this;
}

/**
 * Subtraction operator, returning a new, subtracted matrix.
 *
 * @param matrix
 *
 * @return Matrix with subtracted components
 */
RFMath::Matrix RFMath::Matrix::operator-(const Matrix& matrix) const
{
    Matrix result;

    for(int i = 0; i < 16; ++i)
    {
        result._elements[i] = this->_elements[i] - matrix[i];
    }

    return result;
}

/**
 * Subtraction operator, modifying the current matrix.
 *
 * @param matrix
 *
 * @return Matrix with modified components
 */
RFMath::Matrix& RFMath::Matrix::operator-=(const Matrix& matrix)
{
    for(int i = 0; i < 16; ++i)
    {
        this->_elements[i] -= matrix[i];
    }

    return *this;
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

    for(int i = 0; i < 16; ++i)
    {
        result._elements[i] = this->_elements[i] * scalar;
    }

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
    for(int i = 0; i < 16; ++i)
    {
        this->_elements[i] *= scalar;
    }

    return *this;
}

/**
 * Matrix-vector multiplication operator.
 *
 * @param vector
 *
 * @return New, transformed vector
 */
RFMath::Vector4 RFMath::Matrix::operator*(const Vector4& vector) const
{
    Vector4 result;

    result.SetX(this->_elements[0] * vector.GetX() + this->_elements[4] * vector.GetY() + this->_elements[8] * vector.GetZ() + this->_elements[12] * vector.GetW());
    result.SetY(this->_elements[1] * vector.GetX() + this->_elements[5] * vector.GetY() + this->_elements[9] * vector.GetZ() + this->_elements[13] * vector.GetW());
    result.SetZ(this->_elements[2] * vector.GetX() + this->_elements[6] * vector.GetY() + this->_elements[10] * vector.GetZ() + this->_elements[14] * vector.GetW());
    result.SetW(this->_elements[3] * vector.GetX() + this->_elements[7] * vector.GetY() + this->_elements[11] * vector.GetZ() + this->_elements[15] * vector.GetW());

    result.Clean();

    return result;
}

/**
 * Vector-matrix multiplication operator.
 *
 * @param vector
 * @param matrix
 *
 * @return New, transformed vector
 */
DLL_API RFMath::Vector4 RFMath::operator*(const Vector4& vector, const Matrix& matrix)
{
    Vector4 result;

    result.SetX(matrix[0] * vector.GetX() + matrix[1] * vector.GetY() + matrix[2] * vector.GetZ() + matrix[3] * vector.GetW());
    result.SetY(matrix[4] * vector.GetX() + matrix[5] * vector.GetY() + matrix[6] * vector.GetZ() + matrix[7] * vector.GetW());
    result.SetZ(matrix[8] * vector.GetX() + matrix[9] * vector.GetY() + matrix[10] * vector.GetZ() + matrix[11] * vector.GetW());
    result.SetW(matrix[12] * vector.GetX() + matrix[13] * vector.GetY() + matrix[14] * vector.GetZ() + matrix[15] * vector.GetW());

    result.Clean();

    return result;
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

    for(int i = 0; i < 16; ++i)
    {
        this->_elements[i] = result[i];
    }

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