#pragma once

class Transform
{
public:
	Transform() = default;
	Transform(const glm::vec2& position, const glm::vec2& size, const float rotation = 0.0f);

	glm::mat4* GetWorldLocation();
	glm::vec2* GetPosition();
	glm::vec2* GetSize();
	float GetRotation();

	void UpdatePosition(const glm::vec2& position);
	void UpdateSize(const glm::vec2& size);
	void UpdateRotation(const float rotation);

private:
	void CalculateTransform();

private:
	glm::mat4 mWorldLocation;
	glm::vec2 mPosition;
	glm::vec2 mSize;
	float mRotation;
};