--===================================================
-- File Name    : define.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2013-08-07 13:06:59
-- Description  :
-- Modify       :
--===================================================

if not Def then
	Def = {}
end

local Id = 1
local function Accumulate(nId)
	if nId then
		Id = nId
	else
		Id = Id + 1
	end
	return Id
end

Def.szMenuFontName = "MarkerFelt-Thin"
if device == "win32" then
	Def.szMenuFontName = "Microsoft Yahei"
end

Def.ZOOM_LEVEL_WORLD = 1
Def.ZOOM_LEVEL_BULLET = 2
Def.ZOOM_LEVEL_TITLE = 3
Def.ZOOM_LEVEL_PERFORMANCE = 4
Def.ZOOM_LEVEL_MENU = 5
Def.ZOOM_LEVEL_SUB_MENU = 6

Def.tbColor = {
	["black"] = cc.c3b(255, 255, 255),
	["red"]   = cc.c3b(255, 0, 0),
	["green"] = cc.c3b(0, 255, 0),
	["blue"]  = cc.c3b(0, 0, 255),
	["white"] = cc.c3b(0, 0, 0),
	["yellow"] = cc.c3b(255, 255, 0),
}

Def.szBGImg     = "image/background.png"
Def.szTitleFile = "image/ui/title_bg.png"
Def.szFightImg  = "image/icon.png"
Def.szMainBGImg = "image/main.png"

