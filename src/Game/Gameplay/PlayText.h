#pragma once


class PlayText : public Entity
{
public:
	PlayText() = default;

	void BeginPlay() override;
	void Update() override;

	void SetTextColor(const glm::vec3& color);

	void SetTextMessage(std::string_view message);
};

