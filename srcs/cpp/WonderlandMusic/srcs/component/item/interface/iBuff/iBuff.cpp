#include "iBuff.h"

#include <QFileInfo>
#include <qimage.h>

#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <tools/instanceTools.h>
QImage * IBuff::getDrawImageBuffPtr( ) const {
	return IBuff::drawImageBuff;
}
bool IBuff::releaseDrawImageBuff( ) {
	if( IBuff::drawImageBuff == nullptr )
		return false;
	delete IBuff::drawImageBuff;
	IBuff::drawImageBuff = nullptr;
	return true;
}
IBuff::IBuff( ) {
	IBuff::drawImageBuff = new QImage;
	regClassTypeInfoRef( this );
}
IBuff::~IBuff( ) {
	if( IBuff::drawImageBuff )
		delete IBuff::drawImageBuff;
}
QImage IBuff::getDrawImageBuff( ) const {
	QImage imageBuff;
	if( IBuff::drawImageBuff == nullptr )
		return imageBuff;
	imageBuff = *IBuff::drawImageBuff;
	imageBuff.detach( );
	return imageBuff;
}
bool IBuff::setDraw( const QImage &draw ) {
	if( draw.width( ) == 0 || draw.height( ) == 0 )
		return false;
	if( IBuff::drawImageBuff == nullptr )
		this->IBuff::drawImageBuff = new QImage( draw );
	else
		*this->IBuff::drawImageBuff = draw;
	this->IBuff::drawImageBuff->detach( );
	return this->IBuff::drawImageBuff->isDetached( );
}
bool IBuff::isNull( ) const {
	if( IBuff::drawImageBuff == nullptr || IBuff::drawImageBuff->width( ) == 0 || IBuff::drawImageBuff->height( ) == 0 )
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
	*IBuff::drawImageBuff = QImage( );
	return true;
}
bool IBuff::zoomTo( const int &width, const int &height ) {
	if( IBuff::isNull( ) )
		return false;
	*IBuff::drawImageBuff = IBuff::drawImageBuff->scaled( width, height );
	return true;
}
bool IBuff::zoomToWidth( const int &width ) {
	if( IBuff::isNull( ) )
		return false;
	*IBuff::drawImageBuff = IBuff::drawImageBuff->scaledToWidth( width );
	return true;
}
bool IBuff::zoomToHeight( const int &height ) {
	if( IBuff::isNull( ) )
		return false;
	*IBuff::drawImageBuff = IBuff::drawImageBuff->scaledToHeight( height );
	return true;
}
