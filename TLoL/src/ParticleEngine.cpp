#include "ParticleEngine.h"

ParticleEngine::ParticleEngine()
{
    //ctor
}

ParticleEngine::~ParticleEngine()
{
    //dtor
}


double drand48(){
    return (rand()%1000)/1000.0;
}

void ParticleEngine::generateParticle()
{
    int i=0, newDrops = drand48()*60;
    if(NumDrops + newDrops > MAX_DROPS ){
        newDrops = MAX_DROPS - NumDrops;
    }
    for(i = NumDrops;i<NumDrops + newDrops; i++){
        drops[i].alive = true;
        drops[i].xpos = -14.5 + 0.2*drand48();
        drops[i].ypos = 25.8 + 0.2*drand48();
        drops[i].xdir = 0.0075 + 0.025*drand48();
        drops[i].ydir = 0.0;
        drops[i].mass = 0.05 + 0.2 * drand48();
    }
    NumDrops += newDrops;

}

void ParticleEngine::lifeTime()
{
    int i;
    for(i = 0; i<NumDrops;i++){
        if(drops[i].alive){
            if(drops[i].ypos + GRAVITY * drops[i].mass< 0.0){
                drops[i].ydir = -drops[i].ydir;
            }else{
                drops[i].ydir += GRAVITY * drops[i].xdir;
            }
            drops[i].xpos += drops[i].xdir;
            drops[i].ypos += drops[i].ydir;
            if(drops[i].ypos < -5.0 && drops[i].xpos > 5.0){
                drops[i].alive = false;
            }
        }
    }
}

void ParticleEngine::drawParticle()
{
    glPointSize(2);
//    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POINTS);
        for(int i=0;i<NumDrops;i++){
            if(drops[i].alive){
                glVertex3f(drops[i].xpos,drops[i].ypos,-5.0);
            }
        }
    glEnd();
}
