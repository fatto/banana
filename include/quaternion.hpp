//
//  quaternion.hpp
//  banana
//
//  Created by Marco Fattorel on 28/01/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#ifndef banana_quaternion_hpp
#define banana_quaternion_hpp

#include "mathematics.hpp"
#include <string>

namespace Mathematics
{
	struct Quaternion
	{
		float4 quat;
		
		Quaternion() = default;
		Quaternion(float4 q)
		{
			quat = q;
		}
		// real component w immaginary component x y z
		Quaternion(float w, float x, float y, float z)
		{
			quat.xyzw = {x, y, z, w};
		}
		// angle axis
		Quaternion(float angle, const Vector3& axis)
		{
			const float a = angle * 0.5f;
			const float s = sin(a);
			const float c = cos(a);
			quat.w = c;
			quat.xyz = axis.vec.xyz * s;
		}
		Quaternion(const Matrix44& matrix)
		{
			const float44& mat = matrix.mat;
			const float trace = mat.s0 + mat.s5 + mat.sa + mat.sf;
			
			if(trace > 0.f)
			{
				float root = sqrt(1.f + trace); // 2w
				quat.w = .5f * root;
				root = 0.5f / root; // 1/4w
				quat.x = (mat.s6 - mat.s9) * root;
				quat.y = (mat.s8 - mat.s2) * root;
				quat.z = (mat.s1 - mat.s4) * root;
			}
			else
			{
				static int next[3] = { 2, 3, 1};
				int i = 1;
				if(matrix(2,2) > matrix(1,1)) i = 2;
				if(matrix(3,3) > matrix(i,i)) i = 3;
				int j = next[i];
				int k = next[j];
				
				float root = sqrt(matrix(i,i) - matrix(j,j) - matrix(k,k) + 1.f);
				quat[i] = .5f * root;
				root = .5f / root;
				quat.w = (matrix(k,j) - matrix(j,k)) * root;
				quat[j] = (matrix(j,i) + matrix(i,j)) * root;
				quat[k] = (matrix(k,i) + matrix(i,k)) * root;
			}
		}
		Matrix44 matrix() const
		{
			float fTx  = 2.0f*quat.x;
			float fTy  = 2.0f*quat.y;
			float fTz  = 2.0f*quat.z;
			float fTwx = fTx*quat.w;
			float fTwy = fTy*quat.w;
			float fTwz = fTz*quat.w;
			float fTxx = fTx*quat.x;
			float fTxy = fTy*quat.x;
			float fTxz = fTz*quat.x;
			float fTyy = fTy*quat.y;
			float fTyz = fTz*quat.y;
			float fTzz = fTz*quat.z;
			
			float44 ret;
			ret.s048 = {1.f-(fTyy+fTzz), fTxy-fTwz, fTxz+fTwy};
			ret.s159 = {fTxy+fTwz, 1.0f-(fTxx+fTzz), fTyz-fTwx};
			ret.s26a = {fTxz-fTwy, fTyz+fTwx, 1.0f-(fTxx+fTyy)};
			ret.s37bcde = 0.f;
			ret.sf = 1.f;
			return Matrix44(ret);
		}
		void angleAxis(float& angle, Vector3& axis) const
		{
			float3 qua = quat.xyz * quat.xyz;
			const float squareLength = qua.x + qua.y + qua.z;
			
			if(squareLength > epsilonSquared)
			{
				angle = 2.f * acos(quat.w);
				const float inverseLength = 1.f / sqrt(squareLength);
				axis.vec = quat.xyz * inverseLength;
			}
			else
			{
				angle = 0.f;
				axis.vec = {1.f, 0.f, 0.f};
			}
		}
		void zero()
		{
			quat = {0.f, 0.f, 0.f, 0.f};
		}
		void identity()
		{
			quat = {0.f, 0.f, 0.f, 1.f};
		}
		Quaternion dot(const Quaternion& q)
		{
			float4 qq = quat * q.quat;
			return Quaternion(qq.x + qq.y + qq.z + qq.w, 0.f, 0.f, 0.f);
		}
		void dot(const Quaternion& q, Quaternion& result)
		{
			float4 qq = quat * q.quat;
			result.quat = {qq.x + qq.y + qq.z + qq.w, 0.f, 0.f, 0.f};
		}
		Quaternion conjugate()
		{
			float4 res;
			res.xyz = -quat.xyz;
			res.w = quat.w;
			return Quaternion(res);
		}
		void conjugate(Quaternion& result) const
		{
			result.quat.xyz = -quat.xyz;
			result.quat.w = quat.w;
		}
		float length() const
		{
			float4 qq = quat * quat;
			return sqrt(qq.x + qq.y + qq.z + qq.w);
		}
		float norm() const
		{
			float4 qq = quat * quat;
			return qq.x + qq.y + qq.z + qq.w;
		}
		void normalize()
		{
			const float length = this->length();
			if(length == 0.f)
			{
				quat = {0.f, 0.f, 0.f, 1.f};
			}
			else
			{
				float inv = 1.f / length;
				quat *= inv;
			}
		}
		bool normalized() const
		{
			return equal(norm(), 1.f);
		}
		Quaternion inverse() const
		{
			const float n = norm();
			assert(n != 0);
			float4 res;
			res.xyz = -quat.xyz;
			res.w = quat.w;
			return Quaternion(res/n);
		}
		void inverse(Quaternion& result) const
		{
			const float n = norm();
			assert(n != 0);
			result.quat.xyz = -quat.xyz/n;
			result.quat.w = quat.w/n;
		}
		bool operator ==(const Quaternion& other) const
		{
			if ( equal(quat.w,other.quat.w) && equal(quat.x,other.quat.x) && equal(quat.y,other.quat.y) && equal(quat.z,other.quat.z))
				return true;
			return false;
		}
		bool operator !=(const Quaternion& other) const
		{
			return !(*this == other);
		}
		float& operator[](size_t i)
		{
			assert(i >= 0);
			assert(i <= 3);
			return *((float*)&quat+i);
		}
		const float& operator[](size_t i) const
		{
			assert(i >= 0);
			assert(i <= 3);
			return *((float*)&quat+i);
		}
		std::string to_string() const
		{
			return "w:" + std::to_string(quat.w) + " x:" + std::to_string(quat.x) + " y:" + std::to_string(quat.y) + " z:" + std::to_string(quat.z);
		}
	};
	inline Quaternion operator-(const Quaternion &a)
	{
		return Quaternion(-a.quat);
	}
	
	inline Quaternion operator+(const Quaternion &a, const Quaternion &b)
	{
		return Quaternion(a.quat + b.quat);
	}
	
	inline Quaternion operator-(const Quaternion &a, const Quaternion &b)
	{
		return Quaternion(a.quat - b.quat);
	}
	
	inline Quaternion operator*(const Quaternion &a, const Quaternion &b)
	{
		const float4& qa = a.quat;
		const float4& qb = b.quat;
		return Quaternion( qa.w*qb.w - qa.x*qb.x - qa.y*qb.y - qa.z*qb.z,
						  qa.w*qb.x + qa.x*qb.w + qa.y*qb.z - qa.z*qb.y,
						  qa.w*qb.y - qa.x*qb.z + qa.y*qb.w + qa.z*qb.x,
						  qa.w*qb.z + qa.x*qb.y - qa.y*qb.x + qa.z*qb.w );
	}
	
	inline Quaternion& operator+=(Quaternion &a, const Quaternion &b)
	{
		a.quat += b.quat;
		return a;
	}
	
	inline Quaternion& operator-=(Quaternion &a, const Quaternion &b)
	{
		a.quat -= b.quat;
		return a;
	}
	
	inline Quaternion& operator*=(Quaternion &a, const Quaternion &b)
	{
		const float4 qa = a.quat;
		const float4& qb = b.quat;
		a.quat.w = qa.w*qb.w - qa.x*qb.x - qa.y*qb.y - qa.z*qb.z;
		a.quat.x = qa.w*qb.x + qa.x*qb.w + qa.y*qb.z - qa.z*qb.y;
		a.quat.y = qa.w*qb.y - qa.x*qb.z + qa.y*qb.w + qa.z*qb.x;
		a.quat.z = qa.w*qb.z + qa.x*qb.y - qa.y*qb.x + qa.z*qb.w;
		return a;
	}
	
	
	inline bool operator ==(const Quaternion &q, float scalar)
	{
		if ( equal(q.quat.w,scalar) && equal(q.quat.x,0) && equal(q.quat.y,0) && equal(q.quat.z,0))
			return true;
		return false;
	}
	
	inline bool operator !=(const Quaternion &q, float scalar)
	{
		return !(q==scalar);
	}
	
	inline bool operator ==(float scalar, const Quaternion &q)
	{
		if ( equal(q.quat.w,scalar) && equal(q.quat.x,0) && equal(q.quat.y,0) && equal(q.quat.z,0))
			return true;
		return false;
	}
	
	inline bool operator !=(float scalar, const Quaternion &q)
	{
		return !(q==scalar);
	}
	
	inline Quaternion operator*(const Quaternion &a, float s)
	{
		return Quaternion(a.quat * s);
	}
	
	inline Quaternion operator/(const Quaternion &a, float s)
	{
		return Quaternion(a.quat / s);
	}
	
	inline Quaternion& operator*=(Quaternion &a, float s)
	{
		a.quat *= s;
		return a;
	}
	
	inline Quaternion& operator/=(Quaternion &a, float s)
	{
		a.quat /= s;
		return a;
	}
	
	inline Quaternion operator*(float s, const Quaternion &a)
	{
		return Quaternion(a.quat * s);
	}
	
	inline Quaternion& operator*=(float s, Quaternion &a)
	{
		a.quat *= s;
		return a;
	}
	
	inline Quaternion slerp(const Quaternion &a, const Quaternion &b, float t)
	{
		assert(t>=0);
		assert(t<=1);
		
		float flip = 1;
		
		const float4 qq = a.quat * b.quat;
		float cosine = qq.x + qq.y + qq.z + qq.w;
		
		if (cosine<0)
		{
			cosine = -cosine;
			flip = -1;
		}
		
		if ((1-cosine)<epsilon)
			return a * (1-t) + b * (t*flip);
		
		float theta = (float)acos(cosine);
		float sine = (float)sin(theta);
		float beta = (float)sin((1-t)*theta) / sine;
		float alpha = (float)sin(t*theta) / sine * flip;
		
		return a * beta + b * alpha;
	}
}

#endif
