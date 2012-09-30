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
    // Build geometry (and generate vertex buffer)
    std::vector<RFMath::Vector3*>* buffer = this->_pWorld->BuildGeometry();

    // Bind the buffer to the clipper and clip
    this->_pClipper->BindBuffer(buffer);
    std::vector<RFMath::Vector3*>* output = this->_pClipper->Clip();

    for(unsigned int i = 0; i < output->size(); ++i)
    {
        //std::cout << *output->at(i) << std::endl;
    }

#ifdef DEBUG_BUILD
    Logger::GetLogger()->Log("Firing up Kernel...");
#endif
}