#include "game_sprite.h"
#include "game_physics_world.h"

GameSprite::~GameSprite()
{
    if (m_ptr_b2body)
    {
        GamePhysicsWorld::GetInstance()->GetWorld()->DestroyBody(m_ptr_b2body);
        m_ptr_b2body = NULL;
    }
    
}

GameSprite* GameSprite::create()
{
    GameSprite* pRet = new GameSprite();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

GameSprite* GameSprite::createWithTexture(Texture2D *pTexture)
{
    GameSprite* pRet = new GameSprite();
    if (pRet && pRet->initWithTexture(pTexture))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

GameSprite* GameSprite::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
    GameSprite* pRet = new GameSprite();
    if (pRet && pRet->initWithTexture(pTexture, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

GameSprite* GameSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    GameSprite* pRet = new GameSprite();
    if (pRet && pRet->initWithSpriteFrame(pSpriteFrame))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

GameSprite* GameSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    GameSprite* pRet = new GameSprite();
    if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

GameSprite* GameSprite::create(const char *pszFileName)
{
    GameSprite* pRet = new GameSprite();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

GameSprite* GameSprite::create(const char *pszFileName, const Rect& rect)
{
    GameSprite* pRet = new GameSprite();
    if (pRet && pRet->initWithFile(pszFileName, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}
