#include "iCoord.h"

#include <QRect>
QRect * ICoord::getGeometryPtr( ) const {
	return ICoord::geometry;
}
bool ICoord::releaseGeometryPtr( ) {
	if( ICoord::geometry == nullptr )
		return false;
	delete ICoord::geometry;
	ICoord::geometry = nullptr;
	return true;
}
ICoord::ICoord( ) {
	ICoord::geometry = new QRect;
	regClassTypeInfoRef( this );
}
ICoord::~ICoord( ) {
	delete ICoord::geometry;
}
const QRect & ICoord::getGeometry( ) const {
	return *ICoord::geometry;
}
void ICoord::setGeometry( const QRect &geometry ) {
	*this->ICoord::geometry = geometry;
}
void ICoord::setGeometry( const int &x, const int &y, const int &width, const int &height ) {
	*this->ICoord::geometry = QRect( x, y, width, height );
}
bool ICoord::isClick( const QPoint &point ) const {
	return ICoord::geometry->contains( point );
}
bool ICoord::isEmpty( ) const {
	if( ICoord::geometry->width( ) == 0 || ICoord::geometry->height( ) == 0 )
		return true;
	return false;
}
void ICoord::reSize( const int &width, const int &height ) {
	ICoord::geometry->setSize( QSize( width, height ) );
}
void ICoord::moveTo( const int &x, const int &y ) {
	ICoord::geometry->moveTo( x, y );
}
