--===================================================
-- File Name    : demo_scene.lua
-- Creator      : yulei(yulei1@kingsoft.com)
-- Date         : 2014-01-09 17:56:00
-- Modify       :
--===================================================

local Scene = SceneMgr:GetClass("DemoScene", 1)
Scene.tb_property = {
	can_touch     = 1,--可接受触摸事件
	can_pick      = 1,--可用鼠标拖拽物理刚体
	can_drag      = 1,--可拖拽屏幕
	limit_drag    = 1,--拖拽屏幕是否受限制（仅在场景范围内拖拽）
	-- debug_physics = 1, --是否显示物理引擎调试绘制
}

Scene:DeclareListenEvent("Bomb", "OnBomb")
Scene:DeclareListenEvent("BeBomb", "OnBeBombed")
Scene:DeclareListenEvent("WeaponRotate", "OnWeaponRotate")
Scene:DeclareListenEvent("PowerChanged", "OnPowerChanged")
Scene:DeclareListenEvent("Attack", "OnAttack")

local PhysicsWorld = GamePhysicsWorld:GetInstance()
local tb_size_visible = CCDirector:getInstance():getVisibleSize()

function Scene:_Uninit()
	BattleLogic:Uninit()
end

function Scene:_Init()
	local num_ret_code = 0
	local width_visible = tb_size_visible.width
	local height_visible = tb_size_visible.height

	local cc_layer_main = self:GetLayer("main")
	self:LoadControlUI()

	self:CreateMap()

	self:SetFocus(0)
    local tb_param = {
    	str_body = "tank",
    	str_weapon = "tank_weapon",
	}
	local width_scene = self:GetWidth()
    self.tb_player = self:BuildTank(100, 200, tb_param)
    self.tb_enemy = self:BuildTank(width_scene / 2 + 300, 440, tb_param)

    local x, y = self.tb_player.body:getPosition()
	self:MoveCamera(x, y)

    BattleLogic:Init(self.tb_player, self.tb_enemy)
    return 1
end

function Scene:SetFocus(is_need_focus)
	self.is_need_focus = is_need_focus
end

function Scene:IsNeedFocus()
	return self.is_need_focus
end

function Scene:OnLoop(delta)
	if self.physics_sprite_bullet then
		local x, y = self.physics_sprite_bullet:getPosition()
		self:MoveCamera(x, y)
	elseif self:IsNeedFocus() == 1 and self.tb_player.body then
		local x, y = self.tb_player.body:getPosition()
		self:MoveCamera(x, y)
	end	
end

function Scene:OnClick(x, y)
	print(x, y)
end

function Scene:CreateMap()
	local cc_layer_main = self:GetLayer("main")
	local width_scene = 0    
    local height_scene = 0

    local physics_sprite_background = GameSprite:create("image/background.png")
    local rect_raw_background = physics_sprite_background:getTextureRect()
    physics_sprite_background:setAnchorPoint(cc.p(0, 0))
   
    width_scene = rect_raw_background.width
    height_scene = rect_raw_background.height

    num_ret_code = PhysicsWorld:CreateRectEdge(physics_sprite_background, 0, width_scene, 0, height_scene)
    assert(num_ret_code == 1)

    self:SetWidth(width_scene)
	self:SetHeight(height_scene)
	cc_layer_main:addChild(physics_sprite_background)

    local physics_sprite_ground = GameSprite:create(Def.str_ground_img)
	local rect_map = physics_sprite_ground:getTextureRect()
    local position_x = width_scene * 0.5
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
    cc_layer_main:addChild(physics_sprite_body)

	tb_ret.body = physics_sprite_body

    local str_weapon = tb_param.str_weapon
    if str_weapon then
	    local cc_sprite_weapon = GameSprite:create(string.format("image/%s.png", str_weapon))
	    local width_weapon = cc_sprite_weapon:getContentSize().width * 0.5
	    local height_weapon = cc_sprite_weapon:getContentSize().height * 0.5
	    local weapon_x = 15
	    local weapon_y = 40
	    cc_sprite_weapon:setAnchorPoint(cc.p(5 / width_weapon, 0.5))
	    cc_sprite_weapon:setPosition(weapon_x, weapon_y)
	    cc_sprite_weapon:setRotation(-45)
	    physics_sprite_body:addChild(cc_sprite_weapon)
		tb_ret.weapon = cc_sprite_weapon
	end

	local tbParam = {
		str_wheel = "image/tank_wheel.png",
		str_crawler = "image/rect2.png",
	}
	local tb_crawler_belt = Physics:CreateCrawlerBelt(cc_layer_main, tank_x, tank_y, physics_sprite_body, 50, tbParam)
	if not tb_crawler_belt then
		assert(false)
		return
	end

	local tb_property = {
		mask_bits     = 0,
	}
	local motor, radius_motor = Physics:CreateCircleSprite("image/circle.png", tank_x, tank_y, tb_property)
	-- motor:setVisible(false)
	cc_layer_main:addChild(motor)
	tb_ret.motor = motor

	local joint_motor_body = PhysicsWorld:CreateRevoluteJoint(
    	physics_sprite_body, 0, 0,
    	motor, 0, 0
    )
    assert(joint_motor_body)

    local joint_motor_wheel_back = PhysicsWorld:CreateGearJoint(
    	motor, tb_crawler_belt.wheel_back,
    	joint_motor_body, tb_crawler_belt.tb_joint.wheel_back, 1
    )
    assert(joint_motor_wheel_back)

    local joint_motor_wheel_middle = PhysicsWorld:CreateGearJoint(
    	motor, tb_crawler_belt.wheel_middle,
    	joint_motor_body, tb_crawler_belt.tb_joint.wheel_middle, 1
    )
    assert(joint_motor_wheel_middle)

    local joint_motor_wheel_front = PhysicsWorld:CreateGearJoint(
    	motor, tb_crawler_belt.wheel_front,
    	joint_motor_body, tb_crawler_belt.tb_joint.wheel_front, 1
    )
    assert(joint_motor_wheel_front)

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
	self.tb_widget = {}
	local tb_button_list = {"button_left", "button_right", "button_up", "button_down", "button_luanch"}
	for _, str_button_name in ipairs(tb_button_list) do
		local button = uilayer_control:getWidgetByName(str_button_name)
		if button then
			self.tb_widget[#self.tb_widget + 1] = button
			button:addTouchEventListener(OnButtonEvent)
		else
			print(str_button_name)
			assert(false)
		end
	end
end

function Scene:SetUIEnable(enable)
	for _, widget in ipairs(self.tb_widget) do
		widget:setEnabled(enable)
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
	self.uilayer_control:setVisible(false)
	self:SetUIEnable(false)

	local cc_layer_main = self:GetLayer("main")
    local material = GamePhysicsWorld.MATERIAL:new(Def.BULLET_DENSITY, 0, 0.5)

	assert(not self.physics_sprite_bullet)

    local physics_sprite_bullet = BombSprite:create("image/bullet.png")
    local float_scale = 1
    local float_bullet_radius = physics_sprite_bullet:getContentSize().width * 0.25 * float_scale
    physics_sprite_bullet:Init(Def.BULLET_POWER_LINERAR, Def.BULLET_POWER_ANGULAR, Def.BULLET_BOMB_RANGE)

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
    local impulse = BattleLogic:GetBulletPower(power)
    PhysicsWorld:ApplyImpulseByAngular(physics_sprite_bullet, -weapon:getRotation(), impulse);
    self.physics_sprite_bullet = physics_sprite_bullet
end

function Scene:SetGroundSprite(ground)
	self.physics_sprite_ground = ground
end

function Scene:GetGroundSprite()
	return self.physics_sprite_ground
end

function Scene:OnBomb(sprite_bullet, float_bomb_x, float_bomb_y)
	local cc_layer_main = self:GetLayer("main")
	local bomb_sprite = cc.Sprite:create("image/bomb.png")
    bomb_sprite:setPosition(float_bomb_x, float_bomb_y)
    cc_layer_main:addChild(bomb_sprite, Def.ZOOM_LEVEL_WORLD)
    bomb_sprite:setScale(0.05)

   	local action_scale = cc.ScaleTo:create(0.05, 1.0)
    local action_delay_time = cc.DelayTime:create(0.5)
    local action_remove_self = cc.RemoveSelf:create()
    bomb_sprite:runAction(cc.Sequence:create(action_scale, action_delay_time, action_remove_self))

    function RecoverUI()
		self.uilayer_control:setVisible(true)
		self:SetUIEnable(true)
	end
	
	local action_move_left = cc.MoveBy:create(0.02, cc.p(-3, 0))
	local action_move_right = cc.MoveBy:create(0.02, cc.p(3, 0))
	local action_delay_time = cc.DelayTime:create(1)
	local x, y = self.tb_player.body:getPosition()
	local modify_x, modify_y = self:GetModifyPosition(tb_size_visible.width / 2 - x, tb_size_visible.height / 2 - y)
	local action_move_to = cc.MoveTo:create(0.5, cc.p(modify_x, modify_y))
	local action_callback = cc.CallFunc:create(RecoverUI)
	local sequence_actions = cc.Sequence:create(
		action_move_left,
		action_move_right,
		action_move_right,
		action_move_left,
		action_move_left, 
		action_move_right,
		action_delay_time,
		action_move_to,
		action_callback
	)
	cc_layer_main:runAction(sequence_actions)
    cc_layer_main:removeChild(sprite_bullet)
    self.physics_sprite_bullet = nil

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
		self:SetFocus(1)
	elseif str_button_name == "button_right" then
		BattleLogic:StartMove("right")
		self:SetFocus(1)
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
		self:SetFocus(0)
	elseif str_button_name == "button_right" then
		BattleLogic:StopMove()
		self:SetFocus(0)
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
		self:SetFocus(0)
	elseif str_button_name == "button_right" then
		BattleLogic:StopMove()
		self:SetFocus(0)
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

function Scene:OnBeBombed(bomb, target)
	if target ~= self.tb_player.body or target ~= self.tb_enemy.body then
		return
	end
	local bomb_x, bomb_y = bomb:getPosition()
	local target_x, target_y = target:getPosition()

	local vec_x, vec_y = target_x - bomb_x, target_y - bomb_y

	local distance_squared = Lib:GetDistanceSquare(bomb_x, bomb_y, target_x, target_y)
	local distance = math.sqrt(distance_squared)
	local bomb_power_linear = bomb:GetLinearPower() / distance_squared
	local impulse_x = bomb_power_linear * vec_x / distance
	local impulse_y = bomb_power_linear * vec_y / distance
	assert(PhysicsWorld:ApplyImpulse(target, impulse_x, impulse_y) == 1)

	local angular_impulse = bomb:GetAngularPower() / distance_squared
	if (vec_x > 0 and vec_y > 0) or (vec_x < 0 or vec_y < 0) then
		angular_impulse = angular_impulse * -1
	end
	assert(PhysicsWorld:ApplyAngularImpulse(target, angular_impulse) == 1)

	        -- b2Vec2 bomb_vec = ptr_b2body->GetPosition() - m_b2vec2_bomb_point;
        -- float float_r2 = bomb_vec.LengthSquared();
        -- float float_r = sqrt(float_r2);
        -- float float_linear_impulse = m_float_power_linear / float_r2;
        -- float float_impulse_x = float_linear_impulse * bomb_vec.x / float_r;
        -- float float_impulse_y = float_linear_impulse * bomb_vec.y / float_r;
        -- ptr_b2body->ApplyLinearImpulse(
        --     b2Vec2(float_impulse_x, float_impulse_y),
        --     ptr_b2body->GetPosition()
        --     );
        -- float float_angular_impulse = m_float_power_angular / float_r2;
        -- if ((bomb_vec.x > 0.0f && bomb_vec.y > 0.0f) || (bomb_vec.x < 0.0f && bomb_vec.y < 0.0f))
        -- {
        --     float_angular_impulse *= -1;
        -- }
        -- ptr_b2body->ApplyAngularImpulse(float_angular_impulse);
end
