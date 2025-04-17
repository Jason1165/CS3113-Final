#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"

Entity::Entity() {
}

Entity::Entity(GLuint texture_id, std::vector<std::vector<int>> animations, int fps, int animation_frames, int animation_index, int animation_cols, int animation_rows, float width, float height, float speed, int health, int attack, float angle, EntityType entity_type)
    : m_texture_id(texture_id),
    m_animation(animations),
    m_frames_per_second(fps),
    m_animation_frames(animation_frames),
    m_animation_index(animation_index),
    m_animation_cols(animation_cols),
    m_animation_rows(animation_rows),
    m_width(width), m_height(height),
    m_speed(speed), m_health(health), m_attack(attack),
    m_angle(angle),
    m_entity_type(entity_type)
{
    m_offset = glm::vec3(0.0f, -height / 2.0f, 0.0f);
}

Entity::~Entity() 
{
}

void Entity::draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index)
{
    // Step 1: Calculate the UV location of the indexed frame
    float u_coord = (float)(index % m_animation_cols) / (float)m_animation_cols;
    float v_coord = (float)(index / m_animation_cols) / (float)m_animation_rows;

    // Step 2: Calculate its UV size
    float width = 1.0f / (float)m_animation_cols;
    float height = 1.0f / (float)m_animation_rows;

    // Step 3: Just as we have done before, match the texture coordinates to the vertices
    float tex_coords[] =
    {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };

    float vertices[] =
    {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };

    // Step 4: And render
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());

    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

bool const Entity::check_collision(Entity* other) const
{
    float x_distance = fabs(m_position.x - other->m_position.x) - ((m_width + other->m_width) / 2.0f);
    float y_distance = fabs(m_position.y - other->m_position.y) - ((m_height + other->m_height) / 2.0f);

    return x_distance < 0.0f && y_distance < 0.0f;
}

bool const Entity::check_collision_y(Entity* collidable_entities, int collidable_entity_count)
{
    bool collision_result = false;
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity* collidable_entity = &collidable_entities[i];

        if (check_collision(collidable_entity))
        {
            float y_distance = fabs(m_position.y - collidable_entity->m_position.y);
            float y_overlap = fabs(y_distance - (m_height / 2.0f) - (collidable_entity->m_height / 2.0f));
            if (m_velocity.y > 0)
            {
                m_position.y -= y_overlap;
                m_velocity.y = 0;

                // Collision!
                m_collided_top = true;
                collision_result = true;
            }
            else if (m_velocity.y < 0)
            {
                m_position.y += y_overlap;
                m_velocity.y = 0;

                // Collision!
                m_collided_bottom = true;
                collision_result = true;
            }
        }
    }
    return collision_result;
}

bool const Entity::check_collision_x(Entity* collidable_entities, int collidable_entity_count)
{
    bool collision_result = false;
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity* collidable_entity = &collidable_entities[i];

        if (check_collision(collidable_entity))
        {
            float x_distance = fabs(m_position.x - collidable_entity->m_position.x);
            float x_overlap = fabs(x_distance - (m_width / 2.0f) - (collidable_entity->m_width / 2.0f));
            if (m_velocity.x > 0)
            {
                m_position.x -= x_overlap;
                m_velocity.x = 0;

                // Collision!
                m_collided_right = true;
                collision_result = true;

            }
            else if (m_velocity.x < 0)
            {
                m_position.x += x_overlap;
                m_velocity.x = 0;

                // Collision!
                m_collided_left = true;
                collision_result = true;
            }
        }
    }
    return collision_result;
}

void const Entity::check_collision_y(Map* map)
{
    // Probes for tiles above
    glm::vec3 top = glm::vec3(m_position.x, m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_left = glm::vec3(m_position.x - (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_right = glm::vec3(m_position.x + (m_width / 2), m_position.y + (m_height / 2), m_position.z);

    // Probes for tiles below
    glm::vec3 bottom = glm::vec3(m_position.x, m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_left = glm::vec3(m_position.x - (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_right = glm::vec3(m_position.x + (m_width / 2), m_position.y - (m_height / 2), m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    // If the map is solid, check the top three points
    if (map->is_solid(top, &penetration_x, &penetration_y) && m_velocity.y >= 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && m_velocity.y >= 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_right, &penetration_x, &penetration_y) && m_velocity.y >= 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }

    // And the bottom three points
    if (map->is_solid(bottom, &penetration_x, &penetration_y) && m_velocity.y <= 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && m_velocity.y <= 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_right, &penetration_x, &penetration_y) && m_velocity.y <= 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
}

void const Entity::check_collision_x(Map* map)
{
    // Probes for tiles; the x-checking is much simpler
    glm::vec3 left = glm::vec3(m_position.x - (m_width / 2), m_position.y, m_position.z);
    glm::vec3 right = glm::vec3(m_position.x + (m_width / 2), m_position.y, m_position.z);

    float penetration_x = 0;
    float penetration_y = 0;

    if (map->is_solid(left, &penetration_x, &penetration_y) && m_velocity.x <= 0)
    {
        m_position.x += penetration_x;
        m_velocity.x = 0;
        m_collided_left = true;
    }
    if (map->is_solid(right, &penetration_x, &penetration_y) && m_velocity.x >= 0)
    {
        m_position.x -= (penetration_x += 0.001f);
        m_velocity.x = 0;
        m_collided_right = true;
    }
}

bool Entity::update(float delta_time, Entity* player, Entity* collidable_entities, int collidable_entity_count, Map* map)
{
    bool collision_result = false;
    if (!m_is_active) return collision_result;

    m_collided_top = false;
    m_collided_bottom = false;
    m_collided_left = false;
    m_collided_right = false;

    if (m_entity_type == ENEMY) ai_activate(player, delta_time);
    if (m_entity_type == WEAPON) weapon_activate(player, delta_time);

    if (!m_animation_indices.empty())
    {
        m_animation_time += delta_time;
        float seconds_per_frame = (float)1 / m_frames_per_second;

        if (m_animation_time >= seconds_per_frame)
        {
            m_animation_time = 0.0f;
            m_animation_index++;

            if (m_animation_index >= m_animation_frames)
            {
                m_animation_index = 0;
            }
        }
    }

    m_velocity.x = m_movement.x * m_speed;
    m_velocity.y = m_movement.y * m_speed;


    m_position.y += m_velocity.y * delta_time;
    collision_result = collision_result || check_collision_y(collidable_entities, collidable_entity_count);
    check_collision_y(map);

    m_position.x += m_velocity.x * delta_time;
    collision_result = collision_result || check_collision_x(collidable_entities, collidable_entity_count);
    check_collision_x(map);

    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    m_model_matrix = glm::translate(m_model_matrix, m_offset);
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    m_model_matrix = glm::translate(m_model_matrix, -m_offset);
    m_model_matrix = glm::scale(m_model_matrix, m_scale);
    return collision_result;
}

void Entity::render(ShaderProgram* program)
{
    program->set_model_matrix(m_model_matrix);
    if (!m_is_active) return;
    if (!m_animation_indices.empty())
    {
        draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_indices[m_animation_index]);
        return;
    }

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float tex_coords[] = { 0.0,  1.0, 1.0,  1.0, 1.0, 0.0,  0.0,  1.0, 1.0, 0.0,  0.0, 0.0 };

    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());
    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

void Entity::ai_activate(Entity* player, float delta_time)
{

}

void Entity::weapon_activate(Entity* player, float delta_time) 
{
    float angle = 30;
    // TRANSLATING WEAPON TO THE RIGHT POSITION
    glm::vec3 position = player->get_position();
    glm::vec3 offset;
    float offset_x = player->get_width() * 0.12f;
    float offset_y = player->get_height() * 0.04f;
    if (player->get_direction() == RIGHT)
    {
        this->face_right();
        position.x += offset_x;
        if (m_attack_state == HOLDING) m_angle = -angle;
    }
    else 
    {
        this->face_left();
        position.x -= offset_x;
        if (m_attack_state == HOLDING) m_angle = angle;
    }
    position.y += offset_y;
    this->set_position(position);

    // DEALING WITH ACTUALLY ATTACKING
    float left_min = 0 + angle;
    float left_max = 180 - angle;
    float right_min = 0 - angle;
    float right_max = -180 + angle;
    switch (m_attack_state) {
    case HOLDING:
        m_last_attack += delta_time;
        break;
    case SWINGING:
        if (m_last_attack <= m_attack_speed) { m_attack_state = HOLDING; m_last_attack += delta_time; }
        else { m_last_attack = 0.0f; m_attack_state = ATTACKING; }
        break;
    case ATTACKING:
        if (m_angle <= right_min && m_angle >= right_max) 
        {
            m_angle -= 5;
        }
        else if (m_angle >= left_min && m_angle <= left_max) 
        {
            m_angle += 5;
        }
        else 
        {
            m_attack_state = HOLDING;
        }
        break;
    default:
        break;
    }
}


// ----- COLLISION STUFF ----- //

std::vector<glm::vec2> Entity::get_corners()
{
    std::vector<glm::vec2> corners;
    float half_width = m_width / 2.0f;
    float half_height = m_height / 2.0f;

    std::vector<glm::vec2> local_corners = 
    {
        {-half_width,  half_height},        // Top-left
        { half_width,  half_height},        // Top-right
        { half_width, -half_height},        // Bottom-right
        {-half_width, -half_height}         // Bottom-left
    };

    float angle_rad = glm::radians(m_angle);
    float cos_theta = glm::cos(angle_rad);
    float sin_theta = glm::sin(angle_rad);

    for (auto& vertex : local_corners)
    {
        float local_x = vertex.x;
        float local_y = vertex.y;

        float rotated_x = cos_theta * local_x - sin_theta * local_y;
        float rotated_y = sin_theta * local_x + cos_theta * local_y;

        corners.push_back(glm::vec2(m_position.x + rotated_x, m_position.y + rotated_y));
    }

    return corners;
}

std::vector<glm::vec2> Entity::get_edges()
{
    std::vector<glm::vec2> corners = get_corners();
    std::vector<glm::vec2> edges;

    for (size_t i = 0; i < corners.size(); i++) { edges.push_back(corners[(i + 1) % corners.size()] - corners[i]); }

    return edges;
}

std::vector<glm::vec2> Entity::get_normals()
{
    std::vector<glm::vec2> edges = get_edges();
    std::vector<glm::vec2> normals;

    for (auto& edge : edges) { normals.push_back(glm::vec2(-edge.y, edge.x)); }

    // Normalize all the normals
    for (auto& normal : normals) { normal = glm::normalize(normal); }

    return normals;
}

bool Entity::check_collision_SAT(Entity* other)
{
    // get the entity corners to project onto the axes
    std::vector<glm::vec2> self_corners = this->get_corners();
    std::vector<glm::vec2> other_corners = other->get_corners();

    // get the axes
    std::vector<glm::vec2> self_normals = this->get_normals();
    std::vector<glm::vec2> other_normals = other->get_normals();

    // append axes to one list
    std::vector<glm::vec2> axes;
    axes.insert(axes.end(), self_normals.begin(), self_normals.end());
    axes.insert(axes.end(), other_normals.begin(), other_normals.end());

    // for every axis
    for (auto& axis : axes)
    {
        // calculate the min and max projection onto an axis for each object
        float minA = INFINITY, maxA = -INFINITY;
        float minB = INFINITY, maxB = -INFINITY;

        for (auto& vertex : self_corners)
        {
            float proj = glm::dot(vertex, axis);
            minA = std::min(minA, proj);
            maxA = std::max(maxA, proj);
        }

        for (auto& vertex : other_corners)
        {
            float proj = glm::dot(vertex, axis);
            minB = std::min(minB, proj);
            maxB = std::max(maxB, proj);
        }

        // if an axis is found no collision
        if (maxA < minB || maxB < minA) {
            return false;
        }
    }

    // no valid axis so collision
    return true;
}

// helper method to get min/max
// used by valid collision and update
std::pair<float, float> Entity::get_min_max_x()
{
    std::vector<glm::vec2> corners = this->get_corners();
    float mini = INFINITY, maxi = -INFINITY;
    for (auto& vertex : corners) 
    {
        mini = glm::min(mini, vertex.x);
        maxi = glm::max(maxi, vertex.x);
    }
    std::pair<float, float> val = std::make_pair(mini, maxi);
    return val;
}

std::pair<float, float> Entity::get_min_max_y()
{
    std::vector<glm::vec2> corners = this->get_corners();
    float mini = INFINITY, maxi = -INFINITY;
    for (auto& vertex : corners) 
    {
        mini = glm::min(mini, vertex.y);
        maxi = glm::max(maxi, vertex.y);
    }
    std::pair<float, float> val = std::make_pair(mini, maxi);
    return val;
}