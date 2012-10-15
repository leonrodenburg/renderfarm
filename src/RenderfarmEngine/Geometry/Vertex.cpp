#include "Vertex.h"

/**
 * Constructor, setting position and color.
 *
 * @param pPosition
 * @param pColor
 */
RFGeometry::Vertex::Vertex(RFMath::Vector3* pPosition, RFMath::Vector3* pColor)
{
    this->_pPosition = pPosition;
    this->_pColor = pColor;
}

/**
 * Destructor.
 */
RFGeometry::Vertex::~Vertex()
{
    delete this->_pPosition;
    delete this->_pColor;
}

/**
 * Return the position of this vertex.
 *
 * @return Position
 */
RFMath::Vector3* RFGeometry::Vertex::GetPosition()
{
    return this->_pPosition;
}

/**
 * Return the color of this vertex.
 *
 * @return Color
 */
RFMath::Vector3* RFGeometry::Vertex::GetColor()
{
    return this->_pColor;
}

/**
 * Set the position of the vertex.
 *
 * @param pPosition
 */
void RFGeometry::Vertex::SetPosition(RFMath::Vector3* pPosition)
{
    this->_pPosition = pPosition;
}

/**
 * Set the color of the vertex.
 *
 * @param pColor
 */
void RFGeometry::Vertex::SetColor(RFMath::Vector3* pColor)
{
    this->_pColor = pColor;
}
