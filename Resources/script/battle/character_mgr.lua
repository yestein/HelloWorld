--=======================================================================
-- File Name    : character_mgr.lua
-- Creator      : yestein (yestein86@gmail.com)
-- Date         : 
-- Description  :
-- Modify       :
--=======================================================================

if not CharacterMgr then
	CharacterMgr = {}
end

function CharacterMgr:Init()
	self.character_pool = {}
	self.id = 1
end

function CharacterMgr:Uninit()
	self.character_pool = nil
	self.id = nil
end

function CharacterMgr:Create(hp, x, y, sprites)
	local id = self.id
	local tb = Lib:NewClass(Character)
	tb.id = id
	tb:Init(hp, x, y, sprites)
	self.character_pool[id] = tb
	self.id = self.id + 1

	Event:FireEvent("CharacterAdd", id, hp, x, y)
	return tb, id
end

function CharacterMgr:GetById(id)
	return self.character_pool[id]
end

function CharacterMgr:Destory(id)
	self.character_pool[id]:Uninit()
	self.character_pool[id] = nil

	Event:FireEvent("CharacterRemove", id)
end