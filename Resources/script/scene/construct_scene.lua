--=======================================================================
-- File Name    : construct_scene.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-18
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("ConstructScene", 1)
Scene.tb_property = {
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

	local sprite_background = GameSprite:create("image/background.png")
    cc_layer_main:addChild(sprite_background)
    sprite_background:setAnchorPoint(cc.p(0, 0))

	num_ret_code = PhysicsWorld:CreateRectEdge(sprite_background, 0, tb_visible_size.width, 0, tb_visible_size.height)
	assert(num_ret_code == 1)
	
	self:TestCrawlerBelt()
	self:TestSpider()
	return 1
end

function Scene:TestCrawlerBelt()
	local tb_visible_size = CCDirector:getInstance():getVisibleSize()
	local cc_layer_main = self:GetLayer("main")

	local physics_sprite_body, width_body, height_body = Physics:CreatePolygonSprite("tank_2", 200, 100)
    cc_layer_main:addChild(physics_sprite_body)

	local tbParam = {
		str_wheel = "image/tank_wheel.png",
		str_crawler = "image/rect2.png",
	}
	local tb_ret = Physics:CreateCrawlerBelt(cc_layer_main, 200, 100, physics_sprite_body, 50, tbParam)
	if not tb_ret then
		assert(false)
	end

	local tb_property = {
		mask_bits     = 0,
	}
	local motor, radius_motor = Physics:CreateCircleSprite("image/circle.png", 200, 100, tb_property)
	motor:setVisible(false)
	cc_layer_main:addChild(motor)

	local joint_motor_body = PhysicsWorld:CreateRevoluteJoint(
    	physics_sprite_body, 0, 0,
    	motor, 0, 0
    )
    assert(joint_motor_body)

    local joint_motor_wheel_back = PhysicsWorld:CreateGearJoint(
    	motor, tb_ret.wheel_back,
    	joint_motor_body, tb_ret.tb_joint.wheel_back, 1
    )
    assert(joint_motor_wheel_back)

    local joint_motor_wheel_middle = PhysicsWorld:CreateGearJoint(
    	motor, tb_ret.wheel_middle,
    	joint_motor_body, tb_ret.tb_joint.wheel_middle, 1
    )
    assert(joint_motor_wheel_middle)

    local joint_motor_wheel_front = PhysicsWorld:CreateGearJoint(
    	motor, tb_ret.wheel_front,
    	joint_motor_body, tb_ret.tb_joint.wheel_front, 1
    )
    assert(joint_motor_wheel_front)
end

function Scene:TestSpider()
	local tb_visible_size = CCDirector:getInstance():getVisibleSize()
	local cc_layer_main = self:GetLayer("main")

end

