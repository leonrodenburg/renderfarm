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
    this->_clearBlue = 0;
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

    float left[600];
    float right[600];

    std::vector<RFMath::Vector3> triangle;

    triangle.push_back(RFMath::Vector3(0.0f, 0.0f, 0.0f));
    triangle.push_back(RFMath::Vector3(700.0f, 100.0f, 0.0f));
    triangle.push_back(RFMath::Vector3(200.0f, 500.0f, 0.0f));

    RFMath::Vector3 last = triangle.back();
    for(int i = 0; i < 3; ++i)
    {
        float x1 = last[0];
        float y1 = last[1];
        float x2 = triangle.at(i)[0];
        float y2 = triangle.at(i)[1];

        float dx = x2 - x1;
        float dy = y2 - y1;

        if(dy != 0)
        {
            float gradient = dx / dy;

            float ey = floor(y1 + 1) - y1;
            float ex = gradient * ey;

            float Ax = x1 + ex;
            int Ay = floor(y1 + 1);

            int By = floor(y2);

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

        last = triangle.at(i);
    }

    for(int y = 0; y < this->_windowHeight; ++y)
    {
        int xStart = floor(left[y]);
        int xEnd = floor(right[y]);

        for(int x = xStart; x < xEnd; ++x)
        {
            this->_pOutput[y * (this->_windowWidth * 3) + (x * 3)] = 255;
            this->_pOutput[y * (this->_windowWidth * 3) + (x * 3) + 1] = 255;
            this->_pOutput[y * (this->_windowWidth * 3) + (x * 3) + 2] = 255;
        }
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