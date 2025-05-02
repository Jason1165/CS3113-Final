#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 43
#define LEVEL_HEIGHT 43

constexpr char WALLS_FILEPATH[] = "assets/sprites/atlas_tilesheet.png"; // 16 * 28, 4:7, 1.0f, 1.75f
constexpr char PLAYER_FILEPATH[] = "assets/sprites/knight_m_anim.png";

constexpr char BIG_DEMON_FILEPATH[] = "assets/sprites/big_demon_anim.png"; // 32 x 26, 8:9, 1.0f, 1.125f
constexpr char CHORT_FILEPATH[] = "assets/sprites/chort_anim.png"; // 16 x 23, 2:3, 0.8, 1.2
constexpr char NECROMANCER_FILEPATH[] = "assets/sprites/necromancer_anim.png"; // 16 x 23
constexpr char WEAPON_ANIME_SWORD[] = "assets/sprites/weapon_anime_sword.png"; // 12 x 30, 2:5, 1.0f, 2.5f
constexpr char BGM_FILEPATH[] = "assets/audio/Malicious.mp3";

constexpr char FONT_FILEPATH[] = "assets/sprites/fontsheet_white.png";
constexpr char HP_POTION_FILEPATH[] = "assets/sprites/PotionL_Red.png";
constexpr char SP_POTION_FILEPATH[] = "assets/sprites/PotionL_Blue.png";
constexpr char SWORD_SOUND_FILEPATH[] = "assets/audio/591155__ultraaxvii__sword-contact-with-swipe.wav";
constexpr char DEMON_SOUND_FILEPATH[] = "assets/audio/527636__lilmati__demonic-anger.wav";
constexpr char POTION_SOUND_FILEPATH[] = "assets/audio/523651__lilmati__powerup-05.wav";

GLuint fontsheet_idA;


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
}

void LevelA::initialise()
{
    fontsheet_idA = Utility::load_texture(FONT_FILEPATH);
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
        4.0f,                           // speed
        0,                              // health
        50,                             // attack
        0,                              // angle
        WEAPON                          // Entity Type
    );
    m_game_state.weapon->set_position(glm::vec3(1.0f, -1.0f, 0.0f));
    m_game_state.weapon->set_scale(glm::vec3(0.4f, 1.0f, 1.0f));
    m_game_state.weapon->set_attack_cooldown(0.1f);
    m_game_state.weapon->set_attack_state(HOLD);
    m_game_state.weapon->set_weapon_type(SWORD);
    m_game_state.weapon->set_sound(SWORD_SOUND_FILEPATH);


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
        while (abs(rand_movement.x) <= 0.2f || abs(rand_movement.y) <= 0.2f)
        {
            rand_movement = glm::normalize(glm::vec3(float(rand() % 101) - 50, float(rand() % 101) - 50, 0.0f));
        }

        m_game_state.enemies[i].set_position(glm::vec3(20.0f + (1.0f * (i / 5)), -3.0f - (1.0f * (i % 5)), 0.0f));
        m_game_state.enemies[i].set_scale(chort_scale);
        m_game_state.enemies[i].set_attack_cooldown(0.5f);
        m_game_state.enemies[i].set_damage_cooldown(0.10f);
        m_game_state.enemies[i].set_movement(rand_movement);
        m_game_state.enemies[i].set_ai_type(WALKER);
        m_game_state.enemies[i].set_origin(glm::vec3(22.0f, -5.0f, 0.0f));
        m_game_state.enemies[i].set_max_distance(3.0f);
    }


    for (int i = 0; i < 9; i++) 
    {
        m_game_state.enemies[i + 25] = Entity(
            necromancer_texture_id,
            enemy_animation2,
            8,                              // frames per second
            4,                              // animation frame amount
            1,                              // current animation index
            4,                              // animation column amount
            2,                              // animation row amount
            necromancer_width,              // width
            necromancer_height,             // height
            3.0f,                           // speed
            200,                            // health
            5,                              // attack
            0,                              // angle
            ENEMY                           // EntityType
        );

        m_game_state.enemies[i + 25].set_position(glm::vec3(19.0f + (1.0f * (i / 3)), -21.0f - (1.0f * (i % 3)), 0.0f));
        m_game_state.enemies[i + 25].set_scale(necromancer_scale);
        m_game_state.enemies[i + 25].set_attack_cooldown(0.25f);
        m_game_state.enemies[i + 25].set_damage_cooldown(0.10f);
        m_game_state.enemies[i + 25].set_ai_type(GUARD);
        m_game_state.enemies[i + 25].set_ai_state(IDLE);
        m_game_state.enemies[i + 25].set_max_distance(8.0f);

    }

    for (int i = 0; i < 1; i++) 
    {
        m_game_state.enemies[i + 34] = Entity(
            big_demon_texture_id,
            enemy_animation,
            8,
            4,
            1,
            4,
            4,
            big_demon_width*1.2f,
            big_demon_height*1.2f,
            6.0f,
            2000,
            10,
            0,
            ENEMY
        );
        m_game_state.enemies[i + 34].set_position(glm::vec3(35.0f, -35.0f, 0.0f));
        m_game_state.enemies[i + 34].set_scale(big_demon_scale*1.2f);
        m_game_state.enemies[i + 34].set_attack_cooldown(0.1f);
        m_game_state.enemies[i + 34].set_damage_cooldown(0.25f);
        m_game_state.enemies[i + 34].set_ai_type(CHARGE);
        m_game_state.enemies[i + 34].set_ai_state(IDLE);
        m_game_state.enemies[i + 34].set_origin(glm::vec3(35.0f, -35.0f, 0.0f));
        m_game_state.enemies[i + 34].set_max_distance(5.0f);
        m_game_state.enemies[i + 34].set_sound(DEMON_SOUND_FILEPATH);
    }


    for (int i = 35; i <= 70; i++)
    {
        m_game_state.enemies[i].deactivate();
    }


    // ----- POTION ----- //
    GLuint health_potion_id = Utility::load_texture(HP_POTION_FILEPATH);
    GLuint sp_potion_id = Utility::load_texture(SP_POTION_FILEPATH);
    std::vector<std::vector<int>> potion_animation =
    {
        {0, 1, 2, 3, 4, 5, 6},
    };

    m_game_state.enemies[71] = Entity(
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
        300,                            // health
        0,                              // attack
        0,                              // angle
        POTION                          // EntityType
    );
    m_game_state.enemies[71].set_position(glm::vec3(37.0f, -5.0f, 0.0f));
    m_game_state.enemies[71].set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.enemies[71].set_sound(POTION_SOUND_FILEPATH);
    m_game_state.enemies[71].deactivate();

    m_game_state.enemies[72] = Entity(
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
        200,                            // health
        0,                              // attack
        0,                              // angle
        POTION                          // EntityType
    );
    m_game_state.enemies[72].set_position(glm::vec3(6.0f, -37.0f, 0.0f));
    m_game_state.enemies[72].set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.enemies[72].set_sound(POTION_SOUND_FILEPATH);

    m_game_state.enemies[73] = Entity(
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
        1,                              // health
        0,                              // attack
        0,                              // angle
        POTION                          // EntityType
    );
    m_game_state.enemies[73].set_position(glm::vec3(37.0f, -20.0f, 0.0f));
    m_game_state.enemies[73].set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.enemies[73].set_sound(POTION_SOUND_FILEPATH);
    m_game_state.enemies[73].deactivate();

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

bool LevelA::update(float delta_time)
{
    bool collide_with_enemy = m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELA_ENEMY_COUNT, m_game_state.map);
    m_game_state.weapon->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELA_ENEMY_COUNT, m_game_state.map);

    spawn_enemy(delta_time);

    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
        if (m_game_state.enemies[i].get_ai_type() == SHOOTER) {
            m_game_state.enemies[i].shooter_update(delta_time, m_game_state.player, m_game_state.enemies, i);
        }
    }

    if (win_condition())
    {
        m_game_state.next_scene_id = 2;
    }
    if (m_game_state.player->get_hp() <= 0)
    {
        m_game_state.next_scene_id = 5;
    }

    return false;
}

void LevelA::render(ShaderProgram* program)
{
    float alpha_calc = 0.5; // default
    if (m_game_state.player->get_hp() >= 1150) { alpha_calc = 0.25f; }
    else if (m_game_state.player->get_hp() >= 900) { alpha_calc = 0.5f;}
    else if (m_game_state.player->get_hp() >= 650) { alpha_calc = 1.0f;}
    else if (m_game_state.player->get_hp() >= 400) { alpha_calc = 1.5f;}
    else if (m_game_state.player->get_hp() >= 150) { alpha_calc = 2.0f;}
    else { alpha_calc = 3.0f;}
    program->set_alpha(alpha_calc);

    m_game_state.map->render(program);

    for (int i = 0; i < LEVELA_ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i].render(program);
    }

    m_game_state.weapon->render(program);
    m_game_state.player->render(program);

    std::string phrase = "HP: " + std::to_string(m_game_state.player->get_hp());
    glm::vec3 phrase_pos = m_game_state.player->get_position();
    phrase_pos.x -= 0.6f;
    phrase_pos.y += 0.8f;
    Utility::draw_text(program, fontsheet_idA, phrase, 0.2f, 0.01f, phrase_pos);
}


bool LevelA::win_condition()
{
    return !m_game_state.enemies[34].is_active();
}


// i know this is bad code but argh
void LevelA::spawn_enemy(float delta_time)
{
    // potion spawner, and once again ik this is bad code
    if (m_game_state.enemies[71].get_hp() > 0)
    {
        bool activate = true;
        for (int i = 0; i < 25; i++)
        {
            if (m_game_state.enemies[i].is_active()) {
                activate = false;
                break;
            }
        }
        if (activate) { m_game_state.enemies[71].activate(); }
    }
    else
    {
        m_game_state.enemies[71].deactivate();
    }

    if (m_game_state.enemies[73].get_hp() > 0)
    {
        bool activate = true;
        for (int i = 25; i < 34; i++)
        {
            if (m_game_state.enemies[i].is_active()) {
                activate = false;
                break;
            }
        }
        if (activate) { m_game_state.enemies[73].activate(); }
    }
    else
    {
        m_game_state.enemies[73].deactivate();
    }

    // enemy spawner
    levelA_time_accumulator += delta_time;
    if (levelA_time_accumulator >= 1.0f) 
    {
        for (int i = 35; i <= 70; i++)
        {
            if (!m_game_state.enemies[i].is_active()) 
            {
                GLuint necromancer_texture_id = Utility::load_texture(NECROMANCER_FILEPATH);
                float necromancer_width = 0.8f;
                float necromancer_height = 1.2f;
                glm::vec3 necromancer_scale = glm::vec3(necromancer_width, necromancer_height, 1.0f);

                std::vector<std::vector<int>> enemy_animation2 = {
                    {4, 5, 6, 7},
                    {0, 1, 2, 3},
                    {4, 5, 6, 7},
                    {0, 1, 2, 3}
                };

                levelA_time_accumulator = 0.0f;

                // speedy rascals
                m_game_state.enemies[i] = Entity(
                    necromancer_texture_id,
                    enemy_animation2,
                    8,                              // frames per second
                    4,                              // animation frame amount
                    1,                              // current animation index
                    4,                              // animation column amount
                    2,                              // animation row amount
                    necromancer_width,              // width
                    necromancer_height,             // height
                    4.0f,                           // speed
                    1,                              // health
                    1,                              // attack
                    0,                              // angle
                    ENEMY                           // EntityType
                );

                int offset = (i - 35);
                float offset_y = (offset / 6) * 2.0f;
                float offset_x = (offset % 6) * 2.0f;

                m_game_state.enemies[i].activate();
                m_game_state.enemies[i].set_position(glm::vec3(30.0f + offset_x, -30.0f - offset_y, 0.0f));
                m_game_state.enemies[i].set_scale(necromancer_scale);
                m_game_state.enemies[i].set_attack_cooldown(0.25f);
                m_game_state.enemies[i].set_damage_cooldown(0.00f);
                m_game_state.enemies[i].set_ai_type(GUARD);
                m_game_state.enemies[i].set_ai_state(IDLE);
                m_game_state.enemies[i].set_max_distance(8.0f);

                break;
            }
        }
    }
}