#include "iClassTypeInfo.h"

#include <QStringList>

#include "../typeInfoRef.h"
void IClassTypeInfo::moveNullptrToStartArray( ) {
	if( aliasTypeInfoArrayPtr == nullptr && typeInfoMaxCout == 0 || typeInfoMaxCout == typeInfoCrrentCout && aliasTypeInfoArrayPtr == nullptr )
		return;
	ArrayType buff = new TypeInfoRef *[ typeInfoMaxCout ] { nullptr };
	size_t buffIndex = typeInfoMaxCout;
	size_t index = typeInfoMaxCout - 1;
	for( ; index != typeInfoCrrentCout; index -= 1 )
		if( aliasTypeInfoArrayPtr[ index ] ) {
			buffIndex -= 1;
			buff[ buffIndex ] = aliasTypeInfoArrayPtr[ index ];
		}
	if( aliasTypeInfoArrayPtr[ index ] ) {
		buffIndex -= 1;
		buff[ buffIndex ] = aliasTypeInfoArrayPtr[ index ];
	}
	typeInfoCrrentCout = buffIndex;
	delete[] aliasTypeInfoArrayPtr;
	aliasTypeInfoArrayPtr = buff;
}
void IClassTypeInfo::dilatationArray( ) {
	auto newSize = typeInfoMaxCout + addToCount;
	ArrayType buff = new TypeInfoRef *[ newSize ] { nullptr };
	size_t buffIndex = newSize;
	if( aliasTypeInfoArrayPtr && typeInfoMaxCout != 0 && typeInfoMaxCout != typeInfoCrrentCout ) {
		buffIndex = typeInfoMaxCout - 1;
		size_t index = typeInfoMaxCout - 1;
		for( ; index != typeInfoCrrentCout; index -= 1 )
			if( aliasTypeInfoArrayPtr[ index ] ) {
				buffIndex -= 1;
				buff[ buffIndex ] = aliasTypeInfoArrayPtr[ index ];
			}
		if( aliasTypeInfoArrayPtr[ index ] ) {
			buffIndex -= 1;
			buff[ buffIndex ] = aliasTypeInfoArrayPtr[ index ];
		}
	}
	typeInfoCrrentCout = buffIndex;
	if( aliasTypeInfoArrayPtr )
		delete[] aliasTypeInfoArrayPtr;
	aliasTypeInfoArrayPtr = buff;
	typeInfoMaxCout = newSize;
}
size_t IClassTypeInfo::getAddToCount( ) const {
	return addToCount;
}
size_t IClassTypeInfo::getTypeInfoMaxCout( ) const {
	return typeInfoMaxCout;
}
size_t IClassTypeInfo::getTypeInfoCrrentIndex( ) const {
	return typeInfoCrrentCout;
}
IClassTypeInfo::ArrayType IClassTypeInfo::getAliasTypeInfoArrayPtr( ) const {
	return aliasTypeInfoArrayPtr;
}
IClassTypeInfo::IClassTypeInfo( const ClassTypeInfoVar *class_type_info_var ) {
	addToCount = 1024;
	typeInfoMaxCout = 0;
	typeInfoCrrentCout = 0;
	aliasTypeInfoArrayPtr = nullptr;
	classTypeInfoVar = class_type_info_var;
}
IClassTypeInfo::~IClassTypeInfo( ) {
	IClassTypeInfo::deleteArrayClassTypeInfo( );
}
const ClassTypeInfoVar * IClassTypeInfo::getClassTypeInfoVar( ) const {
	return classTypeInfoVar;
}
TypeInfoRef * IClassTypeInfo::getEntityTypeInfoRef( ) const {
	if( typeInfoMaxCout == 0 || aliasTypeInfoArrayPtr == nullptr )
		return nullptr;
	return aliasTypeInfoArrayPtr[ typeInfoCrrentCout ];
}
bool IClassTypeInfo::getAllTypeInfoRefArray( TypeInfoRef **&result_arry_ptr, size_t &result_array_count ) const {
	if( typeInfoMaxCout == 0 || aliasTypeInfoArrayPtr == nullptr )
		return false;
	result_arry_ptr = aliasTypeInfoArrayPtr + typeInfoCrrentCout;
	result_array_count = typeInfoMaxCout - typeInfoCrrentCout;
	return true;
}
bool IClassTypeInfo::getClassNameVector( std::vector< QString > &result_name ) const {
	TypeInfoRef **result_arry_ptr;
	size_t result_array_count;
	if( IClassTypeInfo::getAllTypeInfoRefArray( result_arry_ptr, result_array_count ) ) {
		size_t index = 0;
		result_name.resize( result_array_count );
		auto nameData = result_name.data( );
		for( ; index < result_array_count; index += 1 )
			nameData[ index ] = QString( "%1(0x%2)" ).arg( result_arry_ptr[ index ]->getName( ) ).arg( QString::number( ( size_t ) result_arry_ptr[ index ]->getPtr( ), 16 ) );
		return true;
	}

	return false;
}

void IClassTypeInfo::deleteArrayClassTypeInfo( ) {
	size_t typeIndex;
	if( typeInfoMaxCout && aliasTypeInfoArrayPtr )
		for( typeIndex = typeInfoCrrentCout; typeIndex < typeInfoMaxCout; typeIndex += 1 )
			IClassTypeInfo::deleteTargetClassTypeInfoPtr( aliasTypeInfoArrayPtr[ typeIndex ] );
	if( aliasTypeInfoArrayPtr )
		delete [] aliasTypeInfoArrayPtr;
	aliasTypeInfoArrayPtr = nullptr;
	typeInfoCrrentCout = 0;
	typeInfoMaxCout = 0;
}
TypeInfoRef * IClassTypeInfo::createClassTypeInfo( const IClassTypeInfo *class_type_info, const void *ptr, const std::type_info &type_info, const QString &name ) {
	return new TypeInfoRef( class_type_info, ptr, type_info, name );
}
bool IClassTypeInfo::deleteTargetClassTypeInfoPtr( TypeInfoRef *&delete_type_info_ref ) {
	if( delete_type_info_ref == nullptr )
		return false;
	delete delete_type_info_ref;
	delete_type_info_ref = nullptr;
	return true;
}
TypeInfoRef * IClassTypeInfo::appendClassTypeInfo( TypeInfoRef *type_info_ref ) {
	if( type_info_ref == nullptr )
		return nullptr;
	typeInfoCrrentCout -= 1;
	aliasTypeInfoArrayPtr[ typeInfoCrrentCout ] = type_info_ref;
	return type_info_ref;
}
