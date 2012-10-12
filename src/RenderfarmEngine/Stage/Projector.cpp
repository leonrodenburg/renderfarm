#include "Projector.h"
#include <cmath>

/**
 * Constructor setting the near and far view clipping planes, the
 * view angle and the screen size.
 *
 * @param nearView
 * @param farView
 * @param fieldOfView
 * @param windowWidth
 * @param windowHeight
 */
RFStage::Projector::Projector(float nearView, float farView, float fieldOfView, unsigned int windowWidth, unsigned int windowHeight)
{
    this->_pOutput = new std::vector<RFMath::Vector3*>();
    this->_pOutputMap = new std::vector<RFMath::Vector3*>();
    
    this->_nearView = nearView;
    this->_farView = farView;
    this->_fieldOfView = fieldOfView;

    this->_projectionTransform = RFMath::Matrix();
    this->_projectionTransform.Identity();

    this->_mapTransform = RFMath::Matrix();
    this->_mapTransform.Identity();
    
    float aspectRatio, h, w, Q;
    aspectRatio = (float)windowWidth / windowHeight;
    w = (float)1 / tanf(fieldOfView * 0.5f);
    h = (float)1 / tanf((fieldOfView / aspectRatio) * 0.5f);
    Q = farView / (farView - nearView);

    RFMath::Matrix projectionMatrix;
    projectionMatrix.GetPointer()[0] = w;
    projectionMatrix.GetPointer()[5] = -h;
    projectionMatrix.GetPointer()[10] = Q;
    projectionMatrix.GetPointer()[14] = Q * nearView;
    projectionMatrix.GetPointer()[11] = 1.0f;

    this->_projectionTransform = projectionMatrix;

    // Calculate screen map matrix
    RFMath::Matrix translationMatrix;
    translationMatrix.Translate(1.0f, 1.0f, 0.0f);

    RFMath::Matrix scalingMatrix;
    scalingMatrix.ScaleX(windowWidth / 2.0f);
    scalingMatrix.ScaleY(windowHeight / 2.0f);

    this->_mapTransform = scalingMatrix * translationMatrix;

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Projector initialized...");
#endif
}

/**
 * Destructor.
 */
RFStage::Projector::~Projector()
{
    for(unsigned int i = 0; i < this->_pOutputMap->size(); ++i)
    {
        delete this->_pOutputMap->at(i);
    }

    delete this->_pOutputMap;

    for(unsigned int i = 0; i < this->_pOutput->size(); ++i)
    {
        delete this->_pOutput->at(i);
    }

    delete this->_pOutput;

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Projector destroyed...");
#endif
}

/**
 * Bind a buffer to the projection stage.
 *
 * @param pBuffer
 */
void RFStage::Projector::BindBuffer(std::vector<RFMath::Vector3*>* pBuffer)
{
    this->_pBuffer = pBuffer;
}

/**
 * Project the vertices in the buffer against the 2D plane
 * so they can be mapped to the screen coordinates.
 *
 * @return Projected vertices
 */
std::vector<RFMath::Vector3*>* RFStage::Projector::Project()
{
    for(unsigned int i = 0; i < this->_pOutput->size(); ++i)
    {
        delete this->_pOutput->at(i);
    }
    this->_pOutput->clear();

    for(unsigned int i = 0; i < this->_pBuffer->size(); ++i)
    {
        RFMath::Vector3 vec = *this->_pBuffer->at(i);
        RFMath::Vector4 vec4(vec, 1.0f);
        vec4 = vec4 * this->_projectionTransform;

        RFMath::Vector3* pNew = new RFMath::Vector3();
        pNew->SetX(vec4[0] / vec4[3]);
        pNew->SetY(vec4[1] / vec4[3]);
        pNew->SetZ(vec4[2] / vec4[3]);

        this->_pOutput->push_back(pNew);
    }

    return this->_pOutput;
}

/**
 * Map the current buffer to screen coordinates.
 *
 * @return Buffer in screen coordinates
 */
std::vector<RFMath::Vector3*>* RFStage::Projector::Map()
{
    for(unsigned int i = 0; i < this->_pOutputMap->size(); ++i)
    {
        delete this->_pOutputMap->at(i);
    }
    this->_pOutputMap->clear();

    for(unsigned int i = 0; i < this->_pBuffer->size(); ++i)
    {
        RFMath::Vector3 vec = *this->_pBuffer->at(i);
        vec = this->_mapTransform.Transform(vec);

        RFMath::Vector3* pNew = new RFMath::Vector3();
        pNew->SetX(vec[0]);
        pNew->SetY(vec[1]);
        pNew->SetZ(vec[2]);

        this->_pOutputMap->push_back(pNew);
    }

    return this->_pOutputMap;
}