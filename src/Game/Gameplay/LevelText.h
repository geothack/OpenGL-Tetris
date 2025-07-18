#pragma once


class LevelText : public Entity
{
public:
	LevelText() = default;
	~LevelText() override;

	void BeginPlay() override;
	void Update() override;

	void SetTextColor(const glm::vec3& color);
};

