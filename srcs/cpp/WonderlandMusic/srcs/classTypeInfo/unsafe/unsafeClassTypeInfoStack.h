#ifndef UNSAFECLASSTYPEINFOSTACK_H_H_HEAD__FILE__
#define UNSAFECLASSTYPEINFOSTACK_H_H_HEAD__FILE__
#include <vector>

#include "../interface/iClassTypeInfoStack.h"

class UnsafeClassTypeInfoStack : public IClassTypeInfoStack {
private:
	std::vector< IClassTypeInfo * > classTypeInfoVector;

protected:
	const IClassTypeInfo * fromClassTypeInfoVarGetClassTypeInfo( const IClassTypeInfo *class_type_info ) const override;
	const bool fromClassTypeInfoVarGetClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const IClassTypeInfo *class_type_info ) const override;

public:
	UnsafeClassTypeInfoStack( );
	~UnsafeClassTypeInfoStack( ) override;
	const IClassTypeInfo * appendClassTypeInfoVar( IClassTypeInfo *class_type_info_ptr, void *ptr, const std::type_info &class_type_info, const QString &class_type_name ) override;
	const IClassTypeInfo * getClassTypeInfo( const void *ptr ) const override;
	const bool getClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const void *ptr ) const override;
	bool removeClassTypeInfo( const void *ptr ) override;
	void clear( ) override;
};

#endif // UNSAFECLASSTYPEINFOSTACK_H_H_HEAD__FILE__
