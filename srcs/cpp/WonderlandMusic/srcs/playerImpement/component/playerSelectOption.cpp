#include "playerSelectOption.h"

#include <QMouseEvent>

#include "../../component/playWindow/interface/widget/iPlayerControlWidget.h"

#include "../../head/release_macro.h"

#include "../../mutex/userMutex.h"
bool PlayerSelectOption::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	IPlayerControlWidget *controlWidget = playerControlWidget;
	userMutex->lock( );
	playerControlWidget = nullptr;
	userMutex->unlock( );
	if( controlWidget )
		controlWidget->setPlayerSelectOption( nullptr );
	userMutex->lock( );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
PlayerSelectOption::PlayerSelectOption( ) {
}
PlayerSelectOption::~PlayerSelectOption( ) {
	deleteResource( );
}
bool PlayerSelectOption::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}
bool PlayerSelectOption::init( ) {
	return true;
}
bool PlayerSelectOption::initAfter( ) {
	return true;
}
bool PlayerSelectOption::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	userMutex->lock( );
	playerControlWidget = player_control_widget;
	userMutex->unlock( );
	return true;
}
QWidget * PlayerSelectOption::toWidget( ) {
	return this;
}
bool PlayerSelectOption::updateLayout( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
IPlayerControlWidget * PlayerSelectOption::getPlayerControlWidget( ) const {
	return playerControlWidget;
}
bool PlayerSelectOption::nextTrack( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
bool PlayerSelectOption::previousTrack( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
bool PlayerSelectOption::nextPace( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
bool PlayerSelectOption::previousPace( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
bool PlayerSelectOption::player( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
bool PlayerSelectOption::stop( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
bool PlayerSelectOption::abort( ) {
	userMutex->lock( );
	userMutex->unlock( );
	return true;
}
void PlayerSelectOption::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	event->ignore( );
}
void PlayerSelectOption::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	event->ignore( );
}
void PlayerSelectOption::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	event->ignore( );
}
void PlayerSelectOption::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	event->ignore( );
}
void PlayerSelectOption::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
}
