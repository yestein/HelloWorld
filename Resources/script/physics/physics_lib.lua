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

function Physics:CreateBoxSprite(str_image_path, x, y, tb_property)
	if not tb_property then
		tb_property = {}
	end
	local scale = tb_property.scale or 1
	local density = tb_property.density or 1
	local friction = tb_property.friction or 0.5
	local restitution = tb_property.restitution or 0.5
	local is_bullet = tb_property.is_bullet or 0
	local group_index = tb_property.group_index or 0
	local category_bits = tb_property.category_bits or 0x0001
	local mask_bits = tb_property.mask_bits or 0xFFFF

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

function Physics:CreateCircleSprite(str_image_path, x, y, tb_property)
	if not tb_property then
		tb_property = {}
	end
	local scale = tb_property.scale or 1
	local density = tb_property.density or 1
	local friction = tb_property.friction or 0.5
	local restitution = tb_property.restitution or 0.5
	local is_bullet = tb_property.is_bullet or 0
	local group_index = tb_property.group_index or 0
	local category_bits = tb_property.category_bits or 0x0001
	local mask_bits = tb_property.mask_bits or 0xFFFF

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

function Physics:GetImagePath(str_polygon_name)
	return string.format("image/%s.png", str_polygon_name)
end

function Physics:CreateCrawlerBelt(layer, x, y, body, crawler_belt_width, tbParam)
	local str_wheel = tbParam.str_wheel
	if not str_wheel then
		return nil
	end
	local str_crawler = tbParam.str_crawler
	if not str_crawler then
		return
	end

	local num_ret_code = 0

	--核心部件
	local tb_property = {
		density       = 1,
		friction      = 2,
		restitution   = 0.5,
		is_bullet     = 0,
		group_index   = 0,
		category_bits = 0x0001,
		mask_bits     = Physics.MASK_GROUND,
	}
    local width_body_half = crawler_belt_width / 2
	local wheel_back, radius_back     = Physics:CreateCircleSprite(str_wheel, x - width_body_half, y, tb_property)
	local wheel_middle, radius_middle = Physics:CreateCircleSprite(str_wheel, x, y, tb_property)
	local wheel_front, radius_front   = Physics:CreateCircleSprite(str_wheel, x + width_body_half, y,tb_property)
	
	local wheel_middle_fixed = Physics:CreateCircleSprite(str_wheel, x, y, tb_property)
	wheel_middle_fixed:setVisible(false)

	local joint_body_wheel_back = PhysicsWorld:CreateRevoluteJoint(
    	body, - width_body_half, -20,
    	wheel_back, 0, 0
    )
    assert(joint_body_wheel_back)

    local joint_body_wheel_middle = PhysicsWorld:CreateRevoluteJoint(
    	wheel_middle_fixed, 0, 0,
    	wheel_middle, 0, 0
    )
    assert(joint_body_wheel_middle)

    local joint_body_wheel_middle_fixed = PhysicsWorld:CreateWeldJoint(
    	body, 0, -20,
    	wheel_middle_fixed, 0, 0
    )
    assert(joint_body_wheel_middle_fixed)

    local joint_body_wheel_front = PhysicsWorld:CreateRevoluteJoint(
    	body, width_body_half, -20,
    	wheel_front, 0, 0
    )
    assert(joint_body_wheel_front)

	local texture_crawler = CCTextureCache:getInstance():addImage(str_crawler)
	local width_crawler = texture_crawler:getContentSize().width
	local height_crawler = texture_crawler:getContentSize().height
	local repeat_part_length = 2
	local width_crawler_width_calc = width_crawler - repeat_part_length
	local freqency = 4
	local ratio = 0.9
	local length_crawler_belt = crawler_belt_width * 2 + 2 * 3.14 * radius_front
	local num_group_crawler = math.ceil(length_crawler_belt / (2 * (width_crawler_width_calc)))
	local tb_crawler_group = {}
	local tb_crawler_total = {}
	local offset = {
		{-length_crawler_belt / 4, radius_front + height_crawler / 2,},
		{-length_crawler_belt / 4, -radius_front - height_crawler / 2,},
	}

	tb_property.mask_bits = Physics.MASK_GROUND
	tb_property.density = 2
	for i = 1, 2 do
		tb_crawler_group[i] = {}
		local tb_crawler = tb_crawler_group[i]
		for j = 1, num_group_crawler do
			local crawler_x = x + offset[i][1] + 0.5 * width_crawler + (j - 1) * width_crawler_width_calc
			local crawler_y = y + offset[i][2]
			local sprite_crawler = Physics:CreateBoxSprite(str_crawler, crawler_x, crawler_y, tb_property)
			tb_crawler[#tb_crawler + 1] = sprite_crawler
			tb_crawler_total[#tb_crawler_total + 1] = sprite_crawler
			if j > 1 then
				PhysicsWorld:CreateRevoluteJoint(
					tb_crawler[j], -width_crawler_width_calc / 2, 0,
					tb_crawler[j - 1], width_crawler_width_calc / 2, 0
				)
			end
		end
	end
	PhysicsWorld:CreateRevoluteJoint(
		tb_crawler_group[1][num_group_crawler], width_crawler_width_calc / 2, 0,
		tb_crawler_group[2][num_group_crawler], width_crawler_width_calc / 2, 0
	)

	PhysicsWorld:CreateRevoluteJoint(
		tb_crawler_group[1][1], -width_crawler_width_calc / 2, 0,
		tb_crawler_group[2][1], -width_crawler_width_calc / 2, 0
	)

	local tb_ret = {
		wheel_back   = wheel_back,
		wheel_middle = wheel_middle,
		wheel_front  = wheel_front,
		wheel_middle_fixed = wheel_middle_fixed,
		tb_crawler = tb_crawler_total,
		tb_joint = {
			wheel_back = joint_body_wheel_back,
			wheel_middle = joint_body_wheel_middle,
			wheel_front = joint_body_wheel_front,
		}
	}

	layer:addChild(tb_ret.wheel_back)
	layer:addChild(tb_ret.wheel_middle)
	layer:addChild(tb_ret.wheel_front)
	layer:addChild(tb_ret.wheel_middle_fixed)

	for _, crawler in ipairs(tb_ret.tb_crawler) do
		layer:addChild(crawler)
	end
	return tb_ret
end