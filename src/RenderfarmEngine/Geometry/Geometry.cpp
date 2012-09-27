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
    delete this->_pVertices;
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
 * Return the vertices that make up this geometry (should be filled
 * in subclasses.
 *
 * @return Vertices
 */
std::vector<RFMath::Vector3*>* RFGeometry::Geometry::GetVertices()
{
    return this->_pVertices;
}

/**
 * Return the vertices that make up all the triangles in the geometry
 * (should be filled in subclasses).
 *
 * @return Vertex buffer
 */
std::vector<RFMath::Vector3*>* RFGeometry::Geometry::GetVertexBuffer()
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
 * Construct this geometry with a position.
 *
 * @param position
 */
void RFGeometry::Geometry::_Construct(const RFMath::Vector3& position)
{
    this->_position = position;
    this->_pVertices = new std::vector<RFMath::Vector3*>();
    this->_pVertexBuffer = new std::vector<RFMath::Vector3*>();
}