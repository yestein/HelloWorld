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

function BattleLogic:Init(tb_player, tb_enemy)
	self.is_run = 1
	self.tb_player = tb_player
	self.tb_enemy = tb_enemy
	self.str_move_direction = nil
	self.str_adjust_direction = nil
	self.num_attack_power = nil
end

function BattleLogic:Uninit()
	self.is_run = 0
end

--逻辑帧
function BattleLogic:OnActive(num_frame)
	if self.is_run ~= 1 then
		return
	end
	if num_frame % 3 == 0 then
		if self.str_move_direction then
			local motor = self.tb_player.motor
			local torque = Def.MOTOR_POWER
			if self.str_move_direction == "right" then
				torque = -torque
			end
			PhysicsWorld:ApplyTorque(motor, torque)
			Event:FireEvent("BodyMove", torque)
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

function BattleLogic:GetBulletPower(power)
	return 25 * Def.BULLET_DENSITY + power * 2.5 * Def.BULLET_DENSITY
end

