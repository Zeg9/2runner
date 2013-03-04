#include "Video.h"
#include "Font.h"
#include "tools.h"

#define SLOWNESS 50

int getch(int h, int ch)
{
	if (randint(0,2)!=0) return ch;
	int nch;
	if (ch < 3)
		nch = ch + randint(1,2);
	else if (ch > h-4)
		nch = ch + randint(-2,0);
	else
		nch = ch + randint(-2,2);
	return nch;
}

void startGame()
{
	Device &d = getDevice();
	Image blank("data/blank.png");
	Image block("data/block.png");
	Image adude("data/adude.png");
	Image hebar("data/hebar.png");
	Image hback("data/hback.png");
	Font font("data/font.ttf&15");
	Font bfont("data/font.ttf&20");
	SDL_Event e;
	
	int bw = block.getWidth();
	int bh = block.getHeight();
	const int w = d.getWidth()/bw+1;
	const int h = d.getHeight()/bh+1;
	bool blocks[w][h];
	int ticks = SDL_GetTicks(), sticks=ticks, lticks = ticks, dticks=0;
	int ch = 2;
	for(int x = 0; x < w; x++)
	for (int y = 0; y < h; y++)
		blocks[x][y] = (y>=h-ch);
	float ax(4.0), ay(5.0), av(0.0);
	float health(100.0);
	while (d.run())
	{
		while (d.hasEvent())
		{
			e = d.nextEvent();
			switch (e.type)
			{
				case SDL_KEYDOWN:
					if (ay >=0 && blocks[(int)ax][(int)ay+1])
						av = -1.0;
				default:
					break;
			}
		}
		for(int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			int dx = x*bw-dticks*bw/SLOWNESS;
			if (blocks[x][y])
				d.drawImage(&block,dx,y*bh);
			else
				d.drawImage(&blank,dx,y*bh);
		}
		d.drawImage(&adude,ax*bw,ay*bh);
		font.render("Score: "+tostring(((int)SDL_GetTicks()-sticks)/500),0,0,0,10,16,ALIGN_LEFT,ALIGN_MIDDLE);
		d.drawImage(&hback, 8,d.getHeight()-24);
		d.drawImage(&hebar, 8,d.getHeight()-24,0,0, health*hebar.getWidth()/100, 16);
		font.render(tostring((int)health),0,0,0,hebar.getWidth()+16,d.getHeight()-16,ALIGN_LEFT,ALIGN_MIDDLE);
		d.render();
		ticks = SDL_GetTicks();
		dticks = ticks-lticks;
		if (av < 0) av += .005*d.getDTime();
		if (av > 0) av = 0;
		ay += av;
		if (!blocks[(int)ax][(int)ay+1])
			ay += .025*d.getDTime();
		if (blocks[(int)ax][(int)ay+1] || (ax != (int) ax && blocks[(int)ax+1][(int)ay+1]))
			ay = (int)ay;
		if (ay < 0)
		{
			ay = 0;
			av = 0;
		}
		bool contact = blocks[(int)ax+1][(int)ay];
		if (contact)
		{
			health -= .05*d.getDTime();
			lticks = ticks;
			dticks = 0;
		}
		else if (dticks >= SLOWNESS)
		{
			ch = getch(h,ch);
			for(int x = 0; x < w; x++)
			for (int y = 0; y < h; y++)
			{
				if (x+1 < w)
					blocks[x][y] = blocks[x+1][y];
				else
					blocks[x][y] = (y>=h-ch);
			}
			lticks = ticks;
			dticks = 0;
		}
		if (health <= 0)
		{
			int score = ((int)SDL_GetTicks()-sticks)/500;
			while(d.run())
			{
				while (d.hasEvent())
				{
					e = d.nextEvent();
					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
						return;
				}
				d.clear(32,32,32);
				bfont.render(
					"Your score: " + tostring(score) + "\n"
					"Press return to try again !",
					randint(0,255),randint(0,255),randint(0,255),
					d.getWidth()/2,d.getHeight()/2,ALIGN_CENTER,ALIGN_MIDDLE);
				d.render();
			}
		}
	}
}

int main(int argc, char**argv)
{
	Device &d = getDevice();
	while (d.run()) startGame();
}
