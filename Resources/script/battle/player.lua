--=======================================================================
-- File Name    : player.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-01-22
-- Description  :
-- Modify       :
--=======================================================================

if not Player then
	Player = {}
end

function Player:Init(cc_layer, hp, x, y, tb_construct)
	self.is_run = 1
	self.hp = hp
	self.x = x
	self.y = y
	self.tb_sprite = Construct:BuildTank(cc_layer, x, y, tb_construct)
	self.body = self.tb_sprite.body
	self.weapon = self.tb_sprite.weapon
	self.tb_motor = self.tb_sprite.tb_motor
	self.weapon_type = tb_construct.weapon_type
	self.motor_type = tb_construct.weapon_type

	self.str_move_direction = nil
	self.str_adjust_direction = nil
	self.num_attack_power = nil

	Event:FireEvent("PlayerInit", hp, x, y, tb_construct)
end

function Player:Uninit()
	self.is_run = nil
	self.hp = nil
	self.x = nil
	self.y = nil
	self.tb_sprite = nil
	self.body = nil
	self.weapon = nil
	self.weapon_type = nil
	self.motor_type = nil

	self.str_move_direction = nil
	self.str_adjust_direction = nil
	self.num_attack_power = nil
	Event:FireEvent("PlayerUnInit")
end

function Player:SetHP(hp)
	self.hp = hp
end

function Player:GetHP()
	return self.hp
end

function Player:GetBody()
	return self.body
end

function Player:GetMotor()
	return self.tb_motor
end

function Player:GetPosition()
	return self.body:getPosition()
end

function Player:GetWeaponAngle()
	local rotation_body = self.body:getRotation()
	local rotation = math.floor((rotation_body + self.weapon:getRotation()))
	return -rotation % 360, rotation_body
end

function Player:GetWeaponType()
	return self.weapon_type
end

function Player:OnActive(frame)
	if self.is_run ~= 1 then
		return
	end
	if frame % GameMgr.LOGIC_FPS == 0 then
		self:UpdatePosition()
	end

	if frame % 3 == 0 then
		if self.str_move_direction then
			local tb_motor = self.tb_motor
			local torque = Motor:Move(tb_motor, self.str_move_direction)
			Event:FireEvent("BodyMove", torque)
		end
	end

	if frame % 2 == 0 then
		if self.str_adjust_direction then
			local weapon = self.weapon
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
			weapon:setRotation(rotation_new)
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

function Player:UpdatePosition()
	local x, y = self.body:getPosition()
	if x ~= self.x or y ~= self.y then
		self.x = x
		self.y = y
		Event:FireEvent("UpdatePlayerPosition", x, y)
	end
end

function Player:GetBulletLuanchPosition()
	local x, y = self:GetPosition()
	return x + 50 , y + 70
end

function Player:StartMove(str_direction)
	self.str_move_direction = str_direction
end

function Player:StopMove()
	self.str_move_direction = nil
end

function Player:StartAdjust(str_direction)
	self.str_adjust_direction = str_direction
end

function Player:StopAdjust()
	self.str_adjust_direction = nil
end

function Player:ReadyToAttack()
	self.num_attack_power = 0
	self.num_power_delta = 1
end

function Player:Attack(power)
	local bullet_luanch_x, bullet_luanch_y = self:GetBulletLuanchPosition()

	local tb_bullet_property = {
		bullet_type = Weapon:GetBulletType(self:GetWeaponType()),
		x = bullet_luanch_x,
		y = bullet_luanch_y,
		impulse = BattleLogic:GetBulletPower(self.num_attack_power)
	}
	Event:FireEvent("Attack", tb_bullet_property)
	self.num_attack_power = nil
end