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
	debug_physics = 1, --是否显示物理引擎调试绘制
}

Scene:DeclareListenEvent("Bomb", "OnBomb")
Scene:DeclareListenEvent("BeBombed", "OnBeBombed")
-- Scene:DeclareListenEvent("WeaponRotate", "OnWeaponRotate")
Scene:DeclareListenEvent("PowerChanged", "OnPowerChanged")
Scene:DeclareListenEvent("Attack", "OnAttack")
Scene:DeclareListenEvent("GameOver", "OnGameOver")

local PhysicsWorld = GamePhysicsWorld:GetInstance()
local tb_size_visible = CCDirector:getInstance():getVisibleSize()

function Scene:_Uninit()
	local cc_layer_main = self:GetLayer("main")
	BattleLogic:Uninit()
	Player:Uninit()
	Enemy:Uninit()
	Performance:Uninit(cc_layer_main)
	self.is_run = nil
end

function Scene:_Init()
	local num_ret_code = 0
	local width_visible = tb_size_visible.width
	local height_visible = tb_size_visible.height

	local cc_layer_main = self:GetLayer("main")
	Performance:Init(cc_layer_main)
	self:LoadControlUI()

	self:CreateMap()

	self:SetFocus(0)
	local width_scene = self:GetWidth()

    local tb_construct = {
    	str_body = "tank_1",
    	weapon_type = "test1",
    	motor_type = "test1",
	}
	Player:Init(cc_layer_main, 1000, width_scene / 2 - 300, 250, tb_construct)

	tb_construct.str_body = "tank_1_mirro"
	tb_construct.weapon_type = nil
	Enemy:Init(cc_layer_main, 1000, width_scene / 2 + 300, 250, tb_construct)

    local body = Player:GetBody()
	if not body then
		return
	end
	self:FocusSprite(body)

    BattleLogic:Init(self.tb_enemy)
	self.is_run = 1
	-- self:SetScale(0.8)
    return 1
end

function Scene:OnTouchBegan(x, y)
    return Physics:OnMouseDown(x, y)
end

function Scene:OnTouchMoved(x, y)
    return Physics:OnMouseMoved(x, y)
end

function Scene:OnTouchEnded(x, y)
    return Physics:OnMouseEnded(x, y)
end

function Scene:SetFocus(is_need_focus)
	self.is_need_focus = is_need_focus
end

function Scene:IsNeedFocus()
	return self.is_need_focus
end

function Scene:FocusSprite(sprite)
	local x, y = sprite:getPosition()
	self:MoveCamera(x, y)
end

function Scene:OnLoop(delta)
	if self.is_run ~= 1 then
		return
	end
	local player_body = Player:GetBody()
	if self.physics_sprite_bullet then
		self:FocusSprite(self.physics_sprite_bullet)
	elseif self:IsNeedFocus() == 1 and player_body then
		self:FocusSprite(player_body)
	end	

	
	local rotation, rotation_body = Player:GetWeaponAngle()
	local label_angel = self.uilayer_control:getWidgetByName("label_angel")
	if not label_angel then
		assert(false)
		return
	end
	label_angel = tolua.cast(label_angel, "UILabelAtlas")
	label_angel:setStringValue(tostring(rotation))

	local image_tablet = self.uilayer_control:getWidgetByName("image_tablet")
	if not image_tablet then
		assert(false)
		return
	end
	image_tablet:setRotation(rotation_body)
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
    num_ret_code = PhysicsWorld:SetPolygonBodyWithShapeName(physics_sprite_ground, "map1", offset_x, offset_y, bool_dynamic)
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

    cc_layer_main:addChild(cc_clipping_background)
    cc_clipping_background:addChild(cc_clipping_map_ground)
    cc_clipping_map_ground:addChild(physics_sprite_ground)	
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
	progressbar_power:setPercent(power)

	label_power = tolua.cast(label_power, "UILabelAtlas")
	label_power:setVisible(true)
	label_power:setStringValue(power)
end

function Scene:OnAttack(tb_bullet_property)
	self.uilayer_control:setVisible(false)
	self:SetUIEnable(false)

	local progressbar_power_old = self.uilayer_control:getWidgetByName("progressbar_power_old")
	if not progressbar_power_old then
		assert(false)
		return
	end

	local progressbar_power = self.uilayer_control:getWidgetByName("progressbar_power")
	if not progressbar_power then
		assert(false)
		return
	end	
	progressbar_power_old = tolua.cast(progressbar_power_old, "UILoadingBar")
	progressbar_power = tolua.cast(progressbar_power, "UILoadingBar")
	local percent = progressbar_power:getPercent()
	progressbar_power_old:setPercent(percent)
	progressbar_power:setPercent(0)

	local cc_layer_main = self:GetLayer("main")

	local bullet_type = tb_bullet_property.bullet_type
	local bullet_x, bullet_y = tb_bullet_property.x, tb_bullet_property.y
	local impulse = tb_bullet_property.impulse

	
	local bullet_cfg = Bullet:GetCfg(tb_bullet_property.bullet_type)
    local material = GamePhysicsWorld.MATERIAL:new(bullet_cfg.density, 0, 0.5)

	assert(not self.physics_sprite_bullet)

    local physics_sprite_bullet = BombSprite:create(bullet_cfg.image)
    local scale = bullet_cfg.scale or 1
    local float_bullet_radius = physics_sprite_bullet:getContentSize().width * 0.25 * scale
    physics_sprite_bullet:Init(bullet_type, bullet_cfg.power_linear, bullet_cfg.power_angular, bullet_cfg.bomb_range)
    physics_sprite_bullet:setPosition(bullet_x, bullet_y)
    if scale ~= 1 then
    	physics_sprite_bullet:setScale(scale)
    end
    cc_layer_main:addChild(physics_sprite_bullet, Def.ZOOM_LEVEL_WORLD)

    local is_bullet = 1
    PhysicsWorld:SetCircleBody(
        physics_sprite_bullet, float_bullet_radius, 
        material, 0, 0, 1, is_bullet)
    PhysicsWorld:SetBodyAngularVelocity(physics_sprite_bullet, 2)

	local rotation = Player:GetWeaponAngle()
    PhysicsWorld:ApplyImpulseByAngular(physics_sprite_bullet, rotation, impulse);
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
	local bullet_type = sprite_bullet:GetBulletType()
	local bomb_range = sprite_bullet:GetBombRadius()
	local bomb_sprite = cc.Sprite:create("image/bomb.png")
	local width_bomb_sprite = bomb_sprite:getContentSize().width / 4
    bomb_sprite:setPosition(float_bomb_x, float_bomb_y)
    cc_layer_main:addChild(bomb_sprite, Def.ZOOM_LEVEL_WORLD)
    bomb_sprite:setScale(0.05)

    local final_scale = bomb_range / width_bomb_sprite
   	local action_scale = cc.ScaleTo:create(0.05, final_scale)
    local action_delay_time = cc.DelayTime:create(0.5)
    local action_remove_self = cc.RemoveSelf:create()
    bomb_sprite:runAction(cc.Sequence:create(action_scale, action_delay_time, action_remove_self))

    function RecoverUI()
		if Player:GetHP() <= 0 or Enemy:GetHP() <= 0 then
			self:OnGameOver()
		else
			self.uilayer_control:setVisible(true)
			self:SetUIEnable(true)
		end
	end
	
	local action_move_left = cc.MoveBy:create(0.02, cc.p(-3, 0))
	local action_move_right = cc.MoveBy:create(0.02, cc.p(3, 0))
	local action_delay_time = cc.DelayTime:create(1)
	local x, y = Player:GetPosition()
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
	local destroy_range = Bullet:GetDestoryRange(bullet_type)
	if destroy_range > 0 then
		local destory_x, destory_y = float_bomb_x , float_bomb_y
		local num_ret_code = PhysicsWorld:ClipperPolygonByCircle(ground, destroy_range, 20, destory_x, destory_y)
		if num_ret_code == 1 then
			local scale = destroy_range / 30
		    local pSprite = cc.Sprite:create("image/hole-erase.png")
		    pSprite:setPosition(destory_x, destory_y)
		    pSprite:setScale(scale) 
		    self.pHole:addChild(pSprite)
		    
		    local pSpriteEdge = cc.Sprite:create("image/hole-edge.png")
		    pSpriteEdge:setPosition(destory_x, destory_y) 
		    pSpriteEdge:setScale(scale) 
		    self.pEdge:addChild(pSpriteEdge)
		end
	end
end

function Scene:OnButtonBegan(widget_button)
	local str_button_name = widget_button:getName()
	if str_button_name == "button_left" then
		Player:StartMove("left")
		self:SetFocus(1)
	elseif str_button_name == "button_right" then
		Player:StartMove("right")
		self:SetFocus(1)
	elseif str_button_name == "button_up" then
		Player:StartAdjust("up")
	elseif str_button_name == "button_down" then
		Player:StartAdjust("down")
	elseif str_button_name == "button_luanch" then
		Player:ReadyToAttack()
	end
end

function Scene:OnButtonMoved(widget_button)

end

function Scene:OnButtonEnded(widget_button)
	local str_button_name = widget_button:getName()
	if str_button_name == "button_left" then
		Player:StopMove()
		self:SetFocus(0)
	elseif str_button_name == "button_right" then
		Player:StopMove()
		self:SetFocus(0)
	elseif str_button_name == "button_up" then
		Player:StopAdjust()
	elseif str_button_name == "button_down" then
		Player:StopAdjust()
	elseif str_button_name == "button_luanch" then
		Player:Attack()
	end
end
function Scene:OnButtonCanceled(widget_button)
	local str_button_name = widget_button:getName()
	if str_button_name == "button_left" then
		Player:StopMove()
		self:SetFocus(0)
	elseif str_button_name == "button_right" then
		Player:StopMove()
		self:SetFocus(0)
	elseif str_button_name == "button_up" then
		Player:StopAdjust()
	elseif str_button_name == "button_down" then
		Player:StopAdjust()
	elseif str_button_name == "button_luanch" then
		Player:Attack()
	end
end

Scene.func_button_event = {
	[Ui.TOUCH_EVENT_BEGAN] = Scene.OnButtonBegan,
	[Ui.TOUCH_EVENT_MOVED] = Scene.OnButtonMoved,
	[Ui.TOUCH_EVENT_ENDED] = Scene.OnButtonEnded,
	[Ui.TOUCH_EVENT_CANCELED] = Scene.OnButtonCanceled,
}

function Scene:OnBeBombed(bomb, target)
	if target ~= Player:GetBody() and target ~= Enemy:GetBody() then
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
	if (vec_x < 0 and vec_y > 0) or (vec_x > 0 or vec_y < 0) then
		angular_impulse = angular_impulse * -1
	end
	assert(PhysicsWorld:ApplyAngularImpulse(target, angular_impulse) == 1)

	local bullet_type = bomb:GetBulletType()
	local damage = Bullet:GetDamage(bullet_type)
	local cur_hp, new_hp
	if target == Player:GetBody() then
		cur_hp = Player:GetHP()
		new_hp = cur_hp - damage
		Player:SetHP(new_hp)
	else
		cur_hp = Enemy:GetHP()
		new_hp = cur_hp - damage
		Enemy:SetHP(new_hp)
	end
	Event:FireEvent("CharacterHPChanged", target, cur_hp, new_hp, 1000)
	
	Event:FireEvent("BeBombDamage", bomb, target)
end

function Scene:OnGameOver()
	local cc_layer_main = self:GetLayer("main")
	function GameOver()
		SceneMgr:DestroyScene(self:GetName())
		local cc_scene = SceneMgr:GetSceneObj("MainScene")
		CCDirector:getInstance():replaceScene(cc_scene)
	end	

	self:SysMsg("游戏结束", "red")
	local action_delay_time = cc.DelayTime:create(3)
	local action_callback = cc.CallFunc:create(GameOver)
	local sequence_actions = cc.Sequence:create(
		action_delay_time,
		action_callback
	)
	cc_layer_main:runAction(sequence_actions)
end