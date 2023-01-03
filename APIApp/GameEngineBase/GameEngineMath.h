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
};