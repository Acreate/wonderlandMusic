#include "playerControlWidget.h"

#include <QFileInfo>
#include <QMouseEvent>
#include <QPainter>

#include <component/playWindow/interface/widget/iPlayerWindowCentreWidget.h>

#include "../../application/appInstance/appDataManage.h"

#include "../../component/item/impement/buttonItem/buttonItem.h"
#include "../../component/item/impement/progressItem/progressItem.h"
#include "../../component/item/impement/stringItem/stringItem.h"

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
	int offsetX = 20;
	int offsetY = 10;
	int itemSpace = 10;
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
	userMutex->unlock( );
	repaint( );
	return true;
}
bool PlayerControlWidget::player( const QString &music_file_path ) {
	return false;
}
bool PlayerControlWidget::stop( ) {
	return false;
}
bool PlayerControlWidget::terminate( ) {
	return false;
}
bool PlayerControlWidget::setPlayerTime( const int64_t &player_mill_second_time ) {
	return false;
}
bool PlayerControlWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	setPlayerWindowCentre( nullptr );

	userMutex->lock( );
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
	QWidget::paintEvent( event );
	QPainter painter( this );
	userMutex->lock( );
	thePreviousSong->drawToParintr( painter );
	thePreviousStep->drawToParintr( painter );
	play->drawToParintr( painter );
	theNextStep->drawToParintr( painter );
	theNextSong->drawToParintr( painter );
	userMutex->unlock( );
}
void PlayerControlWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
}
void PlayerControlWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void PlayerControlWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void PlayerControlWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
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
