--=======================================================================
-- File Name    : construct_scene.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-18
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("ConstructScene", 1)
Scene.can_touch = 1 --可接受触摸事件
Scene.can_pick = 1 --可用鼠标拖拽物理刚体

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Scene:_Uninit()

end

function Scene:_Init()
	local tb_visible_size = CCDirector:getInstance():getVisibleSize()
	PhysicsWorld:CreateRectEdge(0, tb_visible_size.width, 0, tb_visible_size.height)

	local cc_layer_main = self:GetLayer("main")
	local tb = {}
	for i = 1, 5 do
		local sprite, width, height = Physics:CreateBoxSprite("image/rect2.png", 100 + i * 16, 100, 1, 0.5, 0.5)
		cc_layer_main:addChild(sprite)
		tb[#tb + 1] = sprite
	end
	for i = 1, 5 do
		local sprite, width, height = Physics:CreateBoxSprite("image/rect2.png", 220 - i * 20, 116, 1, 0.5, 0.5)
		cc_layer_main:addChild(sprite)
		tb[#tb + 1] = sprite
	end
	for i = 1, 10 do
		local i_next = i + 1 <= 10 and i + 1 or 1
		PhysicsWorld:CreateDistanceJoint(tb[i], 0, 0, tb[i_next], 0, 0, 18)
	end
	local pFrontWheel = GameSprite:create("image/tank_wheel.png")
    local float_ball_x = 125
    local float_ball_y = 108
    pFrontWheel:setPosition(float_ball_x, float_ball_y)
    cc_layer_main:addChild(pFrontWheel)

    local float_radius = pFrontWheel:getContentSize().width * 0.5;
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetCircleBody(pFrontWheel, float_radius, m, 0, 0, 1)

    local middle_wheel = GameSprite:create("image/tank_wheel.png")
    local float_ball_x = 145
    local float_ball_y = 108
    middle_wheel:setPosition(float_ball_x, float_ball_y)
    cc_layer_main:addChild(middle_wheel)

    local float_radius = middle_wheel:getContentSize().width * 0.5;
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetCircleBody(middle_wheel, float_radius, m, 0, 0, 1)

    local pBackWheel = GameSprite:create("image/tank_wheel.png")
    local float_ball_x = 165
    local float_ball_y = 108
    pBackWheel:setPosition(float_ball_x, float_ball_y)
    cc_layer_main:addChild(pBackWheel)

    local float_radius = pBackWheel:getContentSize().width * 0.5;
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetCircleBody(pBackWheel, float_radius, m, 0, 0, 1)

    local id_joint = PhysicsWorld:CreateDistanceJoint(
        pFrontWheel, 0,  0,
        middle_wheel, 0, 0
    )
    local id_joint = PhysicsWorld:CreateDistanceJoint(
        middle_wheel, 0,  0,
        pBackWheel, 0, 0
    )
	return 1
end