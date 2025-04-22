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
constexpr char CHORT_FILEPATH[] = "assets/sprites/chort_anim.png"; // 16 x 23, 2:3, 0.8, 1.2
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
    srand(unsigned int(std::time(nullptr)));

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
        5.0f,                           // speed
        1000,                           // health
        0,                              // attack
        0,                              // angle
        PLAYER                          // EntityType
    );
    m_game_state.player->set_position(glm::vec3(1.0f, -1.0f, 0.0f));
    m_game_state.player->set_scale(glm::vec3(0.8f, 1.4f, 1.0f));
    m_game_state.player->set_damage_cooldown(0.5f);


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
        0.4f,                           // width
        1.0f,                           // height
        3.0f,                           // speed
        0,                              // health
        25,                             // attack
        0,                              // angle
        WEAPON                          // Entity Type
    );
    m_game_state.weapon->set_position(glm::vec3(1.0f, -1.0f, 0.0f));
    m_game_state.weapon->set_scale(glm::vec3(0.4f, 1.0f, 1.0f));
    m_game_state.weapon->set_attack_cooldown(0.05f);
    m_game_state.weapon->set_attack_state(HOLDING);


    // ----- ENEMIES ----- //
    m_game_state.enemies = new Entity[LEVELA_ENEMY_COUNT];
    GLuint big_demon_texture_id = Utility::load_texture(BIG_DEMON_FILEPATH);
    float big_demon_width = 1.6f;
    float big_demon_height = 1.8f;
    glm::vec3 big_demon_scale = glm::vec3(big_demon_width, big_demon_height, 1.0f);

    GLuint chort_texture_id = Utility::load_texture(CHORT_FILEPATH);
    float chort_width = 0.8f;
    float chort_height = 1.2f;
    glm::vec3 chort_scale = glm::vec3(chort_width, chort_height, 1.0f);

    std::vector<std::vector<int>> enemy_animation = {
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {12, 13, 14, 15},
        {8, 9, 10, 11},
    };

    for (int i = 0; i < 25; i++) 
    {
        m_game_state.enemies[i] = Entity(
            chort_texture_id,
            enemy_animation,
            8,                              // frames per second
            4,                              // animation frame amount
            2,                              // current animation index
            4,                              // animation column amount
            4,                              // animation row amount
            chort_width,                    // width
            chort_height,                   // height
            3.0f,                           // speed
            200,                            // health
            5,                              // attack
            0,                              // angle
            ENEMY                           // EntityType
        );

        glm::vec3 rand_movement = glm::normalize(glm::vec3(float(rand() % 101) - 50, float(rand() % 101) - 50, 0.0f));

        m_game_state.enemies[i].set_position(glm::vec3(20.0f + (1.0f * (i / 5)), -3.0f - (1.0f * (i % 5)), 0.0f));
        m_game_state.enemies[i].set_scale(chort_scale);
        m_game_state.enemies[i].set_attack_cooldown(1.0f);
        m_game_state.enemies[i].set_damage_cooldown(0.20f);
        m_game_state.enemies[i].set_movement(rand_movement);
        m_game_state.enemies[i].set_ai_type(WALKER);
        m_game_state.enemies[i].set_origin(glm::vec3(22.0f, -5.0f, 0.0f));
        m_game_state.enemies[i].set_max_distance(3.0f);
    }


    for (int i = 25; i < 29; i++) 
    {
        m_game_state.enemies[i] = Entity(
            big_demon_texture_id,
            enemy_animation,
            8,                              // frames per second
            4,                              // animation frame amount
            1,                              // current animation index
            4,                              // animation column amount
            4,                              // animation row amount
            1.6f,                           // width
            1.8f,                           // height
            4.0f,                           // speed
            200,                            // health
            5,                              // attack
            0,                              // angle
            ENEMY                           // EntityType
        );

        m_game_state.enemies[i].set_position(glm::vec3(20.0f + (1.0f * (i-25)), -18.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(1.6f, 1.8f, 1.0f));
        m_game_state.enemies[i].set_attack_cooldown(0.25f);
        m_game_state.enemies[i].set_damage_cooldown(0.20f);
        m_game_state.enemies[i].set_ai_type(GUARD);
        m_game_state.enemies[i].set_ai_state(IDLE);
    }


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