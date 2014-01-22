--=======================================================================
-- File Name    : body.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-01-22
-- Description  :
-- Modify       :
--=======================================================================

if not Body then
	Body = {}
end

Body.tb_cfg = {
	["tank_1"] = {
		image = "image/tank_1.png",
	}
}

local PhysicsWorld = GamePhysicsWorld:GetInstance()


function Body:GetCfg(body_type)
	return self.tb_cfg[body_type]
end