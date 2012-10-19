#include "Rasterizer.h"

/**
 * Default constructor.
 */
RFStage::Rasterizer::Rasterizer(unsigned int windowWidth, unsigned int windowHeight)
{
    this->_windowWidth = windowWidth;
    this->_windowHeight = windowHeight;

    this->_pOutput = new unsigned int[(this->_windowWidth * 3) * this->_windowHeight];
    this->_pDepthBuffer = new float[this->_windowWidth * this->_windowHeight];

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
    delete[] this->_pDepthBuffer;
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
    // Clear depth and frame buffer
    this->_Clear();

    std::vector<RFMath::Vector3*> triangle;

    // Loop over triangles
    for(unsigned int i = 0; i < this->_pBuffer->size(); i += 3)
    {
        // Define arrays and get data from vertices
        float* left = new float[this->_windowHeight];
        float* right = new float[this->_windowHeight];

        for(unsigned int k = 0; k < this->_windowHeight; ++k)
        {
            left[k] = -1.0f;
            right[k] = -1.0f;
        }

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

        float yMin = p1->GetY();
        yMin = (p2->GetY() < yMin) ? p2->GetY() : yMin;
        yMin = (p3->GetY() < yMin) ? p3->GetY() : yMin;
        unsigned int yMinInt = (unsigned int)floor(yMin);

        float yMax = p1->GetY();
        yMax = (p2->GetY() > yMax) ? p2->GetY() : yMax;
        yMax = (p3->GetY() > yMax) ? p3->GetY() : yMax;
        unsigned int yMaxInt = (unsigned int)floor(yMax);

        RFMath::Vector3* last = triangle.back();

        // Scan convert triangle and calculate left and right boundaries
        for(unsigned int k = 0; k < triangle.size(); ++k)
        {
            float x1 = last->GetX();
            float y1 = last->GetY();
            float x2 = triangle.at(k)->GetX();
            float y2 = triangle.at(k)->GetY();

            float dx = x2 - x1;
            float dy = y2 - y1;

            if(!RFMathIsZero(dy))
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
                left[(int)(y1 + 0.5f)] = x1;
                right[(int)(y1 + 0.5f)] = x2;
            }

            last = triangle.at(k);
        }

        // Loop over scanlines
        for(unsigned int y = yMinInt; y < yMaxInt; ++y)
        {
            // Find boundaries
            int xStart = (int)floor(left[y]);
            int xEnd = (int)floor(right[y]);

            // If boundaries are valid
            if(xStart >= 0 && xEnd >= xStart)
            {
                int xFirst = y * (this->_windowWidth * 3) + (xStart * 3);

                // Loop from left boundary to right boundary
                for(int x = 0; x < (xEnd - xStart); ++x)
                {
                    // Calculate interpolated values
                    int xCurrent = xFirst + (x * 3);

                    RFMath::Vector3 position;
                    RFMath::Vector3 color;

                    this->_Interpolate(v1, v2, v3, area, xStart + x, y, &position, &color);

                    // Depth test
                    if(position.GetZ() < this->_pDepthBuffer[y * xStart + x])
                    {
                        // Draw pixel
                        this->_pOutput[xCurrent] = (int)RFMathClamp(color.GetX(), 0.0f, 255.0f);
                        this->_pOutput[xCurrent + 1] = (int)RFMathClamp(color.GetY(), 0.0f, 255.0f);
                        this->_pOutput[xCurrent + 2] = (int)RFMathClamp(color.GetZ(), 0.0f, 255.0f);

                        this->_pDepthBuffer[y * xStart + x] = position.GetZ();
                    }
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
            this->_pDepthBuffer[y * (x / 3)] = FLT_MAX;

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
void RFStage::Rasterizer::_Interpolate(RFGeometry::Vertex* v1, RFGeometry::Vertex* v2, RFGeometry::Vertex* v3, float area, int xCurrent, int yCurrent, RFMath::Vector3* pPosOut, RFMath::Vector3* pColorOut)
{   
    RFMath::Vector3* p1 = v1->GetPosition();
    RFMath::Vector3* p2 = v2->GetPosition();
    RFMath::Vector3* p3 = v3->GetPosition();

    RFMath::Vector3* c1 = v1->GetColor();
    RFMath::Vector3* c2 = v2->GetColor();
    RFMath::Vector3* c3 = v3->GetColor();

    RFMath::Vector3 current((float)xCurrent, (float)yCurrent, 0.0f);

    float area1dist1 = (*v2->GetPosition() - current).Length();
    float area1dist2 = (*v3->GetPosition() - *v2->GetPosition()).Length();
    float area1dist3 = (current - *v3->GetPosition()).Length();
    float area1 = RFMathArea(area1dist1, area1dist2, area1dist3);

    float area2dist1 = (*v3->GetPosition() - current).Length();
    float area2dist2 = (*v1->GetPosition() - *v3->GetPosition()).Length();
    float area2dist3 = (current - *v1->GetPosition()).Length();
    float area2 = RFMathArea(area2dist1, area2dist2, area2dist3);

    float area3dist1 = (*v1->GetPosition() - current).Length();
    float area3dist2 = (*v2->GetPosition() - *v1->GetPosition()).Length();
    float area3dist3 = (current - *v2->GetPosition()).Length();
    float area3 = RFMathArea(area3dist1, area3dist2, area3dist3);

    float x1perc = area1 / area;
    float x2perc = area2 / area;
    float x3perc = area3 / area;

    RFMath::Vector3 finalPosition = (x1perc * *p1) + (x2perc * *p2) + (x3perc * *p3);
    RFMath::Vector3 finalColor = (x1perc * *c1) + (x2perc * *c2) + (x3perc * *c3);

    pPosOut->SetX(finalPosition.GetX());
    pPosOut->SetY(finalPosition.GetY());
    pPosOut->SetZ(finalPosition.GetZ());

    pColorOut->SetX(RFMathClamp(finalColor.GetX(), 0.0f, 255.0f));
    pColorOut->SetY(RFMathClamp(finalColor.GetY(), 0.0f, 255.0f));
    pColorOut->SetZ(RFMathClamp(finalColor.GetZ(), 0.0f, 255.0f));
}