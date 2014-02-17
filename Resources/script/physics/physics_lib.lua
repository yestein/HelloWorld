--=======================================================================
-- File Name    : physics_lib.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-18 
-- Description  : 更方便的使用物理引擎
-- Modify       :
--=======================================================================
if not Physics then
	Physics = {}
end

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Physics:CreateBody(body_type, image_path, x, y, property)
	if body_type == "box" then
		return self:CreateBoxSprite(image_path, x, y, property)
	elseif body_type == "circle" then
		return self:CreateCircleSprite(image_path, x, y, property)
	elseif body_type =="polygon" then
		return self:CreatePolygonSprite(image_path, x, y)
	end
end

function Physics:CreateJoint(joint_type, body_a, body_b, tb_param)
	if joint_type == "revolute" then
		local anchor_x_a, anchor_y_a = 0, 0
		if tb_param.anchor_a then
			anchor_x_a, anchor_y_a = unpack(tb_param.anchor_a)
		end
		local anchor_x_b, anchor_y_b = 0, 0
		if tb_param.anchor_b then
			anchor_x_b, anchor_y_b = unpack(tb_param.anchor_b)
		end
		local is_limit = tb_param.is_limit or 0
		local min_angel = tb_param.min_angel or 0
		local max_angel = tb_param.max_angel or 0
		local speed = tb_param.speed or 10
		local torque = tb_param.torque or 0

		return PhysicsWorld:CreateRevoluteJoint(
			body_a, anchor_x_a, anchor_y_a, 
    		body_b, anchor_x_b, anchor_y_b,
    		is_limit, min_angel, max_angel, speed, torque
    	)
	elseif joint_type == "distance" then
		local anchor_x_a, anchor_y_a = 0, 0
		if tb_param.anchor_a then
			anchor_x_a, anchor_y_a = unpack(tb_param.anchor_a)
		end
		local anchor_x_b, anchor_y_b = 0, 0
		if tb_param.anchor_b then
			anchor_x_b, anchor_y_b = unpack(tb_param.anchor_b)
		end
		local length = tb_param.length or -1
        local frequency_hz = tb_param.frequency_hz or 0
        local damping_ratio = tb_param.damping_ratio or 0
        local is_collide = tb_param.is_collide or 0
		
		return PhysicsWorld:CreateDistanceJoint(
			body_a, anchor_x_a, anchor_y_a, 
    		body_b, anchor_x_b, anchor_y_b,
    		length, frequency_hz, damping_ratio, is_collide
    	)
	end
end

function Physics:CreateBoxSprite(str_image_path, x, y, property)
	if not property then
		property = {}
	end
	local scale = property.scale or 1
	local density = property.density or 1
	local friction = property.friction or 0.5
	local restitution = property.restitution or 0.5
	local is_bullet = property.is_bullet or 0
	local group_index = property.group_index or 0
	local category_bits = property.category_bits or 0x0001
	local mask_bits = property.mask_bits or 0xFFFF

	local physics_sprite = GameSprite:create(str_image_path)
	physics_sprite:setPosition(x, y)
    local width_sprite = physics_sprite:getContentSize().width * scale
    local height_sprite = physics_sprite:getContentSize().height * scale
    if scale ~= 1 then
    	physics_sprite:setScale(scale)
    end
    local width_physics = width_sprite * 0.5
   	local height_physics = height_sprite * 0.5
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    local material = GamePhysicsWorld.MATERIAL:new(density, friction, restitution)
    PhysicsWorld:SetBoxBody(
    	physics_sprite, width_physics, height_physics, material,
    	offset_x, offset_y, bool_dynamic, is_bullet,
    	group_index, category_bits, mask_bits
   	)
    return physics_sprite, width_sprite, height_sprite
end

function Physics:CreateCircleSprite(str_image_path, x, y, property)
	if not property then
		property = {}
	end
	local scale = property.scale or 1
	local density = property.density or 1
	local friction = property.friction or 0.5
	local restitution = property.restitution or 0.5
	local is_bullet = property.is_bullet or 0
	local group_index = property.group_index or 0
	local category_bits = property.category_bits or 0x0001
	local mask_bits = property.mask_bits or 0xFFFF

	local physics_sprite = GameSprite:create(str_image_path)
	physics_sprite:setPosition(x, y)
    local radius_sprite = physics_sprite:getContentSize().width * scale
    if scale ~= 1 then
    	physics_sprite:setScale(scale)
    end
    local radius_physics = radius_sprite * 0.5
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    local material = GamePhysicsWorld.MATERIAL:new(density, friction, restitution)
    PhysicsWorld:SetCircleBody(
    	physics_sprite, radius_physics, material, 
    	offset_x, offset_y, bool_dynamic, is_bullet,
    	group_index, category_bits, mask_bits
    )
    return physics_sprite, radius_physics
end

function Physics:CreatePolygonSprite(str_polygon_name, x, y)
	local str_image_path = self:GetImagePath(str_polygon_name)
	local physics_sprite = GameSprite:create(str_image_path)
	physics_sprite:setPosition(x, y)
    local width_sprite = physics_sprite:getContentSize().width
    local height_sprite = physics_sprite:getContentSize().height
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    assert(PhysicsWorld:SetPolygonBodyWithShapeName(physics_sprite, str_polygon_name, offset_x, offset_y, bool_dynamic) == 1)
    return physics_sprite, width_sprite, height_sprite
end

function Physics:GetImagePath(str_polygon_name)
	return string.format("image/%s.png", str_polygon_name)
end


function Physics:CreateMotor(cc_layer, x, y, physics_sprite_body)
	local tb_ret = {}
	local property = {
		category_bits = Physics.GROUP_MOTOR,
		mask_bits     = Physics.MASK_MOTOR,
	}
	local motor, radius_motor = Physics:CreateCircleSprite("image/circle.png", x, y, property)
	motor:setVisible(false)
	cc_layer:addChild(motor)
	tb_ret.motor = motor

	local joint_motor_body = PhysicsWorld:CreateRevoluteJoint(
		motor, 0, 0,
    	physics_sprite_body, 0, 0    	
    )
    assert(joint_motor_body)
    tb_ret.joint_motor_body = joint_motor_body

    property.friction = 100
	local brake, width_brake, height_brake = Physics:CreateBoxSprite("image/rect1.png", x , y + radius_motor + 15, property)
	brake:setVisible(false)
	cc_layer:addChild(brake)
	tb_ret.brake = brake

	local joint_brake_body = PhysicsWorld:CreateRevoluteJoint(
		brake, width_brake / 2 - 5, 0, 
    	physics_sprite_body, width_brake / 2 - 5, radius_motor + 15,
    	1, 3.14, 4.72, 20, 10
    )
    assert(joint_brake_body)

    local brake1, width_brake, height_brake = Physics:CreateBoxSprite("image/rect1.png", x , y + radius_motor + 15, property)
	brake1:setVisible(false)
	cc_layer:addChild(brake1)
	tb_ret.brake1 = brake1

	local joint_brake_body = PhysicsWorld:CreateRevoluteJoint(
		brake1, -width_brake / 2 + 5, 0, 
    	physics_sprite_body, -width_brake / 2 + 5, radius_motor + 15,
    	1, -4.72, -3.14, -20, 10
    )
    assert(joint_brake_body)

    return tb_ret
end