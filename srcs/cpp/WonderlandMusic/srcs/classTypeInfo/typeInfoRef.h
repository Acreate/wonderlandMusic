#ifndef TYPEINFOREF_H_H_HEAD__FILE__
#define TYPEINFOREF_H_H_HEAD__FILE__
#include <typeinfo>

class QString;

class TypeInfoRef {
	friend class IClassTypeInfo;

	QString *name;
	const IClassTypeInfo *classTypeInfo;
	const type_info &typeInfo;
	void *ptr = nullptr;

protected:
	virtual ~TypeInfoRef( );
	TypeInfoRef( const IClassTypeInfo *class_type_info, void *ptr, const std::type_info &type_info, const QString *const name );
	TypeInfoRef( const IClassTypeInfo *class_type_info, void *ptr, const std::type_info &type_info );
	TypeInfoRef( const IClassTypeInfo *class_type_info, void *ptr, const std::type_info &type_info, const QString &name );

public:
	friend bool operator==( const TypeInfoRef &lhs, const TypeInfoRef &rhs );
	friend bool operator!=( const TypeInfoRef &lhs, const TypeInfoRef &rhs );
	virtual const QString & getName( ) const;
	virtual const std::type_info & getTypeInfo( ) const;
	virtual void * getPtr( ) const;
	virtual const IClassTypeInfo * getClassTypeInfo( ) const;
	virtual bool isType( const void *ptr, const std::type_info &type_info, const QString &name ) const;
	virtual bool isType( const std::type_info &type_info, const QString &name ) const;
	virtual bool isType( const void *ptr, const std::type_info &type_info ) const;
	virtual bool isType( const void *ptr, const QString &name ) const;
	virtual bool isType( const void *ptr ) const;
	virtual bool isType( const std::type_info &type_info ) const;
	virtual bool isType( const QString &name ) const;
};
#endif // TYPEINFOREF_H_H_HEAD__FILE__
