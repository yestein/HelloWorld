--===================================================
-- File Name    : demo_scene.lua
-- Creator      : yulei(yulei1@kingsoft.com)
-- Date         : 2014-01-09 17:56:00
-- Modify       :
--===================================================

local Scene = SceneMgr:GetClass("DemoScene", 1)
local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Scene:_Uninit()
	BattleLogic:Uninit()
	Event:UnRegistEvent("WeaponRotate", self.nRegWeaponRotate)
	Event:UnRegistEvent("PowerChanged", self.nRegPowerChanged)	
	Event:UnRegistEvent("Attack", self.nRegAttack)
	CCDirector:getInstance():getScheduler():unscheduleScriptEntry(self.nRegPhysicsUpdate)
end

function Scene:Create()
	local num_ret_code = 0
	local tb_ui = self:GetUI()
	if not tb_ui then
		return
	end
	local cc_scene = self:GetCCObj()
	if not cc_scene then
		return
	end

	local cc_layer = cc.Layer:create()
	self.cc_layer = cc_layer

	local tb_size_visible = CCDirector:getInstance():getVisibleSize()
	local width_visible = tb_size_visible.width
	local height_visible = tb_size_visible.height

    self:LoadControlUI()
    local width_game = 0    
    local height_game = 0
    assert(PhysicsWorld:LoadPolygonBodyFromFile("physics/map-box2d.plist") == 1)
	for i = 1, 2 do
        local physics_sprite_ground = GameSprite:create("image/map.png")
    	local rect_map = physics_sprite_ground:getTextureRect()

        local position_x = rect_map.width * (i - 0.5) 
        local position_y = rect_map.height / 2
        width_game = width_game + rect_map.width
        physics_sprite_ground:setPosition(position_x, position_y)
    	cc_layer:addChild(physics_sprite_ground, Def.ZOOM_LEVEL_WORLD)

    	local offset_x = 0
    	local offset_y = 0
    	local bool_dynamic = 0   
        num_ret_code = PhysicsWorld:SetPolygonBodyWithShapeName(physics_sprite_ground, "map", offset_x, offset_y, bool_dynamic)
       	assert(num_ret_code == 1)
    end
    local physics_sprite_background = cc.Sprite:create("image/background.png")
    local rect_raw_background = physics_sprite_background:getTextureRect()
    physics_sprite_background:setAnchorPoint(cc.p(0, 0))
    cc_layer:addChild(physics_sprite_background)
    local scale = width_game / rect_raw_background.width
    height_game = rect_raw_background.height * scale
    physics_sprite_background:setScale(scale)

    num_ret_code = PhysicsWorld:CreateRectEdge(0, width_game, 0, height_game)
    assert(num_ret_code == 1)    

    local tb_param = {
    	str_body = "tank",
    	str_weapon = "tank_weapon",
	}
    self.tb_player = self:BuildTank(100, 200, tb_param)
    self.tb_enemy = self:BuildTank(500, 200, tb_param)

    BattleLogic:Init(self.tb_player, self.tb_enemy)

	local touchBeginPoint = nil
    local touchStartPoint = nil
    local function onTouchBegan(x, y)
        touchBeginPoint = {x = x, y = y}
        touchStartPoint = {x = x, y = y}
        local nX, nY = cc_layer:getPosition()
        PhysicsWorld:MouseDown(x - nX,  y - nY)
        return true
    end

    local function onTouchMoved(x, y)
        if touchBeginPoint then
            local nX, nY = cc_layer:getPosition()
            if PhysicsWorld:MouseMove(x - nX,  y - nY) ~= 1 then
                local nNewX, nNewY = nX + x - touchBeginPoint.x, nY + y - touchBeginPoint.y
                local nMinX, nMaxX = width_visible - width_game, 0
                local nMinY, nMaxY = height_visible - height_game,  0
                if nNewX < nMinX then
                    nNewX = nMinX
                elseif nNewX > nMaxX then
                    nNewX = nMaxX
                end

                if nNewY < nMinY then
                    nNewY = nMinY
                elseif nNewY > nMaxY then
                    nNewY = nMaxY
                end
                cc_layer:setPosition(nNewX, nNewY)

                touchBeginPoint = {x = x, y = y}
            end
        end
    end

    local function onTouchEnded(x, y)
         local nX, nY = cc_layer:getPosition()
        PhysicsWorld:MouseUp(x - nX,  y - nY)
        touchBeginPoint = nil
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then   
            return onTouchBegan(x, y)
        elseif eventType == "moved" then
            return onTouchMoved(x, y)
        else
            return onTouchEnded(x, y)
        end
    end

    cc_layer:registerScriptTouchHandler(onTouch)
    cc_layer:setTouchEnabled(true)
    local function tick(delta)
    	self:OnLoop(delta)
    end
    self.nRegPhysicsUpdate = CCDirector:getInstance():getScheduler():scheduleScriptFunc(tick, 0, false)

    self.nRegWeaponRotate = Event:RegistEvent("WeaponRotate", self.OnWeaponRotate, self)
    self.nRegPowerChanged = Event:RegistEvent("PowerChanged", self.OnPowerChanged, self)
    self.nRegAttack = Event:RegistEvent("Attack", self.OnAttack, self)
    
	Event:FireEvent("SceneCreate", self:GetClassName(), self:GetName())
    return cc_layer
end

function Scene:OnLoop(delta)
	PhysicsWorld:Update(delta)
	BattleLogic:OnLoop(delta)
end

function Scene:CreatePloygonCommpent(str_name, x, y)
	local physics_sprite = GameSprite:create(string.format("image/%s.png", str_name))
    local width_commpent = physics_sprite:getContentSize().width
    local height_commpent = physics_sprite:getContentSize().height
    physics_sprite:setPosition(x, y)

    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    PhysicsWorld:SetPolygonBodyWithShapeName(physics_sprite, str_name, offset_x, offset_y, bool_dynamic)
    self.cc_layer:addChild(physics_sprite, Def.ZOOM_LEVEL_WORLD)
    return physics_sprite, width_commpent, height_commpent
end

function Scene:CreateBoxCommpent(str_name, x, y, material, width_physics, height_physics)
	local physics_sprite = GameSprite:create(string.format("image/%s.png", str_name))
    local width_commpent = physics_sprite:getContentSize().width
    local height_commpent = physics_sprite:getContentSize().height
    physics_sprite:setPosition(x, y)

    if not width_physics then
    	width_physics = width_commpent * 0.5
    end
    if not height_physics then
    	height_physics = height_commpent * 0.5
    end
    local offset_x, offset_y, bool_dynamic = 0, 0, 1
    local m = GamePhysicsWorld.MATERIAL:new(1, 0.2, 0.5)
    PhysicsWorld:SetBoxBody(physics_sprite, width_physics, height_physics, material,offset_x, offset_y, bool_dynamic)
    self.cc_layer:addChild(physics_sprite, Def.ZOOM_LEVEL_WORLD)
    return physics_sprite, width_commpent, height_commpent
end

function Scene:BuildTank(tank_x, tank_y, tb_param)
	local tb_ret = {}
	local str_body = tb_param.str_body
	if not str_body then
		assert(false)
		return
	end
	local physics_sprite_body, width_body, height_body = self:CreatePloygonCommpent(str_body, tank_x, tank_y)
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
	    cc_sprite_weapon:setTag(110)
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
	local uilayer_control = Ui:LoadJson(cc_layer, "control/control.ExportJson")
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
    self.cc_layer:addChild(physics_sprite_bullet, Def.ZOOM_LEVEL_WORLD)

    PhysicsWorld:SetCircleBody(
        physics_sprite_bullet, float_bullet_radius, 
        material, 0, 0, 1, 1)

    PhysicsWorld:SetBodyAngularVelocity(physics_sprite_bullet, 2)
    PhysicsWorld:ApplyImpulseByAngular(physics_sprite_bullet, -weapon:getRotation(), 100 + power * 10);
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





	