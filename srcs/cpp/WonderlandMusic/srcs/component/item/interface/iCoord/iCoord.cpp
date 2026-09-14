#include "iCoord.h"

#include <QRect>
ICoord::ICoord( ) {
	geometry = new QRect;
	regClassTypeInfoRef( this );
}
ICoord::~ICoord( ) {
	delete geometry;
}
const QRect & ICoord::getGeometry( ) const {
	return *geometry;
}
void ICoord::setGeometry( const QRect &geometry ) {
	*this->geometry = geometry;
}
bool ICoord::isClick( const QPoint &point ) const {
	return geometry->contains( point );
}
bool ICoord::isEmpty( ) const {
	if( geometry->width( ) == 0 || geometry->height( ) == 0 )
		return true;
	return false;
}
void ICoord::reSize( const int &width, const int &height ) {
	*geometry = QRect( geometry->x( ), geometry->y( ), width, height );
}
void ICoord::moveTo( const int &x, const int &y ) {
	*geometry = QRect( x, y, geometry->width( ), geometry->height( ) );
}
