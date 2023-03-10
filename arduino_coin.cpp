#include <ESP32Servo.h>
//#include <stdio.h>
#include <math.h>
#include <esp_now.h>
#include <WiFi.h>

//ประกาศตัวแปรแทน Servo
Servo servo_five;
Servo servo_one;
int coin_five = 20;
int coin_one = 20;
int status_five = 1;
int status_one = 1;
int roundd;
int cost;
int ans[5] = {0,0,0,0,0};//count_coin_5,count_coin_1,status_5,status_1,debt

// REPLACE WITH THE RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t NinaAddress[] = {0x3C, 0x61, 0x05, 0x03, 0x42, 0x70};
uint8_t NunAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t ViewAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct pay_coin { //รับจากพัช
  int state;
  int cost;
}pay_coin;

typedef struct call_end { //ส่งให้นีน่า
  int state;
}call_end;

typedef struct have_bebt { //ส่งให้นัน
  int state;
  int debt;
}have_bebt;


typedef struct state_coin { //ส่งให้วิว อาจจะรับจากวิวด้วย
  int state;
  int state_1;
  int state_5;
}state_coin;

// Create a struct_message called myData
pay_coin Datacost;
call_end ending;
have_bebt hbedt;
state_coin scoin;

// Create peer interface
esp_now_peer_info_t peerInfo;

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  if (mac_addr[0] == 0x3C && mac_addr[1] == 0x61 && mac_addr[2] == 0x05 && mac_addr[3] == 0x03 && mac_addr[4] == 0x68 && mac_addr[5] == 0x74) {//ยังไม่ใช่ของพัช
    memcpy(&Datacost, incomingData, sizeof(Datacost));
    cost = Datacost.cost;
    Change_Coin();
    Servo_coin();
    if (ans[4] == 0) {
      ending.state = 5;
      esp_err_t result = esp_now_send(NinaAddress, (uint8_t *) &ending, sizeof(ending)); 
      if (result == ESP_OK) {
        Serial.println("Sent state_5 to Nina with success");
      }else {
        Serial.println("Error sending staus_5 to Nina");
      }
    }else {
      ending.state = 6;
      hbedt.state = 6;
      hbedt.debt = ans[4];      
      esp_err_t result = esp_now_send(NinaAddress, (uint8_t *) &ending, sizeof(ending)); 
      if (result == ESP_OK) {
        Serial.println("Sent state_6 to Nina with success");
      }else {
        Serial.println("Error sending staus_6 to Nina");
      }
      esp_err_t result_debt = esp_now_send(NunAddress, (uint8_t *) &hbedt, sizeof(hbedt)); 
      if (result_debt == ESP_OK) {
        Serial.println("Sent state_6 to Nun with success");
      }else {
        Serial.println("Error sending staus_6 to Nun");
      }
    }
    if (status_five == 0 || status_one == 0) {
      scoin.state = 12;
      scoin.state_1 = status_one;
      scoin.state_5 = status_five;
      esp_err_t result = esp_now_send(ViewAddress, (uint8_t *) &scoin, sizeof(scoin)); 
      if (result == ESP_OK) {
        Serial.println("Sent state_12 to View with success");
      }else {
        Serial.println("Error sending staus_12 to View");
      }
    }
  }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  Serial.begin(115200);
  servo_five.attach(13); //เหรียญ 5
  servo_one.attach(04); //เหรียญ 1
  servo_five.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
  delay(1000); // หน่วงเวลา 1000ms
  servo_one.write(90); // สั่งให้ Servo หมุนไปองศาที่ 90
  delay(1000); // หน่วงเวลา 1000ms
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void Servo_coin() 
{
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
}

void loop()
{
  
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