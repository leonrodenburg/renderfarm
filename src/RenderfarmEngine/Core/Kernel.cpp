#include "Kernel.h"

/**
 * Default constructor.
 */
RFCore::Kernel::Kernel(RFGeometry::World* pWorld, unsigned int windowWidth, unsigned int windowHeight)
{
    this->_pWorld = pWorld;
    this->_pClipper = new RFStage::Clipper();

    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;
}

/**
 * Destructor.
 */
RFCore::Kernel::~Kernel()
{
    delete this->_pClipper;
}

/**
 * Bind a buffer to the Kernel, which will be used to render
 * to.
 *
 * @param pBuffer
 */
void RFCore::Kernel::BindBuffer(float* pBuffer)
{
    this->_pBuffer = pBuffer;
}

/**
 * Traverse the rendering pipeline.
 */ 
void RFCore::Kernel::Run()
{
    // Build geometry (and generate vertex buffer)
    std::vector<RFMath::Vector3*>* buffer = this->_pWorld->BuildGeometry();

    // Bind the buffer to the clipper and clip
    this->_pClipper->BindBuffer(buffer);
    std::vector<RFMath::Vector3*>* output = this->_pClipper->Clip();

#ifdef DEBUG_BUILD
    Logger::GetLogger()->Log("Firing up Kernel...");
#endif
}