#include "Scene.h"

class Win : public Scene
{
public:
    int WIN_ENEMY_COUNT = 0;
    float win_time_accumulator = 0.0f;

    ~Win();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;
};