#pragma once
#include <math.h>
#include <cmath>
#include <string>
#include <vector>
#include <Windows.h>

//상속내릴 수 없음
class GameEngineMath final
{
public:
	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);
	static const float PIE;
	static const float PIE2;
	static const float DegToRad;							//Degree->Radian
	static const float RadToDeg;							//Radian->Degree

private:
	//순수가상함수로 만들어서 객체화하지 못하게 막음
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;					
	static const float4 Back;						
	static const float4 Zero;						// w != 0
	static const float4 Null;

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		//r = 1인 원 위의 한 점에서의 벡터는  x = cos, y = sin이 됨(빗변 = 1)
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}


public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	
	int ix() const
	{
		//float을 int로 형변환
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}


	float GetAnagleDeg()
	{
		return GetAnagleRad() * GameEngineMath::RadToDeg;
	}

	void RotaitonZDeg(float _Deg)
	{
		RotaitonZRad(_Deg * GameEngineMath::RadToDeg);
	}

	void RotaitonZRad(float _Rad)									//벡터 회전을 위한 함수
	{
		float4 Copy = *this;
		x = Copy.x * cosf(_Rad) - Copy.y * sinf(_Rad);				//cos 합공식(나중 위치 = 처음 위치 + 각도만큼 이동->각도의 합에 의거한 공식)
		y = Copy.x * sinf(_Rad) + Copy.y * cosf(_Rad);				//sin 합공식
	}

	float4 RotaitonZDegReturn(float _Deg)							//값 반환을 위한 함수(값을 한 번 받지 않으면 먼저 바뀐 값이 나중에 변경될 값에 영향을 줌)
	{
		float4 Copy = *this;
		Copy.RotaitonZDeg(_Deg);
		return Copy;
	}

	float GetAnagleRad()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();										//먼저 정규화를 시켜 r = 1인 원에 놓이는 위치로 변경

		float Result = acosf(AngleCheck.x);							//arccos함수(치역: 각도), cos(정의역: 값)

		if (AngleCheck.y > 0)
		{
			Result = GameEngineMath::PIE2 - Result;
		}
		return Result;
	}

	//회전은 라디안 값으로 계산됨
	void RotaitonZDeg(float _Deg)
	{
		RotaitonZRad(_Deg * GameEngineMath::RadToDeg);
	}
	//벡터의 회전(삼각함수 합공식)
	void RotaitonZRad(float _Rad)
	{
		float4 Copy = *this;
		x = Copy.x * cosf(_Rad) - Copy.y * sinf(_Rad);
		y = Copy.x * sinf(_Rad) + Copy.y * cosf(_Rad);
	}

	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	float4 half() const
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f, w };
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	//벡터의 크기(삼각형의 빗변, 특정 위치에서의 크기)
	float Size() const
	{
		return sqrtf(x * x + y * y);
	}

	//r = 1인 원 둘레 중 한 점의 위치값을 가지도록 조절(크기를 '1'인 vector로 만듦)
	void Normalize()
	{
		float SizeValue = Size();

		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;

	}

	//자기 자신의 벡터를 크기 1로 만들어 반환
	float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	//선형보간법
	static float4 Lerp(const float4& _Start, const float4& _End, float _Ratio)
	{
		return _Start * (1.0f - _Ratio) + (_End * _Ratio);
	}

	static float4 LerpClamp(const float4& _Start, const float4& _End, float _Ratio)
	{
		if (0 >= _Ratio)
		{
			_Ratio = 0.0f;
		}

		if (1.0f <= _Ratio)
		{
			_Ratio = 1.0f;
		}

		return Lerp(_Start, _End, _Ratio);
	}

	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}


	float4 operator +(const float4 _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4 _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator *(const float4 _Value) const
	{
		float4 Return;
		Return.x = x * _Value.x;
		Return.y = y * _Value.y;
		Return.z = z * _Value.z;
		return Return;
	}

	float4 operator /(const float4 _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}

	float4 operator -() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4& operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator *=(const float& _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		return *this;
	}

	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}

	//문자로 출력
	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}
};


class CollisionData
{
public:
	float4 Position;
	float4 Scale; // x만 원의 반지름으로 보겠습니다.

	float Left() const
	{
		return Position.x - Scale.hx();
	}
	float Right() const
	{
		return Position.x + Scale.hx();
	}
	float Top() const
	{
		return Position.y - Scale.hy();
	}
	float Bot() const
	{
		return Position.y + Scale.hy();
	}

	float4 LeftTop() const
	{
		return float4{ Left(), Top() };
	}
	float4 RightTop() const
	{
		return float4{ Right(), Top() };
	}
	float4 LeftBot() const
	{
		return float4{ Left(), Bot() };
	}
	float4 RightBot() const
	{
		return float4{ Right(), Bot() };
	}
};