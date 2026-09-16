#include "classTypeInfo.h"

#include "../mutex/userMutex.h"

ClassTypeInfo::~ClassTypeInfo( ) {
	delete userMutex;
}
ClassTypeInfo::ClassTypeInfo( const ClassTypeInfoVar *class_type_info_var ) : UnsafeClassTypeInfo( class_type_info_var ) {
	userMutex = new UserMutex;
}
const ClassTypeInfoVar * ClassTypeInfo::getClassTypeInfoVar( ) const {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfo::getClassTypeInfoVar( );
	userMutex->unlock( );
	return result;
}
TypeInfoRef * ClassTypeInfo::appendClassTypeInfo( const ClassTypeInfoVar *class_type_info_var, const void *ptr, const std::type_info &type_info, const QString &name ) {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfo::appendClassTypeInfo( class_type_info_var, ptr, type_info, name );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfo::deleteClassTypeInfo( const void *ptr ) {
	userMutex->lock( );
	bool result = UnsafeClassTypeInfo::deleteClassTypeInfo( ptr );
	userMutex->unlock( );
	return result;
}
TypeInfoRef * ClassTypeInfo::getfristTypeInfoRef( const void *ptr ) const {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfo::getfristTypeInfoRef( ptr );
	userMutex->unlock( );
	return result;
}
TypeInfoRef * ClassTypeInfo::getEntityTypeInfoRef( ) const {
	userMutex->lock( );
	auto result = UnsafeClassTypeInfo::getEntityTypeInfoRef( );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfo::getAllTypeInfoRefArray( TypeInfoRef **&result_arry_ptr, size_t &result_array_count ) const {
	userMutex->lock( );
	bool result = UnsafeClassTypeInfo::getAllTypeInfoRefArray( result_arry_ptr, result_array_count );
	userMutex->unlock( );
	return result;
}
