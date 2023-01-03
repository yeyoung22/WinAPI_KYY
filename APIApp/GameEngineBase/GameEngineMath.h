#pragma once

//상속내릴 수 없음
class GameEngineMath final
{
public:
	static const float PIE;
	static const float PIE2;						// 변수명은 숫자가 앞에 올 수 없음

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
	static const float4 Forward;					//앞으로 들어감
	static const float4 Back;						//뒤로 나옴

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	
	int ix() {
		//float을 int로 형변환
		return static_cast<int>(x);
	}

	int iy() {
		return static_cast<int>(y);
	}

	int iz() {
		return static_cast<int>(z);
	}

	int iw() {
		return static_cast<int>(w);
	}
};