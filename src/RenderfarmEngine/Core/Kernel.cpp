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

    this->_pFrontBuffer = new unsigned int[(windowWidth * 3) * windowHeight];
    this->_pBackBuffer = new unsigned int[(windowWidth * 3) * windowHeight];

#ifdef DEBUG_BUILD
    Logger::GetLogger()->Log("Created Kernel...");
#endif
}

/**
 * Destructor.
 */
RFCore::Kernel::~Kernel()
{
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
    static unsigned int offset = 1;
    static unsigned int red = 0;
    static unsigned int green = 0;
    static unsigned int blue = 0;

    // Build geometry (and generate vertex buffer)
    std::vector<RFMath::Vector3*>* buffer = this->_pWorld->BuildGeometry();

    // Bind the buffer to the clipper and clip
    this->_pClipper->BindBuffer(buffer);
    std::vector<RFMath::Vector3*>* output = this->_pClipper->Clip();

    // Edit back buffer
    for(unsigned int y = 0; y < this->_windowHeight; ++y)
    {
        for(unsigned int x = 0; x < this->_windowWidth * 3; x += 3)
        {
            this->_pBackBuffer[y * (this->_windowWidth * 3) + x] = red;
            this->_pBackBuffer[y * (this->_windowWidth * 3) + x + 1] = green;
            this->_pBackBuffer[y * (this->_windowWidth * 3) + x + 2] = blue;
        }
    }

    red += offset;
    green += offset;
    blue += offset;

    if(red == 255)
    {
        offset = -1;
    }
    
    if(red == 0)
    {
        offset = +1;
    }

    // Swap back and front buffer
    unsigned int* pTemp = this->_pFrontBuffer;
    this->_pFrontBuffer = this->_pBackBuffer;
    this->_pBackBuffer = pTemp;

    // Return front buffer
    return this->_pFrontBuffer;
}