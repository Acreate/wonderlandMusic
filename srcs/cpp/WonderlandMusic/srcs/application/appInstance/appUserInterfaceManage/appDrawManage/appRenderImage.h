#ifndef APPRENDERIMAGE_H_H_HEAD__FILE__
#define APPRENDERIMAGE_H_H_HEAD__FILE__

#include <interface/iAppResourceCore.h>

#include "../../../../classTypeInfo/classTypeInfoVar.h"

class IMusicItemWidthInfo;
class IMusicItem;
class IMusicFavoriteItem;
class ItemWidthInfo;
class QSize;
class QWidget;
class QPen;
class QColor;
class QString;
class QImage;
class QFontMetrics;
class QFont;

class AppRenderImage : public IAppResourceCore, public ClassTypeInfoVar {
protected:
	QFont *font = nullptr;
	QFontMetrics *fontMetrics = nullptr;
	QColor *brackGroundColor = nullptr;
	QColor *drawPenColor = nullptr;
	QPen *drawPen = nullptr;

protected:
	bool deleteResource( );
	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font, const QFontMetrics &font_metrics ) const;
	virtual bool getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFontMetrics &font_metrics ) const;

public:
	AppRenderImage( );

	~AppRenderImage( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	bool init( ) override;

	virtual const QFont * getFont( ) const;

	virtual const QFontMetrics * getFontMetrics( ) const;

	virtual bool appendImage( QImage &result_render_image, const QImage &left, const QImage &right ) const;
	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt ) const;
	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font ) const;

	virtual bool getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFont &font ) const;
	virtual bool getTxtSize( QSize &result_txt_size, const QString &render_txt ) const;
	virtual bool renderWidget( QImage &result_render_image, QWidget *render_widget ) const;
};
#endif // APPRENDERIMAGE_H_H_HEAD__FILE__
