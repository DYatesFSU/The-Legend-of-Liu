#ifndef LOADSHADER_H
#define LOADSHADER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

class LoadShader
{
    public:
        LoadShader();
        virtual ~LoadShader();

        void loadFile(char *, string&);


        unsigned int vs,fs,program;
        unsigned int loaderShader(string&, unsigned int mode);
        void initShader(char *,char *);
        void cleanUp();


    protected:

    private:
};

#endif // LOADSHADER_H
