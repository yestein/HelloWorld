--=======================================================================
-- File Name    : main_scene.lua
-- Creator      : yestein(yestein86@gmail.com)
-- Date         : 2013-12-15 12:17:43
-- Description  :
-- Modify       :
--=======================================================================

local MainScene = SceneMgr:GetClass("MainScene", 1)

function MainScene:_Init()

	local tbVisibleSize = CCDirector:getInstance():getVisibleSize()
	local tbOrigin = CCDirector:getInstance():getVisibleOrigin()
    local nOffsetX = tbVisibleSize.width / 2
    local nOffsetY = tbVisibleSize.height / 2

    local cc_layer_main = self:GetLayer("main")

    local spriteBG = CCSprite:create(Def.szMainBGImg)
    local tbRect = spriteBG:getTextureRect()
    local scale = tbVisibleSize.width / tbRect.width
    spriteBG:setPosition(tbOrigin.x, tbOrigin.y)
    spriteBG:setScale(scale)
    cc_layer_main:setPosition(nOffsetX, nOffsetY)
    cc_layer_main:addChild(spriteBG)

    local layerMainMenu = MenuMgr:CreateMenu("MainMenu")
    layerMainMenu:setPosition(20, tbVisibleSize.height - 80)
    self:AddLayer("MainMenu", layerMainMenu, Def.ZOOM_LEVEL_MENU)
    local tbElement = {
        {
            [1] = {
                szItemName = "运行Demo",
                fnCallBack = function()
                    GameMgr:LoadScene("DemoScene")
                end,
            },
        },
        {
            [1] = {
                szItemName = "物理引擎测试",
                fnCallBack = function()
                    GameMgr:LoadScene("PhysicsScene")
                end,
            },
        },
        {
            [1] = {
                szItemName = "cocoStudio导入测试",
                fnCallBack = function()
                    GameMgr:TestCocoStudio()
                end,
            },
        },
        {
            [1] = {
                szItemName = "弹坑测试（包含物理破坏）",
                fnCallBack = function()
                    GameMgr:LoadScene("PolygonBreak")
                end,
            },
        },
        {
            [1] = {
                szItemName = "机械构建测试",
                fnCallBack = function()
                    GameMgr:LoadScene("ConstructScene")
                end,
            },
        },
        {
            [1] = {
                szItemName = "详细爆炸受力分析测试",
                fnCallBack = function()
                    Ui:SysMsg(self:GetUI(), "功能暂未开放", "red")
                end,
            },
        },
        {
            [1] = {
                szItemName = "AI测试",
                fnCallBack = function()
                    Ui:SysMsg(self:GetUI(),"功能暂未开放", "red")
                end,
            },
        },
        {
            [1] = {
                szItemName = "联机测试",
                fnCallBack = function()
                    Ui:SysMsg(self:GetUI(),"功能暂未开放", "red")
                end,
            },
        },
    }
    MenuMgr:UpdateByString("MainMenu", tbElement, 
        {szFontName = Def.szMenuFontName, nSize = 26, szAlignType = "left", nIntervalX = 20, nIntervalY = 20}
    )
    local tb_ui = self:GetUI()
    Ui:AddElement(tb_ui, "LabelTTF", "Title", tbVisibleSize.width / 2, tbVisibleSize.height -50, "Demo功能一览", nil, 40)

	return 1
end

function MainScene:_Uninit()
    -- body
end