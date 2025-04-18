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

#define LEVEL_WIDTH 43
#define LEVEL_HEIGHT 43

constexpr char WALLS_FILEPATH[] = "assets/sprites/atlas_tilesheet.png"; // 16 * 28, 4:7, 1.0f, 1.75f
constexpr char PLAYER_FILEPATH[] = "assets/sprites/knight_m_anim.png";

constexpr char BIG_DEMON_FILEPATH[] = "assets/sprites/big_demon_anim.png"; // 32 x 26, 8:9, 1.0f, 1.125f
constexpr char WEAPON_ANIME_SWORD[] = "assets/sprites/weapon_anime_sword.png"; // 12 x 30, 2:5, 1.0f, 2.5f



unsigned int LEVELA_DATA[] =
{
    1,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,1,2,2,2,2,2,3,0,0,
    4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,
    4,13,13,13,13,13,13,13,13,13,11,2,2,2,2,2,2,2,12,13,13,13,13,13,13,13,11,2,2,2,2,2,2,2,12,13,13,13,13,13,5,0,0,
    4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,
    4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,
    4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,
    4,13,13,13,13,13,13,13,13,13,9,7,7,7,7,7,7,7,10,13,13,13,13,13,13,13,9,7,7,7,7,7,7,7,10,13,13,13,13,13,5,0,0,
    4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,
    4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,6,7,10,13,13,13,9,7,8,0,0,0,0,0,0,0,6,10,13,13,13,9,8,0,0,
    6,7,7,7,7,7,7,7,7,7,8,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,12,13,13,13,11,2,2,3,0,0,0,0,0,1,2,12,13,13,13,11,2,3,0,
    0,1,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,
    0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,
    0,4,13,13,13,13,13,13,13,13,13,11,2,2,2,2,2,12,13,13,13,13,13,13,13,13,13,11,2,2,2,2,2,12,13,13,13,13,13,13,13,5,0,
    0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,
    0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,
    0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,
    0,4,13,13,13,13,13,13,13,13,13,9,7,7,7,7,7,10,13,13,13,13,13,13,13,13,13,9,7,7,7,7,7,10,13,13,13,13,13,13,13,5,0,
    0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,6,7,7,7,7,7,7,7,8,0,
    0,6,7,7,10,13,13,13,9,7,7,8,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,6,7,7,7,7,7,7,7,7,7,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,3,
    0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,1,2,12,13,13,13,11,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,12,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,11,2,2,2,2,2,2,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,7,7,7,7,7,7,10,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,9,7,7,7,7,7,7,7,7,7,7,8,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
    0,0,6,7,7,7,7,7,7,7,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,7,7,7,7,7,7,7,7,7,7,7,7,8
};


LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete    m_game_state.weapon;
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void LevelA::initialise()
{
    m_game_state.next_scene_id = -1;

    // -- MAP -- //
    GLuint map_texture_id = Utility::load_texture(WALLS_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 5, 6);

    // -- PLAYER -- //
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
        4.0f,                           // speed
        500,                            // health
        0,                             // attack
        0,                              // angle
        PLAYER                          // EntityType
    );
    m_game_state.player->set_position(glm::vec3(1.0f, -1.0f, 0.0f));
    m_game_state.player->set_scale(glm::vec3(0.8f, 1.4f, 1.0f));


    // -- WEAPON -- //
    GLuint weapon_texture_id = Utility::load_texture(WEAPON_ANIME_SWORD);
    std::vector<std::vector<int>> weapon_animation =
    {
        {1},{0}
    };

    m_game_state.weapon = new Entity(
        weapon_texture_id,              // texture id
        weapon_animation,               // animations
        1,                              // frames per second
        1,                              // animation frame amount
        0,                              // current animation index
        2,                              // animation column amount
        1,                              // animation row amount
        0.4f,
        1.0f,
        0.0f,
        10,
        10,
        0,
        WEAPON
    );
    m_game_state.weapon->set_position(glm::vec3(1.0f, -1.0f, 0.0f));
    m_game_state.weapon->set_scale(glm::vec3(0.4f, 1.0f, 1.0f));
    m_game_state.weapon->set_cooldown(0.2f);
    m_game_state.weapon->set_attack_state(HOLDING);

    // -- ENEMIES -- //
    m_game_state.enemies = new Entity[LEVELA_ENEMY_COUNT];

    GLuint big_demon_texture_id = Utility::load_texture(BIG_DEMON_FILEPATH);
    std::vector<std::vector<int>> big_demon_animation = {
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {12, 13, 14, 15},
        {8, 9, 10, 11},
    };

    m_game_state.enemies[0] = Entity(
        big_demon_texture_id,
        big_demon_animation,
        8,                              // frames per second
        4,                              // animation frame amount
        1,                              // current animation index
        4,                              // animation column amount
        4,                              // animation row amount
        0.8f,                           // width
        0.9f,                           // height
        4.0f,                           // speed
        50,                             // health
        10,                             // attack
        0,                              // angle
        ENEMY                           // EntityType
    );

    m_game_state.enemies[0].set_position(glm::vec3(22.0f, -5.0f, 0.0f));
    m_game_state.enemies[0].set_scale(glm::vec3(0.8f, 0.9f, 1.0f));
    //m_game_state.enemies[0].deactivate();


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
    m_game_state.weapon->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELA_ENEMY_COUNT, m_game_state.map);
    //std::cout << m_game_state.weapon->get_position().x << " " << m_game_state.weapon->get_position().y << std::endl;

    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    }

    return false;
}

void LevelA::render(ShaderProgram* program)
{
    m_game_state.map->render(program);

    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].render(program);
    }

    m_game_state.weapon->render(program);
    m_game_state.player->render(program);

}