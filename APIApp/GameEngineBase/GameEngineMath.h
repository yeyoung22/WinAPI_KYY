#pragma once

//��ӳ��� �� ����
class GameEngineMath final
{
public:
	static const float PIE;
	static const float PIE2;						// �������� ���ڰ� �տ� �� �� ����

private:
	//���������Լ��� ���� ��üȭ���� ���ϰ� ����
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;					//������ ��
	static const float4 Back;						//�ڷ� ����

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	
	int ix() {
		//float�� int�� ����ȯ
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


	//x, y, z ���� ���� ��ȯ
	float4 half()
	{
		return { x * 0.5f, y * 0.5f , z * 0.5f , w };
	}

	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;

		return Return;
	}

	float4& operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}
};