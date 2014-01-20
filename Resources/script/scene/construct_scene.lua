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
	
	local tbParam = {
		str_main_body = "image/rect3.png",
		str_wheel = "image/tank_wheel.png",
	}
	local tb_ret = Physics:CreateCrawlerBelt(200, 100, tbParam)
	if not tb_ret then
		return
	end
	cc_layer_main:addChild(tb_ret.motor)
	cc_layer_main:addChild(tb_ret.main_body)
	cc_layer_main:addChild(tb_ret.wheel_back)
	cc_layer_main:addChild(tb_ret.wheel_middle)
	cc_layer_main:addChild(tb_ret.wheel_front)
	for _, crawler in ipairs(tb_ret.tb_crawler) do
		cc_layer_main:addChild(crawler)
	end

	local tbParam_2 = {
		str_main_body = "image/rect4.png",
		str_wheel = "image/circle.png",
	}
	local tb_ret_2 = Physics:CreateCrawlerBelt(400, 100, tbParam_2)
	if not tb_ret_2 then
		return
	end
	cc_layer_main:addChild(tb_ret_2.motor)
	cc_layer_main:addChild(tb_ret_2.main_body)
	cc_layer_main:addChild(tb_ret_2.wheel_back)
	cc_layer_main:addChild(tb_ret_2.wheel_middle)
	cc_layer_main:addChild(tb_ret_2.wheel_front)
	for _, crawler in ipairs(tb_ret_2.tb_crawler) do
		cc_layer_main:addChild(crawler)
	end
	return 1
end