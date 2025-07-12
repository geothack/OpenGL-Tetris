#pragma once


class Block : public Entity
{
public:
	Block() = default;

	void BeginPlay() override;
	void Update() override;

private:
};

