#define LOG(argument) std::cout << argument << '\n'
#define FIXED_TIMESTEP 0.0166666f

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include "SDL_mixer.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "stb_image.h"
#include "cmath"
#include <ctime>
#include <vector>

#include "Entity.h"
#include "Scene.h"
#include "Map.h"
#include "Utility.h"

#include "Menu.h"
#include "LevelA.h"
#include "LevelB.h"



// ----- CONSTANTS ----- //

// WINDOW
const float WINDOW_SCALE = 1.5f;
const int WINDOW_WIDTH = 640 * WINDOW_SCALE;
const int WINDOW_HEIGHT = 480 * WINDOW_SCALE;

const float ORTHO_SCALE = 1.5f;

const float BG_RED = 0.0f;
const float BG_BLUE = 0.0f;
const float BG_GREEN = 0.0f;
const float BG_OPACITY = 1.0f;

const int   VIEWPORT_X = 0,
			VIEWPORT_Y = 0,
			VIEWPORT_WIDTH = WINDOW_WIDTH,
			VIEWPORT_HEIGHT = WINDOW_HEIGHT;

const char GAME_WINDOW_NAME[] = "Final Project";

const char  V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
			F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

const float MILLISECONDS_IN_SECOND = 1000.0;

/*
* FILEPATHS
*/

const int NUMBER_OF_TEXTURES = 1;
const GLint LEVEL_OF_DETAIL = 0;
const GLint TEXTURE_BORDER = 0;

enum AppStatus { RUNNING, TERMINATED };
enum ScreenStatus { MENU, PAUSE, REGULAR, GAMEWIN, GAMEOVER};

// ----- VARIABLES ----- //
Scene* g_current_scene;
Menu* g_menu;
LevelA* g_levelA;
LevelB* g_levelB;

Scene* g_levels[3];

SDL_Window* g_display_window;
AppStatus g_app_status = RUNNING;
ScreenStatus g_screen_status = MENU;

ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;


// ----- PROTOTYPES ----- //
void switch_to_scene(Scene* scene);
void initialise();
void process_input();
void update();
void render();
void shutdown();

// ----- GENERAL FUNCTIONS ----- //
void switch_to_scene(Scene* scene)
{
	g_current_scene = scene;
	g_current_scene->initialise(); // DON'T FORGET THIS STEP!
}

void initialise()
{
    // ————— GENERAL ————— //
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow(GAME_WINDOW_NAME,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);

#ifdef _WINDOWS
    glewInit();
#endif

    // ————— VIDEO SETUP ————— //
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);

    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f*ORTHO_SCALE, 5.0f*ORTHO_SCALE, -3.75f*ORTHO_SCALE, 3.75f*ORTHO_SCALE, -1.0f*ORTHO_SCALE, 1.0f*ORTHO_SCALE);
    g_projection_matrix = g_projection_matrix;

    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    g_shader_program.set_alpha(0.5f);

    glUseProgram(g_shader_program.get_program_id());

    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);

    // TEXTURES

    // MAPS
    g_levelA = new LevelA();
    g_levelB = new LevelB();
    g_menu = new Menu();

    g_levels[0] = g_menu;
    g_levels[1] = g_levelA;
    g_levels[2] = g_levelB;

    switch_to_scene(g_levels[0]);

    // EFFECTS

    // MUSIC 
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    // BLENDING 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void process_input()
{
    //g_current_scene->get_state().player->set_movement(glm::vec3(0.0f));

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            g_app_status = TERMINATED;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                if (g_screen_status == MENU)
                {
                    g_screen_status = REGULAR;
                    switch_to_scene(g_levels[1]);
                }
                break;
            case SDLK_q:
                // Quit the game with a keystroke
                g_app_status = TERMINATED;
                break;
            case SDLK_r:
                if (g_current_scene->get_state().weapon->get_attack_state() == HOLD)
                {
                    g_current_scene->get_state().weapon->set_attack_state(REG_START);
                }
                break;
            case SDLK_f:
                if (g_current_scene->get_state().weapon->get_attack_state() == HOLD)
                {
                    g_current_scene->get_state().weapon->set_attack_state(ULT_START);
                }
                break;
            case SDLK_0:
                switch_to_scene(g_levels[0]);
                g_screen_status = MENU;
                break;
            case SDLK_1:
                switch_to_scene(g_levels[1]);
                g_screen_status = REGULAR;
                break;
            case SDLK_2:
                switch_to_scene(g_levels[2]);
                break;
                g_screen_status = REGULAR;
            default:
                break;
            }

        default:
            break;
        }
    }

    const Uint8* key_state = SDL_GetKeyboardState(NULL);
    if (g_screen_status == REGULAR)
    {
        bool pressed = false;
        if (key_state[SDL_SCANCODE_DOWN] || key_state[SDL_SCANCODE_S])
        {
            g_current_scene->get_state().player->move_down();
            pressed = true;
        }
        if (key_state[SDL_SCANCODE_UP] || key_state[SDL_SCANCODE_W])
        {
            g_current_scene->get_state().player->move_up();
            pressed = true;
        }
        if (key_state[SDL_SCANCODE_LEFT] || key_state[SDL_SCANCODE_A])
        {
            g_current_scene->get_state().player->move_left();
            pressed = true;
        }
        if (key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_D])
        {
            g_current_scene->get_state().player->move_right();
            pressed = true;
        }
        if (!pressed) {
            g_current_scene->get_state().player->move_idle();
        }
    }

    // This makes sure that the player can't move faster diagonally
    if (glm::length(g_current_scene->get_state().player->get_movement()) > 1.0f)
    {
        g_current_scene->get_state().player->normalise_movement();
    }
}

void update()
{
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    delta_time += g_accumulator;

    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }


    while (delta_time >= FIXED_TIMESTEP)
    {
        g_current_scene->update(FIXED_TIMESTEP);
        //g_effects->update(FIXED_TIMESTEP);
        delta_time -= FIXED_TIMESTEP;
    }

    g_accumulator = delta_time;

    // changing view matrix
    g_view_matrix = glm::mat4(1.0f);
    g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_current_scene->get_state().player->get_position().x, -g_current_scene->get_state().player->get_position().y, 0));
}


void render()
{
    g_shader_program.set_view_matrix(g_view_matrix);

    glClear(GL_COLOR_BUFFER_BIT);

    // ————— RENDERING THE SCENE (i.e. map, character, enemies...) ————— //
    g_current_scene->render(&g_shader_program);
    //g_effects->render();

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{
    delete g_menu;
    delete g_levelA;
    delete g_levelB;
    SDL_Quit();
}

// ————— GAME LOOP ————— //
int main(int argc, char* argv[])
{
    initialise();

    while (g_app_status == RUNNING)
    {
        process_input();
        update();
        if (g_current_scene->get_state().next_scene_id >= 0)
        {
            int current_hp = g_current_scene->get_state().player->get_hp();
            int next_scene = g_current_scene->get_state().next_scene_id;
            if (next_scene >= 0)
            {
                switch_to_scene(g_levels[next_scene]);
                g_current_scene->get_state().player->set_hp(current_hp);
            }
        }
        render();
    }

    shutdown();
    return 0;
}