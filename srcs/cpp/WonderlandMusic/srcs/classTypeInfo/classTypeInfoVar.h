#ifndef CLASSTYPEINFOVAR_H_H_HEAD__FILE__
#define CLASSTYPEINFOVAR_H_H_HEAD__FILE__
#include <typeinfo>

#include "interface/iClassTypeInfo.h"

class ClassTypeInfoStack;
class QString;
class TypeInfoRef;

class ClassTypeInfoVar {
protected:
	ClassTypeInfoStack *classTypeInfoStack = nullptr;

protected:
	virtual const IClassTypeInfo * getClassTypeInfo( const void *class_ptr ) const;
	virtual const IClassTypeInfo * setClassTypeInfo( const ClassTypeInfoVar *class_ptr, void *ptr, const std::type_info &class_type_info, const char *class_type_name );
	virtual bool deleteClassTypeInfo( const void *class_ptr );
	virtual const IClassTypeInfo * getClassTypeInfo( const void *class_ptr, ClassTypeInfoStack *class_type_info_stack ) const;
	virtual const IClassTypeInfo * setClassTypeInfo( const ClassTypeInfoVar *class_ptr, void *ptr, const std::type_info &class_type_info, const char *class_type_name, ClassTypeInfoStack *class_type_info_stack );
	virtual bool deleteClassTypeInfo( const void *class_ptr, ClassTypeInfoStack *class_type_info_stack );

	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param type_info 类型信息
	/// @param class_name 类型别名
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regClassTypeInfoRef( Reg_Ptr_Type *ptr, const std::type_info &type_info, const QString &class_name ) {
		if( classTypeInfoStack )
			return setClassTypeInfo( ptr, ptr, type_info, class_name, classTypeInfoStack );
		return setClassTypeInfo( ptr, ptr, type_info, class_name );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_name 类型别名
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regClassTypeInfoRef( Reg_Ptr_Type *ptr, const QString &class_name ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		if( classTypeInfoStack )
			return setClassTypeInfo( ptr, ptr, typeInfo, class_name, classTypeInfoStack );
		return setClassTypeInfo( ptr, ptr, typeInfo, class_name );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regClassTypeInfoRef( Reg_Ptr_Type *ptr ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		auto classTypeName = typeInfo.name( );
		if( classTypeInfoStack )
			return setClassTypeInfo( ptr, ptr, typeInfo, classTypeName, classTypeInfoStack );
		return setClassTypeInfo( ptr, ptr, typeInfo, classTypeName );
	}

	/// @brief 查找一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * findClassTypeInfoRef( Reg_Ptr_Type *ptr ) const {
		if( classTypeInfoStack )
			return getClassTypeInfo( ptr, classTypeInfoStack );
		return getClassTypeInfo( ptr );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回true
	template< typename Reg_Ptr_Type >
	bool uninstallTypeInfoRef( Reg_Ptr_Type *ptr ) {
		if( classTypeInfoStack )
			return deleteClassTypeInfo( ptr, classTypeInfoStack );
		return deleteClassTypeInfo( ptr );
	}

protected:
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param type_info 类型信息
	/// @param class_name 类型别名
	/// @param class_type_info_stack 目标堆栈
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regClassTypeInfoRef( Reg_Ptr_Type *ptr, const std::type_info &type_info, const QString &class_name, ClassTypeInfoStack *class_type_info_stack ) {
		return setClassTypeInfo( ptr, ptr, type_info, class_name, class_type_info_stack );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_name 类型别名
	/// @param class_type_info_stack 目标堆栈
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regClassTypeInfoRef( Reg_Ptr_Type *ptr, const QString &class_name, ClassTypeInfoStack *class_type_info_stack ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		return setClassTypeInfo( ptr, ptr, typeInfo, class_name, class_type_info_stack );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_type_info_stack 目标堆栈
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regClassTypeInfoRef( Reg_Ptr_Type *ptr, ClassTypeInfoStack *class_type_info_stack ) {
		auto &typeInfo = typeid( Reg_Ptr_Type );
		auto classTypeName = typeInfo.name( );
		return setClassTypeInfo( ptr, ptr, typeInfo, classTypeName, class_type_info_stack );
	}

	/// @brief 查找一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_type_info_stack 目标堆栈
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * findClassTypeInfoRef( Reg_Ptr_Type *ptr, ClassTypeInfoStack *class_type_info_stack ) const {
		return getClassTypeInfo( ptr, class_type_info_stack );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param class_type_info_stack 目标堆栈
	/// @return 成功返回true
	template< typename Reg_Ptr_Type >
	bool uninstallTypeInfoRef( Reg_Ptr_Type *ptr, ClassTypeInfoStack *class_type_info_stack ) {
		return deleteClassTypeInfo( ptr, class_type_info_stack );
	}

public:
	virtual ~ClassTypeInfoVar( );
};

#endif // CLASSTYPEINFOVAR_H_H_HEAD__FILE__
