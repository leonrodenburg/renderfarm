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

    this->_CalculateVertices();
    this->_CalculateVertexBuffer();
}

/**
 * Return the array of vertices that make up this
 * cube.
 *
 * @return Array of Vector3
 */
RFMath::Vector3* RFGeometry::Cube::GetVertices()
{
    return this->_vertices;
}

/**
 * Return the vertex buffer layout of this cube. This consists of
 * vertices that form triangles that make up the cube. The vertex
 * buffer can be drawn to screen.
 *
 * @return Array of Vector3
 */
const RFMath::Vector3** RFGeometry::Cube::GetVertexBuffer()
{
    return this->_vertexBuffer;
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
    for(int i = 0; i < 8; ++i)
    {
        output << "            " << this->_vertices[i] << std::endl;
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

    this->_CalculateVertices();
    this->_CalculateVertexBuffer();
}

/**
 * Calculate the set of vertices that make up this cube, given
 * the size and position. The position is taken as the center
 * of the cube and the size is the width and height (not the
 * distance from the center to the vertices).
 */
void RFGeometry::Cube::_CalculateVertices()
{
    float halfSize = this->_size / 2;

    // Lower vertices (seen from top)
    // 1-----2
    // |     |
    // |     |
    // 0-----3
    this->_vertices[0] = RFMath::Vector3(-halfSize + this->_position[0], -halfSize + this->_position[1], -halfSize + this->_position[2]);
    this->_vertices[1] = RFMath::Vector3(-halfSize + this->_position[0], -halfSize + this->_position[1],  halfSize + this->_position[2]);
    this->_vertices[2] = RFMath::Vector3( halfSize + this->_position[0], -halfSize + this->_position[1],  halfSize + this->_position[2]);
    this->_vertices[3] = RFMath::Vector3( halfSize + this->_position[0], -halfSize + this->_position[1], -halfSize + this->_position[2]);

    // Upper vertices (seen from top)
    // 5-----6
    // |     |
    // |     |
    // 4-----7
    this->_vertices[4] = RFMath::Vector3(-halfSize + this->_position[0], halfSize + this->_position[1], -halfSize + this->_position[2]);
    this->_vertices[5] = RFMath::Vector3(-halfSize + this->_position[0], halfSize + this->_position[1],  halfSize + this->_position[2]);
    this->_vertices[6] = RFMath::Vector3( halfSize + this->_position[0], halfSize + this->_position[1],  halfSize + this->_position[2]);
    this->_vertices[7] = RFMath::Vector3( halfSize + this->_position[0], halfSize + this->_position[1], -halfSize + this->_position[2]);

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
} 

/**
 * Calculate the triangles that make up the cube.
 */
void RFGeometry::Cube::_CalculateVertexBuffer()
{
    // Lower square, triangle 1
    this->_vertexBuffer[0]  = &(this->_vertices[1]);
    this->_vertexBuffer[1]  = &(this->_vertices[0]);
    this->_vertexBuffer[2]  = &(this->_vertices[2]);

    // Lower square, triangle 2                     
    this->_vertexBuffer[3]  = &(this->_vertices[2]);
    this->_vertexBuffer[4]  = &(this->_vertices[0]);
    this->_vertexBuffer[5]  = &(this->_vertices[3]);

    // Front square, triangle 1
    this->_vertexBuffer[6]  = &(this->_vertices[0]);
    this->_vertexBuffer[7]  = &(this->_vertices[4]);
    this->_vertexBuffer[8]  = &(this->_vertices[3]);

    // Front square, triangle 2
    this->_vertexBuffer[9]  = &(this->_vertices[3]);
    this->_vertexBuffer[10] = &(this->_vertices[4]);
    this->_vertexBuffer[11] = &(this->_vertices[7]);

    // Left square, triangle 1
    this->_vertexBuffer[12] = &(this->_vertices[1]);
    this->_vertexBuffer[13] = &(this->_vertices[5]);
    this->_vertexBuffer[14] = &(this->_vertices[0]);

    // Left square, triangle 2
    this->_vertexBuffer[15] = &(this->_vertices[0]);
    this->_vertexBuffer[16] = &(this->_vertices[5]);
    this->_vertexBuffer[17] = &(this->_vertices[4]);

    // Back square, triangle 1
    this->_vertexBuffer[18] = &(this->_vertices[2]);
    this->_vertexBuffer[19] = &(this->_vertices[6]);
    this->_vertexBuffer[20] = &(this->_vertices[1]);

    // Back square, triangle 2
    this->_vertexBuffer[21] = &(this->_vertices[1]);
    this->_vertexBuffer[22] = &(this->_vertices[6]);
    this->_vertexBuffer[23] = &(this->_vertices[5]);

    // Right square, triangle 1
    this->_vertexBuffer[24] = &(this->_vertices[3]);
    this->_vertexBuffer[25] = &(this->_vertices[7]);
    this->_vertexBuffer[26] = &(this->_vertices[2]);

    // Right square, triangle 2
    this->_vertexBuffer[27] = &(this->_vertices[2]);
    this->_vertexBuffer[28] = &(this->_vertices[7]);
    this->_vertexBuffer[29] = &(this->_vertices[6]);

    // Top square, triangle 1
    this->_vertexBuffer[30] = &(this->_vertices[4]);
    this->_vertexBuffer[31] = &(this->_vertices[5]);
    this->_vertexBuffer[32] = &(this->_vertices[7]);

    // Top square, triangle 2
    this->_vertexBuffer[33] = &(this->_vertices[7]);
    this->_vertexBuffer[34] = &(this->_vertices[5]);
    this->_vertexBuffer[35] = &(this->_vertices[6]);
}