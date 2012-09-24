#include <iostream>
#include <cstdio>

#include "Math/Matrix.h"

int main(int argc, char** argv)
{
    std::cout << "Renderfarm 0.1a - by Leon Rodenburg" << std::endl;

    // Test transformations
    RFMath::Matrix matTrans;
    matTrans.Translate(10.0f, 0.0f, 0.0f);

    RFMath::Matrix matScale;
    matScale.Scale(1.0f, 10.0f, 1.0f);

    RFMath::Matrix matRot;
    matRot.Rotate(RFMathDegToRad(90), 0.0f, RFMathDegToRad(90));

    RFMath::Matrix mat = matTrans * matScale * matRot;

    RFMath::Vector3 vec(10.0f, 5.0f, 0.0f);
    RFMath::Vector3 result = mat.Transform(vec);

    std::cout << result << std::endl;

    // Test matrix inversion (result should be identity)
    RFMath::Matrix matTrans;
    matTrans.Translate(10.0f, 5.0f, 1.0f);

    RFMath::Matrix matTransInv = RFMath::Inverse(matTrans);

    RFMath::Matrix invTest = matTransInv * matTrans;

    std::cout << invTest << std::endl;

    std::getchar();
    return 0;
}