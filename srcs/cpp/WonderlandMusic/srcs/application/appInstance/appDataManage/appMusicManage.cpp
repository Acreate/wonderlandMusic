#include "appMusicManage.h"

#include <QPainter>

#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>

#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <mutex/userMutex.h>

#include <tools/pathTools.h>

#include <musicImpement/info/musicItemWidthInfo.h>
#include <musicImpement/item/musicFavoriteItem.h>
#include <musicImpement/widget/musicCentreWidget.h>

#include <tools/ffmpegTools.h>

#include "../../../component/musicWindow/interface/ItemWidget/iMusicFavoriteItemWidget.h"
#include "../../../component/musicWindow/interface/widget/iMusicFavoriteWidget.h"

bool AppMusicManage::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	clearMusicFavoriteItem( );
	userMutex->lock( );
	supperDecodeFileSuffix.clear( );
	Delete_Resource_App_Core_Ptr( musicItemWidthInfo );
	Delete_Resource_App_Core_Ptr( defaultFavoriteItem );
	auto clearResult = unsafeClear( );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return clearResult;
}

bool AppMusicManage::unsafeClearMusicFavoriteItem( ) {
	size_t count = musicFavoriteItemVector.size( );
	if( count == 0 )
		return true;
	auto data = musicFavoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		delete data[ index ];
	musicFavoriteItemVector.clear( );
	return true;
}

bool AppMusicManage::init( ) {
	supperDecodeFileSuffix = ffmpegTools::getFFmpegSuperMusicType( );
	if( supperDecodeFileSuffix.size( ) == 0 )
		return false;
	return true;
}

bool AppMusicManage::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}

bool AppMusicManage::initAfter( ) {
	if( initDefaultMusicFavoriteItem( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, initDefaultMusicFavoriteItem, tr( "初始化默认收藏项失败" ) );
	return true;
}

bool AppMusicManage::unsafeClear( ) {
	auto clearMusicFavoriteItemResult = unsafeClearMusicFavoriteItem( );
	return clearMusicFavoriteItemResult;
}
bool AppMusicManage::getMusicWindowInfoJsonData( QJsonObject &result_json_object ) {
	return true;
}
bool AppMusicManage::setMusicWindowInfoJsonData( const QJsonObject &result_json_object ) {
	return true;
}

bool AppMusicManage::clear( ) {
	userMutex->lock( );
	auto result = unsafeClear( );
	userMutex->unlock( );
	return result;
}
bool AppMusicManage::setCurrentSelectFavoriteItem( IMusicFavoriteItem *set_select_music_favorite_item ) {
	if( currenstFavoriteItem == set_select_music_favorite_item )
		return true;
	userMutex->lock( );
	auto old = currenstFavoriteItem;
	currenstFavoriteItem = nullptr;
	if( set_select_music_favorite_item == defaultFavoriteItem )
		currenstFavoriteItem = defaultFavoriteItem;
	else {
		size_t count = musicFavoriteItemVector.size( );
		if( count ) {
			auto sourceData = musicFavoriteItemVector.data( );
			size_t index = 0;
			for( ; index < count; index += 1 )
				if( sourceData[ index ] == set_select_music_favorite_item ) {
					currenstFavoriteItem = defaultFavoriteItem;
					break;
				}
		}
	}
	// 不在列表当中，重置
	if( currenstFavoriteItem == nullptr ) {
		currenstFavoriteItem = old;
		userMutex->unlock( );
		return false;
	}
	userMutex->unlock( );
	if( musicCentreWidget )
		return musicCentreWidget->repaintMusicCentreWidget( );
	return true;
}
bool AppMusicManage::getCurrentSelectFavoriteItem( IMusicFavoriteItem *&result_current_select_music_favorite_item ) const {
	result_current_select_music_favorite_item = currenstFavoriteItem;
	return true;
}
bool AppMusicManage::getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	userMutex->lock( );
	bool getMusicFavoriteItem = unsafeGetMusicFavoriteItem( result_default_music_favorite_item, result_music_favorite_item );
	userMutex->unlock( );
	return getMusicFavoriteItem;
}
bool AppMusicManage::getMusicFavoriteItem( std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	userMutex->lock( );
	bool getMusicFavoriteItem = unsafeGetMusicFavoriteItem( result_music_favorite_item );
	return userMutex->result_unlock( getMusicFavoriteItem );
}

IMusicItemWidthInfo * AppMusicManage::getMusicItemWidthInfo( ) const {
	return musicItemWidthInfo;
}
bool AppMusicManage::setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) {
	if( musicItemWidthInfo->setIMusicItemWidthInfo( music_item_width_info ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicItemWidthInfo, setIMusicItemWidthInfo, tr( "配置项的宽度信息异常" ) );
	return true;
}
bool AppMusicManage::musicFileNameSupperDecoder( const QString &file_name ) const {
	size_t count = supperDecodeFileSuffix.size( );
	if( count == 0 )
		return false; // 没有正确解析后缀
	qsizetype indexOf = file_name.indexOf( "." );
	if( indexOf == -1 )
		return false; // 没有后缀
	auto compString = file_name.mid( indexOf + 1 );
	compString = compString.toUpper( );
	auto data = supperDecodeFileSuffix.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == compString )
			return true;
	return false;
}
const std::vector< QString > & AppMusicManage::getSupperDecodeFileSuffix( ) const {
	return supperDecodeFileSuffix;
}
void AppMusicManage::clearMusicFavoriteItem( ) {
	userMutex->lock( );
	size_t count = musicFavoriteItemVector.size( );
	if( count == 0 ) {
		userMutex->unlock( );
		return;
	}
	MusicFavoriteItem **data = musicFavoriteItemVector.data( );
	MusicFavoriteItem **buff = new MusicFavoriteItem *[ count ] { nullptr };
	size_t index;
	for( index = 0; index < count; index += 1 )
		buff[ index ] = data[ index ];
	musicFavoriteItemVector.clear( );
	userMutex->unlock( );
	for( index = 0; index < count; index += 1 )
		delete buff[ index ];
	delete[] buff;
}
MusicFileInfoEx * AppMusicManage::getCurrentPlaterMusicFileInfoEx( ) const {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::playerMusic( const QString &player_music_file_path ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemPlayer( ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemPreviousSong( ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemNextSong( ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemPreviousStep( ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemNextStep( ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemPause( ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemTerminate( ) {
	return currentPlayerMusicItem;
}
MusicFileInfoEx * AppMusicManage::currentMusicItemSetPlayerTime( const long double percentage ) {
	return currentPlayerMusicItem;
}
bool AppMusicManage::unsafeGetMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const {
	result_default_music_favorite_item = defaultFavoriteItem;
	return true;
}
bool AppMusicManage::unsafeGetMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	if( unsafeGetMusicFavoriteItem( result_default_music_favorite_item ) == false )
		return false;
	if( unsafeGetMusicFavoriteItem( result_music_favorite_item ) == false )
		return false;
	return true;
}
bool AppMusicManage::unsafeGetMusicFavoriteItem( std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	size_t count = musicFavoriteItemVector.size( );
	if( count )
		return true;
	result_music_favorite_item.resize( count );
	auto setData = result_music_favorite_item.data( );
	auto sourceData = musicFavoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		setData[ index ] = sourceData[ index ];
	return true;
}
AppMusicManage::AppMusicManage( ) : ClassTypeInfoVar( ) {
	regClassTypeInfoRef( this );
}
AppMusicManage::~AppMusicManage( ) {
	deleteResource( );
}

bool AppMusicManage::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	userMutex->lock( );
	musicCentreWidget = music_centre_widget;

	if( defaultFavoriteItem->setMusicCentreWidget( music_centre_widget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( userMutex->result_unlock( false ), defaultFavoriteItem, setMusicFavoriteItemMusicCentreWidget, tr( "配置收藏夹的 IMusicCentreWidget * 失败" ) );
	size_t count = musicFavoriteItemVector.size( );
	auto data = musicFavoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->setMusicCentreWidget( music_centre_widget ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( userMutex->result_unlock( false ), data[ index ], setMusicFavoriteItemMusicCentreWidget, tr( "配置收藏夹的 IMusicCentreWidget * 失败" ) );
	userMutex->unlock( );
	return true;
}
IMusicCentreWidget * AppMusicManage::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool AppMusicManage::getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const {
	userMutex->lock( );
	bool getMusicFavoriteItem = unsafeGetMusicFavoriteItem( result_default_music_favorite_item );
	return userMutex->result_unlock( getMusicFavoriteItem );
}
bool AppMusicManage::initDefaultMusicFavoriteItem( ) {
	userMutex->lock( );
	MusicFavoriteItem *old = defaultFavoriteItem;
	defaultFavoriteItem = new MusicFavoriteItem;
	defaultFavoriteItem->setName( tr( "默认" ) );
	userMutex->unlock( );
	if( old ) {
		auto musicCentreWidget = old->getMusicCentreWidget( );
		if( musicCentreWidget ) {
			auto musicFavoriteWidget = musicCentreWidget->getMusicFavoriteWidget( );
			if( musicFavoriteWidget )
				musicFavoriteWidget->updateFavoriteItemLayout( );
		}
		old->setParent( nullptr );
		auto musicFavoriteItemWidget = old->getMusicFavoriteItemWidget( );
		if( musicFavoriteItemWidget )
			musicFavoriteItemWidget->setMusicFavoriteWidget( nullptr );
		delete old;
	}
	return true;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
