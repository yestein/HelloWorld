#ifndef __TOLUA_GAME_PHYSICS_WORLD_H__
#define __TOLUA_GAME_PHYSICS_WORLD_H__

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}

#include "game_physics_world.h"
#include "debug_physics_layer.h"

TOLUA_API int tolua_lua_module_open(lua_State* tolua_S);
USING_NS_CC;

#endif // __TOLUA_GAME_PHYSICS_WORLD_H__