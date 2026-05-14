void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
 
  for(;;){
    update_measured_arr(); 
    double I_out = measured_results[4];
    double P_in = measured_results[2];
    if((I_out_reff_in_ma > I_out) && (I_out_reff_in_ma - I_out >= 2) )
      {
        duty++;
      }
  else if((I_out_reff_in_ma < I_out) && (I_out - I_out_reff_in_ma >= 2) )
      {
        duty--;
      }
   if(max_P_in <= P_in || max_current_out_in_ma <= I_out)
      {
        boost = 0;
      }
     

    if(duty > 990){  //Clamps duty cycle 
      duty = 990;
    }else if(duty < 10){
      duty = 10;
    }
    

    if(boost){    //Turn boost on or off and write duty cycle
      digitalWrite(EN_PIN, HIGH);
      ledcWrite(PWM_PIN, 1023-duty);
    }else{
      digitalWrite(EN_PIN, LOW);
    }
    //delay(1);  // Loop time
  }

  
}



 
