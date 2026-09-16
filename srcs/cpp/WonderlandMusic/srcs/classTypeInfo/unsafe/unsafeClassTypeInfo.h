#ifndef UNSAFCECLASSTYPEINFO_H_H_HEAD__FILE__
#define UNSAFCECLASSTYPEINFO_H_H_HEAD__FILE__

#include <typeinfo>

#include "../interface/iClassTypeInfo.h"
class TypeInfoRef;
class UserMutex;
class QString;

class UnsafeClassTypeInfo : public IClassTypeInfo {
protected:
	~UnsafeClassTypeInfo( ) override;
	explicit UnsafeClassTypeInfo( const ClassTypeInfoVar *class_type_info_var );

public:
	TypeInfoRef * getfristTypeInfoRef( const void *ptr ) const override;
	bool deleteClassTypeInfo( const void *p ) override;
	TypeInfoRef * appendClassTypeInfo( const ClassTypeInfoVar *class_type_info_var, const void *ptr, const std::type_info &type_info, const QString &name ) override;
};

#endif // UNSAFCECLASSTYPEINFO_H_H_HEAD__FILE__
