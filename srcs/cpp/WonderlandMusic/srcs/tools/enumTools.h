#ifndef ENUMTOOLS_H_H_HEAD__FILE__
#define ENUMTOOLS_H_H_HEAD__FILE__
#include <QString>
#include <QMetaEnum>

#include "calculateTools.h"

class EnumTools {
	template< typename T >
	static QString errorEnumTypeConver( T val ) {
		return QStringLiteral( "Unknown( conver_error : %1 )" ).arg( typeid( T ).name( ) );
	}

public:
	template< typename T_Colver_Var_Type = int64_t, typename T_Var_Type = int64_t >
	static QString toString( QMetaEnum &meta, T_Var_Type val ) {
		T_Colver_Var_Type value = static_cast< T_Colver_Var_Type >( val );
		bool isEqu;
		if( CalculateTools::equ( isEqu, value, val ) && isEqu ) {
			const char *name = meta.valueToKey( value );
			if( name )
				return QString::fromLatin1( name );
		}
		return errorEnumTypeConver( val );
	}

	template< typename T >
	static QString toString( T val ) {
		QMetaEnum meta = QMetaEnum::fromType< T >( );
		#define t_check( _type , _meta, _var ) \
			if constexpr( sizeof val == sizeof( _type ) ) \
				return toString< _type >( _meta, _var );
		t_check( int8_t, meta, val );
		t_check( int16_t, meta, val );
		t_check( int32_t, meta, val );
		t_check( int64_t, meta, val );
		return errorEnumTypeConver( val );
	}
};

#endif // ENUMTOOLS_H_H_HEAD__FILE__
