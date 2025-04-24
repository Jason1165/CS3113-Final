#include "Scene.h"

class Menu : public Scene
{
public:
    int MENU_ENEMY_COUNT = 0;

    ~Menu();

    void initialise() override;
    bool update(float delta_time) override;
    void render(ShaderProgram* program) override;
};