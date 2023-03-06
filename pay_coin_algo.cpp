#include <stdio.h>
#include <math.h>

int coin_five = 20;
int coin_one = 20;


int main() {
  int five = 0,one = 0,cost = 0;
  int countt = 0,debt = 0;
  int status_five = 1,status_one = 1;
  int result[5] = {0,0,1,1,0}; //count_coin_5,count_coin_1,status_5,status_1,debt
  while (1){
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
          printf("debt = %d",debt);
          result[1] = one;
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("count_coin_5 = %d\n",result[0]);
          printf("count_coin_1 = %d\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five;
        printf("No have 1 coin\n");
        printf("debt = %d",debt);
        result[0] = five;
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("count_coin_5 = %d\n",result[0]);
        printf("count_coin_1 = %d\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        break;
      }else { //5 บาทจ่ายได้
        if (five > coin_five) {// 5 ใช้มากกว่าที่มี
          debt = five - coin_five;
          result[0] = coin_five;
          coin_five = 0;
          status_five = 0;
          printf("No have 5 coin and 1 coin\n");
          printf("debt = %d",debt);
          result[1] = one;
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("count_coin_5 = %d\n",result[0]);
          printf("count_coin_1 = %d\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five; 
        printf("No have 1 coin\n");
        printf("debt = %d",debt);
        result[0] = five;
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("count_coin_5 = %d\n",result[0]);
        printf("count_coin_1 = %d\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        break;
      }
    }else if (coin_five <= 0 && coin_one <= 0) { //5 บาทหมด 1 บาทหมด
      coin_five = 0;
      coin_one = 0;
      status_five = 0;
      status_one = 0;
      printf("No have 5 coin and 1 coin\n");
      printf("debt = %d",cost);
      result[0] = five;
      result[1] = one;
      result[2] = status_five;
      result[3] = status_one;
      result[4] = cost;
      printf("count_coin_5 = %d\n",result[0]);
      printf("count_coin_1 = %d\n",result[1]);
      printf("status_5 = %d\n",result[2]);
      printf("status_1 = %d\n",result[3]);
      printf("debt = %d\n",result[4]);
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
        printf("debt = %d",debt);
        result[0] = five;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("count_coin_5 = %d\n",result[0]);
        printf("count_coin_1 = %d\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
        break;
      }
      coin_one = coin_one - one;
      printf("No have 5 coin\n");
      result[0] = five;
      result[1] = one;
      result[2] = status_five;
      result[3] = status_one;
      result[4] = debt;
      printf("count_coin_5 = %d\n",result[0]);
      printf("count_coin_1 = %d\n",result[1]);
      printf("status_5 = %d\n",result[2]);
      printf("status_1 = %d\n",result[3]);
      printf("debt = %d\n",result[4]);
    }else if (coin_five > 0 && coin_one > 0) { //5 บาทเหลือ 1 บาทเหลือ 
      five = floor(cost/5);
      if (five > coin_five) {// 5 ใช้มากกว่าที่มี
        one = cost - (5*coin_five);
        result[0] = five;
        coin_five = 0;
        status_five = 0;
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          result[1] = coin_one;
          coin_one = 0;
          status_one = 0;
          printf("No have 5 coin and 1 coin\n");
          printf("debt = %d",debt);
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("count_coin_5 = %d\n",result[0]);
          printf("count_coin_1 = %d\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);
          break;
        }
        coin_one = coin_one - one;
        printf("No have 5 coin\n");
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("count_coin_5 = %d\n",result[0]);
        printf("count_coin_1 = %d\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
      }else {
        coin_five = coin_five - five;
        one = cost - (5*five);
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          coin_one = 0;
          status_one = 0; 
          printf("No have and 1 coin\n");
          printf("debt = %d",debt);
          result[0] = five;
          result[1] = one;
          result[2] = status_five;
          result[3] = status_one;
          result[4] = debt;
          printf("count_coin_5 = %d\n",result[0]);
          printf("count_coin_1 = %d\n",result[1]);
          printf("status_5 = %d\n",result[2]);
          printf("status_1 = %d\n",result[3]);
          printf("debt = %d\n",result[4]);  
          break;
        }
        coin_one = coin_one - one;
        result[0] = five;
        result[1] = one;
        result[2] = status_five;
        result[3] = status_one;
        result[4] = debt;
        printf("count_coin_5 = %d\n",result[0]);
        printf("count_coin_1 = %d\n",result[1]);
        printf("status_5 = %d\n",result[2]);
        printf("status_1 = %d\n",result[3]);
        printf("debt = %d\n",result[4]);
      }
    }
    printf("Give you 5 = %d coin\n",five); 
    printf("Give you 1 = %d coin\n",one);
    printf("-------------------------------------\n");
    printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
    printf("----------------#Next------------------\n");
  }
}