#ifndef PROGRESSITEM_H_H_HEAD__FILE__
#define PROGRESSITEM_H_H_HEAD__FILE__
#include "../../interface/iItemDraw/iItemDraw.h"

class ProgressItem : public IItemDraw {
public:
	using ProgressItemDouble = long double;

private:
	QRect *drawRect;
	ProgressItemDouble var;

public:
	ProgressItem( );
	explicit ProgressItem( ProgressItemDouble var );
	~ProgressItem( ) override;
	virtual bool calculateXPosVar( ProgressItemDouble &result_var, const int &x_pos ) const;
	virtual bool calculateVarXPos( int &result_x_pos, const ProgressItemDouble &var ) const;
	virtual ProgressItemDouble getCurrentVar( ) const;
	virtual bool setCurrentVar( const ProgressItemDouble &new_var );
	bool loadFileToDraw( const QString &load_image_file_path ) override;
	bool loadStringToDraw( const QString &set_string_draw_to_buff ) override;
	bool setDraw( const QImage &draw ) override;
	bool drawToParintr( QPainter &painter ) override;

public:
	void moveTo( const int &x, const int &y ) override;
	void reSize( const int &width, const int &height ) override;
	void setGeometry( const QRect &geometry ) override;
	void setGeometry( const int &x, const int &y, const int &width, const int &height ) override;
	virtual const QRect & getDrawRect( ) const;
};

#endif // PROGRESSITEM_H_H_HEAD__FILE__
