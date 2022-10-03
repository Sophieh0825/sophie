#include <iostream>
using namespace std;

int findOptOrders(int weightH , int weightS ,int sumLabor , int sumSupply , int limH , int limS ,int currentSol[] , int itemCount , const double revenue[] , const double labor[] ,const double supply[]);

int findWorst(int itemCount , int weightH , int weightS , const double revenue[] , const double labor[] , const double supply[] , const int currentSol[]);

int main()
{
     double itemCount = 0 , weightH = 0 , weightS = 0 , limH = 0 , limS = 0;
    cin >> itemCount >> limH >> limS;
    double revenue[64] = {0};
    double labor[64] = {0};
    double supply[64] = {0};
    int currentSol[64] = {0};
    double sumLabor = 0 , sumSupply = 0 ,sumRevenue = 0;
    for(int i = 0 ; i < itemCount ; i++)
    {
        cin >> revenue[i];
    }
    for(int i = 0 ; i < itemCount ; i++)
    {
        cin >> labor[i];
        sumLabor += labor[i];
    } 
    for(int i = 0 ; i < itemCount ; i++)
    {
        cin >> supply[i];
        sumSupply += supply[i];
    }
    for(int i = 0 ; i < itemCount ; i++)
    {
        currentSol[i] = 1;   
    }

    int rev  = 0 , maxRev = -1;
  
    for(int h = 0 ; h<=5 ; h++){
        for(int s = 0 ; s<=5 ; s++){

            if (h == 0 && s == 0)
              continue;
          
            rev = findOptOrders(h,s, sumLabor , sumSupply , limH , limS , currentSol , itemCount , revenue , labor , supply) ;
            if(rev > maxRev)
            {
                maxRev = rev;
                weightH = h;
                weightS = s;
            }
        }
    }
    cout << weightH << "," << weightS << "," << maxRev << "\n";
    return 0;
}

int findWorst(int itemCount , int weightH , int weightS , const double revenue[] , const double labor[] , const double supply[] , int currentSol[])
{
    double CP[64] = {0};
    double minCP = 1000000000 , worst = -1 , revWorst = 0;
    for(int i = 0 ; i < itemCount ; i++)
    {
        CP[i] = revenue[i]/((weightH*labor[i])+(weightS*supply[i]));
    }  
    for(int i = 0 ; i < itemCount ; i++)
    {
        if( CP[i] < minCP || (CP[i] == minCP && revenue[i]<revWorst)) 
          {
            if(currentSol[i] == 1)
             {   
                minCP = CP[i];
                revWorst = revenue[i]; 
                worst = i;
              }   
          }
    }     
    
    return worst;
}


int findOptOrders(int weightH , int weightS , int sumLabor , int sumSupply , int limH , int limS ,int currentSol[] , int itemCount , const double revenue[] , const double labor[] ,const double supply[])
{
    int sumRevenue = 0;
    for(int i = 0 ; i<itemCount ; i++)
      {
        currentSol[i] = 1;
      }
    while(sumLabor > limH || sumSupply > limS)
    {
        sumLabor = 0;
        sumSupply = 0;
        
        currentSol[findWorst(itemCount , weightH , weightS , revenue , labor , supply , currentSol)] = 0; 
        
        for(int i = 0 ; i<itemCount ; i++)
        {
            sumLabor += labor[i]*currentSol[i];
            sumSupply += supply[i]*currentSol[i];
        }
    }

    for(int i = 0 ; i<itemCount ; i++)
      {
        sumLabor += labor[i];
      }
    for(int i = 0 ; i<itemCount ; i++)
      {
        sumSupply += supply[i];
      }
    
    for(int i  = 0 ; i < itemCount ; i++)
    {
        sumRevenue += revenue[i]*currentSol[i];
    }
    return sumRevenue;
}
















