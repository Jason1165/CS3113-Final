/**
* Author: Jason Lin
* Assignment: Dungeon Dungeon
* Date due: May 2, 2025, 2:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/


#include "LevelC.h"
#include "Utility.h"

#define LEVEL_WIDTH 60
#define LEVEL_HEIGHT 45

constexpr char WALLS_FILEPATH[] = "assets/sprites/atlas_tilesheet.png"; // 16 * 28, 4:7, 1.0f, 1.75f
constexpr char PLAYER_FILEPATH[] = "assets/sprites/knight_m_anim.png";
constexpr char WEAPON_ANIME_SWORD[] = "assets/sprites/weapon_anime_sword.png"; // 12 x 30, 2:5, 1.0f, 2.5f

constexpr char SKELETON_FILEPATH[] = "assets/sprites/skelet_anim.png"; // 16 x 16
constexpr char BONE_FILEPATH[] = "assets/sprites/bone.png"; // 12 x 24
constexpr char PUMPKIN_DUDE_FILEPATH[] = "assets/sprites/pumpkin_dude_anim.png"; // 16 x 23
constexpr char PUMPKIN_HEAD_FILEPATH[] = "assets/sprites/pumpkin_head.png"; // 16 x 16
constexpr char BIG_DEMON_FILEPATH[] = "assets/sprites/big_demon_anim.png"; // 32 x 26, 8:9, 1.0f, 1.125f
constexpr char CHORT_FILEPATH[] = "assets/sprites/chort_anim.png"; // 16 x 23, 2:3, 0.8, 1.2
constexpr char NECROMANCER_FILEPATH[] = "assets/sprites/necromancer_anim.png"; // 16 x 23
constexpr char BGM_FILEPATH[] = "assets/audio/Myst on the Moor.mp3";


constexpr char FONT_FILEPATH[] = "assets/sprites/fontsheet_white.png";
constexpr char HP_POTION_FILEPATH[] = "assets/sprites/PotionL_Red.png";
constexpr char SP_POTION_FILEPATH[] = "assets/sprites/PotionL_Blue.png";
constexpr char SWORD_SOUND_FILEPATH[] = "assets/audio/591155__ultraaxvii__sword-contact-with-swipe.wav";
constexpr char DEMON_SOUND_FILEPATH[] = "assets/audio/527636__lilmati__demonic-anger.wav";
constexpr char POTION_SOUND_FILEPATH[] = "assets/audio/523651__lilmati__powerup-05.wav";

GLuint fontsheet_idC;


unsigned int LEVELC_DATA[] =
{
        1,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        4,13,13,13,11,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        4,13,13,13,13,11,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        4,13,13,13,13,13,11,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        6,10,13,13,13,13,13,11,3,1,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,6,10,13,13,13,13,13,11,12,13,13,13,13,11,2,3,0,0,0,0,0,0,0,0,0,0,1,2,12,13,13,13,13,11,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,0,0,0,1,12,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,0,1,12,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,1,12,13,13,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,1,12,13,13,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,11,2,2,2,2,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,11,2,2,2,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,0,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,7,7,7,7,10,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,7,7,7,7,7,7,7,7,7,10,13,13,13,5,0,0,0,0,0,0,
        0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,9,8,0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,9,8,0,0,0,0,0,0,0,0,0,6,10,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,9,8,0,0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,9,8,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,9,8,0,0,0,0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,9,8,0,0,0,0,0,0,0,0,0,0,0,1,12,13,13,11,3,0,0,0,0,0,
        0,0,0,0,0,0,0,6,7,10,13,13,13,13,9,7,8,0,0,0,0,0,0,0,0,0,0,6,7,10,13,13,13,13,9,7,8,0,0,0,0,0,0,0,0,0,0,1,2,12,13,13,13,13,11,2,3,0,0,0,
        0,0,0,0,0,0,0,0,0,6,7,7,7,7,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,10,13,13,9,8,0,0,0,0,0,0,0,0,0,0,0,1,12,13,13,13,13,13,13,13,13,11,3,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,0,0,0,0,1,12,13,13,13,13,13,13,13,13,13,13,11,3,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,5,0,
        0,0,0,0,0,1,2,2,2,2,2,3,1,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,1,12,13,13,11,3,0,0,0,0,0,0,0,0,0,1,12,13,13,13,13,13,13,13,13,13,13,13,13,11,3,
        0,0,0,0,1,12,13,13,13,13,13,5,4,13,13,13,13,13,11,3,0,0,0,0,0,0,0,0,1,12,13,13,13,13,11,3,0,0,0,0,0,0,0,0,4,13,13,13,13,13,9,2,2,10,13,13,13,13,13,5,
        0,0,0,0,4,13,13,13,13,13,13,11,12,13,13,13,13,13,13,5,0,0,0,0,0,0,0,1,12,13,13,13,13,13,13,11,3,0,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,4,13,13,13,13,13,5,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,1,12,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,0,4,13,13,13,13,13,5,0,0,4,13,13,13,13,13,5,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,1,12,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,0,4,13,13,13,13,13,11,7,7,12,13,13,13,13,13,5,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,1,12,13,13,13,13,13,13,13,13,13,13,13,13,11,3,0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,9,8,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,5,0,
        0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,9,8,0,
        0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,9,8,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,9,8,0,0,
        0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,9,8,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,6,7,10,13,13,13,13,9,7,8,0,0,0,
        0,0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,9,8,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,6,10,13,13,9,8,0,0,0,0,0,
        0,0,0,0,0,0,0,6,10,13,13,13,13,13,13,9,8,0,0,0,0,0,0,0,4,13,13,13,13,13,13,9,10,13,13,13,13,13,13,5,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,6,10,13,13,13,13,9,8,0,0,0,0,0,0,0,0,6,10,13,13,13,13,13,5,4,13,13,13,13,13,9,8,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,6,10,13,13,9,8,0,0,0,0,0,0,0,0,0,0,6,10,13,13,9,2,8,6,2,10,13,13,9,8,0,0,0,0,0,0,0,0,0,1,2,12,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,0,0,1,12,13,13,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,1,2,12,13,13,13,13,13,5,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,4,13,13,5,0,0,0,0,0,1,2,12,13,13,13,13,13,13,9,8,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,4,13,13,5,0,0,0,1,2,12,13,13,13,13,13,13,13,9,8,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,4,13,13,11,3,0,0,0,0,0,0,0,0,0,0,0,4,13,13,5,0,0,0,0,4,13,13,5,0,0,1,12,13,13,13,13,13,13,13,9,7,8,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,4,13,13,13,11,2,2,2,2,2,2,2,2,2,2,2,12,13,13,11,7,7,7,7,12,13,13,11,2,2,12,13,13,13,13,13,13,9,7,8,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,4,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,7,8,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,6,10,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,9,7,7,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


LevelC::~LevelC()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete    m_game_state.weapon;
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelC::initialise()
{
    fontsheet_idC = Utility::load_texture(FONT_FILEPATH);
    m_game_state.next_scene_id = -1;
    srand(unsigned int(std::time(nullptr)));

    // -- MAP -- //
    GLuint map_texture_id = Utility::load_texture(WALLS_FILEPATH);
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 5, 6);

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
    m_game_state.weapon->set_sound(SWORD_SOUND_FILEPATH);


    // ----- ENEMIES ----- //
    m_game_state.enemies = new Entity[LEVELC_ENEMY_COUNT];

    GLuint skeleton_texture_id = Utility::load_texture(SKELETON_FILEPATH);
    GLuint bone_texture_id = Utility::load_texture(BONE_FILEPATH);
    GLuint pumpkin_dude_texture_id = Utility::load_texture(PUMPKIN_DUDE_FILEPATH);
    GLuint pumpkin_texture_id = Utility::load_texture(PUMPKIN_HEAD_FILEPATH);
    GLuint big_demon_texture_id = Utility::load_texture(BIG_DEMON_FILEPATH);
    GLuint necromancer_texture_id = Utility::load_texture(NECROMANCER_FILEPATH);
    GLuint chort_texture_id = Utility::load_texture(CHORT_FILEPATH);

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

    for (int i = 0; i < 16; i++)
    {
        m_game_state.enemies[i] = Entity(
            necromancer_texture_id,
            enemy_animation2,
            8,                              // frames per second
            4,                              // animation frame amount
            2,                              // current animation index
            4,                              // animation column amount
            2,                              // animation row amount
            0.8f,                           // width
            1.2f,                           // height
            5.0f,                           // speed
            200,                            // health
            5,                              // attack
            0,                              // angle
            ENEMY                           // EntityType
        );

        m_game_state.enemies[i].set_position(glm::vec3(13.0f + (i%4)*1.0f, -13.0f - (i / 4) * 1.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(0.8f, 1.2f, 1.0f));
        m_game_state.enemies[i].set_attack_cooldown(0.25f);
        m_game_state.enemies[i].set_damage_cooldown(0.00f);
        m_game_state.enemies[i].set_ai_type(GUARD);
        m_game_state.enemies[i].set_ai_state(IDLE);
        m_game_state.enemies[i].set_max_distance(8.0f);
    }

    for (int i = 16; i < 24; i+=2)
    {
        m_game_state.enemies[i] = Entity(
            pumpkin_dude_texture_id,        // texture id
            enemy_animation,                // animations
            16,                             // frames per second
            4,                              // animation frame amount
            0,                              // current animation index
            4,                              // animation column amount
            4,                              // animation row amount
            0.6f,                           // width
            0.9f,                           // height
            6.0f,                           // speed
            500,                            // health
            1,                              // attack
            0,                              // angle
            ENEMY                           // Entity Type
        );

        m_game_state.enemies[i].set_position(glm::vec3(30.0f + ((i - 16) / 2) * 1.0f, -5.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(0.6f, 0.9f, 1.0f));
        m_game_state.enemies[i].set_ai_type(THROWER);
        m_game_state.enemies[i].set_damage_cooldown(0.5f);
        m_game_state.enemies[i].set_projectile(pumpkin_texture_id);
        m_game_state.enemies[i].set_max_distance(6.0f);
        m_game_state.enemies[i + 1] = Entity();
        m_game_state.enemies[i + 1].deactivate();
    }

    for (int i = 24; i < 48; i += 2)
    {
        m_game_state.enemies[i] = Entity(
            pumpkin_dude_texture_id,        // texture id
            enemy_animation,                // animations
            16,                             // frames per second
            4,                              // animation frame amount
            0,                              // current animation index
            4,                              // animation column amount
            4,                              // animation row amount
            0.6f,                           // width
            0.9f,                           // height
            6.0f,                           // speed
            200,                            // health
            1,                              // attack
            0,                              // angle
            ENEMY                           // Entity Type
        );

        m_game_state.enemies[i].set_position(glm::vec3(49.0f + (((i-24)/2) % 6) * 1.0f, -28.0f - (((i-24)/2)/6)  * 1.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(0.6f, 0.9f, 1.0f));
        m_game_state.enemies[i].set_ai_type(THROWER);
        m_game_state.enemies[i].set_damage_cooldown(0.5f);
        m_game_state.enemies[i].set_projectile(pumpkin_texture_id);
        m_game_state.enemies[i].set_max_distance(12.0f);
        m_game_state.enemies[i + 1] = Entity();
        m_game_state.enemies[i + 1].deactivate();
    }

    for (int i = 48; i < 50; i++)
    {
        m_game_state.enemies[i] = Entity(
            big_demon_texture_id,
            enemy_animation,
            8,
            4,
            1,
            4,
            4,
            1.6f * 0.8f,
            1.8f * 0.8f,
            3.5f,
            1000,
            5,
            0,
            ENEMY
        );
        m_game_state.enemies[i].set_position(glm::vec3(29.0f + (i-48) * 5.0f, -29.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(1.6f * 0.8f, 1.8f * 0.8f, 1.0f));
        m_game_state.enemies[i].set_attack_cooldown(0.40f);
        m_game_state.enemies[i].set_damage_cooldown(0.20f);
        m_game_state.enemies[i].set_ai_type(CHARGE);
        m_game_state.enemies[i].set_ai_state(IDLE);
        m_game_state.enemies[i].set_origin(glm::vec3(29.0f + (i-48) * 5.0f, -29.0f, 0.0f));
        m_game_state.enemies[i].set_max_distance(5.0f);
    }

    for (int i = 50; i < 74; i += 2)
    {
        m_game_state.enemies[i] = Entity(
            skeleton_texture_id,            // texture id
            enemy_animation,                // animations
            16,                             // frames per second
            4,                              // animation frame amount
            2 + (i/2)%2,                    // current animation index
            4,                              // animation column amount
            4,                              // animation row amount
            1.0f,                           // width
            1.0f,                           // height
            8.0f,                           // speed
            100,                            // health
            1,                              // attack
            0,                              // angle
            ENEMY                           // Entity Type
        );

        m_game_state.enemies[i].set_position(glm::vec3(6.0f + ((i-50)/2) * 1.0f, -25.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(1.0f));
        m_game_state.enemies[i].set_ai_type(SHOOTER);
        m_game_state.enemies[i].set_projectile(bone_texture_id);
        m_game_state.enemies[i].set_max_distance(10.0f);
        m_game_state.enemies[i + 1] = Entity();
        m_game_state.enemies[i + 1].deactivate();
    }

    for (int i = 74; i < 84; i += 2)
    {
        m_game_state.enemies[i] = Entity(
            pumpkin_dude_texture_id,        // texture id
            enemy_animation,                // animations
            16,                             // frames per second
            4,                              // animation frame amount
            0,                              // current animation index
            4,                              // animation column amount
            4,                              // animation row amount
            0.6f,                           // width
            0.9f,                           // height
            5.0f,                           // speed
            300,                            // health
            1,                              // attack
            0,                              // angle
            ENEMY                           // Entity Type
        );

        m_game_state.enemies[i].set_position(glm::vec3(6.0f + ((i - 74) / 2) * 1.0f, -24.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(0.6f, 0.9f, 1.0f));
        m_game_state.enemies[i].set_ai_type(THROWER);
        m_game_state.enemies[i].set_damage_cooldown(0.5f);
        m_game_state.enemies[i].set_projectile(pumpkin_texture_id);
        m_game_state.enemies[i].set_max_distance(6.0f);
        m_game_state.enemies[i + 1] = Entity();
        m_game_state.enemies[i + 1].deactivate();
    }

    for (int i = 84; i < 94; i += 2)
    {
        m_game_state.enemies[i] = Entity(
            pumpkin_dude_texture_id,        // texture id
            enemy_animation,                // animations
            16,                             // frames per second
            4,                              // animation frame amount
            0,                              // current animation index
            4,                              // animation column amount
            4,                              // animation row amount
            0.6f,                           // width
            0.9f,                           // height
            5.0f,                           // speed
            300,                            // health
            1,                              // attack
            0,                              // angle
            ENEMY                           // Entity Type
        );

        m_game_state.enemies[i].set_position(glm::vec3(13.0f + ((i - 84) / 2) * 1.0f, -24.0f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(0.6f, 0.9f, 1.0f));
        m_game_state.enemies[i].set_ai_type(THROWER);
        m_game_state.enemies[i].set_damage_cooldown(0.5f);
        m_game_state.enemies[i].set_projectile(pumpkin_texture_id);
        m_game_state.enemies[i].set_max_distance(6.0f);
        m_game_state.enemies[i + 1] = Entity();
        m_game_state.enemies[i + 1].deactivate();
    }

    for (int i = 94; i < 95; i++)
    {
        m_game_state.enemies[i] = Entity(
            big_demon_texture_id,
            enemy_animation,
            8,
            4,
            1,
            4,
            4,
            1.6f * 1.2f,
            1.8f * 1.2f,
            2.5f,
            4000,
            1,
            0,
            ENEMY
        );
        m_game_state.enemies[i].set_position(glm::vec3(11.5f, -28.5f, 0.0f));
        m_game_state.enemies[i].set_scale(glm::vec3(1.6f * 1.2f, 1.8f * 1.2f, 1.0f));
        m_game_state.enemies[i].set_attack_cooldown(0.50f);
        m_game_state.enemies[i].set_damage_cooldown(0.05f);
        m_game_state.enemies[i].set_ai_type(CHARGE);
        m_game_state.enemies[i].set_ai_state(IDLE);
        m_game_state.enemies[i].set_origin(glm::vec3(11.5f, -28.5f, 0.0f));
        m_game_state.enemies[i].set_max_distance(4.5f);
        m_game_state.enemies[i].set_sound(DEMON_SOUND_FILEPATH);
    }


    // ----- POTION ----- //
    GLuint health_potion_id = Utility::load_texture(HP_POTION_FILEPATH);
    GLuint sp_potion_id = Utility::load_texture(SP_POTION_FILEPATH);
    std::vector<std::vector<int>> potion_animation =
    {
        {0, 1, 2, 3, 4, 5, 6},
    };

    m_game_state.enemies[95] = Entity(
        health_potion_id,               // texture id
        potion_animation,               // animations
        16,                             // frames per second
        7,                              // animation frame amount
        0,                              // current animation index
        7,                              // animation column amount
        1,                              // animation row amount
        1.0f,                           // width
        1.0f,                           // height
        0.0f,                           // speed
        250,                            // health
        15,                             // attack
        0,                              // angle
        POTION                          // EntityType
    );
    m_game_state.enemies[95].set_position(glm::vec3(12.0f, -42.0f, 0.0f));
    m_game_state.enemies[95].set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.enemies[95].set_sound(POTION_SOUND_FILEPATH);

    m_game_state.enemies[96] = Entity(
        sp_potion_id,                   // texture id
        potion_animation,               // animations
        16,                             // frames per second
        7,                              // animation frame amount
        0,                              // current animation index
        7,                              // animation column amount
        1,                              // animation row amount
        1.0f,                           // width
        1.0f,                           // height
        2.0f,                           // speed
        250,                            // health
        0,                             // attack
        0,                              // angle
        POTION                          // EntityType
    );
    m_game_state.enemies[96].set_position(glm::vec3(43.0f, -41.0f, 0.0f));
    m_game_state.enemies[96].set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.enemies[96].set_sound(POTION_SOUND_FILEPATH);

    m_game_state.enemies[97] = Entity(
        health_potion_id,               // texture id
        potion_animation,               // animations
        16,                             // frames per second
        7,                              // animation frame amount
        0,                              // current animation index
        7,                              // animation column amount
        1,                              // animation row amount
        1.0f,                           // width
        1.0f,                           // height
        0.0f,                           // speed
        250,                            // health
        0,                              // attack
        0,                              // angle
        POTION                          // EntityType
    );
    m_game_state.enemies[97].set_position(glm::vec3(51.0f, -12.0f, 0.0f));
    m_game_state.enemies[97].set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.enemies[97].set_sound(POTION_SOUND_FILEPATH);

    /**
     BGM and SFX
     */
     Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

     m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
     Mix_PlayMusic(m_game_state.bgm, -1);
     Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

}

bool LevelC::update(float delta_time)
{
    bool collide_with_enemy = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELC_ENEMY_COUNT, m_game_state.map);

    m_game_state.weapon->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELC_ENEMY_COUNT, m_game_state.map);

    spawn_enemy(delta_time);

    for (int i = 0; i < LEVELC_ENEMY_COUNT; i++)
    {
        if (m_game_state.enemies[i].get_ai_type() == SHOOTER || m_game_state.enemies[i].get_ai_type() == THROWER) {
            m_game_state.enemies[i].shooter_update(delta_time, m_game_state.player, m_game_state.enemies, i + 1);
        }
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);

    }

    if (win_condition())
    {
        m_game_state.next_scene_id = 4;
    }

    if (m_game_state.player->get_hp() <= 0)
    {
        m_game_state.next_scene_id = 5;
    }

    return false;
}

void LevelC::render(ShaderProgram* program)
{
    float alpha_calc = 0.5; // default
    if (m_game_state.player->get_hp() >= 1150) { alpha_calc = 0.25f; }
    else if (m_game_state.player->get_hp() >= 900) { alpha_calc = 0.5f; }
    else if (m_game_state.player->get_hp() >= 650) { alpha_calc = 1.0f; }
    else if (m_game_state.player->get_hp() >= 400) { alpha_calc = 1.5f; }
    else if (m_game_state.player->get_hp() >= 150) { alpha_calc = 2.0f; }
    else { alpha_calc = 3.0f; }
    program->set_alpha(alpha_calc);

    m_game_state.map->render(program);

    for (int i = 0; i < LEVELC_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].render(program);
    }

    m_game_state.weapon->render(program);
    m_game_state.player->render(program);

    std::string phrase = "HP: " + std::to_string(m_game_state.player->get_hp());
    glm::vec3 phrase_pos = m_game_state.player->get_position();
    phrase_pos.x -= 0.6f;
    phrase_pos.y += 0.8f;
    Utility::draw_text(program, fontsheet_idC, phrase, 0.2f, 0.01f, phrase_pos);
}


bool LevelC::win_condition()
{
    return !m_game_state.enemies[94].is_active();
}


// i know this is bad code but argh
void LevelC::spawn_enemy(float delta_time)
{
    // enemy spawner
    levelC_time_accumulator += delta_time;
}