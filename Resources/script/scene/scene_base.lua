--=======================================================================
-- File Name    : scene_base.lua
-- Creator      : yestein(yestein86@gmail.com)
-- Date         : 2013-11-29 21:16:43
-- Description  :
-- Modify       :
--=======================================================================

if not SceneMgr then
	SceneMgr = {}
end
if not SceneMgr._SceneBase then
	SceneMgr._SceneBase = {}
end

local SceneBase = SceneMgr._SceneBase
local PhysicsWorld = GamePhysicsWorld:GetInstance()
local tb_visible_size = CCDirector:getInstance():getVisibleSize()

function SceneBase:DeclareListenEvent(str_event, str_func)
	self.tb_event_listen[str_event] = str_func
end

function SceneBase:Init(str_scene_name)

	self.str_scene_name = str_scene_name
	self.PhysicsWorld = GamePhysicsWorld:GetInstance()
	self.cc_scene = cc.Scene:create()
	self.tb_cc_layer = {}
	self.tb_reg_event = {}

	-- 场景默认设为屏幕大小
	self:SetWidth(tb_visible_size.width)
	self:SetHeight(tb_visible_size.height)

	self:RegisterEventListen()
	Ui:InitScene(str_scene_name, self.cc_scene)
	self:AddReturnMenu()
	self:CreateLayer("main", Def.ZOOM_LEVEL_WORLD)
	self:_Init()

	if self.can_touch == 1 then
		self:RegisterTouchEvent()
	end

	Event:FireEvent("SceneCreate", self:GetClassName(), self:GetName())
end

function SceneBase:Uninit()
	Event:FireEvent("SceneDestroy", self:GetClassName(), self:GetName())
	self:_Uninit()
	self:RemoveReturnMenu()
	Ui:UninitScene(self.str_scene_name)
	self:UnregisterEventListen()
	self.tb_reg_event = nil
	self.tb_cc_layer = nil
	self.cc_scene = nil
	self.PhysicsWorld = nil
	self.str_scene_name = nil
end

function SceneBase:SetWidth(width)
	self.width = width
end
function SceneBase:SetHeight(height)
	self.height = height
end

function SceneBase:GetWidth()
	return self.width
end

function SceneBase:GetHeight()
	return self.height
end

function SceneBase:GetPhysicsWorld()
	return self.PhysicsWorld
end

function SceneBase:CreateLayer(str_layer_name, z_level)
	if self.tb_cc_layer[str_layer_name] then
		cclog("Layer [%s] create Failed! Already Exists", str_layer_name)
		return nil
	end
	local cc_layer = cc.Layer:create()
	assert(self:AddLayer(str_layer_name, cc_layer, z_level) == 1)
	return cc_layer
end

function SceneBase:AddLayer(str_layer_name, cc_layer, z_level)
	if self.tb_cc_layer[str_layer_name] then
		cclog("Layer [%s] create Failed! Already Exists", str_layer_name)
		return nil
	end
	if z_level then 
		if z_level > 0 then
			self.cc_scene:addChild(cc_layer, z_level)
		end
	else
		self.cc_scene:addChild(cc_layer)
	end
	self.tb_cc_layer[str_layer_name] = cc_layer
	return 1
end

function SceneBase:GetLayer(str_layer_name)
	return self.tb_cc_layer[str_layer_name]
end

function SceneBase:RegisterEventListen()
	for str_event, str_func in pairs(self.tb_event_listen) do
		if not self.tb_reg_event[str_event] then
			local id_reg = Event:RegistEvent(str_event, self[str_func], self)
			self.tb_reg_event[str_event] = id_reg
		else
			assert(false)
		end
	end
end

function SceneBase:UnregisterEventListen()
	for str_event, id_reg in pairs(self.tb_reg_event) do
		Event:UnRegistEvent(str_event, id_reg)
	end
	self.tb_reg_event = {}
end

function SceneBase:GetUI()
	return Ui:GetSceneUi(self:GetName())
end

function SceneBase:GetClassName()
	return self.str_class_name
end

function SceneBase:GetName()
	return self.str_scene_name
end

function SceneBase:GetCCObj()
	return self.cc_scene
end

function SceneBase:SysMsg(szMsg, str_color)
	local tb_ui = self:GetUI()
	if tb_ui then
		Ui:SysMsg(tb_ui, szMsg, str_color)
	end
end

function SceneBase:AddReturnMenu()
	local str_name = self:GetName()
	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()
	local layerMenu = MenuMgr:CreateMenu(str_name)
    layerMenu:setPosition(tbVisibleSize.width, tbVisibleSize.height)
    self.cc_scene:addChild(layerMenu, Def.ZOOM_LEVEL_MENU)
    local tbElement = {
	    [1] = {
	        [1] = {
				szNormal   = "image/icon.png",
				szSelected = "image/Icon.png",
	        	fnCallBack = function()
	        		SceneMgr:DestroyScene(str_name)
	        		CCDirector:getInstance():popScene()
	        	end,
	        },
	    },
	}
    MenuMgr:UpdateByImage(str_name, tbElement, 
    	{szAlignType = "right", nIntervalX = 20}
    )
end

function SceneBase:RemoveReturnMenu()
	local str_name = self:GetName()
	MenuMgr:DestroyMenu(str_name)
end

function SceneBase:RegisterTouchEvent(bool_can_pick)
	local cc_layer_main = self:GetLayer("main")
	local touchBeginPoint = nil
    local touchStartPoint = nil

    local function onTouchBegan(x, y)
        touchBeginPoint = {x = x, y = y}
        touchStartPoint = {x = x, y = y}
        local nX, nY = cc_layer_main:getPosition()
        if self.can_pick == 1 then
        	PhysicsWorld:MouseDown(x - nX,  y - nY)
        end
        return true
    end

    local function onTouchMoved(x, y)
        if touchBeginPoint then
            local layer_x, layer_y = cc_layer_main:getPosition()
            local bool_pick = 0
            if self.can_pick == 1 then
             	if PhysicsWorld:MouseMove(x - layer_x,  y - layer_y) == 1 then
             		bool_pick = 1
             	end
            end
            if bool_pick ~= 1 and self.can_drag == 1 then
                local nNewX, nNewY = layer_x + x - touchBeginPoint.x, layer_y + y - touchBeginPoint.y
                if self.limit_drag == 1 then
	                local nMinX, nMaxX = tb_visible_size.width - self:GetWidth() , 0
	                local nMinY, nMaxY = tb_visible_size.height - self:GetHeight(),  0
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
	            end
                cc_layer_main:setPosition(nNewX, nNewY)

                touchBeginPoint = {x = x, y = y}
            end
        end
    end

    local function onTouchEnded(x, y)
        local nX, nY = cc_layer_main:getPosition()
        if x == touchStartPoint.x and y == touchStartPoint.y then
        	if self.OnClick then
        		self:OnClick(x - nX, y - nY)
        	end
        end
        if self.can_pick == 1 then
        	PhysicsWorld:MouseUp(x - nX,  y - nY)
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

    cc_layer_main:registerScriptTouchHandler(onTouch)
    cc_layer_main:setTouchEnabled(true)
end