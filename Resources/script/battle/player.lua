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
	self.str_move_direction = nil
	self.str_adjust_direction = nil
	self.num_attack_power = nil	

	local sprites = Construct:BuildTank(cc_layer, x, y, tb_construct)
	local character = CharacterMgr:Create(hp, x, y, sprites)
	self.id = character:GetId()

	return 1
end

function Player:Uninit()
	CharacterMgr:Destory(self.id)
	self.is_run = nil
	self.hp = nil
	self.x = nil
	self.y = nil
	self.id = nil
	self.str_move_direction = nil
	self.str_adjust_direction = nil
	self.num_attack_power = nil	
end

function Player:GetCharacter()
	local tb = CharacterMgr:GetById(self.id)
	if not tb then
		assert(false)
		return
	end
	return tb
end

function Player:GetBody()
	local tb = self:GetCharacter()
	if not tb then
		return
	end
	return tb:GetBody()
end

function Player:GetWeapon()
	local tb = self:GetCharacter()
	if not tb then
		return
	end
	return tb:GetWeapon()
end

function Player:GetMotor()
	local tb = self:GetCharacter()
	if not tb then
		return
	end
	return tb:GetMotor()
end

function Player:GetPosition()
	return self:GetBody():getPosition()
end

function Player:GetWeaponType()
	local tb = self:GetCharacter()
	if not tb then
		return
	end
	return tb:GetWeaponType()
end

function Player:GetWeaponAngle()
	local rotation_body = self:GetBody():getRotation()
	local rotation = math.floor((rotation_body + self:GetWeapon():getRotation()))
	return -rotation % 360, rotation_body
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
			local tb_motor = self:GetMotor()
			local torque = Motor:Move(tb_motor, self.str_move_direction)
			Event:FireEvent("BodyMove", torque)
		end
	end

	if frame % 2 == 0 then
		if self.str_adjust_direction then
			local weapon = self:GetWeapon()
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
	local x, y = self:GetBody():getPosition()
	if math.floor(x) ~= self.x or math.floor(y) ~= self.y then
		self.x = math.floor(x)
		self.y = math.floor(y)
		Event:FireEvent("UpdatePlayerPosition", self.x, self.y)
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