#include "musicFavoriteWidget.h"

#include <QMouseEvent>

#include <component/musicWindow/interface/ItemWidget/iMusicFavoriteItemWidget.h>
#include <component/musicWindow/interface/info/iMusicDataManage.h>
#include <component/musicWindow/interface/item/iMusicFavoriteItem.h>
#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>

#include <head/result_message_out.h>

#include "../../head/release_macro.h"

MusicFavoriteWidget::MusicFavoriteWidget( ) {
	regClassTypeInfoRef( this );
}
MusicFavoriteWidget::~MusicFavoriteWidget( ) {
	deleteResource( );
}
bool MusicFavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicFavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicFavoriteWidget::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
QWidget * MusicFavoriteWidget::toWidget( ) {
	return this;
}
IMusicCentreWidget * MusicFavoriteWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
void MusicFavoriteWidget::peelMusicFavoriteItem( ) {
	if( defaultItem ) {
		defaultItem->setMusicCentreWidget( nullptr );
		auto musicFavoriteItemWidget = defaultItem->getMusicFavoriteItemWidget( );
		if( musicFavoriteItemWidget )
			musicFavoriteItemWidget->setMusicFavoriteWidget( nullptr );
	}
	size_t count = musicFavoriteItems.size( );
	if( count ) {
		auto data = musicFavoriteItems.data( );
		size_t index = 0;
		for( ; index < count; index += 1 ) {
			auto musicFavoriteItemWidget = data[ index ]->getMusicFavoriteItemWidget( );
			musicFavoriteItemWidget->setMusicFavoriteWidget( nullptr );
		}
	}
	defaultItem = nullptr;
	musicFavoriteItems.clear( );
}
bool MusicFavoriteWidget::deleteResource( ) {
	auto musicCentreWidget = getMusicCentreWidget( );
	if( musicCentreWidget )
		musicCentreWidget->removeMusicFavoriteWidget( this );

	peelMusicFavoriteItem( );
	return true;
}
void MusicFavoriteWidget::mouseMoveEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicFavoriteWidget::mousePressEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicFavoriteWidget::mouseReleaseEvent( QMouseEvent *event ) {
	event->ignore( );
}

bool MusicFavoriteWidget::initBefore( ) {
	deleteResource( );
	setMouseTracking( true );
	return true;
}
bool MusicFavoriteWidget::init( ) {
	return true;
}
bool MusicFavoriteWidget::initAfter( ) {
	return true;
}
bool MusicFavoriteWidget::fromYPosGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &pos_y ) const {
	return true;
}
bool MusicFavoriteWidget::fromIndexGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &index ) const {
	return true;
}
bool MusicFavoriteWidget::fromNameGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const QString &index ) const {
	return true;
}
bool MusicFavoriteWidget::updateFavoriteItemLayout( ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicDataManage = musicCentreWidget->getMusicDataManage( );
	if( musicDataManage == nullptr )
		return false;
	peelMusicFavoriteItem( );
	if( musicDataManage->getMusicFavoriteItem( defaultItem, musicFavoriteItems ) == false )
		return false;
	int offsetX = 0, offsetY = 0;
	if( updateChildItem( defaultItem, offsetX, offsetY ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, updateChildItem, tr( "配置 [ 默认 ] 收藏项异常" ) );
	size_t count = musicFavoriteItems.size( );
	if( count ) {
		auto data = musicFavoriteItems.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( updateChildItem( data[ index ], offsetX, offsetY ) == false )
				return Result_Var_Function_Messag_Ptr_Out_Args( false, this, updateChildItem, tr( "配置 [ %1 ] 收藏项异常" ).arg( index ) );
	}
	resize( offsetX, offsetY );
	return true;
}

int MusicFavoriteWidget::setAdapiveWidth( const int &adaptive_width ) {
	return 0;
}
bool MusicFavoriteWidget::updateChildItem( IMusicFavoriteItem *music_favorite_item, int &offset_x, int &offset_y ) {
	int width, height;
	auto musicFavoriteItemWidget = music_favorite_item->getMusicFavoriteItemWidget( );
	if( musicFavoriteItemWidget->setMusicFavoriteWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "配置收藏组件异常" ) );
	if( musicFavoriteItemWidget->setPos( 0, 0 ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "配置位置异常" ) );
	if( musicFavoriteItemWidget->updateLayout( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "配置更新布局异常" ) );
	if( musicFavoriteItemWidget->showItemWidget( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "配置显示异常" ) );
	if( musicFavoriteItemWidget->getSize( width, height ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "获取大小异常" ) );
	offset_y += height;
	if( offset_x < width )
		offset_x = width;
	return true;
}
