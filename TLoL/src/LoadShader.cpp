#include "LoadShader.h"

LoadShader::LoadShader()
{
    //ctor
}

LoadShader::~LoadShader()
{
    //dtor
}
void LoadShader::loadFile(char* Filename, string& str)
{
    char tmp[1024];
    ifstream in(Filename);
    if(!in.is_open())
    {
        cout<<"file not open"<<endl;
        return;
    }
    while(!in.eof())
    {
        in.getline(tmp, 1024);
        str += tmp;
        str+='\n';
    }
    cout<< str << endl;
}

unsigned int LoadShader::loaderShader(string& source, unsigned int mode)
{
    unsigned int id;
    const char* csource;
    char error[1024];
    id = glCreateShader(mode);
    csource = source.c_str();
    glShaderSource(id,1,&csource,NULL);
    glCompileShader(id);
    glGetShaderInfoLog(id,1024,NULL,error);
    cout<<"compile Status \n"<<error<<endl;
    return id;
}

void LoadShader::initShader(char* Vfilename, char* Ffilename)
{
    string source;
    loadFile(Vfilename,source);
    vs = loaderShader(source,GL_VERTEX_SHADER);
    source = "";

    loadFile(Ffilename,source);
    fs = loaderShader(source,GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    //glUseProgram(program);
}

void LoadShader::cleanUp()
{
  glDetachShader(program,vs);
  glDetachShader(program,fs);
  glDeleteShader(vs);
  glDeleteShader(fs);
  glDeleteProgram(program);
}
