--=======================================================================
-- File Name    : game_scene.lua
-- Creator      : yestein(yestein86@gmail.com)
-- Date         : 2013-11-29 21:16:43
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("GameScene", 1)

function Scene:_Uninit()

end

function Scene:Create()
	local sceneGame = self:GetCCObj()
	if not sceneGame then
		return
	end
	
	local cc_layer = cc.Layer:create()
	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()
	
    self.cc_cc_layer = cc_layer
    local bg = cc.Sprite:create("image/background.png")
    local bgRect = bg:getTextureRect()
    bg:setPosition(tbVisibleSize.width / 2, bgRect.height / 2)
    cc_layer:addChild(bg)
    
	
    local node = cc.Sprite:create("image/map.png")
	local tbRect = node:getTextureRect()
    local clippingNodeBG = cc.ClippingNode:create(node)
    node:setPosition(tbVisibleSize.width / 2, tbVisibleSize.height / 2)
   	clippingNodeBG:setAlphaThreshold(0.05)
    clippingNodeBG:setInverted(false)
    
    
    local clippingNode = cc.ClippingNode:create(node)
   	clippingNode:setAlphaThreshold(0.05)
    clippingNode:setInverted(true)
    
    clippingNode:addChild(node)
    
    local pHole = cc.Node:create()
    clippingNode:setStencil(pHole)

    local pEdge = cc.Node:create()
    clippingNode:addChild(pEdge)
    
    local touchBeginPoint = nil
	local touchStartPoint = nil
    local function onTouchBegan(x, y)
        touchBeginPoint = {x = x, y = y}
        touchStartPoint = {x = x, y = y}
        return true
    end

    local function onTouchMoved(x, y)
    end

    local function onTouchEnded(x, y)
        local cx, cy = cc_layer:getPosition()
        local pSprite = cc.Sprite:create("image/hole-erase.png")
        pSprite:setPosition(x - cx, y - cy) 
        pHole:addChild(pSprite)
        
        local pSpriteEdge = cc.Sprite:create("image/hole-edge.png")
        pSpriteEdge:setPosition(x - cx, y - cy) 
        pEdge:addChild(pSpriteEdge)
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
    cc_layer:addChild(clippingNodeBG)
    clippingNodeBG:addChild(clippingNode)

	Event:FireEvent("SceneCreate", self:GetClassName(), self:GetName())
    return cc_layer
end