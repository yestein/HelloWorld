--=======================================================================
-- File Name    : scene_base.lua
-- Creator      : yestein(yestein86@gmail.com)
-- Date         : 2013-11-29 21:16:43
-- Description  :
-- Modify       :
--=======================================================================

if not SceneMgr then
	SceneMgr = {}
end

if not SceneMgr._SceneBase then
	SceneMgr._SceneBase = {}
end

local SceneBase = SceneMgr._SceneBase

function SceneBase:Init(str_scene_name, cc_scene)
	self.str_scene_name = str_scene_name
	self.cc_scene = cc_scene
	Ui:InitScene(str_scene_name, cc_scene)
end

function SceneBase:Uninit()
	MenuMgr:DestroyMenu(self.str_scene_name)
	Ui:UninitScene(self.str_scene_name)
	self.str_scene_name = nil
	self.cc_scene = nil
	self:_Uninit()
end

function SceneBase:GetUI()
	return Ui:GetSceneUi(self:GetName())
end

function SceneBase:_Uninit()
end

function SceneBase:Create()
	cclog("Scene [%s] Create Error!", self:GetName())
end

function SceneBase:RemoveSprite(pSprite)
	cclog("Scene [%s]  RemoveSprite Failed!", self:GetName())
end

function SceneBase:GetClassName()
	return self.str_class_name
end

function SceneBase:GetName()
	return self.str_scene_name
end

function SceneBase:GetCCObj()
	return self.cc_scene
end

function SceneBase:SysMsg(szMsg, str_color)
	local tb_ui = self:GetUI()
	if tb_ui then
		Ui:SysMsg(tb_ui, szMsg, str_color)
	end
end