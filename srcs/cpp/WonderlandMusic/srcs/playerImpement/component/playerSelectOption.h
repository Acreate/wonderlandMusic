#ifndef PLAYERSELECTOPTION_H_H_HEAD__FILE__
#define PLAYERSELECTOPTION_H_H_HEAD__FILE__
#include <QWidget>

#include "../../component/playWindow/interface/playerComponent/iPlayerSelectOption.h"

class PlayerSelectOption : public QWidget, public IPlayerSelectOption {
	Q_OBJECT;
protected:
	IPlayerControlWidget* playerControlWidget = nullptr;
	UserMutex* userMutex = nullptr;
protected:
	bool deleteResource( );

public:
	PlayerSelectOption( );
	~PlayerSelectOption( ) override;
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

protected:
	bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) override;
	QWidget * toWidget( ) override;
	bool updateLayout( ) override;
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent(QResizeEvent *event) override;
public:
	IPlayerControlWidget * getPlayerControlWidget( ) const override;
	bool nextTrack( ) override;
	bool previousTrack( ) override;
	bool nextPace( ) override;
	bool previousPace( ) override;
	bool player( ) override;
	bool stop( ) override;
	bool abort( ) override;
};

#endif // PLAYERSELECTOPTION_H_H_HEAD__FILE__
