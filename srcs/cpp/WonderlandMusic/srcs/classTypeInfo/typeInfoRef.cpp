#include "typeInfoRef.h"

#include <QList>
#include <QString>
#include <typeinfo>

TypeInfoRef::TypeInfoRef( const IClassTypeInfo *class_type_info, void *ptr, const std::type_info &type_info, const QString *const name ) : classTypeInfo( class_type_info ), name( new QString( *name ) ),
	typeInfo( type_info ),
	ptr( ptr ) {
	auto stringList = name->split( " " );
	qsizetype count = stringList.size( ) - 1;
	auto pointer = stringList.data( );
	*this->name = pointer[ count ];
}
TypeInfoRef::TypeInfoRef( const IClassTypeInfo *class_type_info, void *ptr, const std::type_info &type_info ) : TypeInfoRef( class_type_info, ptr, type_info, typeInfo.name( ) ) {
}
TypeInfoRef::TypeInfoRef( const IClassTypeInfo *class_type_info, void *ptr, const std::type_info &type_info, const QString &name ) : TypeInfoRef( class_type_info, ptr, type_info, &name ) {
}
const QString & TypeInfoRef::getName( ) const {
	return *name;
}
const std::type_info & TypeInfoRef::getTypeInfo( ) const {
	return typeInfo;
}
void * TypeInfoRef::getPtr( ) const {
	return ptr;
}
const IClassTypeInfo * TypeInfoRef::getClassTypeInfo( ) const {
	return classTypeInfo;
}
bool TypeInfoRef::isType( const void *ptr, const std::type_info &type_info, const QString &name ) const {
	return *this->name == name
		&& this->typeInfo == type_info
		&& this->ptr == ptr;
}
bool TypeInfoRef::isType( const std::type_info &type_info, const QString &name ) const {
	return *this->name == name
		&& this->typeInfo == type_info;
}
bool TypeInfoRef::isType( const void *ptr, const std::type_info &type_info ) const {
	return this->typeInfo == type_info
		&& this->ptr == ptr;
}
bool TypeInfoRef::isType( const void *ptr, const QString &name ) const {
	return *this->name == name
		&& this->ptr == ptr;
}
bool TypeInfoRef::isType( const void *ptr ) const {
	return this->ptr == ptr;
}
bool TypeInfoRef::isType( const std::type_info &type_info ) const {
	return this->typeInfo == type_info;
}
bool TypeInfoRef::isType( const QString &name ) const {
	return *this->name == name;
}
bool operator==( const TypeInfoRef &lhs, const TypeInfoRef &rhs ) {
	return *lhs.name == *rhs.name
		&& lhs.typeInfo == rhs.typeInfo
		&& lhs.ptr == rhs.ptr;
}
bool operator!=( const TypeInfoRef &lhs, const TypeInfoRef &rhs ) {
	return !( lhs == rhs );
}
TypeInfoRef::~TypeInfoRef( ) {
	delete name;
}
