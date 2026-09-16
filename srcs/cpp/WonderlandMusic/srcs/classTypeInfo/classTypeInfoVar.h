#ifndef CLASSTYPEINFOVAR_H_H_HEAD__FILE__
#define CLASSTYPEINFOVAR_H_H_HEAD__FILE__
#include <typeinfo>

#include "interface/iClassTypeInfo.h"

class QString;
class TypeInfoRef;

class ClassTypeInfoVar {
protected:
	virtual const IClassTypeInfo * getClassTypeInfo( const void *class_ptr ) const;
	virtual const IClassTypeInfo * setClassTypeInfo( const ClassTypeInfoVar *class_ptr, const void *ptr, const std::type_info &class_type_info, const char *class_type_name );

	virtual bool deleteClassTypeInfo( const void *class_ptr );

	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @param type_info 类型信息
	/// @param class_name 类型别名
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * regClassTypeInfoRef( Reg_Ptr_Type *ptr, const std::type_info &type_info, const QString &class_name ) {
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
		return setClassTypeInfo( ptr, ptr, typeInfo, classTypeName );
	}

	/// @brief 查找一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回注册的对象指针
	template< typename Reg_Ptr_Type >
	const IClassTypeInfo * findClassTypeInfoRef( Reg_Ptr_Type *ptr ) const {
		return getClassTypeInfo( ptr );
	}
	/// @brief 注册一个类型对象
	/// @tparam Reg_Ptr_Type 注册的类型
	/// @param ptr 类型的指针对象
	/// @return 成功返回true
	template< typename Reg_Ptr_Type >
	bool uninstallTypeInfoRef( Reg_Ptr_Type *ptr ) {
		return deleteClassTypeInfo( ptr );
	}

public:
	virtual ~ClassTypeInfoVar( );
};

#endif // CLASSTYPEINFOVAR_H_H_HEAD__FILE__
