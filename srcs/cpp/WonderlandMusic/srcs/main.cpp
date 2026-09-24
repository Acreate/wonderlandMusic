#include "initMain.h"

#include "head/result_message_out.h"

int main( int argc, char *argv[ ], char *envp[ ] ) {
	int runMainCode = -1;
	InitMain *initMain = new InitMain( argc, argv, envp );
	do {
		if( initMain->initBefore( ) == false ) {
			Result_Var_Function_Messag_Ptr_Out_Args( initMain->getExecCode( ), initMain, initBefore, QObject::tr( "生成工作环境异常" ) );
			break;
		}
		if( initMain->init( ) == false ) {
			Result_Var_Function_Messag_Ptr_Out_Args( initMain->getExecCode( ), initMain, init, QObject::tr( "初始化工作环境异常" ) );
			break;
		}
		if( initMain->initAfter( ) == false ) {
			Result_Var_Function_Messag_Ptr_Out_Args( initMain->getExecCode( ), initMain, initAfter, QObject::tr( "准备工作环境异常" ) );
			break;
		}
		runMainCode = initMain->runMain( );
	} while( false );

	delete initMain;
	return runMainCode;
}
