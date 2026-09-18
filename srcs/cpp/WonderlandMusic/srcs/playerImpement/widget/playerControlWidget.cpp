#include "playerControlWidget.h"

#include <QFileInfo>
#include <QMouseEvent>
#include <QPainter>

#include <component/playWindow/interface/widget/iPlayerWindowCentreWidget.h>

#include "../../application/appInstance/appDataManage.h"
#include "../../application/appInstance/appDataManage/appMusicManage.h"

#include "../../component/item/impement/buttonItem/buttonItem.h"
#include "../../component/item/impement/progressItem/progressItem.h"
#include "../../component/item/impement/timeItem/timeItem.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"

#include "../../tools/instanceTools.h"

PlayerControlWidget::PlayerControlWidget( ) {
	regClassTypeInfoRef( this );
}
PlayerControlWidget::~PlayerControlWidget( ) {
	deleteResource( );
}
QWidget * PlayerControlWidget::toWidget( ) {
	return this;
}
bool PlayerControlWidget::setPlayerWindowCentre( IPlayerWindowCentreWidget *play_window_centre_widget ) {
	if( play_window_centre_widget ) {
		auto widget = play_window_centre_widget->toWidget( );
		if( widget ) {
			setParent( widget );
			show( );
		} else {
			setParent( nullptr );
			hide( );
		}
	} else {
		setParent( nullptr );
		hide( );
	}
	playerWindowCentreWidget = play_window_centre_widget;
	return true;
}
IPlayerWindowCentreWidget * PlayerControlWidget::getPlayerWindowCentre( ) const {
	return playerWindowCentreWidget;
}
bool PlayerControlWidget::updateLayout( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	if( isHidden( ) == true )
		return false;
	userMutex->lock( );
	int itemSpace = 10;
	int offsetX = itemSpace * 2;
	int offsetY = itemSpace;
	int height = this->height( ) - offsetY - offsetY;
	#define move_to_pos( _ptr, _x, _y, _scale_to_height , _move_erro_msg, _scale_erro_msg) \
		_ptr->moveTo( _x, _y );\
		if(_ptr->zoomToHeight( _scale_to_height ) == false)\
			return Result_Var_Function_Messag_Ptr_Out_Args( false, _ptr, zoomToHeight, _move_erro_msg ); \
		if( _ptr->scaleToImageSize( ) == false )\
			return Result_Var_Function_Messag_Ptr_Out_Args( false, _ptr, scaleToImageSize, _scale_erro_msg );
	move_to_pos( thePreviousSong, offsetX, offsetY, height, tr( "移动失败" ), tr( "缩放失败失败" ) )
	offsetX += thePreviousSong->getGeometry( ).width( ) + itemSpace;
	move_to_pos( thePreviousStep, offsetX, offsetY, height, tr( "移动失败" ), tr( "缩放失败失败" ) )
	offsetX += thePreviousStep->getGeometry( ).width( ) + itemSpace;
	move_to_pos( play, offsetX, offsetY, height, tr( "移动失败" ), tr( "缩放失败失败" ) )
	offsetX += play->getGeometry( ).width( ) + itemSpace;
	move_to_pos( theNextStep, offsetX, offsetY, height, tr( "移动失败" ), tr( "缩放失败失败" ) )
	offsetX += theNextStep->getGeometry( ).width( ) + itemSpace;
	move_to_pos( theNextSong, offsetX, offsetY, height, tr( "移动失败" ), tr( "缩放失败失败" ) )
	offsetX += theNextSong->getGeometry( ).width( ) + itemSpace * 4;
	// 进度条
	int width = this->width( );
	int modWidth;
	auto heightHalf = height / 2;
	playerTimeItem->setFontSize( heightHalf );
	playerTimeItem->scaleToImageSize( );
	modWidth = width - playerTimeItem->getGeometry( ).width( ) - itemSpace * 2;
	playerTimeItem->moveTo( modWidth, offsetY );
	modWidth = width - offsetX - itemSpace * 2;
	height = height - heightHalf - itemSpace;
	offsetY = offsetY + heightHalf + itemSpace;
	playerProgressItem->setGeometry( offsetX, offsetY, modWidth, height );
	// 时间
	userMutex->unlock( );
	repaint( );
	return true;
}
bool PlayerControlWidget::currentMusicItemPlayer( ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemPlayer( ) != nullptr;
}
bool PlayerControlWidget::currentMusicItemPreviousSong( ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemPreviousSong( ) != nullptr;
}
bool PlayerControlWidget::currentMusicItemNextSong( ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemNextSong( ) != nullptr;
}
bool PlayerControlWidget::currentMusicItemPreviousStep( ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemPreviousStep( ) != nullptr;
}
bool PlayerControlWidget::currentMusicItemNextStep( ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemNextStep( ) != nullptr;
}
bool PlayerControlWidget::currentMusicItemPause( ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemPause( ) != nullptr;
}
bool PlayerControlWidget::currentMusicItemTerminate( ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemTerminate( ) != nullptr;
}

bool PlayerControlWidget::currentMusicItemSetPlayerTime( const long double &player_mill_second_time ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	return appMusicManage->currentMusicItemSetPlayerTime( player_mill_second_time ) != nullptr;
}
bool PlayerControlWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	setPlayerWindowCentre( nullptr );

	userMutex->lock( );
	clickItem = nullptr;
	Delete_Resource_App_Core_Ptr( thePreviousSong );
	Delete_Resource_App_Core_Ptr( theNextSong );
	Delete_Resource_App_Core_Ptr( theNextStep );
	Delete_Resource_App_Core_Ptr( thePreviousStep );
	Delete_Resource_App_Core_Ptr( play );
	Delete_Resource_App_Core_Ptr( pause );
	Delete_Resource_App_Core_Ptr( termination );
	Delete_Resource_App_Core_Ptr( playerProgressItem );
	Delete_Resource_App_Core_Ptr( playerTimeItem );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void PlayerControlWidget::paintEvent( QPaintEvent *event ) {
	if( userMutex == nullptr )
		return;
	QPainter painter( this );
	userMutex->lock( );
	thePreviousSong->drawToParintr( painter );
	thePreviousStep->drawToParintr( painter );
	play->drawToParintr( painter );
	theNextStep->drawToParintr( painter );
	theNextSong->drawToParintr( painter );
	playerProgressItem->drawToParintr( painter );
	playerTimeItem->drawToParintr( painter );
	userMutex->unlock( );
}
void PlayerControlWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	event->ignore( );
}
void PlayerControlWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	event->ignore( );
}
void PlayerControlWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	event->ignore( );
	clickItem = getPos( event->pos( ) );
}
void PlayerControlWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	event->ignore( );
	if( userMutex == nullptr || clickItem == nullptr )
		return;
	auto point = event->pos( );
	int x = point.x( );
	bool isUpdate = false;
	userMutex->lock( );
	if( clickItem->isClick( point ) ) {
		if( clickItem == play )
			PlayerControlWidget::currentMusicItemPlayer( );
		else if( clickItem == thePreviousSong ) {
			PlayerControlWidget::currentMusicItemPreviousSong( );
		} else if( clickItem == theNextSong ) {
			PlayerControlWidget::currentMusicItemNextSong( );
		} else if( clickItem == thePreviousStep ) {
			PlayerControlWidget::currentMusicItemPreviousStep( );
		} else if( clickItem == theNextStep ) {
			PlayerControlWidget::currentMusicItemNextStep( );
		} else if( clickItem == pause ) {
			PlayerControlWidget::currentMusicItemPause( );
		} else if( clickItem == termination ) {
			PlayerControlWidget::currentMusicItemTerminate( );
		} else if( clickItem == playerProgressItem ) {
			using ProgressItemDouble = std::remove_pointer_t< std::remove_reference_t< decltype(playerProgressItem) > >::ProgressItemDouble;
			ProgressItemDouble var;
			if( playerProgressItem->calculateXPosVar( var, x ) ) {
				playerProgressItem->setCurrentVar( var );
				PlayerControlWidget::currentMusicItemSetPlayerTime( var );
				isUpdate = true;
			}
		}
	}
	clickItem = nullptr;
	userMutex->unlock( );
	if( isUpdate )
		update( );
}

void PlayerControlWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	//updateLayout( );
}
bool PlayerControlWidget::initBefore( ) {
	PlayerControlWidget::deleteResource( );
	setMouseTracking( true );
	userMutex = new UserMutex;
	thePreviousSong = new ButtonItem( ButtonItem::Type::Ico );
	theNextSong = new ButtonItem( ButtonItem::Type::Ico );
	theNextStep = new ButtonItem( ButtonItem::Type::Ico );
	thePreviousStep = new ButtonItem( ButtonItem::Type::Ico );
	play = new ButtonItem( ButtonItem::Type::Ico );
	pause = new ButtonItem( ButtonItem::Type::Ico );
	termination = new ButtonItem( ButtonItem::Type::Ico );
	playerProgressItem = new ProgressItem;
	playerTimeItem = new TimeItem;
	return true;
}
bool PlayerControlWidget::init( ) {
	return true;
}
bool PlayerControlWidget::initAfter( ) {
	auto appDataManage = InstanceTools::getAppDataManage( );
	const QString &settingPath = appDataManage->getAppSettingPath( );
	#define load_button_png_resource( _button_Ptr , _resource_file_path , msg )\
		if( _button_Ptr->loadFileToDraw( settingPath + _resource_file_path ) == false ) \
			return Result_Var_Function_Messag_Ptr_Out_Args( false, _button_Ptr, loadFileToDraw, msg );
	load_button_png_resource( thePreviousSong, "/png/上一曲.png", tr( "资源加载失败" ) );
	load_button_png_resource( theNextSong, "/png/下一曲.png", tr( "资源加载失败" ) );
	load_button_png_resource( theNextStep, "/png/上一步.png", tr( "资源加载失败" ) );
	load_button_png_resource( thePreviousStep, "/png/下一步.png", tr( "资源加载失败" ) );
	load_button_png_resource( play, "/png/播放.png", tr( "资源加载失败" ) );
	load_button_png_resource( pause, "/png/停止.png", tr( "资源加载失败" ) );
	load_button_png_resource( termination, "/png/终止.png", tr( "资源加载失败" ) );
	return true;
}
IItemDraw * PlayerControlWidget::getPos( const QPoint &pos ) const {
	IItemDraw *result = nullptr;
	if( userMutex == nullptr )
		return result;
	userMutex->lock( );
	#define set_clik( _result , _check, pos ) \
		if(_check->isClick( pos )) { \
			_result = _check; \
			break; \
		}
	do {
		set_clik( result, thePreviousSong, pos );
		set_clik( result, theNextSong, pos );
		set_clik( result, thePreviousStep, pos );
		set_clik( result, theNextStep, pos );
		set_clik( result, play, pos );
		set_clik( result, pause, pos );
		set_clik( result, termination, pos );
		set_clik( result, playerProgressItem, pos );
	} while( false );

	userMutex->unlock( );
	return result;
}
