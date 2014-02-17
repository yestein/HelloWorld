--=======================================================================
-- File Name    : performance.lua
-- Creator      : yestein(yestein86@gmail.com)
-- Date         : 2013-12-05 21:16:23
-- Description  :
-- Modify       :
--=======================================================================

if not Performance then
	Performance = {}
end

local szFlyLabelFont = "Courier"
if device == "win32" then
    szFlyLabelFont = "Microsoft Yahei"
end

Performance.MAX_DISPLAY_DAMAGE = 20

function Performance:Init(layer)

    self.tbFlyLabel = {}
    self.nDamageIndex = 1
	for i = 1, self.MAX_DISPLAY_DAMAGE do
		local labelFly = CCLabelTTF:create("-100", szFlyLabelFont, 60)
        layer:addChild(labelFly, 10)
        labelFly:setVisible(false)
        self.tbFlyLabel[i] = labelFly
	end
	self.hp = {}
	self:RegistEvent()
end

function Performance:Uninit(layer)
    self:UnRegistEvent()
    self.nDamageIndex = nil
	for i, labelFly in ipairs(self.tbFlyLabel) do
        layer:removeChild(labelFly, true)
	end
	self.hp = nil
	self.tbFlyLabel = nil	
end

function Performance:GetAvaiableFlyLabel()
	local label = self.tbFlyLabel[self.nDamageIndex]

	self.nDamageIndex = self.nDamageIndex + 1
	if self.nDamageIndex > self.MAX_DISPLAY_DAMAGE then
		self.nDamageIndex = self.nDamageIndex - self.MAX_DISPLAY_DAMAGE
	end
	return label
end

function Performance:RegistEvent()
	if not self.nRegCharacterAdd then
		self.nRegCharacterAdd = Event:RegistEvent("CharacterAdd", self.OnCharacterAdd, self)
	end

	if not self.nRegHPChanged then
		self.nRegHPChanged = Event:RegistEvent("CharacterHPChanged", self.OnCharacterHPChanged, self)
	end
end

function Performance:UnRegistEvent()
	if self.nRegCharacterAdd then
		Event:UnRegistEvent("CharacterAdd", self.nRegCharacterAdd )
		self.nRegCharacterAdd = nil
	end

	if self.nRegHPChanged then
		Event:UnRegistEvent("CharacterHPChanged", self.nRegHPChanged )
		self.nRegHPChanged = nil
	end
end

function Performance:OnCharacterAdd(id, hp)
	local character = CharacterMgr:GetById(id)
	if not character then
		return
	end
	local pSprite = character:GetBody()
	local tbSpriteSize = pSprite:getContentSize()
	local spriteHP = cc.Sprite:create("image/blood.png")
	local progressHP = CCProgressTimer:create(spriteHP)
	local progressSize = spriteHP:getContentSize()
	progressHP:setType(1)
	progressHP:setMidpoint(cc.p(0, 0.5))
    progressHP:setBarChangeRate(cc.p(1, 0))	
	progressHP:setPercentage(100)
	progressHP:setAnchorPoint(cc.p(0.5, 0))
    progressHP:setScaleX(tbSpriteSize.width / progressSize.width)
    progressHP:setScaleY(10 / progressSize.height)
    progressHP:setPosition(tbSpriteSize.width / 2, tbSpriteSize.height + 20)
    -- progressHP:setVisible(false)
    pSprite:addChild(progressHP)
    character:SetProgressHP(progressHP)
end

function Performance:OnCharacterHPChanged(id, nBeforeHP, nAfterHP, nMaxHP)
	local character = CharacterMgr:GetById(id)
	if not character then
		return
	end

	local pSprite = character:GetBody()
	local progressHP = character:GetProgressHP()
	if progressHP then
		progressHP:setPercentage(nAfterHP * 100 / nMaxHP)
	end	

	local nDamage = nAfterHP - nBeforeHP
	local color = nil
	local szMsg = nil
	if nDamage == 0 then
		return
	elseif nDamage < 0 then
		color = Def.tbColor["red"]
		szMsg = tostring(nDamage)
	elseif nDamage > 0 then
		color = Def.tbColor["red"]
		szMsg = "+"..tostring(nDamage)
	end

	local nX, nY = pSprite:getPosition()
	local label = self:GetAvaiableFlyLabel()
	if not label then
		return
	end
	label:setColor(color)
	label:setString(szMsg)	
	label:setVisible(true)
	label:setPosition(nX, nY + 10)
	local action = CCSpawn:createWithTwoActions(CCFadeOut:create(1), CCMoveBy:create(1, cc.p(0, 40)))
	label:runAction(action)
end