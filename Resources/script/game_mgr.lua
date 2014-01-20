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

GameMgr.LOGIC_FPS = 25
GameMgr.TIME_PER_FRAME = 1 / GameMgr.LOGIC_FPS
local PhysicsWorld = GamePhysicsWorld:GetInstance()

function GameMgr:Init()
	GameMgr.num_frame = 0
	GameMgr.accumulate = 0
	return 1
end

function GameMgr:OnLoop(delta)
	self.accumulate = self.accumulate + delta
	if self.accumulate > self.TIME_PER_FRAME then
		self.num_frame = self.num_frame + 1
		self:OnActive(self.num_frame)
		self.accumulate = self.accumulate - self.TIME_PER_FRAME
	end
end

function GameMgr:OnActive(num_frame)
	BattleLogic:OnActive(num_frame)
end

function GameMgr:GetCurrentFrame()
	return self.num_frame
end

function GameMgr:LoadScene(szSceneName)
    local tb_scene = SceneMgr:GetScene(szSceneName)
    if not tb_scene then
		tb_scene = SceneMgr:CreateScene(szSceneName, szSceneName)
	end
	local cc_scene = tb_scene:GetCCObj()
	CCDirector:getInstance():pushScene(cc_scene)
	return tb_scene
end

function GameMgr:TestCocoStudio()
	local tb_scene = SceneMgr:CreateScene("TestCocoStudio", "BlankScene")
	assert(tb_scene)
	local cc_scene = tb_scene:GetCCObj()
	assert(cc_scene)
	local cc_layer = tb_scene:GetLayer("main")
	assert(cc_layer)

	local uilayer_control = Ui:LoadJson(cc_layer, "ui/control/control.ExportJson")
	assert(uilayer_control)
	self.uilayer_control = uilayer_control
	local function OnButtonEvent(widget_button, event)
		tb_scene:SysMsg(string.format("%s %d", widget_button:getName(), event), "yellow")
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
	CCDirector:getInstance():pushScene(cc_scene)
end
