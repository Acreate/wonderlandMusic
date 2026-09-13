#include "progressItem.h"

#include <QRect>

#include "../../../tools/calculateTools.h"
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
		if( CalculateTools::equ( mod, width ) == false )
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
		if( CalculateTools::equ( o, cmp ) == false )
			result_x_pos += 1;
	}
	return true;
}
