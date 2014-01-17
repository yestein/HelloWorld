#include "debug_physics_layer.h" 
#include "game_physics_world.h"

DebugPhysicsLayer::DebugPhysicsLayer()
    :m_ptr_gles_debug_draw(NULL)
    ,m_ptr_b2World(NULL)
{

}
bool DebugPhysicsLayer::init() 
{
	bool bool_result = false;
	int num_ret_code = FALSE;
    uint32 flags = 0;

    m_ptr_gles_debug_draw = NULL;
    m_ptr_b2World = NULL;

	KGLOG_PROCESS_ERROR(Layer::init());
    m_ptr_gles_debug_draw = new GLESDebugDraw(PTM_RATIO);
    KGLOG_PROCESS_ERROR(m_ptr_gles_debug_draw);
    
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    //flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    m_ptr_gles_debug_draw->SetFlags(flags);

    KGLOG_PROCESS_ERROR(SetupWorld());

	bool_result = true;
Exit0:
	return bool_result;
}

BOOL DebugPhysicsLayer::SetupWorld()
{
	int num_result = FALSE;
	int num_ret_code = FALSE;

    b2World* b2world = GamePhysicsWorld::GetInstance()->GetWorld();
    KGLOG_PROCESS_ERROR(b2world);

    m_ptr_b2World = b2world;

    m_ptr_b2World->SetDebugDraw(m_ptr_gles_debug_draw);

	num_result = TRUE;
Exit0:
	return num_result;

}

void DebugPhysicsLayer::draw()
{
    if (!m_ptr_b2World)
    {
        return;
    }
    CCLayer::draw();

    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);

    kmGLPushMatrix();

    m_ptr_b2World->DrawDebugData();

    kmGLPopMatrix();
}
