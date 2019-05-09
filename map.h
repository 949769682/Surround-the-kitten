#ifndef MAP_H
#define MAP_H


#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define random() ((rand() % (11-0))+ 0)

class Create_map
{
public:
    int _map[11][11];
    int x;
    int y;
    Create_map();
    ~Create_map(){cout<< "xi gou han shu "<< endl;}
    void Showmap();
    int Thinking();
    int* min(int *a,int *b);
    void obstacle();
};
Create_map::Create_map()
{
    for(x=0;x<11;x++)
    {
        for(y=0;y<11;y++)
        {
            int _x = x<(10-x)? x:(10-x);
            int _y = y<(10-y)? y:(10-y);
            _x < _y? (_map[x][y] = _x):(_map[x][y] = _y);
        }
    }
    obstacle();
    x = 5;
    y = 5;
    cout<< "gou zao han shu "<< endl;

}

void Create_map::Showmap()
{
    for(x=0;x<11;x++)
    {
        for(y=0;y<11;y++)
        {
            cout<< &_map[x][y]<< " ";
        }
        cout<< endl;
    }

}
int* Create_map::min(int *a,int *b)
{
    return *a<*b? a:b;
}
int Create_map::Thinking()
{


    if(_map[x][y]!=0)
    {
        int *address;
        if(x%2==0)
        {
            address = min(min(min(&_map[x-1][y-1],&_map[x+1][y]),&_map[x-1][y]),min(min(&_map[x+1][y-1],&_map[x][y-1]),&_map[x][y+1]));

        }
        else
        {
            address = min(min(min(&_map[x-1][y],&_map[x+1][y+1]),&_map[x-1][y+1]),min(min(&_map[x+1][y],&_map[x][y-1]),&_map[x][y+1]));

        }
        if(*address == 100)
        {
            return 0;
        }
        else
        {
            x = (address - &_map[0][0])/11;   //猫应该移动的位置
            y = (address - &_map[0][0])%11;
            return 1;
        }


    }
    else
    {
        //位于边界时
        return 2;
    }
}


void Create_map::obstacle()
{
    srand((unsigned int)time(NULL));
    for(int i=0;i<6;i++)
    {
        int _x,_y;
        while(1)
        {
            _x = random();
            _y = random();
            if((!(x==5&&y==5)) && _map[_x][_y]!=100)
                break;
        }
        _map[_x][_y] = 100;
    }

}


#endif // MAP_H
