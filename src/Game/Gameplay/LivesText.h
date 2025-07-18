#pragma once


class LivesText : public Entity
{
public:
	LivesText() = default;

	void BeginPlay() override;
	void Update() override;

	void SetTextColor(const glm::vec3& color);

private:

};

