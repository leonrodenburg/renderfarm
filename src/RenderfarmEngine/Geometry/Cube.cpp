#include "Cube.h"

/**
 * Default constructor.
 */
RFGeometry::Cube::Cube() : Geometry(RFMath::Vector3(0.0f, 0.0f, 0.0f))
{
    this->_Construct(10.0f);
}

/**
 * Constructor, setting the size and initializing the position at the
 * origin.
 *
 * @param size
 */
RFGeometry::Cube::Cube(float size) : Geometry(RFMath::Vector3(0.0f, 0.0f, 0.0f))
{
    this->_Construct(size);
}

/**
 * Constructor, setting the position and size of the
 * cube.
 *
 * @param size
 * @parma position
 */
RFGeometry::Cube::Cube(float size, const RFMath::Vector3& position) : Geometry(position)
{
    this->_Construct(size);
}

/**
 * Destructor.
 */
RFGeometry::Cube::~Cube()
{
    // Delete vertices
    if(this->_pVertexBuffer != 0)
    {
        for(unsigned int i = 0; i < this->_pVertexBuffer->size(); ++i)
        {
            //delete this->_pVertexBuffer->at(i);
        }
        this->_pVertexBuffer->clear();
    }
}

/**
 * Return the size of the cube.
 *
 * @return Size
 */
float RFGeometry::Cube::GetSize()
{
    return this->_size;
}

/**
 * Set the size of the cube.
 *
 * @param size
 */
void RFGeometry::Cube::SetSize(float size)
{
    this->_size = size;
}

/**
 * Prepare the vertices and its buffer.
 */
void RFGeometry::Cube::PrepareBuffers()
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

    float halfSize = this->_size / 2;

    // Lower vertices (seen from top)
    // 1-----2
    // |     |
    // |     |
    // 0-----3
    this->_pVertexPositions->push_back(new RFMath::Vector3(-halfSize + this->_position[0], -halfSize + this->_position[1], -halfSize + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3(-halfSize + this->_position[0], -halfSize + this->_position[1],  halfSize + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3( halfSize + this->_position[0], -halfSize + this->_position[1],  halfSize + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3( halfSize + this->_position[0], -halfSize + this->_position[1], -halfSize + this->_position[2]));

    // Upper vertices (seen from top)
    // 5-----6
    // |     |
    // |     |
    // 4-----7
    this->_pVertexPositions->push_back(new RFMath::Vector3(-halfSize + this->_position[0], halfSize + this->_position[1], -halfSize + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3(-halfSize + this->_position[0], halfSize + this->_position[1],  halfSize + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3( halfSize + this->_position[0], halfSize + this->_position[1],  halfSize + this->_position[2]));
    this->_pVertexPositions->push_back(new RFMath::Vector3( halfSize + this->_position[0], halfSize + this->_position[1], -halfSize + this->_position[2]));

    // Result:
    //
    //     5--------6
    //    /|       /| 
    //   / |      / |
    //  4--------7  |
    //  |  1-----|--2
    //  | /      | /
    //  |/       |/
    //  0--------3

    // Prepare vertex buffer
    if(this->_pVertexBuffer != 0)
    {
        for(unsigned int i = 0; i < this->_pVertexBuffer->size(); ++i)
        {
            delete this->_pVertexBuffer->at(i);
        }
        this->_pVertexBuffer->clear();
    }

    // Lower square, triangle 1
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(2), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(1), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(0), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));

    // Lower square, triangle 2                     
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(0), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(3), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(2), new RFMath::Vector3(255.0f, 0.0f, 0.0f)));

    // Front square, triangle 1
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(0), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(4), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(7), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
    
    // Front square, triangle 2
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(7), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(3), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(0), new RFMath::Vector3(0.0f, 255.0f, 0.0f)));

    // Left square, triangle 1
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(1), new RFMath::Vector3(255.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(5), new RFMath::Vector3(255.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(4), new RFMath::Vector3(255.0f, 255.0f, 0.0f)));

    // Left square, triangle 2
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(4), new RFMath::Vector3(255.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(0), new RFMath::Vector3(255.0f, 255.0f, 0.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(1), new RFMath::Vector3(255.0f, 255.0f, 0.0f)));

    // Back square, triangle 1
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(2), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(6), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(5), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));

    // Back square, triangle 2
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(5), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(1), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(2), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));

    // Right square, triangle 1
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(3), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(7), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(6), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));

    // Right square, triangle 2
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(6), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(2), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(3), new RFMath::Vector3(0.0f, 0.0f, 255.0f)));

    // Top square, triangle 1
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(4), new RFMath::Vector3(121.0f, 12.0f, 122.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(5), new RFMath::Vector3(121.0f, 12.0f, 122.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(6), new RFMath::Vector3(121.0f, 12.0f, 122.0f)));

    // Top square, triangle 2
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(6), new RFMath::Vector3(121.0f, 12.0f, 122.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(7), new RFMath::Vector3(121.0f, 12.0f, 122.0f)));
    this->_pVertexBuffer->push_back(new RFGeometry::Vertex(this->_pVertexPositions->at(4), new RFMath::Vector3(121.0f, 12.0f, 122.0f)));
}

/**
 * Print info about this cube, for debugging purposes.
 *
 * @param output
 */
void RFGeometry::Cube::Print(std::ostream& output)
{
    output << "    Cube {" << std::endl;
    output << "        Size: " << this->_size << std::endl;
    output << "        Vertices: {" << std::endl;
    for(unsigned int i = 0; i < this->_pVertexPositions->size(); ++i)
    {
        output << "            " << this->_pVertexPositions->at(i) << std::endl;
    }
    output << "        }" << std::endl;
    output << "    }";
}

/**
 * Construct the cube object and calculate the vertices and
 * vertex buffer.
 *
 * @param size
 */
void RFGeometry::Cube::_Construct(float size)
{
    this->_size = size;
    this->PrepareBuffers();
}