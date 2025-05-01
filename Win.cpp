#include "Win.h"
#include "Utility.h"

#define LEVEL_WIDTH 15
#define LEVEL_HEIGHT 15

constexpr char WALLS_FILEPATH[] = "assets/sprites/atlas_tilesheet.png"; // 16 * 28, 4:7, 1.0f, 1.75f
constexpr char PLAYER_FILEPATH[] = "assets/sprites/knight_m_anim.png";

constexpr char FONT_FILEPATH[] = "assets/sprites/fontsheet_white.png";
GLuint fontsheet_idwin;


unsigned int WIN_DATA[] =
{
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13
};

Win::~Win()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete    m_game_state.weapon;
    Mix_FreeMusic(m_game_state.bgm);
}

void Win::initialise()
{
    fontsheet_idwin = Utility::load_texture(FONT_FILEPATH);
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture(WALLS_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, WIN_DATA, map_texture_id, 1.0f, 5, 6);


    // ----- PLAYER
    GLuint player_texture_id = Utility::load_texture(PLAYER_FILEPATH);
    std::vector<std::vector<int>> player_walking_animation =
    {
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {12, 13, 14, 15},
        {8, 9, 10, 11},
        {16, 16, 16, 16},
        {17, 17, 17, 17}
    };

    m_game_state.player = new Entity(
        player_texture_id,              // texture id
        player_walking_animation,       // animations
        8,                              // frames per second
        4,                              // animation frame amount
        3,                              // current animation index
        4,                              // animation column amount
        5,                              // animation row amount
        0.8f,                           // width
        1.4f,                           // height
        5.0f,                           // speed
        1000,                           // health
        0,                              // attack
        0,                              // angle
        PLAYER                          // EntityType
    );
    m_game_state.player->set_position(glm::vec3(7.0f, -7.0f, 0.0f));
    m_game_state.player->set_scale(glm::vec3(0.8f, 1.4f, 1.0f));

    /**
     BGM and SFX
     */
     //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
     //m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
     //Mix_PlayMusic(m_game_state.bgm, -1);
     //Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

     //m_game_state.jump_sfx = Mix_LoadWAV(JUMP_FILEPATH);
}

bool Win::update(float delta_time)
{
    win_time_accumulator += delta_time;
    if (win_time_accumulator >= 8.0f) win_time_accumulator -= 8.0f;
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, WIN_ENEMY_COUNT, m_game_state.map);
    return false;
}

void Win::render(ShaderProgram* program)
{
    float alpha_calc = 2 - glm::sqrt(abs(win_time_accumulator - 4.0f));
    program->set_alpha(alpha_calc / 2);

    m_game_state.map->render(program);
    m_game_state.player->render(program);
    Utility::draw_text(program, fontsheet_idwin, "YOU WIN!", 0.4f, 0.05f, glm::vec3(-1.5f + 7.0f, 2.0f - 7.0f, 0.0f));
    Utility::draw_text(program, fontsheet_idwin, "Press 0", 0.25f, 0.05f, glm::vec3(-0.8f + 7.0f, -2.0f - 7.0f, 0.0f));
    Utility::draw_text(program, fontsheet_idwin, "for Menu!", 0.25f, 0.05f, glm::vec3(-1.0f + 7.0f, -2.5f - 7.0f, 0.0f));

}