void Task1code( void * pvParameters ){    //peripheral core 
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    
  //for blakey to fill in 
  
  display.clearDisplay();
  display_screen(measured_results, 6); 

  delay(100);
  }

}
