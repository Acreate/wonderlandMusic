#include "musicCentreWidget.h"

#include <QJsonObject>
#include <QMouseEvent>

#include <application/appInstance/appDataManage.h>
#include <application/appInstance/appUserInterfaceManage/appMenuManage.h>

#include <component/musicWindow/musicWindow.h>
#include <component/musicWindow/interface/info/iMusicDataManage.h>
#include <component/musicWindow/interface/widget/iMusicFavoriteWidget.h>
#include <component/musicWindow/interface/widget/iMusicListWidget.h>
#include <component/musicWindow/interface/widget/iMusicTitleWidget.h>
#include <component/musicWindow/interface/widget/iMusicWidget.h>
#include <component/musicWindow/musicScrollArea/musicScrollArea.h>
#include <component/musicWindow/transparencyScrollBar/transparencyScrollBar.h>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <musicImpement/info/musicWidgetSizeInfo.h>

#include <mutex/userMutex.h>

#include <tools/instanceTools.h>

#include "../../application/appInstance/appDataManage/appMusicManage.h"

MusicCentreWidget::MusicCentreWidget( ) : QWidget( ), musicWindow( nullptr ) {
	regClassTypeInfoRef( this );
}
MusicCentreWidget::~MusicCentreWidget( ) {
	deleteResource( );
}

bool MusicCentreWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	dragStatus = Drag_Status::None;
	readDragStatus = Drag_Status::None;
	cursorShape = Qt::CursorShape::ArrowCursor;
	setCursor( cursorShape );
	isContainsMusicScrollArea = false;
	isDrag = false;
	isContainsViewport = false;
	clickWidth = 5;
	favoriteLeft = 0;
	favoriteRight = 0;
	favoriteWidth = 0;
	titleTop = 0;
	titleBottom = 0;
	titleHeight = 0;
	dragOrgX = 0;
	dragOrgY = 0;
	dragOffsetX = 0;
	dragOffsetY = 0;
	if( musicFavoriteWidget )
		musicFavoriteWidget->setMusicCentreWidget( nullptr );
	if( musicListWidget )
		musicListWidget->setMusicCentreWidget( nullptr );
	if( musicTitleWidget )
		musicTitleWidget->setMusicCentreWidget( nullptr );
	musicfavoriteWidgetScrollArea->takeWidget( );
	musicListWidgetScrollArea->takeWidget( );
	musicTitleWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( musicfavoriteWidgetScrollArea );
	Delete_Resource_App_Core_Ptr( musicListWidgetScrollArea );
	Delete_Resource_App_Core_Ptr( musicTitleWidgetScrollArea );
	favoriteWidth = titleHeight = 0;
	userMutex->unlock( );
	if( musicWindow )
		musicWindow->setMusicCentreWidget( nullptr );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}

void MusicCentreWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	synchronizationChildrenWidgetSize( );
}

void MusicCentreWidget::mouseMoveEvent( QMouseEvent *event ) {
	event->accept( );
	userMutex->lock( );
	switch( readDragStatus ) {
		case Drag_Status::None : {
			auto point = event->pos( );
			if( musicFavoriteWidget ) {
				int x = point.x( );
				if( x > favoriteLeft && x < favoriteRight ) {
					dragStatus = Drag_Status::MusicFavoriteWidget;
					if( cursorShape != Qt::CursorShape::SizeHorCursor ) {
						cursorShape = Qt::CursorShape::SizeHorCursor;
						userMutex->unlock( );
						setCursor( cursorShape );
						return;
					}
					userMutex->unlock( );
					return;
				}
			}
			dragStatus = Drag_Status::None;
			if( cursorShape != Qt::CursorShape::ArrowCursor ) {
				cursorShape = Qt::CursorShape::ArrowCursor;
				userMutex->unlock( );
				setCursor( cursorShape );
				return;
			}
			userMutex->unlock( );
			return;
		}
		case Drag_Status::MusicFavoriteWidget : {
			favoriteWidth = dragOrgX + event->x( ) - dragOffsetX;
			favoriteWidth = std::max( favoriteWidth, minWidth );
			setFavoriteWidth( favoriteWidth );
			userMutex->unlock( );
			synchronizationChildrenWidgetSize( );
			return;
		}
	}
	dragStatus = Drag_Status::None;
	if( cursorShape != Qt::CursorShape::ArrowCursor ) {
		cursorShape = Qt::CursorShape::ArrowCursor;
		userMutex->unlock( );
		setCursor( cursorShape );
		return;
	}
	userMutex->unlock( );
}
void MusicCentreWidget::mousePressEvent( QMouseEvent *event ) {
	event->accept( );
	auto mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::MouseButton::LeftButton : {
			userMutex->lock( );
			readDragStatus = dragStatus;
			switch( dragStatus ) {
				case Drag_Status::None :
					userMutex->unlock( );
					return;
				case Drag_Status::MusicFavoriteWidget : {
					dragOffsetX = event->x( );
					dragOrgX = favoriteWidth;
					userMutex->unlock( );
					return;
				}
				case Drag_Status::MusicTitleWidget : {
					dragOffsetY = event->y( );
					dragOrgY = titleHeight;
					userMutex->unlock( );
					return;
				}
			}
			userMutex->unlock( );
		}
		break;
	}
}
void MusicCentreWidget::mouseReleaseEvent( QMouseEvent *event ) {
	event->accept( );
	auto mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::MouseButton::LeftButton : {
			userMutex->lock( );
			readDragStatus = dragStatus = Drag_Status::None;
			if( cursorShape != Qt::CursorShape::ArrowCursor ) {
				cursorShape = Qt::CursorShape::ArrowCursor;
				userMutex->unlock( );
				setCursor( cursorShape );
				return;
			}
			userMutex->unlock( );
		}
		break;
		case Qt::MouseButton::RightButton : {
			while( musicFavoriteWidget ) {
				auto widget = musicFavoriteWidget->toWidget( );
				if( widget == nullptr )
					break;
				auto pos = event->globalPos( );
				if( musicfavoriteWidgetScrollArea->containsPosInView( isContainsMusicScrollArea, isContainsViewport, pos ) == false )
					break;
				if( isContainsViewport == false )
					return;
				auto appMusicManage = InstanceTools::getAppMusicManage( );
				IMusicFavoriteItem *musicFavoriteItem;
				if( appMusicManage->getMusicFavoriteItem( musicFavoriteItem ) == false )
					break;
				if( execMenu( musicFavoriteWidget, musicFavoriteItem, event->globalPos( ) ) == false )
					Result_Void_Function_Messag_Ptr_Out_Args( this, execMenu, tr( "收藏夹菜单显示异常" ) );
				break;
			}
			while( musicListWidget ) {
				auto widget = musicListWidget->toWidget( );
				if( widget == nullptr )
					break;
				auto pos = event->globalPos( );
				if( musicListWidgetScrollArea->containsPosInView( isContainsMusicScrollArea, isContainsViewport, pos ) == false )
					break;
				if( isContainsViewport == false )
					return;
				std::vector< IMusicItem * > result;
				if( execMenu( musicListWidget, nullptr, event->globalPos( ) ) == false )
					Result_Void_Function_Messag_Ptr_Out_Args( this, execMenu, tr( "列表菜单显示异常" ) );
				break;
			}
		}
		break;
	}
}
bool MusicCentreWidget::setMusicWindow( MusicWindow *music_window ) {
	musicWindow = music_window;
	setParent( musicWindow );
	return true;
}
QWidget * MusicCentreWidget::toWidget( ) {
	return this;
}
bool MusicCentreWidget::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::FocusOut :
		case QEvent::FocusIn :
		case QEvent::Enter :
		case QEvent::Leave :
			do {
				userMutex->lock( );
				readDragStatus = dragStatus = Drag_Status::None;
				if( cursorShape != Qt::CursorShape::ArrowCursor ) {
					cursorShape = Qt::CursorShape::ArrowCursor;
					userMutex->unlock( );
					setCursor( cursorShape );
					break;
				}
				userMutex->unlock( );
			} while( false );

			break;
	}
	return QWidget::event( event );
}

bool MusicCentreWidget::initBefore( ) {
	deleteResource( );
	clickWidth = 5;
	favoriteLeft = 0;
	favoriteRight = 0;
	favoriteWidth = 0;
	titleTop = 0;
	titleBottom = 0;
	titleHeight = 0;
	isContainsMusicScrollArea = false;
	isContainsViewport = false;

	isDrag = false;
	minWidth = clickWidth * 4;
	musicfavoriteWidgetScrollArea = new MusicScrollArea( this );
	musicTitleWidgetScrollArea = new MusicScrollArea( this );
	musicListWidgetScrollArea = new MusicScrollArea( this );
	userMutex = new UserMutex;
	setMouseTracking( true );
	cursorShape = Qt::CursorShape::ArrowCursor;
	musicTitleWidgetScrollArea->setVerticalScrollBar( new TransparencyScrollBar( this ) );
	musicTitleWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	auto verticalScrollBar = musicTitleWidgetScrollArea->verticalScrollBar( );
	if( verticalScrollBar )
		verticalScrollBar->setEnabled( false );
	auto horizontalScrollBar = musicTitleWidgetScrollArea->horizontalScrollBar( );
	auto scrollBar = musicListWidgetScrollArea->horizontalScrollBar( );

	connect( scrollBar, &QScrollBar::valueChanged, horizontalScrollBar, &QScrollBar::setValue );
	connect( scrollBar, &QScrollBar::rangeChanged, horizontalScrollBar, &QScrollBar::setRange );

	return true;
}
bool MusicCentreWidget::init( ) {
	return true;
}
bool MusicCentreWidget::initAfter( ) {
	synchronizationChildrenWidgetSize( );
	musicListWidgetScrollArea->show( );
	musicfavoriteWidgetScrollArea->show( );
	musicTitleWidgetScrollArea->show( );
	return true;
}

bool MusicCentreWidget::getJsonData( QJsonObject &get_json_object ) const {
	if( musicTitleWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicTitleWidget, getJsonData, tr( "未配置组件" ) );
	if( musicFavoriteWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteWidget, getJsonData, tr( "未配置组件" ) );
	if( musicListWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, getJsonData, tr( "未配置组件" ) );
	QJsonObject musicTitleJson;
	if( musicTitleWidget->getJsonData( musicTitleJson ) == false )
		return false;
	QJsonObject musicFavoriteJson;
	if( musicFavoriteWidget->getJsonData( musicFavoriteJson ) == false )
		return false;
	QJsonObject musicListJson;
	if( musicListWidget->getJsonData( musicListJson ) == false )
		return false;

	get_json_object.insert( classTypeTools::getTypeName( musicTitleWidget ), musicTitleJson );
	get_json_object.insert( classTypeTools::getTypeName( musicListWidget ), musicListJson );
	get_json_object.insert( classTypeTools::getTypeName( musicFavoriteWidget ), musicFavoriteJson );
	return true;
}
bool MusicCentreWidget::setJsonData( const QJsonObject &set_json_object ) {
	if( musicTitleWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicTitleWidget, setJsonData, tr( "未配置组件" ) );
	if( musicFavoriteWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteWidget, setJsonData, tr( "未配置组件" ) );
	if( musicListWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, setJsonData, tr( "未配置组件" ) );
	auto end = set_json_object.end( );
	auto iterator = set_json_object.find( classTypeTools::getTypeName( musicTitleWidget ) );
	if( iterator == end )
		return false;
	QJsonObject musicTitleJson = iterator->toObject( );
	iterator = set_json_object.find( classTypeTools::getTypeName( musicListWidget ) );
	if( iterator == end )
		return false;
	QJsonObject musicListJson = iterator->toObject( );
	iterator = set_json_object.find( classTypeTools::getTypeName( musicFavoriteWidget ) );
	if( iterator == end )
		return false;
	QJsonObject musicFavoriteJson = iterator->toObject( );

	if( musicTitleWidget->setJsonData( musicTitleJson ) == false )
		return false;
	if( musicFavoriteWidget->setJsonData( musicFavoriteJson ) == false )
		return false;
	if( musicListWidget->setJsonData( musicListJson ) == false )
		return false;
	return true;
}

MusicWindow * MusicCentreWidget::getMusicWindow( ) const {
	return musicWindow;
}
IMusicFavoriteWidget * MusicCentreWidget::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}

IMusicListWidget * MusicCentreWidget::getMusicListWidget( ) const {
	return musicListWidget;
}

IMusicTitleWidget * MusicCentreWidget::getMusicTitleWidget( ) const {
	return musicTitleWidget;
}
IMusicDataManage * MusicCentreWidget::getMusicDataManage( ) const {
	return musicDataManage;
}
bool MusicCentreWidget::setMusicDataManage( IMusicDataManage *const music_data_manage ) {
	if( music_data_manage->setMusicCentreWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_data_manage, music_data_manage, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicDataManage && musicDataManage->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( musicDataManage, musicDataManage, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	musicDataManage = music_data_manage;
	repaintMusicCentreWidget( );
	return true;
}
IMusicFavoriteMenu * MusicCentreWidget::getMusicFavoriteMenu( ) const {
	return InstanceTools::getAppMenuManage( )->getMusicFavoriteMenu( );
}
IMusicListMenu * MusicCentreWidget::getMusicListMenu( ) const {
	return InstanceTools::getAppMenuManage( )->getMusicListMenu( );
}
IMusicWidgetSizeInfo * MusicCentreWidget::getMusicWidgetSizeInfo( ) const {
	return InstanceTools::getAppDataManage( )->getMusicWidgetSizeInfo( );
}

bool MusicCentreWidget::setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) {
	if( music_favorite_widget == nullptr ) {
		if( musicFavoriteWidget && musicFavoriteWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		this->musicFavoriteWidget = music_favorite_widget;
		musicfavoriteWidgetScrollArea->takeWidget( );
		return true;
	}
	QWidget *widget = music_favorite_widget->toWidget( );
	if( widget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_favorite_widget, toWidget, tr( "不存在配置的 QWidget 组件失败" ) );
	if( music_favorite_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_favorite_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicFavoriteWidget ) {
		if( musicFavoriteWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		musicfavoriteWidgetScrollArea->takeWidget( );
	}
	this->musicFavoriteWidget = music_favorite_widget;
	musicfavoriteWidgetScrollArea->setWidget( widget );
	synchronizationChildrenWidgetSize( );
	repaintFavoriteWidget( );
	return true;
}
bool MusicCentreWidget::setMusicListWidget( IMusicListWidget *const music_list_widget ) {
	if( music_list_widget == nullptr ) {
		if( musicListWidget && musicListWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		this->musicListWidget = music_list_widget;
		musicListWidgetScrollArea->takeWidget( );
		return true;
	}
	QWidget *widget = music_list_widget->toWidget( );
	if( widget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_list_widget, toWidget, tr( "不存在配置的 QWidget 组件失败" ) );
	if( music_list_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_list_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicListWidget ) {
		if( musicListWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		musicListWidgetScrollArea->takeWidget( );
	}
	this->musicListWidget = music_list_widget;
	musicListWidgetScrollArea->setWidget( widget );
	synchronizationChildrenWidgetSize( );
	repaintListWidget( );
	return true;
}
bool MusicCentreWidget::setMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) {
	if( music_title_widget == nullptr ) {
		if( musicTitleWidget && musicTitleWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicTitleWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		this->musicTitleWidget = music_title_widget;
		musicTitleWidget->setMusicItemWidthInfo( nullptr );
		musicTitleWidgetScrollArea->takeWidget( );
		return true;
	}
	QWidget *widget = music_title_widget->toWidget( );
	if( widget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_title_widget, toWidget, tr( "不存在配置的 QWidget 组件失败" ) );
	if( music_title_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_title_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicTitleWidget ) {
		if( musicTitleWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicTitleWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		musicTitleWidgetScrollArea->takeWidget( );
	}
	this->musicTitleWidget = music_title_widget;
	musicTitleWidgetScrollArea->setWidget( widget );
	synchronizationChildrenWidgetSize( );
	repaintTitleWidget( );
	return true;
}
bool MusicCentreWidget::removeMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) {
	if( music_favorite_widget == nullptr )
		return false;
	if( musicFavoriteWidget == nullptr )
		return false;
	auto thisFavoriteWidget = musicFavoriteWidget->toWidget( );
	auto removeFavoriteWidget = music_favorite_widget->toWidget( );
	if( thisFavoriteWidget != removeFavoriteWidget )
		return false;
	if( musicListWidget )
		musicListWidget->setCurrentMusicFavoriteItem( nullptr );

	if( musicFavoriteWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	musicFavoriteWidget = nullptr;
	return true;
}
bool MusicCentreWidget::removeMusicListWidget( IMusicListWidget *const music_list_widget ) {
	if( music_list_widget == nullptr )
		return false;
	if( musicListWidget == nullptr )
		return false;
	auto thisWidget = musicListWidget->toWidget( );
	auto removeWidget = music_list_widget->toWidget( );
	if( thisWidget != removeWidget )
		return false;
	if( musicListWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	if( musicListWidget->setCurrentMusicFavoriteItem( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, setCurrentMusicFavoriteItem, tr( "配置 nullptr 组件失败" ) );
	musicListWidget = nullptr;
	return true;
}
bool MusicCentreWidget::removeMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) {
	if( music_title_widget == nullptr )
		return false;
	if( musicTitleWidget == nullptr )
		return false;
	auto thisWidget = musicTitleWidget->toWidget( );
	auto removeWidget = music_title_widget->toWidget( );
	if( thisWidget != removeWidget )
		return false;
	if( musicTitleWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicTitleWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	musicTitleWidget = nullptr;
	return true;
}

bool MusicCentreWidget::repaintListWidget( ) {
	if( musicListWidget == nullptr )
		return false;
	return musicListWidget->updateCurrentMusicFavoriteItem( );
}
bool MusicCentreWidget::repaintTitleWidget( ) {
	if( musicTitleWidget == nullptr )
		return false;
	return musicTitleWidget->updateMusicItemWidthInfoLayout( );
}
bool MusicCentreWidget::repaintFavoriteWidget( ) {
	if( musicFavoriteWidget == nullptr )
		return false;
	return musicFavoriteWidget->updateFavoriteItemLayout( );
}
bool MusicCentreWidget::repaintMusicCentreWidget( ) {
	if( repaintTitleWidget( ) == false )
		return false;
	if( repaintListWidget( ) == false )
		return false;
	if( repaintFavoriteWidget( ) == false )
		return false;
	return true;
}
bool MusicCentreWidget::synchronizationChildrenWidgetSize( ) {
	auto musicWidgetSizeInfo = getMusicWidgetSizeInfo( );
	if( musicWidgetSizeInfo == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, getMusicWidgetSizeInfo, tr( "找不到窗口大小组件" ) );
	if( userMutex == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, userMutex, tr( "锁未能确定指向有效对象" ) );
	userMutex->lock( );
	// 当前组件高度
	int thisCentreHeight = this->height( );
	if( thisCentreHeight > 0 ) {
		// 当前组件宽度
		int thisCentreWidthWidth = this->width( );
		if( thisCentreWidthWidth > 0 ) {
			favoriteWidth = musicWidgetSizeInfo->getFavoriteWidth( );
			favoriteLeft = favoriteWidth - clickWidth;
			favoriteRight = favoriteWidth + clickWidth;
			titleHeight = musicWidgetSizeInfo->getTitleHeight( );
			titleTop = titleHeight - clickWidth;
			titleBottom = titleHeight + clickWidth;
			musicfavoriteWidgetScrollArea->setGeometry( 0, 0, favoriteWidth, thisCentreHeight );
			int modeWidth = thisCentreWidthWidth - favoriteWidth;
			musicTitleWidgetScrollArea->setGeometry( favoriteWidth, 0, modeWidth, titleHeight );
			int modHeight = thisCentreHeight - titleHeight;
			musicListWidgetScrollArea->setGeometry( favoriteWidth, titleHeight, modeWidth, modHeight );
			return userMutex->result_unlock( true );
		}
		return userMutex->result_unlock( Result_Var_Function_Messag_Ptr_Out_Args( false, this, calculateSize, tr( "宽度失效:%1" ).arg(thisCentreWidthWidth ) ) );
	}
	return userMutex->result_unlock( Result_Var_Function_Messag_Ptr_Out_Args( false, this, calculateSize, tr( "高度失效:%1" ).arg( thisCentreHeight ) ) );
}
bool MusicCentreWidget::setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	if( musicListWidget == nullptr )
		return false;
	return musicListWidget->setCurrentMusicFavoriteItem( music_favorite_item );
}
