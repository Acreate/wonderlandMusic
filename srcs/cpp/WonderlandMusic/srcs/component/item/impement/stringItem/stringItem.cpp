#include "stringItem.h"

#include <QPainter>
#include <QString>

#include "../../../../head/result_message_out.h"

StringItem::StringItem( ) {
	string = new QString;
}
StringItem::~StringItem( ) {
	delete string;
}
bool StringItem::setString( const QString &new_string ) {
	if( IItemDraw::loadStringToDraw( new_string ) == false )
		return false;
	*string = new_string;
	return true;
}
const QString & StringItem::getString( ) const {
	return *string;
}
bool StringItem::loadFileToDraw( const QString &load_image_file_path ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, loadFileToDraw, QObject::tr( "该类无法使用 loadFileToDraw" ) );
}
bool StringItem::loadStringToDraw( const QString &set_string_draw_to_buff ) {
	return IItemDraw::loadStringToDraw( set_string_draw_to_buff );
}
bool StringItem::setDraw( const QImage &draw ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, setDraw, QObject::tr( "该类无法使用 setDraw" ) );
}
