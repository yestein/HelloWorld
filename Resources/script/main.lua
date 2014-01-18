--===================================================
-- File Name    : main.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2013-08-07 13:06:54
-- Description  :
-- Modify       :
--===================================================


-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

require("script/preload.lua")

function cclog(...)
    print(string.format(...))
end

function CPPEvent(...)
	Event:FireEvent(...)
end

local function mainLoop(delta)
	local tbModule = nil
	function ModulLoop()
		tbModule:OnLoop(delta)
	end
	tbModule = Physics
	xpcall(ModulLoop, __G__TRACKBACK__)

	tbModule = SceneMgr
	xpcall(ModulLoop, __G__TRACKBACK__)

	tbModule = GameMgr
	xpcall(ModulLoop, __G__TRACKBACK__)
end

local function main()
	print("Main Start")
	-- avoid memory leak
	collectgarbage("setpause", 100)
	collectgarbage("setstepmul", 5000)

	math.randomseed(os.time())
	math.random(100)

	assert(Event:Preload() == 1)
	if _DEBUG then
    	assert(Debug:Init(Debug.MODE_BLACK_LIST) == 1)
    end
    
	assert(GameMgr:Init() == 1)
    assert(SceneMgr:Init() == 1)
    assert(MenuMgr:Init() == 1)
    assert(Ui:Init() == 1)
    assert(Physics:Init() == 1)

    if _DEBUG then
    	assert(SceneMgr:CheckAllClass() == 1)
    end

    CCDirector:getInstance():getScheduler():scheduleScriptFunc(mainLoop, 0, false)
	local tbMainScene = SceneMgr:CreateScene("MainScene", "MainScene")
	assert(tbMainScene)
	local cc_scene = tbMainScene:GetCCObj()
	assert(cc_scene)
    CCDirector:getInstance():runWithScene(cc_scene)
end
xpcall(main, __G__TRACKBACK__)
