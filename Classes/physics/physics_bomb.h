
#ifndef __PHYSICS_BOMB_H__
#define __PHYSICS_BOMB_H__

#include "Box2D/Box2D.h"
#include "base.h"
#include <set>

class BombCallback;
class GameSprite;
class BombSprite;

class PhysicsBomb : public b2QueryCallback
{
public:
    PhysicsBomb(
        BombSprite* ptr_bomb_sprite,
        BombCallback* ptr_bomb_callback = NULL
    );
    bool ReportFixture(b2Fixture* fixture);
    BOOL ProcessBomb();
private:
     BombSprite* m_ptr_bomb_sprite;
     BombCallback* m_ptr_bomb_callback;
     std::set<GameSprite*> m_stl_bebomblist;
};
#endif