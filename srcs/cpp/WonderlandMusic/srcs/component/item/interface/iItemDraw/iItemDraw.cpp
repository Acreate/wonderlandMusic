#include "iItemDraw.h"

#include <QPainter>
IItemDraw::IItemDraw( ) {
	regClassTypeInfoRef( this );
}
IItemDraw::~IItemDraw( ) {
}
bool IItemDraw::drawToParintr( QPainter &painter ) {
	if( IItemDraw::isShow( ) == false )
		return false;
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
bool IItemDraw::isShow( ) const {
	return show;
}
void IItemDraw::setShow( const bool show ) {
	this->show = show;
}
