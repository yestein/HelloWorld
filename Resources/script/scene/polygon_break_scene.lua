--=======================================================================
-- File Name    : polygon_break_scene.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-15
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("PolygonBreak", 1)
local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Scene:Create()
	local sceneGame = self:GetCCObj()
	if not sceneGame then
		return
	end
	local cc_layer = cc.Layer:create()
	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()
	
       
    PhysicsWorld:CreateRectEdge(0, tbVisibleSize.width * 2, 0, tbVisibleSize.height * 2);
    
    local pMainBody = GameSprite:create("image/background.png")
    local tbBodyRect = pMainBody:getTextureRect()
    local float_body_x = tbBodyRect.width / 2
    local float_body_y = tbBodyRect.height / 2
    pMainBody:setPosition(float_body_x, float_body_y)
    cc_layer:addChild(pMainBody)
    self.test_polygon = pMainBody

    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetBoxBody(pMainBody, tbBodyRect.width / 2, tbBodyRect.height / 2, m, 0, 0, 0)


    local touchBeginPoint = nil
    local touchStartPoint = nil
    local function onTouchBegan(x, y)
        touchBeginPoint = {x = x, y = y}
        touchStartPoint = {x = x, y = y}
        local nX, nY = cc_layer:getPosition()
        return true
    end

    local function onTouchMoved(x, y)
        if touchBeginPoint then
            local nX, nY = cc_layer:getPosition()

            local nNewX, nNewY = nX + x - touchBeginPoint.x, nY + y - touchBeginPoint.y
            cc_layer:setPosition(nNewX, nNewY)

            touchBeginPoint = {x = x, y = y}
        end
    end

    local function onTouchEnded(x, y)
         local nX, nY = cc_layer:getPosition()
         if x == touchStartPoint.x and y == touchStartPoint.y then
         	self:BreakPolygon(x - nX, y - nY)
         end
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

function Scene:BreakPolygon(x, y)
	local polygon = self.test_polygon
    
end