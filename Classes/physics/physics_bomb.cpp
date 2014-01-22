#include "physics_bomb.h"
#include "bomb_sprite.h"
#include "game_physics_world.h"

PhysicsBomb::PhysicsBomb(
    BombSprite* ptr_bomb_sprite,
    BombCallback* ptr_bomb_callback
): m_ptr_bomb_sprite(ptr_bomb_sprite),
m_ptr_bomb_callback(ptr_bomb_callback)
{

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
        if (m_ptr_bomb_callback)
        {
            m_ptr_bomb_callback->BeBombed(m_ptr_bomb_sprite, ptr_sprite);
        }
    }    

	num_result = TRUE;
Exit0:
	return num_result;
}