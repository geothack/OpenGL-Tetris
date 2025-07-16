#pragma once


class ScoreText : public Entity
{
public:
	ScoreText() = default;
	~ScoreText() override;

	void BeginPlay() override;
	void Update() override;
};

