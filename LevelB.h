#pragma once
#include "Scene.h"

class LevelB : public Scene
{
public:
    int LEVELB_ENEMY_COUNT = 0;
    float levelB_time_accumulator = 0.0f;

    ~LevelB();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;

    void spawn_enemy(float delta_time);
    bool win_condition();
};