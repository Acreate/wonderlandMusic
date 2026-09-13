#ifndef OPTIONBUTTON_H_H_HEAD__FILE__
#define OPTIONBUTTON_H_H_HEAD__FILE__

#include <QWidget>

#include "../../../classTypeInfo/classTypeInfoVar.h"
class OptionPanel;

class OptionButton : public QWidget, public virtual ClassTypeInfoVar {
	Q_OBJECT;

	friend class OptionWindow;
	friend class OptionPanel;

	OptionWindow *optionWindow;

	OptionPanel *optionPanel = nullptr;
	int startOffsetX;
	int startOffsetY;

public:
	enum class Show_Type {
		All,
		Txt,
		Icon
	};

protected:
	bool click = false;
	Show_Type showType = Show_Type::All;
	~OptionButton( ) override;

public:
	OptionButton( OptionWindow *option_window );
	virtual bool isClick( ) const;
	virtual Show_Type getShowType( ) const;
	virtual void setShowType( const Show_Type show );
	virtual QSize updateSize( );

protected:
	void paintEvent( QPaintEvent * ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void enterEvent( QEnterEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
};
#endif // OPTIONBUTTON_H_H_HEAD__FILE__
