#include "World.h"

/**
 * Default constructor.
 */
RFGeometry::World::World()
{
    this->_pGeometry = new std::map<int, Geometry*>();
    this->_currentIndex = 1;
}

/**
 * Destructor.
 */
RFGeometry::World::~World()
{
    delete this->_pGeometry;
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

}