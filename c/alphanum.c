//Created by David Lopes
//Used with his permission for Ashely Taylor and Chas Jhin's Final Project

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"gfx.h"

#define PI 3.1415926535897932384626433832795028

/*Draws a circle centered at (x,y) with radius r*/
void drawCircle(float x, float y, float r) {
  float theta;
  for(theta = 0; theta <= 2*PI; theta += PI/100)
      gfx_line(x+r*cos(theta), y+r*sin(theta), x+r*cos(theta+PI/100), y+r*sin(theta+PI/100));
}

/*Takes two opposing vertices as input*/
void drawBox(float x1, float y1, float x2, float y2) {
  gfx_line(x1, y1, x2, y1);
  gfx_line(x1, y1, x1, y2);
  gfx_line(x2, y2, x1, y2);
  gfx_line(x2, y2, x2, y1);
}

void draw_A(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x+h/2, y, x+h/2, y+h);
}

void draw_B(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+3*h/8, y);
  gfx_line(x, y+h, x+3*h/8, y+h);
  gfx_line(x, y+h/2, x+3*h/8, y+h/2);
  gfx_line(x+h/2, y+h/4, x+3*h/8, y);
  gfx_line(x+h/2, y+3*h/4, x+3*h/8, y+h);
  gfx_line(x+h/2, y+h/4, x+3*h/8, y+h/2);
  gfx_line(x+h/2, y+3*h/4, x+3*h/8, y+h/2);
}

void draw_C(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h, x+h/2, y+h);
}

void draw_D(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+3*h/8, y);
  gfx_line(x, y+h, x+3*h/8, y+h);
  gfx_line(x+h/2, y+h/4, x+3*h/8, y);
  gfx_line(x+h/2, y+3*h/4, x+3*h/8, y+h);
  gfx_line(x+h/2, y+h/4, x+h/2, y+3*h/4);
}

void draw_E(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
}

void draw_F(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
}

void draw_G(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y+h, x+h/2, y+h/2);
  gfx_line(x+h/4, y+h/2, x+h/2, y+h/2);
}

void draw_H(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
}

void draw_I(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/4, y, x+h/4, y+h);
}

void draw_J(int x, int y, int h) {
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h);
  gfx_line(x, y+h, x, y+h/2);
}

void draw_K(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y+h/2, x+h/2, y);
  gfx_line(x, y+h/2, x+h/2, y+h);
}

void draw_L(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
}

void draw_M(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h);
  gfx_line(x, y, x+h/4, y+h/2);
  gfx_line(x+h/2, y, x+h/4, y+h/2);
}

void draw_N(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h);
  gfx_line(x, y, x+h/2, y+h);
}

void draw_O(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h);
}

void draw_P(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+3*h/8, y);
  gfx_line(x+h/2, y+h/4, x+3*h/8, y);
  gfx_line(x+h/2, y+h/4, x+3*h/8, y+h/2);
  gfx_line(x, y+h/2, x+3*h/8, y+h/2);
}

void draw_Q(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+h/2, y);
  gfx_line(x+h/2, y, x+h/2, y+3*h/4);
  gfx_line(x, y+h, x+3*h/8, y+h);
  gfx_line(x+h/2, y+3*h/4, x+3*h/8, y+h);
  gfx_line(x+h/4, y+h/2, x+h/2, y+h);
}

void draw_R(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y, x+3*h/8, y);
  gfx_line(x, y+h/2, x+3*h/8, y+h/2);
  gfx_line(x+h/2, y+h/4, x+3*h/8, y);
  gfx_line(x+h/2, y+h/4, x+3*h/8, y+h/2);
  gfx_line(x+h/4, y+h/2, x+h/2, y+h);
}

void draw_S(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y+h, x+h/2, y+h/2);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x, y, x, y+h/2);
}

void draw_T(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x+h/4, y, x+h/4, y+h);
}

void draw_U(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h);
}

void draw_V(int x, int y, int h) {
  gfx_line(x, y, x+h/4, y+h);
  gfx_line(x+h/2, y, x+h/4, y+h);
}

void draw_W(int x, int y, int h) {
  gfx_line(x, y, x, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h);
  gfx_line(x+h/4, y+h/2, x+h/2, y+h);
  gfx_line(x, y+h, x+h/4, y+h/2);
}

void draw_X(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y+h);
  gfx_line(x, y+h, x+h/2, y);
}

void draw_Y(int x, int y, int h) {
  gfx_line(x, y, x+h/4, y+h/2);
  gfx_line(x+h/2, y, x+h/4, y+h/2);
  gfx_line(x+h/4, y+h/2, x+h/4, y+h);
}

void draw_Z(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x, y+h, x+h/2, y);
}

void draw_one(int x, int y, int h) {
  gfx_line(x+h/2, y, x+h/2, y+h);
}

void draw_two(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x+h/2, y, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x, y+h/2);
  gfx_line(x, y+h/2, x, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
}     

void draw_three(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x+h/2, y, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
}

void draw_four(int x, int y, int h) {
  gfx_line(x, y, x, y+h/2);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
}

void draw_five(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y, x, y+h/2);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
}

void draw_six(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y, x, y+h/2);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
  gfx_line(x, y+h/2, x, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
}

void draw_seven(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x+h/2, y, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
}

void draw_eight(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y, x, y+h/2);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
  gfx_line(x, y+h/2, x, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h/2);
}

void draw_nine(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y, x, y+h/2);
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h/2);
}

void draw_zero(int x, int y, int h) {
  gfx_line(x, y, x+h/2, y);
  gfx_line(x, y, x, y+h/2);
  gfx_line(x+h/2, y+h/2, x+h/2, y+h);
  gfx_line(x, y+h/2, x, y+h);
  gfx_line(x, y+h, x+h/2, y+h);
  gfx_line(x+h/2, y, x+h/2, y+h/2);
}

void draw_positive(int x, int y, int h) {
  gfx_line(x, y+h/2, x+h/2, y+h/2);
  gfx_line(x+h/4, y+h/4, x+h/4, y+3*h/4);
}

void draw_negative(int x, int y, int h) {
  gfx_line(x, y+h/2, x+h/2, y+h/2);
}

void draw_colon(int x, int y, int h) {
  drawBox(x+3*h/16, y+12*h/16, x+4*h/16, y+13*h/16);
  drawBox(x+3*h/16, y+6*h/16,  x+4*h/16,  y+7*h/16);
}

void draw_period(int x, int y, int h) {
  drawBox(x+3*h/16, y+14*h/16, x+4*h/16, y+h);
}

void draw_comma(int x, int y, int h) {
  gfx_line(x+3*h/8, y+h, x+2*h/8, y+18*h/16);
}

void draw_slash(int x, int y, int h) {
  gfx_line(x, y+h, x+h/2, y);
}

void draw_open_angle(int x, int y, int h) {
  gfx_line(x+h/2, y, x, y+h/2);
  gfx_line(x, y+h/2, x+h/2, y+h);
}

void draw_close_angle(int x, int y, int h) {
  gfx_line(x+h/2, y+h/2, x, y+h);
  gfx_line(x, y, x+h/2, y+h/2);
}

//added by Chas
void draw_exclamation_mark(int x, int y, int h) {
	draw_period(x, y, h);
	drawBox(x+3*h/16, y, x+4*h/16, y+h-5);
}

void draw_character(char character, int x, int y, int h) {
  character = toupper(character);
  switch (character) {
  case 'A':
    draw_A(x, y, h); break;
  case 'B':
    draw_B(x, y, h); break;
  case 'C':
    draw_C(x, y, h); break;
  case 'D':
    draw_D(x, y, h); break;
  case 'E':
    draw_E(x, y, h); break;
  case 'F':
    draw_F(x, y, h); break;
  case 'G':
    draw_G(x, y, h); break;
  case 'H':
    draw_H(x, y, h); break;
  case 'I':
    draw_I(x, y, h); break;
  case 'J':
    draw_J(x, y, h); break;
  case 'K':
    draw_K(x, y, h); break;
  case 'L':
    draw_L(x, y, h); break;
  case 'M':
    draw_M(x, y, h); break;
  case 'N':
    draw_N(x, y, h); break;
  case 'O':
    draw_O(x, y, h); break;
  case 'P':
    draw_P(x, y, h); break;
  case 'Q':
    draw_Q(x, y, h); break;
  case 'R':
    draw_R(x, y, h); break;
  case 'S':
    draw_S(x, y, h); break;
  case 'T':
    draw_T(x, y, h); break;
  case 'U':
    draw_U(x, y, h); break;
  case 'V':
    draw_V(x, y, h); break;
  case 'W':
    draw_W(x, y, h); break;
  case 'X':
    draw_X(x, y, h); break;
  case 'Y':
    draw_Y(x, y, h); break;
  case 'Z':
    draw_Z(x, y, h); break;
  case '1':
    draw_one(x, y, h); break;
  case '2':
    draw_two(x, y, h); break;
  case '3':
    draw_three(x, y, h); break;
  case '4':
    draw_four(x, y, h); break;
  case '5':
    draw_five(x, y, h); break;
  case '6':
    draw_six(x, y, h); break;
  case '7':
    draw_seven(x, y, h); break;
  case '8':
    draw_eight(x, y, h); break;
  case '9':
    draw_nine(x, y, h); break;
  case '0':
    draw_zero(x, y, h); break;
  case '-':
    draw_negative(x, y, h); break;
  case '.':
    draw_period(x, y, h); break;
  case ',':
    draw_comma(x, y, h); break;
  case ':':
    draw_colon(x, y, h); break;
  case '/':
    draw_slash(x, y, h); break;
  case '<':
    draw_open_angle(x, y, h); break;
  case '>':
    draw_close_angle(x, y, h); break;
	case '!':
		draw_exclamation_mark(x, y, h); break;
  }
}

void drawString(char *string, int x, int y, int h) {
  int ix;
  for(ix = 0; string[ix]; ix++)
    draw_character(string[ix], x+ix*4*h/5, y, h);
}
