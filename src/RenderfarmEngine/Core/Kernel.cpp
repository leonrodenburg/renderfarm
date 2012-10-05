#include "Kernel.h"

/**
 * Default constructor.
 */
RFCore::Kernel::Kernel(RFGeometry::World* pWorld, unsigned int windowWidth, unsigned int windowHeight)
{
    this->_pWorld = pWorld;
    this->_pClipper = new RFStage::Clipper();
    this->_pRasterizer = new RFStage::Rasterizer(windowWidth, windowHeight);

#ifdef DEBUG_BUILD
    Logger::GetLogger()->Log("Created Kernel...");
#endif
}

/**
 * Destructor.
 */
RFCore::Kernel::~Kernel()
{
    delete this->_pRasterizer;
    delete this->_pClipper;
}

/**
 * Return the current front buffer.
 *
 * @return Current front buffer with colors
 */
unsigned int* RFCore::Kernel::GetFrontBuffer()
{
    return this->_pFrontBuffer;
}

/**
 * Traverse the rendering pipeline, draw in the back buffer,
 * swap with the front buffer and return it.
 *
 * @return Front buffer;
 */ 
unsigned int* RFCore::Kernel::Run()
{
    // Build geometry (and generate vertex buffer)
    std::vector<RFMath::Vector3*>* pBuffer = this->_pWorld->BuildGeometry();

    // Bind the buffer to the clipper and clip
    this->_pClipper->BindBuffer(pBuffer);
    pBuffer = this->_pClipper->Clip();

    // Bind the buffer to the rasterizer
    this->_pRasterizer->BindBuffer(pBuffer);
    this->_pBackBuffer = this->_pRasterizer->Rasterize();

    // Swap back and front buffer
    unsigned int* pTemp = this->_pFrontBuffer;
    this->_pFrontBuffer = this->_pBackBuffer;
    this->_pBackBuffer = pTemp;

    // Return front buffer
    return this->_pFrontBuffer;
}