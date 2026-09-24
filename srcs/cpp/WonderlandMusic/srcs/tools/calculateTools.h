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
	inline bool isZero( const char *ptr, const size_t &ptr_count ) {
		size_t index = 0;
		char zero = 0;
		for( ; index < ptr_count; index += 1 )
			if( ptr[ index ] != zero )
				return false;
		return true;
	}
	template< typename T_Left_Type, typename R_Left_Type >
	bool equ( bool &result_var, const T_Left_Type &left, const R_Left_Type &right ) {
		result_var = false;
		auto leftTypeSize = sizeof( T_Left_Type );
		auto rightTypeSize = sizeof( R_Left_Type );
		if( leftTypeSize != rightTypeSize ) {
			if( leftTypeSize > rightTypeSize ) {
				auto leftPtr = ( const char * ) &left;
				auto rightPtr = ( const char * ) &right;
				decltype(leftTypeSize) index = 0;
				for( ; index < rightTypeSize; index += 1 )
					if( leftPtr[ index ] != rightPtr[ index ] )
						return true;

				auto lastCount = leftTypeSize - rightTypeSize;
				if( isZero( leftPtr + index, lastCount ) == false )
					return true;

				result_var = true;
				return true;
			} else {
				auto leftPtr = ( const char * ) &left;
				auto rightPtr = ( const char * ) &right;
				decltype(leftTypeSize) index = 0;
				for( ; index < leftTypeSize; index += 1 )
					if( leftPtr[ index ] != rightPtr[ index ] )
						return true;

				auto lastCount = rightTypeSize - leftTypeSize;
				if( isZero( rightPtr + index, lastCount ) == false )
					return true;

				result_var = true;
				return true;
			}
		}
		decltype(leftTypeSize) index = 0;
		auto leftPtr = ( const char * ) &left;
		auto rightPtr = ( const char * ) &right;
		for( ; index < leftTypeSize; index += 1 )
			if( leftPtr[ index ] != rightPtr[ index ] )
				return true;
		result_var = true;
		return true;
	}
};

#endif // CALCULATETOOLS_H_H_HEAD__FILE__
