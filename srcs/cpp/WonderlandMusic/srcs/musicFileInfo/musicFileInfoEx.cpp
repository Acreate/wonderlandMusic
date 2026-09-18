#include "musicFileInfoEx.h"

#include <QFileInfo>
MusicFileInfoEx::Music_Staus MusicFileInfoEx::getMusicStaus( ) const {
	return musicStaus;
}
MusicFileInfoEx::File_Status MusicFileInfoEx::getFileStatus( ) const {
	return fileStatus;
}
const QString & MusicFileInfoEx::getFilePath( ) const {
	return filePath;
}
MusicFileInfoEx::MusicFileInfoEx( const QString &file_path ) {
	QFileInfo fileInfo( filePath );
	this->filePath = fileInfo.absoluteFilePath( );
	if( fileInfo.exists( ) == false ) {
		this->fileStatus = File_Status::Not_Exist;
		return;
	}
	this->fileStatus = File_Status::Exist;
}
