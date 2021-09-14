#pragma once
#include "AnimationSprite.h"
class Explosion :
    public BaseObject
{
public:
    Explosion(Vector2 position, int type, int size);
    ~Explosion();

    void		Init() override;
    void		Draw() override;
    void		Update(GLfloat deltatime) override;

    void        Spawn(Vector2 position, int type, int size);

    bool        m_isFinish;
protected:
    std::shared_ptr<AnimationSprite> m_anim;

};

