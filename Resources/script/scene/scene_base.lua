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

	if self:CanTouch() == 1 then
		self:RegisterTouchEvent()
	end

	if self:IsDebugPhysics() == 1 then
	    	local layer_main = self:GetLayer("main")
	        local layer_debug_phyiscs = DebugPhysicsLayer:create()

			layer_main:addChild(layer_debug_phyiscs, 10)

	    end

	Event:FireEvent("SceneCreate", self:GetClassName(), self:GetName())
end

function SceneBase:Uninit()
	Event:FireEvent("SceneDestroy", self:GetClassName(), self:GetName())
	self:_Uninit()
	local cc_layer_main = self:GetLayer("main")
	self.cc_scene:removeChild(cc_layer_main)
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
    local tbElement = nil
    if str_name ~= "MainScene" then
	    tbElement = {
		    [1] = {
		        [1] = {
					szItemName = "返回主菜单",
		        	fnCallBack = function()
		        		SceneMgr:DestroyScene(str_name)
		        		CCDirector:getInstance():popScene()
		        	end,
		        },
		        [2] = {
					szItemName = "重载脚本和场景",
		        	fnCallBack = function()
		        		self:Reload()
		        		SceneMgr:DestroyScene(str_name)
		        		CCDirector:getInstance():popScene()
						local tbScene = GameMgr:LoadScene(str_name)
						tbScene:SysMsg("重载完毕", "green")
		        	end,
		        },
		    },
		}
	else
		tbElement = {
		    [1] = {
		        [1] = {
					szItemName = "重载脚本",
		        	fnCallBack = function()
		        		self:Reload()
		        	end,
		        },
		    },
		}
	end
    MenuMgr:UpdateByString(str_name, tbElement, 
    	{szFontName = Def.szMenuFontName, nSize = 30, szAlignType = "right", nIntervalX = 20}
    )
end

function SceneBase:RemoveReturnMenu()
	local str_name = self:GetName()
	MenuMgr:DestroyMenu(str_name)
end

function SceneBase:IsDebugPhysics()
	if self.tb_property and self.tb_property.debug_physics == 1 then
		return 1
	end
end

function SceneBase:CanTouch()
	if self.tb_property and self.tb_property.can_touch == 1 then
		return 1
	end
	return 0
end

function SceneBase:CanPick()
	if self.tb_property and self.tb_property.can_pick == 1 then
		return 1
	end
	return 0
end

function SceneBase:CanDrag()
	if self.tb_property and self.tb_property.can_drag == 1 then
		return 1
	end
	return 0
end

function SceneBase:IsLimitDrag()
	if self.tb_property and self.tb_property.limit_drag == 1 then
		return 1
	end
	return 0
end

function SceneBase:RegisterTouchEvent()
	local cc_layer_main = self:GetLayer("main")
	local touchBeginPoint = nil
    local touchStartPoint = nil

    local function onTouchBegan(x, y)
        touchBeginPoint = {x = x, y = y}
        touchStartPoint = {x = x, y = y}
        local nX, nY = cc_layer_main:getPosition()
        if self:CanPick() == 1 then
        	PhysicsWorld:MouseDown(x - nX,  y - nY)
        end
        return true
    end

    local function onTouchMoved(x, y)
        if touchBeginPoint then
            local layer_x, layer_y = cc_layer_main:getPosition()
            local bool_pick = 0
            if self:CanPick() == 1 then
             	if PhysicsWorld:MouseMove(x - layer_x,  y - layer_y) == 1 then
             		bool_pick = 1
             	end
            end
            if bool_pick ~= 1 and self:CanDrag() == 1 then
                local new_layer_x, new_layer_y = layer_x + x - touchBeginPoint.x, layer_y + y - touchBeginPoint.y
                self:MoveMainLayer(new_layer_x, new_layer_y)

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
        if self:CanPick() == 1 then
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

function SceneBase:MoveCamera(x, y)
	local layer_x, layer_y = tb_visible_size.width / 2 - x, tb_visible_size.height / 2 - y
	return self:MoveMainLayer(layer_x, layer_y)
end

function SceneBase:MoveMainLayer(position_x, position_y)
	local cc_layer_main = self:GetLayer("main")
	assert(cc_layer_main)
	if self:IsLimitDrag() == 1 then
        position_x, position_y = self:GetModifyPosition(position_x, position_y)
    end
    cc_layer_main:setPosition(position_x, position_y)
end

function SceneBase:GetModifyPosition(position_x, position_y)
	local min_x, max_x = tb_visible_size.width - self:GetWidth() , 0
    local min_y, max_y = tb_visible_size.height - self:GetHeight(),  0
    if position_x < min_x then
        position_x = min_x
    elseif position_x > max_x then
        position_x = max_x
    end

    if position_y < min_y then
        position_y = min_y
    elseif position_y > max_y then
        position_y = max_y
    end
    return position_x, position_y
end

function SceneBase:Reload()
	function reload(str_file)
		dofile(str_file)
		print("Reload\t["..str_file.."]")
	end
	print("开始重载脚本...")
	reload("script/scene/scene_base.lua")
	reload("script/scene/scene_mgr.lua")
	reload("script/scene/demo_scene.lua")
	reload("script/scene/construct_scene.lua")
	reload("script/physics/physics_lib.lua")
	reload("script/physics/physics_mgr.lua")
	reload("script/battle_logic.lua")
	reload("script/game_mgr.lua")
	reload("script/lib.lua")
	reload("script/menu.lua")
	reload("script/misc_math.lua")
	reload("script/ui.lua")
	reload("script/define.lua")

	
	print("脚本重载完毕")
end