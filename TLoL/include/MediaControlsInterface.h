#ifndef MEDIACONTROLSINTERFACE_H
#define MEDIACONTROLSINTERFACE_H


class MediaControlsInterface
{
    public:
        virtual void play() = 0;
        virtual void playOnce() = 0;
        virtual void pause() = 0;
        virtual void restart() = 0;

    protected:

    private:
};

#endif // MEDIACONTROLSINTERFACE_H
