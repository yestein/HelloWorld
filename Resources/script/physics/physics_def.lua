--=======================================================================
-- File Name    : physics_def.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  :
-- Modify       :
--=======================================================================
if not Physics then
	Physics = {}
end

Physics.tb_plist = {
	"physics/map.plist",
}

-- 默认物理世界重力
Physics.DEFAULT_GRAVITY = {0, -20}

local tb = {
	body = {"tank_2.png", 0, 0},
	frontwheel = {"tank_wheel.png", 30, -10},
	backwheel = {"tank_wheel.png"},
}

Physics.GROUP_GROUND = 0x0001
Physics.GROUP_TANK   = 0x0002
Physics.GROUP_MOTOR = 0x8000

Physics.MASK_GROUND = 0x0001
Physics.MASK_MOTOR = 0x8000
