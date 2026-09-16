#include "unsafeClassTypeInfo.h"

#include "../typeInfoRef.h"

UnsafeClassTypeInfo::~UnsafeClassTypeInfo( ) {
}
UnsafeClassTypeInfo::UnsafeClassTypeInfo( const ClassTypeInfoVar *class_type_info_var ) : IClassTypeInfo( class_type_info_var ) {
}
TypeInfoRef * UnsafeClassTypeInfo::getfristTypeInfoRef( const void *ptr ) const {
	size_t infoMaxCout = IClassTypeInfo::getTypeInfoMaxCout( );
	if( infoMaxCout == 0 )
		return nullptr;
	size_t typeIndex = IClassTypeInfo::getTypeInfoCrrentIndex( );
	if( typeIndex == infoMaxCout )
		return nullptr;
	auto typeInfoArrayPtr = IClassTypeInfo::getAliasTypeInfoArrayPtr( );
	for( ; typeIndex < infoMaxCout; typeIndex += 1 )
		if( typeInfoArrayPtr[ typeIndex ]->isType( ptr ) )
			return typeInfoArrayPtr[ typeIndex ];
	return nullptr;
}
TypeInfoRef * UnsafeClassTypeInfo::getfristTypeInfoRef( const void *ptr, const std::type_info &type_info, const QString &name ) const {
	size_t infoMaxCout = IClassTypeInfo::getTypeInfoMaxCout( );
	if( infoMaxCout == 0 )
		return nullptr;
	size_t typeIndex = IClassTypeInfo::getTypeInfoCrrentIndex( );
	if( typeIndex == infoMaxCout )
		return nullptr;
	auto typeInfoArrayPtr = IClassTypeInfo::getAliasTypeInfoArrayPtr( );
	for( ; typeIndex < infoMaxCout; typeIndex += 1 )
		if( typeInfoArrayPtr[ typeIndex ]->isType( ptr, type_info, name ) )
			return typeInfoArrayPtr[ typeIndex ];
	return nullptr;
}
TypeInfoRef * UnsafeClassTypeInfo::getfristTypeInfoRef( const void *ptr, const QString &name ) const {
	size_t infoMaxCout = IClassTypeInfo::getTypeInfoMaxCout( );
	if( infoMaxCout == 0 )
		return nullptr;
	size_t typeIndex = IClassTypeInfo::getTypeInfoCrrentIndex( );
	if( typeIndex == infoMaxCout )
		return nullptr;
	auto typeInfoArrayPtr = IClassTypeInfo::getAliasTypeInfoArrayPtr( );
	for( ; typeIndex < infoMaxCout; typeIndex += 1 )
		if( typeInfoArrayPtr[ typeIndex ]->isType( ptr, name ) )
			return typeInfoArrayPtr[ typeIndex ];
	return nullptr;
}
TypeInfoRef * UnsafeClassTypeInfo::getfristTypeInfoRef( const QString &name ) const {
	size_t infoMaxCout = IClassTypeInfo::getTypeInfoMaxCout( );
	if( infoMaxCout == 0 )
		return nullptr;
	size_t typeIndex = IClassTypeInfo::getTypeInfoCrrentIndex( );
	if( typeIndex == infoMaxCout )
		return nullptr;
	auto typeInfoArrayPtr = IClassTypeInfo::getAliasTypeInfoArrayPtr( );
	for( ; typeIndex < infoMaxCout; typeIndex += 1 )
		if( typeInfoArrayPtr[ typeIndex ]->isType( name ) )
			return typeInfoArrayPtr[ typeIndex ];
	return nullptr;
}
TypeInfoRef * UnsafeClassTypeInfo::getfristTypeInfoRef( const void *ptr, const std::type_info &type_info ) const {
	size_t infoMaxCout = IClassTypeInfo::getTypeInfoMaxCout( );
	if( infoMaxCout == 0 )
		return nullptr;
	size_t typeIndex = IClassTypeInfo::getTypeInfoCrrentIndex( );
	if( typeIndex == infoMaxCout )
		return nullptr;
	auto typeInfoArrayPtr = IClassTypeInfo::getAliasTypeInfoArrayPtr( );
	for( ; typeIndex < infoMaxCout; typeIndex += 1 )
		if( typeInfoArrayPtr[ typeIndex ]->isType( ptr, type_info ) )
			return typeInfoArrayPtr[ typeIndex ];
	return nullptr;
}
bool UnsafeClassTypeInfo::deleteClassTypeInfo( const void *ptr ) {
	size_t infoMaxCout = IClassTypeInfo::getTypeInfoMaxCout( );
	if( infoMaxCout == 0 )
		return false;
	size_t infoCrrentCout = IClassTypeInfo::getTypeInfoCrrentIndex( );
	if( infoCrrentCout == infoMaxCout )
		return false;
	size_t buffIndex = 0;
	size_t index = infoCrrentCout;
	auto typeInfoArrayPtr = IClassTypeInfo::getAliasTypeInfoArrayPtr( );
	for( ; index < infoMaxCout; index += 1 )
		if( typeInfoArrayPtr[ index ]->isType( ptr ) ) {
			IClassTypeInfo::deleteTargetClassTypeInfoPtr( typeInfoArrayPtr[ index ] );
			buffIndex += 1;
			typeInfoArrayPtr[ index ] = nullptr;
		}
	if( buffIndex == 0 )
		return false;
	IClassTypeInfo::moveNullptrToStartArray( );
	return true;
}

TypeInfoRef * UnsafeClassTypeInfo::appendClassTypeInfo( const ClassTypeInfoVar *class_type_info_var, const void *ptr, const std::type_info &type_info, const QString &name ) {
	// 并非本子类
	if( class_type_info_var != UnsafeClassTypeInfo::getClassTypeInfoVar( ) )
		return nullptr;
	// 匹配是否存在类型信息
	TypeInfoRef *typeInfoRef = UnsafeClassTypeInfo::getfristTypeInfoRef( ptr, type_info, name );
	if( typeInfoRef )
		return typeInfoRef;
	// 是否需要扩充
	size_t infoCrrentCout = IClassTypeInfo::getTypeInfoCrrentIndex( );
	if( 0 == infoCrrentCout )
		dilatationArray( );
	// 新建类型类型
	typeInfoRef = IClassTypeInfo::createClassTypeInfo( this, ptr, type_info, name );
	// 失败
	if( typeInfoRef == nullptr )
		return nullptr;
	if( typeInfoRef == IClassTypeInfo::appendClassTypeInfo( typeInfoRef ) )
		return typeInfoRef;
	IClassTypeInfo::deleteTargetClassTypeInfoPtr( typeInfoRef );
	return nullptr;
}
