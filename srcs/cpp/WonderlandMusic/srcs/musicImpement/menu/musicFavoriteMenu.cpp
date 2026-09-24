#include "musicFavoriteMenu.h"

#include <QJsonObject>

#include <application/appInstance/appDataManage/jsonKey/musicFavoriteMenuJsonKey.h>
#include <application/appInstance/appDataManage/translate/musicFavoriteMenuTranslate.h>
#include <application/appInstance/appUserInterfaceManage/appMenuManage.h>

#include <component/musicWindow/musicWindow.h>
#include <component/musicWindow/interface/item/iMusicFavoriteItem.h>
#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>
#include <component/musicWindow/interface/widget/iMusicFavoriteWidget.h>

#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <tools/instanceTools.h>
#include <tools/pathTools.h>
#include <tools/widgetTools.h>
MusicFavoriteMenu::MusicFavoriteMenu( ) {
}
MusicFavoriteMenu::~MusicFavoriteMenu( ) {
	deleteResource( );
}
bool MusicFavoriteMenu::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( createFavoriteItemAction );
	Delete_Resource_App_Core_Ptr( renameFavoriteItemAction );
	Delete_Resource_App_Core_Ptr( deleteFavoriteItemAction );
	Delete_Resource_App_Core_Ptr( addMusicFileAction );
	Delete_Resource_App_Core_Ptr( addMusicDirAction );
	return true;
}
bool MusicFavoriteMenu::initBefore( ) {
	deleteResource( );
	createFavoriteItemAction = addAction( "" );
	renameFavoriteItemAction = addAction( "" );
	deleteFavoriteItemAction = addAction( "" );
	addMusicFileAction = addAction( "" );
	addMusicDirAction = addAction( "" );
	return true;
}
bool MusicFavoriteMenu::init( ) {
	return true;
}
bool MusicFavoriteMenu::initAfter( ) {
	if( AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		createFavoriteItemAction->setText( translate.getCreateFavoriteItem( ) );
		return true;
	} ) == false )
		return false;
	auto signal = &QAction::triggered;
	connect( createFavoriteItemAction, signal, this, &MusicFavoriteMenu::slot_createFavoriteItem );
	connect( renameFavoriteItemAction, signal, this, &MusicFavoriteMenu::slot_renameFavoriteItem );
	connect( deleteFavoriteItemAction, signal, this, &MusicFavoriteMenu::slot_deleteFavoriteItem );
	connect( addMusicFileAction, signal, this, &MusicFavoriteMenu::slot_addMusicFile );
	connect( addMusicDirAction, signal, this, &MusicFavoriteMenu::slot_addMusicDir );
	return true;
}
bool MusicFavoriteMenu::getJsonData( QJsonObject &get_json_object ) const {
	if( AppJsonKeyTools::getMusicFavoriteMenu( [&get_json_object, this] ( const MusicFavoriteMenuJsonKey &json_key ) {
		get_json_object.insert( json_key.getLoadMultDir( ), PathTools::getAutoShortenPathName( openSelecteMultiDirWidgetPath ) );
		get_json_object.insert( json_key.getLoadMultFile( ), PathTools::getAutoShortenPathName( openSelecteMultiFileWidgetPath ) );
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicFavoriteMenu::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getMusicFavoriteMenu( [&set_json_object, this] ( const MusicFavoriteMenuJsonKey &json_key ) {
		auto end = set_json_object.end( );
		auto iterator = set_json_object.find( json_key.getLoadMultDir( ) );
		if( iterator == end )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "找不到匹配的目录路径" ) );
		openSelecteMultiDirWidgetPath = iterator.value( ).toString( );
		iterator = set_json_object.find( json_key.getLoadMultFile( ) );
		if( iterator == end )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "找不到匹配的文件路径" ) );

		openSelecteMultiFileWidgetPath = iterator.value( ).toString( );
		if( openSelecteMultiFileWidgetPath.isEmpty( ) )
			openSelecteMultiFileWidgetPath = QDir::currentPath( );
		if( openSelecteMultiDirWidgetPath.isEmpty( ) )
			openSelecteMultiDirWidgetPath = QDir::currentPath( );
		return true;
	} ) == false )
		return false;
	return true;
}
IMusicCentreWidget * MusicFavoriteMenu::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicFavoriteMenu::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicFavoriteMenu::execMenu( IMusicFavoriteWidget *music_favorite_widget, IMusicFavoriteItem *favorite_item, const QPoint &mouse_global_point ) {
	if( music_favorite_widget == nullptr )
		return false;
	musicFavoriteWidget = music_favorite_widget;
	musicFavoriteItem = favorite_item;

	if( AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		if( musicFavoriteItem ) {
			QString name;
			if( musicFavoriteItem->getName( name ) == false )
				return false;
			renameFavoriteItemAction->setText( translate.getRenameFavoriteItem( ).arg( name ) );
			renameFavoriteItemAction->setEnabled( true );
			deleteFavoriteItemAction->setText( translate.getDeleteFavoriteItem( ).arg( name ) );
			deleteFavoriteItemAction->setEnabled( true );
			addMusicFileAction->setText( translate.getAddMusicFileToFavoriteItem( ).arg( name ) );
			addMusicFileAction->setEnabled( true );
			addMusicDirAction->setText( translate.getAddMusicDirToFavoriteItem( ).arg( name ) );
			addMusicDirAction->setEnabled( true );
		} else {
			renameFavoriteItemAction->setText( translate.getIllegalRenameFavoriteItem( ) );
			renameFavoriteItemAction->setEnabled( false );
			deleteFavoriteItemAction->setText( translate.getIllegalDeleteFavoriteItem( ) );
			deleteFavoriteItemAction->setEnabled( false );
			addMusicFileAction->setText( translate.getIllegalAddMusicFileToFavoriteItem( ) );
			addMusicFileAction->setEnabled( false );
			addMusicDirAction->setText( translate.getIllegalAddMusicDirToFavoriteItem( ) );
			addMusicDirAction->setEnabled( false );
		}
		return true;
	} ) == false )
		return false;

	return InstanceTools::getAppMenuManage( )->popMusicFavoriteMenu( mouse_global_point );
}

void MusicFavoriteMenu::hideEvent( QHideEvent *hide_event ) {
	QMenu::hideEvent( hide_event );
}
void MusicFavoriteMenu::slot_createFavoriteItem( ) {
}
void MusicFavoriteMenu::slot_renameFavoriteItem( ) {
}
void MusicFavoriteMenu::slot_deleteFavoriteItem( ) {
}
void MusicFavoriteMenu::slot_addMusicFile( ) {
	if( musicFavoriteItem == nullptr )
		Result_Void_Function_Messag_Ptr_Out_Args( this, slot_addMusicFile, tr( "不存在指定收藏夹" ) );
	AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		std::vector< QString > resultFile;
		auto musicCentreWidget = musicFavoriteWidget->getMusicCentreWidget( );
		auto musicWindow = musicCentreWidget->getMusicWindow( );
		QWidget *openWidget = musicWindow->toWidget( );

		QString filter;
		if( PathTools::getSupperDecodeFileSuffixFilter( filter ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, nullptr, getSupperDecodeFileSuffixFilter, tr( "该软件不支持任意音频" ) );
		if( WidgetTools::showMultipleSelectFileDialog( resultFile, openSelecteMultiFileWidgetPath, openWidget, translate.getSelectMusicFile( ), filter ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, nullptr, showMultipleSelectFileDialog, tr( "选择文件失败" ) );
		QFileInfo info( resultFile[ 0 ] );
		auto dir = info.dir( );
		openSelecteMultiFileWidgetPath = dir.path( );
		if( musicFavoriteItem->loadMusicFile( resultFile ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItem, loadMusicFile, tr( "加载文件失败" ) );
		return true;
	} );
}
void MusicFavoriteMenu::slot_addMusicDir( ) {
	if( musicFavoriteItem == nullptr )
		Result_Void_Function_Messag_Ptr_Out_Args( this, slot_addMusicDir, tr( "不存在指定收藏夹" ) );
	AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		std::vector< QString > resultFile;
		auto musicCentreWidget = musicFavoriteWidget->getMusicCentreWidget( );
		QWidget *openWidget = musicCentreWidget->getMusicWindow( );
		if( WidgetTools::showMultipleSelectDirDialog( resultFile, openSelecteMultiDirWidgetPath, openWidget, translate.getSelectMusicFile( ) ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, nullptr, showMultipleSelectDirDialog, tr( "选择目录失败" ) );
		QFileInfo info( resultFile[ 0 ] );
		auto dir = info.dir( );
		openSelecteMultiDirWidgetPath = dir.path( );
		if( musicFavoriteItem->loadMusicDirPath( resultFile ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItem, loadMusicDirPath, tr( "加载目录失败" ) );
		return true;
	} );
}
QMenu * MusicFavoriteMenu::toMenu( ) {
	return this;
}
