#ifndef IBUFF_H_H_HEAD__FILE__
#define IBUFF_H_H_HEAD__FILE__
#include <classTypeInfo/classTypeInfoVar.h>

class QPainter;
class QString;
class QImage;

class IBuff : public virtual ClassTypeInfoVar {
private:
	QImage *draw;

public:
	IBuff( );
	~IBuff( ) override;
	virtual const QImage & getDraw( ) const;
	virtual bool setDraw( const QImage &draw );
	virtual bool isNull( ) const;

	virtual bool loadFileToDraw( const QString &load_image_file_path );

	virtual bool drawToParintr( QPainter &painter ) = 0;
};

#endif // IBUFF_H_H_HEAD__FILE__
