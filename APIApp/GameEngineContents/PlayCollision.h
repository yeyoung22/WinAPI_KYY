#pragma once

// 설명 : 트리거용 콜리전, 깃발 등 고정된 위치의 충돌체와 관련한 기능
class PlayCollision
{
public:
	// constrcuter destructer
	PlayCollision();
	~PlayCollision();

	// delete Function
	PlayCollision(const PlayCollision& _Other) = delete;
	PlayCollision(PlayCollision&& _Other) noexcept = delete;
	PlayCollision& operator=(const PlayCollision& _Other) = delete;
	PlayCollision& operator=(PlayCollision&& _Other) noexcept = delete;

protected:

private:

};

