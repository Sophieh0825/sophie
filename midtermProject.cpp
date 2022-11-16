#include <iostream>
using namespace std;

void satisfyOffRequest(int offRequest, int **request, int **schedule);
void arrangeOff(int employeeCnt, int dayCnt, int dayOffDemand, int **schedule, int **demand , int *sortNum, int *offSum, int nightCnt , int shiftType , int maxOfNight);
void arrangeNight(int employeeCnt, int dayCnt, int shiftType, int nightCnt, int maxOfNight, int **shift, int *nightShift, int **schedule);
void arrangeAll(int employeeCnt, int dayCnt, int shiftType, int nightCnt, int **schedule, int *nightShift, int **shift, int& fitCnt);

int main() 
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  // 宣告變數
  int employeeCnt = 0;  // 員工數量
  int dayCnt = 0;       // 一個月有幾天
  int shiftType = 0;    // 班型數
  int dayOffDemand = 0; // 休假需求
  int wUnsatis = 0;     // 未滿足休假需求的權重
  int wOverNight = 0;   // 超額夜班數的權重
  int offRequest = 0;   // 員工休假需求

  cin >> employeeCnt >> dayCnt >> shiftType >> dayOffDemand >> wUnsatis >> wOverNight >> offRequest;

  int **shift = new int *[31]; // 班型[班型數+1][時刻]
  for (int i = 0; i < 31; i++)
    shift[i] = new int[24];

  for (int i = 1; i < shiftType + 1; i++) // 輸入班型(從1開始)
    for (int j = 0; j < 24; j++)
      cin >> shift[i][j];
  for (int i = 0; i < 24; i++) // 輸入第0種班型
    cin >> shift[0][i];

  int **demand = new int *[31]; // 人力需求[天數][時刻]
  for (int i = 0; i < 31; i++)
    demand[i] = new int[24];

  for (int i = 0; i < dayCnt; i++) // 輸入人力需求
    for (int j = 0; j < 24; j++)
      cin >> demand[i][j];

  int **request = new int *[2]; // 休假需求
  for (int i = 0; i < 2; i++)
    request[i] = new int[offRequest];

  for (int i = 0; i < 2; i++) // 輸入員工休假需求
    for (int j = 0; j < offRequest; j++)
      cin >> request[i][j];

  ///// 輸入部分結束 /////

  int **schedule = new int *[employeeCnt];
  for(int i = 0; i < employeeCnt; i++)
    schedule[i] = new int[dayCnt + 1]; // 欲輸出的班表陣列

  for(int i = 0; i < employeeCnt; i++)
    for(int j = 0; j < dayCnt; j++)
      schedule[i][j] = -1; // 初始化

  int nightCnt = 0;
  
  int *nightShift = new int[shiftType + 1];
  for(int i = 0; i < shiftType + 1; i++)
    nightShift[i] = 0;

  int *nightSum = new int [shiftType + 1];
  for(int i = 0; i < shiftType; i++)
    nightSum[i] = 0;

  for(int i = 0 ; i < shiftType + 1 ; i++) // 夜班班型要掃描陣列
    for(int j = 0 ; j < 24 ; j++）
      nightSum[i] += shift[i][j];
      
  for(int i = 0; i < shiftType + 1; i++) // 夜班班型要掃描陣列
  {
    for(int j = 18; j < 24; j++)
    {
      if(shift[i][j] == 1 && nightSum[i] >= 8) // 如果 shift[i][18～23] == 1 開始就是夜班
        nightShift[i] = 1;
    }
  }

  int maxOfNight = 0; // maxOfNight是夜班班型的最後一個班型編號
  for(int i = 0; i < shiftType + 1; i++)
  {
    if(nightShift[i] == 1) 
    {
      nightCnt++; // 夜班班型nightCnt++

      if(i > maxOfNight)
        maxOfNight = i;
    }
  }

  // 計算每一位員工的休假數
  int *offSum = new int[employeeCnt];
  for (int i = 0; i < employeeCnt; i++)
    offSum[i] = 0;
  
  // 計算每一天的缺工人數
  int *totalDemand = new int[dayCnt];
  
  for(int i = 0; i < dayCnt; i++)
    totalDemand[i] = 0;
 
  for(int i = 0; i < dayCnt; i++)
    for(int j = 0; j < 24; j++)
      totalDemand[i] += demand[i][j];

  // 依照所需員工數由大到小排
  int *sortNum = new int[dayCnt];
  int *sortDayDemand = new int[dayCnt];

  for (int i = 0; i < dayCnt; i++)
  {
    sortDayDemand[i] = totalDemand[i];
    sortNum[i] = i;
  }

  for (int i = 1; i < dayCnt; i++)
  {
    for (int j = i; j > 0; j--)
    {
      if (sortDayDemand[j] > sortDayDemand[j - 1]) /////???
      {
        int tmpDemand = 0, tmpNum = 0;
        tmpDemand = sortDayDemand[j - 1];
        sortDayDemand[j - 1] = sortDayDemand[j];
        sortDayDemand[j] = tmpDemand;

        tmpNum = sortNum[j - 1];
        sortNum[j - 1] = sortNum[j];
        sortNum[j] = tmpNum;
      }
      else 
        break;
    }
  }

  int fitCnt = 0;

  satisfyOffRequest(offRequest, request, schedule);
  arrangeOff(employeeCnt, dayCnt, dayOffDemand, schedule, demand , sortNum, offSum, nightCnt ,shiftType ,maxOfNight);
  arrangeNight(employeeCnt, dayCnt, shiftType, nightCnt, maxOfNight, shift, nightShift, schedule);
  arrangeAll(employeeCnt, dayCnt, shiftType, nightCnt, schedule, nightShift, shift, fitCnt);

  for (int i = 0; i < employeeCnt; i++) 
    for (int j = 0; j < dayCnt; j++) 
      if(schedule[i][j] == -3)
        schedule[i][j] = 0;
  
  for (int i = 0; i < employeeCnt; i++) 
  {
    for (int j = 0; j < dayCnt; j++) 
    {
      if(fitCnt == 0 && schedule[i][j] == -1)
        schedule[i][j] = 2;
    }
  }
    
  // 最終輸出的部分
  for (int i = 0; i < employeeCnt; i++) 
  {
    for (int j = 0; j < dayCnt - 1; j++)
      cout << schedule[i][j] << ",";
    
    cout << schedule[i][dayCnt - 1] << "\n";
  }

  return 0;
}

void satisfyOffRequest(int offRequest, int **request, int **schedule) 
{
  // 先滿足最特殊的休假需求, schedule[i][j] = 0;
  for (int k = 0; k < offRequest; k++)
  {
    int i = request[0][k] - 1;
    int j = request[1][k] - 1;
    // j 是第 i 號員工欲休假的日子，因為日子編號從0開始所以要-1
    schedule[i][j] = -3;
  }
}

void arrangeOff(int employeeCnt, int dayCnt, int dayOffDemand, int **schedule, int **demand, int *sortNum, int *offSum , int nightCnt , int shiftType , int maxOfNight) // 安排休假班型
{
  // 讓每個員工做五休二
  // 前28天都排一週二休 共七種休假
  for (int i = 0; i < employeeCnt; i++) 
  {
    for (int j = 0; j < 28; j++) 
    {
      if ((i + 1) % 7 != 0)
      {
        if ((j + 1) % 7 == (i + 1) % 7)
        {
          schedule[i][j] = 0;
          schedule[i][j + 1] = 0;
        }
      } 
      else if ((i + 1) % 7 == 0)
      {
        if ((j + 1) % 7 == 1 || (j + 1) % 7 == 0) 
          schedule[i][j] = 0;
      }
    }
  }
  
  //如果天數大於等於29天 再排其餘的休假
  if (dayCnt >= 29) 
  {
    for (int i = 0; i < employeeCnt; i++) 
    {
      for (int j = 28; j < dayCnt; j++) 
      {
        if ((i + 1) % 7 <= 3 && (i + 1) % 7 != 0)
        {
          if ((j + 1) % 7 == (i + 1) % 7) 
          {
            schedule[i][j] = 0;
            schedule[i][j + 1] = 0;
          }
        }
      }
    }
  }

  for (int i = 0; i < employeeCnt; i++)
  {
    for (int j = 0; j < dayCnt; j++)
    {
      if (schedule[i][j] == 0 || schedule[i][j] == -3)
        offSum[i] += 1;
    }
  }

  for(int i = 0 ; i < employeeCnt ; i++)
  {
    for(int j = dayCnt - 1 ; j >= 1 ; j--)
    {
      if(offSum[i] > dayOffDemand)
      {  
        if(schedule[i][j] == 0 && schedule[i][j - 1] == 0)
          schedule[i][j] = -4;
      }  
    }
  }

  int w = 0;
  for(int i = 0 ; i < employeeCnt ; i++)
  {
    for(int j = 0 ; j < dayCnt ; j++)
    {
      if(schedule[i][j] == -4)
      {
        if ((w % nightCnt) != 0)
          schedule[i][j] = w % nightCnt + (shiftType - nightCnt);
        else if ((w % nightCnt) == 0)
          schedule[i][j] = maxOfNight;

        w += 2;
      }
    }
  }

  // 算每個員工的休假數
  for (int i = 0; i < employeeCnt; i++)
  {
    for (int j = 0; j < dayCnt; j++)
      offSum[i] = 0;
  }
  for (int i = 0; i < employeeCnt; i++)
  {
    for (int j = 0; j < dayCnt; j++)
    {
      if (schedule[i][j] == 0 || schedule[i][j] == -3)
        offSum[i] += 1;
    }
  }

  int m = dayCnt - 1;
  for (int i = 0; i < employeeCnt; i++)
  {
    while (offSum[i] < dayOffDemand)
    {
      if (m < 0)
        m = dayCnt - 1;

      int a = sortNum[m];
      if(schedule[i][a] != 0 && schedule[i][a] != -3)
      {
        schedule[i][a] = 0;
        m--;
        offSum[i]++;
        // cout << i << " " << a << " " << offSum[i] << "+\n";
      }
      else
        m--;
    }
  }
}

void arrangeNight(int employeeCnt, int dayCnt, int shiftType, int nightCnt, int maxOfNight, int **shift, int *nightShift, int **schedule) // 安排夜班班型
{
  for (int i = 0; i < employeeCnt; i++) // 休二完的後一天上夜班
  {
    for (int j = dayCnt - 1; j >= 2; j--)
    {
      if ((schedule[i][j - 1] == 0 && schedule[i][j - 2] == 0) && (schedule[i][j] != -3 && schedule[i][j] != 0))
        schedule[i][j] = -5;
    }
  }

  int w = 0;
  for (int i = 0; i < employeeCnt; i++)
  {
    for (int j = 0; j < dayCnt; j++) 
    {
      if (schedule[i][j] == -5) 
      {
        if ((w % nightCnt) != 0)
          schedule[i][j] = w % nightCnt + (shiftType - nightCnt);
        else if ((w % nightCnt) == 0)
          schedule[i][j] = maxOfNight;

        w += 2;
      }
    }
  }
}

void arrangeAll(int employeeCnt, int dayCnt, int shiftType, int nightCnt, int **schedule, int *nightShift, int **shift, int& fitCnt)
{
  int *halfCnt = new int[shiftType];
  for(int i = 0 ; i < shiftType ; i++)
  {
    for(int j = 0 ; j < 18 ; j++)
    {
      if(shift[i][j] == 1)
        halfCnt[i]++;
    }
  }

  fitCnt = 0;
  for(int i = 0 ; i < shiftType ; i++)
  {
    if(halfCnt[i] >= 8 && nightShift[i] != 1)
    {
      nightShift[i] = 2;
      fitCnt++;
    }
      
  }
  if(fitCnt == 0)
  {
    for(int i = 0; i < shiftType; i++)
      nightShift[i] = 2;
  }

  // 需要先算出nightCnt夜班班型，才可以使用這個function
  int index = 0; // 只是一個為了運算宣告的變數 
  int index2 = 0; // 另一個用來宣告的變數
  for (int j = 0 ; j < dayCnt ; j++)
  {
    for (int i = 0 ; i < employeeCnt ; i++) 
    {
        index = 1;
     
        while(index != 0)
        {
          if(index2 >= shiftType)
            index2 = 0;
          
          if(schedule[i][j] == -1 && nightShift[index2] == 2) // 如果i員工在第j天還沒有安排班型的話
          {
            schedule[i][j] = index2 ;
            index2++;
            index = 0;
            // 日班班型總共有shiftType - nightCnt個
          }
          else if(schedule[i][j] == -1)
            index2++;
          else
            index = 0;
        }
    }
  }
}
