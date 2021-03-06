/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LiquidCrystal.h"
#include <stdbool.h>
#include "Buzzer.h"


#include <stdio.h>
//#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

typedef unsigned char byte;

byte doodler[] = {
    0x00,
    0x04,
    0x15,
    0x0F,
    0x15,
    0x04,
    0x00,
    0x00};

byte stair[] = {
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06};

byte brokenStair[] = {
    0x06,
    0x06,
    0x06,
    0x00,
    0x00,
    0x06,
    0x06,
    0x06};

byte coil[] = {
    0x00,
    0x00,
    0x1F,
    0x15,
    0x15,
    0x1F,
    0x00,
    0x00};

byte hole[] = {
    0x00,
    0x1F,
    0x10,
    0x10,
    0x10,
    0x10,
    0x1F,
    0x00};

byte monster[] = {
    0x0A,
    0x04,
    0x0E,
    0x0A,
    0x0A,
    0x0E,
    0x04,
    0x0A
};

byte shotCharactor[] = {
  0x00,
  0x00,
  0x0E,
  0x0E,
  0x0E,
  0x0E,
  0x00,
  0x00
};

int board[20][4];
int score = 0;
int difficulty = 5;
int doodlerPosition[2] = {0, 0};
int doodlerDisplacementCount = 1;
int downStatus = 0;
int upStatus = 7;
int lastPosition [2];
int newPosition [2];
int realCharactorInCurrentPosition = -1;
int startMoveDown = 0;
int lockMoving = 1;
int isInOverViewPage = 1;
int isInMenu = 0;
int isInMembersPage = 0;
int isGameStarted = 0;
int isShotInScreen = 0;
int shotPosition[2];
int realCharactorInShotPosiotion;


#define EMPTY_CELL_NUM  -1
#define DOODLER_NUM  0
#define STAIR_NUM  1
#define BROKEN_STAIR_NUM  2
#define COIL_NUM  3
#define HOLE_NUM 4
#define MONSTER_NUM  5
#define SHOT_NUM 6
#define REMOVE  0
#define MOVE  1
#define WRITE  2
#define NORMAL_DOWN_STATUS  0
#define MONSTER_DOWN_STATUS  1
#define NORMAL_UP_STATUS 7
#define COIL_UP_STATUS  15
#define LEFT  -1
#define RIGHT  1
char buffer[32];
int x=5234;
int y=1;

void genarateBoard(int blankRow);
/////////////////////////////kepad////////////////////
uint32_t now = 0;

void initBoard(){
	for (int i=0;i<20;i++){
		for (int j=0;j<4;j++){
			board[i][j]=-1;
		}
	}
}

void shot(){
  realCharactorInShotPosiotion = board[doodlerPosition[0] + 2][doodlerPosition[1]];
  setCursor(doodlerPosition[0] +2, doodlerPosition[1]);
  shotPosition[0] = doodlerPosition[0] +2;
  shotPosition[1] = doodlerPosition[1];
  if(realCharactorInShotPosiotion == MONSTER_NUM){
    print(" ");
    board[shotPosition[0]][shotPosition[1]] = EMPTY_CELL_NUM;
    isShotInScreen = 0;
  } else{
    write(SHOT_NUM);
    isShotInScreen = 1;
  }
}

void print1OnScreen(){
	setCursor(11, 1);
	write(-1);
	setCursor(12, 2);
	write(-1);
	setCursor(11, 2);
	write(-1);
	setCursor(10, 2);
	write(-1);
	setCursor(9, 2);
	write(-1);
	setCursor(8, 2);
	write(-1);
	setCursor(7, 2);
	write(-1);
	setCursor(6, 2);
	write(-1);
}

void print2OnScreen(){
	setCursor(12, 0);
	write(-1);
	setCursor(12, 1);
	write(-1);
	setCursor(12, 2);
	write(-1);
	setCursor(12, 3);
	write(-1);
	setCursor(11, 0);
	write(-1);
	setCursor(11, 3);
	write(-1);
	setCursor(10, 3);
	write(-1);
	setCursor(9, 0);
	write(-1);
	setCursor(9, 1);
	write(-1);
	setCursor(9, 2);
	write(-1);
	setCursor(9, 3);
	write(-1);
	setCursor(8, 0);
	write(-1);
	setCursor(7, 0);
	write(-1);
	setCursor(7, 3);
	write(-1);
	setCursor(6, 0);
	write(-1);
	setCursor(6, 1);
	write(-1);
	setCursor(6, 2);
	write(-1);
	setCursor(6, 3);
	write(-1);
}

void print3OnScreen(){
	setCursor(12, 1);
	write(-1);
	setCursor(12, 2);
	write(-1);
	setCursor(12, 3);
	write(-1);
	setCursor(11, 3);
	write(-1);
	setCursor(10, 3);
	write(-1);
	setCursor(9, 1);
	write(-1);
	setCursor(9, 2);
	write(-1);
	setCursor(9, 3);
	write(-1);
	setCursor(8, 3);
	write(-1);
	setCursor(7, 3);
	write(-1);
	setCursor(6, 1);
	write(-1);
	setCursor(6, 2);
	write(-1);
	setCursor(6, 3);
	write(-1);
}

void clearScreen() {
	for (int i = 0 ; i < 20; i++) {
		for(int j = 0; j < 4; j++) {
			setCursor(i, j);
			print(" ");
		}
	}
}

void startGame(){
	isInMenu = 0;
	clearScreen();
	print1OnScreen();
	clearScreen();
	print2OnScreen();
	clearScreen();
	print3OnScreen();
	clearScreen();
	genarateBoard(20);
	isGameStarted = 1;
	lockMoving = 0;
	HAL_TIM_Base_Start_IT(&htim4);
}

void showGameOverView(){
  isGameStarted = 0;
  lockMoving = 1;
  isInOverViewPage = 1;
  clear();
  setCursor(12,1);
  print("Doolde");
  setCursor(12,2);
  print("Jump");
  setCursor(3,1);
  write(DOODLER_NUM);
  setCursor(4,1);
  write(STAIR_NUM);
  setCursor(5,1);
  write(BROKEN_STAIR_NUM);
  setCursor(6,1);
  write(HOLE_NUM);
  setCursor(7,1);
  write(COIL_NUM);
  setCursor(8,1);
  write(MONSTER_NUM);
  setCursor(3,3);
  print("5.Menu");
//  BUZZER_Play_GameOfThrones();
}

void menu(){
  isInOverViewPage = 0;
  isInMembersPage = 0;
  isInMenu = 1;
  clear();
  setCursor(6,0);
  print("2.Start");
  setCursor(6,2);
  print("3.About");
}

void showGroupMembersName(){
  isInMenu = 0;
  isInMembersPage = 1;
  clear();
  setCursor(5,0);
  print("SaeedRahmani");
  setCursor(5,1);
  print("MohammadRaee");
  setCursor(8,3);
  print("6.Menu");
}

void changeBoard(int lastPosition [], int curPosotion [],int charNum , int moveOrRemoveOrWrite){
  if(moveOrRemoveOrWrite == MOVE){
    board[lastPosition[0]][lastPosition[1]] = EMPTY_CELL_NUM;
    board[curPosotion[0]][curPosotion[1]] = charNum;
  } else if(moveOrRemoveOrWrite == REMOVE){
    board[lastPosition[0]][lastPosition[1]] = EMPTY_CELL_NUM;
  } else if(moveOrRemoveOrWrite == WRITE){
    board[curPosotion[0]][curPosotion[1]] = charNum;
  }
}

void horizontalMoving(int direction){
  changeBoard(doodlerPosition,doodlerPosition,EMPTY_CELL_NUM,WRITE);
  setCursor(doodlerPosition[0],doodlerPosition[1]);
  print(" ");
  if(direction == LEFT){
    if(doodlerPosition[1] > 0){
      doodlerPosition[1] -= 1;
    }else {
      doodlerPosition[1] = 3;
    }
  }else {
    if(doodlerPosition[1] < 3){
      doodlerPosition[1] += 1;
    }else {
      doodlerPosition[1] = 0;
    }
  }
  changeBoard(doodlerPosition,doodlerPosition,DOODLER_NUM,WRITE);
  setCursor(doodlerPosition[0],doodlerPosition[1]);
  write(DOODLER_NUM);
}

void Rows_Set_Mode(uint8_t mode)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, mode ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, mode ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, mode ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, mode ? (GPIO_PIN_SET) : (GPIO_PIN_RESET));
}


uint8_t Get_Pressed_Row(uint16_t GPIO_Pin)
{
	Rows_Set_Mode(0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin)==1){
		Rows_Set_Mode(1);
		return 0;

	}
	Rows_Set_Mode(0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin)==1){
		Rows_Set_Mode(1);
		return 1;
	}
	Rows_Set_Mode(0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin)==1){
		Rows_Set_Mode(1);
		return 2;
	}
	Rows_Set_Mode(0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_Pin)==1){
		Rows_Set_Mode(1);
		return 3;
	}
	return 0;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if((HAL_GetTick() - now ) < 600){
		return;
	}
	//LED On board
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);

	int number = 0, row;
	row = Get_Pressed_Row(GPIO_Pin);
	switch(GPIO_Pin)
	{
		case GPIO_PIN_0:{
			number = 4 * row + 1;
			break;
		}

		case GPIO_PIN_1:{
			number = 4 * row + 2;
			break;
		}
		case GPIO_PIN_2:{
			number = 4 * row + 3;
			break;
		}
		case GPIO_PIN_3:{
			number = 4 * row + 4;
			break;
		}
	}
	Rows_Set_Mode(1);
	now = HAL_GetTick();
	if (number==1 && lockMoving == 0){
		horizontalMoving(LEFT);
	}
	else if(number == 2 && isInMenu == 1) {
		startGame();
	}
	else if(number == 3 && isInMenu == 1){
		showGroupMembersName();
	}
	else if (number==4 && lockMoving == 0){
		horizontalMoving(RIGHT);
	}
	else if (number==5 && isInOverViewPage == 1) {
		menu();
	}
	else if(number == 6 && isInMembersPage == 1){
		menu();
	} else if (number==8 && isShotInScreen==0){
		shot();
	}
}
/////////////////////////////end keypad//////////////////

//////////////////////////// 7 Segment ///////////////////
void numberToBCD(int i){
	int x1=i&1;
	int x2=i&2;
	int x3=i&4;
	int x4=i&8;
	if (x1>0) x1=1;
	if (x2>0) x2=1;
	if (x3>0) x3=1;
	if (x4>0) x4=1;

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, x1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, x2);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, x3);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, x4);
}



////////////////////////// end 7 segment//////////////////

uint32_t value = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  //	if(hadc->Instance == ADC1)
  //	{

  value = HAL_ADC_GetValue(hadc);
  int tmp=((int)value)%10;
  difficulty=3;
//  HAL_ADC_Start_IT(&hadc1);
  //	}
}

int getRandom(int maxNum){
  int rand_num= rand() % (maxNum);
  return rand_num;
}

void initialCharactorToBoard(int charCount, int charNum, int blankRow){
  for(int i = 0; i < charCount; i++){
    int sw = 1;
    while(sw){
      int row = getRandom(20);
      int col = getRandom(4);
      if(board[19-row][col] == -1){
        board[19-row][col] = charNum;
        sw = 0;
      }
    }
  }
}

int checkStairInsideDoodler(int accessRowCount){
  int sw = 1;
  for(int i = doodlerPosition[0];i<doodlerPosition[0] + accessRowCount && sw ==1;i++){
    for(int j = 0; j<4 && sw==1 ;j++){
      if(board[i][j]==STAIR_NUM) sw=0;
    }
  }
  if(sw==1) return 0;
  else return 1;
}

bool validateInitializeBoard(int blankRow){
  int sw = 1;
  for(int i = 20-blankRow; i<20 && sw==1; i++){
    if(board[i][0]==HOLE_NUM && board[i][1]==HOLE_NUM && board[i][2]==HOLE_NUM && board[i][3]==HOLE_NUM ){
       sw = 0;
     }
     else if(board[i][0]==MONSTER_NUM && board[i][1]==MONSTER_NUM && board[i][2]==MONSTER_NUM && board[i][3]==MONSTER_NUM ){
       sw = 0;
     }
  }
  if(sw == 1){
    sw = checkStairInsideDoodler(upStatus);
  }
  if(sw == 1) return true;
  else return false;
}

void updateScore(int upCount){
  score += upCount;
}

void changeShot(){
  setCursor(shotPosition[0],shotPosition[1]);
  print(" ");
  shotPosition[0] -= newPosition[0];
  setCursor(shotPosition[0],shotPosition[1]);
  write(SHOT_NUM);
}

void pageUp(){
  if(newPosition[0] != 0){
    for(int i = 0; i < newPosition[0]; i++){
      for(int j = 0; j < 4; j++){
        if(board[i][j] != EMPTY_CELL_NUM){
          board[i][j] = EMPTY_CELL_NUM;
          setCursor(i,j);
          print(" ");
        }
      }
    }
    for(int i=newPosition[0];i<20;i++){
      for(int j =0 ; j<4; j++){
        if(board[i][j] != EMPTY_CELL_NUM){
          setCursor(i,j);
          print(" ");
          setCursor(i-newPosition[0],j);
          write(board[i][j]);
          board[i-newPosition[0]][j]=board[i][j];
          board[i][j] = EMPTY_CELL_NUM;
        }
      }
    }
    if (isShotInScreen==1){
    	changeShot();
    }

    doodlerPosition[0] -= newPosition[0];
    genarateBoard(newPosition[0]);
    updateScore(newPosition[0]+1);
  }
}

void printBoard(int minRow){
  for(int i = minRow; i< 20;i++){
    for(int j = 0; j<4;j++){
      if(board[i][j] != -1){
        setCursor(i,j);
        write(board[i][j]);
      }
    }
  }
}

void genarateBoard(int blankRow) {
  int randomMaxNum = difficulty;
  int stairCount;
  int brokenStairCount;
  int holeCount;
  int monsterCount;
  int coilCount;

  int stairDificaltyScore = 5;
  int brokenStairDificultyScore = -3;
  int holeDificultyScore = -30;
  int coilDificultyScore = 8;
  int monsterDificultyScore = -30;


  while(1){
    stairCount = getRandom(randomMaxNum);
    brokenStairCount = getRandom(randomMaxNum);
    holeCount = getRandom(randomMaxNum);
    coilCount = getRandom(randomMaxNum);
    monsterCount = getRandom(randomMaxNum);

    int difficultyScore = stairCount * stairDificaltyScore + brokenStairCount * brokenStairDificultyScore + holeCount * holeDificultyScore + coilCount * coilDificultyScore + monsterCount * monsterDificultyScore;

    if(difficultyScore < randomMaxNum *(-10)){
      initialCharactorToBoard(stairCount,STAIR_NUM,blankRow);
      initialCharactorToBoard(brokenStairCount,BROKEN_STAIR_NUM,blankRow);
      initialCharactorToBoard(holeCount,HOLE_NUM,blankRow);
      initialCharactorToBoard(coilCount,COIL_NUM,blankRow);
      initialCharactorToBoard(monsterCount,MONSTER_NUM,blankRow);
      if(validateInitializeBoard(blankRow)){
        printBoard(20-blankRow);
        break;
      }
    }
  }
}

void crashEmptyCell(){
  setCursor(lastPosition[0], lastPosition[1]);
  if(startMoveDown == 1){
	  if (realCharactorInCurrentPosition==-1){
		  print(" ");
	  }else{
		  write(realCharactorInCurrentPosition);
	  }
    startMoveDown = 0;
    changeBoard(lastPosition,lastPosition,realCharactorInCurrentPosition,WRITE);
  }
  else {
    print(" ");
    changeBoard(lastPosition,lastPosition,EMPTY_CELL_NUM,WRITE);
  }
  setCursor(newPosition[0], newPosition[1]);
  write(DOODLER_NUM);
  doodlerPosition[0] =  newPosition[0];
  changeBoard(doodlerPosition,doodlerPosition,DOODLER_NUM,WRITE);
}

void crashStair(){
  doodlerDisplacementCount = 1;
  pageUp();
}

void crashBrokenStair(){
  setCursor(lastPosition[0], lastPosition[1]);
  if(startMoveDown == 1){
	  if (realCharactorInCurrentPosition==-1){
		  print(" ");
	  }else{
		  write(realCharactorInCurrentPosition);
	  }
      startMoveDown = 0;
      changeBoard(lastPosition,lastPosition,realCharactorInCurrentPosition,WRITE);
  }
  else {
      print(" ");
      changeBoard(lastPosition,lastPosition,EMPTY_CELL_NUM,WRITE);
  }
  setCursor(newPosition[0], newPosition[1]);
  write(DOODLER_NUM);
  doodlerPosition[0] =  newPosition[0];
  changeBoard(doodlerPosition,doodlerPosition,DOODLER_NUM,WRITE);
}

void crashCoil(){
  doodlerDisplacementCount = 1;
  upStatus = COIL_UP_STATUS;
  pageUp();
}

void gameOver(){
	lockMoving = 1;
    HAL_TIM_Base_Stop_IT(&htim4);
	clear();
	setCursor(5,1);
	print("Game Over !");
	clearScreen();
	setCursor(8,1);
	print("score: ");
	sprintf(buffer,"%d",score);
	setCursor(15,1);
	print(buffer);
    BUZZER_Play_Doom();
}

void crashHole(){
  gameOver();
}

void crashMonster(){
  lockMoving = 1;
  doodlerDisplacementCount = -1;
  downStatus = MONSTER_DOWN_STATUS;
}

void checkDownChange(){
  if(newPosition[0] == -1){
    gameOver();
  }
  else{
    switch( board[newPosition[0]][newPosition[1]] ){
      case EMPTY_CELL_NUM: {
        crashEmptyCell();
        break;
      } case STAIR_NUM: {
        crashStair();
        break;
      } case BROKEN_STAIR_NUM :{
        crashBrokenStair();
        break;
      } case COIL_NUM : {
        crashCoil();
        break;
      } case HOLE_NUM : {
        crashHole();
        break;
      } case MONSTER_NUM : {
        crashMonster();
        break;
      }
    }
  }
}

void setLastAndNewPosition(int moveDirecrion){
  lastPosition[0] = doodlerPosition[0];
  lastPosition[1] = doodlerPosition[1];
  newPosition[0] = doodlerPosition[0]+moveDirecrion ;
  newPosition[1] = doodlerPosition[1];
}

void normalMoveDown(){
  setLastAndNewPosition(-1);
  checkDownChange();
}

void crashMonsterMoveDown(){
  setLastAndNewPosition(-1);
  if(newPosition[0] < 0){
    gameOver();
  } else{
    setCursor(lastPosition[0], lastPosition[1]);
    print(" ");
    setCursor(newPosition[0], newPosition[1]);
    write(DOODLER_NUM);
    doodlerPosition[0] =  newPosition[0];
  }
}

void checkUpChange(){
  if(doodlerDisplacementCount == 1){
	  setCursor(lastPosition[0], lastPosition[1]);
	  print(" ");
	  changeBoard(lastPosition,lastPosition,EMPTY_CELL_NUM,WRITE);
	  realCharactorInCurrentPosition = board[newPosition[0]][newPosition[1]];
	  setCursor(newPosition[0], newPosition[1]);
	  write(DOODLER_NUM);
	  doodlerPosition[0] =  newPosition[0];
	  changeBoard(newPosition,newPosition,DOODLER_NUM,WRITE);
   }else if(realCharactorInCurrentPosition == HOLE_NUM){
		crashHole();
   }else if(realCharactorInCurrentPosition == MONSTER_NUM){
		crashMonster();
   }else {
	  setCursor(lastPosition[0], lastPosition[1]);
	  changeBoard(lastPosition,lastPosition,realCharactorInCurrentPosition,WRITE);
	  if (realCharactorInCurrentPosition==-1){
		  print(" ");
	  }else{
		  write(realCharactorInCurrentPosition);
	  }
	  realCharactorInCurrentPosition = board[newPosition[0]][newPosition[1]];
	  setCursor(newPosition[0], newPosition[1]);
	  write(DOODLER_NUM);
	  doodlerPosition[0] =  newPosition[0];
	  changeBoard(newPosition,newPosition,DOODLER_NUM,WRITE);
  }
}

void moveUp(int countMoveUP){
  setLastAndNewPosition(1);
  checkUpChange();
  doodlerDisplacementCount += 1;
  if (doodlerDisplacementCount == countMoveUP) {
    doodlerDisplacementCount = -1;
    startMoveDown = 1;
  }
}

void changeDoodlerPosition(int moveDirecrion) {
  if (moveDirecrion == 1) {
    switch (upStatus){
      case NORMAL_UP_STATUS:{
        moveUp(8);
        break;
      }case COIL_UP_STATUS : {
        moveUp(16);
        break;
      }
    }
  }
  else if (moveDirecrion == -1) {
    switch(downStatus){
      case NORMAL_DOWN_STATUS: {
        normalMoveDown();
        break;
      }
      case MONSTER_DOWN_STATUS: {
        crashMonsterMoveDown();
        break;
      }
    }
  }
}

void moveShot(){
  setCursor(shotPosition[0],shotPosition[1]);
  if(realCharactorInShotPosiotion == -1){
    print(" ");
  } else {
    write(realCharactorInShotPosiotion);
  }
  shotPosition[0] += 1;
  if(shotPosition[0] < 20){
    realCharactorInShotPosiotion = board[shotPosition[0]][shotPosition[1]];
    setCursor(shotPosition[0],shotPosition[1]);
    if(realCharactorInShotPosiotion == MONSTER_NUM){
      print(" ");
      board[shotPosition[0]][shotPosition[1]] = EMPTY_CELL_NUM;
      isShotInScreen = 0;
    } else {
      write(SHOT_NUM);
    }
  } else {
    isShotInScreen = 0;
  }
}

void moveDoodler() {
  if (doodlerDisplacementCount >= 1) {
    changeDoodlerPosition(1);
  }
  else {
    changeDoodlerPosition(-1);
  }
  if(isShotInScreen==1){
  	moveShot();
  }
}

bool stopFlag = true;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {


  if (htim->Instance == TIM3) // TIM3 for controlling the buzzer
  {


	  x=score+difficulty*1000;


	  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
//   0
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, 0);

	  //9
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8, 1);
	  numberToBCD(x%10);
	  y=x/10;
	  HAL_Delay(5);

	  //8
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9, 1);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,1);
	  numberToBCD(y%10);
	  y=y/10;
	  HAL_Delay(5);

	  //7
//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12,0);decimal
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, 1);
	  numberToBCD(y%10);
	  y=y/10;
	  HAL_Delay(5);

	  //6
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, 1);
	  numberToBCD(y%10);
	  y=y/10;
	  HAL_Delay(5);

//	if(stopFlag)
//	{
//		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
//		stopFlag = false;
//	}
//	else
//	{
//		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
//		stopFlag = true;
//	}
  }
  if (htim->Instance == TIM4){
	  if(isGameStarted == 1){
		  moveDoodler();
	  }

   }
  if (htim->Instance == TIM1){
	  if(isShotInScreen==1){
		  moveShot();
	  }
   }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USB_PCD_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  //  bool x = false;

  Rows_Set_Mode(1);
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  LiquidCrystal(GPIOD, GPIO_PIN_0, 0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7);
  begin(20, 4);
  createChar(DOODLER_NUM, doodler);
  createChar(STAIR_NUM, stair);
  createChar(BROKEN_STAIR_NUM, brokenStair);
  createChar(COIL_NUM, coil);
  createChar(HOLE_NUM, hole);
  createChar(MONSTER_NUM, monster);
  setCursor(0, 0);
  createChar(SHOT_NUM,shotCharactor);
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  HAL_ADC_Start_IT(&hadc1);
//  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

//  htim2.Instance->CCR3 = 50;

  initBoard();
  BUZZER_SetTIM(&htim2, TIM_CHANNEL_3);
  board[0][2] = DOODLER_NUM;
  doodlerPosition[0] = 0;
  doodlerPosition[1] = 2;
  srand(value);
  showGameOverView();
//  genarateBoard(20);


//  for(int i = 0 ; i < 30; i++){
//	  HAL_Delay(1000);
//	  moveDoodler();
//  }

  HAL_TIM_Base_Start_IT(&htim3);
//  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_TIM1|RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_6B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 720-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 72-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 10000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 7200-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MEMS_INT3_Pin MEMS_INT4_Pin */
  GPIO_InitStruct.Pin = MEMS_INT3_Pin|MEMS_INT4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD11 PD12 PD13 PD14
                           PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD4 PD5
                           PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: print("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
