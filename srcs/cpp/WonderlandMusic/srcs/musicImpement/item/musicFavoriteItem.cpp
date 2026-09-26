#include "musicFavoriteItem.h"

#include <qimage.h>

#include <component/musicWindow/interface/item/iMusicItem.h>

#include <mutex/userMutex.h>

#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>

#include <musicImpement/itemWidget/musicFavoriteItemWidget.h>

#include <component/musicWindow/musicWindow.h>

#include "musicInfoItem.h"

#include "../../application/appInstance/appDataManage/appMusicManage.h"

#include "../../component/musicWindow/interface/widget/iMusicListWidget.h"

#include "../../head/result_message_out.h"

#include "../../musicFileInfo/musicFileInfo.h"
#include "../../musicFileInfo/musicFileInfoList.h"

#include "../../tools/classTypeTools.h"
#include "../../tools/enumTools.h"
#include "../../tools/instanceTools.h"
#include "../../tools/invokeMethodTools.h"
#include "../../tools/pathTools.h"
#include "../../tools/sourceLocationTools.h"

bool MusicFavoriteItem::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicFavoriteItemUserMutex->lock( );
	musicCentreWidget = music_centre_widget;
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
MusicInfoItem * MusicFavoriteItem::load( MusicFileInfo *music_info ) {
	if( music_info->isOK( ) == false )
		return nullptr;
	musicFavoriteItemUserMutex->lock( );
	auto musicItem = new MusicInfoItem( this, *music_info );
	musicItemVector.emplace_back( musicItem );
	musicFavoriteItemUserMutex->unlock( );
	if( musicCentreWidget == nullptr )
		return musicItem;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return musicItem;
	musicListWidget->updateMusicFavoriteItem( this );
	return musicItem;
}
std::vector< MusicInfoItem * > MusicFavoriteItem::load( const std::vector< MusicFileInfo * > &music_infos ) {
	musicFavoriteItemUserMutex->lock( );
	size_t count = music_infos.size( );
	if( count == 0 ) {
		musicFavoriteItemUserMutex->unlock( );
		return { };
	}
	std::vector< MusicInfoItem * > result( count );
	size_t createCount = 0;
	auto data = music_infos.data( );
	size_t index = 0;
	auto resultData = result.data( );
	for( ; index < count; index += 1 )
		if( data[ index ]->isOK( ) ) {
			resultData[ createCount ] = new MusicInfoItem( this, *data[ index ] );
			createCount += 1;
		}
	if( createCount == 0 ) {
		musicFavoriteItemUserMutex->unlock( );
		return { };
	}
	result.resize( createCount );
	musicItemVector.append_range( result );
	musicFavoriteItemUserMutex->unlock( );
	if( musicCentreWidget == nullptr )
		return result;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return result;
	musicListWidget->updateMusicFavoriteItem( this );
	return result;
}
bool MusicFavoriteItem::getName( QString &result_name ) const {
	musicFavoriteItemUserMutex->lock( );
	result_name = name;
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::removeMusicItem( IMusicItem *music_item ) {
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::clear( ) {
	musicFavoriteItemUserMutex->lock( );
	musicItemVector.clear( );
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::update( ) {
	if( musicCentreWidget == nullptr )
		return false;
	musicCentreWidget->repaintMusicCentreWidget( );
	return true;
}
size_t MusicFavoriteItem::getMusicVector( std::vector< IMusicItem * > &result_clone_vector ) const {
	musicFavoriteItemUserMutex->lock( );
	auto result = musicItemVector.size( );
	result_clone_vector.resize( result );
	if( result ) {
		auto source = musicItemVector.data( );
		auto dest = result_clone_vector.data( );
		size_t index = 0;
		for( ; index < result; index += 1 )
			dest[ index ] = source[ index ];
	}
	musicFavoriteItemUserMutex->unlock( );
	return result;
}
void MusicFavoriteItem::setName( const QString &name ) {
	musicFavoriteItemUserMutex->lock( );
	this->name = name;
	musicFavoriteItemUserMutex->unlock( );
	if( musicFavoriteItemWidget )
		musicFavoriteItemWidget->updateLayout( );
}
IMusicCentreWidget * MusicFavoriteItem::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
IMusicFavoriteItemWidget * MusicFavoriteItem::getMusicFavoriteItemWidget( ) const {
	return musicFavoriteItemWidget;
}
bool MusicFavoriteItem::loadMusicDirPath( const std::vector< QString > &music_file_path ) {
	size_t result = 0;
	QStringList filterMusicFileList;
	QStringList getFileList;
	if( PathTools::entryFilePath( filterMusicFileList, music_file_path ) ) {
		result = PathTools::filterFile( getFileList, filterMusicFileList );
		if( result ) {
			result = PathTools::filterMusicFile( filterMusicFileList, getFileList );
			if( result ) {
				size_t index = 0;
				auto pointer = filterMusicFileList.data( );
				std::vector< QString > file( result );
				auto filePathDataPtr = file.data( );
				size_t fileIndex = 0;
				auto appMusicManage = InstanceTools::getAppMusicManage( );
				for( ; index < result; index += 1 )
					if( appMusicManage->musicFileNameSupperDecoder( pointer[ index ] ) ) {
						filePathDataPtr[ fileIndex ] = pointer[ index ];
						fileIndex += 1;
					}
				if( fileIndex == 0 )
					return false;
				file.resize( fileIndex );
				MusicFileInfoList *musicInfoList = new MusicFileInfoList( file );
				connect( musicInfoList, &MusicFileInfoList::signal_finish, this, &MusicFavoriteItem::loadOverMusicFileList );
				musicInfoList->start( );
			}
		}
	}
	return result;
}
bool MusicFavoriteItem::loadMusicFile( const std::vector< QString > &music_file_path ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	size_t count = music_file_path.size( );
	if( count == 0 )
		return false;
	std::vector< QString > file( count );
	auto data = music_file_path.data( );
	size_t index = 0;
	size_t fileIndex = 0;
	auto filePathDataPtr = file.data( );
	for( ; index < count; index += 1 )
		if( appMusicManage->musicFileNameSupperDecoder( data[ index ] ) ) {
			filePathDataPtr[ fileIndex ] = data[ index ];
			fileIndex += 1;
		}
	if( fileIndex == 0 )
		return false;
	file.resize( fileIndex );
	MusicFileInfoList *musicInfoList = new MusicFileInfoList( file );

	connect( musicInfoList, &MusicFileInfoList::signal_finish, this, &MusicFavoriteItem::loadOverMusicFileList );
	musicInfoList->start( );
	return true;
}
bool MusicFavoriteItem::loadMusicFile( const QString &music_file_path ) {
	if( PathTools::isMusicFile( music_file_path ) == false )
		return false;
	auto musicInfo = new MusicFileInfo( music_file_path );
	if( musicInfo == nullptr )
		return false;
	connect( musicInfo, &MusicFileInfo::finished, [this, musicInfo]( ) {
		loadOverMusicFile( musicInfo );
	} );
	musicInfo->start( );
	return true;
}
void MusicFavoriteItem::loadOverMusicFileList( MusicFileInfoList *music_file_info_list ) {
	auto status = music_file_info_list->getStatus( );
	auto chars = EnumTools::toString( status );
	if( status != MusicFileInfoList::Status::Finish ) {
		InvokeMethodTools::invokeQueuedConnectionMethod( [this, music_file_info_list] ( ApplicationManage *applicationManage ) {
			Result_Void_Function_Messag_Ptr_Out_Args( music_file_info_list, getStatus, tr( "读取异常" ) );
			delete music_file_info_list;
		} );
		return;
	}
	InvokeMethodTools::invokeQueuedConnectionMethod( [this, music_file_info_list] ( ApplicationManage *applicationManage ) {
		std::vector< MusicFileInfo * > getResult;
		if( music_file_info_list->getOverLoadMusicVector( getResult ) )
			load( getResult );
		delete music_file_info_list;
	} );
}
void MusicFavoriteItem::loadOverMusicFile( MusicFileInfo *music_file_info ) {
	InvokeMethodTools::invokeQueuedConnectionMethod( [this, music_file_info] ( ApplicationManage *applicationManage ) {
		load( music_file_info );
		delete music_file_info;
	} );
}
MusicFavoriteItem::MusicFavoriteItem( ) {
	classTypeTools::regTypeInfoRef( this );
	musicFavoriteItemUserMutex = new UserMutex;
	musicFavoriteItemWidget = new MusicFavoriteItemWidget;
	musicFavoriteItemWidget->bindMusicFavoriteItem( this );
}
MusicFavoriteItem::~MusicFavoriteItem( ) {
	musicFavoriteItemUserMutex->lock( );
	setParent( nullptr );
	size_t count = musicItemVector.size( );
	if( count ) {
		size_t index = 0;
		auto data = musicItemVector.data( );
		for( ; index < count; index += 1 ) {
			data[ index ]->setMusicFavoriteItem( nullptr );
			delete data[ index ];
		}
	}
	musicItemVector.clear( );
	if( musicFavoriteItemWidget ) {
		musicFavoriteItemWidget->bindMusicFavoriteItem( nullptr );
		musicFavoriteItemWidget->setMusicFavoriteWidget( nullptr );
		delete musicFavoriteItemWidget;
	}
	musicFavoriteItemWidget = nullptr;
	musicFavoriteItemUserMutex->unlock( );
	delete musicFavoriteItemUserMutex;
	musicFavoriteItemUserMutex = nullptr;
}
