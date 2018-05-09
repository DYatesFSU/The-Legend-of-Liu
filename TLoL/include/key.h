#ifndef KEY_H
#define KEY_H

#include<GlobalDataStructures.h>
#include<textureLoader.h>

class textureLoader;

class key
{
    public:
        key();
        virtual ~key();
        cartesian3d vertices[4];


        textureLoader *objectTexture;

        void keyInit();

        void drawKey();


    protected:

    private:
};

#endif // KEY_H
