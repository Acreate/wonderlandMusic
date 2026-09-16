#include "classTypeInfoVar.h"

#include "../application/appInstance.h"

#include "../tools/instanceTools.h"
const IClassTypeInfo * ClassTypeInfoVar::getClassTypeInfo( const void *class_ptr ) const {
	auto appInstance = InstanceTools::getAppInstance( );
	if( appInstance == nullptr )
		return nullptr;
	return appInstance->findClassTypeInfo( class_ptr );
}
const IClassTypeInfo * ClassTypeInfoVar::setClassTypeInfo( const ClassTypeInfoVar *class_ptr, const void *ptr, const std::type_info &class_type_info, const char *class_type_name ) {
	auto appInstance = InstanceTools::getAppInstance( );
	if( appInstance == nullptr )
		return nullptr;
	QString typeName = class_type_name;
	return appInstance->appendClassTypeInfoVar( class_ptr, ptr, class_type_info, typeName );
}
bool ClassTypeInfoVar::deleteClassTypeInfo( const void *class_ptr ) {
	auto appInstance = InstanceTools::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	return appInstance->removeClassTypeInfoVar( class_ptr );
}
ClassTypeInfoVar::~ClassTypeInfoVar( ) {
	uninstallTypeInfoRef( this );
}
