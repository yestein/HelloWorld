--=======================================================================
-- File Name    : enemy.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  :
-- Modify       :
--=======================================================================
if not Enemy then
	Enemy = {}
end

function Enemy:Init(cc_layer, hp, x, y, tb_construct)
	self.hp = hp
	self.x = x
	self.y = y
	self.tb_sprite = Construct:BuildTank(cc_layer, x, y, tb_construct)
	self.body = self.tb_sprite.body
	self.weapon = self.tb_sprite.weapon
	self.tb_motor = self.tb_sprite.tb_motor
	self.weapon_type = tb_construct.weapon_type
	self.motor_type = tb_construct.weapon_type


	Event:FireEvent("CharacterAdd", self.body, hp, x, y, tb_construct)
end

function Enemy:Uninit()
	self.hp = nil
	self.x = nil
	self.y = nil
	self.tb_sprite = nil
	self.body = nil
	self.weapon = nil
	self.weapon_type = nil
	self.motor_type = nil

	Event:FireEvent("EnemyUnInit")
end

function Enemy:SetHP(hp)
	self.hp = hp
end

function Enemy:GetHP()
	return self.hp
end

function Enemy:GetBody()
	return self.body
end

function Enemy:GetMotor()
	return self.tb_motor
end

function Enemy:GetPosition()
	return self.body:getPosition()
end

function Enemy:GetWeaponAngle()
	local rotation_body = self.body:getRotation()
	local rotation = math.floor((rotation_body + self.weapon:getRotation()))
	return -rotation % 360, rotation_body
end

function Enemy:GetWeaponType()
	return self.weapon_type
end
