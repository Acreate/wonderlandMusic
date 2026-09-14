#include "iBuff.h"

#include <QFileInfo>
#include <qimage.h>

#include "../../../../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "../../../../tools/instanceTools.h"
QImage * IBuff::getDrawImageBuffPtr( ) const {
	return drawImageBuff;
}
IBuff::IBuff( ) {
	drawImageBuff = new QImage;
	regClassTypeInfoRef( this );
}
IBuff::~IBuff( ) {
	delete drawImageBuff;
}
QImage IBuff::getDrawImageBuff( ) const {
	auto imageBuff = *drawImageBuff;
	imageBuff.detach( );
	return imageBuff;
}
bool IBuff::setDraw( const QImage &draw ) {
	if( draw.width( ) == 0 || draw.height( ) == 0 )
		return false;
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
	return appRenderImage->renderTxt( *drawImageBuff, set_string_draw_to_buff );
}
bool IBuff::clear( ) {
	if( IBuff::isNull( ) )
		return true;
	*drawImageBuff = QImage( );
	return true;
}
