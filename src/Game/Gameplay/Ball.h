#pragma once
class Ball : public Entity
{
public:
	Ball() = default;

	void BeginPlay() override;
	void Update() override;
};

