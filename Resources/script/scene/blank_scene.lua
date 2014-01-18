--=======================================================================
-- File Name    : blank_scene.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-01-18
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("BlankScene", 1)

function Scene:_Uninit()

end

function Scene:_Init()
	return 1
end