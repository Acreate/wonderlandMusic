#include "progressItem.h"

#include <QPainter>
#include <QRect>

#include <head/result_message_out.h>

ProgressItem::ProgressItem( ) : ProgressItem( 1 ) {
}
ProgressItem::ProgressItem( ProgressItemDouble var ) : var( var ) {
	regClassTypeInfoRef( this );
	releaseDrawImageBuff( );
	ProgressItem::drawRect = new QRect;
}

ProgressItem::~ProgressItem( ) {
	delete ProgressItem::drawRect;
}
bool ProgressItem::calculateXPosVar( ProgressItemDouble &result_var, const int &x_pos ) const {
	auto &&geometry = ICoord::getGeometry( );
	auto porgressLeft = geometry.x( );
	if( porgressLeft > x_pos ) // 溢出左侧
		return false;
	result_var = geometry.width( );
	auto porgressRight = porgressLeft + result_var;
	if( porgressRight < x_pos ) // 溢出右侧
		return false;
	ProgressItemDouble offsetX = x_pos - porgressLeft;
	result_var = offsetX / result_var;
	return true;
}
bool ProgressItem::calculateVarXPos( int &result_x_pos, const ProgressItemDouble &new_var ) const {
	if( new_var < 0.0 || new_var > 1.0 )
		return false;
	auto &&geometry = ICoord::getGeometry( );
	result_x_pos = geometry.width( ) * new_var;
	return true;
}
ProgressItem::ProgressItemDouble ProgressItem::getCurrentVar( ) const {
	return var;
}

bool ProgressItem::setCurrentVar( const ProgressItemDouble &new_var ) {
	if( new_var > 1.0 || new_var < 0.0 )
		return false;
	var = new_var;
	int width = IItemDraw::getGeometry( ).width( );
	width = width * var;
	ProgressItem::drawRect->setWidth( width );
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
	painter.fillRect( *ProgressItem::drawRect, Qt::GlobalColor::darkGreen );
	return true;
}
void ProgressItem::moveTo( const int &x, const int &y ) {
	IItemDraw::moveTo( x, y );
	ProgressItem::drawRect->moveTo( x, y );
}
void ProgressItem::reSize( const int &width, const int &height ) {
	IItemDraw::reSize( width, height );
	ProgressItem::drawRect->setSize( QSize( width * var, height ) );
}
void ProgressItem::setGeometry( const QRect &geometry ) {
	IItemDraw::setGeometry( geometry );

	*ProgressItem::drawRect = geometry;
	ProgressItem::drawRect->setWidth( geometry.width( ) * var );
}
void ProgressItem::setGeometry( const int &x, const int &y, const int &width, const int &height ) {
	IItemDraw::setGeometry( x, y, width, height );
	*ProgressItem::drawRect = QRect( x, y, width * var, height );
}
const QRect & ProgressItem::getDrawRect( ) const {
	return *drawRect;
}
