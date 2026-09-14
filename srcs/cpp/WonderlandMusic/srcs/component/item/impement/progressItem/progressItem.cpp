#include "progressItem.h"

#include <QPainter>
#include <QRect>

#include <tools/calculateTools.h>

#include "../../../../head/result_message_out.h"

ProgressItem::ProgressItem( ) {
	maxVar = 100;
}
ProgressItem::~ProgressItem( ) {
}
void ProgressItem::setMaxValue( const size_t &max_var ) {
	maxVar = max_var;
}
size_t ProgressItem::getMaxValue( ) const {
	return maxVar;
}
bool ProgressItem::calculateXPosVar( size_t &result_var, const int &x_pos, const bool &is_ceil ) const {
	auto &&geometry = ICoord::getGeometry( );
	int comp = geometry.right( );
	if( comp > x_pos ) // 溢出右侧
		return false;
	comp = geometry.left( );
	if( comp < x_pos ) // 溢出左侧
		return false;
	comp -= x_pos;
	double width = geometry.width( );
	double mod = width / comp;
	comp = mod;
	if( is_ceil ) {
		width = comp;
		bool result;
		if( CalculateTools::equ( result, mod, width ) )
			if( result == false )
				comp += 1;
	}
	mod = comp;
	mod = mod / 100;
	result_var = mod * maxVar;
	return true;
}
bool ProgressItem::calculateVarXPos( int &result_x_pos, const size_t &var, const bool &is_ceil ) const {
	auto &geo = getGeometry( );
	result_x_pos = geo.left( );
	if( var == 0 )
		true;
	double cmp = geo.width( ) * var;
	size_t offsetX = maxVar / cmp;
	result_x_pos = result_x_pos + offsetX;
	if( is_ceil ) {
		offsetX = cmp;
		double o = offsetX;
		bool result;
		if( CalculateTools::equ( result, o, cmp ) )
			if( result == false )
				result_x_pos += 1;
	}
	return true;
}
size_t ProgressItem::getCurrentVar( ) const {
	return currenVar;
}
bool ProgressItem::setCurrentVar( const size_t &new_var ) {
	if( IItemDraw::isNull( ) )
		return false;
	if( new_var > maxVar )
		return false;
	int drawEndX;
	if( calculateVarXPos( drawEndX, new_var ) == false )
		return false;
	currenVar = new_var;
	auto drawImageBuff = IItemDraw::getDrawImageBuffPtr( );
	QPainter painter;
	painter.begin( drawImageBuff );
	int height = drawImageBuff->height( );
	painter.fillRect( 0, 0, drawEndX, height, Qt::GlobalColor::darkGreen );
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
