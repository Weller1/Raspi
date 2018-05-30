/**
 *  @filename   :   main.cpp
 *  @brief      :   2.13inch e-paper display (B) demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 15 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include "epd2in13b.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#define COLORED      1
#define UNCOLORED    0
using namespace std;
int main(void)
{
  Epd epd;
  if (epd.Init() != 0) {
      printf("e-Paper init failed\n");
      return -1;
    }
  unsigned char* frame_black = (unsigned char*)malloc(epd.width * epd.height / 8);
  unsigned char* frame_red = (unsigned char*)malloc(epd.width * epd.height / 8);
  Paint paint_black(frame_black, epd.width, epd.height);
  Paint paint_red(frame_red, epd.width, epd.height);
  paint_black.Clear(UNCOLORED);
  paint_red.Clear(UNCOLORED);

    /* Draw something to the frame buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
  paint_black.SetRotate(1);
  paint_red.SetRotate(1);
  std::string busses = "Bussit";
  char const *busses_char = busses.c_str();
  paint_black.DrawStringAt(10, 8, busses_char, &Font24, COLORED);
  bool run = true;
  std::string arrivals_3;
  std::string arrivals_4;
  std::string arrivals_6;
  while (run){
    // Check bus n. 4
    ifstream four_file("timetables4k.txt");
  if (four_file.good())
  {
    getline(four_file, arrivals_4);
  }
    four_file.close();

    ifstream six_file("timetables6k.txt");
    if (six_file.good())
    {
      getline(six_file, arrivals_6);
    }
    six_file.close();

    ifstream three_file("timetables3k.txt");
    if (three_file.good())
    {
      getline(three_file, arrivals_3);
    }
    three_file.close();

    std::string three = "3K:";
    std::string four = "4K:";
    std::string six = "6K:";
    three = three + arrivals_3;
    four = four + arrivals_4;
    six = six + arrivals_6;
    char const *three_char = three.c_str();
    char const *four_char = four.c_str();
    char const *six_char = six.c_str();
    time_t ct = time(0);
    struct tm* currtime = localtime(&ct);
    std::this_thread::sleep_for(std::chrono::milliseconds(60000));
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);
    std::string hour = std::to_string(currtime->tm_hour + 3);
    std::string minute = std::to_string(currtime->tm_min + 1);
    if (minute.length() == 1) {
      minute = "0" + minute;
    }
    std::string times = hour + ":" + minute;
    char const *showtime = times.c_str();
    paint_black.DrawLine(0, 35, 500, 36, COLORED);

    paint_black.DrawLine(120,0,121,70, COLORED);

    paint_black.DrawStringAt(10, 8, busses_char, &Font24, COLORED);
    paint_red.DrawStringAt(125, 8, showtime, &Font24, COLORED);
    paint_black.DrawStringAt(0, 40, three_char, &Font16, COLORED);
    paint_black.DrawStringAt(0, 60, four_char, &Font16, COLORED);
    paint_black.DrawStringAt(0, 80, six_char, &Font16, COLORED);

    epd.DisplayFrame(frame_black, frame_red);


  }


    /*Write strings to the buffer */
    // paint_black.DrawStringAt(4, 30, "Testijuttu", &Font16, COLORED);
    // paint_red.DrawStringAt(6, 10, "Testijuttu2", &Font16, UNCOLORED);

    /* Display the frame_buffer */

    /* Display the image buffer */
    //epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);

    epd.Sleep();
    return 0;
}
