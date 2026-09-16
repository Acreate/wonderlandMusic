#ifndef TEMPLATEARGS_H_H_HEAD__FILE__
#define TEMPLATEARGS_H_H_HEAD__FILE__
#include <QString>
#include <string>
#include <utility>
#include <typeinfo>

#include "../classTypeInfo/interface/iClassTypeInfo.h"

class ClassTypeInfoStack;
class TypeInfoRef;
class OptionPanel;
class QObject;

namespace classTypeTools {
	namespace entityTools {
		/// @brief 获取指针指向对象的名称
		/// @param ty 匹配指针
		/// @return 指针类型
		QString getTypeName( const QObject *ty );

		/// @brief 获取指针指向对象的名称
		/// @param ty 匹配指针
		/// @return 指针类型
		QString getTypeName( const nullptr_t ty );
		/// @brief 获取指针指向对象的名称
		/// @param ty 匹配指针
		/// @return 指针类型
		QString getTypeName( const void *ty );

		/// @brief 删除指针指向对象的类对象信息
		/// @param ptr 匹配指针
		/// @return 成功返回 true
		bool deleteClassTypeInfo( const void *ptr );
		/// @brief 设置指针对象信息
		/// @param class_ptr 设置的指针
		/// @param class_type_info 设置的类型
		/// @param class_type_name 设置的名称
		/// @return 设置指针指向对象信息。失败返回 nullptr
		const IClassTypeInfo * setClassTypeInfo( const void *class_ptr, const std::type_info &class_type_info, const char *class_type_name );
		/// @brief 获取指针匹配的对象信息
		/// @param ty 匹配指针
		/// @return 失败返回 nullptr
		const IClassTypeInfo * getClassTypeInfo( const void *ty );
		/// @brief 匹配指针类型
		/// @param ptr 匹配指针
		/// @param ptr_type 匹配对象类型
		/// @return 不匹配返回 false
		bool isType( const void *ptr, const std::type_info &ptr_type );
		/// @brief 匹配指针类型
		/// @param ptr 匹配指针
		/// @param ptr_type 匹配对象类型
		/// @param class_type_name 对象类型
		/// @return 不匹配返回 false
		bool isType( const void *ptr, const std::type_info &ptr_type, const char *class_type_name );

		/// @brief 获取指针指向对象的名称
		/// @param ty 匹配指针
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 指针类型
		QString getTypeName( const QObject *ty, ClassTypeInfoStack *class_type_info_stack );

		/// @brief 获取指针指向对象的名称
		/// @param ty 匹配指针
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 指针类型
		QString getTypeName( const nullptr_t ty, ClassTypeInfoStack *class_type_info_stack );
		/// @brief 获取指针指向对象的名称
		/// @param ty 匹配指针
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 指针类型
		QString getTypeName( const void *ty, ClassTypeInfoStack *class_type_info_stack );

		/// @brief 删除指针指向对象的类对象信息
		/// @param ptr 匹配指针
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 成功返回 true
		bool deleteClassTypeInfo( const void *ptr, ClassTypeInfoStack *class_type_info_stack );
		/// @brief 设置指针对象信息
		/// @param class_ptr 设置的指针
		/// @param class_type_info 设置的类型
		/// @param class_type_name 设置的名称
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 设置指针指向对象信息。失败返回 nullptr
		const IClassTypeInfo * setClassTypeInfo( const void *class_ptr, const std::type_info &class_type_info, const char *class_type_name, ClassTypeInfoStack *class_type_info_stack );
		/// @brief 获取指针匹配的对象信息
		/// @param ty 匹配指针
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 失败返回 nullptr
		const IClassTypeInfo * getClassTypeInfo( const void *ty, ClassTypeInfoStack *class_type_info_stack );
		/// @brief 匹配指针类型
		/// @param ptr 匹配指针
		/// @param ptr_type 匹配对象类型
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 不匹配返回 false
		bool isType( const void *ptr, const std::type_info &ptr_type, ClassTypeInfoStack *class_type_info_stack );
		/// @brief 匹配指针类型
		/// @param ptr 匹配指针
		/// @param ptr_type 匹配对象类型
		/// @param class_type_name 对象类型
		/// @param class_type_info_stack 参考信息堆栈
		/// @return 不匹配返回 false
		bool isType( const void *ptr, const std::type_info &ptr_type, const char *class_type_name, ClassTypeInfoStack *class_type_info_stack );
	}

	/// @brief 剥离类型描述符
	/// @tparam T 剥离类型
	/// @return 基础类型名称
	template< typename T >
	consteval auto stripPtrAndRef( ) {
		if constexpr( std::is_pointer_v< T > ) {
			return stripPtrAndRef< std::remove_pointer_t< T > >( );
		} else if constexpr( std::is_lvalue_reference_v< T > || std::is_rvalue_reference_v< T > ) {
			return stripPtrAndRef< std::remove_reference_t< T > >( );
		} else {
			return std::type_identity< T > { };
		}
	}
	/// @brief 剥离描述符类型
	template< typename T >
	using TStripAllPtrRef_T = typename decltype(stripPtrAndRef< T >( ))::type;

	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regTypeInfoRef( Reg_Ptr_Type *ptr ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		auto classTypeName = typeInfo.name( );
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
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_type_info_stack 指定的类型堆栈
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regTypeInfoRef( Reg_Ptr_Type *ptr, ClassTypeInfoStack *class_type_info_stack ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		return entityTools::setClassTypeInfo( ptr, typeInfo, typeInfo.name( ), class_type_info_stack );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_name 类型别名
	/// @param class_type_info_stack 指定的类型堆栈
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regTypeInfoRef( Reg_Ptr_Type *ptr, const char * &class_name, ClassTypeInfoStack *class_type_info_stack ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		return entityTools::setClassTypeInfo( ptr, typeInfo, class_name, class_type_info_stack );
	}

	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_type_info_stack 指定的类型堆栈
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	bool uninstallTypeInfoRef( Reg_Ptr_Type *ptr, ClassTypeInfoStack *class_type_info_stack ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		QString name = typeInfo.name( );
		return entityTools::deleteClassTypeInfo( ptr, class_type_info_stack );
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
	/// @brief 获取指针对象类型名称
	/// @param ptr 获取的指向对象
	/// @return 对象类型名称
	inline QString getTypeName( const nullptr_t ptr ) {
		return entityTools::getTypeName( ptr );
	}
	/// @brief 获取匹配对象类型名称
	/// @tparam type 类型
	/// @return 匹配对象类型名称
	template< typename type >
	QString getTypeName( ) {
		return QString( typeid( type ).name( ) );
	}
	/// @brief 获取匹配的指针对象类型名称
	/// @tparam type 类型
	/// @param ptr 匹配指针对象
	/// @return 指针对象类型名称
	template< typename type >
	QString getTypeName( const type *ptr ) {
		QString name = entityTools::getTypeName( ptr );
		if( name.isEmpty( ) )
			return QString( typeid( type ).name( ) );
		return name;
	}
	/// @brief 检测指针类型是否为匹配对象类型
	/// @tparam target_type 匹配的类型
	/// @tparam type 指针对象类型
	/// @param ptr 对象指针
	/// @return 检查对象指针指向类型是否为 target_type 类型，匹配返回 true
	template< typename target_type, typename type >
	bool isType( const type &ptr ) {
		auto &ptrType = typeid( target_type );
		auto typeName = ptrType.name( );
		constexpr bool is_type_ptr = std::is_pointer_v< type >;
		if constexpr( is_type_ptr )
			return entityTools::isType( ptr, ptrType, typeName );
		return entityTools::isType( &ptr, ptrType, typeName );
	}
	/// @brief 转换指针到匹配类型
	/// @tparam target_type 转换的目标类型
	/// @tparam type 当前指针对象类型
	/// @param ptr 被转换的指针
	/// @return 失败返回 nullptr
	template< typename target_type, typename type >
	target_type * cast_type( type *ptr ) {
		if( classTypeTools::isType< target_type >( ptr ) == false )
			return nullptr;
		return static_cast< target_type * >( ptr );
	}

	/// @brief 转换指针到匹配类型
	/// @tparam target_type 转换的目标类型
	/// @tparam type 当前指针对象类型
	/// @param ptr 被转换的指针
	/// @return 失败返回 nullptr
	template< typename target_type, typename type >
	const target_type * cast_type( const type *ptr ) {
		if( classTypeTools::isType< target_type >( ptr ) == false )
			return nullptr;
		return static_cast< const target_type * >( ptr );
	}
	/// @brief 获取匹配的指针对象类型名称
	/// @tparam type 类型
	/// @param ptr 匹配指针对象
	/// @param class_type_info_stack 指定匹配的对象信息存储目标
	/// @return 指针对象类型名称
	template< typename type >
	QString getTypeName( const type *ptr, ClassTypeInfoStack *class_type_info_stack ) {
		QString name = entityTools::getTypeName( ptr, class_type_info_stack );
		if( name.isEmpty( ) )
			return QString( typeid( type ).name( ) );
		return name;
	}
	/// @brief 检测指针类型是否为匹配对象类型
	/// @tparam target_type 匹配的类型
	/// @tparam type 指针对象类型
	/// @param ptr 对象指针
	/// @param class_type_info_stack 指定匹配的对象信息存储目标
	/// @return 检查对象指针指向类型是否为 target_type 类型，匹配返回 true
	template< typename target_type, typename type >
	bool isType( const type &ptr, ClassTypeInfoStack *class_type_info_stack ) {
		auto &ptrType = typeid( target_type );
		auto typeName = ptrType.name( );
		constexpr bool is_type_ptr = std::is_pointer_v< type >;
		if constexpr( is_type_ptr )
			return entityTools::isType( ptr, ptrType, typeName, class_type_info_stack );
		return entityTools::isType( &ptr, ptrType, typeName, class_type_info_stack );
	}
	/// @brief 转换指针到匹配类型
	/// @tparam target_type 转换的目标类型
	/// @tparam type 当前指针对象类型
	/// @param ptr 被转换的指针
	/// @param class_type_info_stack 指定匹配的对象信息存储目标
	/// @return 失败返回 nullptr
	template< typename target_type, typename type >
	target_type * cast_type( type *ptr, ClassTypeInfoStack *class_type_info_stack ) {
		if( classTypeTools::isType< target_type >( ptr, class_type_info_stack ) == false )
			return nullptr;
		return static_cast< target_type * >( ptr );
	}

	/// @brief 转换指针到匹配类型
	/// @tparam target_type 转换的目标类型
	/// @tparam type 当前指针对象类型
	/// @param ptr 被转换的指针
	/// @param class_type_info_stack 指定匹配的对象信息存储目标
	/// @return 失败返回 nullptr
	template< typename target_type, typename type >
	const target_type * cast_type( const type *ptr, ClassTypeInfoStack *class_type_info_stack ) {
		if( classTypeTools::isType< target_type >( ptr, class_type_info_stack ) == false )
			return nullptr;
		return static_cast< const target_type * >( ptr );
	}
}

#endif // TEMPLATEARGS_H_H_HEAD__FILE__
