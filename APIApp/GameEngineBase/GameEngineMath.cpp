#include "GameEngineMath.h"
#include "GameEngineString.h"

const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;


const float4 float4::Left = { -1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Up = { 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::Down = { 0.0f, 1.0f, 0.0f, 1.0f };


const float4 float4::Forward  = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back     = { 0.0f, 0.0f, -1.0f, 1.0f };

const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Null = { 0.0f, 0.0f, 0.0f, 0.0f };


//정수 입력시 각 자리숫자를 반환
std::vector<unsigned int> GameEngineMath::GetDigits(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(_Value);

	int StartIndex = 0;													//양수

	if (0 != StringValue.size() && StringValue[0] == '-')				//음수: '-'부호를 제외한 그 다음 인덱스를 시작으로 봄
	{
		StartIndex = 1;
	}

	ResultValue.reserve(StringValue.size());							//들어오는 인자의 길이만큼 reserve

	for (size_t i = StartIndex; i < StringValue.size(); i++)		
	{
		ResultValue.push_back(StringValue[i] - '0');
	}

	return ResultValue;
}

//들어온 인자의 사이즈(길이)
unsigned int GameEngineMath::GetLenth(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

	std::string StringValue = GameEngineString::ToString(_Value);

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')
	{
		StartIndex = 1;
	}

	return static_cast<unsigned int>(StringValue.size()) - StartIndex;
}