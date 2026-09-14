#ifndef BUTTONITEM_H_H_HEAD__FILE__
#define BUTTONITEM_H_H_HEAD__FILE__
#include "../../interface/iItemDraw/iItemDraw.h"

class ButtonItem : public IItemDraw {
public:
	enum class Type {
		Txt,
		Ico,
		All
	};

protected:
	ButtonItem::Type type;
	QString *txt;
	QImage *ico;
	virtual bool updateDrawBuff( );

public:
	ButtonItem( );
	~ButtonItem( ) override;
	virtual ButtonItem::Type getType( ) const;
	virtual const QString & getTxt( ) const;
	virtual const QImage & getIco( ) const;
	bool clear( ) override;
	bool loadFileToDraw( const QString &load_image_file_path ) override;
	bool loadStringToDraw( const QString &set_string_draw_to_buff ) override;
	virtual bool setIco( const QImage &ico );
	virtual bool setTxt( const QString &txt );
	bool setDraw( const QImage &draw ) override;
	bool drawToParintr( QPainter &painter ) override;
};

#endif // BUTTONITEM_H_H_HEAD__FILE__
