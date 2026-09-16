#ifndef ICLASSTYPEINFO_H_H_HEAD__FILE__
#define ICLASSTYPEINFO_H_H_HEAD__FILE__

#include <typeinfo>
#include <vector>
class ClassTypeInfo;
class ClassTypeInfoVar;
class TypeInfoRef;
class UserMutex;
class QString;
class IClassTypeInfoStack;

class IClassTypeInfo {
	friend class IClassTypeInfoStack;

protected:
	using ArrayType = TypeInfoRef **;

private:
	const ClassTypeInfoVar *classTypeInfoVar;
	size_t addToCount;
	size_t typeInfoMaxCout;
	size_t typeInfoCrrentCout;
	ArrayType aliasTypeInfoArrayPtr;

protected:
	virtual void moveNullptrToStartArray( );
	virtual void dilatationArray( );
	virtual size_t getAddToCount( ) const;
	virtual size_t getTypeInfoMaxCout( ) const;
	virtual size_t getTypeInfoCrrentIndex( ) const;
	virtual ArrayType getAliasTypeInfoArrayPtr( ) const;

	virtual void deleteArrayClassTypeInfo( );
	virtual TypeInfoRef * createClassTypeInfo( const IClassTypeInfo *class_type_info, const void *ptr, const std::type_info &type_info, const QString &name );
	virtual bool deleteTargetClassTypeInfoPtr( TypeInfoRef *&delete_type_info_ref );

	virtual TypeInfoRef * appendClassTypeInfo( TypeInfoRef *type_info_ref );

protected:
	explicit IClassTypeInfo( const ClassTypeInfoVar *class_type_info_var );
	virtual ~IClassTypeInfo( );

public:
	virtual const ClassTypeInfoVar * getClassTypeInfoVar( ) const;
	virtual TypeInfoRef * getfristTypeInfoRef( const void *ptr ) const = 0;
	virtual TypeInfoRef * getEntityTypeInfoRef( ) const;
	virtual bool getAllTypeInfoRefArray( TypeInfoRef **&result_arry_ptr, size_t &result_array_count ) const;
	virtual bool deleteClassTypeInfo( const void *p ) = 0;
	virtual TypeInfoRef * appendClassTypeInfo( const ClassTypeInfoVar *class_type_info_var, const void *ptr, const std::type_info &type_info, const QString &name ) = 0;
	virtual bool getClassNameVector( std::vector< QString > &result_name ) const;
};

#endif // ICLASSTYPEINFO_H_H_HEAD__FILE__
