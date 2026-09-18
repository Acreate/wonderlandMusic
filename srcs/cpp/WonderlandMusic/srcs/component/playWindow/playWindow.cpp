#include "playWindow.h"

#include <QMouseEvent>

#include <head/release_macro.h>

#include <mutex/userMutex.h>

#include "interface/widget/iPlayerControlWidget.h"
#include "interface/widget/iPlayerWindowCentreWidget.h"

PlayWindow::PlayWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {
	regClassTypeInfoRef( this );
}
PlayWindow::~PlayWindow( ) {
	deleteResource( );
}
bool PlayWindow::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	if( playerWindowCentreWidget )
		playerWindowCentreWidget->setPlayWindow( nullptr );
	takeCentralWidget( );
	playerWindowCentreWidget = nullptr;
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void PlayWindow::paintEvent( QPaintEvent *event ) {
	QMainWindow::paintEvent( event );
}
void PlayWindow::showEvent( QShowEvent *event ) {
	QMainWindow::showEvent( event );
	updateLayout( );
}
void PlayWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
	updateLayout( );
}
void PlayWindow::mouseDoubleClickEvent( QMouseEvent *event ) {
	QMainWindow::mouseDoubleClickEvent( event );
	event->ignore( );
}
void PlayWindow::mouseMoveEvent( QMouseEvent *event ) {
	QMainWindow::mouseMoveEvent( event );
	event->ignore( );
}
void PlayWindow::mousePressEvent( QMouseEvent *event ) {
	QMainWindow::mousePressEvent( event );
	event->ignore( );
}
void PlayWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );
	event->ignore( );
}
bool PlayWindow::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	setMouseTracking( true );
	return true;
}
bool PlayWindow::init( ) {
	return true;
}
bool PlayWindow::initAfter( ) {
	return true;
}
IPlayerWindowCentreWidget * PlayWindow::getPlayerWindowCentreWidget( ) const {
	return playerWindowCentreWidget;
}
bool PlayWindow::setPlayerWindowCentreWidget( IPlayerWindowCentreWidget *const player_window_centre_widget ) {
	if( playerWindowCentreWidget )
		playerWindowCentreWidget->setPlayWindow( nullptr );
	takeCentralWidget( );
	playerWindowCentreWidget = player_window_centre_widget;
	if( playerWindowCentreWidget ) {
		playerWindowCentreWidget->setPlayWindow( this );
		auto widget = playerWindowCentreWidget->toWidget( );
		setCentralWidget( widget );
	}
	return true;
}
IPlayerInfoListWidget * PlayWindow::getPlayerInfoListWidget( ) const {
	if( playerWindowCentreWidget == nullptr )
		return nullptr;
	return playerWindowCentreWidget->getPlayerInfoListWidget( );
}
bool PlayWindow::setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->setPlayerInfoListWidget( player_info_list_widget );
}
IPlayerControlWidget * PlayWindow::getPlayerControlWidget( ) const {
	if( playerWindowCentreWidget == nullptr )
		return nullptr;
	return playerWindowCentreWidget->getPlayerControlWidget( );
}
bool PlayWindow::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->setPlayerControlWidget( player_control_widget );
}
bool PlayWindow::updateLayout( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->updateLayout( );
}
bool PlayWindow::currentMusicItemPlayer( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemPlayer( );
}
bool PlayWindow::currentMusicItemPreviousSong( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemPreviousSong( );
}
bool PlayWindow::currentMusicItemNextSong( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemNextSong( );
}
bool PlayWindow::currentMusicItemPreviousStep( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemPreviousStep( );
}
bool PlayWindow::currentMusicItemNextStep( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemNextStep( );
}
bool PlayWindow::currentMusicItemPause( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemPause( );
}
bool PlayWindow::currentMusicItemTerminate( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemTerminate( );
}
bool PlayWindow::currentMusicItemSetPlayerTime( const long double percentage ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->currentMusicItemSetPlayerTime(percentage );
}
