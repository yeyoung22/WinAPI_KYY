#pragma once

// ���� : Ʈ���ſ� �ݸ���, ��� �� ������ ��ġ�� �浹ü�� ������ ���
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

