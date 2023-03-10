#include "led_strip.h"

Color::Color()
  : m_color_red{0}
  , m_color_green{0}
  , m_color_blue{0}
{
}

Color::Color(uint8_t a_color_red, uint8_t a_color_green,
uint8_t a_color_blue)
  : m_color_red{a_color_red}
  , m_color_green{a_color_green}
  , m_color_blue{a_color_blue}
{
}

Color::~Color()
{
}

void Color::SetColorRed(const uint8_t a_color_red)
{
  m_color_red = a_color_red;
}

void Color::SetColorGreen(const uint8_t a_color_green)
{
  m_color_green = a_color_green;
}

void Color::SetColorBlue(const uint8_t a_color_blue)
{
  m_color_blue = a_color_blue;
}

uint8_t Color::GetColorRed() const
{
  return m_color_red;
}
uint8_t Color::GetColorGreen(void) const
{
  return m_color_green;
}
uint8_t Color::GetColorBlue(void) const
{
  return m_color_blue;
}  

const Color& Color::GetColor() const
{
  return *this;
}

Color& Color::operator++()
{
       if(m_color_red == m_color_blue)
         m_color_red == 255 ? --m_color_red : ++m_color_red; 
  else if (m_color_green == m_color_red)
    m_color_green == 255 ? --m_color_green : ++m_color_green;
  else if (m_color_blue == m_color_green)
    m_color_blue == 255 ? --m_color_blue: ++m_color_blue;
  
  else if (m_color_red == 255)
    m_color_blue > 0 ? ++m_color_blue : --m_color_green;
  else if (m_color_green == 255)
    m_color_red > 0 ? ++m_color_red: --m_color_blue;
  else if (m_color_blue == 255)
    m_color_green > 0 ? ++m_color_green : --m_color_red; 
  
  return *this;
}

Color& Color::operator--()
{
       if(m_color_red == m_color_blue)
         m_color_red == 255 ? --m_color_blue: ++m_color_blue; 
  else if (m_color_green == m_color_red)
    m_color_green == 255 ? --m_color_red : ++m_color_red;
  else if (m_color_blue == m_color_green)
    m_color_blue == 255 ? --m_color_green: ++m_color_green;
  
  else if (m_color_red == 255)
    m_color_blue > 0 ? --m_color_blue : ++m_color_green;
  else if (m_color_green == 255)
    m_color_red > 0 ? --m_color_red: ++m_color_blue;
  else if (m_color_blue == 255)
    m_color_green > 0 ? --m_color_green : ++m_color_red; 

  return *this;
}

Color Color::operator++(int)
{
  Color temp{*this};
  ++(*this);
  return temp;
}

Color Color::operator--(int)
{
  Color temp {*this};
  --(*this);
  return temp;
}


Led::Led()
	: m_color{}
	, m_brightness{0}
	, m_dimmer_brightness{0}
{
}

Led::~Led()
{
}

void Led::SetColor (Color& a_color)
{
  m_color->SetColorRed(a_color.GetColorRed());
  m_color->SetColorGreen(a_color.GetColorGreen());
  m_color->SetColorBlue(a_color.GetColorBlue());
}

Color Led::GetColor()
{
  Color temp_color{};
  return temp_color;
  ///here implementation
}

void Led::SetBrightness(uint8_t a_brightness)
{
  m_brightness = a_brightness;
}

uint8_t Led::GetBrightness()
{
  return m_brightness;
}

LedStrip::LedStrip()
	: m_animation{Animation::fromlefttoright}
	, isdimmerenabled{false}
{
  //isdimmeractive based on pio
}

LedStrip::~LedStrip()
{
}

void LedStrip::SetNumOfLeds(uint8_t a_num)
{
 //increase/decrease vector size
}

uint8_t LedStrip::GetNumOfLeds()
{
// return vector size
  return 0;
}

void LedStrip::SetAnimation(Animation a_animation)
{
  m_animation = a_animation;
}

LedStrip::Animation LedStrip::GetAnimation()
{
  return m_animation;
}

void LedStrip::EnableDimmer()
{
  isdimmerenabled = true;
}

void LedStrip::DisableDimmer()
{
  isdimmerenabled = false;
}

void LedStrip::Show()
{
//here show function
}