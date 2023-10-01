#ifndef __CSBF_FileSupport__
#define __CSBF_FileSupport__

#include "BasicDataTypeDeclarations.h"

typedef char csFileMode;
const csFileMode csReadBinary = 0;
const csFileMode csWriteBinary = 1;

class CS_Path{
private:
    string nowpath;
public:
    CS_Path();
    CS_Path& join(const string name);
    operator string();
};

class CS_File{

private:
    FILE *file;
    csFileMode fileMode;
    i32 fileLength;
    ui8 *buffer;
    i32 bufferLength;
    
private:
    void ResizeAndClearBuffer(i32 size);
    i32  GetPositionNow();
    void GoToHead();
    void GoToEnd();
    void GoTo(i32 position);

public:
	CS_File();
    void Open(string fileName_, csFileMode fileMode_);
    void Read();
    void Write();
    void Close();
	ui8* GetBufferPointer();
    ~CS_File();
};

#endif
