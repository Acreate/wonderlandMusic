#ifndef APPINSTANCE_H_H_HEAD__FILE__
#define APPINSTANCE_H_H_HEAD__FILE__

#include <QApplication>

#include "../classTypeInfo/classTypeInfoVar.h"

#include "../interface/iAppResourceCore.h"

class ClassTypeInfoStack;
class IClassTypeInfoStack;
class IClassTypeInfo;
class ClassTypeInfoVarStack;
class UserMutex;
class ApplicationManage;
class AppDateTimerManage;
class AppUserInterfaceManage;
class AppDataManage;

class AppInstance : public IAppResourceCore, public ClassTypeInfoVar {
	friend class AppInstanceTool;

private:
	static AppInstance *instance;

protected:
	class AppParam {
		friend class AppInstance;
		friend class ApplicationManage;
		int argc;
		char **argv;
		int app_flag_s;

	public:
		virtual ~AppParam( );

		AppParam( int argc, char **argv, int app_flag_s );

		virtual int getArgc( ) const;

		virtual char ** getArgv( ) const;

		virtual int getAppFlagS( ) const;
	};

	/// @brief 锁
	UserMutex *userMutex = nullptr;
	/// @brief app 运行参数
	AppParam appParam;
	/// @brief 应用循环
	ApplicationManage *applicationManage = nullptr;
	/// @brief 数据管理
	AppDataManage *appDataManage = nullptr;
	/// @brief 用户界面
	AppUserInterfaceManage *appUserInterfaceManage = nullptr;
	/// @brief 时间管理
	AppDateTimerManage *appDateTimerManage = nullptr;
	/// @brief 类接口信息
	ClassTypeInfoStack *classTypeInfoStack = nullptr;

protected:
	AppInstance( int &argc, char **argv, int app_flag_s = QCoreApplication::ApplicationFlags );

	~AppInstance( ) override;

public:
	static AppInstance * getAppInstance( );

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
	virtual int exec( );
	virtual int quit( );

protected:
	bool deleteResource( );

public:
	virtual AppDataManage * getAppDataManage( ) const;

	virtual AppUserInterfaceManage * getAppUserInterfaceManage( ) const;

	virtual AppDateTimerManage * getAppDateTimerManage( ) const;

	virtual ApplicationManage * getApplicationManage( ) const;
	virtual const IClassTypeInfo * appendClassTypeInfoVar( const ClassTypeInfoVar *class_type_info_var, void *ptr, const std::type_info &class_type_info, const char *class_type_name );
	virtual const IClassTypeInfo * findClassTypeInfo( const void *ptr ) const;
	virtual bool removeClassTypeInfoVar( const void *ptr );
};

class AppInstanceTool {
	friend class InitMain;
	static AppInstance *appInstance;
	static bool deleteAppInstance( AppInstance *&app_instance );
	static AppInstance * createAppInstance( int &argc, char **argv, int app_flag_s = QCoreApplication::ApplicationFlags );
};
#endif // APPINSTANCE_H_H_HEAD__FILE__
