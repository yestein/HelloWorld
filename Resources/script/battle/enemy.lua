--=======================================================================
-- File Name    : enemy.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  :
-- Modify       :
--=======================================================================
if not Enemy then
	Enemy = {}
end

function Enemy:Init(cc_layer, hp, x, y, tb_construct)
	self.list = {}
	for i = 1, 1 do
		self.list[i] = {
			hp = hp,
			x = x,
			y = y,
		}
		local sprites = Construct:BuildTank(cc_layer, x, y, tb_construct)
		local character = CharacterMgr:Create(hp, x, y, sprites)
		self.list[i].id = character.id
	end
	return 1
end

function Enemy:Uninit()
	for _, enemy in ipairs(self.list) do
		CharacterMgr:Destory(enemy.id)
	end
end
