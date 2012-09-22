#include "Matrix.h"

/**
 * Default constructor
 */
RFMath::Matrix::Matrix()
{

}

/**
 * Destructor
 */
RFMath::Matrix::~Matrix()
{
    
}

/**
 * Output stream operator overload
 *
 * @param output
 * @param matrix
 *
 * @return Output stream
 */
DLLEX std::ostream& RFMath::operator<<(std::ostream& output, const RFMath::Matrix& matrix)
{
    output << "Matrix {" << std::endl;
    output << "}" << std::endl;
    return output;
}