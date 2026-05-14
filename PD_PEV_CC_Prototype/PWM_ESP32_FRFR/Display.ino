void display_screen(float *arr, int size){

  display.setTextSize(1);
  
  display.setCursor(1,1);
  display.print("Input:");
  
  display.setCursor(1,15);
  display.print(arr[0]);
  display.print("V");

  display.setCursor(1,30);
  display.print(arr[1]);
  display.print("mA");

  display.setCursor(1,45);
  display.print(arr[2]);
  display.print("W");

  display.setCursor(82,1);
  display.print("Output:");
  
  display.setCursor(82,15);
  display.print(arr[3]);
  display.print("V");

  display.setCursor(82,30);
  display.print(arr[4]);
  display.print("mA");

  display.setCursor(82,45);
  display.print(arr[5]);
  display.print("W");

  display.setCursor(50, 1);
  if(boost){
    display.print("ON");
  }else{
    display.print("OFF");
  }

  display.setCursor(50, 15);
  display.print(duty);

  display.display();
}
