#ifndef __BOMB_BULLET_H__
#define __BOMB_BULLET_H__

#include "cocos2d.h"
#include "game_sprite.h"

USING_NS_CC;

class BombSprite : public GameSprite
{
public:
    static BombSprite* create();
    static BombSprite* createWithTexture(Texture2D *pTexture);
    static BombSprite* createWithTexture(Texture2D *pTexture, const Rect& rect);
    static BombSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
    static BombSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    static BombSprite* create(const char *pszFileName);
    static BombSprite* create(const char *pszFileName, const Rect& rect);

    BombSprite(){};
    ~BombSprite(){};

    virtual BOOL IsBomb() {return TRUE;};
    BOOL OnBomb();

    BOOL Init(float power_linear, float power_angular, float radius)
    {
        m_float_power_linear = power_linear;
        m_float_power_angular = power_angular;
        m_float_bomb_radius = radius;
        return TRUE;
    };

    float GetLinearPower() {return m_float_power_linear;};
    float GetAngularPower() {return m_float_power_angular;};
    float GetBombRadius() {return m_float_bomb_radius;};

private:
    float m_float_power_linear;
    float m_float_power_angular;
    float m_float_bomb_radius;    
};

#endif