#ifndef IBUFF_H_H_HEAD__FILE__
#define IBUFF_H_H_HEAD__FILE__
#include <classTypeInfo/classTypeInfoVar.h>

class QPainter;
class QString;
class QImage;

class IBuff : public virtual ClassTypeInfoVar {
private:
	QImage *drawImageBuff;

protected:
	virtual QImage * getDrawImageBuffPtr( ) const;
	virtual bool releaseDrawImageBuff( );

public:
	IBuff( );
	~IBuff( ) override;
	virtual QImage getDrawImageBuff( ) const;
	virtual bool setDraw( const QImage &draw );
	virtual bool isNull( ) const;

	virtual bool loadFileToDraw( const QString &load_image_file_path );
	virtual bool loadStringToDraw( const QString &set_string_draw_to_buff );

	virtual bool drawToParintr( QPainter &painter ) = 0;
	virtual bool clear( );
	virtual bool zoomTo( const int &width, const int &height );
	virtual bool zoomToWidth( const int &width );
	virtual bool zoomToHeight( const int &height );
};

#endif // IBUFF_H_H_HEAD__FILE__
