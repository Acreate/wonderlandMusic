#include "drawItem.h"

#include <QPainter>
#include <qimage.h>

DrawItem::DrawItem( ) {
	regClassTypeInfoRef( this );
}
DrawItem::~DrawItem( ) {
}
bool DrawItem::drawToParintr( QPainter &painter ) {
	if( IBuff::isNull( ) )
		return false;
	if( ICoord::isEmpty( ) )
		return false;
	painter.drawImage( getGeometry( ), getDraw( ) );
	return true;
}
bool DrawItem::scaleToImageSize( ) {
	if( IBuff::isNull( ) )
		return false;
	auto &image = IBuff::getDraw( );
	ICoord::reSize( image.width( ), image.height( ) );
	return true;
}
