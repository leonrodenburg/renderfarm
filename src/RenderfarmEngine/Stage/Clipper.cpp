#include "Clipper.h"

/**
 * Default constructor.
 */
RFStage::Clipper::Clipper()
{
    this->_pOutput = new std::vector<RFMath::Vector3*>();
}

/**
 * Destructor.
 */
RFStage::Clipper::~Clipper()
{
    delete this->_pOutput;
}

/**
 * Bind a vertex buffer to the clipping stage.
 *
 * @param buffer
 */
void RFStage::Clipper::BindBuffer(const std::vector<RFMath::Vector3*>& buffer)
{
    this->_pBuffer = &buffer;
}