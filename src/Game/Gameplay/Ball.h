#pragma once


class Ball : public Entity
{
public:
	Ball() = default;

	Ball(Entity& player);

	void BeginPlay() override;
	void Update() override;

	bool HasShot = false;

private:
	void SwitchDirection(const int xDir, const int yDir);

private:
	Entity* mPlayer;

};

