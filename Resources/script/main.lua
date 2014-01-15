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

require("preload")

local sharedDirector = CCDirector:getInstance()
local sharedEngine = SimpleAudioEngine:getInstance()
local sharedFileUtils = CCFileUtils:getInstance()

local tbVisibleSize = sharedDirector:getVisibleSize()
local tbOrigin = sharedDirector:getVisibleOrigin()
local nOffsetX, nOffsetY = 0, 0

function cclog(...)
    print(string.format(...))
end

function CPPEvent(szEvent, physics_sprite)
	Event:FireEvent(szEvent, physics_sprite)
end

local function main()
	print("Main Start")
	-- avoid memory leak
	collectgarbage("setpause", 100)
	collectgarbage("setstepmul", 5000)
	
	-- play background music, preload effect
	
	-- uncomment below for the BlackBerry version
	-- local bgMusicPath = sharedFileUtils:fullPathForFilename("background.ogg")
	-- local bgMusicPath = sharedFileUtils:fullPathForFilename("1.mp3")
	-- sharedEngine:playBackgroundMusic(bgMusicPath, true)
	-- local effectPath = sharedFileUtils:fullPathForFilename("effect1.wav")
	-- sharedEngine:preloadEffect(effectPath)
	
	math.randomseed(os.time())
	math.random(100)
	Event:Preload()
    Debug:Init(Debug.MODE_BLACK_LIST)
    
	GameMgr:Init()
    SceneMgr:Init()
    MenuMgr:Init()
    Ui:Init()
    GamePhysicsWorld:GetInstance():Init(0, -20)
    
	local tbMainScene = SceneMgr:CreateScene("MainScene", "MainScene")
	local sceneMain = tbMainScene:GetCCObj()
	local layerBG = tbMainScene:Create()
	sceneMain:addChild(layerBG, Def.ZOOM_LEVEL_WORLD)

	local layerMainMenu = MenuMgr:CreateMenu("MainMenu")
	layerMainMenu:setPosition(20, tbVisibleSize.height - 80)
    sceneMain:addChild(layerMainMenu, Def.ZOOM_LEVEL_MENU)
    local tbElement = {
    	[1] = {
	    	[1] = {
	        	szItemName = "运行Demo",
	        	fnCallBack = function()
	        		GameMgr:StartPhysicsScene("DemoScene")
	        	end,
	        },
	    },
	    [2] = {
	        [1] = {
	        	szItemName = "弹坑测试",
	        	fnCallBack = function()
	        		GameMgr:StartNormalScene("GameScene")
	        	end,
	        },
	    },	    
	    [3] = {
	    	[1] = {
	        	szItemName = "物理引擎测试",
	        	fnCallBack = function()
	        		GameMgr:StartPhysicsScene("PhysicsScene")
	        	end,
	        },
	    },
	    [4] = {
	    	[1] = {
	        	szItemName = "cocoStudio测试用",
	        	fnCallBack = function()
	        		GameMgr:TestCocoStudio()
	        	end,
	        },
		},
		[5] = {
	    	[1] = {
	        	szItemName = "机械构建测试",
	        	fnCallBack = function()
	        		tbMainScene:SysMsg("功能暂未开放", "red")
	        	end,
	        },
		},
		[6] = {
	    	[1] = {
	        	szItemName = "详细爆炸受力分析测试",
	        	fnCallBack = function()
	        		tbMainScene:SysMsg("功能暂未开放", "red")
	        	end,
	        },
		},
		[7] = {
	    	[1] = {
	        	szItemName = "AI测试",
	        	fnCallBack = function()
	        		tbMainScene:SysMsg("功能暂未开放", "red")
	        	end,
	        },
		},
		[8] = {
	    	[1] = {
	        	szItemName = "联机测试",
	        	fnCallBack = function()
	        		tbMainScene:SysMsg("功能暂未开放", "red")
	        	end,
	        },
		},
    }
    MenuMgr:UpdateByString("MainMenu", tbElement, 
    	{szFontName = Def.szMenuFontName, nSize = 26, szAlignType = "left", nIntervalX = 20, nIntervalY = 20}
    )
    local tb_ui = tbMainScene:GetUI()
    Ui:AddElement(tb_ui, "LabelTTF", "Title", tbVisibleSize.width / 2, tbVisibleSize.height -50, "Demo功能一览", nil, 40)
    sharedDirector:runWithScene(sceneMain)
end

function test(n)
	print(n)
end

xpcall(main, __G__TRACKBACK__)
