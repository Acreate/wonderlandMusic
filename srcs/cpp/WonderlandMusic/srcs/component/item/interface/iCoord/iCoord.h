#ifndef ICOORD_H_H_HEAD__FILE__
#define ICOORD_H_H_HEAD__FILE__
#include <classTypeInfo/classTypeInfoVar.h>

class QPoint;
class QRect;

class ICoord : public virtual ClassTypeInfoVar {
private:
	QRect *geometry;

protected:
	virtual QRect * getGeometryPtr( ) const;

public:
	ICoord( );
	~ICoord( ) override;
	virtual const QRect & getGeometry( ) const;
	virtual void setGeometry( const QRect &geometry );
	virtual void setGeometry( const int &x, const int &y, const int &width, const int &height );
	virtual bool isClick( const QPoint &point ) const;
	virtual bool isEmpty( ) const;
	virtual void reSize( const int &width, const int &height );
	virtual void moveTo( const int &x, const int &y );
};

#endif // ICOORD_H_H_HEAD__FILE__
