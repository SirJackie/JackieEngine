#ifndef __CSBF_FileSupport__
#define __CSBF_FileSupport__

#include "BasicDataTypeDeclarations.h"
#include "FrameBuffer.h"

typedef char csFileMode;
const csFileMode csReadBinary = 0;
const csFileMode csWriteBinary = 1;

class CS_Path{
public:
    string nowpath;
    CS_Path();
    CS_Path& join(const string name);
    operator string();
};

class CS_File{
public:
    FILE *file;
    csFileMode fileMode;
    i32 fileLength;
    ui8 *buffer;
    i32 bufferLength;

    CS_File();

    void ResizeAndClearBuffer(i32 size);
    i32  GetPositionNow();
    void GoToHead();
    void GoToEnd();
    void GoTo(i32 position);

    void Open(string fileName_, csFileMode fileMode_);
    void Read();
    void Write();
    void Close();

    ~CS_File();
};

#endif
