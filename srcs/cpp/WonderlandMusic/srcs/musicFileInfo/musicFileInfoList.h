#ifndef MUSICINFOLIST_H_H_HEAD__FILE__
#define MUSICINFOLIST_H_H_HEAD__FILE__
#include <QThread>

class UserMutex;
class MusicFileInfo;

class MusicFileInfoList : public QObject {
	Q_OBJECT;

public:
	enum class Status {
		None,
		Start,
		Run,
		Finish,
		Interrupt,
		Error
	};

	Q_ENUM( Status );

private:
	std::vector< MusicFileInfo * > overLoadMusicVector;
	std::vector< MusicFileInfo * > musicVector;
	MusicFileInfo *current = nullptr;
	UserMutex *userMutex;
	size_t count;
	size_t index;
	MusicFileInfo * *musicVectorDataPtr;
	Status status;
	bool interruption;

protected:
	virtual void overWork( );

public:
	MusicFileInfoList( const std::vector< QString > &file_list );
	MusicFileInfoList( );
	~MusicFileInfoList( ) override;
	virtual bool appendLoadMusicFileList( const std::vector< QString > &file_list );
	virtual bool getOverLoadMusicVector( std::vector< MusicFileInfo * > &result_over_load_music_info_vector ) const;
	virtual QStringList toQStringList( ) const;
	virtual operator QString( ) const;
	virtual size_t getCount( ) const;
	virtual bool moveToMusicInfoVector( std::vector< MusicFileInfo * > &result_detach_vector );
	virtual bool requestInterruption( );
	virtual bool isFinished( ) const;
	virtual bool isRunning( ) const;
	virtual bool isInterruptionRequested( ) const;
	virtual bool start( );
	virtual Status getStatus( ) const;
Q_SIGNALS:
	void signal_finish( MusicFileInfoList *music_file_info_list );
	void signal_start( MusicFileInfoList *music_file_info_list );
};

#endif // MUSICINFOLIST_H_H_HEAD__FILE__
