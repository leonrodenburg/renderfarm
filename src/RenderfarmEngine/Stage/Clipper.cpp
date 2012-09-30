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
    for(unsigned int i = 0; i < this->_pOutput->size(); ++i)
    {
        delete this->_pOutput->at(i);
    }

    std::vector<RFMath::Vector3*> outputList;
    std::vector<RFMath::Vector3*> inputList;
    float dot;
    float lastDot;

    for(unsigned int i = 0; i < this->_pBuffer->size(); i += 3)
    {
        outputList.clear();
        outputList.push_back(this->_pBuffer->at(i));
        outputList.push_back(this->_pBuffer->at(i + 1));
        outputList.push_back(this->_pBuffer->at(i + 2));

        for(int j = 0; j < 6; ++j)
        {
            inputList = outputList;
            outputList.clear();

            if(inputList.size() > 0)
            {
                RFMath::Vector3* pLast = inputList.back();
                for(unsigned int k = 0; k < inputList.size(); ++k)
                {
                    dot = inputList.at(k)->Dot(this->_planeNormals[j]) - 1.0f;
                    lastDot = pLast->Dot(this->_planeNormals[j]) - 1.0f;

                    if(dot <= 0.0f && lastDot <= 0.0f)
                    {
                        outputList.push_back(inputList.at(k));
                    }
                    else if(dot > 0.0f && lastDot <= 0.0f)
                    {
                        RFMath::Vector3 intersection = this->_CalculateIntersection(pLast, inputList.at(k), &this->_planeNormals[j]);
                        RFMath::Vector3* pAdd = new RFMath::Vector3(intersection);
                        outputList.push_back(pAdd);
                    }
                    else if(dot <= 0.0 && lastDot > 0.0f)
                    {
                        RFMath::Vector3 intersection = this->_CalculateIntersection(pLast, inputList.at(k), &this->_planeNormals[j]);
                        RFMath::Vector3* pAdd = new RFMath::Vector3(intersection);
                        outputList.push_back(pAdd);

                        outputList.push_back(inputList.at(k));
                    }

                    /*if(dot <= 0.0f)
                    {
                        if(lastDot > 0.0f)
                        {
                            RFMath::Vector3 intersection = this->_CalculateIntersection(pLast, inputList.at(k), &this->_planeNormals[j]);
                            RFMath::Vector3* pAdd = new RFMath::Vector3(intersection);
                            outputList.push_back(pAdd);
                        }

                        outputList.push_back(inputList.at(k));
                    }
                    else if(lastDot <= 0.0f)
                    {
                        RFMath::Vector3 intersection = this->_CalculateIntersection(pLast, inputList.at(k), &this->_planeNormals[j]);
                        RFMath::Vector3* pAdd = new RFMath::Vector3(intersection);
                        outputList.push_back(pAdd);
                    }*/

                    pLast = inputList.at(k);
                }
            } 
        }

        for(unsigned int m = 0; m < outputList.size(); ++m)
        {
            std::cout << *outputList.at(m) << std::endl;
            this->_pOutput->push_back(outputList.at(m));
        }

        std::cout << "<< Triangle" << std::endl;
        std::cout << std::endl;

        /*RFMath::Vector3* pLast = outputList[2];

        float dot = 0.0f;

        for(int j = 0; j < 3; ++j)
        {
            
            if(dot > 0.0f)
            {
                RFMath::Vector3 intersect = this->_CalculateIntersection(pLast, outputList[j], &this->_planeNormals[0]);
                if(intersect.IsZero())
                {
                    std::cout << *outputList[j] << " -> removed" << std::endl;
                }
            }

            pLast = outputList[j];
        }

        std::cout << std::endl;*/
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
RFMath::Vector3 RFStage::Clipper::_CalculateIntersection(RFMath::Vector3* pFrom, RFMath::Vector3* pTo, RFMath::Vector3* pPlaneNormal)
{
    float nDotV = pPlaneNormal->Dot(*pTo - *pFrom);
    if(RFMathIsZero(nDotV))
    {
        return RFMath::Vector3();
    }

    float t = pPlaneNormal->Dot(*pPlaneNormal - *pFrom) / nDotV;
    return *pFrom + (t * (*pTo - *pFrom));  
}