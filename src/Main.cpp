#include <iostream>
#include <cstdio>

#include "Math/Matrix.h"

int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

    RFMath::Matrix matTrans;
    matTrans.Translate(10.0f, 0.0f, 0.0f);

    RFMath::Matrix matScale;
    matScale.Scale(10.0f, 1.0f, 1.0f);

    RFMath::Matrix matRot;
    matRot.RotationY(RFMathDegToRad(90));

    RFMath::Matrix mat = matScale * matTrans * matRot;

    RFMath::Vector3 vec(10.0f, 5.0f, 0.0f);
    RFMath::Vector3 result = vec * mat;

    std::cout << result << std::endl;

    std::getchar();
    return 0;
}