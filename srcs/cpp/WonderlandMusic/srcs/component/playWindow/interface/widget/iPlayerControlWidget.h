#ifndef IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#define IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
#include <cstdint>

#include "iPlayerWindowCentreChildWidget.h"

class QString;

class IPlayerControlWidget : public IPlayerWindowCentreChildWidget {
public:
	virtual bool player( const QString &music_file_path ) = 0;
	virtual bool stop( ) = 0;
	virtual bool terminate( ) = 0;
	virtual bool setPlayerTime( const int64_t &player_mill_second_time ) = 0;

protected:
	IPlayerControlWidget( );
	~IPlayerControlWidget( ) override;
};

#endif // IPLAYERCONTROLWIDGET_H_H_HEAD__FILE__
