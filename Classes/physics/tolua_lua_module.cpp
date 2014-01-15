/*
** Lua binding: lua_module
** Generated automatically by tolua++-1.0.92 on 01/15/14 11:38:25.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_lua_module_open (lua_State* tolua_S);

#include "tolua_lua_module.hpp"
#include "game_physics_world.h"  
#include "game_sprite.h"  
#include "bomb_sprite.h"  
#include "Box2D/Dynamics/b2Body.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_GameSprite (lua_State* tolua_S)
{
 GameSprite* self = (GameSprite*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_GamePhysicsWorld (lua_State* tolua_S)
{
 GamePhysicsWorld* self = (GamePhysicsWorld*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_GamePhysicsWorld__MATERIAL (lua_State* tolua_S)
{
 GamePhysicsWorld::MATERIAL* self = (GamePhysicsWorld::MATERIAL*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_DebugPhysicsLayer (lua_State* tolua_S)
{
 DebugPhysicsLayer* self = (DebugPhysicsLayer*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_BombSprite (lua_State* tolua_S)
{
 BombSprite* self = (BombSprite*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Layer");
 tolua_usertype(tolua_S,"DebugPhysicsLayer");
 tolua_usertype(tolua_S,"GameSprite");
 tolua_usertype(tolua_S,"Sprite");
 tolua_usertype(tolua_S,"Rect");
 tolua_usertype(tolua_S,"BombSprite");
 tolua_usertype(tolua_S,"GamePhysicsWorld");
 tolua_usertype(tolua_S,"SpriteFrame");
 tolua_usertype(tolua_S,"b2Body");
 tolua_usertype(tolua_S,"Texture2D");
 tolua_usertype(tolua_S,"GamePhysicsWorld::MATERIAL");
}

/* method: new of class  MATERIAL */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_MATERIAL_new00
static int tolua_lua_module_GamePhysicsWorld_MATERIAL_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GamePhysicsWorld::MATERIAL",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float density = ((float)  tolua_tonumber(tolua_S,2,0));
  float friction = ((float)  tolua_tonumber(tolua_S,3,0));
  float restitution = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   GamePhysicsWorld::MATERIAL* tolua_ret = (GamePhysicsWorld::MATERIAL*)  Mtolua_new((GamePhysicsWorld::MATERIAL)(density,friction,restitution));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GamePhysicsWorld::MATERIAL");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MATERIAL */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_MATERIAL_new00_local
static int tolua_lua_module_GamePhysicsWorld_MATERIAL_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GamePhysicsWorld::MATERIAL",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float density = ((float)  tolua_tonumber(tolua_S,2,0));
  float friction = ((float)  tolua_tonumber(tolua_S,3,0));
  float restitution = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   GamePhysicsWorld::MATERIAL* tolua_ret = (GamePhysicsWorld::MATERIAL*)  Mtolua_new((GamePhysicsWorld::MATERIAL)(density,friction,restitution));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GamePhysicsWorld::MATERIAL");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_new00
static int tolua_lua_module_GamePhysicsWorld_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GamePhysicsWorld* tolua_ret = (GamePhysicsWorld*)  Mtolua_new((GamePhysicsWorld)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GamePhysicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_new00_local
static int tolua_lua_module_GamePhysicsWorld_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GamePhysicsWorld* tolua_ret = (GamePhysicsWorld*)  Mtolua_new((GamePhysicsWorld)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GamePhysicsWorld");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_delete00
static int tolua_lua_module_GamePhysicsWorld_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_GetInstance00
static int tolua_lua_module_GamePhysicsWorld_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GamePhysicsWorld* tolua_ret = (GamePhysicsWorld*)  GamePhysicsWorld::GetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GamePhysicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_Init00
static int tolua_lua_module_GamePhysicsWorld_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float float_gravity_x = ((float)  tolua_tonumber(tolua_S,2,0));
  float float_gravity_y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Init(float_gravity_x,float_gravity_y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Uninit of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_Uninit00
static int tolua_lua_module_GamePhysicsWorld_Uninit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Uninit'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Uninit();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Uninit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRectEdge of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreateRectEdge00
static int tolua_lua_module_GamePhysicsWorld_CreateRectEdge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float float_left = ((float)  tolua_tonumber(tolua_S,2,0));
  float float_right = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_buttom = ((float)  tolua_tonumber(tolua_S,4,0));
  float float_top = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRectEdge'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateRectEdge(float_left,float_right,float_buttom,float_top);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateRectEdge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBoxBody of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_SetBoxBody00
static int tolua_lua_module_GamePhysicsWorld_SetBoxBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"GamePhysicsWorld::MATERIAL",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_width = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_height = ((float)  tolua_tonumber(tolua_S,4,0));
  GamePhysicsWorld::MATERIAL* ptr_material = ((GamePhysicsWorld::MATERIAL*)  tolua_tousertype(tolua_S,5,0));
  float float_offset_x = ((float)  tolua_tonumber(tolua_S,6,0));
  float float_offset_y = ((float)  tolua_tonumber(tolua_S,7,0));
  int bool_dynamic = ((int)  tolua_tonumber(tolua_S,8,0));
  int bool_is_bullet = ((int)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBoxBody'", NULL);
#endif
  {
   int tolua_ret = (int)  self->SetBoxBody(ptr_sprite,float_width,float_height,ptr_material,float_offset_x,float_offset_y,bool_dynamic,bool_is_bullet);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBoxBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCircleBody of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_SetCircleBody00
static int tolua_lua_module_GamePhysicsWorld_SetCircleBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"GamePhysicsWorld::MATERIAL",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_radius = ((float)  tolua_tonumber(tolua_S,3,0));
  GamePhysicsWorld::MATERIAL* ptr_material = ((GamePhysicsWorld::MATERIAL*)  tolua_tousertype(tolua_S,4,0));
  float float_offset_x = ((float)  tolua_tonumber(tolua_S,5,0));
  float float_offset_y = ((float)  tolua_tonumber(tolua_S,6,0));
  int bool_dynamic = ((int)  tolua_tonumber(tolua_S,7,0));
  int bool_is_bullet = ((int)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCircleBody'", NULL);
#endif
  {
   int tolua_ret = (int)  self->SetCircleBody(ptr_sprite,float_radius,ptr_material,float_offset_x,float_offset_y,bool_dynamic,bool_is_bullet);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCircleBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBodyAngularVelocity of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_SetBodyAngularVelocity00
static int tolua_lua_module_GamePhysicsWorld_SetBodyAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_velocity = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBodyAngularVelocity'", NULL);
#endif
  {
   int tolua_ret = (int)  self->SetBodyAngularVelocity(ptr_sprite,float_velocity);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBodyAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadPolygonBodyFromFile of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_LoadPolygonBodyFromFile00
static int tolua_lua_module_GamePhysicsWorld_LoadPolygonBodyFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  const std::string file_name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadPolygonBodyFromFile'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LoadPolygonBodyFromFile(file_name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)file_name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadPolygonBodyFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPolygonBodyWithShapeName of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_SetPolygonBodyWithShapeName00
static int tolua_lua_module_GamePhysicsWorld_SetPolygonBodyWithShapeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  const std::string shape_name = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  float float_offset_x = ((float)  tolua_tonumber(tolua_S,4,0));
  float float_offset_y = ((float)  tolua_tonumber(tolua_S,5,0));
  int bool_dynamic_body = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPolygonBodyWithShapeName'", NULL);
#endif
  {
   int tolua_ret = (int)  self->SetPolygonBodyWithShapeName(ptr_sprite,shape_name,float_offset_x,float_offset_y,bool_dynamic_body);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)shape_name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPolygonBodyWithShapeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateDistanceJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreateDistanceJoint00
static int tolua_lua_module_GamePhysicsWorld_CreateDistanceJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,11,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite_a = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_offset_anchor_a_x = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_offset_anchor_a_y = ((float)  tolua_tonumber(tolua_S,4,0));
  GameSprite* ptr_sprite_b = ((GameSprite*)  tolua_tousertype(tolua_S,5,0));
  float float_offset_anchor_b_x = ((float)  tolua_tonumber(tolua_S,6,0));
  float float_offset_anchor_b_y = ((float)  tolua_tonumber(tolua_S,7,0));
  float float_length = ((float)  tolua_tonumber(tolua_S,8,-1.0f));
  float float_frequency_hz = ((float)  tolua_tonumber(tolua_S,9,0.0f));
  float float_damping_ratio = ((float)  tolua_tonumber(tolua_S,10,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateDistanceJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateDistanceJoint(ptr_sprite_a,float_offset_anchor_a_x,float_offset_anchor_a_y,ptr_sprite_b,float_offset_anchor_b_x,float_offset_anchor_b_y,float_length,float_frequency_hz,float_damping_ratio);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateDistanceJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreatePrismaticJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreatePrismaticJoint00
static int tolua_lua_module_GamePhysicsWorld_CreatePrismaticJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,14,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,15,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite_a = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_offset_anchor_a_x = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_offset_anchor_a_y = ((float)  tolua_tonumber(tolua_S,4,0));
  GameSprite* ptr_sprite_b = ((GameSprite*)  tolua_tousertype(tolua_S,5,0));
  float float_offset_anchor_b_x = ((float)  tolua_tonumber(tolua_S,6,0));
  float float_offset_anchor_b_y = ((float)  tolua_tonumber(tolua_S,7,0));
  float float_axis_x = ((float)  tolua_tonumber(tolua_S,8,0));
  float float_axis_y = ((float)  tolua_tonumber(tolua_S,9,0));
  float float_lower = ((float)  tolua_tonumber(tolua_S,10,0));
  float float_upper = ((float)  tolua_tonumber(tolua_S,11,0));
  int bool_collide_connected = ((int)  tolua_tonumber(tolua_S,12,0));
  float float_motor_speed = ((float)  tolua_tonumber(tolua_S,13,0.0f));
  float float_max_motor_force = ((float)  tolua_tonumber(tolua_S,14,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreatePrismaticJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreatePrismaticJoint(ptr_sprite_a,float_offset_anchor_a_x,float_offset_anchor_a_y,ptr_sprite_b,float_offset_anchor_b_x,float_offset_anchor_b_y,float_axis_x,float_axis_y,float_lower,float_upper,bool_collide_connected,float_motor_speed,float_max_motor_force);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreatePrismaticJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateFixedPrismaticJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreateFixedPrismaticJoint00
static int tolua_lua_module_GamePhysicsWorld_CreateFixedPrismaticJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_offset_anchor_x = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_offset_anchor_y = ((float)  tolua_tonumber(tolua_S,4,0));
  float float_axis_x = ((float)  tolua_tonumber(tolua_S,5,0));
  float float_axis_y = ((float)  tolua_tonumber(tolua_S,6,0));
  float float_lower = ((float)  tolua_tonumber(tolua_S,7,0));
  float float_upper = ((float)  tolua_tonumber(tolua_S,8,0));
  int bool_collide_connected = ((int)  tolua_tonumber(tolua_S,9,0));
  float float_motor_speed = ((float)  tolua_tonumber(tolua_S,10,0.0f));
  float float_max_motor_force = ((float)  tolua_tonumber(tolua_S,11,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateFixedPrismaticJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateFixedPrismaticJoint(ptr_sprite,float_offset_anchor_x,float_offset_anchor_y,float_axis_x,float_axis_y,float_lower,float_upper,bool_collide_connected,float_motor_speed,float_max_motor_force);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateFixedPrismaticJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateRevoluteJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreateRevoluteJoint00
static int tolua_lua_module_GamePhysicsWorld_CreateRevoluteJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite_a = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_offset_anchor_a_x = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_offset_anchor_a_y = ((float)  tolua_tonumber(tolua_S,4,0));
  GameSprite* ptr_sprite_b = ((GameSprite*)  tolua_tousertype(tolua_S,5,0));
  float float_offset_anchor_b_x = ((float)  tolua_tonumber(tolua_S,6,0));
  float float_offset_anchor_b_y = ((float)  tolua_tonumber(tolua_S,7,0));
  int bool_enable_limit = ((int)  tolua_tonumber(tolua_S,8,0));
  float float_lower_angle = ((float)  tolua_tonumber(tolua_S,9,0.0f));
  float float_upper_angle = ((float)  tolua_tonumber(tolua_S,10,0.0f));
  float float_motor_speed = ((float)  tolua_tonumber(tolua_S,11,0.0f));
  float float_max_motor_torque = ((float)  tolua_tonumber(tolua_S,12,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateRevoluteJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateRevoluteJoint(ptr_sprite_a,float_offset_anchor_a_x,float_offset_anchor_a_y,ptr_sprite_b,float_offset_anchor_b_x,float_offset_anchor_b_y,bool_enable_limit,float_lower_angle,float_upper_angle,float_motor_speed,float_max_motor_torque);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateRevoluteJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateFixedRevoluteJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreateFixedRevoluteJoint00
static int tolua_lua_module_GamePhysicsWorld_CreateFixedRevoluteJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_offset_anchor_x = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_offset_anchor_y = ((float)  tolua_tonumber(tolua_S,4,0));
  int bool_enable_limit = ((int)  tolua_tonumber(tolua_S,5,0));
  float float_lower_angle = ((float)  tolua_tonumber(tolua_S,6,0.0f));
  float float_upper_angle = ((float)  tolua_tonumber(tolua_S,7,0.0f));
  float float_motor_speed = ((float)  tolua_tonumber(tolua_S,8,-10.0f));
  float float_max_motor_torque = ((float)  tolua_tonumber(tolua_S,9,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateFixedRevoluteJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateFixedRevoluteJoint(ptr_sprite,float_offset_anchor_x,float_offset_anchor_y,bool_enable_limit,float_lower_angle,float_upper_angle,float_motor_speed,float_max_motor_torque);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateFixedRevoluteJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateWheelJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreateWheelJoint00
static int tolua_lua_module_GamePhysicsWorld_CreateWheelJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,14,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite_a = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_offset_anchor_a_x = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_offset_anchor_a_y = ((float)  tolua_tonumber(tolua_S,4,0));
  GameSprite* ptr_sprite_b = ((GameSprite*)  tolua_tousertype(tolua_S,5,0));
  float float_offset_anchor_b_x = ((float)  tolua_tonumber(tolua_S,6,0));
  float float_offset_anchor_b_y = ((float)  tolua_tonumber(tolua_S,7,0));
  float float_axis_x = ((float)  tolua_tonumber(tolua_S,8,0));
  float float_axis_y = ((float)  tolua_tonumber(tolua_S,9,0));
  float float_damping_ratio = ((float)  tolua_tonumber(tolua_S,10,0.7f));
  int bool_enable_motor = ((int)  tolua_tonumber(tolua_S,11,1));
  float float_motor_speed = ((float)  tolua_tonumber(tolua_S,12,-10.0f));
  float float_max_motor_torque = ((float)  tolua_tonumber(tolua_S,13,2.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateWheelJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateWheelJoint(ptr_sprite_a,float_offset_anchor_a_x,float_offset_anchor_a_y,ptr_sprite_b,float_offset_anchor_b_x,float_offset_anchor_b_y,float_axis_x,float_axis_y,float_damping_ratio,bool_enable_motor,float_motor_speed,float_max_motor_torque);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateWheelJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateGearJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_CreateGearJoint00
static int tolua_lua_module_GamePhysicsWorld_CreateGearJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* ptr_sprite_a = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  GameSprite* ptr_sprite_b = ((GameSprite*)  tolua_tousertype(tolua_S,3,0));
  int joint_id_a = ((int)  tolua_tonumber(tolua_S,4,0));
  int joint_id_b = ((int)  tolua_tonumber(tolua_S,5,0));
  float float_ratio = ((float)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateGearJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->CreateGearJoint(ptr_sprite_a,ptr_sprite_b,joint_id_a,joint_id_b,float_ratio);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateGearJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DestoryJoint of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_DestoryJoint00
static int tolua_lua_module_GamePhysicsWorld_DestoryJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  int joint_id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DestoryJoint'", NULL);
#endif
  {
   int tolua_ret = (int)  self->DestoryJoint(joint_id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DestoryJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyImpulse of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_ApplyImpulse00
static int tolua_lua_module_GamePhysicsWorld_ApplyImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_impulse_x = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_impulse_y = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyImpulse'", NULL);
#endif
  {
   int tolua_ret = (int)  self->ApplyImpulse(sprite,float_impulse_x,float_impulse_y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyImpulseByAngular of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_ApplyImpulseByAngular00
static int tolua_lua_module_GamePhysicsWorld_ApplyImpulseByAngular00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"GameSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  GameSprite* sprite = ((GameSprite*)  tolua_tousertype(tolua_S,2,0));
  float float_angular = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_strength = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyImpulseByAngular'", NULL);
#endif
  {
   int tolua_ret = (int)  self->ApplyImpulseByAngular(sprite,float_angular,float_strength);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyImpulseByAngular'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_Update00
static int tolua_lua_module_GamePhysicsWorld_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float float_delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Update(float_delta);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Bomb of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_Bomb00
static int tolua_lua_module_GamePhysicsWorld_Bomb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float float_bomb_x = ((float)  tolua_tonumber(tolua_S,2,0));
  float float_bomb_y = ((float)  tolua_tonumber(tolua_S,3,0));
  float float_power_linear = ((float)  tolua_tonumber(tolua_S,4,0));
  float float_power_angular = ((float)  tolua_tonumber(tolua_S,5,0));
  float float_bomb_radius = ((float)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Bomb'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Bomb(float_bomb_x,float_bomb_y,float_power_linear,float_power_angular,float_bomb_radius);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Bomb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MouseDown of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_MouseDown00
static int tolua_lua_module_GamePhysicsWorld_MouseDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float float_x = ((float)  tolua_tonumber(tolua_S,2,0));
  float float_y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MouseDown'", NULL);
#endif
  {
   int tolua_ret = (int)  self->MouseDown(float_x,float_y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MouseDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MouseUp of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_MouseUp00
static int tolua_lua_module_GamePhysicsWorld_MouseUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float float_x = ((float)  tolua_tonumber(tolua_S,2,0));
  float float_y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MouseUp'", NULL);
#endif
  {
   self->MouseUp(float_x,float_y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MouseUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MouseMove of class  GamePhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_lua_module_GamePhysicsWorld_MouseMove00
static int tolua_lua_module_GamePhysicsWorld_MouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GamePhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GamePhysicsWorld* self = (GamePhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float float_x = ((float)  tolua_tonumber(tolua_S,2,0));
  float float_y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MouseMove'", NULL);
#endif
  {
   int tolua_ret = (int)  self->MouseMove(float_x,float_y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DebugPhysicsLayer */
#ifndef TOLUA_DISABLE_tolua_lua_module_DebugPhysicsLayer_new00
static int tolua_lua_module_DebugPhysicsLayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DebugPhysicsLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DebugPhysicsLayer* tolua_ret = (DebugPhysicsLayer*)  Mtolua_new((DebugPhysicsLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DebugPhysicsLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DebugPhysicsLayer */
#ifndef TOLUA_DISABLE_tolua_lua_module_DebugPhysicsLayer_new00_local
static int tolua_lua_module_DebugPhysicsLayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DebugPhysicsLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DebugPhysicsLayer* tolua_ret = (DebugPhysicsLayer*)  Mtolua_new((DebugPhysicsLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DebugPhysicsLayer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DebugPhysicsLayer */
#ifndef TOLUA_DISABLE_tolua_lua_module_DebugPhysicsLayer_delete00
static int tolua_lua_module_DebugPhysicsLayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugPhysicsLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugPhysicsLayer* self = (DebugPhysicsLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  DebugPhysicsLayer */
#ifndef TOLUA_DISABLE_tolua_lua_module_DebugPhysicsLayer_create00
static int tolua_lua_module_DebugPhysicsLayer_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DebugPhysicsLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DebugPhysicsLayer* tolua_ret = (DebugPhysicsLayer*)  DebugPhysicsLayer::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DebugPhysicsLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_create00
static int tolua_lua_module_GameSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameSprite* tolua_ret = (GameSprite*)  GameSprite::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_createWithTexture00
static int tolua_lua_module_GameSprite_createWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture2D* pTexture = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
  {
   GameSprite* tolua_ret = (GameSprite*)  GameSprite::createWithTexture(pTexture);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_createWithTexture01
static int tolua_lua_module_GameSprite_createWithTexture01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Rect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Texture2D* pTexture = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
  const Rect* rect = ((const Rect*)  tolua_tousertype(tolua_S,3,0));
  {
   GameSprite* tolua_ret = (GameSprite*)  GameSprite::createWithTexture(pTexture,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_lua_module_GameSprite_createWithTexture00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_createWithSpriteFrame00
static int tolua_lua_module_GameSprite_createWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFrame* pSpriteFrame = ((SpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  {
   GameSprite* tolua_ret = (GameSprite*)  GameSprite::createWithSpriteFrame(pSpriteFrame);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrameName of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_createWithSpriteFrameName00
static int tolua_lua_module_GameSprite_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszSpriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   GameSprite* tolua_ret = (GameSprite*)  GameSprite::createWithSpriteFrameName(pszSpriteFrameName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_create01
static int tolua_lua_module_GameSprite_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   GameSprite* tolua_ret = (GameSprite*)  GameSprite::create(pszFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_lua_module_GameSprite_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_create02
static int tolua_lua_module_GameSprite_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Rect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const Rect* rect = ((const Rect*)  tolua_tousertype(tolua_S,3,0));
  {
   GameSprite* tolua_ret = (GameSprite*)  GameSprite::create(pszFileName,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_lua_module_GameSprite_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_new00
static int tolua_lua_module_GameSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameSprite* tolua_ret = (GameSprite*)  Mtolua_new((GameSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_new00_local
static int tolua_lua_module_GameSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameSprite* tolua_ret = (GameSprite*)  Mtolua_new((GameSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_delete00
static int tolua_lua_module_GameSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameSprite* self = (GameSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBomb of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_IsBomb00
static int tolua_lua_module_GameSprite_IsBomb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameSprite* self = (GameSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBomb'", NULL);
#endif
  {
   int tolua_ret = (int)  self->IsBomb();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBomb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnBomb of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_OnBomb00
static int tolua_lua_module_GameSprite_OnBomb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameSprite* self = (GameSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnBomb'", NULL);
#endif
  {
   int tolua_ret = (int)  self->OnBomb();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnBomb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetB2Body of class  GameSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_GameSprite_GetB2Body00
static int tolua_lua_module_GameSprite_GetB2Body00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameSprite* self = (GameSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetB2Body'", NULL);
#endif
  {
   b2Body* tolua_ret = (b2Body*)  self->GetB2Body();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Body");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetB2Body'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_create00
static int tolua_lua_module_BombSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BombSprite* tolua_ret = (BombSprite*)  BombSprite::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_createWithTexture00
static int tolua_lua_module_BombSprite_createWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture2D* pTexture = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
  {
   BombSprite* tolua_ret = (BombSprite*)  BombSprite::createWithTexture(pTexture);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithTexture of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_createWithTexture01
static int tolua_lua_module_BombSprite_createWithTexture01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Rect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Texture2D* pTexture = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
  const Rect* rect = ((const Rect*)  tolua_tousertype(tolua_S,3,0));
  {
   BombSprite* tolua_ret = (BombSprite*)  BombSprite::createWithTexture(pTexture,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_lua_module_BombSprite_createWithTexture00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrame of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_createWithSpriteFrame00
static int tolua_lua_module_BombSprite_createWithSpriteFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SpriteFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFrame* pSpriteFrame = ((SpriteFrame*)  tolua_tousertype(tolua_S,2,0));
  {
   BombSprite* tolua_ret = (BombSprite*)  BombSprite::createWithSpriteFrame(pSpriteFrame);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrameName of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_createWithSpriteFrameName00
static int tolua_lua_module_BombSprite_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszSpriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   BombSprite* tolua_ret = (BombSprite*)  BombSprite::createWithSpriteFrameName(pszSpriteFrameName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_create01
static int tolua_lua_module_BombSprite_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   BombSprite* tolua_ret = (BombSprite*)  BombSprite::create(pszFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_lua_module_BombSprite_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_create02
static int tolua_lua_module_BombSprite_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Rect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const Rect* rect = ((const Rect*)  tolua_tousertype(tolua_S,3,0));
  {
   BombSprite* tolua_ret = (BombSprite*)  BombSprite::create(pszFileName,*rect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_lua_module_BombSprite_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_new00
static int tolua_lua_module_BombSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BombSprite* tolua_ret = (BombSprite*)  Mtolua_new((BombSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_new00_local
static int tolua_lua_module_BombSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BombSprite* tolua_ret = (BombSprite*)  Mtolua_new((BombSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BombSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_delete00
static int tolua_lua_module_BombSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BombSprite* self = (BombSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBomb of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_IsBomb00
static int tolua_lua_module_BombSprite_IsBomb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BombSprite* self = (BombSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBomb'", NULL);
#endif
  {
   int tolua_ret = (int)  self->IsBomb();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBomb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_Init00
static int tolua_lua_module_BombSprite_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BombSprite* self = (BombSprite*)  tolua_tousertype(tolua_S,1,0);
  float power_linear = ((float)  tolua_tonumber(tolua_S,2,0));
  float power_angular = ((float)  tolua_tonumber(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Init(power_linear,power_angular,radius);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearPower of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_GetLinearPower00
static int tolua_lua_module_BombSprite_GetLinearPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BombSprite* self = (BombSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearPower'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLinearPower();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularPower of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_GetAngularPower00
static int tolua_lua_module_BombSprite_GetAngularPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BombSprite* self = (BombSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularPower'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngularPower();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngularPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBombRadius of class  BombSprite */
#ifndef TOLUA_DISABLE_tolua_lua_module_BombSprite_GetBombRadius00
static int tolua_lua_module_BombSprite_GetBombRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BombSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BombSprite* self = (BombSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBombRadius'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetBombRadius();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBombRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngle of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetAngle00
static int tolua_lua_module_b2Body_GetAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngle'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularVelocity of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetAngularVelocity00
static int tolua_lua_module_b2Body_SetAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float omega = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularVelocity'", NULL);
#endif
  {
   self->SetAngularVelocity(omega);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularVelocity of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetAngularVelocity00
static int tolua_lua_module_b2Body_GetAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularVelocity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngularVelocity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyTorque of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_ApplyTorque00
static int tolua_lua_module_b2Body_ApplyTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float torque = ((float)  tolua_tonumber(tolua_S,2,0));
  bool wake = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyTorque'", NULL);
#endif
  {
   self->ApplyTorque(torque,wake);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyAngularImpulse of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_ApplyAngularImpulse00
static int tolua_lua_module_b2Body_ApplyAngularImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float impulse = ((float)  tolua_tonumber(tolua_S,2,0));
  bool wake = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyAngularImpulse'", NULL);
#endif
  {
   self->ApplyAngularImpulse(impulse,wake);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyAngularImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMass of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetMass00
static int tolua_lua_module_b2Body_GetMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMass'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMass();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInertia of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetInertia00
static int tolua_lua_module_b2Body_GetInertia00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInertia'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetInertia();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInertia'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetLinearDamping00
static int tolua_lua_module_b2Body_GetLinearDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearDamping'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLinearDamping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinearDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetLinearDamping00
static int tolua_lua_module_b2Body_SetLinearDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float linearDamping = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinearDamping'", NULL);
#endif
  {
   self->SetLinearDamping(linearDamping);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinearDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetAngularDamping00
static int tolua_lua_module_b2Body_GetAngularDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularDamping'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngularDamping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngularDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularDamping of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetAngularDamping00
static int tolua_lua_module_b2Body_SetAngularDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float angularDamping = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularDamping'", NULL);
#endif
  {
   self->SetAngularDamping(angularDamping);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGravityScale of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetGravityScale00
static int tolua_lua_module_b2Body_GetGravityScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGravityScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetGravityScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGravityScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGravityScale of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetGravityScale00
static int tolua_lua_module_b2Body_SetGravityScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGravityScale'", NULL);
#endif
  {
   self->SetGravityScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGravityScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBullet of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetBullet00
static int tolua_lua_module_b2Body_SetBullet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBullet'", NULL);
#endif
  {
   self->SetBullet(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBullet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBullet of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_IsBullet00
static int tolua_lua_module_b2Body_IsBullet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBullet'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBullet();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBullet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSleepingAllowed of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetSleepingAllowed00
static int tolua_lua_module_b2Body_SetSleepingAllowed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSleepingAllowed'", NULL);
#endif
  {
   self->SetSleepingAllowed(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSleepingAllowed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSleepingAllowed of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_IsSleepingAllowed00
static int tolua_lua_module_b2Body_IsSleepingAllowed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSleepingAllowed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSleepingAllowed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSleepingAllowed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAwake of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetAwake00
static int tolua_lua_module_b2Body_SetAwake00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAwake'", NULL);
#endif
  {
   self->SetAwake(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAwake'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAwake of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_IsAwake00
static int tolua_lua_module_b2Body_IsAwake00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAwake'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAwake();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAwake'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActive of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetActive00
static int tolua_lua_module_b2Body_SetActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActive'", NULL);
#endif
  {
   self->SetActive(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsActive of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_IsActive00
static int tolua_lua_module_b2Body_IsActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsActive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsActive();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFixedRotation of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_SetFixedRotation00
static int tolua_lua_module_b2Body_SetFixedRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFixedRotation'", NULL);
#endif
  {
   self->SetFixedRotation(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFixedRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFixedRotation of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_IsFixedRotation00
static int tolua_lua_module_b2Body_IsFixedRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFixedRotation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFixedRotation();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFixedRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNext of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetNext00
static int tolua_lua_module_b2Body_GetNext00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNext'", NULL);
#endif
  {
   b2Body* tolua_ret = (b2Body*)  self->GetNext();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Body");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNext'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNext of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_GetNext01
static int tolua_lua_module_b2Body_GetNext01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const b2Body* self = (const b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNext'", NULL);
#endif
  {
   const b2Body* tolua_ret = (const b2Body*)  self->GetNext();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const b2Body");
  }
 }
 return 1;
tolua_lerror:
 return tolua_lua_module_b2Body_GetNext00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Dump of class  b2Body */
#ifndef TOLUA_DISABLE_tolua_lua_module_b2Body_Dump00
static int tolua_lua_module_b2Body_Dump00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Body",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Body* self = (b2Body*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dump'", NULL);
#endif
  {
   self->Dump();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dump'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_lua_module_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GamePhysicsWorld","GamePhysicsWorld","",tolua_collect_GamePhysicsWorld);
  #else
  tolua_cclass(tolua_S,"GamePhysicsWorld","GamePhysicsWorld","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GamePhysicsWorld");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"MATERIAL","GamePhysicsWorld::MATERIAL","",tolua_collect_GamePhysicsWorld__MATERIAL);
   #else
   tolua_cclass(tolua_S,"MATERIAL","GamePhysicsWorld::MATERIAL","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"MATERIAL");
    tolua_function(tolua_S,"new",tolua_lua_module_GamePhysicsWorld_MATERIAL_new00);
    tolua_function(tolua_S,"new_local",tolua_lua_module_GamePhysicsWorld_MATERIAL_new00_local);
    tolua_function(tolua_S,".call",tolua_lua_module_GamePhysicsWorld_MATERIAL_new00_local);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"new",tolua_lua_module_GamePhysicsWorld_new00);
   tolua_function(tolua_S,"new_local",tolua_lua_module_GamePhysicsWorld_new00_local);
   tolua_function(tolua_S,".call",tolua_lua_module_GamePhysicsWorld_new00_local);
   tolua_function(tolua_S,"delete",tolua_lua_module_GamePhysicsWorld_delete00);
   tolua_function(tolua_S,"GetInstance",tolua_lua_module_GamePhysicsWorld_GetInstance00);
   tolua_function(tolua_S,"Init",tolua_lua_module_GamePhysicsWorld_Init00);
   tolua_function(tolua_S,"Uninit",tolua_lua_module_GamePhysicsWorld_Uninit00);
   tolua_function(tolua_S,"CreateRectEdge",tolua_lua_module_GamePhysicsWorld_CreateRectEdge00);
   tolua_function(tolua_S,"SetBoxBody",tolua_lua_module_GamePhysicsWorld_SetBoxBody00);
   tolua_function(tolua_S,"SetCircleBody",tolua_lua_module_GamePhysicsWorld_SetCircleBody00);
   tolua_function(tolua_S,"SetBodyAngularVelocity",tolua_lua_module_GamePhysicsWorld_SetBodyAngularVelocity00);
   tolua_function(tolua_S,"LoadPolygonBodyFromFile",tolua_lua_module_GamePhysicsWorld_LoadPolygonBodyFromFile00);
   tolua_function(tolua_S,"SetPolygonBodyWithShapeName",tolua_lua_module_GamePhysicsWorld_SetPolygonBodyWithShapeName00);
   tolua_function(tolua_S,"CreateDistanceJoint",tolua_lua_module_GamePhysicsWorld_CreateDistanceJoint00);
   tolua_function(tolua_S,"CreatePrismaticJoint",tolua_lua_module_GamePhysicsWorld_CreatePrismaticJoint00);
   tolua_function(tolua_S,"CreateFixedPrismaticJoint",tolua_lua_module_GamePhysicsWorld_CreateFixedPrismaticJoint00);
   tolua_function(tolua_S,"CreateRevoluteJoint",tolua_lua_module_GamePhysicsWorld_CreateRevoluteJoint00);
   tolua_function(tolua_S,"CreateFixedRevoluteJoint",tolua_lua_module_GamePhysicsWorld_CreateFixedRevoluteJoint00);
   tolua_function(tolua_S,"CreateWheelJoint",tolua_lua_module_GamePhysicsWorld_CreateWheelJoint00);
   tolua_function(tolua_S,"CreateGearJoint",tolua_lua_module_GamePhysicsWorld_CreateGearJoint00);
   tolua_function(tolua_S,"DestoryJoint",tolua_lua_module_GamePhysicsWorld_DestoryJoint00);
   tolua_function(tolua_S,"ApplyImpulse",tolua_lua_module_GamePhysicsWorld_ApplyImpulse00);
   tolua_function(tolua_S,"ApplyImpulseByAngular",tolua_lua_module_GamePhysicsWorld_ApplyImpulseByAngular00);
   tolua_function(tolua_S,"Update",tolua_lua_module_GamePhysicsWorld_Update00);
   tolua_function(tolua_S,"Bomb",tolua_lua_module_GamePhysicsWorld_Bomb00);
   tolua_function(tolua_S,"MouseDown",tolua_lua_module_GamePhysicsWorld_MouseDown00);
   tolua_function(tolua_S,"MouseUp",tolua_lua_module_GamePhysicsWorld_MouseUp00);
   tolua_function(tolua_S,"MouseMove",tolua_lua_module_GamePhysicsWorld_MouseMove00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DebugPhysicsLayer","DebugPhysicsLayer","Layer",tolua_collect_DebugPhysicsLayer);
  #else
  tolua_cclass(tolua_S,"DebugPhysicsLayer","DebugPhysicsLayer","Layer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DebugPhysicsLayer");
   tolua_function(tolua_S,"new",tolua_lua_module_DebugPhysicsLayer_new00);
   tolua_function(tolua_S,"new_local",tolua_lua_module_DebugPhysicsLayer_new00_local);
   tolua_function(tolua_S,".call",tolua_lua_module_DebugPhysicsLayer_new00_local);
   tolua_function(tolua_S,"delete",tolua_lua_module_DebugPhysicsLayer_delete00);
   tolua_function(tolua_S,"create",tolua_lua_module_DebugPhysicsLayer_create00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GameSprite","GameSprite","Sprite",tolua_collect_GameSprite);
  #else
  tolua_cclass(tolua_S,"GameSprite","GameSprite","Sprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GameSprite");
   tolua_function(tolua_S,"create",tolua_lua_module_GameSprite_create00);
   tolua_function(tolua_S,"createWithTexture",tolua_lua_module_GameSprite_createWithTexture00);
   tolua_function(tolua_S,"createWithTexture",tolua_lua_module_GameSprite_createWithTexture01);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_lua_module_GameSprite_createWithSpriteFrame00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_lua_module_GameSprite_createWithSpriteFrameName00);
   tolua_function(tolua_S,"create",tolua_lua_module_GameSprite_create01);
   tolua_function(tolua_S,"create",tolua_lua_module_GameSprite_create02);
   tolua_function(tolua_S,"new",tolua_lua_module_GameSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_lua_module_GameSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_lua_module_GameSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_lua_module_GameSprite_delete00);
   tolua_function(tolua_S,"IsBomb",tolua_lua_module_GameSprite_IsBomb00);
   tolua_function(tolua_S,"OnBomb",tolua_lua_module_GameSprite_OnBomb00);
   tolua_function(tolua_S,"GetB2Body",tolua_lua_module_GameSprite_GetB2Body00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"BombSprite","BombSprite","GameSprite",tolua_collect_BombSprite);
  #else
  tolua_cclass(tolua_S,"BombSprite","BombSprite","GameSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"BombSprite");
   tolua_function(tolua_S,"create",tolua_lua_module_BombSprite_create00);
   tolua_function(tolua_S,"createWithTexture",tolua_lua_module_BombSprite_createWithTexture00);
   tolua_function(tolua_S,"createWithTexture",tolua_lua_module_BombSprite_createWithTexture01);
   tolua_function(tolua_S,"createWithSpriteFrame",tolua_lua_module_BombSprite_createWithSpriteFrame00);
   tolua_function(tolua_S,"createWithSpriteFrameName",tolua_lua_module_BombSprite_createWithSpriteFrameName00);
   tolua_function(tolua_S,"create",tolua_lua_module_BombSprite_create01);
   tolua_function(tolua_S,"create",tolua_lua_module_BombSprite_create02);
   tolua_function(tolua_S,"new",tolua_lua_module_BombSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_lua_module_BombSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_lua_module_BombSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_lua_module_BombSprite_delete00);
   tolua_function(tolua_S,"IsBomb",tolua_lua_module_BombSprite_IsBomb00);
   tolua_function(tolua_S,"Init",tolua_lua_module_BombSprite_Init00);
   tolua_function(tolua_S,"GetLinearPower",tolua_lua_module_BombSprite_GetLinearPower00);
   tolua_function(tolua_S,"GetAngularPower",tolua_lua_module_BombSprite_GetAngularPower00);
   tolua_function(tolua_S,"GetBombRadius",tolua_lua_module_BombSprite_GetBombRadius00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"b2Body","b2Body","",NULL);
  tolua_beginmodule(tolua_S,"b2Body");
   tolua_function(tolua_S,"GetAngle",tolua_lua_module_b2Body_GetAngle00);
   tolua_function(tolua_S,"SetAngularVelocity",tolua_lua_module_b2Body_SetAngularVelocity00);
   tolua_function(tolua_S,"GetAngularVelocity",tolua_lua_module_b2Body_GetAngularVelocity00);
   tolua_function(tolua_S,"ApplyTorque",tolua_lua_module_b2Body_ApplyTorque00);
   tolua_function(tolua_S,"ApplyAngularImpulse",tolua_lua_module_b2Body_ApplyAngularImpulse00);
   tolua_function(tolua_S,"GetMass",tolua_lua_module_b2Body_GetMass00);
   tolua_function(tolua_S,"GetInertia",tolua_lua_module_b2Body_GetInertia00);
   tolua_function(tolua_S,"GetLinearDamping",tolua_lua_module_b2Body_GetLinearDamping00);
   tolua_function(tolua_S,"SetLinearDamping",tolua_lua_module_b2Body_SetLinearDamping00);
   tolua_function(tolua_S,"GetAngularDamping",tolua_lua_module_b2Body_GetAngularDamping00);
   tolua_function(tolua_S,"SetAngularDamping",tolua_lua_module_b2Body_SetAngularDamping00);
   tolua_function(tolua_S,"GetGravityScale",tolua_lua_module_b2Body_GetGravityScale00);
   tolua_function(tolua_S,"SetGravityScale",tolua_lua_module_b2Body_SetGravityScale00);
   tolua_function(tolua_S,"SetBullet",tolua_lua_module_b2Body_SetBullet00);
   tolua_function(tolua_S,"IsBullet",tolua_lua_module_b2Body_IsBullet00);
   tolua_function(tolua_S,"SetSleepingAllowed",tolua_lua_module_b2Body_SetSleepingAllowed00);
   tolua_function(tolua_S,"IsSleepingAllowed",tolua_lua_module_b2Body_IsSleepingAllowed00);
   tolua_function(tolua_S,"SetAwake",tolua_lua_module_b2Body_SetAwake00);
   tolua_function(tolua_S,"IsAwake",tolua_lua_module_b2Body_IsAwake00);
   tolua_function(tolua_S,"SetActive",tolua_lua_module_b2Body_SetActive00);
   tolua_function(tolua_S,"IsActive",tolua_lua_module_b2Body_IsActive00);
   tolua_function(tolua_S,"SetFixedRotation",tolua_lua_module_b2Body_SetFixedRotation00);
   tolua_function(tolua_S,"IsFixedRotation",tolua_lua_module_b2Body_IsFixedRotation00);
   tolua_function(tolua_S,"GetNext",tolua_lua_module_b2Body_GetNext00);
   tolua_function(tolua_S,"GetNext",tolua_lua_module_b2Body_GetNext01);
   tolua_function(tolua_S,"Dump",tolua_lua_module_b2Body_Dump00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_lua_module (lua_State* tolua_S) {
 return tolua_lua_module_open(tolua_S);
};
#endif

