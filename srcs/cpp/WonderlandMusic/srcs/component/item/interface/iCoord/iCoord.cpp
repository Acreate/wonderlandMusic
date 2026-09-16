#include "iCoord.h"

#include <QRect>
QRect * ICoord::getGeometryPtr( ) const {
	return ICoord::geometry;
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
	*ICoord::geometry = QRect( ICoord::geometry->x( ), ICoord::geometry->y( ), width, height );
}
void ICoord::moveTo( const int &x, const int &y ) {
	*ICoord::geometry = QRect( x, y, ICoord::geometry->width( ), ICoord::geometry->height( ) );
}
