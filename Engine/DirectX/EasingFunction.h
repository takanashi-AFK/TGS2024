#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <map>
#include <string>
#include <functional>

using namespace DirectX;
using std::function;
using std::string;
using std::map;

namespace Direct3D
{
    map<string, function<double(double)>> EaseFunc
    {
        {"InSine",    [](double t) { return (sin(XM_PIDIV2 * t));        }},
        {"OutSine",   [](double t) { return (1 + sin(XM_PIDIV2 * (--t))); }},
        {"InOutSine", [](double t) {  return 0.5 * (1 + sin(XM_PI * (t - 0.5))); }},
        {"InQuad",    [](double t) {  return t * t; }},
        {"OutQuad",    [](double t) { return t * (2 - t); }},
        {"InOutQuad",   [](double t) { return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1; }},
        {"InCubic",     [](double t) { return t * t * t; }},
        {"OutCubic",    [](double t) { return 1 + (--t) * t * t; }},
        {"InOutCubic",  [](double t) { return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t); }},
        {"InQuart",     [](double t) {   t *= t; return t * t; }},
        {"OutQuart",    [](double t) {   t = (--t) * t; return 1 - t * t; }},
        {"InOutQuart",  [](double t) { if (t < 0.5) { t *= t; return 8 * t * t; }
                                       else { t = (--t) * t; return 1 - 8 * t * t; }}},
        {"InQuint",     [](double t) { double t2 = t * t; return t * t2 * t2; }},
        {"InOutQuint",  [](double t) { double t2; if (t < 0.5) { t2 = t * t; return 16 * t * t2 * t2; }
                                         else { t2 = (--t) * t; return 1 + 16 * t * t2 * t2; }}},
        {"InExpo",      [](double t) { return (pow(2, 8 * t) - 1) / 255; }},
        {"OutExpo",     [](double t) { return 1 - pow(2, -8 * t); }},
        {"InOutExpo",   [](double t) {if (t < 0.5) { return (pow(2, 16 * t) - 1) / 510; }
                                      else { return 1 - 0.5 * pow(2, -16 * (t - 0.5)); }}},
        {"InCirc",      [](double t) { return 1 - sqrt(1 - t); }},
        {"OutCirc",     [](double t) { return sqrt(t); }},
        {"InOutCirc",   [](double t) { if (t < 0.5) { return (1 - sqrt(1 - 2 * t)) * 0.5; }
                                       else { return (1 + sqrt(2 * t - 1)) * 0.5; }}},
        {"InBack",      [](double t) { return t * t * (2.70158 * t - 1.70158); }},
        {"OutBack",     [](double t) { return 1 + (--t) * t * (2.70158 * t + 1.70158); }},
        {"InOutBack",   [](double t) { if (t < 0.5) { return t * t * (7 * t - 2.5) * 2; }
                                       else { return 1 + (--t) * t * 2 * (7 * t + 2.5); }}},
        {"InElastic",   [](double t) { double t2 = t * t; return t2 * t2 * sin(t * XM_PI * 4.5); }},
        {"OutElastic",  [](double t) { double t2 = (t - 1) * (t - 1); return 1 - t2 * t2 * cos(t * XM_PI * 4.5); }},
        {"InOutElastic",[](double t) { double t2; if (t < 0.45) { t2 = t * t; return 8 * t2 * t2 * sin(t * XM_PI * 9); }
                                       else if (t < 0.55) { return 0.5 + 0.75 * sin(t * XM_PI * 4); }
                                       else { t2 = (t - 1) * (t - 1); return 1 - 8 * t2 * t2 * sin(t * XM_PI * 9); }}},
        {"InBounce",    [](double t) { return pow(2, 6 * (t - 1)) * abs(sin(t * XM_PI * 3.5)); }},
        {"OutBounce",   [](double t) { return 1 - pow(2, -6 * t) * abs(cos(t * XM_PI * 3.5)); }},
        {"InOutBounce", [](double t) { if (t < 0.5) { return 8 * pow(2, 8 * (t - 1)) * abs(sin(t * XM_PI * 7)); } else { return 1 - 8 * pow(2, -8 * t) * abs(sin(t * XM_PI * 7)); }}}
    };
};
