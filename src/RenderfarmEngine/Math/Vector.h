#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace RFMath
{
	class __declspec(dllexport) Vector
	{
	public:
		Vector();
		Vector(float x, float y, float z);
		virtual ~Vector();
	private:
		float _x;
		float _y;
		float _z;
	};
}


#endif