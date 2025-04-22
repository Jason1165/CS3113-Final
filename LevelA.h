#pragma once
#include "Scene.h"

class LevelA : public Scene
{
public:
    int LEVELA_ENEMY_COUNT = 29;

    ~LevelA();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;
};