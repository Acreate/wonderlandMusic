#include "stringItem.h"

#include <QPainter>
#include <QString>

StringItem::StringItem( ) {
	string = new QString;
}
StringItem::~StringItem( ) {
	delete string;
}
void StringItem::setString( const QString &new_string ) {
	*string = new_string;
}
const QString & StringItem::getString( ) const {
	return *string;
}
bool StringItem::drawToParintr( QPainter &painter ) {
	if( IBuff::isNull( ) )
		return false;
	if( ICoord::isEmpty( ) )
		return false;
	painter.drawImage( getGeometry( ), getDraw( ) );
	return true;
}
