#ifndef PROGRESSITEM_H_H_HEAD__FILE__
#define PROGRESSITEM_H_H_HEAD__FILE__
#include "../../interface/iItemDraw/iItemDraw.h"

class ProgressItem : public IItemDraw {
private:
	size_t maxVar;
	size_t currenVar;

protected:

public:
	ProgressItem( );
	~ProgressItem( ) override;
	virtual void setMaxValue( const size_t &max_var );
	virtual size_t getMaxValue( ) const;
	virtual bool calculateXPosVar( size_t &result_var, const int &x_pos, const bool &is_ceil = true ) const;
	virtual bool calculateVarXPos( int &result_x_pos, const size_t &var, const bool &is_ceil = true ) const;
	virtual size_t getCurrentVar( ) const;
	virtual bool setCurrentVar( const size_t &new_var );
	bool loadFileToDraw( const QString &load_image_file_path ) override;
	bool loadStringToDraw( const QString &set_string_draw_to_buff ) override;
	bool setDraw( const QImage &draw ) override;
};

#endif // PROGRESSITEM_H_H_HEAD__FILE__
