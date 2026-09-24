#ifndef IWIDGETCOMPONENT_H_H_HEAD__FILE__
#define IWIDGETCOMPONENT_H_H_HEAD__FILE__

#include "iObjectComponent.h"

class QSize;
class QWidget;
class QPoint;
class QRect;

class IWidgetComponent : public virtual IObjectComponent {
public:
	explicit IWidgetComponent( );
	IWidgetComponent( const IWidgetComponent & ) = delete;

	virtual const QRect & getGeometry( ) const =0;
	virtual const QPoint & getPoint( ) const =0;
	virtual bool setGeometry( const QRect &new_geometry ) const =0;
	virtual bool setPoint( const QPoint &new_point ) =0;
	virtual QWidget * toWidget( ) =0;
	virtual const QWidget * toWidget( ) const =0;
	virtual const QSize & getSize( ) const =0;
	virtual bool setSize( const QSize &new_size ) const =0;
	virtual bool setShowStatus( const bool &show_status ) =0;
	virtual bool getShowStatus( ) const =0;
	virtual operator QWidget *( );
};

#endif // IWIDGETCOMPONENT_H_H_HEAD__FILE__
