--=======================================================================
-- File Name    : wheel_crawler.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  :
-- Modify       :
--=======================================================================

if not WheelCrawler then
	WheelCrawler = {}
end

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function WheelCrawler:Create(layer, x, y, body, tb_param)
	local crawler_belt_width = tb_param.width
	if not crawler_belt_width then
		return nil
	end
	local image_wheel = tb_param.image_wheel
	if not image_wheel then
		return nil
	end
	-- local image_crawler = tb_param.image_crawler
	-- if not image_crawler then
	-- 	return
	-- end

	local tb_property = {
		density       = tb_param.density or 1,
		friction      = tb_param.friction or 10,
		restitution   = tb_param.restitution or 0.5,
		is_bullet     = 0,
		group_index   = 0,
		category_bits = 0x0001,
		mask_bits     = Physics.MASK_GROUND,
	}
    local width_body_half = crawler_belt_width / 2
	local wheel_back, radius_back     = Physics:CreateCircleSprite(image_wheel, x - width_body_half, y, tb_property)
	local wheel_middle, radius_middle = Physics:CreateCircleSprite(image_wheel, x, y + 5, tb_property)
	local wheel_front, radius_front   = Physics:CreateCircleSprite(image_wheel, x + width_body_half, y,tb_property)
	
	local joint_body_wheel_back = PhysicsWorld:CreateRevoluteJoint(
    	body, - width_body_half, 0,
    	wheel_back, 0, 0
    )
    assert(joint_body_wheel_back)

    local joint_body_wheel_middle = PhysicsWorld:CreateRevoluteJoint(
    	body, 0, 5,
    	wheel_middle, 0, 0
    )
    assert(joint_body_wheel_middle)

    local joint_body_wheel_front = PhysicsWorld:CreateRevoluteJoint(
    	body, width_body_half, 0,
    	wheel_front, 0, 0
    )
    assert(joint_body_wheel_front)

 --    local TextureCache = cc.Director:getInstance():getTextureCache()
	-- local texture_crawler = TextureCache:addImage(image_crawler)
	-- local width_crawler = texture_crawler:getContentSize().width
	-- local height_crawler = texture_crawler:getContentSize().height
	-- local repeat_part_length = 2
	-- local width_crawler_width_calc = width_crawler - repeat_part_length
	-- local freqency = 4
	-- local ratio = 0.9
	-- local length_crawler_belt = crawler_belt_width * 2 + 2 * 3.14 * radius_front
	-- local num_group_crawler = math.ceil(length_crawler_belt / (2 * (width_crawler_width_calc)))
	-- local tb_crawler_group = {}
	-- local tb_crawler_total = {}
	-- local offset = {
	-- 	{-length_crawler_belt / 4, radius_front + height_crawler / 2,},
	-- 	{-length_crawler_belt / 4, -radius_front - height_crawler / 2,},
	-- }

	-- tb_property.mask_bits = Physics.MASK_GROUND
	-- tb_property.density = 2
	-- tb_property.friction = 10
	-- for i = 1, 2 do
	-- 	tb_crawler_group[i] = {}
	-- 	local tb_crawler = tb_crawler_group[i]
	-- 	for j = 1, num_group_crawler do
	-- 		local crawler_x = x + offset[i][1] + 0.5 * width_crawler + (j - 1) * width_crawler_width_calc
	-- 		local crawler_y = y + offset[i][2]
	-- 		local sprite_crawler = Physics:CreateBoxSprite(image_crawler, crawler_x, crawler_y, tb_property)
	-- 		tb_crawler[#tb_crawler + 1] = sprite_crawler
	-- 		tb_crawler_total[#tb_crawler_total + 1] = sprite_crawler
	-- 		if j > 1 then
	-- 			PhysicsWorld:CreateRevoluteJoint(
	-- 				tb_crawler[j], -width_crawler_width_calc / 2, 0,
	-- 				tb_crawler[j - 1], width_crawler_width_calc / 2, 0
	-- 			)
	-- 		end
	-- 	end
	-- end
	-- PhysicsWorld:CreateRevoluteJoint(
	-- 	tb_crawler_group[1][num_group_crawler], width_crawler_width_calc / 2, 0,
	-- 	tb_crawler_group[2][num_group_crawler], width_crawler_width_calc / 2, 0
	-- )

	-- PhysicsWorld:CreateRevoluteJoint(
	-- 	tb_crawler_group[1][1], -width_crawler_width_calc / 2, 0,
	-- 	tb_crawler_group[2][1], -width_crawler_width_calc / 2, 0
	-- )

	local tb_ret = {
		wheel_back   = wheel_back,
		wheel_middle = wheel_middle,
		wheel_front  = wheel_front,
		tb_crawler = tb_crawler_total,
		tb_joint = {
			wheel_back = joint_body_wheel_back,
			wheel_middle = joint_body_wheel_middle,
			wheel_front = joint_body_wheel_front,
		}
	}

	if not tb_param.visible then
		wheel_back:setVisible(false)
		wheel_middle:setVisible(false)
		wheel_front:setVisible(false)
	end
	layer:addChild(tb_ret.wheel_back)
	layer:addChild(tb_ret.wheel_middle)
	layer:addChild(tb_ret.wheel_front)

	if tb_ret.tb_crawler then
		for _, crawler in ipairs(tb_ret.tb_crawler) do
			layer:addChild(crawler)
		end
	end
	return tb_ret
end