#include "game_physics_world.h"
#include "gles_render.h"
#include "gb2_shape_cache_x.h"
#include "game_sprite.h"
#include "bomb_sprite.h"
#include "physics_bomb.h"
#include "b2concave.h"

GamePhysicsWorld* GamePhysicsWorld::ms_ptr_instance = NULL;
USING_NS_CC;
using namespace ClipperLib;

BOOL GamePhysicsWorld::Init(float float_gravity_x, float float_gravity_y)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    {
        b2Vec2 b2vec2_gravity;
        b2vec2_gravity.Set(float_gravity_x, float_gravity_y);
        m_ptr_b2world = new b2World(b2vec2_gravity);
        KGLOG_PROCESS_ERROR(m_ptr_b2world);

        m_ptr_b2world->SetContactListener(this);

        b2BodyDef bodyDef;
        m_ptr_b2body_ground = m_ptr_b2world->CreateBody(&bodyDef);
        KGLOG_PROCESS_ERROR(m_ptr_b2body_ground);

        m_ptr_b2joint_mouse = NULL;
        m_ptr_bomb_callback = NULL;
    }

	num_result = TRUE;
Exit0:
    if (!num_result)
    {
        SAFE_DELETE(m_ptr_b2world);
    }
	return num_result;
}

BOOL GamePhysicsWorld::Uninit()
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    SAFE_DELETE(m_ptr_b2world);
Exit0:
    return num_result;
}

void GamePhysicsWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    b2Fixture* b2fixture_a = contact->GetFixtureA();
    b2Fixture* b2fixture_b = contact->GetFixtureB();

    b2Body* b2body_a = NULL;
    b2Body* b2body_b = NULL;
    void* bodyUserDataA = NULL;
    void* bodyUserDataB = NULL;
    GameSprite* sprite_body_a;
    GameSprite* sprite_body_b;

    KGLOG_PROCESS_ERROR(b2fixture_a);
    KGLOG_PROCESS_ERROR(b2fixture_b);

    b2body_a = b2fixture_a->GetBody();
    b2body_b = b2fixture_b->GetBody();
    KGLOG_PROCESS_ERROR(b2body_a);
    KGLOG_PROCESS_ERROR(b2body_b);
    
    bodyUserDataA = b2body_a->GetUserData();
    bodyUserDataB = b2body_b->GetUserData();

    sprite_body_a = static_cast<GameSprite*>(bodyUserDataA);
    sprite_body_b = static_cast<GameSprite*>(bodyUserDataB);

    if (sprite_body_a)
    {
        if (sprite_body_a->IsBomb() && (!sprite_body_b || !sprite_body_b->IsBomb()))
        {
            m_array_collide.insert(sprite_body_a);
        }
    }
    
    if (sprite_body_b)
    {
        if (sprite_body_b->IsBomb() && (!sprite_body_a || !sprite_body_a->IsBomb()))
        {
            m_array_collide.insert(sprite_body_b);
        }
    }
Exit0:
    return;
}

BOOL GamePhysicsWorld::Update(float float_delta)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2Body* b2body_it = m_ptr_b2world->GetBodyList();
    KGLOG_PROCESS_ERROR(b2body_it);

	m_ptr_b2world->Step(float_delta, 10, 10);

    for(; b2body_it; b2body_it = b2body_it->GetNext()) 
    { 
        if (b2body_it->GetUserData() != NULL) {
            GameSprite* ptr_sprite_element = (GameSprite *)b2body_it->GetUserData();
            if(!ptr_sprite_element)
            {
                KGLOG_CHECK_ERROR(ptr_sprite_element);
                continue;
            }

            float float_position_x = b2body_it->GetPosition().x * PTM_RATIO;
            float float_position_y = b2body_it->GetPosition().y * PTM_RATIO;

            Point point_position = Point(float_position_x, float_position_y);
            ptr_sprite_element->setPosition(point_position);
            ptr_sprite_element->setRotation( -1* CC_RADIANS_TO_DEGREES(b2body_it->GetAngle()));
        } 
    }
    num_ret_code = processCollide();
    KGLOG_PROCESS_ERROR(num_ret_code);

	num_result = TRUE;
Exit0:
	return num_result;
}

BOOL GamePhysicsWorld::processCollide()
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    CollideVector* vec_collide = &m_array_collide;
    KGLOG_PROCESS_ERROR(vec_collide);
    if(!vec_collide->empty())
    {
        GamePhysicsWorld::CollideVector::iterator it = vec_collide->begin();
        for(NULL;it != vec_collide->end(); ++it)
        {
            GameSprite* ptr_sprite = static_cast<GameSprite*>(*it);
            KGLOG_PROCESS_ERROR(ptr_sprite);
            if(ptr_sprite->IsBomb())
            {
                BombSprite* ptr_bomb_sprite = (BombSprite*)ptr_sprite;
                float float_bomb_radius = ptr_bomb_sprite->GetBombRadius();
                // 这里利用爆炸半径来做一个爆炸物理效果开关
                if (float_bomb_radius > 0.0f)
                {
                    num_ret_code = Bomb(ptr_bomb_sprite);
                    KGLOG_PROCESS_ERROR(num_ret_code);
                }
                if (m_ptr_bomb_callback)
                {
                    m_ptr_bomb_callback->Bomb(ptr_sprite);
                }
            }                   
        }
        vec_collide->clear();
    }

	num_result = TRUE;
Exit0:
	return num_result;
}

BOOL GamePhysicsWorld::Bomb(BombSprite* bomb_sprite)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;
    float bomb_radius = bomb_sprite->GetBombRadius();
    float bomb_x = bomb_sprite->getPositionX();
    float bomb_y = bomb_sprite->getPositionY();
    b2Vec2 p(bomb_x / PTM_RATIO, bomb_y / PTM_RATIO);
    // Make a small box.
    b2AABB aabb;
    b2Vec2 d;
    d.Set(bomb_radius / PTM_RATIO, bomb_radius / PTM_RATIO);
    aabb.lowerBound = p - d;
    aabb.upperBound = p + d;
    PhysicsBomb bomb(bomb_sprite, m_ptr_bomb_callback);
    m_ptr_b2world->QueryAABB(&bomb, aabb);
    num_ret_code = bomb.ProcessBomb();
    KGLOG_PROCESS_ERROR(num_ret_code);
	num_result = TRUE;
Exit0:
	return num_result;
}

//////////////////////////////////////////////////////////////////////////
//  鼠标点选相关
class MouseQueryCallback : public b2QueryCallback
{
public:
    MouseQueryCallback(const b2Vec2& point)
    {
        m_point = point;
        m_fixture = NULL;
    }

    bool ReportFixture(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_dynamicBody)
        {
            bool inside = fixture->TestPoint(m_point);
            if (inside)
            {
                m_fixture = fixture;

                // We are done, terminate the query.
                return false;
            }
        }

        // Continue the query.
        return true;
    }

    b2Vec2 m_point;
    b2Fixture* m_fixture;
};

BOOL GamePhysicsWorld::MouseDown(float float_x, float float_y)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

{
    KG_PROCESS_ERROR(!m_ptr_b2joint_mouse);
    m_b2vec_mouse_position.Set(float_x / PTM_RATIO, float_y/ PTM_RATIO);
    
    // Make a small box.
    b2AABB b2aabb;
    b2Vec2 b2vec_radius;
    b2vec_radius.Set(0.001f, 0.001f);
    b2aabb.lowerBound = m_b2vec_mouse_position - b2vec_radius;
    b2aabb.upperBound = m_b2vec_mouse_position + b2vec_radius;

    // Query the world for overlapping shapes.
    MouseQueryCallback callback(m_b2vec_mouse_position);
    m_ptr_b2world->QueryAABB(&callback, b2aabb);
    KG_PROCESS_ERROR(callback.m_fixture);

    b2Body* b2body_click_body = callback.m_fixture->GetBody();
    KGLOG_PROCESS_ERROR(b2body_click_body);
    b2MouseJointDef b2joint_mouse;
    b2joint_mouse.bodyA = m_ptr_b2body_ground;
    b2joint_mouse.bodyB = b2body_click_body;
    b2joint_mouse.target = m_b2vec_mouse_position;
    b2joint_mouse.maxForce = 1000.0f * b2body_click_body->GetMass();
    m_ptr_b2joint_mouse = (b2MouseJoint*)m_ptr_b2world->CreateJoint(&b2joint_mouse);
    b2body_click_body->SetAwake(true);
}

	num_result = TRUE;
Exit0:
	return num_result;
}

void GamePhysicsWorld::MouseUp(float float_x, float float_y)
{
    if (m_ptr_b2joint_mouse)
    {
        m_ptr_b2world->DestroyJoint(m_ptr_b2joint_mouse);
        m_ptr_b2joint_mouse = NULL;
    }
}

BOOL GamePhysicsWorld::MouseMove(float float_x, float float_y)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    KG_PROCESS_ERROR(m_ptr_b2joint_mouse);
    m_b2vec_mouse_position.Set(float_x / PTM_RATIO, float_y/ PTM_RATIO);
    m_ptr_b2joint_mouse->SetTarget(m_b2vec_mouse_position);
	num_result = TRUE;
Exit0:
	return num_result;
}

//////////////////////////////////////////////////////////////////////////
// 封装API

BOOL GamePhysicsWorld::CreateRectEdge(
    GameSprite* ptr_sprite,
    float left_edge,
    float right_edge,
    float buttom_edge,
    float top_edge
)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2BodyDef b2bodydef_rect_edge;    
    b2EdgeShape b2edgeshape_rect_edge;
    b2FixtureDef b2fixturedef_rect_edge;
    b2Body* b2body_rect_edge = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite);
    KGLOG_PROCESS_ERROR(!ptr_sprite->GetB2Body());
    
    b2bodydef_rect_edge.position.Set(0,0);        
    b2body_rect_edge = m_ptr_b2world->CreateBody(&b2bodydef_rect_edge);
    KGLOG_PROCESS_ERROR(b2body_rect_edge);

    b2fixturedef_rect_edge.shape = &b2edgeshape_rect_edge;
    // Bottom Edge
    b2edgeshape_rect_edge.Set(
        b2Vec2(left_edge / PTM_RATIO, buttom_edge / PTM_RATIO), 
        b2Vec2(right_edge / PTM_RATIO, buttom_edge / PTM_RATIO)
    );
    b2body_rect_edge->CreateFixture(&b2fixturedef_rect_edge);
    // Left Edge
    b2edgeshape_rect_edge.Set(
        b2Vec2(left_edge / PTM_RATIO, buttom_edge / PTM_RATIO), 
        b2Vec2(left_edge / PTM_RATIO, top_edge / PTM_RATIO)
    );
    b2body_rect_edge->CreateFixture(&b2fixturedef_rect_edge);
    // Top Edge
    b2edgeshape_rect_edge.Set(
        b2Vec2(left_edge / PTM_RATIO, top_edge / PTM_RATIO), 
        b2Vec2(right_edge / PTM_RATIO, top_edge / PTM_RATIO)
    );
    b2body_rect_edge->CreateFixture(&b2fixturedef_rect_edge);
    // Right Edge
    b2edgeshape_rect_edge.Set(
        b2Vec2(right_edge / PTM_RATIO, buttom_edge / PTM_RATIO),
        b2Vec2(right_edge / PTM_RATIO, top_edge / PTM_RATIO)
    );
    b2body_rect_edge->CreateFixture(&b2fixturedef_rect_edge);
    
    num_ret_code = ptr_sprite->SetB2Body(b2body_rect_edge);
    KGLOG_PROCESS_ERROR(num_ret_code);

	num_result = TRUE;
Exit0:
    if (!num_result)
    {
        if (b2body_rect_edge)
        {
            m_ptr_b2world->DestroyBody(b2body_rect_edge);
        }
    }
	return num_result;
}

BOOL GamePhysicsWorld::SetBoxBody(
    GameSprite* ptr_sprite, 
    float width,
    float height,
    MATERIAL* ptr_material,
    float offset_x,
    float offset_y,
    BOOL is_dynamic,
    BOOL is_bullet,
    uint16 index_filter_group,
    uint16 category_bits,
    uint16 mask_bits
)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    b2PolygonShape b2polygonshape_box;
    KGLOG_PROCESS_ERROR(ptr_sprite);
    KGLOG_PROCESS_ERROR(!ptr_sprite->GetB2Body());

    b2polygonshape_box.SetAsBox(width / PTM_RATIO, height / PTM_RATIO);

    num_ret_code = SetShapeBody(ptr_sprite, &b2polygonshape_box, ptr_material, offset_x, offset_y, 
        is_dynamic, is_bullet, index_filter_group, category_bits, mask_bits);
    KGLOG_PROCESS_ERROR(num_ret_code);

    num_result = TRUE;
Exit0:
    if (!num_result)
    {
        //TODO
    }
    return num_result;
}

BOOL GamePhysicsWorld::SetCircleBody(
    GameSprite* ptr_sprite, 
    float float_radius,
    MATERIAL* ptr_material,
    float float_offset_x,
    float float_offset_y,
    BOOL bool_dynamic,
    BOOL bool_is_bullet,
    uint16 index_group,
    uint16 category_bits,
    uint16 mask_bits
)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2CircleShape b2circleshape_circle;
    KGLOG_PROCESS_ERROR(ptr_sprite);
    KGLOG_PROCESS_ERROR(!ptr_sprite->GetB2Body());

    b2circleshape_circle.m_radius = float_radius /PTM_RATIO;

    num_ret_code = SetShapeBody(ptr_sprite, &b2circleshape_circle, ptr_material, float_offset_x, float_offset_y,
        bool_dynamic, bool_is_bullet, index_group, category_bits, mask_bits);
    KGLOG_PROCESS_ERROR(num_ret_code);

	num_result = TRUE;
Exit0:
    if (!num_result)
    {
        //TODO
    }
	return num_result;
}

BOOL GamePhysicsWorld::SetShapeBody(
    GameSprite* ptr_sprite,
    b2Shape* ptr_shape,
    MATERIAL* ptr_material,
    float float_offset_x,
    float float_offset_y,
    BOOL bool_dynamic,
    BOOL bool_is_bullet,
    uint16 group_index,
    uint16 category_bits,
    uint16 mask_bits
)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    Point point_offset(float_offset_x, float_offset_y);
    b2BodyDef b2bodydef_shape;
    b2Body* ptr_b2body_shape = NULL;

    b2Fixture* ptr_fixture_shape = NULL;
    b2FixtureDef b2fixturedef_shape;
    b2fixturedef_shape.filter.groupIndex = group_index;
    b2fixturedef_shape.filter.categoryBits = category_bits;
    b2fixturedef_shape.filter.maskBits = mask_bits;

    Point point_shape_position;

    assert(m_ptr_b2world);
    KGLOG_PROCESS_ERROR(ptr_sprite);
    KGLOG_PROCESS_ERROR(!ptr_sprite->GetB2Body());
    KGLOG_PROCESS_ERROR(ptr_shape);
    KGLOG_PROCESS_ERROR(ptr_material);        

    if (bool_dynamic)
    {
        b2bodydef_shape.type = b2_dynamicBody;
    }
    point_shape_position = ptr_sprite->getPosition() + point_offset;    
    b2bodydef_shape.position.Set(point_shape_position.x / PTM_RATIO, point_shape_position.y / PTM_RATIO);
    b2bodydef_shape.userData = (void*)ptr_sprite;
    if (bool_is_bullet)
    {
        b2bodydef_shape.bullet = true;
    }

    ptr_b2body_shape = m_ptr_b2world->CreateBody(&b2bodydef_shape);
    KGLOG_PROCESS_ERROR(ptr_b2body_shape);

    ptr_sprite->SetB2Body(ptr_b2body_shape);
    b2fixturedef_shape.shape = ptr_shape;
    b2fixturedef_shape.density = ptr_material->float_density;
    b2fixturedef_shape.friction = ptr_material->float_friction;
    b2fixturedef_shape.restitution = ptr_material->float_restitution;

    ptr_fixture_shape = ptr_b2body_shape->CreateFixture(&b2fixturedef_shape);
    KGLOG_PROCESS_ERROR(ptr_fixture_shape);    

    num_result = TRUE;
Exit0:
    if (!num_result)
    {
        if (ptr_b2body_shape)
        {
            m_ptr_b2world->DestroyBody(ptr_b2body_shape);
        }
        if (ptr_b2body_shape && ptr_fixture_shape)
        {
            ptr_b2body_shape->DestroyFixture(ptr_fixture_shape);
        }
    }
    return num_result;
}

BOOL GamePhysicsWorld::LoadPolygonBodyFromFile(const std::string &file_name)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;
    GB2ShapeCache* ptr_gb2_shape_cache = GB2ShapeCache::sharedGB2ShapeCache();
	KGLOG_PROCESS_ERROR(ptr_gb2_shape_cache);

    ptr_gb2_shape_cache->addShapesWithFile(file_name);

	num_result = TRUE;
Exit0:
	return num_result;
}
BOOL GamePhysicsWorld::SetPolygonBodyWithShapeName(
    GameSprite* ptr_sprite,
    const std::string &shape_name,
    float float_offset_x,
    float float_offset_y,
    BOOL bool_dynamic_body
)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    
    b2BodyDef bodyDef;
    Point position;
    Point point_offset(float_offset_x, float_offset_y);
    Point anchor_point;
    GB2ShapeCache* ptr_gb2_shape_cache = GB2ShapeCache::sharedGB2ShapeCache();
    b2Body* ptr_b2body_polygon = NULL;
    

    KGLOG_PROCESS_ERROR(ptr_sprite);
    KGLOG_PROCESS_ERROR(!ptr_sprite->GetB2Body());
    KGLOG_PROCESS_ERROR(ptr_gb2_shape_cache);
    
    bodyDef.type = b2_staticBody;
    if (bool_dynamic_body)
    {
        bodyDef.type = b2_dynamicBody;
    }
    position = ptr_sprite->getPosition() + point_offset;
    bodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
    bodyDef.userData = (void*)ptr_sprite;
    ptr_b2body_polygon = m_ptr_b2world->CreateBody(&bodyDef);
    KGLOG_PROCESS_ERROR(ptr_b2body_polygon);

    num_ret_code = ptr_gb2_shape_cache->addFixturesToBody(ptr_b2body_polygon, shape_name);
    KGLOG_PROCESS_ERROR(num_ret_code);

    anchor_point = ptr_gb2_shape_cache->anchorPointForShape(shape_name);
    ptr_sprite->setAnchorPoint(anchor_point);

    num_ret_code = ptr_sprite->SetB2Body(ptr_b2body_polygon);
    KGLOG_PROCESS_ERROR(num_ret_code);

	num_result = TRUE;
Exit0:
    if (!num_result)
    {
        if(ptr_b2body_polygon)
        {
            if (ptr_sprite->GetB2Body() != ptr_b2body_polygon)
            {
                m_ptr_b2world->DestroyBody(ptr_b2body_polygon);
            }
        }
    }
	return num_result;
}

BOOL GamePhysicsWorld::SetBodyAngularVelocity(GameSprite* ptr_sprite, float float_velocity)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2Body* ptr_b2body = NULL;

	KGLOG_PROCESS_ERROR(ptr_sprite);

    ptr_b2body = ptr_sprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body);

    ptr_b2body->SetAngularVelocity(float_velocity);

	num_result = TRUE;
Exit0:
	return num_result;
}

b2Joint* GamePhysicsWorld::CreatePrismaticJoint(
    GameSprite* ptr_sprite_a,
    float float_offset_anchor_a_x,
    float float_offset_anchor_a_y,
    GameSprite* ptr_sprite_b,
    float float_offset_anchor_b_x,
    float float_offset_anchor_b_y,
    float float_axis_x,
    float float_axis_y,
    float float_lower,
    float float_upper,
    BOOL bool_collide_connected,
    float float_motor_speed,
    float float_max_motor_force
)
{
	int num_ret_code = FALSE;

    b2Joint* ptr_b2joint = NULL;
    b2Body* ptr_b2body_a = NULL;
    b2Body* ptr_b2body_b = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite_a);
    KGLOG_PROCESS_ERROR(ptr_sprite_b);

    ptr_b2body_a = ptr_sprite_a->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_a);

    ptr_b2body_b = ptr_sprite_b->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_b);

    {
        b2PrismaticJointDef jd;
        jd.bodyA = ptr_b2body_a;
        jd.bodyB = ptr_b2body_b;
        jd.collideConnected = bool(bool_collide_connected);
        jd.localAnchorA.Set(float_offset_anchor_a_x / PTM_RATIO, float_offset_anchor_a_y / PTM_RATIO);
        jd.localAnchorB.Set(float_offset_anchor_b_x / PTM_RATIO, float_offset_anchor_b_y / PTM_RATIO);
        jd.localAxisA.Set(float_axis_x / PTM_RATIO, float_axis_y / PTM_RATIO);
        jd.referenceAngle = 0.0f;
        jd.enableLimit = bool(1);
        jd.lowerTranslation = float_lower / PTM_RATIO;
        jd.upperTranslation = float_upper / PTM_RATIO;
        jd.enableMotor = bool(1);
        jd.motorSpeed = 0.0f;
        jd.maxMotorForce = 1.0f;

        ptr_b2joint = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint);
    }
Exit0:
	return ptr_b2joint;
}

b2Joint* GamePhysicsWorld::CreateFixedPrismaticJoint(
    GameSprite* ptr_sprite,
    float float_offset_anchor_x,
    float float_offset_anchor_y,
    float float_axis_x,
    float float_axis_y,
    float float_lower,
    float float_upper,
    BOOL bool_collide_connected,
    float float_motor_speed,
    float float_max_motor_force
    )
{
    int num_ret_code = FALSE;

    b2Joint* ptr_b2joint = NULL;
    b2Body* ptr_b2body = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite);

    ptr_b2body = ptr_sprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body);

    {
        b2PrismaticJointDef jd;
        jd.bodyA = m_ptr_b2body_ground;
        jd.bodyB = ptr_b2body;
        jd.collideConnected = bool(bool_collide_connected);
        jd.localAnchorA = ptr_b2body->GetPosition();
        jd.localAnchorB.Set(float_offset_anchor_x / PTM_RATIO, float_offset_anchor_y / PTM_RATIO);
        jd.localAxisA.Set(float_axis_x / PTM_RATIO, float_axis_y / PTM_RATIO);
        jd.referenceAngle = 0.0f;
        jd.enableLimit = bool(1);
        jd.lowerTranslation = float_lower / PTM_RATIO;
        jd.upperTranslation = float_upper / PTM_RATIO;
        jd.enableMotor = bool(1);
        jd.motorSpeed = 0.0f;
        jd.maxMotorForce = 1.0f;

        ptr_b2joint = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint);
    }
Exit0:
    return ptr_b2joint;
}

b2Joint* GamePhysicsWorld::CreateDistanceJoint(
    GameSprite* ptr_sprite_a,
    float float_offset_anchor_a_x,
    float float_offset_anchor_a_y,
    GameSprite* ptr_sprite_b,    
    float float_offset_anchor_b_x,
    float float_offset_anchor_b_y,
    float float_length,
    float float_frequency_hz,
    float float_damping_ratio,
    BOOL bool_collide_connected
)
{
    b2Joint* ptr_b2joint = NULL;
    int num_ret_code = FALSE;
    
    b2Body* ptr_b2body_a = NULL;
    b2Body* ptr_b2body_b = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite_a);
    KGLOG_PROCESS_ERROR(ptr_sprite_b);

    ptr_b2body_a = ptr_sprite_a->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_a);

    ptr_b2body_b = ptr_sprite_b->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_b);

    {
        b2DistanceJointDef jd;
        jd.bodyA = ptr_b2body_a;
        jd.bodyB = ptr_b2body_b;
        jd.localAnchorA.Set(float_offset_anchor_a_x / PTM_RATIO, float_offset_anchor_a_y / PTM_RATIO);
        jd.localAnchorB.Set(float_offset_anchor_b_x / PTM_RATIO, float_offset_anchor_b_y / PTM_RATIO);
        jd.length = float_length / PTM_RATIO;
        jd.collideConnected = bool_collide_connected;
        if (float_length < 0.0f)
        {
            b2Vec2 p_a = ptr_b2body_a->GetWorldPoint(jd.localAnchorA);
            b2Vec2 p_b = ptr_b2body_b->GetWorldPoint(jd.localAnchorB);
            b2Vec2 d = p_a - p_b;            
            jd.length = d.Length();
        }
        jd.frequencyHz = float_frequency_hz;
        jd.dampingRatio = float_damping_ratio;

        ptr_b2joint = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint);
    }
Exit0:
    return ptr_b2joint;
}

b2Joint* GamePhysicsWorld::CreateWeldJoint(
    GameSprite* ptr_sprite_a,
    float float_offset_anchor_a_x,
    float float_offset_anchor_a_y,
    GameSprite* ptr_sprite_b,
    float float_offset_anchor_b_x,
    float float_offset_anchor_b_y,
    float float_frequency_hz,
    float float_damping_ratio
)
{
    int num_ret_code = FALSE;

    b2Joint* ptr_b2joint = NULL;
    b2Body* ptr_b2body_a = NULL;
    b2Body* ptr_b2body_b = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite_a);
    KGLOG_PROCESS_ERROR(ptr_sprite_b);

    ptr_b2body_a = ptr_sprite_a->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_a);

    ptr_b2body_b = ptr_sprite_b->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_b);

    {
        b2WeldJointDef jd;
        jd.bodyA = ptr_b2body_a;
        jd.bodyB = ptr_b2body_b;
        jd.localAnchorA.Set(float_offset_anchor_a_x / PTM_RATIO, float_offset_anchor_a_y / PTM_RATIO);
        jd.localAnchorB.Set(float_offset_anchor_b_x / PTM_RATIO, float_offset_anchor_b_y / PTM_RATIO);
        jd.frequencyHz = float_frequency_hz;
        jd.dampingRatio = float_damping_ratio;

        ptr_b2joint = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint);
    }
Exit0:
    return ptr_b2joint;
}

b2Joint* GamePhysicsWorld::CreateRevoluteJoint(
    GameSprite* ptr_sprite_a,
    float float_offset_anchor_a_x,
    float float_offset_anchor_a_y,
    GameSprite* ptr_sprite_b,    
    float float_offset_anchor_b_x,
    float float_offset_anchor_b_y,
    BOOL bool_enable_limit,
    float float_lower_angle,
    float float_upper_angle,
    float float_motor_speed,
    float float_max_motor_torque,
    BOOL bool_collide_connected
 )
{
    int num_ret_code = FALSE;

    b2Joint* ptr_b2joint = NULL;
    b2Body* ptr_b2body_a = NULL;
    b2Body* ptr_b2body_b = NULL;
    
    KGLOG_PROCESS_ERROR(ptr_sprite_a);
    KGLOG_PROCESS_ERROR(ptr_sprite_b);

    ptr_b2body_a = ptr_sprite_a->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_a);

    ptr_b2body_b = ptr_sprite_b->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_b);

    {
        b2RevoluteJointDef jd;        
        jd.bodyA = ptr_b2body_a;
        jd.bodyB = ptr_b2body_b;
        jd.localAnchorA.Set(float_offset_anchor_a_x / PTM_RATIO, float_offset_anchor_a_y / PTM_RATIO);
        jd.localAnchorB.Set(float_offset_anchor_b_x / PTM_RATIO, float_offset_anchor_b_y / PTM_RATIO);
        jd.enableLimit = bool(bool_enable_limit);
        jd.lowerAngle = float_lower_angle;
        jd.upperAngle = float_upper_angle;
        jd.enableMotor = bool(1);
        jd.motorSpeed = float_motor_speed;
        jd.maxMotorTorque = float_max_motor_torque;
        jd.collideConnected = bool_collide_connected;

        ptr_b2joint = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint);
    }
Exit0:
    return ptr_b2joint;
}

b2Joint* GamePhysicsWorld::CreateFixedRevoluteJoint(
    GameSprite* ptr_sprite,
    float float_offset_anchor_x,
    float float_offset_anchor_y,
    BOOL bool_enable_limit,
    float float_lower_angle,
    float float_upper_angle,
    float float_motor_speed,
    float float_max_motor_torque
)
{
    int num_ret_code = FALSE;

    b2Joint* ptr_b2joint = NULL;
    b2Body* ptr_b2body = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite);

    ptr_b2body = ptr_sprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body);

    {
        b2RevoluteJointDef jd;        
        jd.bodyA = m_ptr_b2body_ground;
        jd.bodyB = ptr_b2body;
        jd.localAnchorA = ptr_b2body->GetPosition();
        jd.localAnchorB.Set(float_offset_anchor_x / PTM_RATIO, float_offset_anchor_y / PTM_RATIO);
        jd.enableLimit = bool(bool_enable_limit);
        jd.lowerAngle = float_lower_angle;
        jd.upperAngle = float_upper_angle;
        jd.enableMotor = bool(1);
        jd.motorSpeed = float_motor_speed;
        jd.maxMotorTorque = float_max_motor_torque;

        ptr_b2joint = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint);
    }
Exit0:
    return ptr_b2joint;
}

b2Joint* GamePhysicsWorld::CreateWheelJoint(
    GameSprite* ptr_sprite_a,
    float float_offset_anchor_a_x,
    float float_offset_anchor_a_y,
    GameSprite* ptr_sprite_b,    
    float float_offset_anchor_b_x,
    float float_offset_anchor_b_y,
    float float_axis_x,
    float float_axis_y,
    float float_damping_ratio,
    BOOL bool_enable_motor,
    float float_motor_speed,
    float float_max_motor_torque
    )
{
    int num_ret_code = FALSE;

    b2Joint* ptr_b2joint = NULL;
    b2Body* ptr_b2body_a = NULL;
    b2Body* ptr_b2body_b = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite_a);
    KGLOG_PROCESS_ERROR(ptr_sprite_b);

    ptr_b2body_a = ptr_sprite_a->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_a);

    ptr_b2body_b = ptr_sprite_b->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_b);

    {
        b2WheelJointDef jd;
        jd.bodyA = ptr_b2body_a;
        jd.bodyB = ptr_b2body_b;
        jd.localAnchorA.Set(float_offset_anchor_a_x / PTM_RATIO, float_offset_anchor_a_y / PTM_RATIO);

        jd.localAnchorB.Set(float_offset_anchor_b_x / PTM_RATIO, float_offset_anchor_b_y / PTM_RATIO);
        jd.localAxisA.Set(float_axis_x, float_axis_y);
        jd.dampingRatio = float_damping_ratio;
        jd.enableMotor = bool(bool_enable_motor);
        jd.motorSpeed = float_motor_speed;
        jd.maxMotorTorque = float_max_motor_torque;

        ptr_b2joint = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint);
    }
Exit0:
    return ptr_b2joint;
}

b2Joint* GamePhysicsWorld::CreateGearJoint(
    GameSprite* ptr_sprite_a,
    GameSprite* ptr_sprite_b,
    b2Joint* ptr_b2joint_a,
    b2Joint* ptr_b2joint_b,
    float float_ratio
)
{
    int num_ret_code = FALSE;
    b2Joint* ptr_b2joint_gear = NULL;
    b2Body* ptr_b2body_a = NULL;
    b2Body* ptr_b2body_b = NULL;

    KGLOG_PROCESS_ERROR(ptr_sprite_a);
    KGLOG_PROCESS_ERROR(ptr_sprite_b);
    KGLOG_PROCESS_ERROR(ptr_b2joint_a);
    KGLOG_PROCESS_ERROR(ptr_b2joint_b);

    ptr_b2body_a = ptr_sprite_a->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_a);

    ptr_b2body_b = ptr_sprite_b->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_b);
    {
        b2GearJointDef jd;
        jd.bodyA = ptr_b2body_a;
        jd.bodyB = ptr_b2body_b;
        jd.joint1 = ptr_b2joint_a;
        jd.joint2 = ptr_b2joint_b;
        jd.ratio = float_ratio;

        ptr_b2joint_gear = m_ptr_b2world->CreateJoint(&jd);
        KGLOG_PROCESS_ERROR(ptr_b2joint_gear);
    }
Exit0:
    return ptr_b2joint_gear;
}

BOOL GamePhysicsWorld::ApplyTorque(GameSprite* sprite, float torque)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    b2Body* ptr_b2body = NULL;

    KGLOG_PROCESS_ERROR(sprite);

    ptr_b2body = sprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body);

    ptr_b2body->ApplyTorque(torque);

    num_result = TRUE;
Exit0:
    return num_result;
}

BOOL GamePhysicsWorld::ApplyImpulse(GameSprite* sprite, float float_impulse_x, float float_impulse_y)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2Body* ptr_b2body = NULL;

    KGLOG_PROCESS_ERROR(sprite);

    ptr_b2body = sprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body);

    ptr_b2body->ApplyLinearImpulse(b2Vec2(float_impulse_x / PTM_RATIO, float_impulse_y / PTM_RATIO), ptr_b2body->GetPosition());

	num_result = TRUE;
Exit0:
	return num_result;
}

BOOL GamePhysicsWorld::ApplyImpulseByAngular(GameSprite* sprite, float float_angular, float float_strength)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    b2Body* ptr_b2body = NULL;

    KGLOG_PROCESS_ERROR(sprite);

    ptr_b2body = sprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body);

    float float_impulse_x = float_strength * cos(CC_DEGREES_TO_RADIANS(float_angular));
    float float_impulse_y = float_strength * sin(CC_DEGREES_TO_RADIANS(float_angular));
    ptr_b2body->ApplyLinearImpulse(b2Vec2(float_impulse_x / PTM_RATIO, float_impulse_y / PTM_RATIO), ptr_b2body->GetPosition());

    num_result = TRUE;
Exit0:
    return num_result;
}

BOOL GamePhysicsWorld::ApplyAngularImpulse(GameSprite* sprite, float impulse)
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    b2Body* ptr_b2body = NULL;

    KGLOG_PROCESS_ERROR(sprite);

    ptr_b2body = sprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body);

    ptr_b2body->ApplyAngularImpulse(impulse);

    num_result = TRUE;
Exit0:
    return num_result;
}

BOOL GamePhysicsWorld::SetupBombCallBack(BombCallback* ptr_callback)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    KGLOG_PROCESS_ERROR(ptr_callback);
	KGLOG_PROCESS_ERROR(!m_ptr_bomb_callback);

    m_ptr_bomb_callback = ptr_callback;

	num_result = TRUE;
Exit0:
	return num_result;
}

BOOL GamePhysicsWorld::ClipperPolygonByCircle(
    GameSprite* ptr_gamesprite,
    float float_raius,
    int int_precision,
    float float_position_x,
    float float_position_y
)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2Body* ptr_b2body_old = NULL;
    b2Fixture* ptr_b2fixture = NULL;
    b2Body* ptr_b2body_new = NULL;
    b2BodyDef bodyDef;
    b2Concave b2concave;
    ClipperLib::Paths clipper_paths_clipper(1);
    float float_offset_x = 0.0f;
    float float_offset_y = 0.0f;


    KGLOG_PROCESS_ERROR(ptr_gamesprite);
    ptr_b2body_old = ptr_gamesprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_old);

    bodyDef.position = ptr_b2body_old->GetPosition();
    float_offset_x = float_position_x - bodyDef.position.x * PTM_RATIO;
    float_offset_y = float_position_y - bodyDef.position.y * PTM_RATIO;
    bodyDef.type = ptr_b2body_old->GetType();
    bodyDef.userData = ptr_b2body_old->GetUserData();
    ptr_b2body_new = m_ptr_b2world->CreateBody(&bodyDef);

    ptr_b2fixture = ptr_b2body_old->GetFixtureList();
    KGLOG_PROCESS_ERROR(ptr_b2fixture);    

    num_ret_code = getClipperCircle(float_raius, int_precision, &clipper_paths_clipper, float_offset_x, float_offset_y);
    KGLOG_PROCESS_ERROR(num_ret_code);

    while (ptr_b2fixture)
    {
        ClipperLib::Paths clipper_paths_main(1);
        
        ClipperLib::Paths clipper_paths_result;
        ClipperLib::Clipper clipper;

        num_ret_code = getPolygonFormBody(ptr_b2fixture, &clipper_paths_main);
        KGLOG_PROCESS_ERROR(num_ret_code);

        num_ret_code = clipper.AddPaths(clipper_paths_main, ptSubject, true);
        KGLOG_PROCESS_ERROR(num_ret_code);

        num_ret_code = clipper.AddPaths(clipper_paths_clipper, ptClip, true);
        KGLOG_PROCESS_ERROR(num_ret_code);

        num_ret_code = clipper.Execute(ClipperLib::ctDifference, clipper_paths_result, pftNonZero, pftNonZero);
        KGLOG_PROCESS_ERROR(num_ret_code);

        Paths::iterator it_group = clipper_paths_result.begin();
        for(NULL; it_group != clipper_paths_result.end(); ++it_group)
        {
            Path::iterator it = it_group->begin();
            b2Vec2 vec_vertices[1000];
            int count_vertices = 0;

            b2FixtureDef b2fixturedef_new;
            b2fixturedef_new.restitution = ptr_b2fixture->GetRestitution();
            b2fixturedef_new.friction = ptr_b2fixture->GetFriction();
            b2fixturedef_new.density = ptr_b2fixture->GetDensity();

            for(NULL; it != it_group->end(); ++it)
            {
                vec_vertices[count_vertices++].Set(float(it->X) / (PTM_RATIO * CLIPPER_RATIO), float(it->Y) / (PTM_RATIO * CLIPPER_RATIO));
            }
            num_ret_code = b2concave.Create(ptr_b2body_new, &b2fixturedef_new, vec_vertices, count_vertices);
            KGLOG_PROCESS_ERROR(num_ret_code);
        }
        ptr_b2fixture = ptr_b2fixture->GetNext();
    }

    num_ret_code = ptr_gamesprite->SetB2Body(ptr_b2body_new);
    KGLOG_PROCESS_ERROR(num_ret_code);

    m_ptr_b2world->DestroyBody(ptr_b2body_old);
    ptr_b2body_old = NULL;

	num_result = TRUE;
Exit0:
    if (!num_result)
    {
        if(ptr_b2body_new)
        {
            m_ptr_b2world->DestroyBody(ptr_b2body_new);
            ptr_b2body_new = NULL;
        }
    }
	return num_result;
}

BOOL GamePhysicsWorld::ClipperPolygonByShape(
    GameSprite* ptr_gamesprite,
    const std::string &shape_name,
    float float_position_x,
    float float_position_y
    )
{
    int num_result = FALSE;
    int num_ret_code = FALSE;

    b2Body* ptr_b2body_old = NULL;
    b2Fixture* ptr_b2fixture = NULL;
    b2Body* ptr_b2body_new = NULL;
    b2BodyDef bodyDef;
    b2Concave b2concave;
    ClipperLib::Paths clipper_paths_clipper(1);
    float float_offset_x = 0.0f;
    float float_offset_y = 0.0f;


    KGLOG_PROCESS_ERROR(ptr_gamesprite);
    ptr_b2body_old = ptr_gamesprite->GetB2Body();
    KGLOG_PROCESS_ERROR(ptr_b2body_old);

    bodyDef.position = ptr_b2body_old->GetPosition();
    float_offset_x = float_position_x - bodyDef.position.x * PTM_RATIO;
    float_offset_y = float_position_y - bodyDef.position.y * PTM_RATIO;
    bodyDef.type = ptr_b2body_old->GetType();
    bodyDef.userData = ptr_b2body_old->GetUserData();
    ptr_b2body_new = m_ptr_b2world->CreateBody(&bodyDef);

    ptr_b2fixture = ptr_b2body_old->GetFixtureList();
    KGLOG_PROCESS_ERROR(ptr_b2fixture);    

    num_ret_code = getPolygonFromCache(shape_name, &clipper_paths_clipper, float_offset_x, float_offset_y);
    KGLOG_PROCESS_ERROR(num_ret_code);

    while (ptr_b2fixture)
    {
        ClipperLib::Paths clipper_paths_main(1);

        ClipperLib::Paths clipper_paths_result;
        ClipperLib::Clipper clipper;

        num_ret_code = getPolygonFormBody(ptr_b2fixture, &clipper_paths_main);
        KGLOG_PROCESS_ERROR(num_ret_code);

        num_ret_code = clipper.AddPaths(clipper_paths_main, ptSubject, true);
        KGLOG_PROCESS_ERROR(num_ret_code);

        num_ret_code = clipper.AddPaths(clipper_paths_clipper, ptClip, true);
        KGLOG_PROCESS_ERROR(num_ret_code);

        num_ret_code = clipper.Execute(ClipperLib::ctDifference, clipper_paths_result, pftNonZero, pftNonZero);
        KGLOG_PROCESS_ERROR(num_ret_code);

        Paths::iterator it_group = clipper_paths_result.begin();
        for(NULL; it_group != clipper_paths_result.end(); ++it_group)
        {
            Path::iterator it = it_group->begin();
            b2Vec2 vec_vertices[1000];
            int count_vertices = 0;

            b2FixtureDef b2fixturedef_new;
            b2fixturedef_new.restitution = ptr_b2fixture->GetRestitution();
            b2fixturedef_new.friction = ptr_b2fixture->GetFriction();
            b2fixturedef_new.density = ptr_b2fixture->GetDensity();

            for(NULL; it != it_group->end(); ++it)
            {
                vec_vertices[count_vertices++].Set(float(it->X) / (PTM_RATIO * CLIPPER_RATIO), float(it->Y) / (PTM_RATIO * CLIPPER_RATIO));
            }
            num_ret_code = b2concave.Create(ptr_b2body_new, &b2fixturedef_new, vec_vertices, count_vertices);
            KGLOG_PROCESS_ERROR(num_ret_code);
        }
        ptr_b2fixture = ptr_b2fixture->GetNext();
    }

    num_ret_code = ptr_gamesprite->SetB2Body(ptr_b2body_new);
    KGLOG_PROCESS_ERROR(num_ret_code);

    m_ptr_b2world->DestroyBody(ptr_b2body_old);
    ptr_b2body_old = NULL;

    num_result = TRUE;
Exit0:
    if (!num_result)
    {
        if(ptr_b2body_new)
        {
            m_ptr_b2world->DestroyBody(ptr_b2body_new);
            ptr_b2body_new = NULL;
        }
    }
    return num_result;
}

BOOL GamePhysicsWorld::getPolygonFormBody(b2Fixture* ptr_b2fixture, ClipperLib::Paths* ptr_clipper_paths)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2PolygonShape* ptr_b2shape_polygon = NULL;

    KGLOG_PROCESS_ERROR(ptr_b2fixture);
    KGLOG_PROCESS_ERROR(ptr_b2fixture->GetType() == b2Shape::e_polygon);

    ptr_b2shape_polygon = (b2PolygonShape*)ptr_b2fixture->GetShape();
    KGLOG_PROCESS_ERROR(ptr_b2shape_polygon);

    for (int i = 0;i < ptr_b2shape_polygon->m_vertexCount; i++)
    {
        int integer_vertice_x = ptr_b2shape_polygon->m_vertices[i].x * PTM_RATIO * 1000;
        int integer_vertice_y = ptr_b2shape_polygon->m_vertices[i].y * PTM_RATIO * 1000;
        (*ptr_clipper_paths)[0].push_back(IntPoint(integer_vertice_x, integer_vertice_y));
    }	

	num_result = TRUE;
Exit0:
	return num_result;
}

BOOL GamePhysicsWorld::getPolygonFromCache(const std::string &shape_name, ClipperLib::Paths* ptr_clipper_paths, float float_offset_x, float float_offset_y)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;
    GB2FixtureDef* ptr_gb2_fixture_def = NULL;
    GB2ShapeCache* ptr_gb2_shape_cache = GB2ShapeCache::sharedGB2ShapeCache();

    KGLOG_PROCESS_ERROR(ptr_gb2_shape_cache);

    ptr_gb2_fixture_def = ptr_gb2_shape_cache->GetFixtures(shape_name);
    KGLOG_PROCESS_ERROR(ptr_gb2_fixture_def);

    if (ptr_gb2_fixture_def)
    {
        b2FixtureDef* ptr_b2fixture_def = &ptr_gb2_fixture_def->fixture;
        KGLOG_PROCESS_ERROR(ptr_b2fixture_def);

        const b2Shape* ptr_b2shape = ptr_b2fixture_def->shape;
        KGLOG_PROCESS_ERROR(ptr_b2shape->GetType() == b2Shape::e_polygon);

        const b2PolygonShape* ptr_b2polygonshape = (const b2PolygonShape*)ptr_b2shape;

        for (int i = 0;i < ptr_b2polygonshape->m_vertexCount; i++)
        {
            int integer_vertice_x = ptr_b2polygonshape->m_vertices[i].x * PTM_RATIO;
            int integer_vertice_y = ptr_b2polygonshape->m_vertices[i].y * PTM_RATIO;
            (*ptr_clipper_paths)[0].push_back(IntPoint((integer_vertice_x + float_offset_x) * 1000, (integer_vertice_y + float_offset_y) * 1000));
        }
    }
    num_result = TRUE;
Exit0:
	return num_result;
}

BOOL GamePhysicsWorld::getClipperCircle(float float_radius, int int_precision, ClipperLib::Paths* ptr_clipper_paths, float float_offset_x, float float_offset_y)
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    float angle = 2 * 3.14 / int_precision;
    for (int i = 0; i < int_precision; i++) 
    {
        int integer_vertice_x = (float_offset_x + float_radius * cos(angle * i)) * CLIPPER_RATIO;
        int integer_vertice_y = (float_offset_y + float_radius * sin(angle * i)) * CLIPPER_RATIO;
        (*ptr_clipper_paths)[0].push_back(IntPoint(integer_vertice_x, integer_vertice_y));
    }

	num_result = TRUE;
Exit0:
	return num_result;
}