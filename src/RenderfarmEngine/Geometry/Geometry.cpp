#include "Geometry.h"

/**
 * Default constructor.
 */
RFGeometry::Geometry::Geometry()
{
    this->_Construct(RFMath::Vector3(0.0f, 0.0f, 0.0f));
}

/**
 * Constructor setting the position of the geometry in the
 * world.
 *
 * @param position
 */
RFGeometry::Geometry::Geometry(const RFMath::Vector3& position)
{
    this->_Construct(position);
}

/**
 * Destructor.
 */
RFGeometry::Geometry::~Geometry()
{
    delete this->_pVertexPositions;
    delete this->_pVertexBuffer;
}

/**
 * Return the position of the geometry.
 *
 * @return Vector with position
 */
RFMath::Vector3& RFGeometry::Geometry::GetPosition()
{
    return this->_position;
}

/**
 * Set the position of the geometry.
 *
 * @param position
 */
void RFGeometry::Geometry::SetPosition(const RFMath::Vector3& position)
{
    this->_position = position;
}

/**
 * Multiply all vertices of the cube by a transformation matrix.
 *
 * @param matrix
 * @param toOrigin
 */
void RFGeometry::Geometry::Transform(RFMath::Matrix& matrix, bool toOrigin)
{
    if(toOrigin)
    {
        RFMath::Matrix translation;
        translation.Translate(-this->_position.GetX(), -this->_position.GetY(), -this->_position.GetZ());
        this->Transform(translation, false);
    }

    for(unsigned int i = 0; i < this->_pVertexBuffer->size(); ++i)
    {
        RFMath::Vector3 newVector = matrix.Transform(*this->_pVertexBuffer->at(i)->GetPosition());
        RFMath::Vector3* pNewVector = this->_CopyVector(&newVector);

        RFMath::Vector3* currentVector = this->_pVertexBuffer->at(i)->GetPosition();
        delete currentVector;

        this->_pVertexBuffer->at(i)->SetPosition(pNewVector);
    }

    if(toOrigin)
    {
        RFMath::Matrix translation;
        translation.Translate(this->_position.GetX(), this->_position.GetY(), this->_position.GetZ());
        this->Transform(translation, false);
    }
}

/**
 * Return the vertices that make up this geometry (should be filled
 * in subclasses.
 *
 * @return Vertices
 */
std::vector<RFMath::Vector3*>* RFGeometry::Geometry::GetVertexPositions()
{
    return this->_pVertexPositions;
}

/**
 * Return the vertices that make up all the triangles in the geometry
 * (should be filled in subclasses).
 *
 * @return Vertex buffer
 */
std::vector<RFGeometry::Vertex*>* RFGeometry::Geometry::GetVertexBuffer()
{
    return this->_pVertexBuffer;
}

/**
 * Output stream operator.
 *
 * @param output
 * @param geometry
 */
DLL_API std::ostream& RFGeometry::operator<<(std::ostream& output, Geometry& geometry)
{
    output << "Geometry {" << std::endl;
    output << "    Position: " << geometry._position << std::endl;
    output << std::endl;
    geometry.Print(output);
    output << std::endl;
    output << "}";

    return output;
}

/**
 * Copy a vector and return the pointer.
 *
 * @param pVector
 *
 * @return Copy of vector
 */
RFMath::Vector3* RFGeometry::Geometry::_CopyVector(RFMath::Vector3* pVector)
{
    return new RFMath::Vector3(pVector->GetX(), pVector->GetY(), pVector->GetZ());
}

/**
 * Construct this geometry with a position.
 *
 * @param position
 */
void RFGeometry::Geometry::_Construct(const RFMath::Vector3& position)
{
    this->_position = position;
    this->_pVertexPositions = new std::vector<RFMath::Vector3*>();
    this->_pVertexBuffer = new std::vector<RFGeometry::Vertex*>();
}