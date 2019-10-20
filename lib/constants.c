#include "../headers/constants.h"

int W_WIDTH = 1120;
int W_HEIGHT = 620;
const float PI = 3.1416;
const float TWO_PI = 2 * 3.1416;
const float CIRCLE_GROWTH_SPEED = 0.3;
const float MOUSE_DIST_THRESHOLD = 120;
const float PULL_BACK_DRAG = 1 / (float)25;
const float REPELL_DRAG = 1 / (float)10;
const float ANGLE_BIAS = 40 * 3.1416 / 180;
const int MIN_CIRCLE_RAD = 3;
const int MAX_CIRCLE_RAD = 6;
// const Color COLORS[5] = {
// 		{242, 92, 162},
// 		{3, 50, 191},
// 		{3, 43, 165},
// 		{1, 23, 89},
// 		{10, 158, 216},
// };
// const Color COLORS[5] = {
// 		{171, 4, 242},
// 		{124, 7, 242},
// 		{7, 81, 242},
// 		{34, 216, 183},
// 		{214, 242, 4, 1},
// };
// const Color COLORS[5] = {
// 		{216, 4, 43},
// 		{8, 3, 165},
// 		{4, 216, 36},
// 		{242, 182, 4},
// 		{216, 60, 4},
// };
const Color COLORS[5] = {
		{200, 91, 108},
		{254, 117, 104},
		{252, 202, 108},
		{84, 143, 204},
		{49, 91, 138},
};
