#include "Clipper.h"

/**
 * Default constructor.
 */
RFStage::Clipper::Clipper()
{
    this->_Construct(&(RFMath::Vector3(-1.0f, -1.0f, -1.0f)), &(RFMath::Vector3(1.0f, 1.0f, 1.0f)));
}

/**
 * Constructor setting the minimum and maximum clipping points.
 *
 * @param pMin
 * @param pMax
 */
RFStage::Clipper::Clipper(const RFMath::Vector3* pMin, const RFMath::Vector3* pMax)
{
    this->_Construct(pMin, pMax);
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
 * @param pBuffer
 */
void RFStage::Clipper::BindBuffer(const std::vector<RFMath::Vector3*>* pBuffer)
{
    this->_pBuffer = pBuffer;
}

/**
 * Clip the buffer against the minimum and maximum point, stitching together
 * partially clipped triangles, and build a new list of vertices that pass
 * through.
 *
 * @return Vertices to be rendered
 */
std::vector<RFMath::Vector3*>* RFStage::Clipper::Clip()
{
    return this->_pOutput;
}

/**
 * Construct the Clipper object, setting the minimum and maximum points
 * against which the vertices will be clipped.
 *
 * @param pMin
 * @param pMax
 */
void RFStage::Clipper::_Construct(const RFMath::Vector3* pMin, const RFMath::Vector3* pMax)
{
    this->_pOutput = new std::vector<RFMath::Vector3*>();
    this->_pMin = pMin;
    this->_pMax = pMax;
}