#include "Utility/PreLibrary.h"
#include "Transform.h"

Transform::Transform(const glm::vec2& position, const glm::vec2& size, const float rotation) : mPosition(position), mSize(size), mRotation(rotation)
{
	CalculateTransform();
}

glm::mat4* Transform::GetWorldLocation()
{
	return &mWorldLocation;
}

glm::vec2* Transform::GetPosition()
{
	return &mPosition;
}

glm::vec2* Transform::GetSize()
{
	return &mSize;
}

float Transform::GetRotation()
{
	return mRotation;
}

void Transform::UpdatePosition(const glm::vec2& position)
{
	mPosition = position;
	CalculateTransform();
}

void Transform::UpdateSize(const glm::vec2& size)
{
	mSize = size;
	CalculateTransform();
}

void Transform::UpdateRotation(const float rotation)
{
	mRotation = rotation;
	CalculateTransform();
}

void Transform::CalculateTransform()
{
	mWorldLocation = glm::mat4(1.0f);
	mWorldLocation = glm::translate(mWorldLocation, glm::vec3(mPosition, 0.0f));

	mWorldLocation = glm::translate(mWorldLocation, glm::vec3(0.5f * mSize.x, 0.5f * mSize.y, 0.0f));
	mWorldLocation = glm::rotate(mWorldLocation, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	mWorldLocation = glm::translate(mWorldLocation, glm::vec3(-0.5f * mSize.x, -0.5f * mSize.y, 0.0f));

	mWorldLocation = glm::scale(mWorldLocation, glm::vec3(mSize, 1.0f));
}
