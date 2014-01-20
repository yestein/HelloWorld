--=======================================================================
-- File Name    : physics_mgr.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-18
-- Description  :
-- Modify       :
--=======================================================================
if not Physics then
	Physics = {}
end

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Physics:Init()
	if PhysicsWorld:Init(unpack(self.DEFAULT_GRAVITY)) ~= 1 then
		return 0
	end
	if self:LoadPList() ~= 1 then
		return 0
	end
	return 1
end

function Physics:OnLoop(delta)
	PhysicsWorld:Update(delta)
end

function Physics:SetGravity(gravity_x, gravity_y)
	PhysicsWorld:SetGravity(gravity_x, gravity_y)
end