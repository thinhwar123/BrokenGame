#pragma once
#include "Sprite2D.h"
class AnimationSprite :
    public Sprite2D
{
public:
    AnimationSprite();
    AnimationSprite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);

    void		Init() override;
    void		Draw() override;
    void		Update(GLfloat deltatime) override;

    int m_numFrames;
    int m_currentFrame;
    float m_frameTime;
    float m_currentFrameTime;
};

