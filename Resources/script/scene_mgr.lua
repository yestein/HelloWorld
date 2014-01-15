--=======================================================================
-- File Name    : scene_mgr.lua
-- Creator      : yestein(yestein86@gmail.com)
-- Date         : 2013-11-28 20:57:43
-- Description  :
-- Modify       :
--=======================================================================

if not SceneMgr then
    SceneMgr = {}
end

require("script/scene_base.lua")

if not SceneMgr.tb_class_logic_scene then
    SceneMgr.tb_class_logic_scene = {}
end

function SceneMgr:Init()
	self.tb_logic_scene = {}
end

function SceneMgr:Uninit()
	self.tb_logic_scene = {}
end

function SceneMgr:GetScene(str_name)
	return self.tb_logic_scene[str_name]
end

function SceneMgr:GetSceneObj(str_name)
    local tb_logic_scene = self:GetScene(str_name)
    if tb_logic_scene then
        return tb_logic_scene:GetCCObj()
    end
end

function SceneMgr:GetClass(str_class_name, bool_create)
    if not SceneMgr.tb_class_logic_scene[str_class_name] and bool_create then
        local tb_class = Lib:NewClass(self._SceneBase)
        tb_class.str_class_name = str_class_name
        SceneMgr.tb_class_logic_scene[str_class_name] = tb_class
    end
    return SceneMgr.tb_class_logic_scene[str_class_name]    
end

function SceneMgr:CreateScene(str_name, str_class_name)
	if self.tb_logic_scene[str_name] then
		cclog("Create Scene [%s] Failed! Already Exists", str_name)
		return
	end
    if not str_class_name then
        str_class_name = str_name
    end
     local tb_class = SceneMgr:GetClass(str_class_name)
    if not tb_class then
        return cclog("Error! No Scene Class [%s] !", str_class_name)
    end

	local cc_scene = cc.Scene:create()   
	local tb_logic_scene = Lib:NewClass(tb_class)
    tb_logic_scene:Init(str_name, cc_scene)
    self.tb_logic_scene[str_name] = tb_logic_scene
	return tb_logic_scene
end

function SceneMgr:DestroyScene(str_name)
    if not self.tb_logic_scene[str_name] then
        cclog("Create Scene [%s] Failed! Not Exists", str_name)
        return
    end
    self.tb_logic_scene[str_name]:Uninit()
    self.tb_logic_scene[str_name] = nil
    return tb_logic_scene
end