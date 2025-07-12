#include "Utility/PreLibrary.h"
#include "Piece.h"
#include "Utility/Verify.h"

Piece::Piece(std::span<int> alignment, Color color) : mColor(color)
{
    if (alignment.size() != mAlignment.size()) 
    {
        Verify::Update("Error alignment size must be 4", 0);
    }
    std::copy(alignment.begin(), alignment.end(), mAlignment.begin());
}

void Piece::BeginPlay()
{
}

void Piece::Update()
{
}
