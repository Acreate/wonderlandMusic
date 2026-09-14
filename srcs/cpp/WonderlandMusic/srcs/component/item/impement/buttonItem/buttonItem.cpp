#include "buttonItem.h"

#include <QFileInfo>
#include <qimage.h>

#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <head/result_message_out.h>

#include <tools/instanceTools.h>
bool ButtonItem::updateDrawBuff( ) {
	if( IItemDraw::clear( ) == false )
		return false;
	switch( type ) {
		case Type::Txt :
			if( txt->isEmpty( ) )
				return false;
			return IItemDraw::loadStringToDraw( *txt );
		case Type::Ico :
			if( ico->width( ) == 0 || ico->height( ) == 0 )
				return false;
			return IItemDraw::setDraw( *this->ico );
		case Type::All : {
			if( txt->isEmpty( ) == false )
				if( IItemDraw::loadStringToDraw( *txt ) == false )
					return false;
			if( ico->width( ) == 0 || ico->height( ) == 0 )
				if( IItemDraw::isNull( ) )
					return false;
				else
					return true;
			QImage buff = IItemDraw::getDrawImageBuff( );
			auto appRenderImage = InstanceTools::getAppRenderImage( );
			QImage result;
			if( appRenderImage->appendImage( result, buff, *this->ico ) == false )
				return false;
			return IItemDraw::setDraw( result );
		}
	}

	return false;
}
ButtonItem::ButtonItem( ) {
	txt = new QString;
	ico = new QImage;
}
ButtonItem::~ButtonItem( ) {
	delete txt;
	delete ico;
}
ButtonItem::ButtonItem( ButtonItem::Type type ) : ButtonItem( ) {
	this->type = type;
}
ButtonItem::ButtonItem(const QString &txt ) : ButtonItem( ) {
	type = Type::Txt;
	setTxt( txt );
}
ButtonItem::ButtonItem(const QImage &ico ) : ButtonItem( ) {
	type = Type::Ico;
	setIco( ico );
}
ButtonItem::Type ButtonItem::getType( ) const {
	return type;
}
bool ButtonItem::setType( const ButtonItem::Type &new_type ) {
	if( new_type == type )
		return true;
	auto old = type;
	type = new_type;
	if( updateDrawBuff( ) )
		return true;
	type = old;
	return false;
}
const QString & ButtonItem::getTxt( ) const {
	return *txt;
}
const QImage & ButtonItem::getIco( ) const {
	return *ico;
}
bool ButtonItem::clear( ) {
	bool result = IItemDraw::clear( );
	if( result == false )
		return false;
	*ico = QImage( );
	txt->clear( );
	return result;
}
bool ButtonItem::loadFileToDraw( const QString &load_image_file_path ) {
	QFileInfo info( load_image_file_path );
	if( info.exists( ) == false )
		return false;
	auto fileName = info.absoluteFilePath( );
	QImage load;
	if( load.load( fileName ) == false )
		return false;
	return ButtonItem::setIco( load );
}
bool ButtonItem::loadStringToDraw( const QString &set_string_draw_to_buff ) {
	return setTxt( set_string_draw_to_buff );
}
bool ButtonItem::setIco( const QImage &ico ) {
	*this->ico = ico;
	return updateDrawBuff( );
}
bool ButtonItem::setTxt( const QString &txt ) {
	*this->txt = txt;
	return updateDrawBuff( );
}
bool ButtonItem::setDraw( const QImage &draw ) {
	return ButtonItem::setIco( draw );
}
bool ButtonItem::drawToParintr( QPainter &painter ) {
	return IItemDraw::drawToParintr( painter );
}
