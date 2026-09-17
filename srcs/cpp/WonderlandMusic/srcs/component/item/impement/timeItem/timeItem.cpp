#include "timeItem.h"

#include <QTime>
#include <qfont.h>

#include <head/result_message_out.h>

#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <dateTimeFormat/dateTimeFormat.h>

#include <tools/instanceTools.h>

bool TimeItem::rePaintBuff( ) {
	
	if( TimeItem::time == nullptr || TimeItem::font == nullptr )
		return false;

	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	bool result = appRenderImage->renderTxt( *getDrawImageBuffPtr( ), toString( ), *TimeItem::font );
	if( result == false )
		return false;
	return true;
}
TimeItem::TimeItem( const QTime &set_time, const QFont &set_font ) {
	TimeItem::time = new QTime( set_time );
	TimeItem::font = new QFont( set_font );
}
TimeItem::TimeItem( const QTime &set_time ) {
	TimeItem::time = new QTime( set_time );
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage ) {
		auto font = appRenderImage->getFont( );
		if( font )
			TimeItem::font = new QFont( *font );
	}
	if( TimeItem::font == nullptr )
		TimeItem::font = new QFont( );
}
TimeItem::TimeItem( ) : TimeItem( QTime( ) ) {
}
TimeItem::~TimeItem( ) {
}
bool TimeItem::setFontSize( const int &new_font_sizet ) {
	if( TimeItem::font == nullptr )
		return false;
	TimeItem::font->setPixelSize( new_font_sizet );
	return rePaintBuff( );
}
const QFont & TimeItem::getFont( ) const {
	return *font;
}
bool TimeItem::setFont( const QFont &set_font ) {
	if( TimeItem::font == nullptr )
		return false;
	*TimeItem::font = set_font;
	return rePaintBuff( );
}
const QTime & TimeItem::getTime( ) const {
	return *TimeItem::time;
}
bool TimeItem::setTime( const QTime &set_time ) {
	if( TimeItem::time == nullptr )
		return false;
	*TimeItem::time = set_time;
	return rePaintBuff( );
}
bool TimeItem::setTime( const std::chrono::milliseconds &set_time ) {
	*TimeItem::time = QTime::fromMSecsSinceStartOfDay( set_time.count( ) );
	return rePaintBuff( );
}
bool TimeItem::loadFileToDraw( const QString &load_image_file_path ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, loadFileToDraw, QObject::tr( "该类无法使用 loadFileToDraw" ) );
}
bool TimeItem::loadStringToDraw( const QString &set_string_draw_to_buff ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, loadStringToDraw, QObject::tr( "该类无法使用 loadStringToDraw" ) );
}
bool TimeItem::setDraw( const QImage &draw ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, setDraw, QObject::tr( "该类无法使用 setDraw" ) );
}
QString TimeItem::toString( ) const {
	return DateTimeFormat::millsecondToHourMinSecFrom( *TimeItem::time, true );
}
bool TimeItem::drawToParintr( QPainter &painter ) {
	return IItemDraw::drawToParintr( painter );
}
