#include "Geometry.h"

/**
 * Default constructor.
 */
RFGeometry::Geometry::Geometry()
{

}

/**
 * Constructor setting the position of the geometry in the
 * world.
 *
 * @param position
 */
RFGeometry::Geometry::Geometry(const RFMath::Vector3& position)
{
    this->_position = position;
}

/**
 * Destructor.
 */
RFGeometry::Geometry::~Geometry()
{

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