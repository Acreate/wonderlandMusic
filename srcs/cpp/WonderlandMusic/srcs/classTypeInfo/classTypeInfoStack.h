#ifndef CLASSTYPEINFOSTACK_H_H_HEAD__FILE__
#define CLASSTYPEINFOSTACK_H_H_HEAD__FILE__
#include "unsafe/unsafeClassTypeInfoStack.h"

class UserMutex;

class ClassTypeInfoStack : public UnsafeClassTypeInfoStack {
	UserMutex *userMutex;

public:
	ClassTypeInfoStack( );
	~ClassTypeInfoStack( ) override;
	const IClassTypeInfo * appendClassTypeInfoVar( IClassTypeInfo *class_type_info_ptr, const void *ptr, const std::type_info &class_type_info, const QString &class_type_name ) override;
	const IClassTypeInfo * getClassTypeInfo( const void *ptr ) const override;
	bool removeClassTypeInfo( const void *ptr ) override;
	void clear( ) override;

protected:
	const IClassTypeInfo * fromClassTypeInfoVarGetClassTypeInfo( const IClassTypeInfo *class_type_info ) const override;

public:
	const bool getClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const void *ptr ) const override;
};

#endif // CLASSTYPEINFOSTACK_H_H_HEAD__FILE__
