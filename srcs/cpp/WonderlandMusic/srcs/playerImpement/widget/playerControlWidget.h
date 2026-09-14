#ifndef PLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#define PLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/playWindow/interface/widget/iPlayerControlWidget.h>

#include "../../interface/iAppResourceCore.h"

class StringItem;
class ProgressItem;
class ButtonItem;

class PlayerControlWidget : public QWidget, public IPlayerControlWidget, public IAppResourceCore {
	Q_OBJECT;

private:
	ButtonItem *thePreviousSong = nullptr;
	ButtonItem *theNextSong = nullptr;
	ButtonItem *thePreviousStep = nullptr;
	ButtonItem *theNextStep = nullptr;
	ButtonItem *play = nullptr;
	ButtonItem *pause = nullptr;
	ButtonItem *termination = nullptr;
	ProgressItem *playerProgressItem = nullptr;
	StringItem *playerTimeItem = nullptr;
	UserMutex *userMutex = nullptr;
	IPlayerWindowCentreWidget *playerWindowCentreWidget = nullptr;

public:
	PlayerControlWidget( );
	~PlayerControlWidget( ) override;
	QWidget * toWidget( ) override;
	bool setPlayerWindowCentre( IPlayerWindowCentreWidget *play_window_centre_widget ) override;
	IPlayerWindowCentreWidget * getPlayerWindowCentre( ) const override;
	bool updateLayout( ) override;
	bool player( const QString &music_file_path ) override;
	bool stop( ) override;
	bool terminate( ) override;
	bool setPlayerTime( const int64_t &player_mill_second_time ) override;

protected:
	bool deleteResource( );
	void paintEvent( QPaintEvent *event ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // PLAYERCONTROLWIDGET_H_H_HEAD__FILE__
