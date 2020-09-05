
#include<SFML/Graphics.hpp>
#include<time.h>
#include<SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf ;

int blockIndex;
int blocks[7][4] = {
	{1,3,5,7},//I型
	{2,4,5,7},//Z型 1型
    {3,5,4,6},//Z型 2型
	{3,5,4,7},//T
	{2,3,5,7},//L
	{3,5,7,6},//J
	{2,3,4,5} //田
};
const int ROW_COUNT = 20;
const int COL_COUNT = 10;
int upBlock[4][2] = { 0 };
int table[ROW_COUNT][COL_COUNT] = {0};
struct Point{
	int x;
	int y;
}curBlock[4];


void keyEvent() {



}
void newblock() {
	
	 blockIndex= 1+rand ()% 7;
	 int n = blockIndex - 1;
	 for (int i= 0; i < 4; i++) {

		 curBlock[i].x = blocks[n][i] % 2;
		 curBlock[i].y = blocks[n][i] / 2;
	 }

}
void drawBlocks(Sprite *spriteBlock,RenderWindow *window) {
	//先画 已经降落到底部的方块
	for (int i = 0; i < ROW_COUNT;i++) {
		for (int j = 0; j < COL_COUNT; j++) {
			if (table[i][j]) {
			 //画小方块
				spriteBlock->setTextureRect(IntRect(table[i][j]*18,0,18,18));
				spriteBlock->setPosition(j * 18, i * 18);
				spriteBlock->move(28, 31);
				window->draw(*spriteBlock);
			}
		
		}
	}
	for (int i = 0; i < 4; i++) {

		spriteBlock->setTextureRect(IntRect(blockIndex * 18, 0, 18, 18));
		spriteBlock->setPosition(curBlock[i].x * 18, curBlock[i].y * 18);
	}




}
int main(){
	srand(time(NULL));
	RenderWindow window(

		VideoMode(320, 416),//窗口模式大小
		"rofei-2020"       //窗口标题
     );
	//加载背景图片
	Texture t1; //把图片文件加载到内存
	t1.loadFromFile("shaomo.jpg");
	Sprite spriteBg(t1);//根据图片来创建精灵

	Texture t2;
	t2.loadFromFile("tiles.jpg");
	Sprite spriteBlock(t2);
	
	//让窗口渲染这个精灵
	window.draw(spriteBg);
	window.display();//刷新并显示窗口
	
	//产生第一个方块
	newblock();

	while(window.isOpen()){
	
	    //等待用户按键按下，并处理
		keyEvent();

		//把方块画出来
		drawBlocks(&spriteBlock, &window);
	
	
	
	
	}

	system("pause");

	return 0;
}

