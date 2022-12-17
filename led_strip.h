#ifndef __LED_STRIP_H__
#define __LED_STRIP_H__

#include <stdint.h>

class Color
{
public:
  Color();
  Color(const uint8_t a_color_red, const uint8_t a_color_green, const uint8_t a_color_blue);
  ~Color();
  void SetColorRed(const uint8_t a_color_red);
  void SetColorGreen(const uint8_t a_color_green);
  void SetColorBlue(const uint8_t a_color_blue);
  uint8_t GetColorRed() const;
  uint8_t GetColorGreen() const;
  uint8_t GetColorBlue() const;
  const Color& GetColor() const;

  Color& operator++();
  Color& operator--();
  Color operator++(int);
  Color operator--(int);
private:
  uint8_t m_color_red;
  uint8_t m_color_green;
  uint8_t m_color_blue;
};

class Led : public Color
{
public:
  Led();
  ~Led();
  void SetColor(Color& a_color);
  Color GetColor ();
  void SetBrightness(uint8_t a_brightness);
  uint8_t GetBrightness();
private:
  Color* color;
  uint8_t brightness;
};

class LedStrip : public Led
{
public:
    enum Animation
  {
    fromlefttoright,
    fromrighttoleft,
    fromcentertoedges,
    fromedgestocenter,
    brightnessadjustable,
    onecolortoanother
  };
  LedStrip();
  ~LedStrip();
  void SetNumOfLeds(uint8_t a_num);
  uint8_t GetNumOfLeds();
  void SetAnimation(Animation a_animation);
  Animation GetAnimation();
  void EnableDimmer();
  void DisableDimmer();
  void Show();
private:
  bool isdimmerenabled;
  Animation animation;
  //array of leds <vector>
};

#endif // __LED_STRIP_H__
