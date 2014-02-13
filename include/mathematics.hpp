//
//  mathematics.hpp
//  banana
//
//  Created by Marco Fattorel on 27/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#ifndef banana_mathematics_hpp
#define banana_mathematics_hpp

#include <cmath>
#include <cfloat>
#include <cassert>

namespace Mathematics
{
	const float tau = 2.f * M_PI;
	const float epsilon = FLT_EPSILON;
	const float epsilonSquared = epsilon * epsilon;
	
	typedef float float3 __attribute__((ext_vector_type(3)));
	typedef float float4 __attribute__((ext_vector_type(4)));
	typedef float float44 __attribute__((ext_vector_type(4*4)));
	
	inline bool equal(float a, float b)
	{
		const float d = a - b;
		if(d < epsilon && d > -epsilon)
			return true;
		return false;
	}
	inline float min(float a, float b)
	{
		return a < b ? a : b;
	}
	inline float max(float a, float b)
	{
		return a > b ? a : b;
	}
	inline unsigned int sign(float v)
	{
		return std::signbit(v);
	}
	inline float abs(float v)
	{
		*(int *)&v &= 0x7fffffff;
		return v;
	}
	inline float lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}
	inline float snap(float p, float grid)
	{
		return grid ? floor((p + grid * 0.5) / grid) * grid : p;
	}
	inline float clamp(float x, float minVal, float maxVal)
	{
		return min(max(x, minVal), maxVal);
	}
}

#include "vector.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"

#endif
