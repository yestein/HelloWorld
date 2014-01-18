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
		local labelFly = CCLabelTTF:create("-100", szFlyLabelFont, 18)
        layer:addChild(labelFly, 10)
        labelFly:setVisible(false)
        self.tbFlyLabel[i] = labelFly
	end
	self:UnRegistEvent()
	self:RegistEvent()
end

function Performance:Uninit()
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

end

function Performance:UnRegistEvent()

end
