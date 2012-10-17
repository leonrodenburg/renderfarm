#include "Rasterizer.h"

/**
 * Default constructor.
 */
RFStage::Rasterizer::Rasterizer(unsigned int windowWidth, unsigned int windowHeight)
{
    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;

    this->_pOutput = new unsigned int[(this->_windowWidth * 3) * this->_windowHeight];

    this->_clearRed = 0;
    this->_clearGreen = 0;
    this->_clearBlue = 80;

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Rasterizer initialized...");
#endif
}

/**
 * Destructor.
 */
RFStage::Rasterizer::~Rasterizer()
{
    delete[] this->_pOutput;

#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log("Rasterizer destroyed...");
#endif
}

/**
 * Bind a buffer to the rasterizer stage.
 *
 * @param pBuffer
 */
void RFStage::Rasterizer::BindBuffer(std::vector<RFGeometry::Vertex*>* pBuffer)
{
    this->_pBuffer = pBuffer;
}

/**
 * Set the clear colors used.
 *
 * @param red
 * @param green
 * @param blue
 */
void RFStage::Rasterizer::SetClearColor(unsigned int red, unsigned int green, unsigned int blue)
{
    this->_clearRed = red;
    this->_clearGreen = green;
    this->_clearBlue = blue;
}

/**
 * Rasterize the buffer and return the resulting pixel colors. Pixel colors are
 * output in the order RGB.
 *
 * @return Array of pixel colors
 */
unsigned int* RFStage::Rasterizer::Rasterize()
{
    this->_Clear();

    std::vector<RFMath::Vector3*> triangle;

    for(unsigned int i = 0; i < this->_pBuffer->size(); i += 3)
    {
        float* left = new float[this->_windowHeight];
        float* right = new float[this->_windowHeight];

        RFGeometry::Vertex* v1 = this->_pBuffer->at(i);
        RFGeometry::Vertex* v2 = this->_pBuffer->at(i + 1);
        RFGeometry::Vertex* v3 = this->_pBuffer->at(i + 2);

        RFMath::Vector3* p1 = v1->GetPosition();
        RFMath::Vector3* p2 = v2->GetPosition();
        RFMath::Vector3* p3 = v3->GetPosition();

        float side1 = (*p1 - *p3).Length();
        float side2 = (*p2 - *p1).Length();
        float side3 = (*p3 - *p2).Length();
        float area = RFMathArea(side1, side2, side3);

        triangle.push_back(p1);
        triangle.push_back(p2);
        triangle.push_back(p3);

        RFMath::Vector3* last = triangle.back();

        for(unsigned int k = 0; k < triangle.size(); ++k)
        {
            float x1 = last->GetX();
            float y1 = last->GetY();
            float x2 = triangle.at(k)->GetX();
            float y2 = triangle.at(k)->GetY();

            float dx = x2 - x1;
            float dy = y2 - y1;

            if(dy != 0)
            {
                float gradient = dx / dy;

                float ey = floor(y1) - y1;
                float ex = gradient * ey;

                float Ax = x1 + ex;
                int Ay = (int)floor(y1);

                int By = (int)floor(y2);

                float x = Ax;

                if(Ay < By)
                {
                    for(int y = Ay; y < By; ++y)
                    {
                        right[y] = x;
                        x += gradient;
                    }
                }
                else
                {
                    for(int y = Ay; y > By; --y)
                    {
                        left[y] = x;
                        x -= gradient;
                    }
                }
            }
            else
            {
                left[(int)y1] = x1;
                right[(int)y1] = x2;
            }

            last = triangle.at(k);
        }

        for(unsigned int y = 0; y < this->_windowHeight; ++y)
        {
            int xStart = (int)floor(left[y]);
            int xEnd = (int)floor(right[y]);

            if(xStart > 0 && xEnd > 0)
            {
                int xFirst = y * (this->_windowWidth * 3) + (xStart * 3);

                for(int x = 0; x < (xEnd - xStart); ++x)
                {
                    int xCurrent = xFirst + (x * 3);

                    RFMath::Vector3 vecCurrent((float)xStart + x, (float)y, 0.0f);

                    unsigned int colors[3];
                    this->_GetPixelColor(v1, v2, v3, area, &vecCurrent, colors);
                    this->_pOutput[xCurrent] = colors[0];
                    this->_pOutput[xCurrent + 1] = colors[1];
                    this->_pOutput[xCurrent + 2] = colors[2];
                }
            }
        }

        delete[] left;
        delete[] right;

        triangle.clear();
    }

    return this->_pOutput;
}

/**
 * Clear the output buffer with the clear colors.
 */
void RFStage::Rasterizer::_Clear()
{
    for(unsigned int y = 0; y < this->_windowHeight; ++y)
    {
        for(unsigned int x = 0; x < (this->_windowWidth * 3); x += 3)
        {
            this->_pOutput[y * (this->_windowWidth * 3) + x] = this->_clearRed;
            this->_pOutput[y * (this->_windowWidth * 3) + x + 1] = this->_clearGreen;
            this->_pOutput[y * (this->_windowWidth * 3) + x + 2] = this->_clearBlue;
        }
    }
}

/**
 * Calculate the pixel color using barycentric interpolation.
 *
 * @param v1
 * @param v2
 * @param v3
 * @param area
 * @param pCurrent
 *
 * @return Array of colors
 */
void RFStage::Rasterizer::_GetPixelColor(RFGeometry::Vertex* v1, RFGeometry::Vertex* v2, RFGeometry::Vertex* v3, float area, RFMath::Vector3* pCurrent, unsigned int* pOut)
{   
    RFMath::Vector3* x1 = v1->GetColor();
    RFMath::Vector3* x2 = v2->GetColor();
    RFMath::Vector3* x3 = v3->GetColor();

    float area1dist1 = (*v2->GetPosition() - *pCurrent).Length();
    float area1dist2 = (*v3->GetPosition() - *v2->GetPosition()).Length();
    float area1dist3 = (*pCurrent - *v3->GetPosition()).Length();
    float area1 = RFMathArea(area1dist1, area1dist2, area1dist3);

    float area2dist1 = (*v3->GetPosition() - *pCurrent).Length();
    float area2dist2 = (*v1->GetPosition() - *v3->GetPosition()).Length();
    float area2dist3 = (*pCurrent - *v1->GetPosition()).Length();
    float area2 = RFMathArea(area2dist1, area2dist2, area2dist3);

    float area3dist1 = (*v1->GetPosition() - *pCurrent).Length();
    float area3dist2 = (*v2->GetPosition() - *v1->GetPosition()).Length();
    float area3dist3 = (*pCurrent - *v2->GetPosition()).Length();
    float area3 = RFMathArea(area3dist1, area3dist2, area3dist3);

    float x1perc = area1 / area;
    float x2perc = area2 / area;
    float x3perc = area3 / area;

    RFMath::Vector3 final = (x1perc * *x1) + (x2perc * *x2) + (x3perc * *x3);

    pOut[0] = (int)RFMathClamp(final.GetX(), 0.0f, 255.0f);
    pOut[1] = (int)RFMathClamp(final.GetY(), 0.0f, 255.0f);
    pOut[2] = (int)RFMathClamp(final.GetZ(), 0.0f, 255.0f);
}