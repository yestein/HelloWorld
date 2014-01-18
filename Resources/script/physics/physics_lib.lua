--=======================================================================
-- File Name    : physics_lib.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-1-18 
-- Description  : 更方便的使用物理引擎
-- Modify       :
--=======================================================================
if not Physics then
	Physics = {}
end

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Physics:CreatePolygonSprite(str_polygon_name, x, y)
	local str_image_path = self:GetImagePath(str_polygon_name)
	local physics_sprite = GameSprite:create(str_image_path)
	physics_sprite:setPosition(x, y)
    local width_sprite = physics_sprite:getContentSize().width
    local height_sprite = physics_sprite:getContentSize().height
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    assert(PhysicsWorld:SetPolygonBodyWithShapeName(physics_sprite, str_polygon_name, offset_x, offset_y, bool_dynamic) == 1)
    return physics_sprite, width_sprite, height_sprite
end

function Physics:CreateBoxSprite(str_image_path, x, y, density, friction, restitution, scale)
	if not scale then
		scale = 1
	end
	local physics_sprite = GameSprite:create(str_image_path)
	physics_sprite:setPosition(x, y)
    local width_sprite = physics_sprite:getContentSize().width * scale
    local height_sprite = physics_sprite:getContentSize().height * scale
    if scale ~= 1 then
    	physics_sprite:setScale(scale)
    end
    local width_physics = width_sprite * 0.5
   	local height_physics = height_sprite * 0.5
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    local material = GamePhysicsWorld.MATERIAL:new(density, friction, restitution)
    PhysicsWorld:SetBoxBody(physics_sprite, width_physics, height_physics, material, offset_x, offset_y, bool_dynamic)
    return physics_sprite, width_sprite, height_sprite
end


function Physics:GetImagePath(str_polygon_name)
	return string.format("image/%s.png", str_polygon_name)
end