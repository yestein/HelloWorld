
#ifndef __PHYSICS_BOMB_H__
#define __PHYSICS_BOMB_H__

#include "Box2D/Box2D.h"

class BombCallback;

class PhysicsBomb : public b2QueryCallback
{
public:
    PhysicsBomb(
        float float_bomb_x,
        float float_bomb_y,
        float float_power_linear,
        float float_power_angular,
        float float_bomb_radius,
        BombCallback* ptr_bomb_callback = NULL
    );
    bool ReportFixture(b2Fixture* fixture);
private:
     b2Vec2 m_b2vec2_bomb_point;
     float m_float_power_linear;
     float m_float_power_angular;
     float m_float_bomb_radius;
     BombCallback* m_ptr_bomb_callback;
};
#endif