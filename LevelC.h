#pragma once
#include "Scene.h"

class LevelC : public Scene
{
public:
    int LEVELC_ENEMY_COUNT = 98;
    float levelC_time_accumulator = 0.0f;

    ~LevelC();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;

    void spawn_enemy(float delta_time);
    bool win_condition();
};