#pragma once


class TitleText : public Entity
{
public:
	TitleText() = default;

	void BeginPlay() override;
	void Update() override;

	void SetTextMessage(std::string_view message);

	void SetTextColor(const glm::vec3& color);

private:
};

