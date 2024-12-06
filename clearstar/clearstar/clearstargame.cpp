//9月11号，消灭星星项目启动

#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <easyx.h>
#include <windows.h>

const int length = 10;
const int width = 10;
const int floor_length = 40;
const int small_floor = 3;//方块UI优化
long Real_score = 0;
int  floor_Tick = 0;
ExMessage startmessage;
ExMessage message_get;
#define nofloor 0
#define normal  1
#define ticked  2
#define record  3

#define UP    100
#define DOWN  200
#define LEFT  300
#define RIGHT 400
typedef struct star_message {//统一坐标指的是数组所存储的
	int star_x;
	int star_y;
	COLORREF color;
	int state;
}stars;
stars teststar{ 0,0, BLACK , 0};
int Level = 1;
long Target = 0;
int Levelscore(int level ,int power) {
	if (level == 1) {
		Target += 1000;
	}
	else if (level == 2) {
		Target += 2000;
	}
	else if (level == 3) {
		Target += 3000;
	}
	else {
		int add_score = (rand() % 3 + 1)*1000;
		Target += add_score;
	}
	return Target;
}
//long Target[] = { }
stars floor[width][length];//是从下往上数,y=0在下方
void testtext(int x, int y, TCHAR text[], int Length, int Width);
void testnum(int x, int y, int num, int text_length, int text_width);
void startgame() {
	cleardevice();
	TCHAR record_text1[] = _T("点左键开始新游戏");
	testtext(100, -300, record_text1, 20, 10);
	/*testtext(100, -430, record_text2, 20, 10);
	testtext(370, -430, record_text3, 20, 10);*/
	Sleep(1000);
	while (1) {
		message_get = getmessage();
		if (message_get.lbutton == 1) {
			return;
		}
	}
}

void Nextgame() {
	//Blackdraw(0, -430, 400, 0);
	cleardevice();
	TCHAR text1[] = _T("目标分数：");
	testtext(100,-300,text1, 20,10);
	testnum(200,-300, Target, 20,10 );
}
void overgame() {
	if (Target >= Real_score) {
		TCHAR text1[] = _T("游戏失败");
		testtext(150, -300, text1, 30, 15);
		Level = 1;
		Real_score = 0;
		Target = 0;
		Sleep(2000);
		flushmessage();
		startgame();
	}
}
void Blackdraw(int _x1,int _y1,int _x2 ,int _y2) {
	setfillcolor(BLACK);
	solidrectangle(_x1, _y1, _x2, _y2);
}
long add_score(int floor_boom) {
	int score = 5 * floor_boom * floor_boom;
	return score;
}
int remain_score(int floor_remain) {
	int score = 2000 - 20 * floor_remain * floor_remain;
	if (score <= 0) {
		return 0;
	}
	else {
		return score;
	}
}
long add_score(int floor_boom);
void printscore() {
	TCHAR score_text[] = _T("score");
	testtext(250, -550, score_text ,20,10);
	/*TCHAR score[10];
	_stprintf_s(score, _T("%d"), Real_score);*/
	testnum(320, -550, Real_score ,20,10);
	TCHAR score_target[] = _T("目标分数：");
	testtext(100,-620, score_target, 20,10);
	testnum(200, -620, Target, 20, 10);
}
void recordscore(int floor_tick) {
	TCHAR record_text1[] = _T("选择");
	TCHAR record_text2[] = _T("星星，破坏将获得");
	TCHAR record_text3[] = _T("分");
	testtext(10, -430 ,record_text1,20, 10);
	testtext(100, -430, record_text2,20, 10);
	testtext(370,-430, record_text3,20, 10);
	//TCHAR record_num1[5];
	//TCHAR record_num2[10];
	//_stprintf_s(record_num1, _T("%d"), floor_tick);//star
	//_stprintf_s(record_num2, _T("%d"), add_score);//score
	testnum(60, -430, floor_tick, 20, 10);
	testnum(300,-430, add_score(floor_tick),20, 10);

}
void Remain_score(int floor_tick) {
	Blackdraw(0, -450, 400, -405);
	TCHAR record_text1[] = _T("剩余");
	TCHAR record_text2[] = _T("星星，将获得");
	TCHAR record_text3[] = _T("分");
	testtext(10, -430, record_text1, 20, 10);
	testtext(100, -430, record_text2, 20, 10);
	testtext(370, -430, record_text3, 20, 10);
	testnum(60, -430, floor_tick, 20, 10);
	testnum(300, -430, remain_score(floor_tick), 20, 10);
}
void initstar() {
	for (int star_x = 0; star_x <= 9; star_x++) {
		for (int star_y = 0; star_y <= 9; star_y++) {
			floor[star_y][star_x].star_y = star_y;
			floor[star_y][star_x].star_x = star_x;
			floor[star_y][star_x].color = WHITE;
			floor[star_y][star_x].state = normal;
		}
	}

}
COLORREF num_change_col(int floorcolor);
void flushstar( int power) {
	for (int star_x = 0; star_x <= 9; star_x++) {
		for (int star_y = 0; star_y <= 9; star_y++) {
			int Color = rand() % power;
			floor[star_y][star_x].state = normal;
			floor[star_y][star_x].color = num_change_col(Color);
		}
	}
}

typedef struct star_color {
	COLORREF color1;
	COLORREF color2;
	COLORREF color3;
	COLORREF color4;
	COLORREF color5;
}star_color ;
star_color initcolor = { RED, YELLOW, GREEN, BLUE, CYAN };
star_color loadcolor ;
COLORREF randcolor() {
	int Color = rand();
	Color = Color % 5 + 1;
	if (Color == 1) {
		return initcolor.color1;
	}else if (Color == 2) {
		return initcolor.color2;
	}else if (Color == 3) {
		return initcolor.color3;
	}else if (Color == 4) {
		return initcolor.color4;
	}else if (Color == 5) {
		return initcolor.color5;
	}

}
void testcircle(COLORREF Color) {//测试代码勿删
	//setfillcolor(randcolor(rand()));
	setfillcolor(Color);
	fillcircle(300, -500, 50);
}
COLORREF num_change_col(int floorcolor) {
	if (floorcolor == 0) {
		return loadcolor.color1;
	}
	else if(floorcolor == 1) {
		return loadcolor.color2;
	}
	else if(floorcolor == 2) {
		return loadcolor.color3;
	}
	else if(floorcolor == 3) {
		return loadcolor.color4;
	}
	else if(floorcolor == 4) {
		return loadcolor.color5;
	}
	else {
		return BROWN;
	}
}
//yes
COLORREF num_change_lin(int floorstate){
	if (floorstate == normal) {
		return BLACK;
	}
	else if(floorstate == ticked){
		return WHITE;
	}
	else if (floorstate == record) {
		return YELLOW;
	}
	else if (floorstate == nofloor ) {
		return BLACK;
	}
	else {
		return RED;
	}
}
void testtext( int x, int y,TCHAR text[] ,int Length,int Width) {
	settextstyle(Length, Width, _T("Consolas"));
	outtextxy(x, y, text);
}

void testnum(int x ,int y,int num ,int text_length ,int text_width) {
	settextstyle(text_length, text_width ,_T("Consolas"));
	settextcolor(YELLOW);
	/*int Num = 1;
	while (num > 10) {
		Num++;
		num = num / 10;
	}
	TCHAR* text = (TCHAR*)malloc(sizeof(TCHAR) * (Num));
	if (text == NULL) {
		testcircle(RED);
		return;
	}*/
	TCHAR text[10];
	memset(text, 0, sizeof(text));
	//_tcscpy_s(text, 2, _T("0"));
	//TCHAR text[Num] = _T("000");
	//text = (TCHAR*)_T("000");
	//testcircle(GREEN);
	_stprintf_s(text, _T("%d"), num);

	//while (num > 10) {
	//	Num++;
	//	num = num / 10;
	//}
	////outtextxy(x, y, text);
	//for (int ii = 0; ii< Num; ii++) {
	//	outtextxy(x + ii*length , y, text[ii]);
	//}
	outtextxy(x , y, text);

}
void drawstar_origin(int loca_y_o, int loca_x_o) {//核心组件之生成地板
	//画出方块的位置和颜色
	int floorstate = floor[loca_y_o][loca_x_o].state;
	COLORREF floorcolor = floor[loca_y_o][loca_x_o].color;
	loca_x_o = loca_x_o * 40 + 20;
	loca_y_o = -(loca_y_o * 40 + 20);
	int loca_x = loca_x_o - floor_length / 2;
	int loca_y = loca_y_o + floor_length / 2;//方向往上
	//int floorcolor = floor[loca_y_o][loca_x_o].color;
	
	setfillcolor(floorcolor);
	setlinecolor(num_change_lin(floorstate));
	//setlinecolor(WHITE);
	fillroundrect(loca_x, loca_y, loca_x + (floor_length-small_floor)
		, loca_y - (floor_length-small_floor),20,20);
	
};

void alldrawstar() {
	for (int loca_x = 0; loca_x <= length -1; loca_x++) {
		for (int loca_y = 0; loca_y <= width -1; loca_y++) {
			drawstar_origin(loca_y, loca_x);
		}
	}

}
bool change_loca_xy(short * address_x, short* address_y)
//存放的位置与地板数组对应
{	
	if (*address_x <= 0 || *address_x >= floor_length * length
		|| *address_y >= 0 || *address_y <= -floor_length * length) {
		
		return 0;
	}
	else{
		/*setlinecolor(WHITE);
		line(0, 0, 380, -600);*/
		//setlinecolor(RED);
		//line(200, -320, *address_x, *address_y);
		short loca_x = *address_x / 40;
		short loca_y =  - *address_y / 40;
		//line(200, -320, loca_x* 40 + 20, -loca_y * 40 -20);
		*address_x = loca_x;
		*address_y = loca_y;
		/*TCHAR test_xy[5];
		settextstyle(100, 40, _T("Consolas"));
		_stprintf_s(test_xy, _T("%d"), *address_x);
		outtextxy(200, -500, test_xy);*/
		return 1;
	}

}
void floor_normal() {
	for (int loca_x = 0; loca_x <= length - 1; loca_x++) {
		for (int loca_y = 0; loca_y <= width - 1; loca_y++) {
			if (floor[loca_y][loca_x].state == record 
				|| floor[loca_y][loca_x].state == ticked) {
				floor[loca_y][loca_x].state = normal;
			}
		}
	}
}

stars gettickfloor() {
	//TCHAR test_xy[5];
	bool floor_tick = 1;
	do  {
		if (peekmessage(&startmessage, EX_MOUSE, FALSE)) {
			
			getmessage(&message_get, EX_MOUSE);
			if (message_get.lbutton) {
				flushmessage();
				//cleardevice();
				//setfillcolor(GREEN);
				//fillcircle(200, -320, 50);
				short loca_x = message_get.x;
				short loca_y = message_get.y;
				loca_y = loca_y - 640;
				if (loca_x <= 0 || loca_x >= floor_length * length
					|| loca_y >= 0 || loca_y <= -floor_length * length) {
					//这意味着选中的不是方块
					setfillcolor(GREEN);
					//settextcolor(RED);

					/*settextstyle(100, 40, _T("Consolas"));
					_stprintf_s(test_xy, _T("%d"), loca_y);
					outtextxy(100, -500, test_xy);*/
					//fillcircle(100, -220, 50);
					continue;
				
				}
				else {
					int change = change_loca_xy(&loca_x, &loca_y);
					if (change && floor[loca_y][loca_x].state != nofloor) {
						//再次检测是否越位并转化鼠标值为方块方位
						//并检测方块状态是否为不为空
						//floor_normal();
						//floor[loca_y][loca_x].state = ticked;
						//testcircle();
						return floor[loca_y][loca_x];
					}
					
				}
				
			}
		}//判断
	} while (floor_tick);//循环
	
}
bool over_floor(int loca_x, int loca_y) {
	if (loca_x< 0 || loca_x > length - 1 || loca_y<0 || loca_y >width - 1) {
		return 0;
	}
	else {
		return 1;
	}
}
	stars* up_clear( stars* Floor ) {
		//stars floor = Floor;
		int loca_x = Floor->star_x;
		int loca_y = Floor->star_y + 1;
		stars* thanfloor = &floor[loca_y][loca_x];
		if (thanfloor->color == Floor->color && thanfloor->state == normal
			&& over_floor(loca_x, loca_y)) {
			thanfloor->state = ticked;
			return thanfloor;
		}
		else {
			return NULL;
		}
	
	}
	stars* down_clear(stars* Floor) {
		//stars floor = Floor;
		int loca_x = Floor->star_x;
		int loca_y = Floor->star_y - 1;
		stars* thanfloor = &floor[loca_y][loca_x];
		if (thanfloor->color == Floor->color && thanfloor->state == normal
			&& over_floor(loca_x, loca_y)) {
			thanfloor->state = ticked;
			return thanfloor;
		}
		else {
			return NULL;
		}

	}
	stars* left_clear(stars* Floor) {
		//stars floor = Floor;
	
		int loca_x = Floor->star_x - 1;
		int loca_y = Floor->star_y;
		stars* thanfloor = &floor[loca_y][loca_x];
		if (thanfloor->color == Floor->color && thanfloor->state == normal
			&& over_floor(loca_x, loca_y)) {
			thanfloor->state = ticked;
			//testcircle(GREEN);
			return thanfloor;
		}
		else {
			//testcircle(RED);
			return NULL;
		}

	}
	stars* right_clear(stars* Floor) {
		//stars floor = Floor;
		int loca_x = Floor->star_x + 1;
		int loca_y = Floor->star_y;
		stars* thanfloor = &floor[loca_y][loca_x];
		if (thanfloor->color == Floor->color && thanfloor->state == normal
			&& over_floor(loca_x, loca_y)) {
			thanfloor->state = ticked;
			return thanfloor;
		}
		else {
			return NULL;
		}

	}
	stars* all_clear(stars* Floor) {
		//testcircle(GREEN);
		Floor->state = record;
		stars* testup = Floor;
		stars* testdown = Floor;
		stars* testleft = Floor; 
		stars* testlight = Floor;
		//TCHAR testnum[5];
		//int testupdown = 0;
			//testupdown++;
			//testcircle(GREEN);
			//_stprintf_s(testnum, _T("%d"), testupdown);
			//testtext(testnum);
		testup = up_clear(testup);
	
		testdown = down_clear(testdown);
		testleft = left_clear(testleft);
		testlight = right_clear(testlight);
		if (testup == NULL) {
			//return NULL;
		}
		else {
			all_clear(testup);
		}
		if (testdown == NULL) {
			//return NULL;
		}
		else {
			//testcircle(GREEN);
			all_clear(testdown);
		}
		if (testleft == NULL) {
			//return NULL;
		}
		else {
			all_clear(testleft);
		}
		if (testlight == NULL) {
			return NULL;
		}
		else {
			all_clear(testlight);
		}
	}
int travel_Floor(const int travel){
	int floor_num = 0;
	for (int loca_x = 0; loca_x <= length - 1; loca_x++) {
		for (int loca_y = 0; loca_y <= width - 1; loca_y++) {
			if (floor[loca_y][loca_x].state == travel) {
				floor_num++;
			}
		}
	}
	return floor_num;
}
void tick_or_clear(stars* Floor);
bool kuosan(stars Floor) {
	Blackdraw(0,-450,400,-405);
	if (Floor.state == normal) {
		floor_normal();
		Floor.state = record;
		int loca_y = Floor.star_y;
		int loca_x = Floor.star_x;
		COLORREF Color = Floor.color;
		//floor_Tick = 1;
		//floor[loca_y][loca_x].state = record;
		//将其标记为记录，检测上下左右颜色与它的情况是否为正常，是则将其标为选中。
		all_clear(&Floor);
		//recordscore();
		int record_floor = 0;
		record_floor = travel_Floor(record) ;
		if (record_floor <= 1) {
			floor_normal();
		}
		else {
			recordscore(record_floor);
		}
		return TRUE;
	}
	else if (Floor.state == record) {
		//testcircle(randcolor());
		tick_or_clear(&Floor);
		return FALSE;
	}

}
void test_floor1();
void test_floor2();
void tick_or_clear(stars* Floor){
	//if (Floor->state == record) {
	int floor_boom = 0;
	for (int loca_x = 0; loca_x <= length - 1; loca_x++) {
		for (int loca_y = 0; loca_y <= width - 1; loca_y++) {
			if (floor[loca_y][loca_x].state == record) {
				//清除选中的方块
				floor_boom ++;
				floor[loca_y][loca_x].color = BLACK;
				floor[loca_y][loca_x].state = nofloor;
				//预留UI界面

			}
		}
	}
	Real_score += add_score(floor_boom);
	test_floor1();
	//testcircle(YELLOW);
	test_floor2();
	Blackdraw(0,-450,390,-405);
}
void exchange_floor(stars* floor1 , stars* floor2) {
	stars center = *floor1;
	floor1->state = floor2->state;
	floor1->color = floor2->color;
	floor2->state = center.state;
	floor2->color = center.color;
	return;
}
void moveleft_floor(int loca_x){
	int rightfloor = 0;//递增的列数
	int add_x = 1;//要平移的列数
	//testnum(300, -550, loca_x);
	while (rightfloor + loca_x + add_x < length) {
		while(floor[0][loca_x + add_x+ rightfloor].state == normal
			&& rightfloor + loca_x + add_x <length) {
			//int upfloor_y = 0;//内部循环
			//testcircle(GREEN);
			for (int upfloor_y = 0; upfloor_y < width;upfloor_y++) {
				exchange_floor(&floor[upfloor_y][loca_x + rightfloor]
					, &floor[upfloor_y][rightfloor + loca_x +add_x]);
				//upfloor_y++;
			}
			rightfloor++;//平移完就换一行平移
		}
		add_x++;//这一行没有方块，找下一行
		//rightfloor++;
	}

}
void test_floor1() {
	//testcircle(RED);
	for (int loca_x = 0; loca_x < length; loca_x++) {
		for (int loca_y = 0; loca_y < width; loca_y++) {
			if (floor[loca_y][loca_x].state == nofloor) {
				//line( 0, 0 , 380 , -600);//测试代码
				int upfloor = 1;
				while (upfloor + loca_y <= width) {
					if (floor[loca_y + upfloor][loca_x].state == normal) {
						exchange_floor(&floor[loca_y + upfloor][loca_x]
							, &floor[loca_y][loca_x]);
						break;
					}
					upfloor++;
				}
				
				//floor[loca_y][loca_y].color = 99;
			}
		}
	}
	
	//testcircle(GREEN);
}
void test_floor2() {
	int loca_y1 = 0;
	//testcircle(GREEN);
	TCHAR yy[] = _T("fuck");
	//testtext(200,-500 , yy);
	
	for (int loca_x1 = 0; loca_x1 < length; loca_x1++) {
		if (floor[loca_y1][loca_x1].state == nofloor) {
			//testcircle(GREEN);
			//int test = 
			moveleft_floor(loca_x1);
			
		}
	}
}
void testgame() {
	for (int loca_x = 0; loca_x <= length - 1; loca_x++) {
		for (int loca_y = 1; loca_y <= width - 1; loca_y++) {
			floor[loca_y][loca_x].color = RED;
		}
	}
}
bool judge_floor_one(stars* Floor, const int Direction) {
	stars* testup = NULL;
	if(Direction == UP){
		testup = up_clear(Floor);
	}else if (Direction == DOWN) {
		testup = down_clear(Floor);
	}
	else if (Direction == LEFT) {
		testup = left_clear(Floor);
	}
	else if (Direction == RIGHT) {
		testup = right_clear(Floor);
	}
	if (testup == NULL) {
		return 0;
	}
	else { 
		return 1; 
	}
}
bool judge_floor() {
	int judge = 0;
	for (int loca_x = 0; loca_x < length; loca_x++) {
		for (int loca_y = 0; loca_y < width; loca_y++) {
			if (floor[loca_y][loca_x].state == normal) {
				judge += judge_floor_one(&floor[loca_y][loca_x], UP);
				judge += judge_floor_one(&floor[loca_y][loca_x], DOWN);
				judge += judge_floor_one(&floor[loca_y][loca_x], LEFT);
				judge += judge_floor_one(&floor[loca_y][loca_x], RIGHT);
				if (judge  >= 1) {
					
					floor_normal();
					return TRUE;
				}
			}
		}
	}
	floor_normal();
	//testcircle(GREEN);
	//已没有可匹配地块
	return FALSE;
}
void remain_clear() {
	int remain = travel_Floor(normal);
	int UI_remain = 0;
	Remain_score(0);
	for (int i = 1; i <= 8; i++) {
		Blackdraw(0, -400 ,400, 0 );
		Sleep(150);
		alldrawstar();
		Sleep(50);
	}
	for (int loca_x = 0; loca_x <= length - 1; loca_x++) {
		for (int loca_y = width - 1; loca_y >=0 ; loca_y --) {
			if (floor[loca_y][loca_x].state == normal) {
				UI_remain ++ ;
				floor[loca_y][loca_x].color = BLACK;
				floor[loca_y][loca_x].state = nofloor;
				if (UI_remain <= 10 || UI_remain == remain) {
					alldrawstar();
					Remain_score(UI_remain);
					Sleep(300);
				}
			}
		}
	}
	Sleep(500);
	Real_score += remain_score(remain);
	printscore();
	Sleep(500);
}
int main() {
	
	srand(time(NULL));
	initgraph(402,640);
	setorigin(0, 640);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID , 5);
	loadcolor = initcolor;
	initstar();
	int power = 5;
	startgame();
	while (1) {
		Levelscore(Level, power);
		Nextgame();
		flushstar(power);
		Sleep(2000);
		//testgame();
		printscore();
		alldrawstar();
		//testcircle(WHITE);
		//testcircle(randcolor());
		while (1) {
			//testcircle(randcolor());
			Sleep(50);
			int Kuosan = 0;
			Kuosan = kuosan(gettickfloor());
			flushmessage();
			//test_floor();
			//test_floor();
			alldrawstar();
			printscore();
			if (!Kuosan) {
				if (!judge_floor()) {
					Level++;
					remain_clear();
					Sleep(1000);
					overgame();
					break;
				}
			}
		}
	}
	//testover
	scanf_s("%d",&power);
	closegraph();
	return 0;
}
//9月21日，消灭星星项目第一版测试版结束
