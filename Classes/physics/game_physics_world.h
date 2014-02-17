


#ifndef __GAME_PHYSICS_WORLD_H__
#define __GAME_PHYSICS_WORLD_H__

#include "Base.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "clipper.hpp"
USING_NS_CC;

#define PTM_RATIO 32
#define CLIPPER_RATIO 1000

class GameSprite;
class BombSprite;

class BombCallback
{
public:
    virtual ~BombCallback() {}

    virtual BOOL Bomb(GameSprite* ptr_sprite) = 0;
    virtual BOOL BeBombed(BombSprite* ptr_bomb_sprite, GameSprite* ptr_sprite) = 0;
};

class GamePhysicsWorld : public b2ContactListener
{
public:
    typedef std::set<GameSprite*> CollideVector;
    struct MATERIAL
    {
        MATERIAL(float density, float friction, float restitution)
        {
            float_density = density;
            float_friction = friction;
            float_restitution = restitution;
        }
        float float_density;
        float float_friction;
        float float_restitution;
    };
    
public:
	GamePhysicsWorld():m_ptr_b2world(NULL) {};
	~GamePhysicsWorld(){};
	static GamePhysicsWorld* GetInstance()
	{
		if (!ms_ptr_instance)
		{
			ms_ptr_instance = new GamePhysicsWorld();
		}
		return ms_ptr_instance;
	}
	BOOL Init(float float_gravity_x, float float_gravity_y);
	BOOL Uninit();

    // Callbacks for derived classes.
    virtual void BeginContact(b2Contact* contact) override{ B2_NOT_USED(contact); };
    virtual void EndContact(b2Contact* contact) override { B2_NOT_USED(contact); }
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
//     {
//         B2_NOT_USED(contact);
//         B2_NOT_USED(oldManifold);
//     }
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }

    BOOL SetupBombCallBack(BombCallback* ptr_callback);

    BOOL SetGravity(float float_gravity_x, float float_gravity_y)
    {
        m_ptr_b2world->SetGravity(b2Vec2(float_gravity_x, float_gravity_y));
        return TRUE;
    }

    BOOL SetBodyCenter(

    );

    BOOL CreateRectEdge(
        GameSprite* ptr_sprite,
        float float_left,
        float float_right, 
        float float_buttom,
        float float_top
    );

    BOOL SetBoxBody(
        GameSprite* ptr_sprite, 
        float float_width,
        float float_height,
        MATERIAL* ptr_material,
        float float_offset_x,
        float float_offset_y,
        BOOL bool_dynamic,
        BOOL bool_is_bullet = 0,
        uint16 groupIndex = 0,
        uint16 categoryBits = 0x0001,
        uint16 maskBits = 0xFFFF
    );

    BOOL SetPolygonBody(
        GameSprite* ptr_sprite,
        const std::string &shape_name,
        float float_offset_x,
        float float_offset_y,
        BOOL bool_dynamic_body
    );


    BOOL SetCircleBody(GameSprite* ptr_sprite, 
        float float_radius,
        MATERIAL* ptr_material,
        float float_offset_x,
        float float_offset_y,
        BOOL bool_dynamic,
        BOOL bool_is_bullet = 0,
        uint16 groupIndex = 0,
        uint16 categoryBits = 0x0001,
        uint16 maskBits = 0xFFFF
    );

    BOOL SetShapeBody(
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
    );

    BOOL SetBodyAngularVelocity(GameSprite* ptr_sprite, float float_velocity);

    // 从.plist文件中读取多边形
    BOOL LoadPolygonBodyFromFile(const std::string &file_name);
    BOOL SetPolygonBodyWithShapeName(
        GameSprite* ptr_sprite,
        const std::string &shape_name,
        float float_offset_x,
        float float_offset_y,
        BOOL bool_dynamic_body
    );

    // 绑定有距线段关节
    b2Joint* CreateDistanceJoint(
        GameSprite* ptr_sprite_a,
        float float_offset_anchor_a_x,
        float float_offset_anchor_a_y,
        GameSprite* ptr_sprite_b,    
        float float_offset_anchor_b_x,
        float float_offset_anchor_b_y,
        float float_length = -1.0f,
        float float_frequency_hz = 0.0f,
        float float_damping_ratio = 0.0f,
        BOOL bool_collide_connected = 0
    );

    // 绑定焊接关节
    b2Joint* CreateWeldJoint(
        GameSprite* ptr_sprite_a,
        float float_offset_anchor_a_x,
        float float_offset_anchor_a_y,
        GameSprite* ptr_sprite_b,
        float float_offset_anchor_b_x,
        float float_offset_anchor_b_y,
        float float_frequency_hz = 0.0f,
        float float_damping_ratio = 0.0f
    );

    // 绑定伸缩关节
    b2Joint* CreatePrismaticJoint(
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
        BOOL bool_collide_connected = 0,
        float float_motor_speed = 0.0f,
        float float_max_motor_force = 0.0f
    );

    // 绑定固定伸缩关节
    b2Joint* CreateFixedPrismaticJoint(
        GameSprite* ptr_sprite,
        float float_offset_anchor_x,
        float float_offset_anchor_y,
        float float_axis_x,
        float float_axis_y,
        float float_lower,
        float float_upper,
        BOOL bool_collide_connected = 0,
        float float_motor_speed = 0.0f,
        float float_max_motor_force = 0.0f
    );    

    // 绑定旋转关节，注：角度单位为弧度制（π）
    b2Joint* CreateRevoluteJoint(
        GameSprite* ptr_sprite_a,
        float float_offset_anchor_a_x,
        float float_offset_anchor_a_y,
        GameSprite* ptr_sprite_b,    
        float float_offset_anchor_b_x,
        float float_offset_anchor_b_y,
        BOOL bool_enable_limit = 0,
        float float_lower_angle = 0.0f,
        float float_upper_angle = 0.0f,
        float float_motor_speed = 0.0f,
        float float_max_motor_torque = 0.0f,
        BOOL bool_collide_connected = 0
    );

    // 绑定固定旋转关节，注：角度单位为弧度制（π）
    b2Joint* CreateFixedRevoluteJoint(
        GameSprite* ptr_sprite,
        float float_offset_anchor_x,
        float float_offset_anchor_y,
        BOOL bool_enable_limit = 0,
        float float_lower_angle = 0.0f,
        float float_upper_angle = 0.0f,
        float float_motor_speed = -10.0f,
        float float_max_motor_torque = 0.0f
    );

    // 绑定车轮关节（与旋转关节的区别在于可以产生颠簸效果）
    b2Joint* CreateWheelJoint(
        GameSprite* ptr_sprite_a,
        float float_offset_anchor_a_x,
        float float_offset_anchor_a_y,
        GameSprite* ptr_sprite_b,    
        float float_offset_anchor_b_x,
        float float_offset_anchor_b_y,
        float float_axis_x,
        float float_axis_y,
        float float_damping_ratio = 0.7f,
        BOOL bool_enable_motor = 1,
        float float_motor_speed = -10.0f,
        float float_max_motor_torque = 2.0f
    );

    
    // 绑定齿轮关节
    b2Joint* CreateGearJoint(
        GameSprite* ptr_sprite_a,
        GameSprite* ptr_sprite_b,
        b2Joint* joint_a,
        b2Joint* joint_b,
        float float_ratio
    );
    
    BOOL ApplyTorque(GameSprite* sprite, float torque);
    BOOL ApplyImpulse(GameSprite* sprite, float float_impulse_x, float float_impulse_y);
    BOOL ApplyImpulseByAngular(GameSprite* sprite, float float_angular, float float_strength);
    BOOL ApplyAngularImpulse(GameSprite* sprite, float impulse);

    BOOL Update(float float_delta);
    
    BOOL Bomb(BombSprite* bomb_sprite);

    BOOL MouseDown(float float_x, float float_y);
    void MouseUp(float float_x, float float_y);
    BOOL MouseMove(float float_x, float float_y);

    BOOL ClipperPolygonByCircle(
        GameSprite* ptr_gamesprite,
        float float_raius,
        int int_precision,
        float float_position_x,
        float float_position_y
    );

    BOOL ClipperPolygonByShape(
        GameSprite* ptr_gamesprite,
        const std::string &shape_name,
        float float_position_x,
        float float_position_y
        );

    b2World* GetWorld(){ return m_ptr_b2world;}

private:

    BOOL processCollide();
    BOOL getPolygonFormBody(b2Fixture* ptr_b2fixture, ClipperLib::Paths* ptr_clipper_paths);
    BOOL getClipperCircle(float float_radius, int int_precision, ClipperLib::Paths* ptr_clipper_paths, float float_offset_x, float float_offset_y);
    BOOL getPolygonFromCache(const std::string &shape_name, ClipperLib::Paths* ptr_clipper_paths, float float_offset_x, float float_offset_y);
private:
	static GamePhysicsWorld* ms_ptr_instance;
    CollideVector m_array_collide;
	b2World* m_ptr_b2world;

    b2Vec2 m_b2vec_mouse_position;
    b2MouseJoint* m_ptr_b2joint_mouse;
    b2Body* m_ptr_b2body_ground;
    BombCallback* m_ptr_bomb_callback;
};
#endif