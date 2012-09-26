#include "Kernel.h"

/**
 * Default constructor.
 */
RFCore::Kernel::Kernel(RFGeometry::World* pWorld)
{
    this->_pWorld = pWorld;
    this->_pClipper = new RFStage::Clipper();
}

/**
 * Destructor.
 */
RFCore::Kernel::~Kernel()
{
    delete this->_pClipper;
}

/**
 * Start rendering the world.
 */
void RFCore::Kernel::Run()
{
    this->_pWorld->BuildGeometry();

#ifdef DEBUG_BUILD
    Logger::GetLogger()->Log("Firing up Kernel...");
#endif
}