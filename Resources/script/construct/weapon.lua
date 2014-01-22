--=======================================================================
-- File Name    : weapon.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-01-22
-- Description  :
-- Modify       :
--=======================================================================

if not Weapon then
	Weapon = {}
end

Weapon.tb_cfg = {
	["test1"] = {
		image = "image/tank_weapon.png",
		power_luanch = 100,
		power_back = 30,
		angel_max = 180,
		angel_min = 0,
		anchor_x = 0.1,
		anchor_y = 0.5,
		raw_rotation = -45,
		bullet_type = 1,
	},
	["test2"] = {
		image = "image/rect.png",
		power_luanch = 100,
		power_back = 30,
		angel_max = 180,
		angel_min = 0,
		anchor_x = 0.1,
		anchor_y = 0.5,
		raw_rotation = -45,
		bullet_type = 2,
	},
}

function Weapon:GetCfg(weapon_type)
	return self.tb_cfg[weapon_type]
end

function Weapon:GetBulletType(weapon_type)
	local cfg = self:GetCfg(weapon_type)
	assert(cfg)
	return cfg.bullet_type
end

function Weapon:Create(weapon_type, sprite_body, x, y)
	local weapon_cfg = self:GetCfg(weapon_type)
	local cc_sprite_weapon = GameSprite:create(weapon_cfg.image)
	local width_body = sprite_body:getContentSize().width
    local width_weapon = cc_sprite_weapon:getContentSize().width * 0.5
    local height_weapon = cc_sprite_weapon:getContentSize().height * 0.5
    cc_sprite_weapon:setAnchorPoint(cc.p(weapon_cfg.anchor_x, weapon_cfg.anchor_y))
    cc_sprite_weapon:setPosition(x, y)

    cc_sprite_weapon:setRotation(weapon_cfg.raw_rotation)
    sprite_body:addChild(cc_sprite_weapon)
	return cc_sprite_weapon
end