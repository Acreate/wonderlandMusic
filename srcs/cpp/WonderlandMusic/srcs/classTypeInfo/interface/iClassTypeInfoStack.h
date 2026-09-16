#ifndef ICLASSTYPEINFOSTACK_H_H_HEAD__FILE__
#define ICLASSTYPEINFOSTACK_H_H_HEAD__FILE__
#include <typeinfo>
class QString;
class ClassTypeInfoVar;
class IClassTypeInfo;

class IClassTypeInfoStack {
protected:
	IClassTypeInfoStack( );
	virtual ~IClassTypeInfoStack( );

protected:
	virtual const IClassTypeInfo * fromClassTypeInfoVarGetClassTypeInfo( const IClassTypeInfo *class_type_info ) const = 0;
	virtual bool deleteIClassTypeInfo( IClassTypeInfo * &class_type_info ) const;
	virtual const bool fromClassTypeInfoVarGetClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const IClassTypeInfo *class_type_info ) const =0;

public:
	virtual const IClassTypeInfo * appendClassTypeInfoVar( IClassTypeInfo *class_type_info_ptr, const void *ptr, const std::type_info &class_type_info, const QString &class_type_name ) = 0;
	virtual const IClassTypeInfo * getClassTypeInfo( const void *ptr ) const = 0;
	virtual const bool getClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const void *ptr ) const = 0;
	virtual bool removeClassTypeInfo( const void *ptr ) = 0;
	virtual void clear( ) = 0;
};

#endif // ICLASSTYPEINFOSTACK_H_H_HEAD__FILE__
