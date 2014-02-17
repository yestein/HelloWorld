--=======================================================================
-- File Name    : polygon_break_scene.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-15
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("PolygonBreak", 1)
local PhysicsWorld = GamePhysicsWorld:GetInstance()
Scene.property = {
    can_touch  = 1,--可接受触摸事件
    can_pick   = 1,--可用鼠标拖拽物理刚体
    can_drag = 1,
    debug_physics = 1, --是否显示物理引擎调试绘制
}

function Scene:_Uninit( ... )
    -- body
end

function Scene:_Init()
	local cc_layer_main = self:GetLayer("main")
	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()

    local sprite_background = GameSprite:create("image/background.png")
    cc_layer_main:addChild(sprite_background)
    sprite_background:setAnchorPoint(cc.p(0, 0))

    num_ret_code = PhysicsWorld:CreateRectEdge(sprite_background, 0, tbVisibleSize.width, 0, tbVisibleSize.height);
    assert(num_ret_code == 1)

    local gamesprite_map = GameSprite:create("image/map1.png")
    local tbRect = gamesprite_map:getTextureRect()
    local clippingNodeBG = cc.ClippingNode:create(gamesprite_map)
    gamesprite_map:setPosition(tbRect.width / 2, tbRect.height / 2)
    clippingNodeBG:setAlphaThreshold(0.05)
    clippingNodeBG:setInverted(false)
    
    
    local clippingNode = cc.ClippingNode:create(gamesprite_map)
    clippingNode:setAlphaThreshold(0.05)
    clippingNode:setInverted(true)    
    clippingNode:addChild(gamesprite_map)
    
    local pHole = cc.Node:create()
    clippingNode:setStencil(pHole)
    self.pHole = pHole

    local pEdge = cc.Node:create()
    clippingNode:addChild(pEdge)
    self.pEdge = pEdge

    cc_layer_main:addChild(clippingNodeBG)
    clippingNodeBG:addChild(clippingNode)

    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    assert(PhysicsWorld:LoadPolygonBodyFromFile("physics/map.plist") == 1)

    assert(PhysicsWorld:SetBoxBody(gamesprite_map, 100, 100, m, 0, 0, 0) == 1)
    self.test_polygon = gamesprite_map

    local pFrontWheel = GameSprite:create("image/circle.png")
    local float_ball_x = tbVisibleSize.width / 2 + 30
    local float_ball_y = tbVisibleSize.height - 30
    pFrontWheel:setPosition(float_ball_x, float_ball_y)
    cc_layer_main:addChild(pFrontWheel)

    local float_radius = pFrontWheel:getContentSize().width * 0.5;
    
    PhysicsWorld:SetCircleBody(pFrontWheel, float_radius, m, 0, 0, 1)
    return 1
end

function Scene:OnTouchBegan(x, y)
    return Physics:OnMouseDown(x, y)
end

function Scene:OnTouchMoved(x, y)
    return Physics:OnMouseMoved(x, y)
end

function Scene:OnTouchEnded(x, y)
    Physics:OnMouseEnded(x, y)
    return self:BreakPolygon(x, y)
end

function Scene:BreakPolygon(x, y)
	local polygon = self.test_polygon
    PhysicsWorld:ClipperPolygonByShape(polygon, "tank_2", x, y)

    local pSprite = cc.Sprite:create("image/hole-erase.png")
    pSprite:setPosition(x, y) 
    self.pHole:addChild(pSprite)
    
    local pSpriteEdge = cc.Sprite:create("image/hole-edge.png")
    pSpriteEdge:setPosition(x, y) 
    self.pEdge:addChild(pSpriteEdge)
end