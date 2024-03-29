#ifndef banana_vector_hpp
#define banana_vector_hpp

#include "mathematics.hpp"
#include <string>

namespace Mathematics
{
// 	struct Vector2
// 	{
// 		float2 vec;
		
// 		Vector2() = default;
// 		Vector2(float2 v)
// 		{
// 			vec = v;
// 		}
// 		Vector2(float x, float y)
// 		{
// 			vec = {x, y};
// 		}
		
// 		Vector2& zero()
// 		{
// 			vec = 0.f;
// 			return *this;
// 		}
// 		Vector2& up()
// 		{
// 			vec = {0.f, 1.f};
// 			return *this;
// 		}
// 		Vector2& right()
// 		{
// 			vec = {1.f, 0.f};
// 			return *this;
// 		}
// 		Vector2& down()
// 		{
// 			vec = {0.f, -1.f};
// 			return *this;
// 		}
// 		Vector2& left()
// 		{
// 			vec = {-1.f, 0.f};
// 			return *this;
// 		}
// 		void negate()
// 		{
// 			vec.xy = -vec.xy;
// 		}
// 		float dot(const Vector2& vector) const
// 		{
// 			float2 ret = vec * vector.vec;
// 			return ret.x + ret.y;
// 		}
// 		float lengthSquared() const
// 		{
// 			float2 ret = vec * vec;
// 			return ret.x + ret.y;
// 		}
// 		float length() const
// 		{
// 			return sqrt(lengthSquared());
// 		}
// 		Vector2& normalize()
// 		{
// 			const float magnitude = length();
// 			if(magnitude > epsilon)
// 			{
// 				const float scale = 1.f / magnitude;
// 				vec *= scale;
// 			}
// 			return *this;
// 		}
// 		Vector2 unit() const
// 		{
// 			Vector2 vector(*this);
// 			vector.normalize();
// 			return vector;
// 		}
// 		bool normalized() const
// 		{
// 			return equal(length(), 1.f);
// 		}
		
// 		bool operator==(const Vector2& other) const
// 		{
// 			if(equal(vec.x, other.vec.x) && equal(vec.y, other.vec.y))
// 			{
// 				return true;
// 			}
// 			return false;
// 		}
// 		bool operator!=(const Vector2& other) const
// 		{
// 			return !(*this == other);
// 		}
// 		float& operator[](size_t i)
// 		{
// 			assert(i >= 0);
// 			assert(i <= 1);
// 			return *((float*)&vec+i);
// 		}
// 		const float& operator[](size_t i) const
// 		{
// 			assert(i >= 0);
// 			assert(i <= 1);
// 			return *((float*)&vec+i);
// 		}
// 		float* data()
// 		{
// 			return (float*)&vec;
// 		}
// 		const float* data() const
// 		{
// 			return (float*)&vec;
// 		}
// 		std::string to_string() const
// 		{
// 			return " x:" + std::to_string(vec.x) + " y:" + std::to_string(vec.y);
// 		}
// //		friend inline Vector2 operator-(const Vector2& a);
// //		friend inline Vector2 operator+(const Vector2& a, const Vector2& b);
// //		friend inline Vector2 operator-(const Vector2& a, const Vector2& b);
// //		friend inline Vector2 operator*(const Vector2& a, const Vector2& b);
// //		friend inline Vector2& operator+=(Vector2& a, const Vector2& b);
// //		friend inline Vector2& operator-=(Vector2& a, const Vector2& b);
// //		friend inline Vector2& operator*=(Vector2& a, const Vector2& b);
// //
// //		friend inline Vector2 operator*(const Vector2& a, float s);
// //		friend inline Vector2 operator/(const Vector2& a, float s);
// //		friend inline Vector2& operator*=(Vector2& a, float s);
// //		friend inline Vector2& operator/=(Vector2& a, float s);
// //		friend inline Vector2 operator*(float s, const Vector2& a);
// //		friend inline Vector2& operator*=(float s, Vector2& a);
// 	};
// 	inline Vector2 operator-(const Vector2& a)
// 	{
// 		return Vector2(-a.vec);
// 	}
// 	inline Vector2 operator+(const Vector2& a, const Vector2& b)
// 	{
// 		return Vector2(a.vec + b.vec);
// 	}
// 	inline Vector2 operator-(const Vector2& a, const Vector2& b)
// 	{
// 		return Vector2(a.vec - b.vec);
// 	}
// 	inline Vector2 operator*(const Vector2& a, const Vector2& b)
// 	{
// 		return Vector2(a.vec * b.vec);
// 	}
// 	inline Vector2& operator+=(Vector2& a, const Vector2& b)
// 	{
// 		a.vec += b.vec;
// 		return a;
// 	}
// 	inline Vector2& operator-=(Vector2& a, const Vector2& b)
// 	{
// 		a.vec -= b.vec;
// 		return a;
// 	}
// 	inline Vector2& operator*=(Vector2& a, const Vector2& b)
// 	{
// 		a.vec *= b.vec;
// 		return a;
// 	}
	
// 	inline Vector2 operator*(const Vector2& a, float s)
// 	{
// 		return Vector2(a.vec * s);
// 	}
// 	inline Vector2 operator/(const Vector2& a, float s)
// 	{
// 		assert(s != 0);
// 		return Vector2(a.vec / s);
// 	}
// 	inline Vector2& operator*=(Vector2& a, float s)
// 	{
// 		a.vec *= s;
// 		return a;
// 	}
// 	inline Vector2& operator/=(Vector2& a, float s)
// 	{
// 		assert(s != 0.f);
// 		a.vec /= s;
// 		return a;
// 	}
// 	inline Vector2 operator*(float s, const Vector2& a)
// 	{
// 		return Vector2(a.vec * s);
// 	}
// 	inline Vector2& operator*=(float s, Vector2& a)
// 	{
// 		a.vec *= s;
// 		return a;
// 	}




	struct Vector3
	{
		float3 vec;
		
		Vector3() = default;
		Vector3(float3 v)
		{
			vec = v;
		}
		Vector3(::Mathematics::vec<float,3> v)
		{
			vec = {v.v[0], v.v[1], v.v[2]};
		}
		Vector3(float x, float y, float z)
		{
			vec = {x, y, z};
		}
		
		Vector3& zero()
		{
			vec = 0.f;
			return *this;
		}
		Vector3& up()
		{
			vec = {0.f, 1.f, 0.f};
			return *this;
		}
		Vector3& right()
		{
			vec = {1.f, 0.f, 0.f};
			return *this;
		}
		Vector3& front()
		{
			vec = {0.f, 0.f, 1.f};
			return *this;
		}
		Vector3& down()
		{
			vec = {0.f, -1.f, 0.f};
			return *this;
		}
		Vector3& left()
		{
			vec = {-1.f, 0.f, 0.f};
			return *this;
		}
		Vector3& back()
		{
			vec = {0.f, 0.f, -1.f};
			return *this;
		}
		void negate()
		{
			vec.xyz = -vec.xyz;
		}
		float dot(const Vector3& vector) const
		{
			float3 ret = vec * vector.vec;
			return ret.x + ret.y + ret.z;
		}
		Vector3 cross(const Vector3& vector) const
		{
			return Vector3(vec.y * vector.vec.z - vec.z * vector.vec.y, vec.z * vector.vec.x - vec.x * vector.vec.z, vec.x * vector.vec.y - vec.y * vector.vec.x);
		}
		float lengthSquared() const
		{
			float3 ret = vec * vec;
			return ret.x + ret.y + ret.z;
		}
		float length() const
		{
			return sqrt(lengthSquared());
		}
		Vector3& normalize()
		{
			const float magnitude = length();
			if(magnitude > epsilon)
			{
				const float scale = 1.f / magnitude;
				vec *= scale;
			}
			return *this;
		}
		Vector3 unit() const
		{
			Vector3 vector(*this);
			vector.normalize();
			return vector;
		}
		bool normalized() const
		{
			return equal(length(), 1.f);
		}
		
		bool operator==(const Vector3& other) const
		{
			if(equal(vec.x, other.vec.x) && equal(vec.y, other.vec.y) && equal(vec.z, other.vec.z))
			{
				return true;
			}
			return false;
		}
		bool operator!=(const Vector3& other) const
		{
			return !(*this == other);
		}
		float& operator[](size_t i)
		{
			assert(i >= 0);
			assert(i <= 2);
			return *((float*)&vec+i);
		}
		const float& operator[](size_t i) const
		{
			assert(i >= 0);
			assert(i <= 2);
			return *((float*)&vec+i);
		}
		float* data()
		{
			return (float*)&vec;
		}
		const float* data() const
		{
			return (float*)&vec;
		}
		std::string to_string() const
		{
			return " x:" + std::to_string(vec.x) + " y:" + std::to_string(vec.y) + " z:" + std::to_string(vec.z);
		}
//		friend inline Vector3 operator-(const Vector3& a);
//		friend inline Vector3 operator+(const Vector3& a, const Vector3& b);
//		friend inline Vector3 operator-(const Vector3& a, const Vector3& b);
//		friend inline Vector3 operator*(const Vector3& a, const Vector3& b);
//		friend inline Vector3& operator+=(Vector3& a, const Vector3& b);
//		friend inline Vector3& operator-=(Vector3& a, const Vector3& b);
//		friend inline Vector3& operator*=(Vector3& a, const Vector3& b);
//
//		friend inline Vector3 operator*(const Vector3& a, float s);
//		friend inline Vector3 operator/(const Vector3& a, float s);
//		friend inline Vector3& operator*=(Vector3& a, float s);
//		friend inline Vector3& operator/=(Vector3& a, float s);
//		friend inline Vector3 operator*(float s, const Vector3& a);
//		friend inline Vector3& operator*=(float s, Vector3& a);
	};
	inline Vector3 operator-(const Vector3& a)
	{
		return Vector3(-a.vec);
	}
	inline Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.vec + b.vec);
	}
	inline Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.vec - b.vec);
	}
	inline Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.vec * b.vec);
	}
	inline Vector3& operator+=(Vector3& a, const Vector3& b)
	{
		a.vec += b.vec;
		return a;
	}
	inline Vector3& operator-=(Vector3& a, const Vector3& b)
	{
		a.vec -= b.vec;
		return a;
	}
	inline Vector3& operator*=(Vector3& a, const Vector3& b)
	{
		a.vec *= b.vec;
		return a;
	}
	
	inline Vector3 operator*(const Vector3& a, float s)
	{
		return Vector3(a.vec * s);
	}
	inline Vector3 operator/(const Vector3& a, float s)
	{
		assert(s != 0);
		return Vector3(a.vec / s);
	}
	inline Vector3& operator*=(Vector3& a, float s)
	{
		a.vec *= s;
		return a;
	}
	inline Vector3& operator/=(Vector3& a, float s)
	{
		assert(s != 0.f);
		a.vec /= s;
		return a;
	}
	inline Vector3 operator*(float s, const Vector3& a)
	{
		return Vector3(a.vec * s);
	}
	inline Vector3& operator*=(float s, Vector3& a)
	{
		a.vec *= s;
		return a;
	}
}

#endif
