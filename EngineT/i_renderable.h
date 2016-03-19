#pragma once

class IRenderable
{
public:

    virtual ~IRenderable() {}

    virtual void GetWorldMatrix() = 0;
};