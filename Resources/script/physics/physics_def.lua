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

Physics.GROUP_GROUND = 0x0001
Physics.GROUP_TANK   = 0x0002
Physics.GROUP_MOTOR = 0x8000

Physics.MASK_GROUND = 0x0001
Physics.MASK_MOTOR = 0x8000
