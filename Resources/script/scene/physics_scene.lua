--===================================================
-- File Name    : physics_scene.lua
-- Creator      : yulei(yulei1@kingsoft.com)
-- Date         : 2014-01-09 17:56:00
-- Modify       :
--===================================================

local Scene = SceneMgr:GetClass("PhysicsScene", 1)

function Scene:_Uninit()
    CCDirector:getInstance():getScheduler():unscheduleScriptEntry(self.nRegPhysicsUpdate)
end

function Scene:Create()
	local sceneGame = self:GetCCObj()
	if not sceneGame then
		return
	end
	local cc_layer = cc.Layer:create()
	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()
	
    self.cc_layer = cc_layer
    local bg = cc.Sprite:create("image/background.png")
    local bgRect = bg:getTextureRect()
    bg:setAnchorPoint(cc.p(0, 0))
    cc_layer:addChild(bg)

    local nGameWidth = 0
    local PhysicsWorld = GamePhysicsWorld:GetInstance()
    assert(PhysicsWorld:LoadPolygonBodyFromFile("physics/map-box2d.plist") == 1)
	for i = 1, 3 do
        local map = GameSprite:create("image/map.png")
    	local tbRect = map:getTextureRect()

        local nX = tbRect.width * (i - 0.5) 
        local nY = tbRect.height / 2
        nGameWidth = nGameWidth + tbRect.width
        map:setPosition(nX, nY)
    	cc_layer:addChild(map)        
        assert(PhysicsWorld:SetPolygonBodyWithShapeName(map, "map", 0, 0, 0) == 1)
    end
    local scale = nGameWidth / bgRect.width
    local nGameHeight = bgRect.height * scale
    bg:setScale(nGameWidth / bgRect.width)
    
    
    PhysicsWorld:CreateRectEdge(0, nGameWidth, 0, nGameHeight);
    
    local pMainBody = GameSprite:create("image/rect.png")
    local float_body_x = 100
    local float_body_y = tbVisibleSize.height / 2
    local tbBodyRect = pMainBody:getTextureRect()
    pMainBody:setPosition(float_body_x, float_body_y)
    cc_layer:addChild(pMainBody)

    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetBoxBody(pMainBody, tbBodyRect.width / 2, tbBodyRect.height / 2, m, 0, 0, 1)

    local pFrontWheel = GameSprite:create("image/circle.png")
    local float_ball_x = tbVisibleSize.width / 2 + 30
    local float_ball_y = tbVisibleSize.height - 30
    pFrontWheel:setPosition(float_ball_x, float_ball_y)
    cc_layer:addChild(pFrontWheel)

    local float_radius = pFrontWheel:getContentSize().width * 0.5;
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetCircleBody(pFrontWheel, float_radius, m, 0, 0, 1)

    local pBackWheel = GameSprite:create("image/circle.png")
    local float_ball_x = tbVisibleSize.width / 2 - 30
    local float_ball_y = tbVisibleSize.height - 30
    pBackWheel:setPosition(float_ball_x, float_ball_y)
    cc_layer:addChild(pBackWheel)

    local float_radius = pBackWheel:getContentSize().width * 0.5;
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetCircleBody(pBackWheel, float_radius, m, 0, 0, 1)


    local touchBeginPoint = nil
    local touchStartPoint = nil
    local function onTouchBegan(x, y)
        touchBeginPoint = {x = x, y = y}
        touchStartPoint = {x = x, y = y}
        local nX, nY = cc_layer:getPosition()
        PhysicsWorld:MouseDown(x - nX,  y - nY)
        return true
    end

    local function onTouchMoved(x, y)
        if touchBeginPoint then
            local nX, nY = cc_layer:getPosition()
            if PhysicsWorld:MouseMove(x - nX,  y - nY) ~= 1 then
                local nNewX, nNewY = nX + x - touchBeginPoint.x, nY + y - touchBeginPoint.y
                local nMinX, nMaxX = tbVisibleSize.width - nGameWidth, 0
                local nMinY, nMaxY = tbVisibleSize.height - nGameHeight,  0
                if nNewX < nMinX then
                    nNewX = nMinX
                elseif nNewX > nMaxX then
                    nNewX = nMaxX
                end

                if nNewY < nMinY then
                    nNewY = nMinY
                elseif nNewY > nMaxY then
                    nNewY = nMaxY
                end
                cc_layer:setPosition(nNewX, nNewY)

                touchBeginPoint = {x = x, y = y}
            end
        end
    end

    local function onTouchEnded(x, y)
         local nX, nY = cc_layer:getPosition()
        PhysicsWorld:MouseUp(x - nX,  y - nY)
        touchBeginPoint = nil
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then   
            return onTouchBegan(x, y)
        elseif eventType == "moved" then
            return onTouchMoved(x, y)
        else
            return onTouchEnded(x, y)
        end
    end

    cc_layer:registerScriptTouchHandler(onTouch)
    cc_layer:setTouchEnabled(true)

    local function tick(delta)
    	PhysicsWorld:Update(delta);
    end
    self.nRegPhysicsUpdate = CCDirector:getInstance():getScheduler():scheduleScriptFunc(tick, 0, false)

	Event:FireEvent("SceneCreate", self:GetClassName(), self:GetName())
    return cc_layer
end

