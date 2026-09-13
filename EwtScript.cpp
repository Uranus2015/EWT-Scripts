#include<iostream>
#include<windows.h>
#include <conio.h>
//没人用，懒得给新功能和老功能优化了
bool endf(COLORREF endx,COLORREF endy,COLORREF endz);
int main()
{   
    int Classx=0;
    int Classy=0;
    bool unstop=1;
    while(unstop)
    {
        HDC Screen=GetDC(NULL);
        //int i=0;
        //std::cin>>i;
        std::cout<<"好的，请先把你的鼠标放在你要播放的第一个课程上面,然后按键盘读取鼠标坐标\n";
        POINT pt;
        system("pause");
        GetCursorPos(&pt);
        std::cout<<"("<<pt.x<<"\t"<<pt.y<<") \n";
        Classx=pt.x;
        Classy=pt.y;
        std::cout<<"这个是你在第一个课程上的鼠标坐标\n现在鼠标可以移走了\n";
        double screenx=double(GetSystemMetrics(SM_CXSCREEN)/1920);
        double screeny=double(GetSystemMetrics(SM_CYSCREEN)/1080);
        COLORREF Pause=GetPixel(Screen,692*screenx,641*screeny);//检测 认真度检测 按钮上的蓝色
        COLORREF End=GetPixel(Screen,480*screenx,575*screeny);//EWT植物人的喇叭上的深蓝色
        COLORREF End1=GetPixel(Screen,1606*screenx,749*screeny);//EWT植物人的帽子上的棕色
        COLORREF End2=GetPixel(Screen,828*screenx,518*screeny);//心理检测的灰色
        COLORREF class_=GetPixel(Screen,Classx,Classy);//课程蓝色
        while(class_==RGB(242,246,255)&&(Classy+84*screeny)<1034*screeny)
        {   
            Pause=GetPixel(Screen,692*screenx,641*screeny);//检测 认真度检测 按钮上的蓝色
            End=GetPixel(Screen,480*screenx,574*screeny);//EWT植物人的喇叭上的深蓝色
            End1=GetPixel(Screen,402*screenx,520*screeny);//EWT植物人的帽子上的棕色
            End2=GetPixel(Screen,828*screenx,518*screeny);//心理检测的灰色

            if(endf(End,End1,End2))
            {
                std::cout<<"本节课程已完成\n";
                SetCursorPos(Classx,Classy+84*screeny);
                mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
                Classy=Classy+84*screeny;
                Sleep(1024);
                class_=GetPixel(Screen,Classx,Classy);
            }
            else if(Pause==RGB(46,134,255)||Pause==RGB(0,102,255))
            {
                //移动鼠标
                SetCursorPos(692*screenx,641*screeny);
                mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);//点击
                std::cout<<"帮你点完了,喵呜~\\(= ^· w ·^)=";
            }
            Sleep(512);
        }
        std::cout<<"R: "<< (int)GetRValue(class_)
                <<" G: "<< (int)GetGValue(class_)
                <<" B: "<< (int)GetBValue(class_)
                <<"\n当颜色=242,246,255时判定还有课程未完成\n"
                <<(Classy+84*screeny)<<' '<<1034*screeny
                <<" 当前一个值大于后一个值时，判定本页课程已经完成\n";
         //两课程之间相差84px
        ReleaseDC(NULL,Screen);
        Beep(440,250);
        Beep(659,250);
        Beep(659,250);
        Beep(659,250);
        Beep(659,400);
        Beep(587,250);
        Beep(523,250);
        Beep(587,250);
        Beep(523,250);
        Beep(494,250);
        Beep(440,400);
        std::cout<<"此页课程已经播放完毕，请下滑鼠标或者更换下一天的课程\n";
        std::cout<<"按任意键退出程序，否则将在10秒后继续";
        for(int i=0;i<10;i++)
        {
            if(_kbhit())
            {
                unstop=0;
                break;
            }
            Sleep(1000);
        }
    }
    return 0;

}
bool endf(COLORREF endx,COLORREF endy,COLORREF endz)
{
    if(endx==RGB(75,126,251))
    {
        if(endy==RGB(170,143,108)||endz==RGB(67,68,70))
        return 1;
    }
    return 0;
}