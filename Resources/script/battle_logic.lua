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

BattleLogic.LOGIC_FPS = 25
BattleLogic.TIME_PER_FRAME = 1 / BattleLogic.LOGIC_FPS

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function BattleLogic:Init(tb_player, tb_enemy)
	self.accumulate = 0
	self.num_frame = 0
	self.tb_player = tb_player
	self.tb_enemy = tb_enemy
	self.str_move_direction = nil
	self.str_adjust_direction = nil
	self.num_attack_power = nil
end

function BattleLogic:Uninit()
	Event:UnRegistEvent("UIButton", self.nRegButton)
end

function BattleLogic:StartMove(str_direction)
	self.str_move_direction = str_direction
end

function BattleLogic:StopMove()
	self.str_move_direction = nil
end

function BattleLogic:StartAdjust(str_direction)
	self.str_adjust_direction = str_direction
end

function BattleLogic:StopAdjust()
	self.str_adjust_direction = nil
end

function BattleLogic:ReadyToAttack()
	self.num_attack_power = 0
	self.num_power_delta = 1
end

function BattleLogic:Attack()
	Event:FireEvent("Attack", self.num_attack_power)
	self.num_attack_power = nil
end

--逻辑帧
function BattleLogic:OnActive()
	self.num_frame = self.num_frame + 1
	if self.num_frame % 3 == 0 then
		if self.str_move_direction then
			local body = self.tb_player.body
			local impluse = 2500
			if self.str_move_direction == "left" then
				impluse = -2500
			end
			PhysicsWorld:ApplyImpulse(body, impluse, 0)
			print(1)
			Event:FireEvent("BodyMove", impluse)
		end
	
		if self.str_adjust_direction then
			local weapon = self.tb_player.weapon
			local rotation = weapon:getRotation()
			local delta_roataion = 1
			if self.str_adjust_direction == "up" then
				delta_roataion = -1
			end
			local rotation_new = rotation + delta_roataion
			if rotation_new < -180 then
				rotation_new = -180
			elseif rotation_new > 0 then
				rotation_new = 0
			end
			self.tb_player.weapon:setRotation(rotation_new)
			Event:FireEvent("WeaponRotate", rotation_new)
		end
	end

	if self.num_attack_power then
		self.num_attack_power = self.num_attack_power + self.num_power_delta
		if self.num_attack_power > 100 then
			self.num_attack_power = 99
			self.num_power_delta = -1
		elseif self.num_attack_power < 0 then
			self.num_attack_power = 1
			self.num_power_delta = 1
		end
		Event:FireEvent("PowerChanged", self.num_attack_power)
	end
end

function BattleLogic:OnLoop(delta)
	self.accumulate = self.accumulate + delta
	if self.accumulate > self.TIME_PER_FRAME then
		self:OnActive()
		self.accumulate = self.accumulate - self.TIME_PER_FRAME
	end
end