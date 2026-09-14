#ifndef CALCULATETOOLS_H_H_HEAD__FILE__
#define CALCULATETOOLS_H_H_HEAD__FILE__
#include <valarray>

namespace CalculateTools {
	template< typename Var_Type >
	Var_Type max( ) {
		return std::numeric_limits< Var_Type >::max( );
	}
	template< typename Var_Type >
	bool mod( Var_Type &result_var, const Var_Type &left, const Var_Type &right ) {
		if( left < 0 && right < 0 ) {
			result_var = std::abs( left );
			auto absRight = std::abs( right );
			while( result_var > right )
				result_var -= right;
			return true;
		} else if( right < 0 ) {
			result_var = left;
			auto absRight = std::abs( right );
			while( result_var > absRight )
				result_var -= absRight;
			return true;
		} else if( left < 0 )
			return false;
		result_var = left;
		while( result_var > right )
			result_var -= right;
		return true;
	}

	template< typename Var_Type >
	bool equ( bool &result_var, const Var_Type &left, const Var_Type &right ) {
		result_var = false;
		auto typeSize = sizeof( Var_Type );
		decltype(typeSize) index = 0;
		auto leftPtr = ( const char * ) &left;
		auto rightPtr = ( const char * ) &right;
		for( ; index < typeSize; index += 1 )
			if( leftPtr[ index ] != rightPtr[ index ] )
				return true;
		result_var = true;
		return true;
	}
};

#endif // CALCULATETOOLS_H_H_HEAD__FILE__
