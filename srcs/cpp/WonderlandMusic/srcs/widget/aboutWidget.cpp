#include "aboutWidget.h"
#include <QDir>
#include <QLabel>
#include <qstyle.h>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLibraryInfo>

#include "../application/appInstance/applicationManage.h"
#include "../application/appInstance/appDataManage/jsonKey/aboutWidgetJsonKey.h"
#include "../application/appInstance/appDataManage/translate/aboutWidgetTranslate.h"

#include "../head/release_macro.h"

#include "../msgInfo/cmakeInfo.h"
#include "../msgInfo/messageErrorOut.h"

#include "../tools/instanceTools.h"

AboutWidget::AboutWidget( ) : OptionPanel( ) {
}

bool AboutWidget::init( ) {
	QString info;
	if( getSoftwareProtocolInfo( info ) == false )
		return false;

	if( AppTranslateTools::getAboutWidget( [this] ( AboutWidgetTranslate &translate ) {
		auto &titleName = translate.getTitleName( );
		setName( titleName );
		auto applicationManage = InstanceTools::getApplicationManage( );

		setWindowTitle( QString( applicationManage->applicationName( ) + " " + titleName ) );
		return true;
	} ) == false )
		return false;
	QImage qImage;
	if( AppJsonKeyTools::getAboutWidget( [&qImage] ( const AboutWidgetJsonKey &json_key ) {
		auto logoIconPath = json_key.getQtLogoIconPath( );
		QFileInfo fileInfo( logoIconPath );
		bool exists = fileInfo.exists( );
		if( exists == false ) {
			Message_Error_Out << tr( "Qt 标识图像不存在" ) + " : " + logoIconPath;
			auto fileName = ":/qt-project.org/qmessagebox/images/qtlogo-64.png";
			exists = qImage.load( fileName );
			if( exists == false )
				return false;
		}
		if( qImage.load( logoIconPath ) == false ) {
			Message_Error_Out << tr( "Qt 标识图像加载失败，重新使用 .rc 资源" ) + " : " + logoIconPath;
			auto fileName = ":/qt-project.org/qmessagebox/images/qtlogo-64.png";
			exists = qImage.load( fileName );
			if( exists == false )
				return false;
		}
		return true;
	} ) == false )
		return false;

	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( qtIco, 0, Qt::AlignTop );
	mainLayout->addWidget( textBox );

	QStyle *stylePtr = style( );
	auto icon = stylePtr->standardPixmap( QStyle::SP_TitleBarMenuButton );
	icon = icon.scaled( 64, 64 );
	qtIco->setPixmap( icon );
	auto pixmap = QPixmap::fromImage( qImage );
	qtIco->setPixmap( pixmap );
	qtIco->adjustSize( );
	qtIco->update( );
	textBox->setReadOnly( true );
	textBox->setText( info );
	textBox->setAutoFormatting( QTextEdit::AutoAll );
	textBox->adjustSize( );
	textBox->update( );

	mainLayout->update( );
	return true;
}

AboutWidget::~AboutWidget( ) {
	deleteResource( );
}

bool AboutWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( textBox );
	Delete_Resource_App_Core_Ptr( qtIco );
	Delete_Resource_App_Core_Ptr( mainLayout );
	return true;
}
QWidget * AboutWidget::toWidget( ) {
	return this;
}

bool AboutWidget::initBefore( ) {
	deleteResource( );
	mainLayout = new QHBoxLayout( this );

	qtIco = new QLabel( this );

	textBox = new QTextEdit( this );

	return true;
}

bool AboutWidget::initAfter( ) {
	return true;
}
bool AboutWidget::showPanelBefore( ) {
	return true;
}
bool AboutWidget::hidePanelBefore( ) {
	return true;
}
bool AboutWidget::releasePanelBefore( ) {
	return true;
}

bool AboutWidget::getSoftwareProtocolInfo( QString &result_info ) {
	// ===== 1. 软件基础信息（自定义）
	result_info += "<h3 style='color:#2980b9;margin:0;padding:0;'>" + tr( "📄 软件编译&运行协议信息" ) + "</h3><hr/>";
	result_info += "<p><b>" + tr( "软件版本：" ) + QString( "</b>%1</p>" ).arg( QString( "V0.0.1" ) );

	QDateTime compileDateTime;
	if( CmakeInfo::getGeneratePorjectDateTime( compileDateTime ) == false )
		return false;
	QString dateTimeString = compileDateTime.toString( "yyyy" + tr( "年" ) + "MM" + tr( "月" ) + "dd" + tr( "日" ) + " hh" + tr( "时" ) + "mm" + tr( "分" ) + "ss" + tr( "秒" ) );
	result_info += "<p><b>" + tr( "编译时间：" ) + QString( "</b>%1</p>" ).arg( dateTimeString );

	// ===== 2. Qt核心协议/版本信息（重中之重）
	result_info += "<p><b>▷ " + tr( "Qt 编译协议信息" ) + "</b></p>";
	result_info += "<p>" + tr( "Qt库版本" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QT_VERSION_STR );
#ifdef QT_DEBUG
	result_info += "<p>" + tr( "Qt编译模式" ) + "：</p><p style='padding-left:20px;color:red;'>" + tr( "调试版" ) + "</p>";
#else
	result_info += "<p>" + tr( "Qt编译模式" ) + "：</p><p style='padding-left:20px;color:red;'>" + tr( "发布版" ) + "</p>";
#endif
	result_info += "<p>" + tr( "Qt构建架构" ) + QString( "：</p><p style='padding-left:20px;'>%1 位</p>" ).arg( QSysInfo::WordSize );
	result_info += "<p>" + tr( "Qt 库构建架构类型" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QLibraryInfo::isSharedBuild( ) ? tr( "动态库" ) : tr( "静态库" ) );

	// ===== 3. 编译器协议/版本信息（软件编译核心协议）
	result_info += "<p><b>▷" + tr( " 编译器协议信息" ) + "</b></p>";
#ifdef _MSC_VER
	result_info += "<p>" + tr( "编译器" ) + QString( "：</p><p style='padding-left:20px;'>MSVC %1</p>" ).arg( QString::number( _MSC_VER / 100.0, 'f', 1 ) );
	result_info += "<p>" + tr( "编译协议" ) + "：</p><p style='padding-left:20px;'>" + tr( "VC++ 运行时协议" ) + "</p>";
#elif __GNUC__
	result_info += "<p>" + tr( "编译器)" + QString( "：</p><p style='padding-left:20px;'>GCC %1.%2</p>" ).arg( __GNUC__ ).arg( __GNUC_MINOR__ );
	result_info += "<p>" + tr( "编译协议" ) + "：</p><p style='padding-left:20px;'>GNU 开源协议 (GPL)</p>";
#elif __clang__
	result_info += "<p>" + tr( "编译器" ) + "：</p><p style='padding-left:20px;'>Clang</p>";
	result_info += "<p>" + tr( "编译协议" ) + "：</p><p style='padding-left:20px;'>LLVM " + tr( "开源协议" ) + "</p>";
#else
	result_info += "<p>" + tr( "编译器" ) + "：</p><p style='padding-left:20px;'>" + tr( "未知编译器" ) + "</p>";
#endif

	// ===== 4. 系统运行协议/环境信息
	result_info += "<p><b>▷ " + tr( "系统运行协议信息" ) + "</b></p>";
	result_info += "<p>" + tr( "操作系统" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::prettyProductName( ) );
	result_info += "<p>" + tr( "系统架构" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::currentCpuArchitecture( ) );
	result_info += "<p>" + tr( "系统内核" ) + QString( "：</p><p style='padding-left:20px;'>%1</p>" ).arg( QSysInfo::kernelType( ) + " " + QSysInfo::kernelVersion( ) );
	result_info += "<p>" + tr( "运行协议" ) + "：</p><p style='padding-left:20px;'>" + tr( "本地系统原生协议" ) + "</p>";

	// ===== 5. 软件版权协议（必加）

	QStringList stringList;
	QString pStyle( "style='color:#3c8e51;text-align:center;'" );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "©2025 本软件包含的贡献均属于其各自所有者的版权。" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "Qt 及其相应标识均为 Qt 公司有限公司在芬兰及其他国家/地区的商标。" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "所提供的 QT 库受 %1 许可证限制。" ).arg( "LGPL 3.0" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( tr( "所有其他商标均归其各自所有者所有。" ) ).arg( pStyle ) );
	pStyle = QStringLiteral( "style='color:#0079ff;text-align:center;'" );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( QString( "gitee : <a href='https://gitee.com/ChenYLhuman/WonderlandMusic'>https://gitee.com/ChenYLhuman/WonderlandMusic</a>" ) ).arg( pStyle ) );
	stringList.append( QString( "<p %2 >%1</p>" ).arg( QString( "github : <a href='https://github.com/Acreate/WonderlandMusic'>https://github.com/Acreate/WonderlandMusic</a>" ) ).arg( pStyle ) );
	result_info += QString( "<hr/>" ) + stringList.join( QString( "\n" ) );
	return true;
}
