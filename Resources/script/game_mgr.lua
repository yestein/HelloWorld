--=======================================================================
-- File Name    : game_mgr.lua
-- Creator      : yestein(yestein86@gmail.com)
-- Date         : 2013-09-26 13:40:31
-- Description  :
-- Modify       :
--=======================================================================

if not GameMgr then
	GameMgr = {}
end

local szMenuFontName = "MarkerFelt-Thin"
if device == "win32" then
	szMenuFontName = "Microsoft Yahei"
end
function GameMgr:Init()

end

function GameMgr:StartNormalScene(szSceneName)
    -- run
    local tbVisibleSize = CCDirector:getInstance():getVisibleSize()
	local tbScene = SceneMgr:GetScene(szSceneName)
	local scene = nil
	if not tbScene then
		tbScene = SceneMgr:CreateScene(szSceneName, szSceneName)
	    scene = tbScene:GetCCObj()    
	    local layerWorld = tbScene:Create()
		scene:addChild(layerWorld, Def.ZOOM_LEVEL_WORLD)
	    self.layerWorld = layerWorld
		
	    self:AddReturnMenu(scene, szSceneName)
	    Performance:Init(layerWorld)
	end
	scene = tbScene:GetCCObj()
	
	CCDirector:getInstance():pushScene(scene)
end

function GameMgr:StartPhysicsScene(szSceneName, z_level_debug_layer)
    local tbScene = SceneMgr:GetScene(szSceneName)
    local scene = nil
    if not tbScene then
		tbScene = SceneMgr:CreateScene(szSceneName, szSceneName)
		scene = tbScene:GetCCObj()    
		local PhysicsWorld = GamePhysicsWorld:GetInstance()
	    local layerWorld = tbScene:Create()
		scene:addChild(layerWorld, Def.ZOOM_LEVEL_WORLD)

	    self.layerWorld = layerWorld
	    if _DEBUG then
	        local layerDebugPhysics = DebugPhysicsLayer:create()
	        if z_level_debug_layer then
	        	layerWorld:addChild(layerDebugPhysics, z_level_debug_layer)
	        else
	        	layerWorld:addChild(layerDebugPhysics)
	        end
	    end
	    self:AddReturnMenu(scene, szSceneName)
	end
	scene = tbScene:GetCCObj()
	CCDirector:getInstance():pushScene(scene)
end

function GameMgr:AddReturnMenu(scene, szSceneName)
	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()
	local layerMenu = MenuMgr:CreateMenu(szSceneName)
    layerMenu:setPosition(tbVisibleSize.width, tbVisibleSize.height)
    scene:addChild(layerMenu, Def.ZOOM_LEVEL_MENU)
    local tbElement = {
	    [1] = {
	        [1] = {
				szNormal   = "ui/Icon.png",
				szSelected = "ui/Icon.png",
	        	fnCallBack = function()
	        		SceneMgr:DestroyScene(szSceneName)
	        		CCDirector:getInstance():popScene()
	        	end,
	        },
	    },
	}
    MenuMgr:UpdateByImage(szSceneName, tbElement, 
    	{szAlignType = "right", nIntervalX = 20}
    )
end

function GameMgr:TestCocoStudio()
	local tbScene = SceneMgr:CreateScene("TestCocoStudio", "GameScene")
	local cc_scene = tbScene:GetCCObj()
	self:AddReturnMenu(cc_scene, "TestCocoStudio")
	local cc_layer = cc.Layer:create()
	cc_scene:addChild(cc_layer)

	local uilayer_control = Ui:LoadJson(cc_layer, "control/control.ExportJson")
	self.uilayer_control = uilayer_control
	local function OnButtonEvent(widget_button, event)
		tbScene:SysMsg(string.format("%s %d", widget_button:getName(), event), "yellow")
	end
	local tb_button_list = {"button_left", "button_right", "button_up", "button_down", "button_luanch"}
	for _, str_button_name in ipairs(tb_button_list) do
		local button = uilayer_control:getWidgetByName(str_button_name)
		if button then
			button:addTouchEventListener(OnButtonEvent)
		else
			print(str_button_name)
			assert(false)
		end
	end
	CCDirector:getInstance():pushScene(cc_scene); 
end
