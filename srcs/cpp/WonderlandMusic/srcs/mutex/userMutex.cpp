#include "userMutex.h"
#include <mutex>
#include <source_location>

#include "../application/appInstance/appDataManage/translate/messageTranslate.h"
#include "../application/appInstance/appDataManage/translate/userMutexTranslate.h"

#include "../head/result_message_out.h"

#include "../msgInfo/messageErrorOut.h"
#include "../msgInfo/messageString.h"

#include "../tools/sourceLocationTools.h"

void UserMutex::out_debug_info( ) const {
	QString source_file;
	QString source_function;
	QString source_line;

	if( AppTranslateTools::getMessage( [&] ( MessageTranslate &translate ) {
		source_file = translate.getSourceFile( );
		source_function = translate.getSourceFunction( );
		source_line = translate.getSourceLine( );
		return true;
	} ) == false ) {
		source_file = QObject::tr( "源文件" );
		source_function = QObject::tr( "源函数" );
		source_line = QObject::tr( "源行号" );
	}

	QString trylockError;
	QString lastTrylock;
	QString lastLock;
	QString lastUnlock;
	if( AppTranslateTools::getUserMutex( [&] ( UserMutexTranslate &translate ) {
		trylockError = translate.getTrylockError( );
		lastTrylock = translate.getLastTrylock( );
		lastLock = translate.getLastLock( );
		lastUnlock = translate.getLastUnlock( );
		return true;
	} ) == false ) {
		trylockError = QObject::tr( "锁异常" );
		lastTrylock = QObject::tr( "最后一次尝试锁" );
		lastUnlock = QObject::tr( "最后一次解锁" );
		lastLock = QObject::tr( "最后一次锁" );
	}

	MessageString messageString;

	messageString << trylockError << " || " << "\n\t" << lastTrylock << "\t->";
	QString file;
	QString line;
	QString fun;
	SourceLocationTools::formatSourceFilePath( file, fun, line, *trylockSourceLocation );
	if( file.isEmpty( ) == false )
		messageString << "\n\t\t" << source_file << " : " << file;
	if( fun.isEmpty( ) == false )
		messageString << "\n\t\t" << source_function << " : " << fun;
	if( line.isEmpty( ) == false )
		messageString << "\n\t\t" << source_line << " : " << line;
	messageString << "\n\t" << lastLock << "\t->";
	SourceLocationTools::formatSourceFilePath( file, fun, line, *lockSourceLocation );

	if( file.isEmpty( ) == false )
		messageString << "\n\t\t" << source_file << " : " << file;
	if( fun.isEmpty( ) == false )
		messageString << "\n\t\t" << source_function << " : " << fun;
	if( line.isEmpty( ) == false )
		messageString << "\n\t\t" << source_line << " : " << line;
	messageString << "\n\t" << lastUnlock << "\t->";
	SourceLocationTools::formatSourceFilePath( file, fun, line, *unlockSourceLocation );

	if( file.isEmpty( ) == false )
		messageString << "\n\t\t" << source_file << " : " << file;
	if( fun.isEmpty( ) == false )
		messageString << "\n\t\t" << source_function << " : " << fun;
	if( line.isEmpty( ) == false )
		messageString << "\n\t\t" << source_line << " : " << line;
	Message_Error_Out << messageString;
}

UserMutex::UserMutex( ) {
	mutexCorPtr = new std::mutex;
	trylockSourceLocation = new std::source_location;
	lockSourceLocation = new std::source_location;
	unlockSourceLocation = new std::source_location;
}

bool UserMutex::tryLock( const std::source_location &source_location ) const {
	return tryLock( mutexCorPtr, source_location );
}

bool UserMutex::lock( const std::source_location &source_location ) const {
	return lock( mutexCorPtr, source_location );
}

bool UserMutex::unlock( const std::source_location &source_location ) const {
	return unlock( mutexCorPtr, source_location );
}

UserMutex::LockGuard UserMutex::getLockGuard( ) const {
	return getLockGuard( mutexCorPtr );
}

UserMutex::~UserMutex( ) {
	decltype(mutexCorPtr) ptr = mutexCorPtr;
	mutexCorPtr = nullptr;
	if( tryLock( ptr ) == false )
		unlock( ptr );
	delete ptr;
	delete trylockSourceLocation;
	delete lockSourceLocation;
	delete unlockSourceLocation;
}

bool UserMutex::tryLock( std::mutex *mutex_cor_ptr, const std::source_location &source_location ) const {
	if( mutex_cor_ptr == nullptr )
		return false;
	bool tryLock;
	try {
		tryLock = mutex_cor_ptr->try_lock( );
	} catch( ... ) {
		out_debug_info( );
		//tryLock = false;
		_STD _Throw_Cpp_error( std::_RESOURCE_DEADLOCK_WOULD_OCCUR );
	}
	*trylockSourceLocation = source_location;
	return tryLock;
}

bool UserMutex::lock( std::mutex *mutex_cor_ptr, const std::source_location &source_location ) const {
	if( mutex_cor_ptr == nullptr )
		return false;

	bool tryLock;
	try {
		mutex_cor_ptr->lock( );
		tryLock = true;
	} catch( ... ) {
		out_debug_info( );
		//tryLock = false;
		_STD _Throw_Cpp_error( std::_RESOURCE_DEADLOCK_WOULD_OCCUR );
	}
	*lockSourceLocation = source_location;
	return tryLock;
}

bool UserMutex::unlock( std::mutex *mutex_cor_ptr, const std::source_location &source_location ) const {
	if( mutex_cor_ptr == nullptr )
		return false;
	bool tryLock;
	try {
		if( mutex_cor_ptr->try_lock( ) ) {
			out_debug_info( );
			//tryLock = false;
			_STD _Throw_Cpp_error( std::_RESOURCE_DEADLOCK_WOULD_OCCUR );
		}
		mutex_cor_ptr->unlock( );
		tryLock = true;
	} catch( ... ) {
		out_debug_info( );
		//tryLock = false;
		_STD _Throw_Cpp_error( std::_RESOURCE_DEADLOCK_WOULD_OCCUR );
	}
	*unlockSourceLocation = source_location;
	return tryLock;
}

UserMutex::LockGuard UserMutex::getLockGuard( std::mutex *mutex_cor_ptr ) const {
	LockGuard lockGuard( new std::lock_guard< std::mutex >( *mutex_cor_ptr ) );
	return lockGuard;
}
