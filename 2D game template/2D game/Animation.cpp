#include "Animation.h"

Animation MakeAnimation(bool loop, float speed)
{
    return std::make_unique<AnimationData>(loop, speed);
}

Animation MakeAnimation(bool loop, float speed, ipoint position, ipoint size)
{
    Animation output = std::make_unique<AnimationData>(loop, speed);
    output->AddFrame(position, size);

    return output;
}

Animation MakeAnimation(bool loop, float speed, unsigned int amount, ipoint initialpos, ipoint size, unsigned int columns, unsigned int rows)
{
    Animation output = std::make_unique<AnimationData>(loop, speed);
    output->AddFrames(amount, initialpos, size, columns, rows);

    return output;
}
