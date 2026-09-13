#ifndef CALCULATETOOLS_H_H_HEAD__FILE__
#define CALCULATETOOLS_H_H_HEAD__FILE__

namespace CalculateTools {
	template< typename Var_Type >
	Var_Type mod( const Var_Type &left, const Var_Type &right ) {
		Var_Type result = left;
		while( result > right )
			result -= right;
		return result;
	}

	template< typename Var_Type >
	bool equ( const Var_Type &left, const Var_Type &right ) {
		auto typeSize = sizeof( Var_Type );
		decltype(typeSize) index = 0;
		auto leftPtr = ( const char * ) &left;
		auto rightPtr = ( const char * ) &right;
		for( ; index < typeSize; index += 1 )
			if( leftPtr[ index ] != rightPtr[ index ] )
				return false;
		return true;
	}
};

#endif // CALCULATETOOLS_H_H_HEAD__FILE__
