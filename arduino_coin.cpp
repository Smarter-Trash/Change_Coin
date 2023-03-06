#include <ESP32Servo.h>
#include <stdio.h>
#include <math.h>
//ประกาศตัวแปรแทน Servo
Servo servo_five;
Servo servo_one;

void setup()
{
  servo_five.attach(13); //เหรียญ 5
  servo_one.attach(04); //เหรียญ 1
  int coin_five = 20;
  int coin_one = 20;
}

// 1 == remain, 0 == runout

int Change_Coin(int cost) {
  int five = 0,one = 0;
  int countt = 0,debt = 0;
  int result[5] = {0,0,0,0,0}; //count_coin_5,count_coin_1,status_5,status_1,debt
  while (1){
    printf("-------------------------------------\n");
    if  (coin_five > 0 && coin_one <= 0) { //5 บาทเหลือ 1 บาทหมด
      five = floor(cost/5);
      coin_one = 0;
      if (cost % 5 != 0) {
        if (five > coin_five) {// 5 ใช้มากกว่าที่มี
          debt = cost - (5*coin_five);
          coin_five = 0;
          printf("No have 5 coin and 1 coin\n");
          printf("debt = %d",debt);
          result[0] = 0;
          result[1] = 0;
          result[2] = 
          result[3] = 
          result[4] = 
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five; 
        printf("No have 1 coin\n");
        printf("%d",debt);
        break;
      }else { //5 บาทจ่ายได้
        if (five > coin_five) {// 5 ใช้มากกว่าที่มี
          debt = five - coin_five;
          coin_five = 0;
          printf("No have 5 coin and 1 coin\n");
          printf("%d",debt);
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five; 
        printf("No have 1 coin\n");
        printf("%d",debt);
        break;
      }
    }else if (coin_five <= 0 && coin_one <= 0) { //5 บาทหมด 1 บาทหมด
      coin_five = 0;
      coin_one = 0;
      printf("No have 5 coin and 1 coin\n");
      printf("%d",cost);
      break;
    }else if (coin_five <= 0 && coin_one > 0) { //5 บาทหมด 1 บาทเหลือ
      one = cost;
      coin_five = 0;
      if (one > coin_one) {// 1 บาทที่ต้องใช้มีมากกว่าที่มี
        debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
        coin_one = 0;
        printf("No have 5 coin and 1 coin\n");
        printf("%d",debt);
        break;
      }
      coin_one = coin_one - one;
      printf("No have 5 coin\n");
    }else if (coin_five > 0 && coin_one > 0) { //5 บาทเหลือ 1 บาทเหลือ 
      five = floor(cost/5);
      if (five > coin_five) {// 5 เหลือมากกว่าที่มี
        one = cost - (5*coin_five);
        coin_five = 0;
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          coin_one = 0;
          printf("No have 5 coin and 1 coin\n");
          printf("%d",debt);
          break;
        }
        coin_one = coin_one - one;
        printf("No have 5 coin\n");
      }else {
        coin_five = coin_five - five;
        one = cost - (5*five);
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          coin_one = 0;
          printf("No have and 1 coin\n");
          printf("%d",debt);
          break;
        }
        coin_one = coin_one - one;
      }
    }
    printf("Give you 5 = %d coin\n",five); 
    printf("Give you 1 = %d coin\n",one);
    printf("-------------------------------------\n");
    printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
    printf("------------------#Next-------------------\n");
  }
}

void loop()
{
  int cost,count_five,count_one;
  printf("How much: ");
  scanf("%d",&cost);
  servo_five.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
  delay(1000); // หน่วงเวลา 1000ms
  servo_one.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
  delay(1000); // หน่วงเวลา 1000ms
  servo_five.write(0); // สั่งให้ Servo หมุนไปองศาที่ 0 ปัด
  delay(1000); // หน่วงเวลา 1000ms
  servo_one.write(0); // สั่งให้ Servo หมุนไปองศาที่ 0
  delay(1000); // หน่วงเวลา 1000ms
}