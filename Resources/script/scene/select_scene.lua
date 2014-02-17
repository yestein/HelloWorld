--=======================================================================
-- File Name    : select_scene.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  :
-- Modify       :
--=======================================================================

local Scene = SceneMgr:GetClass("SelectScene", 1)
Scene.property = {
	can_touch     = 1, --可接受触摸事件
}
function Scene:_Uninit()

end

function Scene:_Init()
	return 1
end

function Scene:OnTouchBegan(x, y)
    return Physics:OnMouseDown(x, y)
end

function Scene:OnTouchMoved(x, y)
    return Physics:OnMouseMoved(x, y)
end

function Scene:OnTouchEnded(x, y)
    Physics:OnMouseEnded(x, y)
    return self:BreakPolygon(x, y)
end

