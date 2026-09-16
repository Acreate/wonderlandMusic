#include "timeItem.h"

#include <QString>

#include "../../../../dateTimeFormat/dateTimeFormat.h"

#include "../../../../head/result_message_out.h"
TimeItem::TimeItem( const QTime &set_time ) {
}
TimeItem::TimeItem( ) {
}
TimeItem::~TimeItem( ) {
}
const QTime & TimeItem::getTime( ) const {
	return *time;
}
bool TimeItem::setTime( const QTime &set_time ) {
	*TimeItem::time = set_time;
	return false;
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
	QString result;
	int varNumber = time->hour( );
	if( varNumber != 0 )
		if( varNumber < 10 )
			result += "0" + QString::number( varNumber ) + ":";
		else
			result += QString::number( varNumber ) + ":";
	varNumber = time->minute( );
	result += QString::asprintf( "%02d:", varNumber );
	varNumber = time->second( );
	result += QString::asprintf( "%02d", varNumber );
	return result;
}
