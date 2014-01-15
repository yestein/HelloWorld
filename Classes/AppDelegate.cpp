#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "physics/tolua_lua_module.hpp"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

class LuaBombCallBack : public BombCallback
{
    virtual bool BeBombed(GameSprite* ptr_sprite)
    {
        auto engine = LuaEngine::getInstance();
        auto L = engine->getLuaStack()->getLuaState();
        lua_getglobal(L, "CPPEvent");
        lua_pushstring(L, "BeBombed");
        tolua_pushusertype(L ,(void*)ptr_sprite, "GameSprite");
        lua_pcall(L, 2, 0, -3);

        return true;
    }
};

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    director->setOpenGLView(EGLView::getInstance());

    EGLView::getInstance()->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // register lua engine
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    tolua_lua_module_open(engine->getLuaStack()->getLuaState());

#ifdef _DEBUG
    engine->executeString("_DEBUG = 1");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	engine->executeString("device = \"win32\"");
#endif

    std::string path = FileUtils::getInstance()->fullPathForFilename("script/main.lua");
    engine->executeScriptFile(path.c_str());
    LuaBombCallBack* ptr_lua_callback = new LuaBombCallBack();
    GamePhysicsWorld::GetInstance()->SetupBombCallBack(ptr_lua_callback);

	auto LuaStack = engine->getLuaStack();
	engine->executeGlobalFunction("test");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
