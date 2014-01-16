#ifndef __DEBUG_LAYER_H__
#define __DEBUG_LAYER_H__

#include "gles_render.h" 
#include "game_physics_world.h"
USING_NS_CC;

class DebugPhysicsLayer : public Layer {
public:
    DebugPhysicsLayer(){};
    ~DebugPhysicsLayer() {
        SAFE_DELETE(m_ptr_gles_debug_draw);
    }
    virtual bool init ();

    BOOL SetupWorld();
    virtual void draw();

    CREATE_FUNC (DebugPhysicsLayer);
private:
    GLESDebugDraw* m_ptr_gles_debug_draw;
    b2World* m_ptr_b2World;
};
#endif