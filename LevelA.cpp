/**
* Author: Jason Lin
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 5
#define LEVEL_HEIGHT 5

constexpr char WALLS_FILEPATH[] = "assets/sprites/atlas_walls_low-16x16.png"; // 16 * 28 --> 1.0f, 1.75f
constexpr char PLAYER_FILEPATH[] = "assets/sprites/knight_m_anim.png";
constexpr char FLOORS_FILEPATH[] = "assets/sprites/atlas_floor-16x16.png";



unsigned int LEVELA_DATA[] =
{
    3, 4, 4, 4, 5,
    6, 0, 0, 0, 8,
    6, 0, 0, 0, 8,
    6, 0, 0, 0, 8, 
    9, 10, 10, 10, 11
};

unsigned int LEVELA_BG[] =
{
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1
};

LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete    m_game_state.bg_map;
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void LevelA::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint map_texture_id = Utility::load_texture(WALLS_FILEPATH);
    GLuint floor_texture_id = Utility::load_texture(FLOORS_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 3, 5);
    m_game_state.bg_map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_BG, floor_texture_id, 1.0f, 4, 4);

    // -- PLAYER -- //
    std::vector<std::vector<int>> player_walking_animation =
    {
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {12, 13, 14, 15},
        {8, 9, 10, 11},
        {16, 16, 16, 16},
        {17, 17, 17, 17}
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    GLuint player_texture_id = Utility::load_texture(PLAYER_FILEPATH);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        2.0f,                      // speed
        acceleration,              // acceleration
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        4,                        // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        5,                        // animation row amount
        1.0f,                      // width
        1.0f,                      // height
        PLAYER
    );

    m_game_state.player->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.player->set_scale(glm::vec3(1.0f, 1.75f, 1.0f));

    // -- ENEMIES -- //

    m_game_state.enemies = new Entity[LEVELA_ENEMY_COUNT];


    /**
     BGM and SFX
     */
    //Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    //m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    //Mix_PlayMusic(m_game_state.bgm, -1);
    //Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    //m_game_state.jump_sfx = Mix_LoadWAV(JUMP_FILEPATH);
    //m_game_state.death_sfx = Mix_LoadWAV(DEATH_FILEPATH);
}

bool LevelA::update(float delta_time)
{
    bool collide_with_enemy = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELA_ENEMY_COUNT, m_game_state.map);
    collide_with_enemy = collide_with_enemy || m_game_state.player->get_position().y < -20.0f;

    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    }

    return false;
}

void LevelA::render(ShaderProgram* program)
{
    //m_game_state.bg_map->render(program);
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].render(program);
    }
}