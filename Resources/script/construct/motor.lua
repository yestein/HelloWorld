--=======================================================================
-- File Name    : motor.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 2014-01-22
-- Description  :
-- Modify       :
--=======================================================================


if not Motor then
	Motor = {}
end

Motor.tb_cfg = {
	["test1"] = {
		power = 400,
	},
}

local PhysicsWorld = GamePhysicsWorld:GetInstance()

function Motor:GetCfg(motor_type)
	return self.tb_cfg[motor_type]
end

function Motor:Create(motor_type, cc_layer, x, y, physics_sprite_body, tb_tobe_gear, visible)
	local tb_ret = { motor_type = motor_type}
	local tb_property = {
		category_bits = Physics.GROUP_MOTOR,
		mask_bits     = Physics.MASK_MOTOR,
	}
	local motor, radius_motor = Physics:CreateCircleSprite("image/circle.png", x, y, tb_property)
	
	cc_layer:addChild(motor)
	tb_ret.motor = motor

	local joint_motor_body = PhysicsWorld:CreateRevoluteJoint(
		motor, 0, 0,
    	physics_sprite_body, 0, 0    	
    )
    assert(joint_motor_body)
    tb_ret.joint_motor_body = joint_motor_body

    tb_property.friction = 100
	local brake, width_brake, height_brake = Physics:CreateBoxSprite("image/rect1.png", x , y + radius_motor + 15, tb_property)

	cc_layer:addChild(brake)
	tb_ret.brake = brake

	local joint_brake_body = PhysicsWorld:CreateRevoluteJoint(
		brake, width_brake / 2 - 5, 0, 
    	physics_sprite_body, width_brake / 2 - 5, radius_motor + 15,
    	1, 3.14, 4.72, 20, 10
    )
    assert(joint_brake_body)

    local brake1, width_brake, height_brake = Physics:CreateBoxSprite("image/rect1.png", x , y + radius_motor + 15, tb_property)

	cc_layer:addChild(brake1)
	tb_ret.brake1 = brake1
	local joint_brake_body = PhysicsWorld:CreateRevoluteJoint(
		brake1, -width_brake / 2 + 5, 0, 
    	physics_sprite_body, -width_brake / 2 + 5, radius_motor + 15,
    	1, -4.72, -3.14, -20, 10
    )
    assert(joint_brake_body)

    -- Gear

    for _, tb in pairs(tb_tobe_gear) do
	    local joint = PhysicsWorld:CreateGearJoint(
	    	motor, tb.sprite,
	    	joint_motor_body, tb.joint, tb.ratio or 1
	    )
	    assert(joint)
	end

    if not visible then
	    motor:setVisible(false)
		brake:setVisible(false)
		brake1:setVisible(false)
	end

    return tb_ret
end

function Motor:Move(tb_motor, str_direction)
	local motor_type = tb_motor.motor_type
	local motor_cfg = self:GetCfg(motor_type)
	local torque = motor_cfg.power
	if str_direction == "right" then
		torque = -torque
	end
	PhysicsWorld:SetBodyAngularVelocity(tb_motor.brake, -30)
	PhysicsWorld:SetBodyAngularVelocity(tb_motor.brake1, 30)
	PhysicsWorld:ApplyTorque(tb_motor.motor, torque)

	return torque
end