#include "Clipper.h"

/**
 * Default constructor.
 */
RFStage::Clipper::Clipper()
{
    this->_pOutput = new std::vector<RFMath::Vector3*>();

    _planeNormals[0] = RFMath::Vector3::xAxis;
    _planeNormals[1] = -RFMath::Vector3::xAxis;

    _planeNormals[2] = RFMath::Vector3::yAxis;
    _planeNormals[3] = -RFMath::Vector3::yAxis;

    _planeNormals[4] = RFMath::Vector3::zAxis;
    _planeNormals[5] = -RFMath::Vector3::zAxis;
}

/**
 * Destructor.
 */
RFStage::Clipper::~Clipper()
{
    delete this->_pOutput;
}

/**
 * Bind a vertex buffer to the clipping stage. The vertices in the buffer
 * should be in normalized device coordinates (NDC). They will be clipped
 * against a cube with minimum point (-1, -1, -1) and maximum point
 * (1, 1, 1).
 *
 * @param pBuffer
 */
void RFStage::Clipper::BindBuffer(std::vector<RFMath::Vector3*>* pBuffer)
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
    for(unsigned int i = 0; i < this->_pBuffer->size(); i += 3)
    {
        std::vector<RFMath::Vector3*> triangleList;
        triangleList.push_back(this->_pBuffer->at(i));
        triangleList.push_back(this->_pBuffer->at(i + 1));
        triangleList.push_back(this->_pBuffer->at(i + 2));

        for(int j = 0; j < 6; ++j)
        {
            std::vector<RFMath::Vector3*> input = triangleList;
            triangleList.clear();

            if(input.size() > 0)
            {
                RFMath::Vector3* pLast = input.at(input.size() - 1);
                float dotLast = this->_planeNormals[j].Dot(*pLast) + 1.0f;

                for(unsigned int k = 0; k < input.size(); ++k)
                {
                    float dot = this->_planeNormals[j].Dot(*input.at(k)) + 1.0f;
                    if(dot >= 0)
                    {
                        if(dotLast < 0)
                        {
                            RFMath::Vector3* pIntersect = this->_CalculateIntersection(input.at(k), pLast, &this->_planeNormals[j]);
                            if(pIntersect != 0)
                            {
                                triangleList.push_back(pIntersect);
                            }
                        }

                        triangleList.push_back(input.at(k));
                    }
                    else if(dotLast > 0)
                    {
                        RFMath::Vector3* pIntersect = this->_CalculateIntersection(input.at(k), pLast, &this->_planeNormals[j]);
                        if(pIntersect != 0)
                        {
                            triangleList.push_back(pIntersect);
                        }
                    }

                    pLast = input.at(k);
                }
            }
        }

        for(unsigned int m = 0; m < triangleList.size(); ++m)
        {
            this->_pOutput->push_back(triangleList.at(m));
        }
    }
    
    return this->_pOutput;
}

/**
 * Calculate the intersection point between an edge and a plane. Return
 * 0 if it doesn't exist (edge parallel to plane).
 *
 * @param pFrom
 * @param pTo
 * @param pPlaneNormal
 *
 * @return The point on the plane
 */
RFMath::Vector3* RFStage::Clipper::_CalculateIntersection(RFMath::Vector3* pFrom, RFMath::Vector3* pTo, RFMath::Vector3* pPlaneNormal)
{
    std::cout << "Rekenen: " << (*pTo - *pFrom) << std::endl;
    float nDotV = pPlaneNormal->Dot(*pTo - *pFrom);
    if(RFMathIsZero(nDotV))
    {
        return 0;
    }

    float t = (pPlaneNormal->Dot(*pPlaneNormal - *pFrom)) / nDotV;
    if(RFMathIsZero(t))
    {
        return pFrom;
    }
    else
    {
        return &(*pFrom + t * (*pTo - *pFrom));
    }    
}