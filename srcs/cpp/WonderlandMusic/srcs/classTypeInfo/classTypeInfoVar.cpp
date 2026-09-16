#include "classTypeInfoVar.h"

#include "classTypeInfo.h"
#include "classTypeInfoStack.h"

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
	return appInstance->appendClassTypeInfoVar( class_ptr, ptr, class_type_info, class_type_name );
}
bool ClassTypeInfoVar::deleteClassTypeInfo( const void *class_ptr ) {
	auto appInstance = InstanceTools::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	return appInstance->removeClassTypeInfoVar( class_ptr );
}
const IClassTypeInfo * ClassTypeInfoVar::getClassTypeInfo( const void *class_ptr, ClassTypeInfoStack *class_type_info_stack ) const {
	return class_type_info_stack->getClassTypeInfo( class_ptr );
}
const IClassTypeInfo * ClassTypeInfoVar::setClassTypeInfo( const ClassTypeInfoVar *class_ptr, const void *ptr, const std::type_info &class_type_info, const char *class_type_name, ClassTypeInfoStack *class_type_info_stack ) {
	auto classTypeInfo = new ClassTypeInfo( class_ptr );
	auto result = class_type_info_stack->appendClassTypeInfoVar( classTypeInfo, ptr, class_type_info, class_type_name );
	if( result == classTypeInfo )
		return classTypeInfo;
	delete classTypeInfo;
	return result;
}
bool ClassTypeInfoVar::deleteClassTypeInfo( const void *class_ptr, ClassTypeInfoStack *class_type_info_stack ) {
	return class_type_info_stack->removeClassTypeInfo( class_ptr );
}
ClassTypeInfoVar::~ClassTypeInfoVar( ) {
	if( classTypeInfoStack == nullptr )
		uninstallTypeInfoRef( this );
	else
		uninstallTypeInfoRef( this, classTypeInfoStack );
}
