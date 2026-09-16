#include "unsafeClassTypeInfoStack.h"

#include "../interface/iClassTypeInfo.h"
#include <qdebug.h>
const IClassTypeInfo * UnsafeClassTypeInfoStack::fromClassTypeInfoVarGetClassTypeInfo( const IClassTypeInfo *class_type_info ) const {
	size_t index;
	IClassTypeInfo *result;
	if( UnsafeClassTypeInfoStack::fromClassTypeInfoVarGetClassTypeInfo( index, result, class_type_info ) == false )
		return nullptr;
	return result;
}
const bool UnsafeClassTypeInfoStack::fromClassTypeInfoVarGetClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const IClassTypeInfo *class_type_info ) const {
	auto classTypeInfoVar = class_type_info->getClassTypeInfoVar( );
	if( classTypeInfoVar == nullptr )
		return false;
	size_t count = classTypeInfoVector.size( );
	if( count == 0 )
		return false;
	auto data = classTypeInfoVector.data( );
	result_index = 0;
	for( ; result_index < count; result_index += 1 )
		if( data[ result_index ]->getClassTypeInfoVar( ) == classTypeInfoVar ) {
			result_class_type_info = data[ result_index ];
			return true;
		}
	return false;
}
UnsafeClassTypeInfoStack::UnsafeClassTypeInfoStack( ) {
}
UnsafeClassTypeInfoStack::~UnsafeClassTypeInfoStack( ) {
	UnsafeClassTypeInfoStack::clear( );
}
bool UnsafeClassTypeInfoStack::appendClassTypeInfoVar( IClassTypeInfo *class_type_info_ptr, const void *ptr, const std::type_info &class_type_info, const QString &class_type_name ) {
	size_t index;
	IClassTypeInfo *result;
	if( UnsafeClassTypeInfoStack::fromClassTypeInfoVarGetClassTypeInfo( index, result, class_type_info_ptr ) ) {
		auto classTypeInfoVar = result->getClassTypeInfoVar( );
		TypeInfoRef *classTypeInfo = result->appendClassTypeInfo( classTypeInfoVar, ptr, class_type_info, class_type_name );
		return false;
	}
	classTypeInfoVector.emplace_back( class_type_info_ptr );
	return class_type_info_ptr->appendClassTypeInfo( class_type_info_ptr->getClassTypeInfoVar( ), ptr, class_type_info, class_type_name );
}
const IClassTypeInfo * UnsafeClassTypeInfoStack::getClassTypeInfo( const void *ptr ) const {
	IClassTypeInfo *result;
	size_t index;
	return UnsafeClassTypeInfoStack::getClassTypeInfo( index, result, ptr ) ? result : nullptr;
}
const bool UnsafeClassTypeInfoStack::getClassTypeInfo( size_t &result_index, IClassTypeInfo *&result_class_type_info, const void *ptr ) const {
	size_t count = classTypeInfoVector.size( );
	if( count == 0 )
		return false;
	auto data = classTypeInfoVector.data( );
	for( result_index = 0; result_index < count; result_index += 1 )
		if( data[ result_index ]->getClassTypeInfoVar( ) == ptr ) {
			result_class_type_info = data[ result_index ];
			return true;
		}
	for( result_index = 0; result_index < count; result_index += 1 )
		if( data[ result_index ]->getfristClassTypeInfo( ptr ) ) {
			result_class_type_info = data[ result_index ];
			return true;
		}
	return false;
}
bool UnsafeClassTypeInfoStack::removeClassTypeInfo( const void *ptr ) {
	IClassTypeInfo *result;
	size_t index;
	if( UnsafeClassTypeInfoStack::getClassTypeInfo( index, result, ptr ) == false )
		return false;
	classTypeInfoVector.erase( classTypeInfoVector.begin( ) + index );
	IClassTypeInfoStack::deleteIClassTypeInfo( result );
	return true;
}
void UnsafeClassTypeInfoStack::clear( ) {
	size_t count = classTypeInfoVector.size( );
	if( count ) {
		auto data = classTypeInfoVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			IClassTypeInfoStack::deleteIClassTypeInfo( data[ index ] );
		classTypeInfoVector.clear( );
	}
}
