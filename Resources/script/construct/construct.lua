--=======================================================================
-- File Name    : construct.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-01-22
-- Description  :
-- Modify       :
--=======================================================================

if not Construct then
	Construct = {}
end

function Construct:BuildTank(cc_layer, tank_x, tank_y, tb_param)
	local tb_ret = {}
	local str_body = tb_param.str_body
	if not str_body then
		assert(false)
		return
	end
	
    local motor_type = tb_param.motor_type
    if not motor_type then
    	assert(false)
    	return
    end

	local physics_sprite_body, width_body, height_body = Physics:CreatePolygonSprite(str_body, tank_x, tank_y)
    cc_layer:addChild(physics_sprite_body)
	tb_ret.body = physics_sprite_body    

	local weapon_type = tb_param.weapon_type
    if weapon_type then
    	tb_ret.weapon = Weapon:Create(weapon_type, physics_sprite_body, 15, 40)
    end	

	local tbParam = {
		width = 70,
		-- visible = 1,
		image_wheel = "image/circle.png",
		image_crawler = "image/rect2.png",
	}
	local tb_crawler_belt = WheelCrawler:Create(cc_layer, tank_x, tank_y, physics_sprite_body, tbParam)
	if not tb_crawler_belt then
		assert(false)
		return
	end

	local tb_tobe_gear = {
		{
			sprite = tb_crawler_belt.wheel_back, 
			joint = tb_crawler_belt.tb_joint.wheel_back,
		},
		{
			sprite = tb_crawler_belt.wheel_middle, 
			joint = tb_crawler_belt.tb_joint.wheel_middle,
		},
		{
			sprite = tb_crawler_belt.wheel_front, 
			joint = tb_crawler_belt.tb_joint.wheel_front,
		},
	}

	tb_ret.tb_motor = Motor:Create(motor_type, cc_layer, tank_x, tank_y, physics_sprite_body, tb_tobe_gear)

    return tb_ret
end


