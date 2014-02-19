#ifndef banana_matrix_hpp
#define banana_matrix_hpp

#include "mathematics.hpp"
#include <string>

namespace Mathematics
{
	struct Matrix44
	{
		float44 mat;
		Matrix44() = default;
		Matrix44(float44 m)
		{
			mat = m;
		}
		Matrix44(const Vector3& a, const Vector3& b, const Vector3& c)
		{
			mat.s012 = a.vec;
			mat.s456 = b.vec;
			mat.s89a = c.vec;
			mat.s37b = 0.f;
			mat.scdef = {0.f, 0.f, 0.f, 1.f};
		}
		Matrix44& zero()
		{
			mat = 0.f;
			return *this;
		}
		Matrix44& identity()
		{
			mat.s12346789bcde = 0.f;
			mat.s05af = 1.f;
			return *this;
		}
		Matrix44& translate(float x, float y, float z)
		{
			mat.s12346789b = 0.f;
			mat.scde = {x, y, z};
			mat.s05af = 1.f;
			return *this;
		}
		Matrix44& translate(const Vector3& vector)
		{
			mat.s12346789b = 0.f;
			mat.scde = vector.vec;
			mat.s05af = 1.f;
			return *this;
		}
		Matrix44& scale(float s)
		{
			mat.s12346789bcde = 0.f;
			mat.s05af = {s, s, s, 1.f};
			return *this;
		}
		Matrix44& diagonal(float a, float b, float c, float d = 1.f)
		{
			mat.s12346789bcde = 0.f;
			mat.s05af = {a, b, c, d};
			return *this;
		}
		Matrix44& rotate(float angle, Vector3 axis)
		{
			if(axis.lengthSquared() < epsilonSquared)
			{
				identity();
			}
			else
			{
				axis.normalize();
				float c = cos(angle);
				float s = sin(angle);
				float3& axi = axis.vec;
				float3 temp = axi * (1.f - c);
				
				mat.s0 = c + temp.x * axi.x;
				mat.s1 = temp.x * axi.y + s * axi.z;
				mat.s2 = temp.x * axi.z - s * axi.y;
				
				mat.s4 = temp.y * axi.x - s * axi.z;
				mat.s5 = c + temp.y * axi.y;
				mat.s6 = temp.y * axi.z + s * axi.x;
				
				mat.s8 = temp.z * axi.x + s * axi.y;
				mat.s9 = temp.z * axi.y - s * axi.x;
				mat.sa = c + temp.z * axi.z;
				
				mat.s37bcde = 0.f;
				mat.sf = 1.f;
			}
			return *this;
		}
		Matrix44& lookat(const Vector3& eye, const Vector3& at, const Vector3& up)
		{
			Vector3 z_axis = at - eye; z_axis.normalize();
			Vector3 x_axis = z_axis.cross(up); x_axis.normalize();
			Vector3 y_axis = x_axis.cross(z_axis); y_axis.normalize();
			
			mat.s048 = x_axis.vec;
			mat.sc = -x_axis.dot(eye);
			
			mat.s159 = y_axis.vec;
			mat.sd = -y_axis.dot(eye);
			
			mat.s26a = -z_axis.vec;
			mat.se = z_axis.dot(eye);
			
			mat.s37bf = {0.f, 0.f, 0.f, 1.f};
			return *this;
		}
		Matrix44& orthographic(float l, float r, float b, float t, float n, float f)
		{
			float sx = 1.f / (r - l);
			float sy = 1.f / (t - b);
			float sz = 1.f / (f - n);
			
			mat.s0123 = {2.f*sx, 0.f, 0.f, -(r+l) * sx};
			mat.s4567 = {0.f, 2.f*sy, 0.f, -(t+b) * sy};
			mat.s89ab = {0.f, 0.f, 2.f*sz, -(n+f) * sz};
			mat.scdef = {0.f, 0.f, 0.f, 1.f};
			return *this;
		}
//		void perspective(float l, float r, float t, float b, float n, float f)
//		{
//			mat.s05a = {2.f * n / (r-l), 2.f * n / (t-b), f / (f-n)};
//			mat.se = n * f / (n-f);
//			
//			mat.s12346789cdf = 0.f;
//			mat.sb = -1.f;
//		}
		Matrix44& perspective(float fov, float aspect, float n, float f)
		{
			const float fo = 1.f / tan(fov * 0.5f);
			mat.s0 = fo/aspect;
			mat.s5 = fo;
			mat.sa = (f+n) / (n-f);
			mat.sb = -1.f;
			mat.se = (2.f * f * n) / (n - f);
			mat.s12346789cdf = 0.f;
//			const float t = tan(fov * 0.5f) * n;
//			const float b = -t;
//			const float l = aspect * b;
//			const float r = aspect * t;
//			
//			perspective(l, r, t, b, n, f);
			return *this;
		}
		// of sub 3x3 matrix
		float determinant() const
		{
			return mat.s0*mat.s5*mat.sa + mat.s4*mat.s9*mat.s2 + mat.s8*mat.s1*mat.s6 -mat.s8*mat.s5*mat.s2 -mat.s9*mat.s6*mat.s0 -mat.sa*mat.s4*mat.s1;
		}
		bool invertible() const
		{
			return !equal(determinant(), 0.f);
		}
		Matrix44 inverse() const
		{
			Matrix44 matrix;
			inverse(matrix);
			return matrix;
		}
		void inverse(Matrix44& inverse) const
		{
			const float determinant = this->determinant();
			assert(!equal(determinant, 0.f));
			float k = 1.f/determinant;
			
			float44& inv = inverse.mat;
			inv.s0 = (mat.s5 * mat.sa - mat.s6 * mat.s9) * k;
			inv.s4 = (mat.s6 * mat.s8 - mat.s4 * mat.sa) * k;
			inv.s8 = (mat.s4 * mat.s9 - mat.s5 * mat.s8) * k;

			inv.s1 = (mat.s9 * mat.s2 - mat.sa * mat.s1) * k;
			inv.s5 = (mat.sa * mat.s0 - mat.s8 * mat.s2) * k;
			inv.s9 = (mat.s8 * mat.s1 - mat.s9 * mat.s0) * k;
			
			inv.s2 = (mat.s1 * mat.s6 - mat.s2 * mat.s5) * k;
			inv.s6 = (mat.s2 * mat.s4 - mat.s0 * mat.s6) * k;
			inv.sa = (mat.s0 * mat.s5 - mat.s1 * mat.s4) * k;
			
			inv.sc = -(inv.s0 * mat.c + inv.s4 * mat.d + inv.s8 * mat.se);
			inv.sd = -(inv.s1 * mat.c + inv.s5 * mat.d + inv.s9 * mat.se);
			inv.se = -(inv.s2 * mat.c + inv.s6 * mat.d + inv.sa * mat.se);
			
			inv.s37bf = mat.s37bf;
		}
		Matrix44 transpose() const
		{
			return Matrix44(mat.s048c159d26ae37bf);
		}
//		void transform(Vector3& vector) const
//		{
//			float3 xx = vector.vec.xxx;
//			float3 yy = vector.vec.yyy;
//			float3 zz = vector.vec.zzz;
//			vector.vec = {xx * mat.s012 + yy * mat.s456 + zz * mat.s89a + mat.scde};
//		}
//		void transform(const Vector3& vector, Vector3& result) const
//		{
//			float3 xx = vector.vec.xxx;
//			float3 yy = vector.vec.yyy;
//			float3 zz = vector.vec.zzz;
//			result.vec = {xx * mat.s012 + yy * mat.s456 + zz * mat.s89a + mat.scde};
//		}
		void transform3x3(Vector3& vector) const
		{
			float3 xx = vector.vec.xxx;
			float3 yy = vector.vec.yyy;
			float3 zz = vector.vec.zzz;
			vector.vec = {xx * mat.s012 + yy * mat.s456 + zz * mat.s89a};
		}
		void transform3x3(const Vector3& vector, Vector3& result) const
		{
			float3 xx = vector.vec.xxx;
			float3 yy = vector.vec.yyy;
			float3 zz = vector.vec.zzz;
			result.vec = {xx * mat.s012 + yy * mat.s456 + zz * mat.s89a + mat.scde};
		}
//		void add(const Matrix44& matrix)
//		{
//			mat += matrix.mat;
//		}
//		void subtract(const Matrix44& matrix)
//		{
//			mat -= matrix.mat;
//		}
		float& operator()(size_t i, size_t j)
		{
			assert(i>=0);
			assert(i<=3);
			assert(j>=0);
			assert(j<=3);
			return *((float*)&mat+(i + (j<<2)));
		}
		const float& operator()(size_t i, size_t j) const
		{
			assert(i>=0);
			assert(i<=3);
			assert(j>=0);
			assert(j<=3);
			return *((const float*)&mat+(i + (j<<2)));
		}
		float* data()
		{
			return (float*)&mat;
		}
		const float* data() const
		{
			return (float*)&mat;
		}
		std::string to_string() const
		{
			return std::to_string(mat.s0) + " " + std::to_string(mat.s4) + " " + std::to_string(mat.s8) + " " + std::to_string(mat.sc) + "\n" +
				std::to_string(mat.s1) + " " + std::to_string(mat.s5) + " " + std::to_string(mat.s8) + " " + std::to_string(mat.sd) + "\n" +
				std::to_string(mat.s2) + " " + std::to_string(mat.s6) + " " + std::to_string(mat.sa) + " " + std::to_string(mat.se) + "\n" +
				std::to_string(mat.s3) + " " + std::to_string(mat.s7) + " " + std::to_string(mat.sb) + " " + std::to_string(mat.sf);
		}
	};
	inline Matrix44 operator-(const Matrix44& a)
	{
		return Matrix44(-a.mat);
	}
	
	inline Matrix44 operator+(const Matrix44& a, const Matrix44& b)
	{
		return Matrix44(a.mat + b.mat);
	}
	
	inline Matrix44 operator-(const Matrix44& a, const Matrix44& b)
	{
		return Matrix44(a.mat - b.mat);
	}
	
	inline Matrix44 operator*(const Matrix44& a, const Matrix44& b)
	{
		float4 a0 = a.mat.s0123;
		float4 a1 = a.mat.s4567;
		float4 a2 = a.mat.s89ab;
		float4 a3 = a.mat.scdef;
		
		float4 b0 = b.mat.s0123;
		float4 b1 = b.mat.s4567;
		float4 b2 = b.mat.s89ab;
		float4 b3 = b.mat.scdef;
		
		float44 result;
		result.s0123 = a0 * b0.x + a1 * b0.y + a2 * b0.z + a3 * b0.w;
		result.s4567 = a0 * b1.x + a1 * b1.y + a2 * b1.z + a3 * b1.w;
		result.s89ab = a0 * b2.x + a1 * b2.y + a2 * b2.z + a3 * b2.w;
		result.scdef = a0 * b3.x + a1 * b3.y + a2 * b3.z + a3 * b3.w;
		
		return Matrix44(result);
	}
	
	inline Matrix44& operator+=(Matrix44& a, const Matrix44& b)
	{
		a.mat += b.mat;
		return a;
	}
	
	inline Matrix44& operator-=(Matrix44& a, const Matrix44& b)
	{
		a.mat -= b.mat;
		return a;
	}
	
	inline Matrix44& operator*=(Matrix44& a, const Matrix44& b)
	{
		float4 a0 = a.mat.s0123;
		float4 a1 = a.mat.s4567;
		float4 a2 = a.mat.s89ab;
		float4 a3 = a.mat.scdef;
		
		float4 b0 = b.mat.s0123;
		float4 b1 = b.mat.s4567;
		float4 b2 = b.mat.s89ab;
		float4 b3 = b.mat.scdef;
		
		a.mat.s0123 = a0 * b0.x + a1 * b0.y + a2 * b0.z + a3 * b0.w;
		a.mat.s4567 = a0 * b1.x + a1 * b1.y + a2 * b1.z + a3 * b1.w;
		a.mat.s89ab = a0 * b2.x + a1 * b2.y + a2 * b2.z + a3 * b2.w;
		a.mat.scdef = a0 * b3.x + a1 * b3.y + a2 * b3.z + a3 * b3.w;
		
		return a;
	}
	
	inline Vector3 operator*(const Matrix44& matrix, const Vector3& vector)
	{
		float3 xx = vector.vec.xxx;
		float3 yy = vector.vec.yyy;
		float3 zz = vector.vec.zzz;
		return Vector3({xx * matrix.mat.s012 + yy * matrix.mat.s456 + zz * matrix.mat.s89a + matrix.mat.scde});
	}
	
	inline Vector3 operator*(const Vector3& vector, const Matrix44& matrix)
	{
		// when we premultiply x*A we assume the vector is a row vector
		float3 xx = vector.vec.xxx;
		float3 yy = vector.vec.yyy;
		float3 zz = vector.vec.zzz;
		return Vector3({xx * matrix.mat.s048 + yy * matrix.mat.s159 + zz * matrix.mat.s26a + matrix.mat.s37b});
	}
	
	inline Vector3& operator*=(Vector3& vector, const Matrix44& matrix)
	{
		float3 xx = vector.vec.xxx;
		float3 yy = vector.vec.yyy;
		float3 zz = vector.vec.zzz;
		vector.vec = {xx * matrix.mat.s048 + yy * matrix.mat.s159 + zz * matrix.mat.s26a + matrix.mat.s37b};
		return vector;
	}
	
	inline Matrix44 operator*(const Matrix44& a, float s)
	{
		return Matrix44(a.mat * s);
	}
	
	inline Matrix44 operator/(const Matrix44& a, float s)
	{
		assert(s!=0);
		const float inv = 1.0f / s;
		return Matrix44(a.mat * inv);
	}
	
	inline Matrix44& operator*=(Matrix44& a, float s)
	{
		a.mat *= s;
		return a;
	}
	
	inline Matrix44& operator/=(Matrix44& a, float s)
	{
		assert(s!=0);
		const float inv = 1.0f / s;
		a.mat *= inv;
		return a;
	}
	
	inline Matrix44 operator*(float s, const Matrix44& a)
	{
		return Matrix44(a.mat * s);
	}
	
	inline Matrix44& operator*=(float s, Matrix44& a)
	{
		a.mat *= s;
		return a;
	}
}

#endif
