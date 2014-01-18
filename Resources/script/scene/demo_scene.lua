--===================================================
-- File Name    : demo_scene.lua
-- Creator      : yulei(yulei1@kingsoft.com)
-- Date         : 2014-01-09 17:56:00
-- Modify       :
--===================================================

local Scene = SceneMgr:GetClass("DemoScene", 1)
Scene.can_touch = 1 --可接受触摸事件
Scene.can_pick = 1 --可用鼠标拖拽物理刚体
Scene.can_drag = 1 --可拖拽屏幕
Scene.limit_drag = 1 --拖拽屏幕是否受限制（仅在场景范围内拖拽）

Scene:DeclareListenEvent("Bomb", "OnBomb")
Scene:DeclareListenEvent("WeaponRotate", "OnWeaponRotate")
Scene:DeclareListenEvent("PowerChanged", "OnPowerChanged")
Scene:DeclareListenEvent("Attack", "OnAttack")

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Scene:_Uninit()
	BattleLogic:Uninit()
end

function Scene:_Init()
	local num_ret_code = 0
	local tb_size_visible = CCDirector:getInstance():getVisibleSize()
	local width_visible = tb_size_visible.width
	local height_visible = tb_size_visible.height

	local cc_layer_main = self:GetLayer("main")
	self:LoadControlUI()

	self:CreateMap()

    local tb_param = {
    	str_body = "tank",
    	str_weapon = "tank_weapon",
	}
    self.tb_player = self:BuildTank(200, 425, tb_param)
    self.tb_enemy = self:BuildTank(796, 409, tb_param)

    BattleLogic:Init(self.tb_player, self.tb_enemy)
    return 1
end

function Scene:OnClick(x, y)
	print(x, y)
end

function Scene:CreateMap()
	local cc_layer_main = self:GetLayer("main")
	local width_scene = 0    
    local height_scene = 0

    local physics_sprite_ground = GameSprite:create(Def.str_ground_img)
	local rect_map = physics_sprite_ground:getTextureRect()
    local position_x = rect_map.width * 0.5
    local position_y = rect_map.height * 0.5
    physics_sprite_ground:setPosition(position_x, position_y)
    self:SetGroundSprite(physics_sprite_ground)
    local offset_x = 0
	local offset_y = 0
	local bool_dynamic = 0   
    num_ret_code = PhysicsWorld:SetPolygonBodyWithShapeName(physics_sprite_ground, "map_ground", offset_x, offset_y, bool_dynamic)
   	assert(num_ret_code == 1)

   	-- 用于蒙版遮罩
    local cc_clipping_background = cc.ClippingNode:create(physics_sprite_ground)
    cc_clipping_background:setAlphaThreshold(0.05)
    cc_clipping_background:setInverted(false)    
    
    local cc_clipping_map_ground = cc.ClippingNode:create(physics_sprite_ground)
    cc_clipping_map_ground:setAlphaThreshold(0.05)
    cc_clipping_map_ground:setInverted(true)    

    local pHole = cc.Node:create()
    cc_clipping_map_ground:setStencil(pHole)
    self.pHole = pHole

    local pEdge = cc.Node:create()
    cc_clipping_map_ground:addChild(pEdge)
    self.pEdge = pEdge    

    cc_layer_main:addChild(cc_clipping_background, Def.ZOOM_LEVEL_WORLD)
    cc_clipping_background:addChild(cc_clipping_map_ground)
    cc_clipping_map_ground:addChild(physics_sprite_ground)
	
	local cc_sprite_background = cc.Sprite:create("image/background.png")
    local rect_raw_background = cc_sprite_background:getTextureRect()
    cc_sprite_background:setAnchorPoint(cc.p(0, 0))
    
    width_scene = rect_raw_background.width
    height_scene = rect_raw_background.height

    self:SetWidth(width_scene)
	self:SetHeight(height_scene)

	cc_layer_main:addChild(cc_sprite_background)

	num_ret_code = PhysicsWorld:CreateRectEdge(0, width_scene, 0, height_scene)
    assert(num_ret_code == 1)
end

function Scene:BuildTank(tank_x, tank_y, tb_param)
	local tb_ret = {}
	local str_body = tb_param.str_body
	if not str_body then
		assert(false)
		return
	end
	local cc_layer_main = self:GetLayer("main")
	local physics_sprite_body, width_body, height_body = Physics:CreatePolygonSprite(str_body, tank_x, tank_y)
   
    cc_layer_main:addChild(physics_sprite_body, Def.ZOOM_LEVEL_WORLD)

	tb_ret.body = physics_sprite_body

    local str_weapon = tb_param.str_weapon
    if str_weapon then
	    local cc_sprite_weapon = GameSprite:create(string.format("image/%s.png", str_weapon))
	    local width_weapon = cc_sprite_weapon:getContentSize().width * 0.5
	    local height_weapon = cc_sprite_weapon:getContentSize().height * 0.5
	    local weapon_x = 15;
	    local weapon_y = 40;
	    cc_sprite_weapon:setAnchorPoint(cc.p(5 / width_weapon, 0.5))
	    cc_sprite_weapon:setPosition(weapon_x, weapon_y)
	    cc_sprite_weapon:setRotation(-45)
	    physics_sprite_body:addChild(cc_sprite_weapon)

	    -- local weapon_x = tank_x
	    -- local weapon_y = tank_y
	    -- local material = GamePhysicsWorld.MATERIAL:new(2, 0.2, 0.5)
	    -- local physics_sprite_weapon, width_weapon, height_weapon = self:CreateBoxCommpent(str_weapon, weapon_x, weapon_y, material)
	    -- tb_ret.weapon = physics_sprite_weapon

	    -- local b2body = physics_sprite_weapon:GetB2Body()
	    -- b2body:SetGravityScale(0)

	    -- local bool_enable_limit = 1
	    -- local max_angel = 3.14
	    -- local min_angel = 0
	    -- local motor_speed = 10
	    -- local motor_torque = 0
	    -- local joint_id = PhysicsWorld:CreateRevoluteJoint(
		   --  physics_sprite_body, -30, 10,
		   --  physics_sprite_weapon, -width_weapon * 0.5 + 5, 0,
		   --  bool_enable_limit, min_angel, max_angel, motor_speed, motor_torque)
		tb_ret.weapon = cc_sprite_weapon
	end

    return tb_ret
end

function Scene:LoadControlUI()
	local tb_ui = self:GetUI()
	if not tb_ui then
		return
	end
	local cc_layer = Ui:GetLayer(tb_ui)
	local uilayer_control = Ui:LoadJson(cc_layer, "ui/control/control.ExportJson")
	self.uilayer_control = uilayer_control
	local function OnButtonEvent(widget_button, event)
		local func = self.func_button_event[event]
		if func then
			func(self, widget_button)
		end
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
end

function Scene:OnWeaponRotate(rotation)
	local label_angel = self.uilayer_control:getWidgetByName("label_angel")
	if not label_angel then
		assert(false)
		return
	end	
	label_angel = tolua.cast(label_angel, "UILabelAtlas")
	label_angel:setStringValue(tostring(-rotation))
end

function Scene:OnPowerChanged(power)
	local progressbar_power = self.uilayer_control:getWidgetByName("progressbar_power")
	if not progressbar_power then
		assert(false)
		return
	end	
	local label_power = self.uilayer_control:getWidgetByName("label_power")
	if not label_power then
		assert(false)
		return
	end	
	progressbar_power = tolua.cast(progressbar_power, "UILoadingBar")
	progressbar_power:setVisible(true)
	progressbar_power:setPercent(power)

	label_power = tolua.cast(label_power, "UILabelAtlas")
	label_power:setVisible(true)
	label_power:setStringValue(power)
end

function Scene:OnAttack(power)
	local progressbar_power = self.uilayer_control:getWidgetByName("progressbar_power")
	if not progressbar_power then
		assert(false)
		return
	end	
	local label_power = self.uilayer_control:getWidgetByName("label_power")
	if not label_power then
		assert(false)
		return
	end	

	local cc_layer_main = self:GetLayer("main")
    local material = GamePhysicsWorld.MATERIAL:new(4, 0, 0)

    local physics_sprite_bullet = BombSprite:create("image/bullet.png")
    local float_scale = 1
    local float_bullet_radius = physics_sprite_bullet:getContentSize().width * 0.25 * float_scale
    physics_sprite_bullet:Init(250, 500, 80)

    local weapon = self.tb_player.weapon
    local body = self.tb_player.body
    local x, y = body:getPosition()

    physics_sprite_bullet:setPosition(x + 20, y + 50)
    physics_sprite_bullet:setScale(float_scale)
    cc_layer_main:addChild(physics_sprite_bullet, Def.ZOOM_LEVEL_WORLD)

    PhysicsWorld:SetCircleBody(
        physics_sprite_bullet, float_bullet_radius, 
        material, 0, 0, 1, 1)

    PhysicsWorld:SetBodyAngularVelocity(physics_sprite_bullet, 2)
    PhysicsWorld:ApplyImpulseByAngular(physics_sprite_bullet, -weapon:getRotation(), 100 + power * 10);
end

function Scene:SetGroundSprite(ground)
	self.physics_sprite_ground = ground
end

function Scene:GetGroundSprite()
	return self.physics_sprite_ground
end

function Scene:OnBomb(float_bomb_x, float_bomb_y)
	local ground = self:GetGroundSprite()
	local num_ret_code = PhysicsWorld:ClipperPolygonByCircle(ground, 30, 20, float_bomb_x, float_bomb_y)
	if num_ret_code == 1 then
	    local pSprite = cc.Sprite:create("image/hole-erase.png")
	    pSprite:setPosition(float_bomb_x, float_bomb_y) 
	    self.pHole:addChild(pSprite)
	    
	    local pSpriteEdge = cc.Sprite:create("image/hole-edge.png")
	    pSpriteEdge:setPosition(float_bomb_x, float_bomb_y) 
	    self.pEdge:addChild(pSpriteEdge)
	end
end

function Scene:OnButtonBegan(widget_button)
	local str_button_name = widget_button:getName()
	if str_button_name == "button_left" then
		BattleLogic:StartMove("left")
	elseif str_button_name == "button_right" then
		BattleLogic:StartMove("right")
	elseif str_button_name == "button_up" then
		BattleLogic:StartAdjust("up")
	elseif str_button_name == "button_down" then
		BattleLogic:StartAdjust("down")
	elseif str_button_name == "button_luanch" then
		BattleLogic:ReadyToAttack()
	end
end
function Scene:OnButtonMoved(widget_button)

end
function Scene:OnButtonEnded(widget_button)
	local str_button_name = widget_button:getName()
	if str_button_name == "button_left" then
		BattleLogic:StopMove()
	elseif str_button_name == "button_right" then
		BattleLogic:StopMove()
	elseif str_button_name == "button_up" then
		BattleLogic:StopAdjust()
	elseif str_button_name == "button_down" then
		BattleLogic:StopAdjust()
	elseif str_button_name == "button_luanch" then
		BattleLogic:Attack()
	end
end
function Scene:OnButtonCanceled(widget_button)
	local str_button_name = widget_button:getName()
	if str_button_name == "button_left" then
		BattleLogic:StopMove()
	elseif str_button_name == "button_right" then
		BattleLogic:StopMove()
	elseif str_button_name == "button_up" then
		BattleLogic:StopAdjust()
	elseif str_button_name == "button_down" then
		BattleLogic:StopAdjust()
	elseif str_button_name == "button_luanch" then
		BattleLogic:Attack()
	end
end

Scene.func_button_event = {
	[Ui.TOUCH_EVENT_BEGAN] = Scene.OnButtonBegan,
	[Ui.TOUCH_EVENT_MOVED] = Scene.OnButtonMoved,
	[Ui.TOUCH_EVENT_ENDED] = Scene.OnButtonEnded,
	[Ui.TOUCH_EVENT_CANCELED] = Scene.OnButtonCanceled,
}
