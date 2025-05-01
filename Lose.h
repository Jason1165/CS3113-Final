#include "Scene.h"

class Lose : public Scene
{
public:
    int LOSE_ENEMY_COUNT = 0;
    float lose_time_accumulator = 0.0f;

    ~Lose();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;
};