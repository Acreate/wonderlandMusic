#ifndef TIMEITEM_H_H_HEAD__FILE__
#define TIMEITEM_H_H_HEAD__FILE__
#include "../../interface/iItemDraw/iItemDraw.h"

class QTime;

class TimeItem : public IItemDraw {
	QTime *time;

public:
	explicit TimeItem( const QTime &set_time );
	explicit TimeItem( );
	~TimeItem( ) override;
	virtual const QTime & getTime( ) const;
	virtual bool setTime( const QTime &set_time );
	bool loadFileToDraw( const QString &load_image_file_path ) override;
	bool loadStringToDraw( const QString &set_string_draw_to_buff ) override;
	bool setDraw( const QImage &draw ) override;
	QString toString( ) const;
};

#endif // TIMEITEM_H_H_HEAD__FILE__
