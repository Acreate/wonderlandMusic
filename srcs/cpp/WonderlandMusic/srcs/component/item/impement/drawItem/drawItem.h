#ifndef DRAWITEM_H_H_HEAD__FILE__
#define DRAWITEM_H_H_HEAD__FILE__
#include "../../interface/iBuff/iBuff.h"
#include "../../interface/iCoord/iCoord.h"

class QString;
class QPainter;
class QRect;
class QImage;

class DrawItem : public ICoord, public IBuff {
public:
	DrawItem( );
	~DrawItem( ) override;
	bool drawToParintr( QPainter &painter ) override;
	virtual bool scaleToImageSize( );
};

#endif // DRAWITEM_H_H_HEAD__FILE__
