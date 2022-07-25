#include "FileSupport.h"

CS_Path::CS_Path(){
    nowpath = ".";
}

CS_Path& CS_Path::join(const string name){
    extern string CS_OperatingSystem;
    if(CS_OperatingSystem == string("Windows")){
        nowpath += "\\";
        nowpath += name;
    }
    else{
        nowpath += "/";
        nowpath += name;
    }
    return *this;
}

CS_Path::operator string(){
    return nowpath;
}

CS_File::CS_File(){
    file         = csNullPtr;
    fileMode     = csReadBinary;
    fileLength   = 0;
    buffer       = csNullPtr;
    bufferLength = 0;
}

void CS_File::ResizeAndClearBuffer(i32 size){
    if(size == 0){
        delete[] buffer;
        buffer = csNullPtr;
        return;
    }

    if(buffer != csNullPtr){
        delete[] buffer;
    }
    buffer = new ui8[size];
    CS_Memset(buffer, 0, size);
    bufferLength = size;
}

i32 CS_File::GetPositionNow(){
    return ftell(file);
}

void CS_File::GoToHead(){
    fseek(file, 0, SEEK_SET);
}

void CS_File::GoToEnd(){
    fseek(file, 0, SEEK_END);
}

void CS_File::GoTo(i32 position){
    fseek(file, position, SEEK_SET);
}

void CS_File::Open(string fileName_, csFileMode fileMode_){
    fileMode = fileMode_;
    file = fopen(fileName_.c_str(), fileMode == csReadBinary ? "rb" : "wb");

    if(file != csNullPtr){
        // Get the Length of the File
        GoToEnd();
        fileLength = GetPositionNow();
        GoToHead();
    }
    else{
        file         = csNullPtr;
        fileMode     = csReadBinary;
        fileLength   = 0;
    }

    buffer       = csNullPtr;
    bufferLength = 0;
}

void CS_File::Read(){
    ResizeAndClearBuffer(fileLength + 1);
    GoToHead();
    if(fileMode == csReadBinary && file != csNullPtr){
        fread(buffer, sizeof(ui8), fileLength, file);
    }
}

void CS_File::Write(){
    if(fileMode == csWriteBinary && file != csNullPtr){
        fwrite(buffer, sizeof(ui8), bufferLength, file);
    }
    fflush(file);
}

void CS_File::Close(){
    if(file != csNullPtr){
        fclose(file);
        file = csNullPtr;
    }
}

ui8 * CS_File::GetBufferPointer()
{
	return buffer;
}

CS_File::~CS_File(){
    Close();
}
