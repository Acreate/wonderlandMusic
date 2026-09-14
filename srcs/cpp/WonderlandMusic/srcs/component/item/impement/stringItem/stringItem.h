#ifndef STRINGITEM_H_H_HEAD__FILE__
#define STRINGITEM_H_H_HEAD__FILE__
#include "../../interface/iBuff/iBuff.h"
#include "../../interface/iCoord/iCoord.h"

class StringItem : public ICoord, public IBuff {
	QString *string;

public:
	StringItem( );
	~StringItem( ) override;
	virtual void setString( const QString &new_string );
	virtual const QString & getString( ) const;
	bool drawToParintr( QPainter &painter ) override;
};

#endif // STRINGITEM_H_H_HEAD__FILE__
