#ifndef TEMPLATEARGS_H_H_HEAD__FILE__
#define TEMPLATEARGS_H_H_HEAD__FILE__
#include <QString>
#include <string>
#include <utility>
#include <typeinfo>

#include "../classTypeInfo/interface/iClassTypeInfo.h"

class TypeInfoRef;
class OptionPanel;
class QObject;

namespace classTypeTools {
	namespace entityTools {
		QString getTypeName( const void *ty );
		QString getTypeName( const QObject *ty );
		QString getTypeName( const nullptr_t ty );
		bool deleteClassTypeInfo( const void *ptr );

		const IClassTypeInfo * setClassTypeInfo( const void *class_ptr, const std::type_info &class_type_info, const QString &class_type_name );
		const IClassTypeInfo * getClassTypeInfo( const void *ty );
		bool isType( const void *ptr, const std::type_info &ptr_type );
		bool isType( const void *ptr, const std::type_info &ptr_type, const QString &class_type_name );
	}

	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regTypeInfoRef( Reg_Ptr_Type *ptr ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		QString classTypeName = typeInfo.name( );
		return entityTools::setClassTypeInfo( ptr, typeInfo, classTypeName );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_name 类型别名
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regTypeInfoRef( Reg_Ptr_Type *ptr, const QString &class_name ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		return entityTools::setClassTypeInfo( ptr, typeInfo, class_name );
	}

	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	bool uninstallTypeInfoRef( Reg_Ptr_Type *ptr ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		QString name = typeInfo.name( );
		return entityTools::deleteClassTypeInfo( ptr );
	}
	/// @brief 创建指针对象
	/// @tparam Create_Ptr_Type 创建类型
	/// @tparam ptr_create_function_args 调用构造函数时填充的参数
	/// @param ptr 成功创建赋予的参数
	/// @param args 构造函数填充参数列表
	/// @return 创建失败则返回 nullptr 指针
	template< typename Create_Ptr_Type, typename ...ptr_create_function_args >
	static Create_Ptr_Type * make_args_ptr( Create_Ptr_Type *&ptr, ptr_create_function_args && ...args ) {
		ptr = new Create_Ptr_Type( std::forward< ptr_create_function_args >( args ) ... );
		return ptr;
	}

	inline QString getTypeName( const nullptr_t ptr ) {
		return entityTools::getTypeName( ptr );
	}
	template< typename type >
	QString getTypeName( ) {
		return QString( typeid( type ).name( ) );
	}
	template< typename type >
	QString getTypeName( const type *ptr ) {
		QString name = entityTools::getTypeName( ptr );
		if( name.isEmpty( ) )
			return QString( typeid( type ).name( ) );
		return name;
	}
	template< typename type >
	bool isType( const type *ptr ) {
		auto &ptrType = typeid( type );
		QString typeName = ptrType.name( );
		return entityTools::isType( ptr, ptrType, typeName );
	}
	template< typename type >
	bool isType( const type &ptr ) {
		return classTypeTools::isType( &ptr );
	}
	template< typename type >
	type * cast_type( type *ptr ) {
		if( classTypeTools::isType( ptr ) == false )
			return nullptr;
		return ( type * ) ptr;
	}
	template< typename type >
	const type * cast_type( const type *ptr ) {
		if( classTypeTools::isType( ptr ) == false )
			return nullptr;
		return ( const type * ) ptr;
	}
}

#endif // TEMPLATEARGS_H_H_HEAD__FILE__
