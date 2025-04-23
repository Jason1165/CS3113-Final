#pragma once
#include "Scene.h"

class LevelA : public Scene
{
public:
    int LEVELA_ENEMY_COUNT = 35;
    float levelA_time_accumulator = 0.0f;

    ~LevelA();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;
};