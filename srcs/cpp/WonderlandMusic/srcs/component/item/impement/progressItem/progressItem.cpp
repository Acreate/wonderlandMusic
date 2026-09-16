#include "progressItem.h"

#include <QPainter>
#include <QRect>

#include <head/result_message_out.h>

ProgressItem::ProgressItem( ) : ProgressItem( 100 ) {
}
ProgressItem::ProgressItem( ProgressItemDouble var ) : var( var ) {
	regClassTypeInfoRef( this );
	releaseDrawImageBuff( );
}

ProgressItem::~ProgressItem( ) {
}
bool ProgressItem::calculateXPosVar( ProgressItemDouble &result_var, const int &x_pos ) const {
	auto &&geometry = ICoord::getGeometry( );
	auto porgressRight = geometry.right( );
	if( porgressRight > x_pos ) // 溢出右侧
		return false;
	auto porgressLeft = geometry.left( );
	if( porgressRight < x_pos ) // 溢出左侧
		return false;
	result_var = porgressRight - porgressLeft;
	ProgressItemDouble offsetX = x_pos - porgressLeft;
	result_var = result_var / offsetX;
	return true;
}
bool ProgressItem::calculateVarXPos( int &result_x_pos, const ProgressItemDouble &new_var ) const {
	if( new_var < 0 || new_var > ( ( ProgressItemDouble ) 100 ) )
		return false;
	auto &&geometry = ICoord::getGeometry( );
	result_x_pos = geometry.width( ) * new_var;
	return true;
}
ProgressItem::ProgressItemDouble ProgressItem::getCurrentVar( ) const {
	return var;
}

bool ProgressItem::setCurrentVar( const ProgressItemDouble &new_var ) {
	if( new_var < 0 || new_var > ( ( ProgressItemDouble ) 100 ) )
		return false;
	var = new_var;
	auto &&geometry = ICoord::getGeometry( );
	auto width = geometry.width( ) * var;
	auto drawImageBuff = IItemDraw::getDrawImageBuffPtr( );
	QPainter painter;
	painter.begin( drawImageBuff );
	int height = drawImageBuff->height( );
	painter.fillRect( 0, 0, width, height, Qt::GlobalColor::darkGreen );
	painter.end( );
	return true;
}
bool ProgressItem::loadFileToDraw( const QString &load_image_file_path ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, loadFileToDraw, QObject::tr( "该类无法使用 loadFileToDraw" ) );
}
bool ProgressItem::loadStringToDraw( const QString &set_string_draw_to_buff ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, loadStringToDraw, QObject::tr( "该类无法使用 loadStringToDraw" ) );
}
bool ProgressItem::setDraw( const QImage &draw ) {
	return Result_Var_Function_Messag_Ptr_Out_Args( false, this, setDraw, QObject::tr( "该类无法使用 setDraw" ) );
}
bool ProgressItem::drawToParintr( QPainter &painter ) {
	auto &&geometry = ICoord::getGeometry( );
	auto width = geometry.width( ) * var / 100.0L;
	int height = geometry.height( );
	int x = geometry.x( );
	int y = geometry.y( );
	painter.fillRect( x, y, width, height, Qt::GlobalColor::darkGreen );
	return true;
}
