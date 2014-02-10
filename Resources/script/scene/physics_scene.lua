--===================================================
-- File Name    : physics_scene.lua
-- Creator      : yulei(yulei1@kingsoft.com)
-- Date         : 2014-01-09 17:56:00
-- Modify       :
--===================================================

local Scene = SceneMgr:GetClass("PhysicsScene", 1)
Scene.tb_property = {
    can_touch     = 1, --可接受触摸事件
    can_pick      = 1, --可用鼠标拖拽物理刚体
    can_drag      = 1, --可拖拽屏幕
    can_scale     = 1, --可缩放
    debug_physics = 1, --是否显示物理引擎调试绘制
}

function Scene:_Uninit()
end

function Scene:_Init()
	local cc_layer_main = self:GetLayer("main")
	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()

    local bg = GameSprite:create("image/background.png")
    local bgRect = bg:getTextureRect()
    cc_layer_main:addChild(bg)
    bg:setAnchorPoint(cc.p(0, 0))

    local width_scene = 0
    local PhysicsWorld = GamePhysicsWorld:GetInstance()
    assert(PhysicsWorld:LoadPolygonBodyFromFile("physics/map.plist") == 1)

        local map = GameSprite:create("image/map1.png")
    	local tbRect = map:getTextureRect()

        local nX = tbRect.width * 0.5 
        local nY = tbRect.height / 2
        width_scene = width_scene + tbRect.width
        map:setPosition(nX, nY)
    	cc_layer_main:addChild(map)        
        assert(PhysicsWorld:SetPolygonBodyWithShapeName(map, "map1", 0, 0, 0) == 1)

    local scale = width_scene / bgRect.width
    local height_scene = bgRect.height * scale
    bg:setScale(width_scene / bgRect.width)
    
    
    num_ret_code = PhysicsWorld:CreateRectEdge(bg, 0, width_scene, 0, height_scene);
    assert(num_ret_code == 1)
    
    local pMainBody = GameSprite:create("image/rect.png")
    local float_body_x = 100
    local float_body_y = tbVisibleSize.height / 2 + 200
    local tbBodyRect = pMainBody:getTextureRect()
    pMainBody:setPosition(float_body_x, float_body_y)
    cc_layer_main:addChild(pMainBody)

    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetBoxBody(pMainBody, tbBodyRect.width / 2, tbBodyRect.height / 2, m, 0, 0, 1)

    local pFrontWheel = GameSprite:create("image/circle.png")
    local float_ball_x = tbVisibleSize.width / 2 + 30
    local float_ball_y = tbVisibleSize.height - 30
    pFrontWheel:setPosition(float_ball_x, float_ball_y)
    cc_layer_main:addChild(pFrontWheel)

    local float_radius = pFrontWheel:getContentSize().width * 0.5;
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetCircleBody(pFrontWheel, float_radius, m, 0, 0, 1)

    local pBackWheel = GameSprite:create("image/circle.png")
    local float_ball_x = tbVisibleSize.width / 2 - 30
    local float_ball_y = tbVisibleSize.height - 30
    pBackWheel:setPosition(float_ball_x, float_ball_y)
    cc_layer_main:addChild(pBackWheel)

    local float_radius = pBackWheel:getContentSize().width * 0.5;
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetCircleBody(pBackWheel, float_radius, m, 0, 0, 1)

    local id_joint = PhysicsWorld:CreateDistanceJoint(
        pFrontWheel,
        0,
        0,
        pBackWheel,    
        0,
        0,
        50,
        0,
        0.5,
        1
    )

    self:SetWidth(width_scene)
    self:SetHeight(height_scene)
    self:SetScale(0.5)
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


