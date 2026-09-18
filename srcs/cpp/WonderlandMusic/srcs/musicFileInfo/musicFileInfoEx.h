#ifndef MUSICFILEINFOEX_H_H_HEAD__FILE__
#define MUSICFILEINFOEX_H_H_HEAD__FILE__
#include <QString>

#include "../classTypeInfo/classTypeInfoVar.h"

class MusicFileInfoEx : public ClassTypeInfoVar {
public:
	enum class Music_Staus {
		None,
		Play,
		Stop,
	};

	enum class File_Status {
		None,
		Exist,
		Not_Exist,
		Open,
		Not_Open
	};

protected:
	Music_Staus musicStaus = Music_Staus::None;
	File_Status fileStatus = File_Status::None;
	QString filePath;

public:
	virtual Music_Staus getMusicStaus( ) const;
	virtual File_Status getFileStatus( ) const;
	virtual const QString & getFilePath( ) const;
	explicit MusicFileInfoEx( const QString &file_path );
};

#endif // MUSICFILEINFOEX_H_H_HEAD__FILE__
