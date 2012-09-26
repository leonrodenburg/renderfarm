#include "World.h"

/**
 * Default constructor.
 */
RFGeometry::World::World()
{
    this->_pGeometry = new std::map<int, Geometry*>();
    this->_pVertices = new std::vector<RFMath::Vector3*>();
    this->_currentIndex = 1;
}

/**
 * Destructor.
 */
RFGeometry::World::~World()
{
    delete this->_pGeometry;
    delete this->_pVertices;
}

/**
 * Add geometry to the world.
 *
 * @param pGeometry
 *
 * @return The index of the geometry (used as reference)
 */
int RFGeometry::World::AddGeometry(RFGeometry::Geometry* pGeometry)
{
    std::pair<int, Geometry*> newPair(this->_currentIndex, pGeometry);
    ++this->_currentIndex;
    this->_pGeometry->insert(newPair);
    return newPair.first;
}

/**
 * Remove the geometry with the given index.
 *
 * @param index
 */
void RFGeometry::World::RemoveGeometry(int index)
{
    this->_pGeometry->erase(index);
}

/**
 * Build the geometry in the world by creating one large
 * vertex buffer with all triangles.
 *
 * @return Vertex buffer with all vertices in the world.
 */
std::vector<RFMath::Vector3*>* RFGeometry::World::BuildGeometry()
{
    this->_pVertices->clear();

    for(std::map<int, Geometry*>::iterator it = this->_pGeometry->begin(); it != this->_pGeometry->end(); it++)
    {
        std::vector<RFMath::Vector3*>* vertexBuffer = it->second->GetVertexBuffer();
        for(unsigned int i = 0; i < vertexBuffer->size(); ++i)
        {
            this->_pVertices->push_back(vertexBuffer->at(i));
        }
    }

    return this->_pVertices;
}