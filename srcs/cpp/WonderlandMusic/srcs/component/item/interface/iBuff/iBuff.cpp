#include "iBuff.h"

#include <QFileInfo>
#include <qimage.h>

#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <tools/instanceTools.h>
QImage * IBuff::getDrawImageBuffPtr( ) const {
	return drawImageBuff;
}
bool IBuff::releaseDrawImageBuff( ) {
	if( drawImageBuff == nullptr )
		return false;
	delete drawImageBuff;
	drawImageBuff = nullptr;
	return true;
}
IBuff::IBuff( ) {
	drawImageBuff = new QImage;
	regClassTypeInfoRef( this );
}
IBuff::~IBuff( ) {
	if( drawImageBuff )
		delete drawImageBuff;
}
QImage IBuff::getDrawImageBuff( ) const {
	QImage imageBuff;
	if( drawImageBuff == nullptr )
		return imageBuff;
	imageBuff = *drawImageBuff;
	imageBuff.detach( );
	return imageBuff;
}
bool IBuff::setDraw( const QImage &draw ) {
	if( draw.width( ) == 0 || draw.height( ) == 0 )
		return false;
	if( drawImageBuff == nullptr )
		this->drawImageBuff = new QImage( draw );
	else
		*this->drawImageBuff = draw;
	this->drawImageBuff->detach( );
	return this->drawImageBuff->isDetached( );
}
bool IBuff::isNull( ) const {
	if( drawImageBuff == nullptr || drawImageBuff->width( ) == 0 || drawImageBuff->height( ) == 0 )
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
bool IBuff::loadStringToDraw( const QString &set_string_draw_to_buff ) {
	if( set_string_draw_to_buff.isEmpty( ) )
		return IBuff::clear( );
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	QImage buff;
	bool result = appRenderImage->renderTxt( buff, set_string_draw_to_buff );
	if( result == false )
		return false;
	return IBuff::setDraw( buff );
}
bool IBuff::clear( ) {
	if( IBuff::isNull( ) )
		return true;
	*drawImageBuff = QImage( );
	return true;
}
bool IBuff::zoomTo( const int &width, const int &height ) {
	if( IBuff::isNull( ) )
		return false;
	*drawImageBuff = drawImageBuff->scaled( width, height );
	return true;
}
bool IBuff::zoomToWidth( const int &width ) {
	if( IBuff::isNull( ) )
		return false;
	*drawImageBuff = drawImageBuff->scaledToWidth( width );
	return true;
}
bool IBuff::zoomToHeight( const int &height ) {
	if( IBuff::isNull( ) )
		return false;
	*drawImageBuff = drawImageBuff->scaledToHeight( height );
	return true;
}
