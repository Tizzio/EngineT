
#ifndef CALLBACKS_H
#define	CALLBACKS_H

class ICallbacks
{
public:

    virtual void RenderSceneCB() = 0;

    virtual void IdleCB() = 0;
};

#endif	/* I3DAPPLICATION_H */

