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

function Construct:Create(cc_layer, offset_x, offset_y, tb)
	local function pos(x, y)
		return offset_x + x, offset_y + y
	end
	local tb_body_cfg = tb.tb_body
	local tb_body = {}
	if tb_body_cfg then
		for body_name, cfg in pairs(tb_body_cfg) do
			local body_type = cfg[1]
			local image_path = cfg[2]		
			local x, y = pos(cfg[3], cfg[4])
			local tb_property = cfg[5]

			tb_body[body_name] = Physics:CreateBody(body_type, image_path, x, y, tb_property)
			local z_level  = cfg[6]
			if z_level then
				cc_layer:addChild(tb_body[body_name], z_level)
			else
				cc_layer:addChild(tb_body[body_name])
			end
			assert(tb_body[body_name])
		end
	end

	local tb_hide = tb.tb_hide
	if tb_hide then
		for _, body_name in ipairs(tb_hide) do
			tb_body[body_name]:setVisible(false)
		end
	end

	local tb_joint_cfg = tb.tb_joint
	local tb_joint = {}
	if tb_joint_cfg then
		for joint_name, cfg in pairs(tb_joint_cfg) do
			local joint_type = cfg[1]
			local body_a = tb_body[cfg[2]]
			local body_b = tb_body[cfg[3]]
			local tb_param = cfg[4]
			if body_a and body_b then
				tb_joint[joint_name] = Physics:CreateJoint(joint_type, body_a, body_b, tb_param)
				assert(tb_joint[joint_name])
			else
				print("error!")
			end
		end
	end

	local tb_gear = {}
	local tb_gear_cfg = tb.tb_gear
	if tb_gear_cfg then		
		for gear_name, cfg in ipairs(tb_gear_cfg) do
			local body_a = tb_body[cfg[1]]
			local body_b = tb_body[cfg[2]]
			local joint_a = tb_joint[cfg[3]]
			local joint_b = tb_joint[cfg[4]]
			local ratio = cfg[5]

			tb_gear[gear_name] = PhysicsWorld:CreateGearJoint(body_a, body_b, joint_a, joint_b, ratio)
			assert(tb_gear[gear_name])
		end
	end
	return tb_body, tb_joint, tb_gear
end