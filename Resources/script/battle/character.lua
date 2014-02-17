--=======================================================================
-- File Name    : 
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  :
-- Modify       :
--=======================================================================

if not Character then
	Character = {}
end

function Character:Init(hp, x, y, sprites)
	self.cur_hp      = hp
	self.max_hp      = hp
	self.body        = sprites.body
	self.body:setTag(self:GetId())
	self.weapon_type = sprites.weapon_type
	self.weapon      = sprites.weapon
	
	self.motor_type  = sprites.motor_type
	self.motor       = sprites.motor
end

function Character:Uninit()
	self.id          = nil
	self.cur_hp      = nil
	self.max_hp      = nil
	self.body        = nil
	self.weapon_type = nil
	self.weapon      = nil
	
	self.motor_type  = nil
	self.motor       = nil

	self.progressHP  = nil
end

function Character:GetId()
	return self.id
end

function Character:SetCurHP(value)
	self.cur_hp = value
end

function Character:SetProgressHP(progressHP)
	self.progressHP = progressHP
end

function Character:GetProgressHP()
	return self.progressHP
end

function Character:GetCurHP()
	return self.cur_hp
end

function Character:GetMaxHP()
	return self.max_hp
end

function Character:ChangeHP(change_value)
	local old_value = self.cur_hp
	local new_value = old_value + change_value
	if new_value > self.max_hp then
		new_value = self.max_hp
	elseif new_value < 0 then
		new_value = 0
	end
	self.cur_hp = new_value                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
	Event:FireEvent("CharacterHPChanged", self:GetId(), old_value, new_value, self.max_hp)
end

function Character:GetBody()
	return self.body
end

function Character:GetWeapon()
	return self.weapon
end

function Character:GetWeaponType()
	return self.weapon_type
end

function Character:GetMotor()
	return self.motor
end

function Character:GetMotorType()
	return self.motor_type
end