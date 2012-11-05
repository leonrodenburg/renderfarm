#include "Clipper.h"
#include <iostream>

/**
 * Default constructor.
 */
RFStage::Clipper::Clipper()
{
    this->_pOutput = new std::vector<RFGeometry::Vertex*>();

    _planeNormals[0] = RFMath::Vector3::xAxis;
    _planeNormals[1] = RFMath::Vector3::yAxis;
    _planeNormals[2] = RFMath::Vector3::zAxis;
    _planeNormals[3] = -RFMath::Vector3::xAxis;
    _planeNormals[4] = -RFMath::Vector3::yAxis;
    _planeNormals[5] = -RFMath::Vector3::zAxis;

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Clipper initialized...");
#endif
}

/**
 * Destructor.
 */
RFStage::Clipper::~Clipper()
{
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Clipper destroyed...");
#endif
}

/**
 * Bind a vertex buffer to the clipping stage. The vertices in the buffer
 * should be in normalized device coordinates (NDC). They will be clipped
 * against a cube with minimum point (-1, -1, -1) and maximum point
 * (1, 1, 1).
 *
 * @param pBuffer
 */
void RFStage::Clipper::BindBuffer(std::vector<RFGeometry::Vertex*>* pBuffer)
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
std::vector<RFGeometry::Vertex*>* RFStage::Clipper::Clip()
{
    this->_pOutput->clear();

    std::vector<RFGeometry::Vertex*> outputList;
    std::vector<RFGeometry::Vertex*> inputList;
    float dot;
    float lastDot;

    for(unsigned int i = 0; i < this->_pBuffer->size(); i += 3)
    {
        RFGeometry::Vertex* v1 = this->_pBuffer->at(i);
        RFGeometry::Vertex* v2 = this->_pBuffer->at(i + 1);
        RFGeometry::Vertex* v3 = this->_pBuffer->at(i + 2);

        // If the triangle is front facing (otherwise it can be clipped / culled)
        if(this->_IsFrontFacing(v1->GetPosition(), v2->GetPosition(), v3->GetPosition()))
        {
            outputList.clear();
            outputList.push_back(v1);
            outputList.push_back(v2);
            outputList.push_back(v3);

            for(int j = 0; j < 6; ++j)
            {
                inputList = outputList;
                outputList.clear();

                if(inputList.size() > 0)
                {
                    RFGeometry::Vertex* pLast = inputList.back();
                    for(unsigned int k = 0; k < inputList.size(); ++k)
                    {
                        RFGeometry::Vertex* pCurrent = inputList.at(k);
                        dot = pCurrent->GetPosition()->Dot(this->_planeNormals[j]) - 1.0f;
                        lastDot = pLast->GetPosition()->Dot(this->_planeNormals[j]) - 1.0f;

                        if(dot <= 0.0f) // Current vertex 'inside' current plane
                        {
                            if(lastDot > 0.0f) // Last vertex 'outside' current plane
                            {
                                RFMath::Vector3 intersection = this->_CalculateIntersection(pLast->GetPosition(), pCurrent->GetPosition(), &this->_planeNormals[j]);

                                if(!intersection.IsZero())
                                {
                                    RFMath::Vector3* pAdd = new RFMath::Vector3(intersection);
                                    RFGeometry::Vertex vert(pAdd, pLast->GetColor());
                                    outputList.push_back(&vert);
                                }
                            }

                            outputList.push_back(pCurrent);
                        }
                        else if(lastDot <= 0.0f) // Last vertex 'inside' current plane
                        {
                            RFMath::Vector3 intersection = this->_CalculateIntersection(pLast->GetPosition(), pCurrent->GetPosition(), &this->_planeNormals[j]);

                            if(!intersection.IsZero())
                            {
                                RFMath::Vector3* pAdd = new RFMath::Vector3(intersection);
                                RFGeometry::Vertex vert(pAdd, pLast->GetColor());
                                outputList.push_back(&vert);
                            }
                        }

                        pLast = pCurrent;
                    }
                } 
            }

            // Post process if result is a polygon (not a triangle anymore)
            if(outputList.size() > 3)
            {
                std::vector<RFGeometry::Vertex*> triangles;
                triangles.push_back(outputList.at(0));
                triangles.push_back(outputList.at(1));
                triangles.push_back(outputList.at(2));

                triangles.push_back(outputList.at(2));
                triangles.push_back(outputList.at(3));
                triangles.push_back(outputList.at(0));

                if(outputList.size() > 4)
                {
                    triangles.push_back(outputList.at(3));
                    triangles.push_back(outputList.at(4));
                    triangles.push_back(outputList.at(0));
                }

                outputList.clear();
                
                for(unsigned int i = 0; i < triangles.size(); ++i)
                {
                    outputList.push_back(triangles.at(i));
                }
            }

            for(unsigned int m = 0; m < outputList.size(); ++m)
            {
                this->_pOutput->push_back(outputList.at(m));
            }
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

/**
 * Return true if the triangle formed by the three vertices is front facing,
 * false if it is not. If the triangle is not front-facing, it can be culled.
 *
 * @param p1
 * @param p2
 * @param p3
 *
 * @return True if front-facing, false if not
 */
bool RFStage::Clipper::_IsFrontFacing(RFMath::Vector3* p1, RFMath::Vector3* p2, RFMath::Vector3* p3)
{
    // Calculate normal of triangle surface
    RFMath::Vector3 line1 = *p2 - *p1;
    RFMath::Vector3 line2 = *p3 - *p1;
    RFMath::Vector3 normal = line1.Cross(line2);

    // Calculate triangle -> camera vector
    RFMath::Vector3 origin(0.0f, 0.0f, -1.0f);
    RFMath::Vector3 toCamera = *p1 - origin;

    // Normalize vectors
    toCamera = toCamera.Normalize();
    normal = normal.Normalize();

    // Dot triangle normal with camera vector
    float dot = toCamera.Dot(normal);

    // If the angle is equal to or larger than 90 degrees 
    if(dot > 0.0f)
    {
        return false;
    }

    return true;
}