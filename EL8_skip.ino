#include <MsTimer2.h> //ライブラリ宣言
//初期設定
const int buttonPin = 11; // 磁気センサーの番号
int num = 8; //使用するELワイヤーの本数
int all_on_flg = 0; //同時点灯用のフラグ
int timeflg = 0; //タイマー用フラグ
int buttonState = 0;//押しボタンの状態を読み取るための変数
int flg = 0; //磁気センサーに近づけた回数のフラグ
int flg2 = 0; //磁気センサー有効状態を０、無効状態を１と記録するフラグ
int swt = 0; //磁気センサー状態管理フラグ
unsigned int timeCount = 0; //プログラムの発動時間を設定するために使用
//関数設定
void all_on(); //同時点灯
void all_off(); //同時消灯
void blk(); //同時点滅
void rdm(); //ランダム

void timerFire() //タイムカウントの関数
{
  timeCount++; //秒ごとに＋１
}

void setup() //最初に一回だけ実行されるプログラミング
{
  for (int l_pin = 2; l_pin <= 9; l_pin++) //ELワイヤーで使用するピンを出力として初期化します
  {
    pinMode(l_pin, OUTPUT); //ELワイヤーで使用するピンを出力として初期化
  }
  pinMode(buttonPin, INPUT); //磁気センサー番号（１１番）を入力として初期化します。
  MsTimer2::set(1000, timerFire); //1秒ごとに呼び出す
  MsTimer2::start(); //タイマーを開始
  Serial.begin(9600);
}

void all_on() //同時点灯
{
  if (all_on_flg == 1) //同時点灯の状態の時
  {
    return; //同時点灯の関数に戻る、下は実行しない
  }
  //使用するELワイヤー全て「オン」にする
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    digitalWrite(l_pin , HIGH);
  }
  all_on_flg = 1; //同時点灯用のフラグを１にする
}

void all_off() //同時消灯
{
  if (all_on_flg > 0) //同時点灯の状態の時
  {
    all_on_flg = 0; //同時点灯用のフラグを０にする
  }
  //使用するELワイヤー全て「オフ」にする　
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    digitalWrite(l_pin , LOW);
  }
}

void blk() //同時点滅
{
  if (all_on_flg > 0) //同時点灯の状態の時
  {
    all_on_flg = 0; //同時点灯用のフラグを０にする
  }
  //使用するELワイヤー全て「オン」にする　
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    digitalWrite(l_pin , HIGH);
  }
  delay(850); //0.85秒間止まる
  //使用するELワイヤー全て「オフ」にする　
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    digitalWrite(l_pin , LOW);
  }
  delay(850); //0.85秒間止まる
}

void rdm() //ランダム中身（偶数と奇数で交互に光る）
{
  if (all_on_flg > 0) //同時点灯の状態の時
  {
    all_on_flg = 0; //同時点灯用のフラグを０にする
  }
  //偶数のELワイヤーを「オン」にする　
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    if (l_pin % 2 == 0)
    {
      digitalWrite(l_pin , HIGH);
    }
  }
  delay(850); //0.85秒間止まる
  //偶数のELワイヤーを「オフ」にする　
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    if (l_pin % 2 == 0)
    {
      digitalWrite(l_pin , LOW);
    }
  }
  //奇数のELワイヤーを「オン」にする　
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    if (l_pin % 2 == 1)
    {
      digitalWrite(l_pin , HIGH);
    }
  }
  delay(850); //0.85秒間止まる
  //奇数のELワイヤーを「オフ」にする　
  for (int l_pin = 2; l_pin <= num + 1; l_pin++)
  {
    if (l_pin % 2 == 1)
    {
      digitalWrite(l_pin , LOW);
    }
  }
}

void loop() //繰り返し
{
  int pWhileButtonState = LOW;

  // pButtonState = buttonState;
  // buttonState = digitalRead(buttonPin);
  // if (pButtonState == LOW && buttonState == HIGH)

  buttonState = digitalRead(buttonPin);
  //磁気センサーに使づいたとき
  if (buttonState == HIGH)
  {
    if (flg == 0 ) //初めて近づいたとき
    {
      flg = 1; //1回目の近づきで、フラグが１
    }
    else if (flg == 1 && flg2 == 1) //2回目近づいたとき
    {
      flg = 2; //２回目に近づいたときフラグが２
      swt = 1; //磁気センサー状態管理フラグを１
      timeflg = 0; //タイマー用フラグを１にする
    }
    else if (flg == 2 && flg2 == 1) //３回目近づいたとき
    {
      flg = 3;//３回目に近づいたときフラグが3
      swt = 1; //磁気センサー状態管理フラグを１
      timeflg = 0 ; //タイマー用フラグを１にする
    }
  }
  //スイッチを押した回数による処理内容の条件分岐
  if (flg == 1 && swt == 0) //スイッチ１回目
  {
    if (timeflg == 0) //タイムカウントを０に初期化
    {
      timeCount = 0; //タイマー用フラグが０の時（同時点灯状態でないとき）
      timeflg = 1; //タイマー用フラグを１にする
    }
    pWhileButtonState = LOW; // whileの前に必ず
    while (timeCount <= 50) //５０秒間ループ
    {
      Serial.print("timeCount: ");
      Serial.println(timeCount);
      if (timeCount > 5) {
        int whileButtonState = digitalRead(buttonPin);
        Serial.print(whileButtonState);
        Serial.print("\t");
        Serial.print(whileButtonState);
        Serial.print("\t");
        Serial.println(timeCount);

        if (pWhileButtonState == LOW && whileButtonState == HIGH)
        {
          timeCount = 50;
          Serial.print("********");
          Serial.print(timeCount);
          Serial.println("********");
        }
        pWhileButtonState = whileButtonState;
      }


      if (timeCount <= 3) //３秒以内の時
      {
        all_on(); //同時点灯（３秒）
      }
      if (timeCount > 3 && timeCount <= 19) //３秒より大きく１９秒以内の時
      {
        blk(); //同時点滅（１６秒）
      }
      if (timeCount > 19 && timeCount <= 44) //１９秒より大きく４４秒以内の時
      {
        rdm(); //ランダム（２５秒）
      }
      if (timeCount > 44 && timeCount <= 50) //４４秒より大きく５０秒以内の時
      {
        blk(); //同時点滅（６秒）
      }
    }
    all_off(); //同時消灯（２回目まで）
    swt = 1; //磁気センサー状態管理フラグを１
    flg2 = 0; //磁気センサーを反応する状態にする
  }
  if (flg == 2  && swt == 1) //スイッチ２回目
  {
    if (timeflg == 0) //タイマー用フラグが０の時（同時点灯状態でないとき）
    {
      timeCount = 0; //タイムカウントを０に初期化
      timeflg = 1; //タイマー用フラグを１にする
    }

    pWhileButtonState = LOW; // whileの前に必ず
    while (timeCount <= 159) //1５９秒間ループ
    {
          Serial.print("timeCount: ");
      Serial.println(timeCount);
      if (timeCount > 5) {
        int whileButtonState = digitalRead(buttonPin);
        Serial.print(whileButtonState);
        Serial.print("\t");
        Serial.print(whileButtonState);
        Serial.print("\t");
        Serial.println(timeCount);

        if (pWhileButtonState == LOW && whileButtonState == HIGH)
        {
          timeCount = 159;
          Serial.print("********");
          Serial.print(timeCount);
          Serial.println("********");
        }
        pWhileButtonState = whileButtonState;
      }
      if (timeCount <= 14) //１４秒以内の時
      {
        rdm(); //ランダム（１４秒）
      }
      if (timeCount > 14 && timeCount <= 36) //１４秒より大きく３６秒以内の時
      {
        all_on(); //同時点灯（２２秒）
      }
      if (timeCount > 36 && timeCount <= 46) //３６秒より大きく４６秒以内の時
      {
        blk(); //同時点滅（１０秒）
      }
      if (timeCount > 46 && timeCount <= 76) //４６秒より大きく７６秒以内の時
      {
        all_on(); //同時点灯（３０秒）
      }
      if (timeCount > 76 && timeCount <= 83) //７６秒より大きく８３秒以内の時
      {
        blk(); //同時点滅（７秒）
      }
      if (timeCount > 83 && timeCount <= 109) //８３秒より大きく１０９秒以内の時
      {
        all_on(); //同時点灯（２６秒）
      }
      if (timeCount > 109 && timeCount <= 116) //１０９秒より大きく１１６秒以内の時
      {
        blk(); //同時点滅（７秒）
      }
      if (timeCount > 116 && timeCount <= 142) //１１６秒より大きく１４２秒以内の時
      {
        all_on(); //同時点灯（２６秒）
      }
      if (timeCount > 142 && timeCount <= 159) //１４２秒より大きく１５９秒以内の時
      {
        blk(); //同時点滅（１７秒）
      }
    }
    all_off(); //同時消灯（３回目まで）
    flg2 = 0; //磁気センサーを反応する状態にする
  }
  if (flg == 3  && swt == 1) //スイッチ３回目　
  {
    if (timeflg == 0) //タイマー用フラグが０の時（同時点灯状態でないとき）
    {
      timeCount = 0; //タイムカウントを０に初期化
      timeflg = 1; //タイマー用フラグを１にする
    }
    all_on(); //同時点灯（終わりまで）
    flg2 = 0; //磁気センサーを反応する状態にする
  }
  if (buttonState == LOW)  //磁気センサーから遠ざかったとき
  {
    flg2 = 1; //磁気センサーを無効にする
  }
}
