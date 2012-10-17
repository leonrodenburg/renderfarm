#include "Kernel.h"

/**
 * Constructor, setting the world, near and far view clipping plane distances,
 * the field of view in degrees and the window size.
 *
 * @param pWorld
 * @param nearView
 * @param farView
 * @param fieldOfView
 * @param windowWidth
 * @param windowHeight
 */
RFCore::Kernel::Kernel(RFGeometry::World* pWorld, float nearView, float farView, float fieldOfView, unsigned int windowWidth, unsigned int windowHeight)
{
    this->_pWorld = pWorld;
    this->_pProjector = new RFStage::Projector(nearView, farView, fieldOfView, windowWidth, windowHeight);
    this->_pClipper = new RFStage::Clipper();
    this->_pRasterizer = new RFStage::Rasterizer(windowWidth, windowHeight);

#ifdef DEBUG
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
    delete this->_pProjector;

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Kernel destroyed...");
#endif
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
 * Return the pointer to the clipper used.
 *
 * @return Clipper
 */
RFStage::Clipper* RFCore::Kernel::GetClipper()
{
    return this->_pClipper;
}

/**
 * Return the pointer to the rasterizer used.
 *
 * @return Rasterizer
 */
RFStage::Rasterizer* RFCore::Kernel::GetRasterizer()
{
    return this->_pRasterizer;
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
    std::vector<RFGeometry::Vertex*>* pBuffer = this->_pWorld->BuildGeometry();

    // Project the vertices
    this->_pProjector->BindBuffer(pBuffer);
    pBuffer = this->_pProjector->Project();

    // Bind the buffer to the clipper and clip
    //this->_pClipper->BindBuffer(pBuffer);
    //pBuffer = this->_pClipper->Clip();

    // Map the vertices to screen coordinates
    this->_pProjector->BindBuffer(pBuffer);
    pBuffer = this->_pProjector->Map();

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