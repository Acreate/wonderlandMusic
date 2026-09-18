#ifndef IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#define IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#include <cstdint>

#include "iPlayerWindowCentreChildWidget.h"

class QString;

class IPlayerControlWidget : public IPlayerWindowCentreChildWidget {
public:
	enum class Status {
		Player,
		Pause
	};

public:
	virtual bool currentMusicItemPlayer( ) = 0;
	virtual bool currentMusicItemPreviousSong( ) = 0;
	virtual bool currentMusicItemNextSong( ) = 0;
	virtual bool currentMusicItemPreviousStep( ) = 0;
	virtual bool currentMusicItemNextStep( ) = 0;
	virtual bool currentMusicItemPause( ) = 0;
	virtual bool currentMusicItemTerminate( ) = 0;
	virtual bool currentMusicItemSetPlayerTime( const long double &player_mill_second_time ) = 0;

protected:
	IPlayerControlWidget( );
	~IPlayerControlWidget( ) override;
	virtual bool setPlayerControlWidgetStatus( const Status &status ) = 0;
	virtual Status getPlayerControlWidgetStatus( ) const =0;
};

#endif // IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
