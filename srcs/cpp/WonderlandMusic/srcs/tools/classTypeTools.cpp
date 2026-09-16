#include "classTypeTools.h"

#include "instanceTools.h"

#include "../application/appInstance.h"

#include "../classTypeInfo/classTypeInfoStack.h"
#include "../classTypeInfo/typeInfoRef.h"

QString classTypeTools::entityTools::getTypeName( const nullptr_t ty ) {
	return QString( "void" );
}
QString classTypeTools::entityTools::getTypeName( const QObject *ty ) {
	return ty->metaObject( )->className( );
}

QString classTypeTools::entityTools::getTypeName( const void *ty ) {
	auto classTypeInfo = entityTools::getClassTypeInfo( ty );
	if( classTypeInfo == nullptr )
		return QString( );
	auto typeInfoRef = classTypeInfo->getEntityTypeInfoRef( );
	if( typeInfoRef == nullptr )
		return QString( "" );
	auto name = typeInfoRef->getName( );
	return name;
}

bool classTypeTools::entityTools::deleteClassTypeInfo( const void *ptr ) {
	auto appInstance = InstanceTools::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	return appInstance->removeClassTypeInfoVar( ptr );
}
const IClassTypeInfo * classTypeTools::entityTools::setClassTypeInfo( const void *class_ptr, const std::type_info &class_type_info, const char *class_type_name ) {
	auto appInstance = InstanceTools::getAppInstance( );
	if( appInstance == nullptr )
		return nullptr;
	auto findClassTypeInfo = appInstance->appendClassTypeInfoVar( nullptr, class_ptr, class_type_info, class_type_name );
	return findClassTypeInfo;
}
const IClassTypeInfo * classTypeTools::entityTools::getClassTypeInfo( const void *ty ) {
	auto appInstance = InstanceTools::getAppInstance( );
	if( appInstance == nullptr )
		return nullptr;
	auto findClassTypeInfo = appInstance->findClassTypeInfo( ty );
	if( findClassTypeInfo == nullptr )
		return nullptr;
	return findClassTypeInfo;
}
bool classTypeTools::entityTools::isType( const void *ptr, const std::type_info &ptr_type ) {
	auto classTypeInfo = entityTools::getClassTypeInfo( ptr );
	if( classTypeInfo == nullptr )
		return false;
	auto typeInfoRef = classTypeInfo->getfristTypeInfoRef( ptr_type );
	if( typeInfoRef == nullptr )
		return false;
	return true;
}
bool classTypeTools::entityTools::isType( const void *ptr, const std::type_info &ptr_type, const char *class_type_name ) {
	auto classTypeInfo = entityTools::getClassTypeInfo( ptr );
	if( classTypeInfo == nullptr )
		return false;
	QString typeName = class_type_name;
	auto charses = typeName.split( " " );
	qint64 nameCount = charses.size( );
	if( nameCount == 0 )
		return false;
	typeName = charses.data( )[ nameCount - 1 ];
	auto typeInfoRef = classTypeInfo->getfristTypeInfoRef( ptr_type, typeName );
	if( typeInfoRef == nullptr )
		return false;
	return true;
}
QString classTypeTools::entityTools::getTypeName( const void *ty, ClassTypeInfoStack *class_type_info_stack ) {
	auto classTypeInfo = class_type_info_stack->getClassTypeInfo( ty );
	if( classTypeInfo == nullptr )
		return QString( );
	auto typeInfoRef = classTypeInfo->getEntityTypeInfoRef( );
	if( typeInfoRef == nullptr )
		return QString( "" );
	auto name = typeInfoRef->getName( );
	return name;
}
QString classTypeTools::entityTools::getTypeName( const QObject *ty, ClassTypeInfoStack *class_type_info_stack ) {
	return ty->metaObject( )->className( );
}
QString classTypeTools::entityTools::getTypeName( const nullptr_t ty, ClassTypeInfoStack *class_type_info_stack ) {
	return QString( "void" );
}
bool classTypeTools::entityTools::deleteClassTypeInfo( const void *ptr, ClassTypeInfoStack *class_type_info_stack ) {
	return class_type_info_stack->removeClassTypeInfo( ptr );
}
const IClassTypeInfo * classTypeTools::entityTools::setClassTypeInfo( const void *class_ptr, const std::type_info &class_type_info, const char *class_type_name, ClassTypeInfoStack *class_type_info_stack ) {
	return nullptr;
}
const IClassTypeInfo * classTypeTools::entityTools::getClassTypeInfo( const void *ty, ClassTypeInfoStack *class_type_info_stack ) {
	return class_type_info_stack->getClassTypeInfo( ty );
}
bool classTypeTools::entityTools::isType( const void *ptr, const std::type_info &ptr_type, ClassTypeInfoStack *class_type_info_stack ) {
	auto classTypeInfo = class_type_info_stack->getClassTypeInfo( ptr );
	if( classTypeInfo == nullptr )
		return false;
	auto typeInfoRef = classTypeInfo->getfristTypeInfoRef( ptr_type );
	if( typeInfoRef == nullptr )
		return false;
	return true;
}
bool classTypeTools::entityTools::isType( const void *ptr, const std::type_info &ptr_type, const char *class_type_name, ClassTypeInfoStack *class_type_info_stack ) {
	auto classTypeInfo = class_type_info_stack->getClassTypeInfo( ptr );
	if( classTypeInfo == nullptr )
		return false;
	auto typeInfoRef = classTypeInfo->getfristTypeInfoRef( ptr_type, class_type_name );
	if( typeInfoRef == nullptr )
		return false;
	return true;
}
