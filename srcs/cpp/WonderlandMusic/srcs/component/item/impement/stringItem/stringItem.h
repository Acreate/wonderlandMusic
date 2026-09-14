#ifndef STRINGITEM_H_H_HEAD__FILE__
#define STRINGITEM_H_H_HEAD__FILE__
#include "../../interface/iItemDraw/iItemDraw.h"

class StringItem : public IItemDraw {
	QString *string;

public:
	StringItem( );
	~StringItem( ) override;
	virtual bool setString( const QString &new_string );
	virtual const QString & getString( ) const;
	bool loadFileToDraw( const QString &load_image_file_path ) override;
	bool loadStringToDraw( const QString &set_string_draw_to_buff ) override;
	bool setDraw( const QImage &draw ) override;
};

#endif // STRINGITEM_H_H_HEAD__FILE__
