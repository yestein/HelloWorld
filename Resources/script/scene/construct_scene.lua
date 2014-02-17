--=======================================================================
-- File Name    : construct_scene.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-18
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("ConstructScene", 1)
Scene.property = {
	can_drag = 1,
	can_touch = 1, --可接受触摸事件
	can_pick  = 1, --可用鼠标拖拽物理刚体
	debug_physics = 1, --是否显示物理引擎调试绘制
}

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Scene:_Uninit()

end

function Scene:_Init()
	local tb_visible_size = CCDirector:getInstance():getVisibleSize()
	local cc_layer_main = self:GetLayer("main")

	local sprite_background = GameSprite:create("image/1935.png")
	local tb_rect = sprite_background:getContentSize()
	local scale = tb_visible_size.width / tb_rect.width
    cc_layer_main:addChild(sprite_background)
    sprite_background:setAnchorPoint(cc.p(0, 0))
    sprite_background:setScale(scale)

	num_ret_code = PhysicsWorld:CreateRectEdge(sprite_background, 0, tb_rect.width * scale, 0, tb_rect.height * scale)
	assert(num_ret_code == 1)
	
	-- self:TestCrawlerBelt()
	self:TestSpider1()
	self:TestSpider2()
	self:SetScale(4)
	PhysicsWorld:SetGravity(0, -10)
	return 1
end

function Scene:OnTouchBegan(x, y)
    return Physics:OnMouseDown(x, y)
end

function Scene:OnTouchMoved(x, y)
    return Physics:OnMouseMoved(x, y)
end

function Scene:OnTouchEnded(x, y)
    return Physics:OnMouseEnded(x, y)
end

function Scene:TestCrawlerBelt()
	local tb_visible_size = CCDirector:getInstance():getVisibleSize()
	local cc_layer_main = self:GetLayer("main")

	local tb_construct = {
    	str_body = "tank_1",
    	weapon_type = "test1",
    	motor_type = "test1",
	}
	Construct:BuildTank(cc_layer_main, 200, 200, tb_construct)
end

function Scene:TestSpider1()
	local tb_visible_size = CCDirector:getInstance():getVisibleSize()
	local cc_layer_main = self:GetLayer("main")

	local frequency_hz = 10
	local damping_ratio = 0.5

	local leg_up_offset_x = 60
	local leg_up_offset_y = 0
	local leg_down_offset_x = 100
	local leg_down_offset_y = -40

	local scale = 0.1

	local round_radius = 20
	local round_leg_length = 60
	local leg_up_body_length = 90--Lib:GetDistance(round_radius, 0, leg_up_offset_x, round_leg_length)
	local leg_down_body_length = Lib:GetDistance(round_radius, 0, leg_down_offset_x, leg_down_offset_y)
	local leg_width = 50

	local leg_distance = Lib:GetDistance(leg_up_offset_x, leg_up_offset_y, leg_down_offset_x, leg_down_offset_y)
	local tb = {
		tb_body = {
			main  = {"box", "image/rect.png", 0, 0, {group_index = -1}},
			motor = {"circle", "image/circle.png", 0, 0, {scale = 2, group_index = -1}},
			leg_1 = {"polygon", "leg_1", leg_up_offset_x, 0},			
			leg_3 = {"polygon", "leg_3", -leg_up_offset_x, 0},
			leg_5 = {"polygon", "leg_1", leg_up_offset_x, 0},
			leg_7 = {"polygon", "leg_3", -leg_up_offset_x, 0},
			leg_9 = {"polygon", "leg_1", leg_up_offset_x, 0},
			leg_11 = {"polygon", "leg_3", -leg_up_offset_x, 0},

			leg_2 = {"polygon", "leg_2", leg_down_offset_x, leg_down_offset_y},
			leg_4 = {"polygon", "leg_4", -leg_down_offset_x, leg_down_offset_y},
			leg_6 = {"polygon", "leg_2", leg_down_offset_x, leg_down_offset_y},
			leg_8 = {"polygon", "leg_4", -leg_down_offset_x, leg_down_offset_y},			
			leg_10 = {"polygon", "leg_2", leg_down_offset_x, leg_down_offset_y},			
			leg_12 = {"polygon", "leg_4", -leg_down_offset_x, leg_down_offset_y},
		},
		tb_hide = {"main", "motor"},
		tb_joint = {
			motor_main  = {"revolute", "main", "motor", {speed = -2, torque = 400}},

			main_leg1  = {"revolute", "main", "leg_1", {anchor_a = {leg_up_offset_x, 0}}},
			main_leg3  = {"revolute", "main", "leg_3", {anchor_a = {-leg_up_offset_x, 0}}},

			main_leg5  = {"revolute", "main", "leg_5", {anchor_a = {leg_up_offset_x, 0}}},
			main_leg7  = {"revolute", "main", "leg_7", {anchor_a = {-leg_up_offset_x, 0}}},

			main_leg9  = {"revolute", "main", "leg_9", {anchor_a = {leg_up_offset_x, 0}}},
			main_leg11 = {"revolute", "main", "leg_11", {anchor_a = {-leg_up_offset_x, 0}}},

			motor_leg1 = {"distance", "motor", "leg_1", 
				{anchor_a = {0, round_radius}, anchor_b = {0, round_leg_length}, length = leg_up_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg3 = {"distance", "motor", "leg_3", 
				{anchor_a = {0, round_radius}, anchor_b = {0, round_leg_length}, length = leg_up_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg5 = {"distance", "motor", "leg_5", 
				{anchor_a = {round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, round_leg_length}, length = leg_up_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg7 = {"distance", "motor", "leg_7", 
				{anchor_a = {round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, round_leg_length}, length = leg_up_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg9 = {"distance", "motor", "leg_9", 
				{anchor_a = {-round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, round_leg_length}, length = leg_up_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg11 = {"distance", "motor", "leg_11", 
				{anchor_a = {-round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, round_leg_length}, length = leg_up_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg2 = {"distance", "motor", "leg_2", 
				{anchor_a = {0, round_radius}, anchor_b = {0, 0}, length = leg_down_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			motor_leg4 = {"distance", "motor", "leg_4", 
				{anchor_a = {0, round_radius}, anchor_b = {0, 0}, length = leg_down_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},	
			motor_leg6 = {"distance", "motor", "leg_6", 
				{anchor_a = {round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, 0}, length = leg_down_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			motor_leg8 = {"distance", "motor", "leg_8", 
				{anchor_a = {round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, 0}, length = leg_down_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			motor_leg10 = {"distance", "motor", "leg_10", 
				{anchor_a = {-round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, 0}, length = leg_down_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			motor_leg12 = {"distance", "motor", "leg_12", 
				{anchor_a = {-round_radius * 0.866, -round_radius * 0.5}, anchor_b = {0, 0}, length = leg_down_body_length, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},	

			leg1_leg2_1 = {"distance", "leg_1", "leg_2", 
				{anchor_a = {0, 0}, anchor_b = {0, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg1_leg2_2 = {"distance", "leg_1", "leg_2", 
				{anchor_a = {leg_width, 0}, anchor_b = {leg_width, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg1_leg2_3 = {"distance", "leg_1", "leg_2", 
				{anchor_a = {0, 0}, anchor_b = {0, -round_leg_length}, length = leg_distance + round_leg_length, frequency_hz = 1.5, damping_ratio = 0.5}
			},
			leg3_leg4_1 = {"distance", "leg_3", "leg_4", 
				{anchor_a = {0, 0}, anchor_b = {0, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg3_leg4_2 = {"distance", "leg_3", "leg_4", 
				{anchor_a = {-leg_width, 0}, anchor_b = {-leg_width, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg3_leg4_3 = {"distance", "leg_3", "leg_4", 
				{anchor_a = {0, 0}, anchor_b = {0, -round_leg_length}, length = leg_distance + round_leg_length, frequency_hz = 1.5, damping_ratio = 0.5}
			},
			leg5_leg6_1 = {"distance", "leg_5", "leg_6", 
				{anchor_a = {0, 0}, anchor_b = {0, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg5_leg6_2 = {"distance", "leg_5", "leg_6", 
				{anchor_a = {leg_width, 0}, anchor_b = {leg_width, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg5_leg6_3 = {"distance", "leg_5", "leg_6", 
				{anchor_a = {0, 0}, anchor_b = {0, -round_leg_length}, length = leg_distance + round_leg_length, frequency_hz = 1.5, damping_ratio = 0.5}
			},
			leg7_leg8_1 = {"distance", "leg_7", "leg_8", 
				{anchor_a = {0, 0}, anchor_b = {0, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg7_leg8_2 = {"distance", "leg_7", "leg_8", 
				{anchor_a = {-leg_width, 0}, anchor_b = {-leg_width, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg7_leg8_3 = {"distance", "leg_7", "leg_8", 
				{anchor_a = {0, 0}, anchor_b = {0, -round_leg_length}, length = leg_distance + round_leg_length, frequency_hz = 1.5, damping_ratio = 0.5}
			},
			leg9_leg10_1 = {"distance", "leg_9", "leg_10", 
				{anchor_a = {0, 0}, anchor_b = {0, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg9_leg10_2 = {"distance", "leg_9", "leg_10", 
				{anchor_a = {leg_width, 0}, anchor_b = {leg_width, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg9_leg10_3 = {"distance", "leg_9", "leg_10", 
				{anchor_a = {0, 0}, anchor_b = {0, -round_leg_length}, length = leg_distance + round_leg_length, frequency_hz = 1.5, damping_ratio = 0.5}
			},
			leg11_leg12_1 = {"distance", "leg_11", "leg_12", 
				{anchor_a = {0, 0}, anchor_b = {0, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg11_leg12_2 = {"distance", "leg_11", "leg_12", 
				{anchor_a = {-leg_width, 0}, anchor_b = {-leg_width, 0}, length = leg_distance, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
			leg11_leg12_3 = {"distance", "leg_11", "leg_12", 
				{anchor_a = {0, 0}, anchor_b = {0, -round_leg_length}, length = leg_distance + round_leg_length, frequency_hz = 1.5, damping_ratio = 0.5}
			},
		},
	}

	Construct:Create(cc_layer_main, 300, 300, tb)
end

function Scene:TestSpider2()
	local tb_visible_size = CCDirector:getInstance():getVisibleSize()
	local cc_layer_main = self:GetLayer("main")

	local frequency_hz = 10
	local damping_ratio = 0.5

	local leg_up_offset_x = 15
	local leg_up_offset_y = 0
	local leg_down_offset_x = 23
	local leg_down_offset_y = -10

	local scale = 0.1

	local round_radius = 5
	local round_leg_length = 15
	local leg_up_body_length = 22.5--Lib:GetDistance(round_radius, 0, leg_up_offset_x, round_leg_length)
	local leg_down_body_length = Lib:GetDistance(round_radius, 0, leg_down_offset_x, leg_down_offset_y)
	local leg_width = 10

	local motor_scale = 0.5
	local leg_scale = 0.5
	local radius = 16 * motor_scale
	local leg_length = 32

	local distance1 = 28
	local distance2 = leg_length * 0.75

	local tb = {
		tb_body = {
			main  = {"box", "image/rect1.png", 0, 0, {group_index = -1}},
			motor = {"circle", "image/circle.png", 0, 0, {scale = motor_scale, group_index = -1}},
			leg1 = {"box", "image/rect1.png", leg_length, 0, {scale = leg_scale, group_index = -1}},		
			leg2 = {"box", "image/rect1.png", leg_length * 1.5, 0, {scale = leg_scale, group_index = -1}},

			leg3 = {"box", "image/rect1.png", leg_length, 0, {scale = leg_scale, group_index = -1}},		
			leg4 = {"box", "image/rect1.png", leg_length * 1.5, 0, {scale = leg_scale, group_index = -1}},

			leg5 = {"box", "image/rect1.png", leg_length, 0, {scale = leg_scale, group_index = -1}},		
			leg6 = {"box", "image/rect1.png", leg_length * 1.5, 0, {scale = leg_scale, group_index = -1}},

			leg7 = {"box", "image/rect1.png", leg_length, 0, {scale = leg_scale, group_index = -1}},		
			leg8 = {"box", "image/rect1.png", leg_length * 1.5, 0, {scale = leg_scale, group_index = -1}},

			leg9 = {"box", "image/rect1.png", leg_length, 0, {scale = leg_scale, group_index = -1}},		
			leg10 = {"box", "image/rect1.png", leg_length * 1.5, 0, {scale = leg_scale, group_index = -1}},

			leg11 = {"box", "image/rect1.png", leg_length, 0, {scale = leg_scale, group_index = -1}},		
			leg12 = {"box", "image/rect1.png", leg_length * 1.5, 0, {scale = leg_scale, group_index = -1}},
		},
		tb_hide = {"main", "motor"},
		tb_joint = {
			motor_main  = {"revolute", "main", "motor", {speed = -2, torque = 400}},
			main_leg1  = {"revolute", "main", "leg1", {scale = leg_scale, is_limit = 1, min_angel = -1.57, max_angel = 0, anchor_a = {leg_length * 0.5, leg_length * 0.5}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}}},
			leg1_leg2  = {"revolute", "leg1", "leg2", {scale = leg_scale, is_limit = 1, min_angel = 4.71, max_angel = 6.28, anchor_a = {leg_length * 0.5 * leg_scale, 0}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}}},

			motor_leg1 = {"distance", "motor", "leg1", 
				{anchor_a = {round_radius, 0}, anchor_b = {leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg2 = {"distance", "motor", "leg2", 
				{anchor_a = {round_radius, 0}, anchor_b = {leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			main_leg3  = {"revolute", "main", "leg3", {scale = leg_scale, is_limit = 1, min_angel = 0, max_angel = 1.57, anchor_a = {-leg_length * 0.5, leg_length * 0.5}, anchor_b = {leg_length * 0.5 * leg_scale, 0}}},
			leg3_leg4  = {"revolute", "leg3", "leg4", {scale = leg_scale, is_limit = 1, min_angel = 0, max_angel = 1.57, anchor_a = {-leg_length * 0.5 * leg_scale, 0}, anchor_b = {leg_length * 0.5 * leg_scale, 0}}},

			motor_leg3 = {"distance", "motor", "leg3", 
				{anchor_a = {round_radius, 0}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg4 = {"distance", "motor", "leg4", 
				{anchor_a = {round_radius, 0}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			main_leg5  = {"revolute", "main", "leg5", {scale = leg_scale, is_limit = 1, min_angel = -1.57, max_angel = 0, anchor_a = {leg_length * 0.5, leg_length * 0.5}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}}},
			leg5_leg6  = {"revolute", "leg5", "leg6", {scale = leg_scale, is_limit = 1, min_angel = 4.71, max_angel = 6.28, anchor_a = {leg_length * 0.5 * leg_scale, 0}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}}},

			motor_leg5 = {"distance", "motor", "leg5", 
				{anchor_a = {-round_radius * 0.5, round_radius * 0.866}, anchor_b = {leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg6 = {"distance", "motor", "leg6", 
				{anchor_a = {-round_radius * 0.5, round_radius * 0.866}, anchor_b = {leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			main_leg7  = {"revolute", "main", "leg7", {scale = leg_scale, is_limit = 1, min_angel = 0, max_angel = 1.57, anchor_a = {-leg_length * 0.5, leg_length * 0.5}, anchor_b = {leg_length * 0.5 * leg_scale, 0}}},
			leg7_leg8  = {"revolute", "leg7", "leg8", {scale = leg_scale, is_limit = 1, min_angel = 0, max_angel = 1.57, anchor_a = {-leg_length * 0.5 * leg_scale, 0}, anchor_b = {leg_length * 0.5 * leg_scale, 0}}},

			motor_leg7 = {"distance", "motor", "leg7", 
				{anchor_a = {-round_radius * 0.5, round_radius * 0.866}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg8 = {"distance", "motor", "leg8", 
				{anchor_a = {-round_radius * 0.5, round_radius * 0.866}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			main_leg9  = {"revolute", "main", "leg9", {scale = leg_scale, is_limit = 1, min_angel = -1.57, max_angel = 0, anchor_a = {leg_length * 0.5, leg_length * 0.5}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}}},
			leg9_leg10  = {"revolute", "leg9", "leg10", {scale = leg_scale, is_limit = 1, min_angel = 4.71, max_angel = 6.28, anchor_a = {leg_length * 0.5 * leg_scale, 0}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}}},

			motor_leg9 = {"distance", "motor", "leg9", 
				{anchor_a = {-round_radius * 0.5, -round_radius * 0.866}, anchor_b = {leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg10 = {"distance", "motor", "leg10", 
				{anchor_a = {-round_radius * 0.5, -round_radius * 0.866}, anchor_b = {leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			main_leg11  = {"revolute", "main", "leg11", {scale = leg_scale, is_limit = 1, min_angel = 0, max_angel = 1.57, anchor_a = {-leg_length * 0.5, leg_length * 0.5}, anchor_b = {leg_length * 0.5 * leg_scale, 0}}},
			leg11_leg12  = {"revolute", "leg11", "leg12", {scale = leg_scale, is_limit = 1, min_angel = 0, max_angel = 1.57, anchor_a = {-leg_length * 0.5 * leg_scale, 0}, anchor_b = {leg_length * 0.5 * leg_scale, 0}}},

			motor_leg11 = {"distance", "motor", "leg11", 
				{anchor_a = {-round_radius * 0.5, -round_radius * 0.866}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},

			motor_leg12 = {"distance", "motor", "leg12", 
				{anchor_a = {-round_radius * 0.5, -round_radius * 0.866}, anchor_b = {-leg_length * 0.5 * leg_scale, 0}, length = distance1, frequency_hz = frequency_hz, damping_ratio = damping_ratio}
			},
		},
	}
	Construct:Create(cc_layer_main, 100, 50, tb)
end