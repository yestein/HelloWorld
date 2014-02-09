--=======================================================================
-- File Name    : bullet_cfg.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-01-22
-- Description  :
-- Modify       :
--=======================================================================

if not Bullet then
	Bullet = {}
end


Bullet.tb_cfg = {
	[1] = {
		image = "image/bullet.png",
		density = 0.01,
		power_linear = 100000,
		power_angular = 150000,
		destroy_range = 30,
		bomb_range = 50,
		damage = 100,
	},
	[2] = {
		image = "image/icon.png",
		scale = 0.5,
		density = 0.01,
		power_linear = 100000,
		power_angular = 150000,
		destroy_range = 30,
		destroy_num = 3,
		bomb_range = 30,
		damage = 200,
	},
}

function Bullet:GetCfg(bullet_type)
	return self.tb_cfg[bullet_type]
end

function Bullet:GetDestoryRange(bullet_type)
	local cfg = self:GetCfg(bullet_type)
	if not cfg then
		return 0
	end

	return cfg.destroy_range
end

function Bullet:GetDestoryNum(bullet_type)
	local cfg = self:GetCfg(bullet_type)
	if not cfg then
		return 0
	end

	return cfg.destroy_num or 1
end

function Bullet:GetDamage(bullet_type)
	local cfg = self:GetCfg(bullet_type)
	if not cfg then
		return 0
	end

	return cfg.damage
end
