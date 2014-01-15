--===================================================
-- File Name    : preload.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2013-08-07 13:07:04
-- Description  :
-- Modify       :
--===================================================

if not _G.Def then
	_G.Def = {}
end

if not _G.Event then
	_G.Event = {}
end

if not _G.Misc then
	_G.Misc = {}
end

if not _G.GameMgr then
	_G.GameMgr = {}
end

if not _G.Lib then
	_G.Lib = {}
end

if not _G.MenuMgr then
	_G.MenuMgr = {}
end

if not _G.SceneMgr then
	_G.SceneMgr = {}
end

if not _G.Debug then
	_G.Debug  = {}
end

if not _G.Performance then
	_G.Performance  = {}
end

require("define")
require("misc_math")
require("lib")
require("event")
require("dbg")
require("performance")
require("game_mgr")
require("menu")
require("scene_mgr")
require("scene_base")
require("game_scene")
require("physics_scene")
require("main_scene")
require("ui")
require("demo_scene")
require("battle_logic")



