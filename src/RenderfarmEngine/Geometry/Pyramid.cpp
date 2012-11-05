#include "Pyramid.h"

/**
 * Default constructor.
 */
RFGeometry::Pyramid::Pyramid() : Geometry(RFMath::Vector3(0.0f, 0.0f, 0.0f))
{
    this->_Construct(5.0f, 5.0f);
}

/**
 * Constructor, setting the size and initializing the position at the
 * origin.
 *
 * @param size
 */
RFGeometry::Pyramid::Pyramid(float base, float height) : Geometry(RFMath::Vector3(0.0f, 0.0f, 0.0f))
{
    this->_Construct(base, height);
}

/**
 * Constructor, setting the position and size of the
 * cube.
 *
 * @param size
 * @parma position
 */
RFGeometry::Pyramid::Pyramid(float base, float height, const RFMath::Vector3& position) : Geometry(position)
{
    this->_Construct(base, height);
}

/**
 * Destructor.
 */
RFGeometry::Pyramid::~Pyramid()
{
  
}

/**
 * Return the length of the base's sides.
 *
 * @return Base side length
 */
float RFGeometry::Pyramid::GetBase()
{
    return this->_base;
}

/**
 * Set the length of the base's sides.
 *
 * @param base
 */
void RFGeometry::Pyramid::SetBase(float base)
{
    this->_base = base;
}

/**
 * Return the height of the pyramid.
 *
 * @return Height
 */
float RFGeometry::Pyramid::GetHeight()
{
    return this->_height;
}

/**
 * Set the height of the pyramid.
 *
 * @param height
 */
void RFGeometry::Pyramid::SetHeight(float height)
{
    this->_height = height;
}

/**
 * Prepare the vertices and its buffer.
 */
void RFGeometry::Pyramid::PrepareBuffers()
{
    // Prepare vertices
    if(this->_pVertexPositions != 0)
    {
        for(unsigned int i = 0; i < this->_pVertexPositions->size(); ++i)
        {
            delete this->_pVertexPositions->at(i);
        }
        this->_pVertexPositions->clear();
    }

    float halfBase = this->_base / 2;
    float halfHeight = this->_height / 2;

    // Vertices (seen from top)
    // 3      2
    // --------
    // |\    /|
    // | \  / |
    // |  \/  |
    // |  4\  |
    // | /  \ | 
    // |/    \|
    // --------
    // 0      1

    // Add base vertices
    this->_pVertexPositions->push_back(new RFMath::Vector3(-halfBase + this->_position[0], -halfHeight + this->_position[1], -halfBase + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3(halfBase + this->_position[0], -halfHeight + this->_position[1], -halfBase + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3(halfBase + this->_position[0], -halfHeight + this->_position[1], halfBase + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3(-halfBase + this->_position[0], -halfHeight + this->_position[1], halfBase + this->_position[2]));

    // Add top vertex
    this->_pVertexPositions->push_back(new RFMath::Vector3(this->_position[0], halfHeight + this->_position[1], this->_position[2]));

    // Prepare vertex buffer
    if(this->_pVertexBuffer != 0)
    {
        for(unsigned int i = 0; i < this->_pVertexBuffer->size(); ++i)
        {
            delete this->_pVertexBuffer->at(i);
        }
        this->_pVertexBuffer->clear();
    }

    // Base, right triangle
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(0)), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(1)), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(2)), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));

    // Base, left triangle
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(2)), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(3)), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(0)), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));

    // Front triangle
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(0)), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(4)), new RFMath::Vector3(255.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(1)), new RFMath::Vector3(255.0f, 0.0f, 255.0f)));

    // Right triangle
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(1)), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(4)), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(2)), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));

    // Back triangle
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(2)), new RFMath::Vector3(0.0f, 255.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(4)), new RFMath::Vector3(0.0f, 255.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(3)), new RFMath::Vector3(0.0f, 255.0f, 255.0f)));

    // Left triangle
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(3)), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(4)), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_CopyVector(this->_pVertexPositions->at(0)), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
}

/**
 * Print info about this pyramid, for debugging purposes.
 *
 * @param output
 */
void RFGeometry::Pyramid::Print(std::ostream& output)
{
    output << "    Pyramid {" << std::endl;
    output << "        Base: " << this->_base << std::endl;
    output << "        Height: " << this->_height << std::endl;
    output << "        Vertices: {" << std::endl;
    for(unsigned int i = 0; i < this->_pVertexPositions->size(); ++i)
    {
        output << "            " << this->_pVertexPositions->at(i) << std::endl;
    }
    output << "        }" << std::endl;
    output << "    }";
}

/**
 * Construct the pyramid object and calculate the vertices and
 * vertex buffer.
 *
 * @param base
 * @param height
 */
void RFGeometry::Pyramid::_Construct(float base, float height)
{
    this->_base = base;
    this->_height = height;
    this->PrepareBuffers();
}