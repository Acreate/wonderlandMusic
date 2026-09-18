#ifndef PLAYERWINDOWCENTREWIDGET_H_H_HEAD__FILE__
#define PLAYERWINDOWCENTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../../component/playWindow/interface/widget/iPlayerWindowCentreWidget.h"

class UserMutex;

class PlayerWindowCentreWidget : public QWidget, public IPlayerWindowCentreWidget {
	Q_OBJECT;

protected:
	UserMutex *userMutex = nullptr;
	PlayWindow *playWindow = nullptr;
	IPlayerInfoListWidget *playerInfoListWidget = nullptr;
	IPlayerControlWidget *playerControlWidget = nullptr;

public:
	PlayerWindowCentreWidget( );
	~PlayerWindowCentreWidget( ) override;
	PlayWindow * getPlayWindow( ) const override;
	bool setPlayWindow( PlayWindow *play_window ) override;
	bool setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget ) override;
	bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) override;
	QWidget * toWidget( ) override;
	bool updateLayout( ) override;
	IPlayerInfoListWidget * getPlayerInfoListWidget( ) const override;
	IPlayerControlWidget * getPlayerControlWidget( ) const override;
	bool currentMusicItemPlayer( ) override;
	bool currentMusicItemPreviousSong( ) override;
	bool currentMusicItemNextSong( ) override;
	bool currentMusicItemPreviousStep( ) override;
	bool currentMusicItemNextStep( ) override;
	bool currentMusicItemPause( ) override;
	bool currentMusicItemTerminate( ) override;
	bool currentMusicItemSetPlayerTime( const long double percentage ) override;

protected:
	bool deleteResource( );
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // PLAYERWINDOWCENTREWIDGET_H_H_HEAD__FILE__
