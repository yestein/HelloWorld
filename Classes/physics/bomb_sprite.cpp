#include "bomb_sprite.h"
#include "base.h"

BombSprite* BombSprite::create()
{
    BombSprite* pRet = new BombSprite();
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

BombSprite* BombSprite::createWithTexture(Texture2D *pTexture)
{
    BombSprite* pRet = new BombSprite();
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

BombSprite* BombSprite::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
    BombSprite* pRet = new BombSprite();
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

BombSprite* BombSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    BombSprite* pRet = new BombSprite();
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

BombSprite* BombSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    BombSprite* pRet = new BombSprite();
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

BombSprite* BombSprite::create(const char *pszFileName)
{
    BombSprite* pRet = new BombSprite();
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

BombSprite* BombSprite::create(const char *pszFileName, const Rect& rect)
{
    BombSprite* pRet = new BombSprite();
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

BOOL BombSprite::OnBomb()
{
	int num_result = FALSE;
	int num_ret_code = FALSE;
{
    Node* node_parent = this->getParent();
    KGLOG_PROCESS_ERROR(node_parent);
    Point bomb_postion = this->getPosition();
    auto ptr_sprite_bomb = BombSprite::create("image/bomb.png");
    ptr_sprite_bomb->setPosition(bomb_postion);
    node_parent->addChild(ptr_sprite_bomb, 1);
    ptr_sprite_bomb->setScale(0.1f);
    ScaleTo* scale= ScaleTo::create(0.05f, 1.0f);
    DelayTime* delay_time = DelayTime::create(0.5f);
    RemoveSelf* remove_self = CCRemoveSelf::create();
    ptr_sprite_bomb->runAction(Sequence::create(scale, delay_time, remove_self, NULL));

    MoveBy* move_left = MoveBy::create(0.02f, Point(-3.0f, 0.0f));
    MoveBy* move_right = MoveBy::create(0.02f, Point(3.0f, 0.0f));
    node_parent->runAction(Sequence::create(move_left, move_right, move_right, move_left, move_left, move_right, NULL));
    node_parent->removeChild(this);
}

	num_result = TRUE;
Exit0:
	return num_result;
}
