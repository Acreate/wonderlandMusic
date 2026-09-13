#ifndef PROGRESSITEM_H_H_HEAD__FILE__
#define PROGRESSITEM_H_H_HEAD__FILE__
#include "../drawItem/drawItem.h"

class ProgressItem : public DrawItem {
private:
	size_t maxVar;

public:
	ProgressItem( );
	~ProgressItem( ) override;
	virtual void setMaxValue( const size_t &max_var );
	virtual size_t getMaxValue( ) const;
	virtual bool calculateXPosVar( size_t &result_var, const int &x_pos, const bool &is_ceil = true ) const;
	virtual bool calculateVarXPos( int &result_x_pos, const size_t &var, const bool &is_ceil = true ) const;
};

#endif // PROGRESSITEM_H_H_HEAD__FILE__
