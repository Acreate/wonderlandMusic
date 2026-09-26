#include "musicListWidget.h"

#include <QMouseEvent>

#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>

#include "../../component/musicWindow/interface/ItemWidget/iMusicItemWidget.h"
#include "../../component/musicWindow/interface/info/iMusicItemWidthInfo.h"
#include "../../component/musicWindow/interface/item/iMusicFavoriteItem.h"
#include "../../component/musicWindow/interface/item/iMusicItem.h"
#include "../../component/musicWindow/interface/widget/iMusicTitleWidget.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"

MusicListWidget::MusicListWidget( ) {
	regClassTypeInfoRef( this );
}
MusicListWidget::~MusicListWidget( ) {
	deleteResource( );
}
bool MusicListWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicListWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicListWidget::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicListWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	caculateHeight = 0;
	auto musicCentreWidget = getMusicCentreWidget( );
	if( musicCentreWidget ) {
		userMutex->unlock( );
		musicCentreWidget->removeMusicListWidget( this );
		userMutex->lock( );
	}
	userMutex->unlock( );
	return true;
}
void MusicListWidget::mouseMoveEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicListWidget::mousePressEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	event->ignore( );
}
bool MusicListWidget::unsafeUpdateCurrentMusicFavoriteItem( ) {
	if( musicFavoriteItem == nullptr )
		return false;
	if( musicCentreWidget == nullptr )
		return false;
	auto titleWidget = musicCentreWidget->getMusicTitleWidget( );
	if( titleWidget == nullptr )
		return false;
	auto musicItemWidthInfo = titleWidget->getMusicItemWidthInfo( );
	if( musicItemWidthInfo == nullptr )
		return false;
	std::vector< IMusicItem * > resultClone;
	if( musicFavoriteItem->getMusicVector( resultClone ) == 0 )
		return true;
	size_t count = resultClone.size( );
	if( count == 0 )
		return true;
	auto musicItem = resultClone.data( );
	size_t index = 0;
	IMusicItemWidget *musicItemWidget;

	caculateHeight = 0;
	caculateWidth = musicItemWidthInfo->getCalculateMinWidth( );
	int thisHeight = musicItemWidthInfo->getSuggestHeight( );
	IMusicItem *item;
	for( ; index < count; index += 1 ) {
		item = musicItem[ index ];
		if( item->setMusicCentreWidget( musicCentreWidget ) == false )
			continue;
		musicItemWidget = item->getMusicItemWidget( );
		if( musicItemWidget == nullptr ) {
			Result_Var_Function_Messag_Ptr_Out_Args( nullptr, musicItem[ index ], getMusicItemWidget, tr( "返回值 nullptr" ) );
			continue;
		}
		if( musicItemWidget->setMusicListWidget( this ) == false ) {
			Result_Var_Function_Messag_Ptr_Out_Args( nullptr, musicItemWidget, setMusicListWidget, tr( "配置 MusicListWidget 失败" ) );
			continue;
		}
		item->setIdCode( index + 1 );
		if( musicItemWidget->updateLayout( ) == false ) {
			Result_Var_Function_Messag_Ptr_Out_Args( nullptr, musicItemWidget, updateLayout, tr( "更新布局" ) );
			continue;
		}
		auto widget = musicItemWidget->toWidget( );
		if( widget == nullptr ) {
			Result_Var_Function_Messag_Ptr_Out_Args( nullptr, musicItemWidget, toWidget, tr( "没有窗口组件" ) );
			continue;
		}
		widget->setGeometry( 0, caculateHeight, caculateWidth, thisHeight );
		caculateHeight += thisHeight;
	}
	return true;
}
bool MusicListWidget::updateMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	userMutex->lock( );
	if( musicFavoriteItem != music_favorite_item )
		return userMutex->result_unlock( false );
	auto updateResult = unsafeUpdateCurrentMusicFavoriteItem( );
	userMutex->unlock( );
	if( updateResult )
		resize( caculateWidth, caculateHeight );
	return updateResult;
}
bool MusicListWidget::updateCurrentMusicFavoriteItem( ) {
	userMutex->lock( );
	auto updateResult = unsafeUpdateCurrentMusicFavoriteItem( );
	userMutex->unlock( );
	if( updateResult )
		resize( caculateWidth, caculateHeight );
	return updateResult;
}

bool MusicListWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	setMouseTracking( true );
	return true;
}
bool MusicListWidget::init( ) {
	return true;
}
bool MusicListWidget::initAfter( ) {
	return true;
}
QWidget * MusicListWidget::toWidget( ) {
	return this;
}
IMusicCentreWidget * MusicListWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
IMusicFavoriteItem * MusicListWidget::getCurrentMusicFavoriteItem( ) const {
	return musicFavoriteItem;
}
bool MusicListWidget::setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	userMutex->lock( );
	auto old = musicFavoriteItem;
	musicFavoriteItem = music_favorite_item;
	userMutex->unlock( );
	if( old ) {
		std::vector< IMusicItem * > result;
		size_t musicItemCount = old->getMusicVector( result );
		if( musicItemCount ) {
			auto data = result.data( );
			size_t index = 0;
			for( ; index < musicItemCount; index += 1 )
				if( data[ index ] ) {
					auto musicItemWidget = data[ index ]->getMusicItemWidget( );
					if( musicItemWidget == nullptr )
						continue;
					musicItemWidget->setMusicListWidget( nullptr );
				}
		}
	}

	return music_favorite_item == nullptr ? true : updateCurrentMusicFavoriteItem( );
}
bool MusicListWidget::fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) const {
	userMutex->lock( );
	if( musicFavoriteItem )
		return userMutex->result_unlock( false );
	userMutex->unlock( );
	return false;
}
bool MusicListWidget::fromIndexGetMusicItem( IMusicItem *&result_music_item, const size_t &index ) const {
	userMutex->lock( );
	if( musicFavoriteItem )
		return userMutex->result_unlock( false );
	userMutex->unlock( );
	return false;
}
bool MusicListWidget::fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) const {
	userMutex->lock( );
	if( musicFavoriteItem )
		return userMutex->result_unlock( false );
	userMutex->unlock( );
	return false;
}
bool MusicListWidget::fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) const {
	userMutex->lock( );
	if( musicFavoriteItem )
		return userMutex->result_unlock( false );
	userMutex->unlock( );
	return false;
}
bool MusicListWidget::fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) const {
	userMutex->lock( );
	if( musicFavoriteItem )
		return userMutex->result_unlock( false );
	userMutex->unlock( );
	return false;
}
bool MusicListWidget::fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) const {
	userMutex->lock( );
	if( musicFavoriteItem )
		return userMutex->result_unlock( false );
	userMutex->unlock( );
	return false;
}
