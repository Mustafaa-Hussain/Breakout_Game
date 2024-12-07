#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>

#define LEFT 75
#define RIGHT 77

class Paddle {
	int x, y, old_x, width, height;

public:
	Paddle(int init_x, int init_y, int w, int h) {
		x = old_x = init_x;
		y = init_y;
		width = w;
		height = h;
	}

	void draw() {
		setfillstyle(SOLID_FILL, BLACK	);
		bar(old_x, y, old_x + width, y + height);
		
		setfillstyle(SOLID_FILL, GREEN);
		bar(x, y, x + width, y + height);
	}

	void moveLeft() {
		old_x = x;
		x -= 20;
		if (x < 0) x = 0;
	}

	void moveRight() {
		old_x = x;
		x += 20;
		if (x > 600 - width) x = 600 - width;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getWidth() { return width; }
};

class Ball {
	int x, old_x,
		y, old_y,
		dx, dy,
		radius;

public:
	Ball(int init_x, int init_y, int init_dx, int init_dy, int r) {
		x = old_x = init_x;
		y = old_y = init_y;
		
		dx = init_dx;
		dy = init_dy;
		radius = r;
	}

	void draw() {
		setfillstyle(SOLID_FILL, BLACK);
		fillellipse(old_x, old_y, radius, radius);
		setcolor(0);
		circle(old_x, old_y, radius);

		setfillstyle(SOLID_FILL, WHITE);
		fillellipse(x, y, radius, radius);
	}

	void move() {
		old_x = x;
		old_y = y;
		
		x += dx;
		y += dy;

		if (x <= radius || x >= 620 - radius) dx = -dx;
		if (y <= radius) dy = -dy;
		
	}

	int getX() { return x; }
	int getY() { return y; }
	int getRadius() { return radius; }
	void reverseDirectionY() { dy = -dy; }
};

class Bricks {
	int rows, cols;
	int bricks[5][10];
	int brickWidth, brickHeight;

public:
	Bricks(int r, int c);

	void draw();

	//ToDo negative drow 
	//this will drow brick with background color
	//over the one was destroyed
	void removeBrick();

	int checkCollision(Ball& ball);
};

Bricks::Bricks(int r, int c) {
	rows = r;
	cols = c;
	brickWidth = 60;
	brickHeight = 20;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bricks[i][j] = 1;
		}
	}
}


void Bricks::draw() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (bricks[i][j] == 1) {
				setfillstyle(SOLID_FILL, BLUE);
				bar(j * brickWidth + 10, i * brickHeight + 20,
					j * brickWidth + 10 + brickWidth - 2, i * brickHeight + 20 + brickHeight - 2);
			}
		}
	}
}

void Bricks::removeBrick() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (bricks[i][j] == 0) {
				setfillstyle(SOLID_FILL, BLACK);
				bar(j * brickWidth + 10, i * brickHeight + 20,
					j * brickWidth + 10 + brickWidth - 2, i * brickHeight + 20 + brickHeight - 2);
			}
		}
	}
}

int Bricks::checkCollision(Ball& ball) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (bricks[i][j] == 1) {
				int brickX = j * brickWidth + 10;
				int brickY = i * brickHeight + 10;

				if (ball.getX() >= brickX && ball.getX() <= brickX + brickWidth &&
					ball.getY() >= brickY && ball.getY() <= brickY + brickHeight) {
					bricks[i][j] = 0;
					ball.reverseDirectionY();

					return 1;
				}
			}
		}
	}
	return 0;
}

class Game {
	Paddle paddle;
	Ball ball;
	Bricks bricks;
	int score;
	int score_flag;

public:
	Game() : paddle(250, 450, 100, 10), ball(300, 300, -2, -3, 8), bricks(5, 10), score(0) {

		int gd = DETECT, gm;
		initgraph(&gd, &gm, "D:\\BGI");

		setcolor(15);
		sprintf(buf, "Score: %d", score);
		outtextxy(10, 10, buf);

		score_flag = 1;

	}

	void run();

private:
	char buf[50];
	
	
	void draw() {
		paddle.draw();
		bricks.draw();
		bricks.removeBrick();
		ball.draw();
		

		if(score_flag){
			setfillstyle(SOLID_FILL, BLACK	);
			bar(10, 10 , 100, 18);

			setcolor(15);
			sprintf(buf, "Score: %d", score);
			outtextxy(10, 10, buf);
			score_flag = 0;
		}
	}

	void input();

	void update();

	int checkGameOver() {
		setcolor(15);
		if (ball.getY() > getmaxy()) {
			outtextxy(200, 200, "Game Over");
			outtextxy(200, 230, "Press any key to exit");
			getch();
			return 1;
		}

		if (score == 50) {
			outtextxy(200, 200, "You Won!");
			getch();
			return 1;
		}

		return 0;
	}
};

void Game::update() {
		ball.move();
		
		if (ball.getY() + ball.getRadius() >= paddle.getY() &&
			ball.getX() >= paddle.getX() &&
			ball.getX() <= paddle.getX() + paddle.getWidth()) {
			ball.reverseDirectionY();

			sound(1000);
			delay(20);
			nosound();
		}

		if (bricks.checkCollision(ball)) {
			score++;
			score_flag = 1;

			sound(1200);
			delay(50);
			nosound();
		}
	}

void Game::run() {

		while (1) {
			//cleardevice();
			draw();
			input();
			update();

			if (checkGameOver()) break;

            delay(10);
        }
		getch();

        closegraph();
    }


void Game::input() {
    if (kbhit()) {
        switch (getch()) {
        case LEFT: paddle.moveLeft(); break;
        case RIGHT: paddle.moveRight(); break;
        }
    }
}

int main() {
    Game game;
    game.run();
    return 0;
}
