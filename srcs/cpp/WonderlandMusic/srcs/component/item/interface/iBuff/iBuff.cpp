#include "iBuff.h"

#include <QFileInfo>
#include <qimage.h>
IBuff::IBuff( ) {
	draw = new QImage;
	regClassTypeInfoRef( this );
}
IBuff::~IBuff( ) {
	delete draw;
}
const QImage & IBuff::getDraw( ) const {
	return *draw;
}
bool IBuff::setDraw( const QImage &draw ) {
	if( draw.width( ) == 0 || draw.height( ) == 0 )
		return false;
	*this->draw = draw;
	this->draw->detach( );
	return this->draw->isDetached( );
}
bool IBuff::isNull( ) const {
	if( draw == nullptr || draw->width( ) == 0 || draw->height( ) == 0 )
		return true;
	return false;
}
bool IBuff::loadFileToDraw( const QString &load_image_file_path ) {
	QFileInfo loadFile( load_image_file_path );
	if( loadFile.exists( ) == false )
		return false;
	auto absoluteFilePath = loadFile.absoluteFilePath( );
	QImage buff;
	if( buff.load( absoluteFilePath ) == false )
		return false;
	if( IBuff::setDraw( buff ) == false )
		return false;
	return IBuff::isNull( );
}
