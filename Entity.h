#ifndef ENTITY_H
#define ENTITY_H

#include "Map.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "SDL_mixer.h"

enum EntityType { PLAYER, ENEMY, WEAPON };
enum AttackState { HOLDING, SWINGING, ATTACKING };
enum AIType {};
enum AIState {};

enum AnimationDirection { LEFT, RIGHT, IDLE_LEFT, IDLE_RIGHT, HIT_LEFT, HIT_RIGHT };

class Entity
{

protected:

	EntityType m_entity_type;
	AIType m_ai_type;
	AIState m_ai_state;
	AnimationDirection m_direction;
	AttackState m_attack_state;

	// ----- ACTIVE ----- //
	bool m_is_active = true;

	// ----- TRANSFORMATIONS ----- //
	glm::vec3 m_movement;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	glm::vec3 m_offset;

	glm::mat4 m_model_matrix;

	float m_angle;

	// ----- TEXTURE ----- //
	GLuint m_texture_id;

	// ----- ANIMATION ----- //
	std::vector<std::vector<int>> m_animation;
	std::vector<int> m_animation_indices = {};

	int m_animation_cols;
	int m_animation_frames;
	int m_animation_index;
	int m_animation_rows;

	float m_animation_time = 0.0f; // default 0 no need for constructor to change it
	int m_frames_per_second = 8; // set to 8 but constructor can change it

	float m_width = 1.0f;
	float m_height = 1.0f;

	// ----- COLLISIONS ----- // 
	bool m_collided_top = false;
	bool m_collided_bottom = false;
	bool m_collided_left = false;
	bool m_collided_right = false;


	// ----- SOUND ----- //
	Mix_Chunk* m_sound_sfx = nullptr;

	// ----- GAME STATS ----- //
	float m_speed;
	int m_health;
	int m_attack;
	float m_attack_speed;
	float m_last_attack = 0.0f;

public:
	Entity();
	Entity(GLuint texture_id, std::vector<std::vector<int>> animations, int fps, int animation_frames, int animation_index, int animation_cols, int animation_rows, float width, float height, float speed, int health, int attack, float angle, EntityType entity_type);
	~Entity();

	// ----- METHODS ----- //
	void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);
	bool const check_collision(Entity* other) const;

	bool const check_collision_y(Entity* collidable_entities, int collidable_entity_count);
	bool const check_collision_x(Entity* collidable_entities, int collidable_entity_count);

	void const check_collision_y(Map* map);
	void const check_collision_x(Map* map);

	bool update(float delta_time, Entity* player, Entity* collidable_entities, int collidable_entity_count, Map* map);
	void render(ShaderProgram* program);

	void ai_activate(Entity* player, float delta_time);
	void weapon_activate(Entity* player, float delta_time);

	void normalise_movement() { m_movement = glm::normalize(m_movement); }

	// ----- SEPARATING AXIS THEOREM ----- //
	std::vector<glm::vec2> get_corners();
	std::vector<glm::vec2> get_edges();
	std::vector<glm::vec2> get_normals();

	std::pair<float, float> get_min_max_x();
	std::pair<float, float> get_min_max_y();
	bool check_collision_SAT(Entity* other);


	// ----- ANIMATION INDEX ----- //
	void face_left() { m_animation_indices = m_animation[LEFT]; m_direction = LEFT; }
	void face_right() { m_animation_indices = m_animation[RIGHT]; m_direction = RIGHT;  }
	void face_idle_left() { m_animation_indices = m_animation[IDLE_LEFT]; m_direction = IDLE_LEFT;  }
	void face_idle_right() { m_animation_indices = m_animation[IDLE_RIGHT]; m_direction = IDLE_RIGHT;  }

	void move_left() { m_movement.x = -1.0f; face_left(); }
	void move_right() { m_movement.x = 1.0f;  face_right(); }

	void move_up() { m_movement.y = 1.0f; this->get_direction() == RIGHT ? face_right() : face_left(); }
	void move_down() { m_movement.y = -1.0f; this->get_direction() == RIGHT ? face_right() : face_left(); }
	void move_idle() { m_movement = glm::vec3(0.0f); this->get_direction() == RIGHT ? face_idle_right() : face_idle_left(); }

	// ----- GETTERS ----- //
	EntityType	const get_entity_type()		const { return m_entity_type; }
	AIType		const get_ai_type()			const { return m_ai_type; }
	AIState		const get_ai_state()		const { return m_ai_state; }
	glm::vec3	const get_position()		const { return m_position; }
	glm::vec3	const get_velocity()		const { return m_velocity; }
	glm::vec3	const get_acceleration()	const { return m_acceleration; }
	glm::vec3	const get_movement()		const { return m_movement; }
	glm::vec3	const get_scale()			const { return m_scale; }
	GLuint		const get_texture_id()		const { return m_texture_id; }
	float		const get_speed()			const { return m_speed; }
	bool		const get_collided_top()	const { return m_collided_top; }
	bool		const get_collided_bottom() const { return m_collided_bottom; }
	bool		const get_collided_right()	const { return m_collided_right; }
	bool		const get_collided_left()	const { return m_collided_left; }
	
	// ----- NEW STUFF
	float		const get_angle()			const { return m_angle;  }
	float		const get_width()			const { return m_width;  }
	float		const get_height()			const { return m_height;  }
	AnimationDirection const get_direction() const 
	{ 
		if (m_direction == LEFT || m_direction == IDLE_LEFT || m_direction == HIT_LEFT) { return LEFT;  }
		return RIGHT;
	}
	float		const get_attack_speed()	const { return m_attack_speed;  }
	AttackState const get_attack_state()	const { return m_attack_state;  }
	glm::vec3	const get_offset()			const { return m_offset;  }

	// ----- ACTIVATION ----- //
	void activate() { m_is_active = true; };
	void deactivate() { m_is_active = false; };
	bool get_active() { return m_is_active; };

	// ----- SETTERS ----- //
	void const set_entity_type(EntityType new_entity_type) { m_entity_type = new_entity_type; }
	void const set_ai_type(AIType new_ai_type) { m_ai_type = new_ai_type; }
	void const set_ai_state(AIState new_state) { m_ai_state = new_state; }
	void const set_position(glm::vec3 new_position) { m_position = new_position; }
	void const set_velocity(glm::vec3 new_velocity) { m_velocity = new_velocity; }
	void const set_acceleration(glm::vec3 new_acceleration) { m_acceleration = new_acceleration; }
	void const set_movement(glm::vec3 new_movement) { m_movement = new_movement; }
	void const set_scale(glm::vec3 new_scale) { m_scale = new_scale; }
	void const set_texture_id(GLuint new_texture_id) { m_texture_id = new_texture_id; }
	void const set_speed(float new_speed) { m_speed = new_speed; }
	void const set_animation_cols(int new_cols) { m_animation_cols = new_cols; }
	void const set_animation_rows(int new_rows) { m_animation_rows = new_rows; }
	void const set_animation_frames(int new_frames) { m_animation_frames = new_frames; }
	void const set_animation_index(int new_index) { m_animation_index = new_index; }
	void const set_animation_time(float new_time) { m_animation_time = new_time; }

	// ----- NEW STUFF
	void const set_width(float new_width) { m_width = new_width; }
	void const set_height(float new_height) { m_height = new_height; }
	void const set_angle(float new_angle) { m_angle = new_angle; }
	void const set_attack_speed(float new_attack_speed) { m_attack_speed = new_attack_speed; }
	void const set_attack_state(AttackState new_attack_state) { m_attack_state = new_attack_state; }
	void const set_offset(glm::vec3 new_offset) { m_offset = new_offset;  }

	void set_sound(const char* filepath)
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		m_sound_sfx = Mix_LoadWAV(filepath);
	}
};

#endif // ENTITY_H