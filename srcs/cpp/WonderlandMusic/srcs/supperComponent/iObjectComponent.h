#ifndef IOBJECTCOMPONENT_H_H_HEAD__FILE__
#define IOBJECTCOMPONENT_H_H_HEAD__FILE__
#include <classTypeInfo/classTypeInfoVar.h>

class QObject;

class IObjectComponent : public virtual ClassTypeInfoVar {
	IObjectComponent *parent = nullptr;
	std::vector< IObjectComponent * > children;

protected:
	virtual bool removeChild( IObjectComponent *remove_target );
	virtual bool appendChild( IObjectComponent *append_target );
	virtual bool deleteChild( IObjectComponent *delete_target );
	virtual bool deleteThis( );

public:
	explicit IObjectComponent( );
	IObjectComponent( const IObjectComponent & ) = delete;
	virtual QObject * toObject( ) =0;
	virtual bool setParent( IObjectComponent *parent );
	virtual IObjectComponent * getParent( ) const;
	virtual const std::vector< IObjectComponent * > & getChiildren( ) const;
	virtual bool clearChiildren( );
	virtual operator QObject *( );
	~IObjectComponent( ) override;
};

#endif // IOBJECTCOMPONENT_H_H_HEAD__FILE__
