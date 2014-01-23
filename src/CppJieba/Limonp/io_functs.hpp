/************************************
 * file enc : utf8
 * author   : wuyanyi09@gmail.com
************************************/
#ifndef LIMONP_IO_FUNCTS_H
#define LIMONP_IO_FUNCTS_H
#include <fstream>
#include <iostream>
#include <stdlib.h>
namespace Limonp
{
    using namespace std;
    inline bool loadFile2Str(const char * const filepath, string& res)
    {
        ifstream in(filepath);
        if(!in)
        {
            return false;
        }
        istreambuf_iterator<char> beg(in), end;
        res.assign(beg, end);
        in.close();
        return true;
    }
    
    inline void loadStr2File(const char * const filename, ios_base::openmode mode, const string& str)
    {
        ofstream out(filename, mode);
        ostreambuf_iterator<char> itr (out);
        copy(str.begin(), str.end(), itr);
        out.close();
    }

    inline int ReadFromFile(const char * fileName, char* buf, int maxCount, const char* mode)
    {                                        
        FILE* fp = fopen(fileName, mode);    
        if (!fp)                             
          return 0;                          
        int ret;                             
        fgets(buf, maxCount, fp) ? ret = 1 : ret = 0;                                       
        fclose(fp);                          
        return ret;                          
    }                                        

    inline int WriteStr2File(const char* fileName, const char* buf, const char* mode)
    {                                          
        FILE* fp = fopen(fileName, mode);      
        if (!fp)                               
          return 0;                            
        int n = fprintf(fp, "%s", buf);        
        fclose(fp);                            
        return n;                              
    }                                          

    inline bool checkFileExist(const string& filePath)
    {
        fstream _file;
        _file.open(filePath.c_str(), ios::in);
        if(_file)
          return true;
        return false;
    }

    inline bool createDir(const string& dirPath, bool p = true)
    {
        string dir_str(dirPath);
        string cmd = "mkdir";
        if(p)
        {
            cmd += " -p";
        }
        cmd += " " + dir_str; 
        int res = system(cmd.c_str());
        return res;
    }

    inline bool checkDirExist(const string& dirPath)
    {
        return checkFileExist(dirPath);
    }
}
#endif
