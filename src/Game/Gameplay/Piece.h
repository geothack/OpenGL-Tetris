#pragma once

#include "Render/Material.h"

class Piece : public Entity
{
public:
	Piece() = default;
	Piece(std::span<int> alignment, Color color);

	void BeginPlay() override;
	void Update() override;
	

private:
	Color mColor;

	std::array<int,4> mAlignment;
};

