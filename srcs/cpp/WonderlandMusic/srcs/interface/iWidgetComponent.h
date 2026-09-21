#ifndef IWIDGETCOMPONENT_H_H_HEAD__FILE__
#define IWIDGETCOMPONENT_H_H_HEAD__FILE__
#include <qobject.h>

#include "../classTypeInfo/classTypeInfoVar.h"

class QSize;
class QWidget;
class QPoint;
class QRect;

class IWidgetComponent : public virtual ClassTypeInfoVar {
public:
	virtual const QRect & getGeometry( ) const;
	virtual const QPoint & getPoint( ) const;
	virtual bool setGeometry( const QRect &new_geometry ) const;
	virtual bool setPoint( const QPoint &new_point );
	virtual QWidget * toWidget( );
	virtual const QWidget * toWidget( ) const;
	virtual const QSize & getSize( ) const;
	virtual bool setSize( const QSize &new_size ) const;
	virtual bool setShowStatus( const bool &show_status );
	virtual bool getShowStatus( ) const;
	virtual bool setParent( IWidgetComponent *parent );
	virtual IWidgetComponent * getParent( ) const;
};

#endif // IWIDGETCOMPONENT_H_H_HEAD__FILE__
