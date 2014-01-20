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

function Physics:CreateBoxSprite(str_image_path, x, y, density, friction, restitution, scale, is_bullet)
	if not scale then
		scale = 1
	end
	if not is_bullet then
		is_bullet = 0
	end
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
    PhysicsWorld:SetBoxBody(physics_sprite, width_physics, height_physics, material, offset_x, offset_y, bool_dynamic, is_bullet)
    return physics_sprite, width_sprite, height_sprite
end

function Physics:CreateCircleSprite(str_image_path, x, y, density, friction, restitution, scale, is_bullet)
	if not scale then
		scale = 1
	end
	if not is_bullet then
		is_bullet = 0
	end
	local physics_sprite = GameSprite:create(str_image_path)
	physics_sprite:setPosition(x, y)
    local radius_sprite = physics_sprite:getContentSize().width * scale
    if scale ~= 1 then
    	physics_sprite:setScale(scale)
    end
    local radius_physics = radius_sprite * 0.5
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    local material = GamePhysicsWorld.MATERIAL:new(density, friction, restitution)
    PhysicsWorld:SetCircleBody(physics_sprite, radius_physics, material, offset_x, offset_y, bool_dynamic, is_bullet)
    return physics_sprite, radius_physics
end

function Physics:GetImagePath(str_polygon_name)
	return string.format("image/%s.png", str_polygon_name)
end

function Physics:CreateCrawlerBelt(x, y, tbParam)
	local str_main_body = tbParam.str_main_body
	if not str_main_body then
		return nil
	end

	local str_wheel = tbParam.str_wheel
	if not str_wheel then
		return nil
	end

	local num_ret_code = 0

	--核心部件
	local main_body, width_body, height_body = Physics:CreateBoxSprite(str_main_body, x, y, 0.1, 0.5, 0.5)
    main_body:setVisible(false)

    local width_body_half = width_body / 2
    local wheel_back, radius_back = Physics:CreateCircleSprite(str_wheel, x - width_body_half, y, 1, 2, 0.5)
    local joint_body_wheel_back = PhysicsWorld:CreateRevoluteJoint(
    	main_body, -width_body_half, 0,
    	wheel_back, 0, 0
    )
    assert(joint_body_wheel_back >= 0)

    local wheel_middle, radius_middle = Physics:CreateCircleSprite(str_wheel, x, y, 1, 2, 0.5)
    local joint_body_wheel_middle = PhysicsWorld:CreateRevoluteJoint(
    	main_body, 0, 0,
    	wheel_middle, 0, 0
    )
    assert(joint_body_wheel_middle >= 0)

    local wheel_front, radius_front = Physics:CreateCircleSprite(str_wheel, x + width_body_half, y, 1, 2, 0.5)
	local joint_body_wheel_front = PhysicsWorld:CreateRevoluteJoint(
    	main_body, width_body_half, 0,
    	wheel_front, 0, 0
    )
    assert(joint_body_wheel_front >= 0)

    local motor_offset_y = 10
    local physics_motor = GameSprite:create("image/circle.png")
	physics_motor:setPosition(x, y + motor_offset_y)
	physics_motor:setVisible(false)
    local radius_sprite = physics_motor:getContentSize().width
    local radius_physics = radius_sprite * 0.5
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    local material = GamePhysicsWorld.MATERIAL:new(1, 0.5, 0.0)
    num_ret_code = PhysicsWorld:SetCircleBody(physics_motor, radius_physics, material, offset_x, offset_y, bool_dynamic, 0, 1, 0)
    assert(num_ret_code == 1)    

    local joint_motor_body = PhysicsWorld:CreateRevoluteJoint(
    	physics_motor, 0, 0,
    	main_body, 0, motor_offset_y
    )
    assert(joint_motor_body >= 0)

    -- local joint_motor_fix_1 = PhysicsWorld:CreateDistanceJoint(
    -- 	physics_motor, 0, 0,
    -- 	wheel_back, 0, 0
    -- )
    -- assert(joint_motor_fix_1 >= 0)

    -- local joint_motor_fix_2 = PhysicsWorld:CreateDistanceJoint(
    -- 	physics_motor, 0, 0,
    -- 	wheel_front, 0, 0
    -- )
    -- assert(joint_motor_fix_2 >= 0)

    local joint_motor_wheel_back = PhysicsWorld:CreateGearJoint(
    	physics_motor, wheel_back,
    	joint_motor_body, joint_body_wheel_back, 1
    )
    assert(joint_motor_wheel_back >= 0)

    local joint_motor_wheel_middle = PhysicsWorld:CreateGearJoint(
    	physics_motor, wheel_middle,
    	joint_motor_body, joint_body_wheel_middle, 1
    )
    assert(joint_motor_wheel_middle >= 0)

    local joint_motor_wheel_front = PhysicsWorld:CreateGearJoint(
    	physics_motor, wheel_front,
    	joint_motor_body, joint_body_wheel_front, 1
    )
    assert(joint_motor_wheel_front >= 0)

	local width_crawler = 10
	local height_crawler = 5
	local freqency = 4
	local ratio = 0.9
	local length_crawler_belt = width_body * 2 + 2 * 3.14 * radius_front
	local num_group_crawler = math.ceil(length_crawler_belt / (4 * 10))
	local tb_crawler_group = {}
	local tb_crawler_total = {}
	local offset = {
		{-num_group_crawler * width_crawler, radius_front + height_crawler / 2,},
		{0, radius_front + height_crawler / 2,},
		{-num_group_crawler * width_crawler, -radius_front - height_crawler / 2,},
		{0, -radius_front - height_crawler / 2,},
	}

	for i = 1, 4 do
		tb_crawler_group[i] = {}
		local tb_crawler = tb_crawler_group[i]
		for j = 1, num_group_crawler do
			local crawler_x = x + offset[i][1] + (j - 0.5) * width_crawler
			local crawler_y = y + offset[i][2]
			local sprite_crawler = Physics:CreateBoxSprite("image/rect2.png", crawler_x, crawler_y, 2, 2, 0.5)
			tb_crawler[#tb_crawler + 1] = sprite_crawler
			tb_crawler_total[#tb_crawler_total + 1] = sprite_crawler
			if j > 1 then
				PhysicsWorld:CreateWeldJoint(
					tb_crawler[j], -width_crawler / 2, 0,
					tb_crawler[j - 1], width_crawler / 2, 0,
					freqency, ratio
				)
			end
		end
	end
	PhysicsWorld:CreateWeldJoint(
		tb_crawler_group[1][1], -width_crawler / 2, 0,
		tb_crawler_group[3][1], -width_crawler / 2, 0,
		freqency, ratio
	)
	PhysicsWorld:CreateWeldJoint(
		tb_crawler_group[2][num_group_crawler], width_crawler / 2, 0,
		tb_crawler_group[4][num_group_crawler], width_crawler / 2, 0,
		freqency, ratio
	)
	PhysicsWorld:CreateWeldJoint(
		tb_crawler_group[1][num_group_crawler], width_crawler / 2, 0,
		tb_crawler_group[2][1], -width_crawler / 2, 0,
		freqency, ratio
	)
	PhysicsWorld:CreateWeldJoint(
		tb_crawler_group[3][num_group_crawler], width_crawler / 2, 0,
		tb_crawler_group[4][1], -width_crawler / 2, 0,
		freqency, ratio
	)

	local tbRet = {
		motor = physics_motor,
		main_body    = main_body,
		wheel_back   = wheel_back,
		wheel_middle = wheel_middle,
		wheel_front  = wheel_front,
		tb_crawler = tb_crawler_total,
		tb_joint = {
			wheel_back = joint_body_wheel_back,
			wheel_middle = joint_body_wheel_middle,
			wheel_front = joint_body_wheel_front,
			motor_body = joint_motor_body,
			motor_wheel_back = joint_motor_wheel_back,
			motor_wheel_middle = joint_motor_wheel_middle,
			motor_wheel_front = joint_motor_wheel_front,
		}
	}
	return tbRet
end