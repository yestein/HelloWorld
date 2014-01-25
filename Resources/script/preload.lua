--===================================================
-- File Name    : preload.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2013-08-07 13:07:04
-- Description  :
-- Modify       :
--===================================================

require("script/define.lua")
require("script/misc_math.lua")
require("script/lib.lua")
require("script/event.lua")
if _DEBUG then
require("script/dbg.lua")
end
require("script/performance.lua")
require("script/game_mgr.lua")
require("script/menu.lua")
require("script/ui.lua")

require("script/construct/construct.lua")
require("script/construct/body.lua")
require("script/construct/motor.lua")
require("script/construct/weapon.lua")

require("script/construct/movement/wheel_crawler.lua")
require("script/construct/movement/spider.lua")

require("script/battle/player.lua")
require("script/battle/enemy.lua")
require("script/battle/battle_logic.lua")
require("script/battle/bullet_cfg.lua")

require("script/scene/scene_mgr.lua")
require("script/scene/scene_base.lua")
require("script/scene/physics_scene.lua")
require("script/scene/main_scene.lua")
require("script/scene/demo_scene.lua")
require("script/scene/polygon_break_scene.lua")
require("script/scene/blank_scene.lua")
require("script/scene/construct_scene.lua")

require("script/physics/physics_def.lua")
require("script/physics/physics_lib.lua")
require("script/physics/physics_io.lua")
require("script/physics/physics_mgr.lua")