#pragma once
#ifndef IWodUmbraObject_H
#define IWodUmbraObject_H

const int WcoOK = 1;
const int WcoNotReady = 2;
const int WcoFailed = -1;

namespace Umbra
{
    class Cell;
}

BLUE_INTERFACE( IWodUmbraObject ) : public IRoot
{
    virtual void RemoveFromCell() = 0;
    virtual int AddToCell( Umbra::Cell* cell ) = 0;
};

#endif // IWodUmbraObject_H
