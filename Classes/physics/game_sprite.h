#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__

#include "cocos2d.h"
#include "base.h"
USING_NS_CC;
class b2Body;

class GameSprite : public Sprite
{
public:
    static GameSprite* create();
    static GameSprite* createWithTexture(Texture2D *pTexture);
    static GameSprite* createWithTexture(Texture2D *pTexture, const Rect& rect);
    static GameSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
    static GameSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    static GameSprite* create(const char *pszFileName);
    static GameSprite* create(const char *pszFileName, const Rect& rect);

    GameSprite():m_ptr_b2body(NULL){};
    ~GameSprite();

    virtual BOOL IsBomb() {return FALSE;};
    virtual BOOL OnBomb(){ return FALSE;};
    BOOL SetB2Body(b2Body* ptr_b2body){ m_ptr_b2body = ptr_b2body; return TRUE;};
    b2Body* GetB2Body() { return m_ptr_b2body;};

private:
    bool m_bool_bomb;
    b2Body* m_ptr_b2body;
};

#endif