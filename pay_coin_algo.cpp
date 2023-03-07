#include <stdio.h>
#include <math.h>

int coin_five = 20;
int coin_one = 20;
int status_five;
int status_one;
int roundd = 0;


int main() {
  int result[5] = {0,0,1,1,0}; //count_coin_5,count_coin_1,status_5,status_1,debt
  while (1){
    int five = 0,one = 0,cost = 0;
    int countt = 0,debt = 0;
    if (roundd == 0) {
      printf("status_five: ");
      scanf("%d",&status_five);
      printf("status_one: ");
      scanf("%d",&status_one);
    }
    printf("How much: ");
    scanf("%d",&cost);
    printf("-------------------------------------\n");
    if  (coin_five > 0 && coin_one <= 0) { //5 บาทเหลือ 1 บาทหมด
      five = floor(cost/5);
      coin_one = 0;
      status_one = 0;
      if (cost % 5 != 0) {
        if (five > coin_five) {// 5 ใช้มากกว่าที่มี
          debt = cost - (5*coin_five);
          result[0] = coin_five;
          coin_five = 0;
          status_five = 0;
          printf("No have 5 coin and 1 coin\n");
          roundd = 0;
          result[1] = one;
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("Give you 5 = %d coin\n",result[0]);
          printf("Give you 1 = %d coin\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n");
          //return result;
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five;
        if (coin_five == 0) {
          status_five = 0;
        }
        printf("No have 1 coin\n");
        roundd++;
        result[0] = five;
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("Give you 5 = %d coin\n",result[0]);
        printf("Give you 1 = %d coin\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        //return result;
        break;
      }else { //5 บาทจ่ายได้
        if (five > coin_five) {// 5 ใช้มากกว่าที่มี
          debt = five - coin_five;
          result[0] = coin_five;
          coin_five = 0;
          status_five = 0;
          printf("No have 5 coin and 1 coin\n");
          roundd = 0;
          result[1] = one;
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("Give you 5 = %d coin\n",result[0]);
          printf("Give you 1 = %d coin\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n");
          //return result;
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five; 
        if (coin_five == 0) {
          status_five = 0;
        }
        printf("No have 1 coin\n");
        roundd++;
        result[0] = five;
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("Give you 5 = %d coin\n",result[0]);
        printf("Give you 1 = %d coin\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        //return result;
        break;
      }
    }else if (coin_five <= 0 && coin_one <= 0) { //5 บาทหมด 1 บาทหมด
      coin_five = 0;
      coin_one = 0;
      status_five = 0;
      status_one = 0;
      printf("No have 5 coin and 1 coin\n");
      roundd = 0;
      result[0] = five;
      result[1] = one;
      result[2] = status_five;
      result[3] = status_one;
      result[4] = cost;
      printf("Give you 5 = %d coin\n",result[0]);
      printf("Give you 1 = %d coin\n",result[1]);
      printf("status_5 = %d\n",result[2]);
      printf("status_1 = %d\n",result[3]);
      printf("debt = %d\n",result[4]);
      printf("-------------------------------------\n");
      printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
      printf("----------------#Next------------------\n");
      //return result;
      break;
    }else if (coin_five <= 0 && coin_one > 0) { //5 บาทหมด 1 บาทเหลือ
      one = cost;
      coin_five = 0;
      status_five = 0;
      if (one > coin_one) {// 1 บาทที่ต้องใช้มีมากกว่าที่มี
        debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
        result[1] = coin_one;
        coin_one = 0;
        status_one = 0;
        printf("No have 5 coin and 1 coin\n");
        roundd = 0;
        result[0] = five;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("Give you 5 = %d coin\n",result[0]);
        printf("Give you 1 = %d coin\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        //return result;
        break;
      }
      coin_one = coin_one - one;
      if (coin_one == 0) {
        status_one = 0;
      }
      printf("No have 5 coin\n");
      roundd++;
      result[0] = five;
      result[1] = one;
      result[2] = status_five;
      result[3] = status_one;
      result[4] = debt;
      printf("Give you 5 = %d coin\n",result[0]);
      printf("Give you 1 = %d coin\n",result[1]);
      printf("status_5 = %d\n",result[2]);
      printf("status_1 = %d\n",result[3]);
      printf("debt = %d\n",result[4]);
      printf("-------------------------------------\n");
      printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
      printf("----------------#Next------------------\n");
      //return result;
    }else if (coin_five > 0 && coin_one > 0) { //5 บาทเหลือ 1 บาทเหลือ 
      five = floor(cost/5);
      if (five > coin_five) {// 5 ใช้มากกว่าที่มี
        one = cost - (5*coin_five);
        result[0] = coin_five;
        coin_five = 0;
        status_five = 0;
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          result[1] = coin_one;
          coin_one = 0;
          status_one = 0;
          printf("No have 5 coin and 1 coin\n");
          roundd = 0;
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("Give you 5 = %d coin\n",result[0]);
          printf("Give you 1 = %d coin\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n");
          //return result;
          break;
        }
        coin_one = coin_one - one;
        if (coin_one == 0) {
          status_one = 0;
        }
        printf("No have 5 coin\n");
        roundd++;
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("Give you 5 = %d coin\n",result[0]);
        printf("Give you 1 = %d coin\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        //return result;
      }else {
        coin_five = coin_five - five;
        if (coin_five == 0) {
          status_five = 0;
        }
        one = cost - (5*five);
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          result[1] = coin_one;
          coin_one = 0;
          status_one = 0; 
          printf("No have and 1 coin\n");
          roundd++;
          result[0] = five;
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("Give you 5 = %d coin\n",result[0]);
          printf("Give you 1 = %d coin\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n");  
          //return result;
          break;
        }
        coin_one = coin_one - one;
        if (coin_one == 0){
          status_one = 0;
        }
        roundd++;
        result[0] = five;
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("Give you 5 = %d coin\n",result[0]);
        printf("Give you 1 = %d coin\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        //return result;
      }
    } 
  }
}