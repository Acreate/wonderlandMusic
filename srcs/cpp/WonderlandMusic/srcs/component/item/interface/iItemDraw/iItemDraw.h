#ifndef IITEMDRAW_H_H_HEAD__FILE__
#define IITEMDRAW_H_H_HEAD__FILE__
#include "../iBuff/iBuff.h"

#include "../iCoord/iCoord.h"

class QPainter;

class IItemDraw : public ICoord, public IBuff {
private:
	bool show = true;

public:
	IItemDraw( );
	~IItemDraw( ) override;
	bool drawToParintr( QPainter &painter ) override;
	virtual bool scaleToImageSize( );
	virtual bool isShow( ) const;
	virtual void setShow( const bool show );
};

#endif // IITEMDRAW_H_H_HEAD__FILE__
