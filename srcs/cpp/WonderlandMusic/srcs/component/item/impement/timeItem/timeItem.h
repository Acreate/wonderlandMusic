#ifndef TIMEITEM_H_H_HEAD__FILE__
#define TIMEITEM_H_H_HEAD__FILE__
#include <chrono>

#include "../../interface/iItemDraw/iItemDraw.h"

class QFont;
class QTime;

class TimeItem : public IItemDraw {
	QTime *time = nullptr;
	QFont *font = nullptr;

protected:
	virtual bool rePaintBuff( );

public:
	explicit TimeItem( const QTime &set_time, const QFont &set_font );
	explicit TimeItem( const QTime &set_time );
	explicit TimeItem( );
	~TimeItem( ) override;
	virtual bool setFontSize( const int &new_font_sizet );
	virtual const QFont & getFont( ) const;
	virtual bool setFont( const QFont &set_font );
	virtual const QTime & getTime( ) const;
	virtual bool setTime( const QTime &set_time );
	virtual bool setTime( const std::chrono::milliseconds &set_time );
	bool loadFileToDraw( const QString &load_image_file_path ) override;
	bool loadStringToDraw( const QString &set_string_draw_to_buff ) override;
	bool setDraw( const QImage &draw ) override;
	virtual QString toString( ) const;
};

#endif // TIMEITEM_H_H_HEAD__FILE__
