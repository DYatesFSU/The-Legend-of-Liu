#ifndef MEDIACONTROLSINTERFACE_H
#define MEDIACONTROLSINTERFACE_H


class MediaControlsInterface
{
    public:
        virtual void play() = 0;
        void playOnce();
        void pause();
        void restart();
        void setSourceFile(std::string);

    protected:

    private:
};

#endif // MEDIACONTROLSINTERFACE_H
