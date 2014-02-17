--=======================================================================
-- File Name    : battle_logic.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-14
-- Description  :
-- Modify       :
--=======================================================================

if not BattleLogic then
	BattleLogic = {}
end

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function BattleLogic:Init()
	self.is_run = 1
	CharacterMgr:Init()
end

function BattleLogic:Uninit()
	self.is_run = 0
	CharacterMgr:Uninit()
end

--逻辑帧
function BattleLogic:OnActive(num_frame)
	if self.is_run ~= 1 then
		return
	end
	
end

function BattleLogic:GetBulletPower(power)
	return 25 * Def.BULLET_DENSITY + power * 2.5 * Def.BULLET_DENSITY
end

