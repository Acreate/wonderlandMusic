#include "classTypeInfoStack.h"

#include "../mutex/userMutex.h"
ClassTypeInfoStack::ClassTypeInfoStack( ) {
	userMutex = new UserMutex;
}
ClassTypeInfoStack::~ClassTypeInfoStack( ) {
	userMutex->lock( );
	UnsafeClassTypeInfoStack::clear( );
	userMutex->unlock( );
	delete userMutex;
}
const IClassTypeInfo * ClassTypeInfoStack::appendClassTypeInfoVar( IClassTypeInfo *class_type_info_ptr, void *ptr, const std::type_info &class_type_info, const QString &class_type_name ) {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfoStack::appendClassTypeInfoVar( class_type_info_ptr, ptr, class_type_info, class_type_name );
	userMutex->unlock( );
	return result;
}
const IClassTypeInfo * ClassTypeInfoStack::getClassTypeInfo( const void *ptr ) const {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfoStack::getClassTypeInfo( ptr );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfoStack::removeClassTypeInfo( const void *ptr ) {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfoStack::removeClassTypeInfo( ptr );
	userMutex->unlock( );
	return result;
}
void ClassTypeInfoStack::clear( ) {
	userMutex->lock( );
	UnsafeClassTypeInfoStack::clear( );
	userMutex->unlock( );
}
const IClassTypeInfo * ClassTypeInfoStack::fromClassTypeInfoVarGetClassTypeInfo( const IClassTypeInfo *class_type_info ) const {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfoStack::fromClassTypeInfoVarGetClassTypeInfo( class_type_info );
	userMutex->unlock( );
	return result;
}
const bool ClassTypeInfoStack::getClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const void *ptr ) const {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfoStack::getClassTypeInfo( result_index, result_class_type_info, ptr );
	userMutex->unlock( );
	return result;
}
