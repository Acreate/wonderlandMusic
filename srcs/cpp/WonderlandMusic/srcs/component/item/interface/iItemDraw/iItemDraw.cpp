#include "iItemDraw.h"

#include <QPainter>
IItemDraw::IItemDraw( ) {
}
IItemDraw::~IItemDraw( ) {
}
bool IItemDraw::drawToParintr( QPainter &painter ) {
	if( IBuff::isNull( ) )
		return false;
	if( ICoord::isEmpty( ) )
		return false;
	painter.drawImage( getGeometry( ), getDrawImageBuff( ) );
	return true;
}
bool IItemDraw::scaleToImageSize( ) {
	if( IBuff::isNull( ) )
		return false;
	auto image = IBuff::getDrawImageBuffPtr( );
	ICoord::reSize( image->width( ), image->height( ) );
	return true;
}
