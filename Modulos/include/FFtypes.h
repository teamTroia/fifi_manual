#pragma once
#include "opencv2/opencv.hpp"

#define ffORANGE 0
#define	ffBLUE 1
#define	ffYELLOW 2
#define	ffGREEN 3
#define	ffRED 4
#define	ffPINK 5

#define ffENABLE_CAM 1
#define ffSET_TEAM 2
#define ffSET_PLOTS 4

#define ffPLOT_WAY 1
#define ffPLOT_BALL 2 
#define ffPLOT_MYROBOTS 4
#define ffPLOT_OPPONENTS 8
#define ffPLOT_DESTINY 16

#define ffSIDE_LEFT 1
#define ffSIDE_RIGHT 2

#define ffGOLEIRO 0
#define ffZAGUEIRO 1
#define ffATACANTE 2
#define ffHYBRID 3


struct objectInfo {
	cv::Point2f position = { 0,0 };
	cv::Point2f speed = { 0,0 };
	double psi;
	double psiSpeed;
};

struct pdiObjectInfo : objectInfo {
	cv::Point2f primaryColorPos = { 0,0 };
	cv::Point2f secondaryColorPos = { 0,0 };
	bool found = false;
};

typedef pdiObjectInfo pdiRobot;
typedef pdiObjectInfo pdiBall;
struct pdiPack {
	pdiRobot myRobots[3];
	pdiRobot opRobots[3];
	pdiBall ball;
};

struct infoMyRobot : objectInfo {
	bool PID = false;
	bool angImporta = false;
	bool desvio = false;
	int giro = 0;
};

typedef objectInfo infoOpRobot;
typedef objectInfo infoBall;
struct infoPack {
	infoMyRobot myRobots[3];
	infoOpRobot opRobots[3];
	infoBall ball;
};

struct settingVision {
	cv::Point2f virtualField[34];
	cv::Point2f realField[34];
	bool useCamera = true;
	int teamColor = ffBLUE;
	int opColor = ffYELLOW;
	char plots = 0;
	bool detectaAdv = false;
};

struct settingGlobal {
	int tCiclo = 0;
};