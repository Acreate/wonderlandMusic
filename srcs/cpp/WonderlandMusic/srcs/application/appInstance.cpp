#include "appInstance.h"

#include <QPainter>

#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>
#include <component/musicWindow/musicWindow.h>
#include <component/optionWindow/optionWindow.h>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/init_macro.h>
#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <systemTrayIcon/systemTrayIcon.h>

#include <widget/aboutWidget.h>
#include <widget/settingWidget.h>

#include <window/mainWindow.h>

#include <playerImpement/widget/playerInfoListWidget.h>

#include "../classTypeInfo/classTypeInfo.h"
#include "../classTypeInfo/classTypeInfoStack.h"

#include "../component/playWindow/playWindow.h"

#include "../mutex/userMutex.h"

#include "appInstance/appDataManage.h"
#include "appInstance/appDataManage/appMusicManage.h"
#include "appInstance/appDateTimerManage.h"
#include "appInstance/applicationManage.h"
#include "appInstance/appUserInterfaceManage.h"

AppInstance *AppInstanceTool::appInstance = nullptr;
bool AppInstanceTool::deleteAppInstance( AppInstance *&app_instance ) {
	if( app_instance != appInstance )
		return false;
	delete appInstance;
	app_instance = appInstance = nullptr;
	return true;
}
AppInstance * AppInstanceTool::createAppInstance( int &argc, char **argv, int app_flag_s ) {
	if( appInstance != nullptr )
		return appInstance;
	appInstance = new AppInstance( argc, argv, app_flag_s );
	return appInstance;
}

AppInstance::~AppInstance( ) {
	deleteResource( );
	delete classTypeInfoStack;
	instance = nullptr;
}
AppInstance *AppInstance::instance = nullptr;

AppInstance::AppParam::~AppParam( ) {
}

AppInstance::AppParam::AppParam( int argc, char **argv, int app_flag_s ) : argc( argc ), argv( argv ), app_flag_s( app_flag_s ) {
}

int AppInstance::AppParam::getArgc( ) const {
	return argc;
}

char ** AppInstance::AppParam::getArgv( ) const {
	return argv;
}

int AppInstance::AppParam::getAppFlagS( ) const {
	return app_flag_s;
}

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : appParam( argc, argv, app_flag_s ) {
	instance = this;
	classTypeInfoStack = new ClassTypeInfoStack;
	regClassTypeInfoRef( this );
}

bool AppInstance::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appDateTimerManage );
	Delete_Resource_App_Core_Ptr( applicationManage );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}

AppDataManage * AppInstance::getAppDataManage( ) const {
	return appDataManage;
}

AppUserInterfaceManage * AppInstance::getAppUserInterfaceManage( ) const {
	return appUserInterfaceManage;
}

AppDateTimerManage * AppInstance::getAppDateTimerManage( ) const {
	return appDateTimerManage;
}

ApplicationManage * AppInstance::getApplicationManage( ) const {
	return applicationManage;
}
const IClassTypeInfo * AppInstance::appendClassTypeInfoVar( const ClassTypeInfoVar *class_type_info_var, void *ptr, const std::type_info &class_type_info, const char *class_type_name ) {
	return setClassTypeInfo( class_type_info_var, ptr, class_type_info, class_type_name, classTypeInfoStack );
}
const IClassTypeInfo * AppInstance::findClassTypeInfo( const void *ptr ) const {
	return getClassTypeInfo( ptr, classTypeInfoStack );
}
bool AppInstance::removeClassTypeInfoVar( const void *ptr ) {
	return deleteClassTypeInfo( ptr, classTypeInfoStack );
}
bool AppInstance::init( ) {
	Init_Resource_App_Core_Ptr( applicationManage );
	Init_Resource_App_Core_Ptr( appDateTimerManage );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );

	return true;
}

bool AppInstance::initBefore( ) {
	deleteResource( );
	instance = this;
	userMutex = new UserMutex;
	applicationManage = new ApplicationManage( appParam.argc, appParam.argv, appParam.app_flag_s );
	appDateTimerManage = new AppDateTimerManage;
	appDataManage = new AppDataManage;
	appUserInterfaceManage = new AppUserInterfaceManage;
	Before_Init_Resource_App_Core_Ptr( applicationManage );
	Before_Init_Resource_App_Core_Ptr( appDateTimerManage );
	Before_Init_Resource_App_Core_Ptr( appDataManage );
	Before_Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	return true;
}

bool AppInstance::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( applicationManage );
	After_Init_Resource_App_Core_Ptr( appDateTimerManage );
	After_Init_Resource_App_Core_Ptr( appDataManage );
	After_Init_Resource_App_Core_Ptr( appUserInterfaceManage );

	auto musicCentreWidget = appUserInterfaceManage->getMusicCentreWidget( );

	auto appMusicManage = appDataManage->getAppMusicManage( );
	if( musicCentreWidget->setMusicDataManage( appMusicManage ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicCentreWidget, setMusicDataManage, QObject::tr( "设置音频信息管理组件失败" ) );
	auto musicFavoriteWidget = appUserInterfaceManage->getMusicFavoriteWidget( );
	if( musicCentreWidget->setMusicFavoriteWidget( musicFavoriteWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicCentreWidget, setMusicFavoriteWidget, QObject::tr( "设置音频收藏夹面板组件失败" ) );
	auto musicListWidget = appUserInterfaceManage->getMusicListWidget( );
	if( musicCentreWidget->setMusicListWidget( musicListWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicCentreWidget, setMusicListWidget, QObject::tr( "设置音频信息列表面板组件失败" ) );
	auto musicTitleWidget = appUserInterfaceManage->getMusicTitleWidget( );
	if( musicCentreWidget->setMusicTitleWidget( musicTitleWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicCentreWidget, setMusicTitleWidget, QObject::tr( "设置音频标题面板组件失败" ) );

	IMusicFavoriteItem *musicFavoriteItem = nullptr;
	if( appMusicManage->getMusicFavoriteItem( musicFavoriteItem ) == false || musicFavoriteItem == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appMusicManage, getMusicFavoriteItem, QObject::tr( "无法获取默认收藏项" ) );
	if( musicCentreWidget->setCurrentMusicFavoriteItem( musicFavoriteItem ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicCentreWidget, setCurrentMusicFavoriteItem, QObject::tr( "配置默认收藏项异常" ) );

	auto musicWindow = appUserInterfaceManage->getMusicWindow( );
	if( musicWindow->setMusicCentreWidget( musicCentreWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicWindow, setMusicCentreWidget, QObject::tr( "设置音频主要组件配置初始化失败" ) );
	auto optionWindow = appUserInterfaceManage->getPlayerInfoListWidget( );

	if( optionWindow->addOptionPanel( musicWindow ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, addOptionPanel, QObject::tr( "添加音乐播放面板失败" ) );

	auto settingWidget = appUserInterfaceManage->getSettingWidget( );
	if( optionWindow->addOptionPanel( settingWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, addOptionPanel, QObject::tr( "添加设置面板失败" ) );

	auto aboutWidget = appUserInterfaceManage->getAboutWidget( );
	if( optionWindow->addOptionPanel( aboutWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, addOptionPanel, QObject::tr( "添加关于面板失败" ) );

	if( optionWindow->showOptionPanel( musicWindow ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, showOptionPanel, QObject::tr( "显示音乐播放面板失败" ) );

	auto playerWindowCentreWidget = appUserInterfaceManage->getPlayerWindowCentreWidget( );
	if( playerWindowCentreWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appUserInterfaceManage, getPlayerWindowCentreWidget, QObject::tr("获取播放窗口中心组件失败") );
	if( playerWindowCentreWidget->setPlayerInfoListWidget( optionWindow ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, playerWindowCentreWidget, setPlayerInfoListWidget, QObject::tr("配置播放列表组件失败") );
	auto playerControlWidget = appUserInterfaceManage->getPlayerControlWidget( );
	if( playerControlWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appUserInterfaceManage, getPlayerControlWidget, QObject::tr("获取播放窗口控制组件失败") );
	if( playerWindowCentreWidget->setPlayerControlWidget( playerControlWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, playerWindowCentreWidget, setPlayerControlWidget, QObject::tr("配置播放控制组件失败") );
	auto playerWindow = appUserInterfaceManage->getPlayWindow( );
	if( playerWindow == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appUserInterfaceManage, getPlayWindow, QObject::tr("获取播放窗口失败") );
	if( playerWindow->setPlayerWindowCentreWidget( playerWindowCentreWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, playerWindow, setPlayerInfoListWidget, QObject::tr("配置播放中心组件失败") );

	auto mainWindow = appUserInterfaceManage->getMainWindow( );
	mainWindow->setCentralWidget( playerWindow );
	if( musicWindow->repaintMusicCentreWidget( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicWindow, repaintMusicCentreWidget, QObject::tr( "刷新音频组件失败" ) );
	if( musicWindow->synchronizationChildrenWidgetSize( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicWindow, synchronizationChildrenWidgetSize, QObject::tr( "调整音频组件失败" ) );
	return true;
}

int AppInstance::exec( ) {
	int exec = -1;
	if( appDataManage->readJsonData( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( exec, appDataManage, readJsonData, QObject::tr( "json 读取异常" ) );
	auto systemTrayIcon = appUserInterfaceManage->getSystemTrayIcon( );
	exec = -2;
	if( systemTrayIcon == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( exec, appUserInterfaceManage, getSystemTrayIcon, QObject::tr( "无法获取右下角功能菜单" ) );
	systemTrayIcon->show( );
	exec = -2;
	if( appUserInterfaceManage->showMainWindow( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( exec, appUserInterfaceManage, showMainWindow, QObject::tr( "主窗口显示异常" ) );
	exec = applicationManage->exec( );
	if( appDataManage->writeJsonData( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( exec, appDataManage, writeJsonData, QObject::tr( "json 写入异常" ) );
	return exec;
}
int AppInstance::quit( ) {
	applicationManage->quit( );
	return 0;
}
