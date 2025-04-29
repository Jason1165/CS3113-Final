/**
* Author: Jason Lin
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 55
#define LEVEL_HEIGHT 39

constexpr char WALLS_FILEPATH[] = "assets/sprites/atlas_tilesheet.png"; // 16 * 28, 4:7, 1.0f, 1.75f
constexpr char PLAYER_FILEPATH[] = "assets/sprites/knight_m_anim.png";

constexpr char BIG_DEMON_FILEPATH[] = "assets/sprites/big_demon_anim.png"; // 32 x 26, 8:9, 1.0f, 1.125f
constexpr char CHORT_FILEPATH[] = "assets/sprites/chort_anim.png"; // 16 x 23, 2:3, 0.8, 1.2
constexpr char NECROMANCER_FILEPATH[] = "assets/sprites/necromancer_anim.png"; // 16 x 23
constexpr char WEAPON_ANIME_SWORD[] = "assets/sprites/weapon_anime_sword.png"; // 12 x 30, 2:5, 1.0f, 2.5f

constexpr char FONT_FILEPATH[] = "assets/sprites/fontsheet_white.png";
constexpr char HP_POTION_FILEPATH[] = "assets/sprites/PotionL_Red.png";
constexpr char SP_POTION_FILEPATH[] = "assets/sprites/PotionL_Blue.png";
GLuint fontsheet_idB;


unsigned int LEVELB_DATA[] =
{
        1,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,3,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,
        4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        4,13,13,13,13,13,13,13,13,13,11,2,2,2,2,2,2,2,2,2,2,2,2,2,12,13,13,13,13,13,13,13,5,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        4,13,13,13,13,13,13,13,13,13,9,7,7,7,7,7,7,7,7,7,7,7,7,7,10,13,13,13,13,13,13,13,5,0,0,0,6,7,10,13,13,13,13,13,13,13,13,13,13,13,13,13,9,7,8,
        4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,
        4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,10,13,13,13,9,7,8,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,
        6,7,7,7,7,7,7,7,7,7,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,1,2,12,13,13,13,13,13,13,13,13,13,13,13,13,13,11,2,3,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,12,13,13,13,11,3,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,1,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,12,13,13,13,13,13,11,3,0,0,0,6,7,7,7,10,13,13,13,13,13,13,13,13,13,9,7,7,7,8,
        0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,
        0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,
        0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,
        0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,
        0,6,7,10,13,13,13,9,7,8,0,0,0,0,0,1,7,7,7,7,7,7,12,13,13,13,13,13,13,13,13,13,11,2,2,3,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,4,13,13,13,13,13,13,13,13,13,5,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,6,10,13,13,13,13,13,13,13,9,8,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,5,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,6,10,13,13,13,13,13,9,8,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,6,7,7,7,7,7,7,7,7,7,7,10,13,13,13,9,7,7,7,7,8,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,6,10,13,13,13,9,8,0,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,
        0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,5,0,0,0,0,0,0,0,
        0,0,0,4,13,13,13,11,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,12,13,13,13,11,2,2,2,2,2,2,2,2,2,2,2,2,12,13,13,13,11,2,2,2,2,2,2,3,
        0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,
        0,0,0,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8
};


LevelB::~LevelB()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete    m_game_state.weapon;
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.death_sfx);
}

void LevelB::initialise()
{
    fontsheet_idB = Utility::load_texture(FONT_FILEPATH);
    m_game_state.next_scene_id = -1;
    srand(unsigned int(std::time(nullptr)));

    // -- MAP -- //
    GLuint map_texture_id = Utility::load_texture(WALLS_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, map_texture_id, 1.0f, 5, 6);

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
        4.0f,                           // speed
        0,                              // health
        50,                             // attack
        0,                              // angle
        WEAPON                          // Entity Type
    );
    m_game_state.weapon->set_position(glm::vec3(1.0f, -1.0f, 0.0f));
    m_game_state.weapon->set_scale(glm::vec3(0.4f, 1.0f, 1.0f));
    m_game_state.weapon->set_attack_cooldown(0.2f);
    m_game_state.weapon->set_attack_state(HOLD);
    m_game_state.weapon->set_weapon_type(SWORD);


    // ----- ENEMIES ----- //
    m_game_state.enemies = new Entity[LEVELB_ENEMY_COUNT];
    GLuint big_demon_texture_id = Utility::load_texture(BIG_DEMON_FILEPATH);
    float big_demon_width = 1.6f;
    float big_demon_height = 1.8f;
    glm::vec3 big_demon_scale = glm::vec3(big_demon_width, big_demon_height, 1.0f);

    GLuint chort_texture_id = Utility::load_texture(CHORT_FILEPATH);
    float chort_width = 0.8f;
    float chort_height = 1.2f;
    glm::vec3 chort_scale = glm::vec3(chort_width, chort_height, 1.0f);

    GLuint necromancer_texture_id = Utility::load_texture(NECROMANCER_FILEPATH);
    float necromancer_width = 0.8f;
    float necromancer_height = 1.2f;
    glm::vec3 necromancer_scale = glm::vec3(necromancer_width, necromancer_height, 1.0f);

    std::vector<std::vector<int>> enemy_animation = {
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {12, 13, 14, 15},
        {8, 9, 10, 11}
    };

    std::vector<std::vector<int>> enemy_animation2 = {
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {0, 1, 2, 3}
    };


    // POTION ENTITY
    GLuint health_potion_id = Utility::load_texture(HP_POTION_FILEPATH);
    GLuint sp_potion_id = Utility::load_texture(SP_POTION_FILEPATH);
    std::vector<std::vector<int>> potion_animation =
    {
        {0, 1, 2, 3, 4, 5, 6},
    };

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

bool LevelB::update(float delta_time)
{
    bool collide_with_enemy = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELB_ENEMY_COUNT, m_game_state.map);
    m_game_state.weapon->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELB_ENEMY_COUNT, m_game_state.map);

    spawn_enemy(delta_time);

    for (int i = 0; i < LEVELB_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
    }

    if (win_condition())
    {
        m_game_state.next_scene_id = 0;
    }

    if (m_game_state.player->get_hp() <= 0)
    {
        m_game_state.next_scene_id = 0;
    }

    return false;
}

void LevelB::render(ShaderProgram* program)
{
    float alpha_calc = 0.5;
    if (m_game_state.player->get_hp() >= 1150)
    {
        alpha_calc = 0.25f;
    }
    else if (m_game_state.player->get_hp() >= 900)
    {
        alpha_calc = 0.5f;
    }
    else if (m_game_state.player->get_hp() >= 650)
    {
        alpha_calc = 1.0f;
    }
    else if (m_game_state.player->get_hp() >= 400) {
        alpha_calc = 1.5f;
    }
    else if (m_game_state.player->get_hp() >= 150) {
        alpha_calc = 2.0f;
    }
    else
    {
        alpha_calc = 3.0f;
    }
    program->set_alpha(alpha_calc);

    m_game_state.map->render(program);

    for (int i = 0; i < LEVELB_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].render(program);
    }

    m_game_state.weapon->render(program);
    m_game_state.player->render(program);

    std::string phrase = "HP: " + std::to_string(m_game_state.player->get_hp());
    glm::vec3 phrase_pos = m_game_state.player->get_position();
    phrase_pos.x -= 0.6;
    phrase_pos.y += 0.8f;
    Utility::draw_text(program, fontsheet_idB, phrase, 0.2f, 0.01f, phrase_pos);
}


bool LevelB::win_condition()
{
    return false;
}


// i know this is bad code but argh
void LevelB::spawn_enemy(float delta_time)
{
    // enemy spawner
    levelB_time_accumulator += delta_time;
}