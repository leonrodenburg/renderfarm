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
    this->_clearBlue = 255;
}

/**
 * Destructor.
 */
RFStage::Rasterizer::~Rasterizer()
{
    delete[] this->_pOutput;
}

/**
 * Bind a buffer to the rasterizer stage.
 *
 * @param pBuffer
 */
void RFStage::Rasterizer::BindBuffer(std::vector<RFMath::Vector3*>* pBuffer)
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

    this->_pBuffer->push_back(&RFMath::Vector3(10.0f, 10.0f, 0.0f));
    this->_pBuffer->push_back(&RFMath::Vector3(60.0f, 10.0f, 0.0f));
    this->_pBuffer->push_back(&RFMath::Vector3(10.0f, 60.0f, 0.0f));

    std::vector<RFMath::Vector3*> triangle;

    for(unsigned int i = 0; i < this->_pBuffer->size(); i += 3)
    {
        float* left = new float[this->_windowHeight];
        float* right = new float[this->_windowHeight];

        RFMath::Vector3* p1 = this->_pBuffer->at(i);
        RFMath::Vector3* p2 = this->_pBuffer->at(i + 1);
        RFMath::Vector3* p3 = this->_pBuffer->at(i + 2);

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

                float ey = floor(y1 + 1) - y1;
                float ex = gradient * ey;

                float Ax = x1 + ex;
                int Ay = (int)floor(y1 + 1);

                int By = (int)floor(y2);

                float x = Ax;

                if(Ay < By)
                {
                    for(int y = Ay; y <= By; ++y)
                    {
                        right[y] = x;
                        x += gradient;
                    }
                }
                else
                {
                    for(int y = Ay; y >= By; --y)
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

            for(int x = xStart; x < xEnd; ++x)
            {
                this->_pOutput[y * (this->_windowWidth * 3) + (x * 3)] = 255;
                this->_pOutput[y * (this->_windowWidth * 3) + (x * 3) + 1] = 0;
                this->_pOutput[y * (this->_windowWidth * 3) + (x * 3) + 2] = 0;
            }
        }

        delete[] left;
        delete[] right;

        triangle.clear();
    }

    return this->_pOutput;
}

/**
 * Set whether or not the rasterizer should output wireframe data.
 *
 * @param wireframe
 */
void RFStage::Rasterizer::SetWireframe(bool wireframe)
{
    this->_wireframe = wireframe;
}

/**
 * Set whether or not the rasterizer should output solid triangles
 * (turn this off and wireframe on to only show wireframe).
 *
 * @param solid
 */
void RFStage::Rasterizer::SetSolid(bool solid)
{
    this->_solid = solid;
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