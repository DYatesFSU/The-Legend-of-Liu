#include "Inputs.h"
#include <player.h>
#include <Menu.h>

Inputs::Inputs()
{
    //ctor
   prev_Mouse_X =0;
   prev_Mouse_Y =0;
   Mouse_Translate=0;
   Mouse_Roatate=0;
}

Inputs::~Inputs()
{
    //dtor
}
/*
void Inputs::keyEnv(parallax* plx, float speed)
{
    switch(wParam)
    {
        case VK_LEFT:
            plx->Xmin -=speed;
            plx->Xmax -=speed;
            break;

        case VK_RIGHT:
            plx->Xmin +=speed;
            plx->Xmax +=speed;
            break;

         case VK_UP:
            plx->Ymin -=speed;
            plx->Ymax -=speed;
            break;

        case VK_DOWN:
            plx->Ymin +=speed;
            plx->Ymax +=speed;
            break;

    }
}*/

/*
void Inputs::keyPressed(Model* Mdl)
{
    switch(wParam)
    {
    case VK_LEFT:
        Mdl->RotateX +=1.0;
        break;

    case VK_RIGHT:
        Mdl->RotateX -=1.0;
        break;

    case VK_DOWN:
        Mdl->RotateY -=1.0;
        break;

    case VK_UP:
        Mdl->RotateY +=1.0;
        break;

    case VK_ADD:
        Mdl->Zoom +=1.0;
        break;

    case VK_SUBTRACT:
        Mdl->Zoom -=1.0;
        break;
    }
}
*/
void Inputs::keyPressed(player* ply)
{
    switch(wParam)
    {
     case 0x41: //A Key
       //ply->setxVel(-.005);
       //cout << "xPos: " << ply->getxPos() << ", yPos: " << ply->getyPos() << endl
       //<< "Moving: " << ply->getMoving();
       ply->movingLeft = true;
       ply->facingRight = false;
       //ply->actionTrigger = 1;
        break;

    case 0x44: //D Key
       //ply->setxVel(.005);
       ply->movingRight = true;
       ply->facingRight = true;
        //ply->actionTrigger = 1;
        break;

    case 0x53: //S Key
        //ply->setyVel(-.005);

        ply->movingDown = true;
         //ply->actionTrigger = 1;
        break;

    case 0x57: //W Key
        //ply->setyVel(.005);
        ply->movingUp = true;
         //ply->actionTrigger = 1;
        break;
    case 0x31:


    case VK_ADD:

        break;

    case VK_SUBTRACT:

        break;
    }
}


void Inputs::keyUp(player* ply)
{
  switch (wParam)
            {
        case 0x41:

       ply->setxVel(0);
       ply->movingLeft = false;

        break;
        case 0x44:
       ply->setxVel(0);
       ply->movingRight = false;

        break;
        case 0x57:

       ply->setyVel(0);
       ply->movingUp = false;

        break;
         case 0x53:

       ply->setyVel(0);
       ply->movingDown = false;

        break;
                default:
                break;
            }
}
void Inputs::keyPressed(Menu* menu)
{

     switch(wParam)
    {
    case 0x20:                       // Space to move forward from landing page
        if(menu->state==0)         // check if it's at landing page
        {
              menu->state=1;      // Set state to menu
        }
        break;
    case 0x4E:                   // N key
    if (menu->state==1)
    {
         menu->state=2;        // set state to new game
    }
        break;
    case 0x4F:                // O key

         if (menu->state==1)
    {
         menu->state=3;        // set state to options
    }
        break;

    case 0x48:               // H key
        if (menu->state==1)
        {
            menu->state=4;     // How to play state
        }
        break;

    case 0x50:               // P key
        if (menu->state==2)
        {
            menu->state=5;     // Set state to pause menu
        }
        break;

    case 0x42:                        // B key
        if (menu->state==4)          // if How to state state
        {
            menu->state =1;         // set to menu state
        }
        else if(menu->state==3)     //if Option state
        {
            menu->state =1;      // set to menu state
        }
        else if(menu->state==5)  // if pause state
        {
            menu->state =2;     // set back to game state
        }
        break;

    case 0x51:                    // Q key
        if (menu->state==2)      // if game state
        {
            menu->state =5;    // set it to qqpause menu
        }
        else if (menu->state==5)    // if pause menu
        {
        menu->state =1;      // set it to main menu
        }
        break;

    case 0x43:                  // C credits
        if (menu->state ==1)      // if it's in main menu
        {
            menu->state =0;     // set back to land page for credits
        }
        break;
    }
}



/*
void Inputs::mouseEventDown(Model *Model, double x,double y)
{
        prev_Mouse_X =x;
        prev_Mouse_Y =y;

   switch (wParam)
            {
                case MK_LBUTTON:
                        Mouse_Roatate = true;
                    break;

                case MK_RBUTTON:
                     Mouse_Translate =true;
                    break;
                case MK_MBUTTON:

                    break;

                default:
                    break;
            }
}

 void Inputs::mouseEventUp()
 {
    Mouse_Translate =false;
    Mouse_Roatate =false;
 }

void Inputs::mouseWheel(Model *Model,double Delta)
{
    Model->Zoom += Delta/100;
}

void Inputs::mouseMove(Model *Model,double x,double y)
{
      if(Mouse_Translate)
      {
       Model->Xpos += (x-prev_Mouse_X)/100;
       Model->Ypos -= (y-prev_Mouse_Y)/100;

       prev_Mouse_X =x;
       prev_Mouse_Y =y;
      }

      if(Mouse_Roatate)
      {
        Model->RotateY += (x-prev_Mouse_X)/3;
        Model->RotateX += (y-prev_Mouse_Y)/3;

        prev_Mouse_X =x;
        prev_Mouse_Y =y;
      }
}
void Inputs::keyPressed(skyBox* sky)
{
    switch(wParam)
    {
     case VK_LEFT:
       sky->RotateY += 0.5;
        break;

    case VK_RIGHT:
       sky->RotateY -= 0.5;
        break;

    case VK_DOWN:
         sky->RotateX += 0.5;
        break;

    case VK_UP:
         sky->RotateX -= 0.5;
        break;
    }
}

void Inputs::mouseMove(skyBox* sky, double x, double y)
{

        sky->RotateY += (x-prev_Mouse_X)/3;
        sky->RotateX += (y-prev_Mouse_Y)/3;

        prev_Mouse_X =x;
        prev_Mouse_Y =y;

}
*/
