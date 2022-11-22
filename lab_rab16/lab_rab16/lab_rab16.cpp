#define _USE_MATH_DEFINES
#include <cmath>
#include <conio.h>
#include <windows.h>

class graph
{
protected:
	HWND hwnd;
public:
	HDC hdc;
	graph()
	{
		hwnd = GetForegroundWindow();
		hdc = GetDC(hwnd);
	}
};
//
class world :public graph
{
	POINT* arr;
	int x0;
	int y0;
public:
	int n;
	HPEN pBlack;
	HPEN pYellow;
	HPEN pRed;
	HBRUSH bGreen;
	HBRUSH bBlack;
public:
	world(int x0, int y0)	//конструктор
	{
		this->x0 = x0;
		this->y0 = y0;
		pBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		pYellow = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		pRed = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		bGreen = CreateSolidBrush(RGB(0, 255, 0));
		bBlack = CreateSolidBrush(RGB(0, 0, 0));
		int h = 80;		//амплитуда синусоиды траектории движения
		double da = 2.14;
		double a = 0;
		n = 300;
		arr = new POINT[n];
		for (int i = 0; i < n; i++)
		{
			arr[i].x = (int)a;
			arr[i].y=a/2-((int)(60*sin(a / 90 * M_PI)));
			a += da;
		}
	}
	~world()			//деструктор
	{
		delete[] arr;
	}
	void clear()
	{
		SelectObject(hdc, bBlack);
		SelectObject(hdc, pBlack);
		Rectangle(hdc, 0, 0, x0 * 2, y0 * 2);
	}
	void path()
	{
		SelectObject(hdc, pYellow);
		Polyline(hdc, arr, n);
	}
	POINT getPoint(int n)
	{
		POINT p = { arr[n].x, arr[n].y };
		return p;
	}
};
//
class kreuz
{
	int step, ds;
	int a, b;
public:
	kreuz(int a, int b)	//конструктор
	{
		this->a = a;
		this->b = b;
		step = 0;
		ds = 3;
	}
	void show(world* wrd)
	{
		POINT p = wrd->getPoint(step);
		SelectObject(wrd->hdc, wrd->bGreen);
		SelectObject(wrd->hdc, wrd->pRed);
		Rectangle(wrd->hdc, p.x - a, p.y - b, p.x + a, p.y + b);
	}
	void go(world* wrd)
	{
		int t = 0;
		if ((step <= wrd->n) && (t == 0))
			step += ds;
		else if ((step >= wrd->n)|| (t == 1))
		{
			t == 1;
			step -= ds;
		}
	}
	
};
//
int main()
{
	world* wrd = new world(320, 170);
	kreuz* rc = new kreuz(1, 30);
	kreuz* rc1 = new kreuz(30, 1);	/*создание объектов в динамической
памяти*/
	do
	{
		wrd->clear();
		wrd->path();
		rc->show(wrd);
		rc1->show(wrd);
		Sleep(250);
		rc->go(wrd);
		rc1->go(wrd);
		


	} while (!_kbhit());	//пока не нажата любая клавиша
	delete wrd;		//удаление объекта wrd из динамической памяти
	delete rc;			//удаление объекта rc из динамической памяти
	delete rc1;
	return 0;
}