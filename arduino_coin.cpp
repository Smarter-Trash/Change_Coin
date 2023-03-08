#include <ESP32Servo.h>
//#include <stdio.h>
#include <math.h>
//ประกาศตัวแปรแทน Servo
Servo servo_five;
Servo servo_one;
int coin_five = 20;
int coin_one = 20;
int status_five = 1;
int status_one = 1;
int roundd;
int cost = 24;
int ans[5] = {0,0,0,0,0};//count_coin_5,count_coin_1,status_5,status_1,debt

void setup()
{
  Serial.begin(115200);
  servo_five.attach(13); //เหรียญ 5
  servo_one.attach(04); //เหรียญ 1
  servo_five.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
  delay(1000); // หน่วงเวลา 1000ms
  servo_one.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
  delay(1000); // หน่วงเวลา 1000ms
}

void loop()
{
  //printf("status_five: ");
  //scanf("%d",&status_five);
  //printf("status_one: ");
  //scanf("%d",&status_one);
  //printf("How much: ");
  //scanf("%d",&cost);
  Change_Coin();
  for(int i=0;i<ans[0];i++) {
    servo_five.write(0); // สั่งให้ Servo หมุนไปองศาที่ 0 ปัด
    delay(1000); // หน่วงเวลา 1000ms
    servo_five.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
    delay(1000); // หน่วงเวลา 1000ms
    printf("count_coin_5 = %d\n",i+1);
  }  
  for(int j=0;j<ans[1];j++) {
    servo_one.write(0); // สั่งให้ Servo หมุนไปองศาที่ 0
    delay(1000); // หน่วงเวลา 1000ms
    servo_one.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
    delay(1000); // หน่วงเวลา 1000ms
    printf("count_coin_1 = %d\n",j+1);
  }
  printf("status_55 = %d\n",ans[2]);
  printf("status_11 = %d\n",ans[3]);
  printf("debtt = %d\n",ans[4]);
  delay(5000);
}

void Change_Coin() {
  /*
  ans[0]=3;
  ans[1]=1;  
  ans[2]=0;  
  ans[3]=0;  
  ans[4]=0;  
  */
  while (1){
    int five = 0,one = 0;
    int countt = 0,debt = 0;
    if (roundd == 0) {
      if (status_one == 0) {
        status_one = 1;
        coin_one = 20;
      }
      if (status_five == 0) {
        status_five = 1;
        coin_five = 20;
      }
      //scanf("%d",&status_five);
      //scanf("%d",&status_one); //เปลี่ยนเป็นรับค่าจากบอร์ดอื่น
      printf("status_five: %d",status_five);
      printf("status_one: %d",status_one);
      printf("coin_five: %d",coin_five);
      printf("coin_one: %d",coin_one);
    }
    if  (coin_five > 0 && coin_one <= 0) { //5 บาทเหลือ 1 บาทหมด
      five = floor(cost/5);
      coin_one = 0;
      status_one = 0;
      if (cost % 5 != 0) {
        if (five > coin_five) {// 5 ใช้มากกว่าที่มี
          debt = cost - (5*coin_five);
          ans[0] = coin_five;
          coin_five = 0;
          status_five = 0;
          printf("No have 5 coin and 1 coin\n");
          roundd = 0;
          ans[1] = one;
          ans[2] = status_five;
          ans[3] = status_one;
          ans[4] = debt;
          printf("Give you 5 = %d coin\n",ans[0]);
          printf("Give you 1 = %d coin\n",ans[1]);
          printf("status_5 = %d\n",ans[2]);
          printf("status_1 = %d\n",ans[3]);
          printf("debt = %d\n",ans[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n");
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five;
        if (coin_five == 0) {
          status_five = 0;
        }
        printf("No have 1 coin\n");
        roundd++;
        ans[0] = five;
        ans[1] = one;
        ans[2] = status_five;
        ans[3] = status_one;
        ans[4] = debt;
        printf("Give you 5 = %d coin\n",ans[0]);
        printf("Give you 1 = %d coin\n",ans[1]);
        printf("status_5 = %d\n",ans[2]);
        printf("status_1 = %d\n",ans[3]);
        printf("debt = %d\n",ans[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        break;
      }else { //5 บาทจ่ายได้
        if (five > coin_five) {// 5 ใช้มากกว่าที่มี
          debt = five - coin_five;
          ans[0] = coin_five;
          coin_five = 0;
          status_five = 0;
          printf("No have 5 coin and 1 coin\n");
          roundd = 0;
          ans[1] = one;
          ans[2] = status_five;
          ans[3] = status_one;
          ans[4] = debt;
          printf("Give you 5 = %d coin\n",ans[0]);
          printf("Give you 1 = %d coin\n",ans[1]);
          printf("status_5 = %d\n",ans[2]);
          printf("status_1 = %d\n",ans[3]);
          printf("debt = %d\n",ans[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n");
          break;
        }
        debt = cost - (five*5);
        coin_five = coin_five-five; 
        if (coin_five == 0) {
          status_five = 0;
        }
        printf("No have 1 coin\n");
        roundd++;
        ans[0] = five;
        ans[1] = one;
        ans[2] = status_five;
        ans[3] = status_one;
        ans[4] = debt;
        printf("Give you 5 = %d coin\n",ans[0]);
        printf("Give you 1 = %d coin\n",ans[1]);
        printf("status_5 = %d\n",ans[2]);
        printf("status_1 = %d\n",ans[3]);
        printf("debt = %d\n",ans[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        break;
      }
    }else if (coin_five <= 0 && coin_one <= 0) { //5 บาทหมด 1 บาทหมด
      coin_five = 0;
      coin_one = 0;
      status_five = 0;
      status_one = 0;
      printf("No have 5 coin and 1 coin\n");
      roundd = 0;
      ans[0] = five;
      ans[1] = one;
      ans[2] = status_five;
      ans[3] = status_one;
      ans[4] = cost;
      printf("Give you 5 = %d coin\n",ans[0]);
      printf("Give you 1 = %d coin\n",ans[1]);
      printf("status_5 = %d\n",ans[2]);
      printf("status_1 = %d\n",ans[3]);
      printf("debt = %d\n",ans[4]);
      printf("-------------------------------------\n");
      printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
      printf("----------------#Next------------------\n");
      break;
    }else if (coin_five <= 0 && coin_one > 0) { //5 บาทหมด 1 บาทเหลือ
      one = cost;
      coin_five = 0;
      status_five = 0;
      if (one > coin_one) {// 1 บาทที่ต้องใช้มีมากกว่าที่มี
        debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
        ans[1] = coin_one;
        coin_one = 0;
        status_one = 0;
        printf("No have 5 coin and 1 coin\n");
        roundd = 0;
        ans[0] = five;
        ans[2] = status_five;
        ans[3] = status_one;
        ans[4] = debt;
        printf("Give you 5 = %d coin\n",ans[0]);
        printf("Give you 1 = %d coin\n",ans[1]);
        printf("status_5 = %d\n",ans[2]);
        printf("status_1 = %d\n",ans[3]);
        printf("debt = %d\n",ans[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        break;
      }
      coin_one = coin_one - one;
      if (coin_one == 0) {
        status_one = 0;
      }
      printf("No have 5 coin\n");
      roundd++;
      ans[0] = five;
      ans[1] = one;
      ans[2] = status_five;
      ans[3] = status_one;
      ans[4] = debt;
      printf("Give you 5 = %d coin\n",ans[0]);
      printf("Give you 1 = %d coin\n",ans[1]);
      printf("status_5 = %d\n",ans[2]);
      printf("status_1 = %d\n",ans[3]);
      printf("debt = %d\n",ans[4]);
      printf("-------------------------------------\n");
      printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
      printf("----------------#Next------------------\n");
      break;
    }else if (coin_five > 0 && coin_one > 0) { //5 บาทเหลือ 1 บาทเหลือ 
      five = floor(cost/5);
      if (five > coin_five) {// 5 ใช้มากกว่าที่มี
        one = cost - (5*coin_five);
        ans[0] = coin_five;
        coin_five = 0;
        status_five = 0;
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          ans[1] = coin_one;
          coin_one = 0;
          status_one = 0;
          printf("No have 5 coin and 1 coin\n");
          roundd = 0;
          ans[2] = status_five;
          ans[3] = status_one;
          ans[4] = debt;
          printf("Give you 5 = %d coin\n",ans[0]);
          printf("Give you 1 = %d coin\n",ans[1]);
          printf("status_5 = %d\n",ans[2]);
          printf("status_1 = %d\n",ans[3]);
          printf("debt = %d\n",ans[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n");
          break;
        }
        coin_one = coin_one - one;
        if (coin_one == 0) {
          status_one = 0;
        }
        printf("No have 5 coin\n");
        roundd++;
        ans[1] = one;
        ans[2] = status_five;
        ans[3] = status_one;
        ans[4] = debt;
        printf("Give you 5 = %d coin\n",ans[0]);
        printf("Give you 1 = %d coin\n",ans[1]);
        printf("status_5 = %d\n",ans[2]);
        printf("status_1 = %d\n",ans[3]);
        printf("debt = %d\n",ans[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        break;
      }else {
        coin_five = coin_five - five;
        if (coin_five == 0) {
          status_five = 0;
        }
        one = cost - (5*five);
        if (one > coin_one) {
          debt = one - coin_one; //มากกว่าเท่าไหร่ = ต้องจ่ายครั้งหน้า
          ans[1] = coin_one;
          coin_one = 0;
          status_one = 0; 
          printf("No have and 1 coin\n");
          roundd++;
          ans[0] = five;
          ans[2] = status_five;
          ans[3] = status_one;
          ans[4] = debt;
          printf("Give you 5 = %d coin\n",ans[0]);
          printf("Give you 1 = %d coin\n",ans[1]);
          printf("status_5 = %d\n",ans[2]);
          printf("status_1 = %d\n",ans[3]);
          printf("debt = %d\n",ans[4]);
          printf("-------------------------------------\n");
          printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
          printf("----------------#Next------------------\n"); 
          break; 
        }
        coin_one = coin_one - one;
        if (coin_one == 0){
          status_one = 0;
        }
        roundd++;
        ans[0] = five;
        ans[1] = one;
        ans[2] = status_five;
        ans[3] = status_one;
        ans[4] = debt;
        printf("Give you 5 = %d coin\n",ans[0]);
        printf("Give you 1 = %d coin\n",ans[1]);
        printf("status_5 = %d\n",ans[2]);
        printf("status_1 = %d\n",ans[3]);
        printf("debt = %d\n",ans[4]);
        printf("-------------------------------------\n");
        printf("the rest 5 = %d coin and 1 = %d coin\n",coin_five,coin_one);
        printf("----------------#Next------------------\n");
        break;
      }
    } 
  }
}