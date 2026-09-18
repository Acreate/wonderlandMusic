#include "playerWindowCentreWidget.h"

#include <QMouseEvent>

#include "../../component/playWindow/playWindow.h"
#include "../../component/playWindow/interface/widget/iPlayerControlWidget.h"
#include "../../component/playWindow/interface/widget/iPlayerInfoListWidget.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"
PlayerWindowCentreWidget::PlayerWindowCentreWidget( ) {
	regClassTypeInfoRef( this );
}
PlayerWindowCentreWidget::~PlayerWindowCentreWidget( ) {
	deleteResource( );
}
PlayWindow * PlayerWindowCentreWidget::getPlayWindow( ) const {
	return playWindow;
}
bool PlayerWindowCentreWidget::setPlayWindow( PlayWindow *play_window ) {
	auto old = playWindow;
	playWindow = play_window;
	return old;
}
bool PlayerWindowCentreWidget::setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget ) {
	if( playerInfoListWidget && playerInfoListWidget->setPlayerWindowCentre( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, playerInfoListWidget, setPlayerWindow, tr( "删除配置信息列表组件异常" ) );
	if( player_info_list_widget && player_info_list_widget->setPlayerWindowCentre( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, player_info_list_widget, setPlayerWindow, tr( "新配置信息列表组件异常" ) );
	playerInfoListWidget = player_info_list_widget;
	updateLayout( );
	return true;
}
bool PlayerWindowCentreWidget::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	if( playerControlWidget && playerControlWidget->setPlayerWindowCentre( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, playerControlWidget, setPlayerWindow, tr( "删除配置信息列表组件异常" ) );
	if( player_control_widget && player_control_widget->setPlayerWindowCentre( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, player_control_widget, setPlayerWindow, tr( "新配置信息列表组件异常" ) );
	playerControlWidget = player_control_widget;
	updateLayout( );
	return true;
}
QWidget * PlayerWindowCentreWidget::toWidget( ) {
	return this;
}
bool PlayerWindowCentreWidget::updateLayout( ) {
	// 同时存在
	if( playerControlWidget && playerInfoListWidget ) {
		int currentWidgetHieght = this->height( );
		int currentWidgetWidth = this->width( );
		auto controlWidget = playerControlWidget->toWidget( );
		int controlHeght = 70;
		int listWidgetHeight = currentWidgetHieght - controlHeght;
		auto listWidget = playerInfoListWidget->toWidget( );
		listWidget->setGeometry( 0, 0, currentWidgetWidth, listWidgetHeight );
		controlWidget->setGeometry( 0, listWidgetHeight, currentWidgetWidth, controlHeght );

		if( playerControlWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerControlWidget, updateLayout, tr( "控制组件布局异常" ) );
		if( playerInfoListWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerInfoListWidget, updateLayout, tr( "列表组件布局异常" ) );
		return true;
	}
	if( playerControlWidget ) {
		int currentWidgetHieght = this->height( );
		int currentWidgetWidth = this->width( );
		auto controlWidget = playerControlWidget->toWidget( );
		controlWidget->setGeometry( 0, 0, currentWidgetWidth, currentWidgetHieght );
		if( playerControlWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerControlWidget, updateLayout, tr( "控制组件布局异常" ) );
		return true;
	}
	if( playerInfoListWidget ) {
		int currentWidgetHieght = this->height( );
		int currentWidgetWidth = this->width( );
		auto listWidget = playerInfoListWidget->toWidget( );
		listWidget->setGeometry( 0, 0, currentWidgetWidth, currentWidgetHieght );
		if( playerInfoListWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerInfoListWidget, updateLayout, tr( "列表组件布局异常" ) );
		return true;
	}
	return true;
}
IPlayerInfoListWidget * PlayerWindowCentreWidget::getPlayerInfoListWidget( ) const {
	return playerInfoListWidget;
}
IPlayerControlWidget * PlayerWindowCentreWidget::getPlayerControlWidget( ) const {
	return playerControlWidget;
}
bool PlayerWindowCentreWidget::currentMusicItemPlayer( ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemPlayer( );
}
bool PlayerWindowCentreWidget::currentMusicItemPreviousSong( ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemPreviousSong( );
}
bool PlayerWindowCentreWidget::currentMusicItemNextSong( ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemNextSong( );
}
bool PlayerWindowCentreWidget::currentMusicItemPreviousStep( ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemPreviousStep( );
}
bool PlayerWindowCentreWidget::currentMusicItemNextStep( ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemNextStep( );
}
bool PlayerWindowCentreWidget::currentMusicItemPause( ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemPause( );
}
bool PlayerWindowCentreWidget::currentMusicItemTerminate( ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemTerminate( );
}
bool PlayerWindowCentreWidget::currentMusicItemSetPlayerTime( const long double percentage ) {
	if( playerControlWidget == nullptr )
		return false;
	return playerControlWidget->currentMusicItemSetPlayerTime( percentage );
}
bool PlayerWindowCentreWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	if( playerInfoListWidget )
		playerInfoListWidget->setPlayerWindowCentre( nullptr );
	if( playerControlWidget )
		playerControlWidget->setPlayerWindowCentre( nullptr );
	if( playWindow )
		playWindow->setPlayerWindowCentreWidget( nullptr );
	userMutex->lock( );

	playerInfoListWidget = nullptr;
	playerControlWidget = nullptr;
	playWindow = nullptr;
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void PlayerWindowCentreWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
}
void PlayerWindowCentreWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void PlayerWindowCentreWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void PlayerWindowCentreWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
bool PlayerWindowCentreWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	setMouseTracking( true );
	return true;
}
bool PlayerWindowCentreWidget::init( ) {
	return true;
}
bool PlayerWindowCentreWidget::initAfter( ) {
	return true;
}
