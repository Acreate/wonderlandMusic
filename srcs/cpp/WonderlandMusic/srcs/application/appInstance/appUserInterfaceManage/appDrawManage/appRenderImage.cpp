#include "appRenderImage.h"

#include <QFontDatabase>
#include <QPainter>
#include <QWidget>

#include <head/release_macro.h>
#include <head/result_message_out.h>

bool AppRenderImage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( brackGroundColor );
	Delete_Resource_App_Core_Ptr( drawPenColor );
	Delete_Resource_App_Core_Ptr( drawPen );
	Delete_Resource_App_Core_Ptr( font );
	Delete_Resource_App_Core_Ptr( fontMetrics );
	return true;
}

AppRenderImage::AppRenderImage( ) {
	regClassTypeInfoRef( this );
}

AppRenderImage::~AppRenderImage( ) {
	deleteResource( );
}

bool AppRenderImage::initBefore( ) {
	deleteResource( );
	return true;
}

bool AppRenderImage::initAfter( ) {
	return true;
}

bool AppRenderImage::init( ) {
	brackGroundColor = new QColor( 0, 0, 0, 0 );
	drawPenColor = new QColor( 0, 0, 0, 255 );
	drawPen = new QPen( *drawPenColor );
	font = new QFont( "Microsoft YaHei", 14 );
	fontMetrics = new QFontMetrics( *font );
	auto ttfFilePath = "./program/font/Alibaba/Alibaba-PuHuiTi-Medium.ttf";
	// 使用外部字体，加载字体
	int fontId = QFontDatabase::addApplicationFont( ttfFilePath );

	if( fontId == -1 )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, nullptr, QFontDatabase::addApplicationFont, QObject:: tr("配置文字路径异常: %1").arg( ttfFilePath ) );

	QStringList familyList = QFontDatabase::applicationFontFamilies( fontId );
	if( familyList.isEmpty( ) )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, nullptr, QFontDatabase::applicationFontFamilies, QObject:: tr("配置文字异常: %1").arg( fontId ) );

	QString familyName = familyList.first( );
	*font = QFont( familyName, 14 );
	*fontMetrics = QFontMetrics( *font );
	return true;
}

const QFont * AppRenderImage::getFont( ) const {
	return font;
}

const QFontMetrics * AppRenderImage::getFontMetrics( ) const {
	return fontMetrics;
}
bool AppRenderImage::appendImage( QImage &result_render_image, const QImage &left, const QImage &right ) const {
	int leftHeight = left.height( );

	int targetHeight = right.height( );
	if( targetHeight < leftHeight )
		targetHeight = leftHeight;
	leftHeight = left.width( );
	int targetWidth = leftHeight + right.width( );
	if( targetWidth == 0 || targetHeight == 0 )
		return false;
	result_render_image = QImage( targetWidth, targetHeight, QImage::Format_RGBA8888 );
	result_render_image.fill( 0 );
	QPainter painter;
	painter.begin( &result_render_image );

	painter.drawImage( 0, 0, left );
	painter.drawImage( leftHeight, 0, right );

	painter.end( );
	return true;
}

bool AppRenderImage::renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font, const QFontMetrics &font_metrics ) const {
	int renderWidth = font_metrics.horizontalAdvance( render_txt );
	int fontHeight = font_metrics.height( );
	auto buffImage = QImage( renderWidth, fontHeight, QImage::Format_RGBA8888 );
	if( buffImage.isNull( ) )
		return false;
	buffImage.fill( 0 );
	QPainter painter;
	painter.begin( &buffImage );
	painter.fillRect( 0, 0, renderWidth, fontHeight, *brackGroundColor );
	painter.setPen( *drawPen );
	painter.setFont( font );
	painter.drawText( 0, font_metrics.ascent( ), render_txt );
	painter.end( );
	result_render_image = buffImage;
	return true;
}

bool AppRenderImage::getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFontMetrics &font_metrics ) const {
	if( render_txt.isEmpty( ) )
		return false;
	result_txt_size = QSize( font_metrics.horizontalAdvance( render_txt ), font_metrics.height( ) );
	return true;
}
bool AppRenderImage::renderTxt( QImage &result_render_image, const QString &render_txt ) const {
	return renderTxt( result_render_image, render_txt, *font, *fontMetrics );
}
bool AppRenderImage::renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font ) const {
	if( &font == this->font || font == *this->font )
		return renderTxt( result_render_image, render_txt, *this->font, *this->fontMetrics );
	return renderTxt( result_render_image, render_txt, font, QFontMetrics( font ) );
}
bool AppRenderImage::getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFont &font ) const {
	return getTxtSize( result_txt_size, render_txt, QFontMetrics( font ) );
}
bool AppRenderImage::getTxtSize( QSize &result_txt_size, const QString &render_txt ) const {
	return getTxtSize( result_txt_size, render_txt, *this->fontMetrics );
}

bool AppRenderImage::renderWidget( QImage &result_render_image, QWidget *render_widget ) const {
	if( render_widget == nullptr )
		return false;

	render_widget->adjustSize( );
	QSize size = render_widget->size( );
	QImage buff = QImage( size, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	QPainter painter;
	painter.begin( &buff );
	int width = size.width( );
	int height = size.height( );
	painter.fillRect( 0, 0, width, height, *brackGroundColor );
	render_widget->render( &painter );
	painter.end( );

	return true;
}
