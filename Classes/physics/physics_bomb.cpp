#include "physics_bomb.h"
#include "bomb_sprite.h"
#include "game_physics_world.h"

PhysicsBomb::PhysicsBomb(
    float float_bomb_x,
    float float_bomb_y,
    float float_power_linear,
    float float_power_angular,
    float float_bomb_radius,
    BombCallback* ptr_bomb_callback
): m_float_power_linear(float_power_linear)
, m_float_power_angular(float_power_angular)
, m_float_bomb_radius(float_bomb_radius)
, m_ptr_bomb_callback(ptr_bomb_callback)
{
    m_b2vec2_bomb_point.Set(float_bomb_x, float_bomb_y);
}

bool PhysicsBomb::ReportFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();
    if (body->GetType() == b2_dynamicBody)
    {
        GameSprite* ptr_sprite = (GameSprite*)body->GetUserData();
        if (ptr_sprite && !ptr_sprite->IsBomb())
        {
            m_stl_bebomblist.insert(ptr_sprite);
        }        
    }
    return true;
}

BOOL PhysicsBomb::ProcessBomb()
{
	int num_result = FALSE;
	int num_ret_code = FALSE;
    std::set<GameSprite*>::iterator it = m_stl_bebomblist.begin();
    for (NULL; it != m_stl_bebomblist.end(); ++it)
    {       
        GameSprite* ptr_sprite = (*it);
        b2Body* ptr_b2body = ptr_sprite->GetB2Body();
        KGLOG_PROCESS_ERROR(ptr_b2body);
        b2Vec2 bomb_vec = ptr_b2body->GetPosition() - m_b2vec2_bomb_point;
        float float_r2 = bomb_vec.LengthSquared();
        float float_r = sqrt(float_r2);
        float float_linear_impulse = m_float_power_linear / float_r2;
        float float_impulse_x = float_linear_impulse * bomb_vec.x / float_r;
        float float_impulse_y = float_linear_impulse * bomb_vec.y / float_r;
        ptr_b2body->ApplyLinearImpulse(
            b2Vec2(float_impulse_x, float_impulse_y),
            ptr_b2body->GetPosition()
            );
        float float_angular_impulse = m_float_power_angular / float_r2;
        if ((bomb_vec.x > 0.0f && bomb_vec.y > 0.0f) || (bomb_vec.x < 0.0f && bomb_vec.y < 0.0f))
        {
            float_angular_impulse *= -1;
        }
        ptr_b2body->ApplyAngularImpulse(float_angular_impulse);
        if (m_ptr_bomb_callback)
        {
            m_ptr_bomb_callback->BeBombed(ptr_sprite);
        }
    }
    

	num_result = TRUE;
Exit0:
	return num_result;
}